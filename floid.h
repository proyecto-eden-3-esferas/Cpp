#ifndef FLOID_H
#define FLOID_H

#include <cmath>
#include <exception>
#include <fstream>
#include <functional> // for std::reference_wrapper
#include <iostream>
#include <string>
#include <variant>
#include "optional_ref.h"

#include <concepts>

template <typename C>
concept IsPayload = requires (C c, std::ifstream ifs, std::ofstream ofs) {
  c.length();
  c.clear();
  ofs << c;
  ifs >> c;
  c.load(ifs);
  c.store(ofs);
};

/* floid<> (FileLess objectOID) is a class that can hold
   either a [loadable] payload (such as string or a container) and/or a file offset
   (or some other reference, but currently no template parameter allows for choosing)
   to load some payload (a string?) from (a file, a string?) or to store it.
 * It is the parent of class oid<> (for objectOID), which adds a file reference.
 * If an FSTREAM is provided, then FSTREAM& plus an offset define a slot,
   whereas objects of derived class oid<> each hold a reference to an FSTREAM.
 * It does not hold a reference to a string, container or anything else [loadable]
   because references should not be (de)serialized, only values should.
 * It should be used for holding comparatively large strings, containers and such.
 * TODO:
 * [ ] What is the use of length()?
 * [ ] Should member var 'payload' be a pointer? It may be, but not necessarily,
       as long as payload is a string, a container, or generally something loadable.
 * [ ] handle the case when no string or no offset has been provided at initialization...
       - Through an std::optional?
       - Through more bool variables or through setting and unsetting flags
         in an integer variable? Well, a bool on a 64 architecture takes up just one byte...
 * [ ] review and expand code around floid<> member vars: 'changed' and 'loaded'
 * [ ] What if writing a PAYLOAD to a file overwrites the next PAYLOAD?
       - A simple scheme might set a limit as a template parameter (std::size_t MAX = 1000).
         The actual space available is the slot size less the length of the size string
         less one for an additional space.
         For a slot size of 1000, since the size could take as many as 3 characters,
         available space would be 996 bytes.
       - A more elaborate scheme could ask some overseer for confirmation
         or class floid might have a 'maximum' member variable besides an 'offset'
         to be tweaked by, again, some overseer.
         Such an overseer is being developed as class 'floid_handler'
 * [ ] You might derive floid<> from textoid_or_literal<>,
       or just define an std::variant<PAYLOAD,floid<>> and two function objects for
       calling load or store...
 * [ ] Test the visitor interface in file "floid-visitor.test.cpp"
*/
template <typename CH = char,
          std::size_t SLOTSIZE=1000,
          IsPayload PAYLOAD = std::basic_string<CH> >
