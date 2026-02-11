#ifndef XMLELEMENT_H
#define XMLELEMENT_H


#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#ifndef ATTRIBUTES_H
#include "Attributes.h"
#endif

#ifndef NAMESPACES_H
#include "Namespaces.h"
#endif

#ifndef ENTITIES_H
#include "Entities.h"
#endif

#ifndef LEVEL_H
#include "Level.h"
#endif

// Include unit XMLText as instances of XMLelement may hold instances thereof:
#ifndef XMLTEXT_H
#include "XMLText.h"
#endif


/* This unit contains a large XMLelement<> class
 * and possibly some near-analogous classes, too.
 * Perhaps each class, however interrelated,
   should live in its own header file, however short,
   and get tested separately.
 * ISSUES:
   (1) attributes and namespaces are inherited from ancestors on the XML tree,
       so each element node needs either to
       a) keep its own containers (of attributes and namespaces), or
       b) or references to an instance of Attributes and Namespaces
       c) update it on the fly upon being requested for attributes or namespaces
 * TODO s:
   [x] simplify XMLelement<>
       - no references to XMLdoc<>
       - start small (no namespaces nor attributes)
         then add attributes, then namespaces...
   [x] Handle levels towards providing proper indentation
       (perhaps by including "Level.h")
   [ ] Do not include "Entities.h"
 * TODO
   [x] Should children be held by value or by reference?
       By reference a mean a pointer, not a C++ reference,
       Perhaps only small nodes should be held by value
   [ ] 'children' is declared as a (sequential) container of pointers to XMLnode
       'children' should be prevented from pointing to instances of Namespaces<>, Attributes<>...
       This restriction could be enforced by declaring suitable overloads of add() and add_XMLelement()
   [ ] printing XMLelement does not indent/newline properly (see output of ./XMLelement.test)
   [ ] a pointer to parent node commits the implementation to a tree
   [x] 'namespaces' should hold a reference to Namespaces<>
       preferably with its 'ptr_to_above' member properly set
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>


/* The key, big class: XMLelement */
template <typename CHAR = char,
          PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          typename LEVEL = Level<signed int>,
          template <typename>          typename CONT = std::vector, // sequential container for elements
          template <typename,typename> typename  MAP = std::map     // containers for attributes and namespaces
         >
