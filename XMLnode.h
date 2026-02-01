#ifndef XMLNODE_H
#define XMLNODE_H

#ifndef LEVEL_H
#include "Level.h"
#endif

#include <iostream>

template <typename LEVEL = Level<signed int> >
struct XMLnode {
  virtual bool is_inline() const {return true;};
  virtual bool is_block()  const {return !is_inline();};
  virtual void print(std::ostream& o, LEVEL l) const = 0;
};

#endif
