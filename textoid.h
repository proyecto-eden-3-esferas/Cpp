#ifndef TEXTOID_H
#define TEXTOID_H

#include <cmath>
#include <exception>
#include <fstream>
#include <functional> // for std::reference_wrapper
#include <iostream>
#include <string>
#include <string_view>
#include <variant>
#include "optional_ref.h"

/* fileless_textoid<> is a class that can hold either a string
   and/or a file offset to load a string from file or to store it.
 * class fileless_textoid {
     off_type offset;
     string_t contents;
     [const] string_t& get_text() [const];
     bool store(FILE&);
     bool  load(FILE&);
   }
 * I am aware that its name is a little cumbersome...
 * It is the parent of class textoid<>.
 * If an FSTREAM is provided, then FSTREAM& plus an offset define a slot,
   whereas objects of derived class fileless_textoid<> each hold a reference to an FSTREAM
 * It does not hold a reference to a string
   because references should not be (de)serialized, only values should.
 * It should be used for holding comparatively large strings,
   as a fileless_textoid object is 96 bytes, whereas a std::string is 32 bytes
 * NOTE:
 * TODO:
 * (1) handle the case when no string or no offset has been provided at initialization...
       - Through an std::optional?
       - Through more bool variables or through setting and unsetting flags
         in an integer variable? Well, a bool on a 64 architecture takes up just one byte...
 * (2) review and expand code around fileless_textoid<> member vars: 'changed' and 'loaded'
 * (3) What if writing a STRING to a file overwrites the next STRING?
       - A simple scheme might set a limit as a template parameter (std::size_t MAX = 1000).
         The actual space available is the slot size less the length of the size string
         less one for an additional space.
         For a slot size of 1000, since the size could take as many as 3 characters,
         available space would be 996 bytes.
       - A more elaborate scheme could ask some overseer for confirmation
         or class fileless_textoid might have a 'maximum' member variable besides an 'offset'
         to be tweaked by, again, some overseer.
         Such an overseer is being developed as class 'fileless_textoid_handler'
 * (4) You might derive fileless_textoid<> from textoid_or_literal<>,
       or just define an std::variant<STRING,fileless_textoid<>> and two function objects for
       calling load or store...
*/
template <typename CH = char, std::size_t SLOTSIZE=1000>
class fileless_textoid {
public:
  typedef fileless_textoid<CH,SLOTSIZE> fileless_textoid_t;
  typedef std::basic_string<CH>      string_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::basic_fstream<CH>    fstream_t;
  typedef  fstream_t::off_type          off_type;
  typedef std::size_t                  size_t;
protected:
  // Member variables: a STRING, file address, a boolean for offset set...
  string_t contents;
  off_type offset;
  size_t slotsize;
  size_t slot_capacity; // how large a string can be serialized
  bool changed; // if true, then calling store() should write 'contents' to 'file'
  bool loaded;  //
  bool boff; // bool+offset: has an offset been provided so far?
public:
  // Exception classes:
  class  slot_overflow : public std::exception {};
  class  no_string     : public std::exception {};
  class  no_offset     : public std::exception {};
  //
  bool      is_loaded() const {return loaded;};
  bool     has_string() const {return loaded;};
  bool     has_offset() const {return boff;}
  off_type get_offset() const {return offset;};
  size_t get_slotsize() const {return slotsize;};
  void   set_slotsize(size_t sz) {slotsize=sz;};
  size_t get_slot_capacity() const {return slot_capacity;};
  //
        string_t& get_text(fstream_t& f);
  const string_t& get_text(fstream_t& f) const;
  size_t   size(fstream_t& f) {return get_text(f).length();};
  size_t length(fstream_t& f) {return get_text(f).length();};
  void    clear() {loaded=false; contents.clear();};
  // ram_*() members handle member STRING 'contents'
  size_t ram_size()   const {  return contents.length();};
  size_t ram_length() const {  return contents.length();};
  void   ram_clear()   {loaded=false; contents.clear();};
  bool store(fstream_t& f);
  bool load( fstream_t& f);
  static std::size_t get_slot_capacity(std::size_t max); // how big a string could be stored in a slot of 'max' bytes.
  void               set_slot_capacity() {slot_capacity=get_slot_capacity(slotsize);};
  // assignment of STRING 'contents' and FILE 'offset':
  fileless_textoid_t& set_contents(string_view_t s) {contents=s, changed=true, loaded=true; return *this;};
  fileless_textoid_t& operator=(   string_view_t s) {contents=s, changed=true, loaded=true; return *this;};
  //fileless_textoid_t& operator=( const string_t& s) {contents=s, changed=true, loaded=true; return *this;};
  fileless_textoid_t& set_offset(off_type off) {offset=off;                 boff=true; return *this;};
  fileless_textoid_t& operator()(off_type off) {offset=off;                 boff=true; return *this;};
  fileless_textoid_t& operator=( off_type off) {offset=off,                 boff=true; return *this;};
  // The visitor interface for handling containers or ranges of variant_t objects:
  typedef std::reference_wrapper<string_t>                    string_ref_wrapper_t;
  typedef std::variant<string_t,string_ref_wrapper_t,fileless_textoid_t> variant_t;
  struct print_visitor {
    std::basic_ostream<CH>& os;
    std::basic_fstream<CH>& fs;
    print_visitor(std::basic_ostream<CH>& o, std::basic_fstream<CH>& f) : os(o), fs(f) {};
    void operator() (const  string_t&     str) const {os << str;};
    void operator() (string_ref_wrapper_t srw) const {os << srw.get();};
    void operator() (      fileless_textoid_t&  txtoid) const {os << txtoid.get_text(fs);};
  };
  // constructors taking neither an FSTREAM& nor an OFFSET:
  fileless_textoid()
  :                                                   slotsize(SLOTSIZE), changed(false),loaded(false),boff(false) {set_slot_capacity();};
  fileless_textoid(string_view_t s)
  :                          contents(s),             slotsize(SLOTSIZE), changed(false),loaded(true), boff(false){set_slot_capacity();};
  //
  fileless_textoid(string_view_t s, off_type off)
  :                          contents(s),offset(off), slotsize(SLOTSIZE), changed(false),loaded(true), boff(true) {set_slot_capacity();};
  fileless_textoid(                 off_type off)
  :                                      offset(off), slotsize(SLOTSIZE), changed(false),loaded(false),boff(true) {set_slot_capacity();};
}; // class fileless_textoid

