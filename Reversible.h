#ifndef REVERSIBLE_H
#define REVERSIBLE_H

#include <concepts>
#include <string>
#include <vector>


/* Compilation unit Reversible
 * defines concept Reversible as requiring to have members:
     void effect()
     void reverse()
 * Reversible objects can be called on to effect some change elsewhere
   and initializing them also loads data for undoing the change
 * and defines vector-like class ReversibleSequential
 TODO
 [ ] if you want changes to be redoable, you need a ReversibleVector class,
     that is one bases on an array-like structure such as std::vector or std::deque
 [ ] get concept Reversible to enforce the semantics that
     reverse() actually reverses the action of effect()
 [ ] define a Reversible class for operations on a target std::list
     this would enable editing a string and undoing the changes at will.
 [ ] define a Reversible class for operations on a file system
 [ ] ReversibleSequential should have a sequential or index-addressable container member,
     such as std::vector<Reversible>,
     for storing "deleted" objects.
     In the case of adding and deleting files, it would also need a path to a trash directory.
 [ ] ...
 */

template <typename REV>
concept Reversible = requires (REV rev)
{
  {rev.effect()}  -> std::same_as<void>;
  {rev.reverse()} -> std::same_as<void>;
};

struct TrivialReversible {
  void effect()  {};
  void reverse() {};
};

template <Reversible REV, template <typename> typename CONT = std::vector>
class ReversibleSequential {
  using container_t = CONT<REV>;
public:
  typedef container_t::size_type	         size_type;
  typedef container_t::value_type           value_type;
  typedef container_t::reference	         reference;
  typedef container_t::const_reference const_reference;
  typedef signed int cursor_t;
protected:
  container_t container;
  cursor_t cursor;
        reference current()       {return container[cursor];};
  const_reference current() const {return container[cursor];};
public:
  // Exception interface:
  static inline std::string
  undo_str{"trying to undo a change when all have already been undone!"},
  redo_str{"No change to be redone. Cursor already pointing to the latest change!"};
  struct no_change_to_undo; // an exception struct
  struct no_change_to_redo; // an exception struct
  //
  bool     empty()       const {return cursor == -1;};
  size_type size()       const {return container.size();};
  cursor_t  get_cursor() const {return cursor;};
  // Public members for adding/effecting, reversing and redoing changes:
  template <class... Args>
  void emplace_change(Args&&... args);
  void    push_change(const value_type& change); // adds change and calls change.effect()
  void    undo_change();
  void    redo_change();
  // Constructors and destructor
  ReversibleSequential() : cursor(-1) {};
};

// Implementations of ReversibleSequential<> members:

template <Reversible REV, template <typename> typename CONT>
struct ReversibleSequential<REV,CONT>::no_change_to_undo : public std::exception {
  const char * what() const noexcept {return undo_str.data();};
};
template <Reversible REV, template <typename> typename CONT>
struct ReversibleSequential<REV,CONT>::no_change_to_redo : public std::exception {
  const char * what() const noexcept {return redo_str.data();};
};


template <Reversible REV, template <typename> typename CONT>
template <class... Args>
void ReversibleSequential<REV,CONT>::emplace_change(Args&&... args) {
  container.emplace_back(args...);
  ++cursor;
  current().effect();
};



template <Reversible REV, template <typename> typename CONT>
void ReversibleSequential<REV,CONT>::push_change(const value_type& change) {
  container.push_back(change);
  ++cursor;
  current().effect();
};

template <Reversible REV, template <typename> typename CONT>
void ReversibleSequential<REV,CONT>::undo_change() {
  if(get_cursor() >= 0) {
    current().reverse();
    --cursor;
  }
  else
    throw no_change_to_undo();
};

template <Reversible REV, template <typename> typename CONT>
void ReversibleSequential<REV,CONT>::redo_change() {
  if( (cursor + 1) < container.size() )
    container[++cursor].effect();
  else
    throw no_change_to_redo();
};

#endif
