#ifndef INDENT_H
#define INDENT_H

#ifndef LEVEL_H
#include "Level.h"
#endif

#include <iostream>

/* Manage indenting with class Indent.
 * Class Indent is used as an output manipulator.
 * WARNING Code like this:
 *   OSTREAM << ++indent_object;
 * results in:
 *   ++indent_object;
 *   OSTREAM << indent_object.level << indent_object
 * while you probably wanted:
 *   ++indent_object;
 *   OSTREAM << indent_object;
 * so don't pre or post-increment on the go!
 */


template <typename SINT = signed int>
class Indent : public Level<SINT> {
public:
  typedef        SINT   int_t;
  typedef std::size_t  size_t;
  typedef Level<SINT>  Level_t;
  typedef Indent<SINT> Indent_t;
  using               Level_t::get;
  using               Level_t::level;
  //using Level_t::Level; // inherit constructors
  Indent_t& operator++()    {++level; return *this;};
  Indent_t  operator++(int) {++level; return Indent_t(level - 1, width);};
  Indent_t& operator--()    {--level; return *this;};
  Indent_t  operator--(int) {--level; return Indent_t(level + 1, width);};
  //
  std::ostream& print(std::ostream& o) const override {
    for(int i = 0; i < this->get() * width; i++)
      o << ' ';
    return o;
  };
  // Constructors:
  Indent()                       : Level_t(0), width(2) {};
  Indent(size_t l, size_t w = 2) : Level_t(l), width(w) {};
private:
  std::size_t width;
};

#endif