class XMLelement : public XMLnode<CHAR,PT,LEVEL>  {
public:
  typedef std::basic_string<CHAR> string_t;
  typedef                         string_t name_t;
  typedef Attributes<CHAR,PT,string_t,MAP,LEVEL>   Attributes_t;
  typedef Namespaces<CHAR,MAP,PT,LEVEL>            Namespaces_t;
  //
  typedef XMLnode<CHAR,PT,LEVEL> XMLnode_t;
  typedef                  const XMLnode_t * const_pointer;
  typedef                        XMLnode_t *       pointer;
  using typename XMLnode_t::display;
  //
  typedef XMLelement<CHAR,PT,LEVEL,CONT,MAP> XMLelement_t;
  typedef CONT<pointer> children_t; // a container of pointers to XMLnode<> instances
  //
//protected:
  //const XMLelement_t * parent;
  const name_t         name; // section, h1, body, main ...
  Attributes_t attributes;         // by value, unlike 'namespaces'
  string_t      default_namespace; // held inside the class, by value
  const Namespaces_t & namespaces; // a const C++ reference!
  children_t       children;
  display      display_mode;
  //
public:
  const name_t& get_name() const {return name;};
        Attributes_t& get_attributes()       {return attributes;};
  const Attributes_t& get_attributes() const {return attributes;};
  //
        Namespaces_t& get_namespaces()               {return namespaces;};
  const Namespaces_t& get_namespaces()         const {return namespaces;};
  void            set_default_namespace(const string_t& ns) {default_namespace = ns;};
  const string_t& get_default_namespace()      const;
  /* The following boolean getters are marked virtual
   * because a descendant might redefine them based on their names.
   * For instance, a paragraph (html::p or docbook::para)
   * has display block and holds inline elements. */
  virtual bool is_inline() const {return XMLnode_t::is_inline(display_mode);};
  virtual bool is_block()  const {return XMLnode_t::is_block( display_mode);};
  virtual bool holds_inlines() const {return XMLnode_t::holds_inlines(display_mode);};
  virtual bool holds_blocks()  const {return XMLnode_t::holds_blocks( display_mode);};
  //
  void print_opening_tag_unclosed(std::basic_ostream<CHAR>& o , LEVEL l) const;
  void print_opening_tag(std::basic_ostream<CHAR>& o , LEVEL l) const;
  void print(std::basic_ostream<CHAR>& o, LEVEL l) const override;
public:
//private:
  // Member functions to add children as const pointers to XMLnode<>:
  virtual void add(XMLnode_t &  node) {children.emplace_back(&node);};
  virtual void add(XMLnode_t * pNode) {children.emplace_back(pNode);};
  /* The following overloads of 'add_XMLelement' construct an XMLelement
     and store a reference to it in 'children'.
   * They follow the prototypes of constructors to a large extent.

  pointer add_XMLelement(const string_t& nm, display d = display::block_of_blocks);
  pointer add_XMLelement(const CHAR * pChar, display d = display::block_of_blocks);
  template <typename ITER>
  pointer add_XMLelement(const string_t& nm, ITER be, ITER en, display d = display::block_of_blocks)
  : name(nm), children(be,en), display_mode(d) {};
   */
  // Constructor(s) and destructor:
public:
  XMLelement(const Namespaces_t& ns, const string_t& nm, display d = display::block_of_blocks);
  XMLelement(const Namespaces_t& ns, const CHAR * pChar, display d = display::block_of_blocks);
  template <typename ITER>
  XMLelement(const Namespaces_t& ns, const string_t& nm, ITER be, ITER en, display d = display::block_of_blocks)
  : namespaces(ns), name(nm), children(be,en), display_mode(d) {};
  XMLelement()          = delete;
  virtual ~XMLelement() = default;
};

// Implementation of XMLelement<> member functions:


template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
const std::basic_string<CHAR>& XMLelement<CHAR,PT,LEVEL,CONT,MAP>::get_default_namespace() const {
  if( (default_namespace.length() > 0) || ! namespaces.has_parent())
    return default_namespace;
  else
    return namespaces.get_default_namespace();
};

template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<CHAR,PT,LEVEL,CONT,MAP>::print_opening_tag_unclosed(std::basic_ostream<CHAR>& o , LEVEL l) const {
  if(is_block())
    o << '\n' << l;
  o << '<' << get_name();
  // Print attributes:
  for(const auto & p : attributes)
    o << ' ' << p.first << '=' << '\"' << p.second << '\"';
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<CHAR,PT,LEVEL,CONT,MAP>::print_opening_tag(std::basic_ostream<CHAR>& o , LEVEL l) const {
  print_opening_tag_unclosed(o,l);
  o << '>';
  /*
  if(holds_blocks())
    o << '\n';
  */
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<CHAR,PT,LEVEL,CONT,MAP>::print(std::basic_ostream<CHAR>& o, LEVEL l) const {
  print_opening_tag(o,l);
  /* Print each item in 'children'
   * Remember to indent properly. */
  for(const auto& chi : children)
    chi->print(o, l+1);
  if(holds_blocks())
    o << l;
  o << "</" << get_name() << '>';
  if(is_block())
    o << '\n';
};

template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
XMLelement<CHAR,PT,LEVEL,CONT,MAP>::XMLelement(const Namespaces_t& ns,
                                               const string_t& nm,
                                               display d)
  : namespaces(ns), name(nm), display_mode(d)
  {};

template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
XMLelement<CHAR,PT,LEVEL,CONT,MAP>::XMLelement(const Namespaces_t& ns,
                                               const CHAR* pChar,
                                               display d)
  : namespaces(ns), name(pChar), display_mode(d)
  {};

#endif
