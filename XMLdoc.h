#ifndef XMLDOC_H
#define XMLDOC_H

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#ifndef XMLDOCDECL_H
#include "XMLdocdecl.h"
#endif

#ifndef XML_H
#include "XML.h"
#endif

#ifndef LEVEL_H
#include "Level.h"
#endif

#include <map>
#include <string>
#include <vector>

/* An XML document comprises:
   - an XML declarations
   - possibly, directives to include one or more stylesheets
   - a document declarations, as effected by the class XMLdocdecl<>
 */

template <typename LEVEL = Level<signed int>,
          template <typename>          typename CONT = std::vector, // sequential container for elements
          template <typename,typename> typename  MAP = std::map     // containers for attributes and namespaces
         >
class XMLdoc : public XMLnode<LEVEL> {
public:
  typedef std::string                    string_t;
  typedef XMLdocdecl<MAP,LEVEL>      XMLdocdecl_t;
  typedef XMLelement<LEVEL,CONT,MAP> XMLelement_t;
  typedef CONT<std::string>         stylesheets_t;
  const XMLdocdecl_t * pdocdecl;
  const XMLelement_t * proot;
  stylesheets_t stylesheets;
public:
  void add_stylesheet(const string_t& ss) {stylesheets.push_back(ss);};
public:
  void print_XML_declaration(std::ostream& o) const;
  void print_stylesheet_inclusions(std::ostream& o) const;
  void print_doc_declaration(std::ostream& o) const;
  void print_root(std::ostream& o) const ;
  //
  void print(std::ostream& o, LEVEL l) const override;
  // Constructor(s) and destructor
  XMLdoc() = delete;
  XMLdoc(const XMLdocdecl_t * pdd, const XMLelement_t * prt);
  virtual ~XMLdoc() = default;
};

// Implementation of member functions:

template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
void XMLdoc<LEVEL,CONT,MAP>::print_XML_declaration(std::ostream& o) const {
  o << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
};
template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
void XMLdoc<LEVEL,CONT,MAP>::print_stylesheet_inclusions(std::ostream& o) const {
  if(stylesheets.size()) {
    for(const auto& str : stylesheets)
      o << "<?xml-stylesheet type=\"text/css\" href=\"" << str << "\"?>\n";
  }
};
template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
void XMLdoc<LEVEL,CONT,MAP>::print_doc_declaration(std::ostream& o) const {
  pdocdecl->print(o, LEVEL(0));
};

template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
void XMLdoc<LEVEL,CONT,MAP>::print_root(std::ostream& o) const {
  proot->print(o,LEVEL(1));
};

template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
void XMLdoc<LEVEL,CONT,MAP>::print(std::ostream& o, LEVEL l) const {
  print_XML_declaration(o);
  print_stylesheet_inclusions(o);
  print_doc_declaration(o);
  proot->print(o, LEVEL(0));
};

template <typename LEVEL,
          template <typename> typename CONT,
          template <typename,typename> typename  MAP
         >
XMLdoc<LEVEL,CONT,MAP>::XMLdoc(const XMLdocdecl_t * pdd,
                               const XMLelement_t * prt) : pdocdecl(pdd) , proot(prt)
{};

#endif
