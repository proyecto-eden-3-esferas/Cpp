#ifndef XMLNODE_H
#define XMLNODE_H

/* Class XMLnode<> is an interface for (1) printing and (2) whatever else.
 * Concept PrintTransformer is defined in this file
   so that XMLnode<>::print_transformed(OSTREAM&, LEVEL, ENT)
   filters out a class that does not implement member print_transformed(OSTREAM&, STR) -> void
 * A simple model of PrintTransformer is defined (DefaultPrintTransformer), too.
   Still, a full PrintTransformer for XML is Entities<> (in file "Entities.h")
 * Interface XMLnode<> may be used for formats other than XML, such as JSON, LaTeX
 * This unit adds a template paramenter CHAR (for character type) to former "XMLnode.h"
 * XMLnode declares three virtual member functions:
   (1) virtual void print(std::basic_ostream<CHAR>& o, LEVEL l) const = 0 // pure
   (2) virtual void print_transformed(OSTREAM&, const PRINT_TRANSFORMER&,          LEVEL) const;
   (3) virtual void print_transformed(OSTREAM&, const PRINT_TRANSFORMER&, STRING&, LEVEL) const;
   where (2) defaults to just calling (1) and would be overriden by classes that hold a string to be transformed.


 * Besides, other members for handling display (block or inline) are defined
   They are also expected to be overriden further down the hierarchy.
 * TODO
   [x] define an/two enum (class) for block-inline and for holds blocks (or inlines)
   [ ] consider deleting (3)
       virtual void print_transformed(OSTREAM&, const PRINT_TRANSFORMER&, STRING&, LEVEL) const;
       because all we need is, well, (2)
   [ ] we should also consider deleting (1):
         virtual void print(std::basic_ostream<CHAR>& o, LEVEL l) const = 0 // pure
       as it is incapable of printing-transforming a string
   [ ] ...
 */


#ifndef LEVEL_H
#include "Level.h"
#endif

#include <concepts>
#include <iostream>
#include <map>
#include <string>

/* Define DefaultPrintTransformer
 * as a simple model of concept PrintTransformer
 * (which basically prints a string without transforming it at all) */
template <typename CHAR = char>
struct DefaultPrintTransformer {
  void print_transformed(std::basic_ostream<CHAR>& o, const std::basic_string<CHAR>& str) const {
    o << str;
  };
};

/* Define concept PrintTransformer
 * as a class that implements:
 *   void print_transformed(OSTREAM&, STRING)
 * This is a restriction on the third argument into (overrides of)
 * XMLnode::print_transformed
 */
template<class PT, typename CHAR = char>
concept PrintTransformer = requires(PT pt,
                                   std::basic_ostream<CHAR>& o,
                                   const std::basic_string<char>& str)
{
  { pt.print_transformed(o,str) } -> std::same_as<void>;
};

/* Forward declaration of Entities<CHAR,STRING,MAP>
   so as to provide a default for second template parameter of XMLnode<>
   instead of plain DefaultPrintTransformer.
 * WARNING This declaration may go unused in this (compilation) unit
           as simpler, plainer DefaultPrintTransformer seems more suitable.
 */
  /* virtual print_transformed(OSTREAM&,PRINT_TRANSFORMER,STR,LEVEL),
     whose default implementation just calls print(OSTREAM&, LEVEL),
     and is specifically meant to be overriden by XMLText.
   * NOTE Default implementation, as supplied here, discards 2nd input argument
   * WARNING Recursive invokation throughout a large XML tree
             threatens to be expensive as a pointer to an PrintTransformer
             gets repeatedly pushed onto the execution stack
             unless the compiler knows how to optimize the parameter away.
   */
template <typename CHAR, typename STRING, template <typename,typename> typename MAP>
class Entities;

template <typename CHAR = char,
          PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          typename LEVEL = Level<signed int> >
struct XMLnode {
  typedef XMLnode<CHAR,PT,LEVEL> XMLnode_t;
  typedef PT PrintTransformer_t;
  typedef std::basic_string<CHAR> string_t;
  enum class display {block_of_blocks, block_of_inlines, inline_of_inlines};
  //
  static bool is_block( display d);
  static bool is_inline(display d);
  static bool holds_blocks(display d);
  static bool holds_inlines(display d);
  //
  virtual bool is_inline() const {return true;}; // should be overriden
  virtual bool is_block()  const {return !is_inline();};
  // Printing member functions:
  virtual void print(std::basic_ostream<CHAR>& o, LEVEL l) const = 0;
  virtual void print_transformed(std::basic_ostream<CHAR>& o,
                                 const PrintTransformer_t& pt,
                                 LEVEL l=LEVEL(0)) const;
  virtual void print_transformed(std::basic_ostream<CHAR>& o,
                                 const PrintTransformer_t& pt,
                                 const string_t& str,
                                 LEVEL l=LEVEL(0)) const;
};

// Implementations:


template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
bool XMLnode<CHAR,PT,LEVEL>::is_block( display d) {
  switch (d) {
    case display::block_of_blocks: return true; break;
    case display::block_of_inlines:  return true; break;
    default:                       return false;
  }
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
bool XMLnode<CHAR,PT,LEVEL>::is_inline(display d) {
  switch (d) {
    case display::block_of_blocks:  return false; break;
    case display::block_of_inlines: return false; break;
    default:                        return true;
  }
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
bool XMLnode<CHAR,PT,LEVEL>::holds_blocks(display d) {
  switch (d) {
    case display::block_of_blocks: return true; break;
    default:                       return false;
  }
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
bool XMLnode<CHAR,PT,LEVEL>::holds_inlines(display d) {
  switch (d) {
    case display::block_of_blocks:  return false; break;
    case display::block_of_inlines: return true; break;
    default:                        return true;
  }
};


template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
void XMLnode<CHAR,PT,LEVEL>::print_transformed(std::basic_ostream<CHAR>& o,
                                               const PrintTransformer_t& pt,
                                               LEVEL l) const {
  print(o,l);
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
void XMLnode<CHAR,PT,LEVEL>::print_transformed(std::basic_ostream<CHAR>& o,
                                               const PT& pt,
                                               const string_t& str,
                                               LEVEL l) const {
  if(is_block())
    o << '\n' << l;
  pt.print_transformed(o, str);
};

#endif
