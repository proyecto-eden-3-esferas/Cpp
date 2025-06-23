#ifndef TEXTOID_H
#define TEXTOID_H

#ifndef FILELESS_TEXTOID_H
#include "fileless_textoid.h"
#endif

#ifndef FILELESS_TEXTOID_CPP
#include "fileless_textoid.cpp"
#endif

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

#endif
