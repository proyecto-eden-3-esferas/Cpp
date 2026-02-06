#ifndef XMLNODE_H
#define XMLNODE_H

/* Class XMLnode<> is an interface for:
   (1) printing
 * Concept PrintTransformer is defined in this file
   so that print_transformed(OSTREAM&, LEVEL, ENT)
   filters out a class that does not implement print_transformed(OSTREAM&, STR)
 * A simple model of PrintTransformer is defined (DefaultPrintTransformer), too.
 * This interface may be used for formats other than XML, such as JSON and TeX/LaTeX
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
struct DefaultPrintTransformer {
  void print_transformed(std::ostream& o, const std::string& str) const {
    o << str;
  };
};

/* Define concept PrintTransformer
 * as a class that implements:
 *   void print_transformed(OSTREAM&, STRING)
 * This is a restriction on the third argument into (overrides of)
 * XMLnode::print_transformed
 */
template<class PT>
concept PrintTransformer = requires(PT pt, std::ostream& o, const std::string& str)
{
  { pt.print_transformed(o,str) } -> std::same_as<void>;
};

/* Forward declaration of Entities<STRING,MAP>
   so as to provide a default for second template parameter of XMLnode<>
   instead of plain DefaultPrintTransformer.
 * WARNING This declaration may go unused in this (compilation) unit
           as simpler, plainer DefaultPrintTransformer seems more suitable.
 */
template <typename STRING, template <typename,typename> typename MAP>
class Entities;

template <PrintTransformer PT = DefaultPrintTransformer,
          typename LEVEL = Level<signed int> >
struct XMLnode {
  typedef XMLnode<PT,LEVEL> XMLnode_t;
  typedef PT PrintTransformer_t;
  typedef std::string string_t;
  //
  virtual bool is_inline() const {return true;};
  virtual bool is_block()  const {return !is_inline();};
  // Printing member functions:
  virtual void print(std::ostream& o, LEVEL l) const = 0;
  /* virtual print_transformed(OSTREAM&,PRINT_TRANSFORMER,STR,LEVEL),
     whose default implementation just calls print(OSTREAM&, LEVEL),
     and is specifically meant to be overriden by XMLText and descendants.
   * NOTE Default implementation, as supplied here, discards 2nd input argument
   * WARNING Recursive invokation throughout a large XML tree
             threatens to be expensive as a pointer to an PrintTransformer
             gets repeatedly pushed onto the execution stack
             unless the compiler knows how to optimize the parameter away.
   */
  virtual void print_transformed(std::ostream& o,
                                 const PrintTransformer_t& pt,
                                 LEVEL l=LEVEL(0)) const;
  virtual void print_transformed(std::ostream& o,
                                 const PrintTransformer_t& pt,
                                 const string_t& str,
                                 LEVEL l=LEVEL(0)) const;
};

// Implementations:

template <PrintTransformer PT,
          typename LEVEL>
void XMLnode<PT,LEVEL>::print_transformed(std::ostream& o,
                                          const PrintTransformer_t& pt,
                                          LEVEL l) const {
  print(o,l);
};
template <PrintTransformer PT,
          typename LEVEL>
void XMLnode<PT,LEVEL>::print_transformed(std::ostream& o,
                                          const PT& pt,
                                          const string_t& str,
                                          LEVEL l) const {
  if(is_block())
    o << '\n' << l;
  pt.print_transformed(o, str);
};

#endif
