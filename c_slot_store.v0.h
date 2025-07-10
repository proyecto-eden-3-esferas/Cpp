#ifndef C_SLOT_STORE_H
#define C_SLOT_STORE_H

/* Class c_slot_store<>
 * It handles C-style strings, that is '\0'-terminated strings of characters
 *
 * NOTES:
 * It is assumed that template argument CHAR is a char.
   Still, derived classes may carry on this assumption
   as well as implement partial specializations for other char types
   if seen suitable
 * EXCEPTIONS:
 (1) std::overflow_error("MESSAGE") (members read(...) and write(...) )
 (2) std::out_of_range              (vector::at)
 * TODOs:
 */
#include  <filesystem>
#include     <fstream>
#include    <iostream>
#include <string_view>
#include      <vector>

template <typename CHAR = char, template <typename> typename CONT = std::vector>
class c_slot_store {
public:
  using size_t     = std::size_t;
  using idx_t      = std::size_t;
  using   string_view_t = std::basic_string_view<CHAR>;
  using       fstream_t = std::basic_fstream<CHAR>;
  using random_stream_t = fstream_t;
  using off_type        = fstream_t::off_type;
  using c_slot_store_t    = c_slot_store<CHAR>;
  using      pchar_t    = CHAR* ;
  using     ppchar_t    = CHAR**;
//protected:
  struct String {
    pchar_t   pCh;
    size_t length;
    size_t capacity; // must accomodate '\0', too
    bool    dirty;
    //
    CHAR  operator[] (idx_t i) const {return pCh[i];};
    CHAR& operator[] (idx_t i)       {return pCh[i];};
    String() :                pCh(nullptr),  length(0),         dirty(false) {};
    String(const pchar_t p) : pCh(p),        length(sizeof(p)), dirty(false) {};
    ~String() {delete pCh;};
  }; // struct/class 'String'
  using string_container_t = CONT<String>;
        string_container_t        string_container;
  //bool is_dirty(idx_t i) const {return string_container[i].dirty;};
  //
  bool is_dirty(idx_t i) const;
  pchar_t get_pCh(size_t idx);
  //
  size_t slotsize;
  random_stream_t fs;
  //
  size_t size() const;
  // capacity: how long a string can the ith slot accomodate?
  virtual size_t get_capacity(idx_t i) const {return          slotsize;};
  virtual size_t total_slotsize()      const {return size() * slotsize;};
  virtual size_t start_offset(idx_t i) const {return i      * slotsize;};
  virtual size_t   end_offset(idx_t i) const {return start_offset(i) + get_capacity(i);};
  virtual size_t         size(idx_t i) const {return string_container[i].length;}; // size of data in the ith slot
  virtual size_t   get_length(idx_t i) const {return string_container[i].length;};
  /* read from file into String object:
     write a String object to file: */
  virtual void  read(idx_t idx)                               noexcept(false);
  virtual void  read(idx_t idx, ppchar_t ppCh)                noexcept(false);
  virtual void write(idx_t idx)                               noexcept(false);
  virtual void write(idx_t idx, const pchar_t    s)           noexcept(false);
  virtual void write(idx_t idx, const pchar_t    s, size_t n) noexcept(false);
  string_view_t get_string_view(idx_t i);
  void flush() {fs.flush();};
  // Constructors (must handle std::fstream fs) and destructor:
  c_slot_store(const pchar_t name, size_t slsz = 100, size_t n = 100);
  ~c_slot_store();
};

#endif