class floid {
public:
  typedef floid<CH,SLOTSIZE,PAYLOAD> floid_t;
  typedef PAYLOAD                payload_t;
  typedef std::basic_fstream<CH> fstream_t;
  typedef fstream_t::off_type        off_type;
  typedef std::size_t               size_t;
protected:
  // Member variables: a PAYLOAD, file address, a boolean for offset set...
  payload_t payload;
  off_type offset;
  size_t slotsize;
  bool changed; // if true, then calling store() should write 'payload' to 'file'
  bool  loaded; //
  bool    boff; // bool+offset: has an offset been set?
public:
  // Exception classes:
  class  slot_overflow : public std::exception {};
  class  no_string     : public std::exception {};
  class  no_offset     : public std::exception {};
  //
  bool      is_loaded() const {return loaded;};
  bool    has_payload() const {return loaded;};
  bool     has_offset() const {return boff;}
  off_type get_offset() const {return offset;};
  size_t get_slotsize() const {return slotsize;};
  void   set_slotsize(size_t sz) {slotsize=sz;};
  //
        payload_t& get_payload(fstream_t& f);
  const payload_t& get_payload(fstream_t& f) const;
  size_t length(fstream_t& f) {return get_payload(f).length();};
  void    clear() {loaded=false; payload.clear();};
  // ram_*() members handle member PAYLOAD 'payload'
  size_t ram_length() const {  return payload.length();};
  void   ram_clear()   {loaded=false; payload.clear();};
  bool store(fstream_t& f); // = 0;
  bool load( fstream_t& f); // = 0;
  // assignment of PAYLOAD 'payload' and FILE 'offset':
  floid_t& set_contents(const payload_t & p) {payload=p, changed=true, loaded=true; return *this;};
  floid_t& operator=(   const payload_t & p) {payload=p, changed=true, loaded=true; return *this;};
  //floid_t& operator=( const payload_t& p) {payload=p, changed=true, loaded=true; return *this;};
  floid_t& set_offset(off_type off) {offset=off;                 boff=true; return *this;};
  floid_t& operator()(off_type off) {offset=off;                 boff=true; return *this;};
  floid_t& operator=( off_type off) {offset=off,                 boff=true; return *this;};
  /* The visitor interface for handling containers or ranges of variant_t objects:
   * Now, since this was originally designed for STRINGS, not for just any PAYLOAD,
   * operator<< does not insert some types well.
   * Specifically, the PAYLOAD may be a struct or a class...
   */
  typedef std::reference_wrapper<payload_t>                    payload_ref_wrapper_t;
  typedef std::variant<payload_t,payload_ref_wrapper_t,floid_t> variant_t;
  struct print_visitor {
    std::basic_ostream<CH>& os;
    std::basic_fstream<CH>& fs;
    print_visitor(std::basic_ostream<CH>& o, std::basic_fstream<CH>& f) : os(o), fs(f) {};
    void operator() (const  payload_t&     pl)  const {os << pl;};
    void operator() (payload_ref_wrapper_t prw) const {os << prw.get();};
    void operator() (         floid_t&     fld) const {os << fld.get_payload(fs);};
  };
  // constructors taking no OFFSET:
  floid() :                                slotsize(SLOTSIZE), changed(false), loaded(false),boff(false) {};
  floid(const payload_t & p) : payload(p), slotsize(SLOTSIZE), changed(false), loaded(true), boff(false) {};
  //
  floid(const payload_t & p, off_type off) : payload(p),offset(off), slotsize(SLOTSIZE),
                                             changed(false), loaded(true),  boff(true) {};
  floid(off_type off) :                                 offset(off), slotsize(SLOTSIZE),
                                             changed(false), loaded(false), boff(true) {};
}; // class floid

// const and non-const implementations of get_payload(FSTREAM&) first load(f) if loaded==false,
// They only differ in that non-const version sets 'changed' to true
template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
floid<CH,SLOTSIZE,PAYLOAD>::payload_t& floid<CH,SLOTSIZE,PAYLOAD>::get_payload(std::basic_fstream<CH>& f)       {
  changed=true; // because a non-const reference to 'payload' is being returned
  if(loaded) {
    return payload;
  } else {
    load(f);
    return payload;
  }
};
template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
const floid<CH,SLOTSIZE,PAYLOAD>::payload_t& floid<CH,SLOTSIZE,PAYLOAD>::get_payload(std::basic_fstream<CH>& f) const {
  if(loaded)
    return payload;
  else {
    load(f);
    return payload;
  }
};
template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
bool floid<CH,SLOTSIZE,PAYLOAD>::store(std::basic_fstream<CH>& file) {
  if(length(file) <= slotsize) {
    if(!loaded)
      throw no_string();
    if(!boff)
      throw no_offset();
    file.seekp(offset);
    payload.store(file);
    return true;
  } else {
    throw slot_overflow();
    return false;
  }
};
template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
bool floid<CH,SLOTSIZE,PAYLOAD>::load(std::basic_fstream<CH>& file) {
  if(!boff)
    throw no_offset();
  file.seekg(offset);
  payload.load(file);
  loaded = true;
  changed = false;
  return true;
};


