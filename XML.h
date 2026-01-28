#ifndef XML_H
#define XML_H

#ifndef XML_PRINTABLE_H
#include "XMLprintable.h"
#endif

/* Some tiny (XMLText, XMLComment, XMLCDATA etc.) and large XML*<> classes.
 * Perhaps each class should live in its own header file (however short)
   and get tested individually.
 * TODO
   [ ] Each class should implement XMLprintable<MAP>, shouldn't it?
 *
 */
 /*
 * [...] they state some typedef's and hold variables:
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

#include <map>
#include <string>
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
struct XMLComment : XMLText {
  XMLComment(const std::string& com) : XMLText(com) {};
};
struct XMLCDATA : XMLText {
  XMLCDATA(const std::string& s) : XMLText(s) {};
};

struct XMLprocessing_instruction {
  std::string name;
  std::string instruction;
  XMLprocessing_instruction(const std::string& n, const std::string& i) : name(n), instruction(i) {};
};


/* Class XMLdoc<> holds entities (&mdash; &nbsp; etc.) and the 'doctype' string.
 * It offers suitable getters (for doctype and entities) and setters (for entities).
 * It is neither a child nor a parent.
 * XMLroot<> and each XMLelement<> hold references to an instance of XMLdoc<>
 */
template <template <typename,typename> typename  MAP  = std::map> // container for entities
class XMLdoc {
public:
  typedef std::string string_t;
  typedef             string_t key_t;
  typedef             string_t value_t;
  typedef MAP<key_t, value_t>    entities_t;
  //
  const string_t&   get_doctype()  const {return doctype;};
  //
  bool             has_entity(const key_t& e) const      {return entities.contains(e);};
  const string_t & get_entity(const key_t& k) const      {return entities.at(k);};
  void             set_entity(const key_t& k, const value_t& v) {entities[k] = v;};
  //
        entities_t& get_entities()       {return entities;};
  const entities_t& get_entities() const {return entities;};
  //
  XMLdoc(const string_t& s) :
    doctype(s),
    entities{ {"lt", "<"}, {"gt", ">"}, {"apos", "\'"}, {"quot", "\""}, {"amp", "&"} }
  {};
private:
  const string_t doctype;
  entities_t    entities;
};

/* The key, big class: XMLelement
 * WARNING an XMLelement class is also defined in "XMLelement.h"
 * TODO
 * [ ] Write a function object for std::visit to print contained nodes...
 * [ ] Should children be held by value or by reference?
 *     By reference a mean a pointer, not a C++ reference,
 *     as "[a] variant must have no reference alternative" (according to g++)
 */


template <template <typename>          typename CONT, // container for elements: array, list, forward_list...
          template <typename,typename> typename  MAP>    // containers for attributes and namespaces
class XMLelement; // Forward declaration for both XMLelement_variant<> and and XMLelement<> itself


template <template <typename>          typename CONT,
          template <typename,typename> typename  MAP>
class XMLelement_variant {
public:
  typedef std::string string_t;
  using XMLelement_t = XMLelement<CONT,MAP>;
  // A no-member-variables class centered around 'XML_variant_t':
  using XML_variant_t = std::variant<
    XMLText,
    XMLCDATA,
    XMLComment,
    XMLelement_t,
    XMLprocessing_instruction,
    string_t,
    // pointer versions:
    XMLText*,
    XMLCDATA*,
    XMLComment*,
    XMLelement_t*,
    XMLprocessing_instruction*,
    string_t*,
    // const pointer versions:
    const XMLText*,
    const XMLCDATA*,
    const XMLComment*,
    const XMLelement_t*,
    const XMLprocessing_instruction*,
    const string_t*
    >;
  /* Then we define several helper members
   * (1) an enum to simplify using std::get<INDEX>(VARIANT)
   * (2) two static functions to get the index of pointers:
   *     get_pointer_index(      IDX), and
   *     get_const_pointer_index(IDX)
   * (3)
   * (4) a visitor class XMLprint_variant
   *     This is likely to be huge as XML_variant_t has 18 types
   * NOTE The member variables and functions
   *      as well as the variant definition
   *      and the visitor classes
   *      might be moved up to a base, non-template class
   *      named 'XMLelement_base' or 'XMLelement_variant'
   *      (Remember to forward declare XMLelement before defining such a class)
   */
  enum variants_enum {
    XMLText_enum,
    XMLCDATA_enum,
    XMLComment_enum,
    XMLelement_t_enum,
    XMLprocessing_instruction_enum,
    string_t_enum,
    N // N == number of value types
  };
  //
  static bool is_value(            variants_enum i) {return i <  variants_enum::N;};
  static bool is_pointer(          variants_enum i) {return i >= variants_enum::N;};
  static bool is_const_pointer(    variants_enum i) {return i >= 2*variants_enum::N;};
  static bool is_non_const_pointer(variants_enum i) {return i <  2*variants_enum::N && is_pointer(i);};
  //
  static size_t get_pointer_index(      variants_enum i) {return i +   variants_enum::N;};
  static size_t get_const_pointer_index(variants_enum i) {return i + 2*variants_enum::N;};
};



template <template <typename>          typename CONT = std::vector, // container for elements: array, list, forward_list...
          template <typename,typename> typename  MAP = std::map>    // containers for attributes and namespaces
class XMLelement : public XMLelement_variant<CONT,MAP>, public XMLprintable<MAP> {
public:
  typedef std::string string_t;
  typedef             string_t name_t;
  typedef XMLdoc<MAP> XMLdoc_t;
  typedef         MAP<string_t, string_t>  attributes_t;
  typedef         MAP<string_t, string_t>  namespaces_t;
  typedef         MAP<string_t, string_t>    entities_t;
  using XMLelement_t = XMLelement<CONT,MAP>;
  //
  using XMLelement_variant_t = XMLelement_variant<CONT,MAP>;
  using XMLelement_variant_t::variants_enum;
  using XMLelement_variant_t::get_pointer_index;
  using XMLelement_variant_t::get_const_pointer_index;
  using typename XMLelement_variant_t::XML_variant_t;
  //
  typedef CONT<XML_variant_t> children_t;
  //
  void print_opening_tag_unclosed(std::ostream& o = std::cout) const override {
    o << '<' << get_name() << ' ';
    XMLprintable<MAP>::print_attrs(attributes,o,'\"');
    /* Print each item in 'children'
     * pressumably through std::visit() and a suitable function object.
     * Remember to indent properly.
     */
  };
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
  template <typename T>
  XMLelement_t& add_by_value(const T& t) {children.push_back(t);  return *this;};
  template <typename T>
  XMLelement_t& add_as_pointer(            T& t) {children.push_back(                       &t) ; return *this;};
  template <typename T>
  XMLelement_t& add_as_const_pointer(const T& t) {children.push_back(const_cast<const int*>(&t)); return *this;};
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