template <typename CH, std::size_t SLOTSIZE>
std::size_t fileless_textoid<CH,SLOTSIZE>::get_slot_capacity(std::size_t max) {
  // return input param 'max' minus how many digits 'max' takes up as a string minus 2:
  return max - log10(max) - 2;
}
template <typename CH, std::size_t SLOTSIZE>
bool fileless_textoid<CH,SLOTSIZE>::store(std::basic_fstream<CH>& file) {
  if(length(file) <= slot_capacity) {
    if(!loaded)
      throw no_string();
    if(!boff)
      throw no_offset();
    file.seekp(offset);
    file << get_text(file).length() << ' ' << get_text(file);
    return true;
  } else {
    throw slot_overflow();
    return false;
  }
};

template <typename CH, std::size_t SLOTSIZE>
bool fileless_textoid<CH,SLOTSIZE>::load(std::basic_fstream<CH>& file) {
  if(!boff)
    throw no_offset();
  file.seekg(offset);
  std::size_t len;
  //char c;
  file >> len;
  file.get(); // throw away one char
  //std::cout << "len = " << len << ", pos=" << file.tellg() << ", and c=\'" << c << '\'' << std::endl;
  char * pChar = new char[len + 1];
  file.read(pChar, len);
  pChar[len] = 0;
  contents = pChar;
  delete [] pChar;
  loaded = true;
  changed = false;
  return true;
};
// const and non-const implementations of get_text(FSTREAM&) first load(f) if loaded==false,
// They only differ in that non-const version sets 'changed' to true
template <typename CH, std::size_t SLOTSIZE>
fileless_textoid<CH,SLOTSIZE>::string_t& fileless_textoid<CH,SLOTSIZE>::get_text(std::basic_fstream<CH>& f)       {
  changed=true; // because a non-const reference to 'contents' is being returned
  if(loaded) {
    return contents;
  } else {
    load(f);
    return contents;
  }
};
template <typename CH, std::size_t SLOTSIZE>
const fileless_textoid<CH,SLOTSIZE>::string_t& fileless_textoid<CH,SLOTSIZE>::get_text(std::basic_fstream<CH>& f) const {
  if(loaded)
    return contents;
  else {
    load(f);
    return contents;
  }
};


