#ifndef XMLNODE_H
#define XMLNODE_H

/* Class XMLnode<> is an interface for:
   (1) printing
 * Concept PrintTransformer is defined in this file
   so that print_transformed(OSTREAM&, LEVEL, ENT)
   filters out a class that does not implement print_transformed(OSTREAM&, STR)
 * A simple model of PrintTransformer is defined (DefaultPrintTransformer), too.
 * This interface may be used for formats other than XML, such as JSON and TeX/LaTeX
 * This unit adds a template paramenter CHAR (for character type) to former "XMLnode.h"
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
template<class PT, class CHAR = char>
concept PrintTransformer= requires(PT pt,
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
