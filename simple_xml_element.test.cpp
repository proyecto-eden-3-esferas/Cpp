/* File "simple_xml_element.test.cpp"
 * Simple XML Representation:
     class/struct 'simple_xml_element'
 * It can be used for testing XML tokenizers/parser.
 * a class/struct with:
   - no attributes,
   - no namespace declarations,
   - no display variable (such as XMLelement<>::display, a class defined in "XML/XMLelement.h")
 * To implement indentation, you need to add quite a few pieces:
   (1) include "Level.h",
   (2) write a member function print(OSTREAM&, Level l=0) to overload print(OSTREAM&), and
   (3) add requisite boolean member variables (isBlock, holdsBlocks etc.)
       For instance, a paragraph is a block, but does not hold blocks,
       whereas       a section   is a block, and does     hold blocks, too.
       (You can borrow code from XML/XMLelement.h)
 */


#ifndef SIMPLE_XML_REPRESENTATION_H
#define SIMPLE_XML_REPRESENTATION_H

#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "NamedType.h"

struct    textnode_tag;
struct xml_comment_tag;

typedef NamedType<std::string,    textnode_tag> XML_textnode;
typedef NamedType<std::string, xml_comment_tag> XML_comment;

template <template <typename> typename SEQ>
struct simple_xml_element; // forward declaration

template <template <typename> typename SEQ = std::vector>
struct simple_xml_element {
  typedef std::variant<XML_textnode,
                       XML_comment,
                       simple_xml_element<SEQ>, simple_xml_element<SEQ>*> variant_t;
  typedef SEQ<variant_t> nodes_t;
  //
  std::string name;
  nodes_t nodes;
  //
  void emplace_text(   const std::string& txt) {nodes.emplace_back(XML_textnode(      txt));};
  void emplace_comment(const std::string& cmt) {nodes.emplace_back(XML_comment(       cmt));};
  void emplace_element(const std::string& ele) {nodes.emplace_back(simple_xml_element(ele));};
  void push_pointer(simple_xml_element<SEQ>* ptr) {nodes.push_back( (simple_xml_element*) ptr );};
  //
  virtual std::ostream& print(std::ostream& o = std::cout) const {
    o << '<' << name << '>';
    for(const auto & i : nodes)
      std::visit(printer(o), i);
    o << "</" << name << '>';
    return o;
  }
  struct printer {
    std::ostream & os;
    void operator() (const XML_textnode& txt) const { os << txt.get();};
    void operator() (const XML_comment&  cmt) const { os << "<!--" << cmt.get() << "-->";};
    void operator() (const simple_xml_element& sxe) const { sxe.print(os);};
    void operator() (const simple_xml_element* ptr) const {ptr->print(os);};
    printer(std::ostream& o) : os(o) {};
  };
  //
  simple_xml_element(const std::string & nm) : name(nm) {};
};

#endif


using namespace std;

int main () {
  simple_xml_element sxe0("book");
  sxe0.emplace_text("My first span of text. ");
  sxe0.emplace_comment("My first comment ");
  sxe0.emplace_text("My second span of text. ");

  simple_xml_element sxe1("chapter");
  sxe1.emplace_text("Introduction to this chapter. ");

  sxe0.push_pointer(&sxe1);

  sxe0.print();


  return 0;

}
