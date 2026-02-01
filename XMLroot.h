#ifndef XMLROOT_H
#define XMLROOT_H

#ifndef XML_H
#include "XML.h.bak"
#endif

/* The development of XMLroot has fallen behind.
 * Possibly DEPRECATED
 * Fomerly, it represented an element (XMLelement) whose name was its doctype...
 */

template <template <typename>          typename CONT = std::vector, // container for elements: array, list, forward_list...
          template <typename,typename> typename  MAP = std::map>    // containers for attributes and namespaces
class XMLroot : public XMLelement<CONT,MAP> {
public:
  typedef std::string string_t;
  typedef             string_t name_t;
  typedef XMLdoc<         MAP> XMLdoc_t;
  typedef XMLelement<CONT,MAP> XMLelement_t;
  //
  const name_t& get_name() const {return XMLelement_t::doc.get_doctype();};
  XMLroot(const XMLdoc_t& d) : XMLelement_t(d) {};
};

#endif
