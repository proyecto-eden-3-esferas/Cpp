#ifndef TEXTOID_CPP
#define TEXTOID_CPP

#ifndef TEXTOID_H
#include "textoid.h"
#endif

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
