#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>

/* This file implements class Level<SIGNED_INT>
   which keeps tracks and manages the structural or hierarchical level that an object is (in).
 * By "level" I understand how down in a structural tree something is.
 * Levels start at 0...
 * The higher its level, the deeper the object is embedded.
 * Also, we may want to prevent going beyond some maximum level,
   for instance when recursively visiting a potentially cyclical structure.
   To this end a static 'max_level' member variable represents the maximum allowed level.
   and some action is taken (by member Level::check_depth()) when it gets exceeded,
   such as throwing an exception.
   It is declared static so as to keep creating and copying instances of Level light.
 * In computing, tracking levels allows readable printing of data,
   such as XML and JSON formats, by proper indenting and newlining.
 * Next, a FURTHER DISCUSSION OF LEVELS:
 * Some examples of levels:
   - a non-contained set is level 0, its elements (including its subsets) are level 1,
     the elements and subsubsets of its subsets are level 2, and so on
   - a book is level 0, whereas its chapters are at level 1
   - a box is level 0, the objects inside are level 1,
     the contents of its boxes (if any) are level 2
 * The nodes in a tree structure do have levels.
 * The nodes in a graph do not have unique levels,
   unless the graph is a DAG (directed acyclic graph)
 */


template <typename SINT = signed int>
class Level {
public:
  typedef SINT sint_t;
  typedef std::size_t  size_t;
  // getters
  sint_t       get()       const {return level;};
  sint_t       get_level() const {return get();};
  operator sint_t ()       const {return get();};
  //
  static inline size_t max_level = 30;
protected:
  struct depth_exception : public std::exception {
    std::string message;
    const char * what() const noexcept override { return message.data();};
    depth_exception(std::size_t l);
  };
  virtual void check_level() const;
  //
public:
  Level& operator++()    {++level; check_level(); return *this;};
  Level  operator++(int) {++level; check_level(); return Level(level - 1);};
  Level& operator--()    {--level; return *this;};
  Level  operator--(int) {--level; return Level(level + 1);};
  /* Member function std::ostream& print(std::ostream& o)
   * seems rather redundant,
   * as it should be implemented in a child class,
   * and relies on static member variable static_width.
   * Overriders should append override to its declaration.
   * On the other hand, why add another member variable 'width'?
   * After all, you usually want:
   * (1) levels to be shown as indentation of num * level, and
   * (2) just one 'num' (number of spaces per indentation level) per project.
   */
  inline static size_t static_width = 2;
  virtual std::ostream& print(std::ostream& o) const;
  // virtual std::ostream& operator() (std::ostream& o) const { return print(o); };
  //
  Level& operator=(const Level&  l) {level = l.level; return *this;};
  Level& operator=(      sint_t  l) {level = l;       return *this;};
  Level(sint_t l = 0)   : level(l) {};
  Level(const Level& l) : level(l.level) {};
protected:
  std::size_t level;
};

// Implementations of Level<> Member Functions:

template <typename SINT>
void Level<SINT>::check_level() const {
  if( get() > max_level)
    throw depth_exception(level);
};

template <typename SINT>
Level<SINT>::depth_exception::depth_exception(std::size_t l)
  : message("depth exceeded at level: ")
  { message.append(std::to_string(l));};

template <typename SINT>
std::ostream& Level<SINT>::print(std::ostream& o) const {
  for(int i = 0; i < this->get() * static_width; i++)
    o << ' ';
  return o;
};

// A global insertor for level:

template <typename SINT = signed int>
std::ostream& operator<< (std::ostream& o, const Level<SINT>& i) { return i.print(o); };


#endif
