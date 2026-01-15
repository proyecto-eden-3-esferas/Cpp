#ifndef XML_H
#define XML_H

/* Class XML* states some typedef's and holds variables:
 * - doctype
 * - attributes
 * - entities
 * PROBLEMS
 * (1) attributes and namespaces are inherited from ancestors on the XML tree,
 *     so each element node needs either to
 *     a) keep its own containers (of attributes and namespaces), or
 *     b) update it on the fly upon being requested for either
 * (2)
 * TODO s:
 * [ ] Should nodes be held by reference?
 * [ ] Handle levels towards providing proper indentation
 *     (perhaps by including "Level.h")
 *
 */

#include <list>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

/* Definition of structs/classes: XMLText, XMLprocessing_instruction, XMLCDATA and XMLdoc
 * none of which either hold objects of other classes
 *                   or inherit    from other classes
 */

struct XMLText {
  std::string text;
  XMLText(const std::string& s) : text(s) {};
};

struct XMLprocessing_instruction {
  std::string name;
  std::string instruction;
  XMLprocessing_instruction(const std::string& n, const std::string& i) : name(n), instruction(i) {};
};

struct XMLCDATA {
  const std::string text;
  XMLCDATA(const std::string& s) : text(s) {};
};


template <template <typename,typename> typename  MAP  = std::map> // container for entities: map or unodered_map
class XMLdoc {
public:
  typedef std::string string_t;
  typedef         MAP<string_t, string_t>    entities_t;
  //typedef XML<CONT,MAP> XML_t;
  //
  const string_t&   get_doctype()  const {return doctype;};
        entities_t& get_entities()       {return entities;};
  const entities_t& get_entities() const {return entities;};
  //
  XMLdoc(const string_t& s) : doctype(s) {};
private:
  const string_t doctype;
  entities_t    entities;
  //XMLroot_t xml_root;
};


template <template <typename>          typename CONT, // container for elements: array, list, forward_list...
          template <typename,typename> typename  MAP>    // containers for attributes and namespaces
class XMLelement; // Forward declaration

template <template <typename>          typename CONT = std::vector, // container for elements: array, list, forward_list...
          template <typename,typename> typename  MAP = std::map>    // containers for attributes and namespaces
class XMLelement {
public:
  typedef std::string string_t;
  typedef             string_t name_t;
  typedef XMLdoc<MAP> XMLdoc_t;
  typedef         MAP<string_t, string_t>  attributes_t;
  typedef         MAP<string_t, string_t>  namespaces_t;
  typedef         MAP<string_t, string_t>    entities_t;
  using XMLelement_t = XMLelement<CONT,MAP>;
  using XMLelement_text_or_CDATA = std::variant<
                                     string_t,
                                     XMLelement_t,
                                     XMLCDATA,
                                     XMLprocessing_instruction>;
  typedef CONT<XMLelement_text_or_CDATA> children_t;
  //
  const   string_t& get_doctype()  const {return doc.get_doctype();};
        entities_t& get_entities()       {return doc.get_entities();};
  const entities_t& get_entities() const {return doc.get_entities();};
  //
  const name_t& get_name() const {return name;};
//      string_t& get_doctype()       {return doc.get_doctype();};
//const string_t& get_doctype() const {return doc.get_doctype();};
        attributes_t& get_attributes()       {return attributes;};
  const attributes_t& get_attributes() const {return attributes;};
        namespaces_t& get_default_namespace()       {return default_namepace;};
  const namespaces_t& get_default_namespace() const {return default_namepace;};
        namespaces_t& get_namespaces()       {return namespaces;};
  const namespaces_t& get_namespaces() const {return namespaces;};
  //
protected:
  const XMLdoc_t     & doc;
  const XMLelement_t * parent;
  const name_t         name;
public:
  children_t           children;
//private:
  attributes_t   attributes;
  const string_t default_namepace;
  namespaces_t   namespaces;
  //std::map<string_t, string_t> attributes;
  // Member functions to handle member variables:
  XMLelement_t& add_element(const string_t& nm) {children.emplace_back(XMLelement_t{doc, nm, *this}); return *this;};
  /*
  XMLelement_t& operator+=(const XMLelement_t&              e) {children.push_back(e); return *this;};
  string_t& operator[](const string_t& s) {return attributes[s];};
  XMLelement_t& operator()(const string_t& n, const string_t& attr) {attributes[n] = attr; return *this;};
  XMLelement_t& operator+=(const XMLText&                   t) {children.push_back(t); return *this;};
  XMLelement_t& operator+=(const XMLprocessing_instruction& p) {children.push_back(p); return *this;};
  XMLelement_t& operator+=(const XMLCDATA&                  d) {children.push_back(d); return *this;};
  */
  // Constructor(s):
  XMLelement(const XMLdoc_t& d, const string_t& nm, const XMLelement_t& p) : doc(d), parent(&p),      name(nm) {};
  XMLelement(const XMLdoc_t& d, const string_t& nm)                        : doc(d), parent(nullptr), name(nm) {};
protected:
  XMLelement(const XMLdoc_t& d) : doc(d), parent(nullptr), name(d.get_doctype()) {};
};


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
