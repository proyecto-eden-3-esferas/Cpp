#ifndef FILELESS_TEXTOID_H
#include "fileless_textoid.h"
#endif

#ifndef FILELESS_TEXTOID_CPP
#define FILELESS_TEXTOID_CPP

template <typename CH, std::size_t SLOTSIZE>
std::size_t fileless_textoid<CH,SLOTSIZE>::get_slot_capacity(std::size_t max) {
  // return input param 'max' minus how many digits 'max' takes up as a string minus 2:
  return max - log10(max) - 2;
};

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

// constructors taking neither an FSTREAM& nor an OFFSET:

template <typename CH, std::size_t SLOTSIZE>
fileless_textoid<CH,SLOTSIZE>::fileless_textoid()
  :                          slotsize(SLOTSIZE), changed(false),loaded(false),boff(false)
{set_slot_capacity();};

template <typename CH, std::size_t SLOTSIZE>
fileless_textoid<CH,SLOTSIZE>::fileless_textoid(std::basic_string_view<CH> s)
  : contents(s),             slotsize(SLOTSIZE), changed(false),loaded(true), boff(false)
{set_slot_capacity();};

//

  template <typename CH, std::size_t SLOTSIZE>
fileless_textoid<CH,SLOTSIZE>::fileless_textoid(std::basic_string_view<CH> s,
                                                fileless_textoid<CH,SLOTSIZE>::off_type off)
  : contents(s),offset(off), slotsize(SLOTSIZE), changed(false),loaded(true), boff(true)
{set_slot_capacity();};

template <typename CH, std::size_t SLOTSIZE>
fileless_textoid<CH,SLOTSIZE>::fileless_textoid(fileless_textoid<CH,SLOTSIZE>::off_type off)
  :             offset(off), slotsize(SLOTSIZE), changed(false),loaded(false),boff(true)
{set_slot_capacity();};

#endif