/** oid<CHAR> is a class that can hold either a payload and/or
   an FSTREAM& and a file offset to load one from file or to store it.
 * a (FSTREAM&, OFFSET) pair defines a slot
 * It does not hold a reference to a payload
   because references should be (de)serialized by value.
 * It should be used for holding comparatively large strings,
   as a oid object is 96 bytes, whereas a std::string is 32 bytes
 *
 * TODO:
 * (1) Handle the existence and size of (de)serializing file.
       Specifically, the constructor for std::fstream("myfile.txt")
       does NOT create file "myfile.txt" but it must already exist.
 * (2) review and expand code around oid<> member vars: 'changed' and 'loaded'
 * (3) What if writing a PAYLOAD to a file overwrites the next PAYLOAD?
       - A simple scheme might set a limit as a template parameter (std::size_t MAX = 1000).
         The actual space available is the slot size less the length of the size of payload
         less one for an additional space.
         For a slot size of 1000, since the size could take as many as 3 characters,
         available space would be 996 bytes.
       - A more elaborate scheme could ask some overseer for confirmation
         or class oid might have a 'maximum' member variable besides an 'offset'
         to be tweaked by, again, some overseer.
 * (4) You might derive oid<> from textoid_or_literal<>,
       or just define an std::variant<PAYLOAD,oid<>> and two function objects for
       calling load or store...
*/
template <typename CH = char, std::size_t SLOTSIZE=1000, IsPayload PAYLOAD = std::basic_string<CH> >
class oid : public floid<CH,SLOTSIZE,PAYLOAD> {
public:
  typedef floid<CH,SLOTSIZE,PAYLOAD>  parent_t;
  typedef   oid<CH,SLOTSIZE,PAYLOAD> textoid_t;
  typedef PAYLOAD      payload_t;
  typedef std::reference_wrapper<payload_t> payload_ref_wrapper_t;
  typedef std::basic_fstream<CH>     fstream_t;
  typedef optional_ref<fstream_t>    fstream_opt_ref_wrapper;
  typedef  fstream_t::off_type       off_type;
  typedef std::size_t                  size_t;
  //
  fstream_opt_ref_wrapper file;
  //
        payload_t& get_payload()       {return parent_t::get_payload(file);};
  const payload_t& get_payload() const {return parent_t::get_payload(file);};
  size_t length() {return get_payload().length();};
  void    clear() {return get_payload().clear();};
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
  textoid_t& operator=(const payload_t & p) {parent_t::operator=(p); return *this;};
  // The visitor interface for handling containers or ranges of variant_t objects:
  typedef std::variant<payload_t,payload_ref_wrapper_t,textoid_t> variant_t;
  struct print_visitor {
    std::basic_ostream<CH>& os;
    print_visitor(std::basic_ostream<CH>& o) : os(o) {};
    void operator() (const  payload_t&     pl) const {os << pl;};
    void operator() (payload_ref_wrapper_t prw) const {os << prw.get();};
    void operator() (      textoid_t&  fld) const {os << fld.get_payload();};
  };
  // constructors taking neither an FSTREAM& nor an OFFSET:
  oid()                                  {};
  oid(const payload_t & p) : parent_t(p) {};
  //
  oid(fstream_t& f, off_type off, const payload_t & p) :
                             parent_t(p,off), file(f) {};
  oid(fstream_t& f, off_type off) :
                             parent_t(off),   file(f) {};
}; // class oid
template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
bool oid<CH,SLOTSIZE,PAYLOAD>::store() {
  if(has_file()) return parent_t::store(file.get());
  else           return false;
};

template <typename CH, std::size_t SLOTSIZE, IsPayload PAYLOAD>
bool oid<CH,SLOTSIZE,PAYLOAD>::load() {
  if(has_file()) return parent_t::load(file.get());
  else           return false;
};

#endif
