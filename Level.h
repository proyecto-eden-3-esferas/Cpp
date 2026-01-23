#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

/* This file implements class Level<SIGNED_INT>
   which keeps tracks and manages the structural or hierarchical level that an object is (in).
 * By "level" I understand how down in a structural tree something is.
 * Levels start at 0...
 * The higher its level, the deeper the object is embedded.
 * In computing, tracking levels allows readable printing of data
   such as XML and JSON formats.
 * Some examples:
   - a set is level 0, its elements (including its subsets) are level 1,
     the elements and subsubsets of its subsets are level 2
   - a book is level 0, whereas its chapters are at level 1
   - a box is level 0, its objects are level 1,
     the contents of its boxes (if any) are level 2
 * The nodes in a tree structure do have levels.
 * The nodes in a graph do not have unique levels,
   unless the graph is a DAG (directed acyclic graph)
 */

template <typename SINT = signed int>
class Level {
public:
  typedef SINT int_t;
  typedef std::size_t  size_t;
  //
  Level& operator++()    {++level; return *this;};
  Level  operator++(int) {++level; return Level(level - 1);};
  Level& operator--()    {--level; return *this;};
  Level  operator--(int) {--level; return Level(level + 1);};
  int_t       get() const {return level;};
  // avoid conversion operator?
  operator int_t () const {return level;};
  /* Member function std::ostream& print(std::ostream& o)
   * seems rather redundant,
   * as it should be implemented in a child class,
   * and relies on static member variable static_width.
   * Overriders should append overriden to its declaration.
   * On the other hand, why add another member variable 'width'?
   * You usually want:
   * (1) levels to be shown as indentation of num * level, and
   * (2) just one 'num' (number of spaces per indentation level) per project.
   */
  inline static size_t static_width = 2;
  virtual std::ostream& print(std::ostream& o) const {
    for(int i = 0; i < this->get() * static_width; i++)
      o << ' ';
    return o;
  };
  //
  Level& operator=(const Level& l) {level = l.level; return *this;};
  Level& operator=(      int_t  l) {level = l;       return *this;};
  Level(int_t  l = 0)   : level(l) {};
  Level(const Level& l) : level(l.level) {};
protected:
  std::size_t level;
};

template <typename SINT = signed int>
std::ostream& operator<< (std::ostream& o, const Level<SINT>& i) { return i.print(o); };


#endif
