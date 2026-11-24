#ifndef INDENT_H
#define INDENT_H

#include <iostream>


template <typename CH = char>
class indentation {
  typedef std::size_t size_t;
  const size_t indent_spaces;
  size_t       indent_level;
public:
  indentation<CH>& operator++()  {++indent_level; return *this;};
  indentation<CH>& operator--()  {--indent_level; return *this;};
  indentation<CH>& reset_level() {indent_level= 0; return *this;};
  indentation<CH>& set_level( size_t l) {indent_level  = l; return *this;};
  indentation<CH>& set_spaces(size_t n) {indent_spaces = n; return *this;};
  std::ostream& operator()(std::ostream& o) const {
    for(int i = 0; i < indent_level; ++i)
      for(int j = 0; j <   indent_spaces; ++j)
        o << ' ';
    return o;
  };
  // constructor(s):
  indentation(size_t num_spaces = 2, size_t level = 0) : indent_spaces(num_spaces), indent_level(level) {};
};
template <typename CH=char>
std::ostream& operator<<(std::ostream& o, const indentation<CH> & ind) {
  return ind(o);
};


#endif
