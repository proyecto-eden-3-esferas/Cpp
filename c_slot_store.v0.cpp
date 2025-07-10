#ifndef C_SLOT_STORE_CPP
#define C_SLOT_STORE_CPP

#ifndef C_SLOT_STORE_H
#include "c_slot_store.v0.h"
#endif

#include   <cstring>
#include <stdexcept>

template <typename CHAR, template <typename> typename CONT>
 bool c_slot_store<CHAR,CONT>::is_dirty(typename c_slot_store<CHAR,CONT>::idx_t i) const {
   return string_container[i].dirty;
};

template <typename CHAR, template <typename> typename CONT>
c_slot_store<CHAR,CONT>::pchar_t
c_slot_store<CHAR,CONT>::get_pCh(c_slot_store<CHAR,CONT>::idx_t idx) {
  if( string_container[idx].pCh == nullptr )
    this->read(idx);
  string_container[idx].dirty=true;
  return string_container[idx].pCh;
};

template <typename CHAR, template <typename> typename CONT>
c_slot_store<CHAR,CONT>::size_t
c_slot_store<CHAR,CONT>::size() const {
  return string_container.size();
};

// Implementations of read(IDX, STRING) and write(IDX, STRING[, N])
template <typename CHAR, template <typename> typename CONT>
void c_slot_store<CHAR,CONT>::read(c_slot_store<CHAR,CONT>::idx_t     idx) noexcept(false) {
  // check up on size()
  string_container[idx].pCh      = new CHAR[get_capacity(idx)];
  string_container[idx].capacity =          get_capacity(idx);
  string_container[idx].dirty    = false;

  fs.seekg(start_offset(idx));
  size_t end = end_offset(idx);
  int i = 0;
  CHAR c;
  for (/*rely on external 'i'*/; i < (get_capacity(idx) - 1); ++i) {
    c = fs.get();
    string_container[idx].pCh[i] = c;
    if ( c == '\0') {
      string_container[idx].length = i;
      break;
    }
  } // for
  if(i >= get_capacity(idx))
    throw std::overflow_error("reading larger than capacity c-string!");
};
template <typename CHAR, template <typename> typename CONT>
void c_slot_store<CHAR,CONT>::read(c_slot_store<CHAR,CONT>::idx_t idx,
                                   c_slot_store<CHAR,CONT>::ppchar_t ppCh) noexcept(false) {
  read(idx);
  *ppCh = string_container[idx].pCh;
};

template <typename CHAR, template <typename> typename CONT>
void c_slot_store<CHAR,CONT>::write(c_slot_store<CHAR,CONT>::idx_t idx) noexcept(false) {
  size_t n = strlen(string_container[idx].pCh);
  write(idx,        string_container[idx].pCh, n);
};
template <typename CHAR, template <typename> typename CONT>
void c_slot_store<CHAR,CONT>::write(c_slot_store<CHAR,CONT>::idx_t idx,
                              const c_slot_store<CHAR,CONT>::pchar_t s) noexcept(false) {
  size_t n = strlen(s);
  std::cout << "Writing string: \"" << s << "\", which is " << n << " chars long.\n";
  write(idx,s,n);
};
template <typename CHAR, template <typename> typename CONT>
void c_slot_store<CHAR,CONT>::write(c_slot_store<CHAR,CONT>::idx_t idx,
                              const c_slot_store<CHAR,CONT>::pchar_t s,
                                    c_slot_store<CHAR,CONT>::size_t  n) noexcept(false) {
  if(n >= (get_capacity(idx) - 1) )
    throw std::overflow_error("writing larger than capacity c-string!");
  fs.seekp(start_offset(idx));
  fs.write(s, n);
  fs.put('\0');
  string_container[idx].dirty    = false;
};

template <typename CHAR, template <typename> typename CONT>
c_slot_store<CHAR,CONT>::string_view_t
c_slot_store<CHAR,CONT>::get_string_view(c_slot_store<CHAR,CONT>::idx_t i) {

  return string_view_t(get_pCh(i), get_pCh(i) + get_length(i) + 1);
};

// Implementation of constructors and destructors:
template <typename CHAR, template <typename> typename CONT>
c_slot_store<CHAR,CONT>::c_slot_store(const c_slot_store<CHAR,CONT>::pchar_t name,
                                            c_slot_store<CHAR,CONT>::size_t slsz,
                                            c_slot_store<CHAR,CONT>::size_t n)
: string_container(n), slotsize(slsz), fs(name) {
  std::filesystem::resize_file(name, total_slotsize());
};
template <typename CHAR, template <typename> typename CONT>
c_slot_store<CHAR,CONT>::~c_slot_store() {fs.close();};

#endif
