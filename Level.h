#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

class Level {
public:
  typedef std::size_t size_t;
  //
  Level& operator++()    {++level; return *this;};
  Level  operator++(int) {++level; return Level(level - 1);};
  size_t get() const {return level;};
  operator size_t() const {return get();};
  //
  Level(size_t l = 0)   : level(l) {};
  Level(const Level& l) : level(l.level) {};
private:
  /*const */std::size_t level;
};

#endif
