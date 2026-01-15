#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
  typedef std::size_t size_t;
  //
  const Level& operator++() const {++level; return *this;};
        Level& operator++()       {++level; return *this;};
  //
  Level(size_t l = 0)   : level(l) {};
  Level(const Level& l) : level(l.level) {};
private:
  const std::size_t level;
};

#endif


