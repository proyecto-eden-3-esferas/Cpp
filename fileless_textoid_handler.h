#ifndef FILELESS_TEXTOID_HANDLER_H
#define FILELESS_TEXTOID_HANDLER_H

#ifndef TEXTOID_H
#include "textoid.h"
#endif

#include <cmath>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>


//#define DEBUG_HANDLER

/* Class fileless_textoid_handler<> manages fileless_textoid-like objects
   in a container (e.g. a std::vector)
 * and first and foremost changes offsets to accomodate strings
   larger than the standard slot size, or complex, bulky data structures.
 * The contained type (ELEM template param) must have the following members:
   - accessors: set_offset(off)    and get_offset()
   - accessors: set_slotsize(SIZE) and get_slotsize()
   - accessors: set_slot_capacity(), called to enforce inner consistency
   - bool loaded: this could be removed if elem_t::load(FSTREAM&) checked it
   - load(FSTREAM&) and store(FSTREAM&)
   - an inner class named no_offset (thrown when an element has no offset set: UNUSED CURRENTLY)
 */

/*
 * I have developed some code for handling slots that have been freed
   when multi-slotsize slots have been requested or particular slotsizes increased.
   I rely on two maps, from sizes to offsets and back,
   and have defined a helper function print_free(OSTREAM&) for testing and debugging.
   Should this section grow into a seperate class? Should it be named recycler<>?
 * bool 'offsets_warped' is set when offsets are no longer evenly spaced and growing,
   that is, either an element as received a different slotsize,
   or an element's offset has been changed.
   If changed, full serialization would demand that offsets be stored, too,
   maybe through print_offsets(OSTREAM&)
 * TODO:
   (1) Complete the body of:
       void TEXT_HANDLER<CH,SLOTSIZE,ELEM,CONT>::store()
       with code for checking that objects fit in their alloted slots.
       (A sketch of a solution has been provided in said body as a comment.)
   (2) Rename fileless_textoid_handler<> to, say, record_handler<>,
       and adapt "record.h" from zettelkasten/zettelkasten.h
       to conform with record_handler<>
   (3) Test and tweak the first constructor:
       fileless_textoid_handler::fileless_textoid_handler(BASE_FILENAME)
       meant for constructing unloaded objects of type elem_t
       and setting their corresponding offsets and slotsizes.
   (4) Discuss and implement how to use this class for holding serializable records with metadata
   (5) implement the reusing of freed offsets:
       - join contiguous runs of freed slots into one
 */
//#define LOAD_ALL_ELEMS_WHEN_INCREASING_SLOTSIZE
namespace fs = std::filesystem;
template <typename CH=char,
          std::size_t SLOTSIZE=1000,
          typename ELEM = fileless_textoid<CH,SLOTSIZE>,
          typename CONT=std::vector<ELEM> // remove? Code relies on CONT being indexable
         >
class fileless_textoid_handler {
public:
  // Same typedef's as in fileless_textoid:
  typedef ELEM elem_t;
  typedef std::basic_string<CH>      string_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::basic_fstream<CH>     fstream_t;
  typedef std::basic_ifstream<CH>   ifstream_t;
  typedef  fstream_t::off_type       off_type;
  typedef std::size_t                  size_t;
  typedef      size_t                 index_t;
  // Typedef's and vars for handling slot that have been freed when multi-slotsize slots have been requested:
  std::multimap<size_t,off_type> numfree_to_off_mm; // multimap from num of slotsizes to an unused offset
       std::map<off_type,size_t> off_to_numfree_m;  // map from unused offsets to num of slotsizes
  typedef std::pair<off_type,bool> off_bool_pair;   // return type of member reuse_offset_for_n_slots(N)
  //
        string_t fname;    // name of the serializing file
  const string_t offfname; // name of the file with cardinal\n then "offset slotsize" lines
  fstream_t fs;
  CONT fts; // a container of f[ileless] t[extoid]s
  size_t slotsize; // this may be changed by changing all offsets, protected/private?
  off_type highest_offset; // keep updated? obtainable from 'highest_idx', though
  index_t  highest_idx;    // keep updated
  off_type get_requested_size() const {return highest_offset + fts[highest_idx].get_slotsize();};
  size_t   get_current_size()   const {return fs::file_size(fname);};
  bool offsets_warped; // offsets are no longer evenly spaced and in ascending order
  //
  static size_t num_digits(size_t num) {return ceil(log10(num+1));};
  //
  const typename CONT::const_reference operator[](index_t i) const {return fts[i];};
        typename CONT::      reference operator[](index_t i)       {return fts[i];};
  size_t size() const {return fts.size();};
  void adjust_size();            // resize 'fs' to accomodate 'slots_available' slots
  void resize(double k=1.0);         // resize 'fs' to accomodate 'slots_available' * k (if k > 1)
  size_t add(const elem_t& e, size_t num_slots=1); // construct a textoid in 'fts'... and return its index
  void increase_slotsize(size_t newsz); // if newsz > slotsize, then multiply all ft.slotsize by a k > 1
  bool increase_slotsize_by(index_t idx, size_t num_slsz); // fts[idx].slotsize += num_slsz * slotsize
  void decrease_slotsize(size_t newsz) {}; // UNIMPLEMENTED
  void  load();
  void store(); // serialize out all fileless_textoid's to FSTREAM fs
  //
  size_t how_many_freed_offsets(size_t n) const {return numfree_to_off_mm.count(n);};
  void print_free(   std::basic_ostream<CH>& o = std::cout) const; // print freed offsets and such for debugging
  void print_offsets(std::basic_ostream<CH>& o = std::cout) const; // print offsets for serializing
  void print_offsets_and_slotsizes(std::basic_ostream<CH>& o = std::cout) const; // same, plus e.slotsize
  void print_size_offsets_and_slotsizes(std::basic_ostream<CH>& o = std::cout) const;
  void print_state(std::basic_ostream<CH>& o = std::cout) const;
  void write_size_offsets_and_slotsizes() const;
  // Member functions for handling slot that have been freed when multi-slotsize slots have been requested:
  void insert_numfree_and_offset(size_t n, off_type of); // called by increase_slotsize(IDX,N)
  void unregister_free_offset(off_type of)  {}; // UNIMPLEMENTED
  void splice_contiguous_freed()            {}; // UNIMPLEMENTED, POSSIBLY UNNECESSARY
  off_bool_pair reuse_offset_for_n_slots(size_t n); // returns a freed offset for n*slotsize bytes
  //
  fileless_textoid_handler() = delete;
  fileless_textoid_handler(string_view_t name); // initialize offsets and slotsizes from <name>.off
  fileless_textoid_handler(string_view_t name, size_t num_slots);
  ~fileless_textoid_handler();
}; // class fileless_textoid_handler

