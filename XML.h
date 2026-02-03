#ifndef XML_H
#define XML_H

#ifndef CASCADE_MAP_H
#include "CascadeMap.h"
#endif

#ifndef LEVEL_H
#include "Level.h"
#endif

/* Some tiny (XMLText, XMLComment, XMLCDATA etc.) and large XMLelement<> etc. classes.
 * Perhaps each class should live in its own header file (however short)
   and get tested individually.
 * TODO
   [ ] Each class should implement XMLprintable<MAP>, shouldn't it?
 * ISSUES:
   (1) attributes and namespaces are inherited from ancestors on the XML tree,
       so each element node needs either to
       a) keep its own containers (of attributes and namespaces), or
       b) update it on the fly upon being requested for attributes or namespaces
       The solution to be adopted is
       for XMLelement to contain attributes and namespaces as CascadeMap<>
   (2)
 * TODO s:
   [ ] XMLText::print(OSTREAM&,LEVEL) should process both default and defined entities
   [ ] write XMLCommentBlock
   [ ] write XMLCDATABlock
   [ ] write XMLprocessing_instructionBlock
   [x] simplify XMLelement<>
       - no references to XMLdoc<>
       - start small (no namespaces nor attributes)
         then add attributes, then namespaces...
   [x] Handle levels towards providing proper indentation
       (perhaps by including "Level.h")
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

/* Definition of structs/classes: XMLText, XMLprocessing_instruction, XMLCDATA and XMLdoc
 * none of which either hold objects of other classes
 *                   or inherit    from other classes
 */

template <typename LEVEL = Level<signed int> >
class XMLText : public XMLnode<LEVEL> {
protected:
  std::string text;
public:
  void print(std::ostream& o, LEVEL l) const override;
  //
  XMLText(const std::string& s) : text(s) {};
};
template <typename LEVEL>
void XMLText<LEVEL>::print(std::ostream& o, LEVEL l) const {
  for(auto c : text)
    {
      switch (c) {
        case '<' : o << "&lt;";   break;
        case '>' : o << "&gt;";   break;
        case '\'': o << "&apos;"; break;
        case '\"': o << "&quot;"; break;
        case '&':  o << "&amp;";  break;
        default:   o << c;
      }
    }
};

template <typename LEVEL = Level<signed int> >
struct XMLComment : XMLText<Level<signed int> > {
  using XMLText<Level<signed int> >::text;
  void print(std::ostream& o, LEVEL l) const override { o << "<!-- " << text << " -->";};
  //
  XMLComment(const std::string& com) : XMLText<LEVEL>(com) {};
};
template <typename LEVEL = Level<signed int> >
struct XMLCDATA : XMLText<Level<signed int> > {
  using XMLText<Level<signed int> >::text;
  void print(std::ostream& o, LEVEL l) const override { o << "<![CDATA[" << text << "]]>";};
  //
  XMLCDATA(const std::string& s) : XMLText<LEVEL>(s) {};
};
template <typename LEVEL = Level<signed int> >
struct XMLprocessing_instruction {
  std::string name;
  std::string instruction;
  void print(std::ostream& o, LEVEL l) const override { o << "<?" << name << ' ' << instruction  << " ?>";}
  //
  XMLprocessing_instruction(const std::string& n, const std::string& i) : name(n), instruction(i) {};
};



/* The key, big class: XMLelement
 * WARNING an XMLelement class is also defined in "XMLelement.h"
 * TODO
   [ ] Should children be held by value or by reference?
       By reference a mean a pointer, not a C++ reference,
       Perhaps only small nodes should be held by value
   [ ] a pointer to parent node commits the implementation to a tree
 */
template <typename LEVEL = Level<signed int>,
          template <typename>          typename CONT = std::vector, // sequential container for elements
          template <typename,typename> typename  MAP = std::map     // containers for attributes and namespaces
         >
class XMLelement : public XMLnode<LEVEL>  {
public:
  typedef std::string string_t;
  typedef             string_t name_t;
  typedef CascadeMap<string_t, string_t, std::map> CascadeMap_t;
  typedef CascadeMap_t attributes_t;
  typedef CascadeMap_t namespaces_t;
  typedef XMLnode<LEVEL> XMLnode_t;
  typedef const XMLnode_t * const_pointer;
  typedef       XMLnode_t *       pointer;
  typedef XMLelement<LEVEL,CONT,MAP> XMLelement_t;
  typedef CONT<pointer> children_t;
  //
//protected:
  //const XMLelement_t * parent;
  const name_t         name;
  attributes_t   attributes;
  string_t default_namepace;
  attributes_t   namespaces;
  children_t       children;
  bool                block; // whether this element has display="block""
  bool         hold_inlines; // whether this element holds inline elements
  //
public:
  const name_t& get_name() const {return name;};
        attributes_t& get_attributes()       {return attributes;};
  const attributes_t& get_attributes() const {return attributes;};
  void            set_default_namespace(const string_t& ns) {default_namepace = ns;};
        string_t& get_default_namespace()       {return default_namepace;};
  const string_t& get_default_namespace() const {return default_namepace;};
        namespaces_t& get_namespaces()       {return namespaces;};
  const namespaces_t& get_namespaces() const {return namespaces;};
  /* The following boolean getters are marked virtual
   * because a descendant might redefine them based on their names.
   * For instance, a paragraph (html::p or docbook::para)
   * has display block and holds inline elements. */
  virtual bool is_inline() const {return !block;};
  virtual bool is_block()  const {return  block;};
  virtual bool holds_inlines() const {return  hold_inlines;};
  virtual bool holds_blocks()  const {return !hold_inlines;};
  //
  void print_opening_tag_unclosed(std::ostream& o , LEVEL l) const;
  void print_opening_tag(std::ostream& o , LEVEL l) const;
  void print(std::ostream& o, LEVEL l) const override;
public:
//private:
  // Member functions to add children as const pointers to XMLnode<>:
  virtual void add(XMLnode_t &  node) {children.emplace_back(&node);};
  virtual void add(XMLnode_t * pNode) {children.emplace_back(pNode);};
  // Constructor(s) and destructor:
  XMLelement(const string_t& nm, bool blk=true, bool hi=false);
  template <typename ITER>
  XMLelement(const string_t& nm, ITER be, ITER en, bool blk=true, bool hi=false)
  : name(nm), children(be,en), block(blk), hold_inlines(hi) {};
  XMLelement()          = delete;
  virtual ~XMLelement() = default;
};

// Implementation of XMLelement<> member functions:

template <typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<LEVEL,CONT,MAP>::print_opening_tag_unclosed(std::ostream& o , LEVEL l) const {
  if(is_block())
    o << '\n' << l;
  o << '<' << get_name();
  // Print attributes:
  for(const auto & p : attributes)
    o << ' ' << p.first << '=' << '\"' << p.second << '\"';
};
template <typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<LEVEL,CONT,MAP>::print_opening_tag(std::ostream& o , LEVEL l) const {
  print_opening_tag_unclosed(o,l);
  o << '>';
  /*
  if(holds_blocks())
    o << '\n';
  */
};
template <typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
void XMLelement<LEVEL,CONT,MAP>::print(std::ostream& o, LEVEL l) const {
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

template <typename LEVEL,
          template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
XMLelement<LEVEL,CONT,MAP>::XMLelement(const string_t& nm, bool blk, bool hi)
  : name(nm), block(blk), hold_inlines(hi)
  {};
#endif
