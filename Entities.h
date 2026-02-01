#ifndef ENTITIES_H
#define ENTITIES_H

#include <map>
#include <iostream>
#include <string>

/* Class Entities<STRING,MAP> contains:
   - a map for entities
   - a map for system entities
 * It also defines a member function (declare_doctype_and_entities(OSTREAM&))
   for printing a DOCTYPE declarations with all entities stored so far.
 * TODO s
 * [ ] add more kinds of entities
 * [ ] check the kinds of entities
 * [ ] member functions for querying either map
 */


template <typename STRING=std::string, template <typename,typename> typename MAP = std::map>
class Entities {
public:
  typedef STRING string_t;
  typedef MAP<string_t,string_t> map_t;
  //
  map_t system_entities;
  map_t entities;
  const static map_t inline default_entities{ {"lt","<"}, {"gt",">"}, {"apos","\'"}, {"quot","\""}, {"amp","&"} };
  //
  void add_entity(       const string_t& key,  const string_t& value) {       entities[key] = value;};
  void add_system_entity(const string_t& key,  const string_t& value) {system_entities[key] = value;};
  //
  void print_all_entities(          std::ostream& o) const;
  void declare_doctype_and_entities(std::ostream& o, const string_t& name)                      const;
  void declare_doctype_and_entities(std::ostream& o, const string_t& name, const string_t& dtd) const;
  void print_system_entity(std::ostream& o, const string_t& key,  const string_t& value) const;
  void print_entity(       std::ostream& o, const string_t& key,  const string_t& value) const;
  //
  Entities() = default;
  template <typename ITER>
  Entities(ITER be, ITER en) : entities(be,en) {};
};

// Implementation of members

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_all_entities(std::ostream& o) const {
  o << " [\n";
  for(const auto& pa : system_entities) {
    o << "  ";
    print_system_entity(o, pa.first, pa.second);
    o << '\n';
  }
  for(const auto& pa : entities) {
    o << "  ";
    print_entity(o, pa.first, pa.second);
    o << '\n';
  }
  o << "]";
};
template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::declare_doctype_and_entities(    std::ostream& o, const string_t& name) const {
  o << "<!DOCTYPE " << name ;
  if(system_entities.size() || entities.size())
    print_all_entities(o);
  o << ">\n";
};
template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::declare_doctype_and_entities(    std::ostream& o, const string_t& name, const string_t& dtd) const {
  o << "<!DOCTYPE " << name << " SYSTEM \"" << dtd << '\"';
  if(system_entities.size() || entities.size())
    print_all_entities(o);
  o << ">\n";
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_system_entity(std::ostream& o, const string_t& key, const string_t& value) const {
  o << "<!ENTITY " << key << " SYSTEM \"" << value << "\">";
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_entity(std::ostream& o, const string_t& key, const string_t& value) const {
  o << "<!ENTITY " << key << " \"&" << value << ";\">";
};




#endif