// Implementation of fileless_textoid_handler<> constructors and destructor:

template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::fileless_textoid_handler(string_view_t name)
: fname(name), offfname(fname + ".off"), slotsize(SLOTSIZE),
  highest_offset(0), highest_idx(0), offsets_warped(false) {
  ifstream_t temp(offfname);
  size_t n;
  off_type temp_off;
  size_t   temp_slotsize;
  temp.seekg(0);
  temp >> n;
  for(int i = 0; i < n; ++i) {
    fts.push_back(elem_t{});
    temp >> temp_off;
    temp >> temp_slotsize;
    //std::cout << "read offset " << temp_off << " and slotsize " << temp_slotsize << '\n';
    fts.back().set_offset(temp_off);
    fts.back().set_slotsize(temp_slotsize);
    if(temp_off > highest_offset) {
      highest_idx    = i;
      highest_offset = temp_off;
    }
  }
  temp.close();
  string_t objfname = fname + ".str"; fname = objfname;
  fs.open(fname, std::ios_base::in | std::ios_base::out);
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::fileless_textoid_handler(string_view_t name, size_t num_slots)
: fname(name), offfname(fname + ".off"), slotsize(SLOTSIZE),
  highest_offset(0), highest_idx(0), offsets_warped(false) {
  string_t objfname = fname + ".str"; fname = objfname;
  // if(!fs::exists(fname)) fstream_t{fname}; // useless
  fs::resize_file(fname,num_slots*SLOTSIZE);
  fs.open(fname, std::ios_base::in | std::ios_base::out);
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::~fileless_textoid_handler() {
  // call store(fs) on all its fileless_textoid<>'s?
  fs.close();
};

// Implementation of other fileless_textoid_handler<> member functions:
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::adjust_size() {
  const size_t requested = get_requested_size();
  if(get_current_size()  < requested)
    fs::resize_file(fname, requested);
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::resize(double k) {
  size_t num_bytes = get_requested_size();
  if(k > 1.0)
    num_bytes *= k;
  if(get_current_size() < num_bytes)
    fs::resize_file(fname,num_bytes);
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
std::size_t fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::add(const elem_t& e, size_t n) {
  if(n!=1)
    offsets_warped=true;
  fts.emplace_back(e);
  fts.back().set_slotsize(n*slotsize);
  off_bool_pair obp = reuse_offset_for_n_slots(n);
  if(obp.second)
    fts.back().set_offset(obp.first);
  else {
    if(size() > 1)
      highest_offset += fts[highest_idx].get_slotsize(); // add previous_elem.slotsize
    fts.back().set_offset(highest_offset);
    highest_idx    = fts.size() - 1;
    adjust_size();
  }
  return fts.size() - 1;
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::increase_slotsize(std::size_t newsz) {
  if(newsz > slotsize) {
    const size_t added_slot_capacity = newsz - slotsize;
#ifdef LOAD_ALL_ELEMS_WHEN_INCREASING_SLOTSIZE
    for(auto & ft : fts) // ensure all elements are loaded
      ft.load(fs);
#endif
    for(auto & ft : fts) {
    //if(ft.has_offset()) { // all elements in fts have offsets
        off_type temp = ft.get_offset();
                 temp /= slotsize;
                 temp *= newsz;
        ft.set_offset(temp);
        ft.set_slotsize((ft.get_slotsize() / slotsize)*newsz);
        ft.set_slot_capacity();
    //} else throw typename elem_t::no_offset();
    } // for
    highest_offset = (highest_offset / slotsize) * newsz;
    slotsize = newsz;
    fs::resize_file(fname, get_requested_size());
    offsets_warped=true;
  } // if
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::insert_numfree_and_offset(size_t n, off_type of) {
  numfree_to_off_mm.insert({n,of});
  off_to_numfree_m. insert({of,n});
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
bool fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::increase_slotsize_by(index_t idx, size_t num_slsz) {
  // fts[idx].slotsize += num_slsz * slotsize
//const size_t num_slots = (fts[idx].get_slotsize() / slotsize) + num_slsz;
//fts[idx].set_slotsize(    fts[idx].get_slotsize() + num_slsz*slotsize);
  fts[idx].set_slotsize( fts[idx].get_slotsize() + num_slsz*slotsize );
  fts[idx].set_slot_capacity();
  off_bool_pair obp = reuse_offset_for_n_slots((fts[idx].get_slotsize() / slotsize) + num_slsz);
  if(obp.second == true) {
    fts[idx].set_offset(obp.first);
#ifdef DEBUG_HANDLER
      std::cout << "recycling offset " << obp.first << '\n';
#endif
  } else {
    if(idx != highest_idx) {
      // discard fts[idx] slot and allocate a new one
#ifdef DEBUG_HANDLER
      std::cout << "increasing non highest offset...\n";
#endif
      insert_numfree_and_offset((fts[idx].get_slotsize())/slotsize - num_slsz,
                                fts[idx].get_offset());
      fts[idx].set_offset(highest_offset + fts[highest_idx].get_slotsize());
      highest_offset=fts[idx].get_offset();
      highest_idx   =    idx;
      offsets_warped=true;
    }
#ifdef DEBUG_HANDLER
     else std::cout << "increasing highest offset...\n";
#endif
    adjust_size();
  } // else
  return true;
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::load() {
  for(auto & ft : fts)
    ft.load(fs);
}
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::store() {
  /* make sure all objects fit in their alloted slots on disk
   * and make adjustments to offsets and object slotsizes.
   * This would require
   * (1) for all objects, calling some member function, like
         std::size_t OBJECT::estimate_requested_size() const, and
   * (2) increasing its alloted slotsize through increase_slotsize_by(idx,n)
   */
  adjust_size();
  for(auto & ft : fts)
    ft.store(fs);
};
// Implementation of fileless_textoid_handler<> member functions for printing:
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::print_free(std::basic_ostream<CH>& o) const {
  if(numfree_to_off_mm.empty())
    o << "No vacated slots. Bye!\n";
  else {
    o << "Free offsets for n*slotsize (slotsize=" << slotsize << "):\n";
    for(auto & e : numfree_to_off_mm)
      o << "- " << e.first << " * slotsize free at offset " << e.second << '\n';
    for(auto & e : off_to_numfree_m)
      o << "- at offset " << e.first << " there are " << e.second << " * slotsize(s) free bytes.\n";
  }
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::print_offsets(std::basic_ostream<CH>& o) const {
  for(auto & e : fts)
    o << e.get_offset() << ' ';
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::print_offsets_and_slotsizes(std::basic_ostream<CH>& o) const {
  for(auto & e : fts)
    o << e.get_offset() << ' ' << e.get_slotsize() << '\n';
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::print_size_offsets_and_slotsizes(std::basic_ostream<CH>& o) const {
  o << size() << '\n';
  print_offsets_and_slotsizes(o);
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::write_size_offsets_and_slotsizes() const {
  std::basic_ofstream<CH> tempof(offfname);
  print_size_offsets_and_slotsizes(tempof);
  tempof.close();
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::print_state(std::basic_ostream<CH>& o) const {
  o << "slotsize= " << slotsize;
  //o << ", slots_used=" << slots_used << ", slots_available=" << slots_available;
  o << ", offsets_warped=" << std::boolalpha << offsets_warped << '\n';
  print_size_offsets_and_slotsizes(o);
  print_free(o);
  o << "serializing file \"" << fname << "\" has size: " << get_current_size() << " bytes\n";
};
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::off_bool_pair fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::reuse_offset_for_n_slots(size_t n) {
  off_bool_pair obp{0,false};
  if(numfree_to_off_mm.contains(n)) {
    auto res = numfree_to_off_mm.find(n);
#ifdef DEBUG_HANDLER
    std::cout << "Found free offset (" << res->second << ") for " << res->first << " slotsize(s)\n";
#endif
    obp.first = res->second;
    obp.second = true;
    // now erase (n,offset) in map and multimap:
    numfree_to_off_mm.erase(res);
    auto res2 = off_to_numfree_m.find(res->second);
                off_to_numfree_m.erase(res2);
    // ...
  } // if
  return obp;
};
/*
template <typename CH, std::size_t SLOTSIZE, typename ELEM, typename CONT>
void fileless_textoid_handler<CH,SLOTSIZE,ELEM,CONT>::MEMBER_FUNCTION(PARAMS)
*/

#endif