/** textoid<CHAR> is a class that can hold either a string and/or
   an FSTREAM& and a file offset to load one from file or to store it.
 * a (FSTREAM&, OFFSET) pair defines a slot
 * It does not hold a reference to a string
   because references should be (de)serialized by value.
 * It should be used for holding comparatively large strings,
   as a textoid object is 96 bytes, whereas a std::string is 32 bytes
 *
 * TODO:
 * (1) Handle the existence and size of (de)serializing file.
       Specifically, the constructor for std::fstream("myfile.txt")
       does NOT create file "myfile.txt" but it must already exist.
 * (2) review and expand code around textoid<> member vars: 'changed' and 'loaded'
 * (3) What if writing a STRING to a file overwrites the next STRING?
       - A simple scheme might set a limit as a template parameter (std::size_t MAX = 1000).
         The actual space available is the slot size less the length of the size string
         less one for an additional space.
         For a slot size of 1000, since the size could take as many as 3 characters,
         available space would be 996 bytes.
       - A more elaborate scheme could ask some overseer for confirmation
         or class textoid might have a 'maximum' member variable besides an 'offset'
         to be tweaked by, again, some overseer.
 * (4) You might derive textoid<> from textoid_or_literal<>,
       or just define an std::variant<STRING,textoid<>> and two function objects for
       calling load or store...
*/
template <typename CH = char, std::size_t SLOTSIZE=1000>
class textoid : public fileless_textoid<CH,SLOTSIZE> {
public:
  typedef fileless_textoid<CH,SLOTSIZE> parent_t;
  typedef textoid<CH,SLOTSIZE> textoid_t;
  typedef std::basic_string<CH>      string_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::reference_wrapper<string_t> string_ref_wrapper_t;
  typedef std::basic_fstream<CH>     fstream_t;
  typedef optional_ref<fstream_t>    fstream_opt_ref_wrapper;
  typedef  fstream_t::off_type       off_type;
  typedef std::size_t                  size_t;
  //
  fstream_opt_ref_wrapper file;
  //
        string_t& get_text()       {return parent_t::get_text(file);};
  const string_t& get_text() const {return parent_t::get_text(file);};
  size_t   size() {return get_text().length();};
  size_t length() {return get_text().length();};
  void    clear() {return get_text().clear();};
  bool has_file() const {return file.has_value();};
  textoid_t& set_file_and_offset(fstream_t& f, off_type off) {file=f;
                                                              parent_t::set_offset(off);
                                                              return *this;};
  textoid_t&         operator() (fstream_t& f, off_type off) {file=f;
                                                              parent_t::set_offset(off);
                                                              return *this;};
  textoid_t&                 set(fstream_t& f, off_type off) {file=f;
                                                              parent_t::set_offset(off);
                                                              return *this;};
  bool store();
  bool load();
  void set_slotsize(std::size_t sl = SLOTSIZE) {
    parent_t::slotsize = sl;
    parent_t::slot_capacity=parent_t::get_slot_capacity(sl);
  };
  textoid_t& operator=(string_view_t s) {parent_t::operator=(s); return *this;};
  // constructors taking neither an FSTREAM& nor an OFFSET:
  textoid()                              {set_slotsize();};
  textoid(string_view_t s) : parent_t(s) {set_slotsize();};
  //
  textoid(fstream_t& f, off_type off, string_view_t s) :
                             parent_t(s,off), file(f) {set_slotsize();};
  textoid(fstream_t& f, off_type off) :
                             parent_t(off),   file(f) {set_slotsize();};
  // The visitor interface for handling containers or ranges of variant_t objects:
  typedef std::variant<string_t,string_ref_wrapper_t,textoid_t> variant_t;
  struct print_visitor {
    std::basic_ostream<CH>& os;
    print_visitor(std::basic_ostream<CH>& o) : os(o) {};
    void operator() (const  string_t&     str) const {os << str;};
    void operator() (string_ref_wrapper_t srw) const {os << srw.get();};
    void operator() (      textoid_t&  txtoid) const {os << txtoid.get_text();};
  };
}; // class textoid
template <typename CH, std::size_t SLOTSIZE>
bool textoid<CH,SLOTSIZE>::store() {
  if(has_file()) return parent_t::store(file.get());
  else           return false;
};

template <typename CH, std::size_t SLOTSIZE>
bool textoid<CH,SLOTSIZE>::load() {
  if(has_file()) return parent_t::load(file.get());
  else           return false;
};
#endif
