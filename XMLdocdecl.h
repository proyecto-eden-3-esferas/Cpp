#ifndef XMLDOCDECL_H
#define XMLDOCDECL_H

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#ifndef ENTITIES_H
#include "Entities.h"
#endif

#include <initializer_list>
#include <map>
#include <string>

/* Class XMLdocdecl<> holds entities (&mdash; &nbsp; etc.) and the 'doctype' as a string.
 * It offers suitable getters (for doctype and entities) and setters (for entities).
 * It is neither a child nor a parent.
 * XMLroot<> holds references to an instance of XMLdocdecl<>
 * Should also each XMLelement<> hold a reference to a XMLdocdecl<>?
 * This class definition has been copied from "XML.h"
 * but the new version works by holding an Element object
 *
 * TODO s
 * [ ] add DTD member variable (std::string DTD)
 * [ ] get print(OSTREAM&, LEVEL) to print the DTD, if there is one
 */

template <template <typename,typename> typename  MAP  = std::map, // container for entities
          typename LEVEL = Level<signed int>
         >
class XMLdocdecl : public XMLnode<LEVEL> {
public:
  typedef std::string string_t;
  typedef             string_t key_t;
  typedef             string_t value_t;
  typedef Entities<string_t,MAP> entities_t;
//private:
  const string_t  doctype;
  entities_t all_entities;
  //
  const string_t& get_doctype() const;
  //
  void add_entity(       const string_t& key,  const string_t& value);
  void add_system_entity(const string_t& key,  const string_t& value);
  //
  void print_all_entities(std::ostream& o) const {all_entities.print_all_entities(o);};
  void declare_doctype_and_entities(std::ostream& o, const string_t& name) const;
  void declare_doctype_and_entities(std::ostream& o, const string_t& name, const string_t& dtd) const;
  void print_system_entity(std::ostream& o, const string_t& key,  const string_t& value) const;
  void print_entity(std::ostream& o, const string_t& key,  const string_t& value) const;
  //
  bool is_inline() const override {return false;};
  void print(std::ostream& o, LEVEL l=0) const override;
  typedef std::pair<string_t,string_t> pair_t;
  // Constructor(s) and destructor:
  XMLdocdecl(const string_t& s);
  template <typename ITER>
  XMLdocdecl(const string_t& s, ITER be, ITER en) : doctype(s), all_entities(be,en) {};
  XMLdocdecl(const string_t& s, std::initializer_list<pair_t> il);
};

#endif


#ifndef XMLDOCDECL_CPP
#define XMLDOCDECL_CPP

/* Implementation of member functions in XMLDoc<>
 */

template <template <typename,typename> typename  MAP, typename LEVEL>
const std::string& XMLdocdecl<MAP,LEVEL>::get_doctype()  const {return doctype;};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::add_entity(const string_t& key,  const string_t& value) {
  all_entities.add_entity(key,value);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::add_system_entity(const string_t& key,  const string_t& value) {
  all_entities.add_system_entity(key,value);
};
template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::declare_doctype_and_entities(std::ostream& o, const string_t& name) const {
  all_entities.declare_doctype_and_entities(o,doctype);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::declare_doctype_and_entities(std::ostream& o, const string_t& name, const string_t& dtd) const {
  all_entities.declare_doctype_and_entities(o,doctype,dtd);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::print_system_entity(std::ostream& o, const string_t& key,  const string_t& value) const {
  all_entities.print_system_entity(o,key,value);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::print_entity(std::ostream& o, const string_t& key,  const string_t& value) const {
  all_entities.print_entity(o,key,value);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
void XMLdocdecl<MAP,LEVEL>::print(std::ostream& o, LEVEL l) const
{
  declare_doctype_and_entities(o,doctype);
};

template <template <typename,typename> typename  MAP, typename LEVEL>
XMLdocdecl<MAP,LEVEL>::XMLdocdecl(const string_t& s) :
  doctype(s)
  {};


template <template <typename,typename> typename  MAP, typename LEVEL>
XMLdocdecl<MAP,LEVEL>::XMLdocdecl(const string_t& s, std::initializer_list<pair_t> il) : doctype(s), all_entities(il.begin(),il.end()) {};

#endif
