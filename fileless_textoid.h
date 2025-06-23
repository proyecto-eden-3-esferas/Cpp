#ifndef FILELESS_TEXTOID_H
#define FILELESS_TEXTOID_H

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
 * A string is serialized to a file
   by writing its size, a space character, then the string (in text mode)
   A string is deserialized from a file
   by reading its size, a space character, then the string (in text mode)
   Thus, a string such as "charity" would be live in a file as: "7 charity"
 * fileless_textoid<> objects also hold information about
   how long a string they can store
   as room must be provided by the size overhead
   Member variable 'slot_capacity' holds this length, whereas
   member functions virtual get_slot_capacity(NUM),
   as well non-virtual get_slot_capacity(), and set_slot_capacity()
   handle slot capacity.
 * A sketch of class fileless_textoid<CHAR>:
   class fileless_textoid {
   protected:
     off_type offset;
     string_t contents;
     size_t slot_capacity;
   public:
     [const] string_t& get_text() [const];
     bool store(FILE&);
     bool  load(FILE&);
   }
 * Class fileless_textoid<> is the parent of class textoid<>.
 * I am aware that 'fileless_textoid<>' is a little cumbersome as a name
 * If an FSTREAM is provided, then FSTREAM& plus an offset define a slot,
   which provides enough information to do load/store (I/O)
   whereas objects of derived class textoid<> each hold a reference to an FSTREAM
   and thus already hold a reference to a file
 * Class fileless_textoid<> does not hold a reference to a string
   because references should not be (de)serialized, only values should.
 * It should be used for holding comparatively large strings,
   as a fileless_textoid<> object is 96 bytes, whereas a std::string is 32 bytes
 * NOTE:
 * TODO:
   [ ] write "throws" specifications
   [x] handle the case when no string or no offset has been provided at initialization...
       - Through an std::optional?
       - Through more bool variables or through setting and unsetting flags
         in an integer variable? Well, a bool on a 64 architecture takes up just one byte...
   [ ] review and expand code around fileless_textoid<> member vars: 'changed' and 'loaded'
   [ ] What if writing a STRING to a file overwrites the next STRING?
       - A simple scheme might set a limit as a template parameter (std::size_t MAX = 1000).
         The actual space available is the slot size less the length of the size string
         less one for an additional space.
         For a slot size of 1000, since the size could take as many as 3 characters,
         available space would be 996 bytes.
       - A more elaborate scheme could ask some overseer for confirmation
         or class fileless_textoid might have a 'maximum' member variable besides an 'offset'
         to be tweaked by, again, some overseer.
         Such an overseer is being developed as class 'fileless_textoid_handler'
   [ ] You might derive fileless_textoid<> from textoid_or_literal<>,
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
  off_type offset; // whereat in a file to start reading characters into 'contents'
  size_t slotsize;
  size_t slot_capacity; // how large a string can be serialized
  bool changed; // if true, then calling store() should write 'contents' to 'file'
  bool loaded;  // does string 'contents' hold a piece of text from file, as intended?
  bool    boff; // bool+offset: has an offset been provided so far?
public:
  // Exception classes:
  class  slot_overflow : public std::exception {};
  class  no_string     : public std::exception {};
  class  no_offset     : public std::exception {};
  //
  bool      is_loaded() const {return loaded;};
  bool     has_string() const {return loaded;};
  bool     has_offset() const {return   boff;}
  off_type get_offset() const {return offset;};
  size_t get_slotsize() const {return slotsize;};
  void   set_slotsize(size_t sz) {slotsize=sz;};
  size_t get_slot_capacity() const {return slot_capacity;};
  //
        string_t& get_text(fstream_t& f);
  const string_t& get_text(fstream_t& f) const;
  size_t            length(fstream_t& f) {return get_text(f).length();};
  void               clear() {loaded=false; contents.clear();};
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
  fileless_textoid();
  fileless_textoid(string_view_t s);
  //
  fileless_textoid(string_view_t s, off_type off);
  fileless_textoid(                 off_type off);
}; // class fileless_textoid

#endif
