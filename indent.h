#ifndef INDENT_H
#define INDENT_H

#include <iostream>

/* Manage indenting though global variables 'indent_level' and 'indent_width'
 * indent is used as an output manipulator.
 * An alternative scheme is class Level in file "Level.h"
 */

std::size_t indent_level = 0;

std::size_t indent_width = 2;

std::ostream& indent(std::ostream& o) {
  for(int i = 0; i < indent_level*indent_width; i++)
    o << ' ';
  return o;
};

#endif
