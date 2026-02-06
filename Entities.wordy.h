#ifndef ENTITIES_H
#define ENTITIES_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>

/* Class Entities<STRING,MAP> contains:
   - a map for internal (macro)  entities ('internal_entities')
   - a map for external (SYSTEM) entities ('external_entities')
 * It also defines overloaded member function:
   - declare_doctype_and_entities(OSTREAM&,NAME)
   - declare_doctype_and_entities(OSTREAM&,NAME,DTD)
   for printing a DOCTYPE declarations with all entities stored so far (plus, possibly, a DTD declaration).
 * TODO s
 * [x] check the kinds of entities: internal and external, not ordinary and SYSTEM
 *     member functions for querying either map:
 * [ ] has_internal_entity(STR), which should check for existance
 * [ ] has_external_entity(STR), which should check for existance of both value and referenced file
 */


template <typename STRING=std::string, template <typename,typename> typename MAP = std::map>
class Entities {
public:
  typedef STRING string_t;
  typedef MAP<string_t,string_t> map_t;
  typedef typename map_t::iterator iterator;
  typedef std::pair<string_t,string_t> value_t;
  typedef Entities<STRING,MAP> Entity_t;
  //
  map_t external_entities;
  map_t internal_entities;
  const static map_t inline default_entities{ {"lt","<"}, {"gt",">"}, {"apos","\'"}, {"quot","\""}, {"amp","&"} };
  //
  bool has_internal_entity(const string_t& key) const {return internal_entities.contains(key);};
  bool has_external_entity(const string_t& key) const {return internal_entities.contains(key);};
  const string_t& get_internal_entity(const string_t& key) const {return internal_entities.at(key);};
  const string_t& get_external_entity(const string_t& key) const {return external_entities.at(key);};
  void add_internal_entity(const string_t& key,  const string_t& value) {internal_entities[key] = value;};
  void add_external_entity(const string_t& key,  const string_t& value) {external_entities[key] = value;};
  //
  std::pair<iterator,bool> insert_internal (const value_t& val) {return internal_entities.insert(val);};
  template <class INITER>
  void insert_internal(INITER first, INITER last) {internal_entities.insert(first,last);};
  void insert_internal(std::initializer_list<value_t> il);
  //
  std::pair<iterator,bool> insert_external (const value_t& val) {return external_entities.insert(val);};
  template <class INITER>
  void insert_external(INITER first, INITER last) {external_entities.insert(first,last);};
  void insert_external(std::initializer_list<value_t> il);
  //
  void print_all_entities(std::ostream& o) const; // print both internal and external entities
  void declare_doctype_and_entities(std::ostream& o, const string_t& name)                      const;
  void declare_doctype_and_entities(std::ostream& o, const string_t& name, const string_t& dtd) const;
  void print_system_entity(std::ostream& o, const string_t& key,  const string_t& value) const;
  void print_entity(       std::ostream& o, const string_t& key,  const string_t& value) const;
  //
  void print_mapped_entity(std::ostream& o, const string_t text) const;
  void print_transformed(  std::ostream& o, const string_t text) const;
  static void copy(std::istream& is, std::ostream& os);
  // Constructors and virtual destructor:
  Entities() = default;
  Entities(std::initializer_list<value_t> il) : internal_entities(il) {};
  Entities(std::initializer_list<value_t> il, std::initializer_list<value_t> el)
  : internal_entities(il), external_entities(el) {};
  template <typename ITER>
  Entities(ITER be, ITER en) : internal_entities(be,en) {};
  template <typename ITER>
  Entities(ITER intbe, ITER inten, ITER extbe, ITER exten)
  : internal_entities(intbe,inten), external_entities(extbe,exten) {};
  virtual ~Entities() = default;
};

#endif


#ifndef ENTITIES_CPP
#define ENTITIES_CPP

// Implementation of Entities<> members

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_all_entities(std::ostream& o) const {
  o << " [\n";
  for(const auto& pa : external_entities) {
    o << "  ";
    print_system_entity(o, pa.first, pa.second);
    o << '\n';
  }
  for(const auto& pa : internal_entities) {
    o << "  ";
    print_entity(o, pa.first, pa.second);
    o << '\n';
  }
  o << "]";
};
template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::declare_doctype_and_entities(    std::ostream& o, const string_t& name) const {
  o << "<!DOCTYPE " << name ;
  if(external_entities.size() || internal_entities.size())
    print_all_entities(o);
  o << ">\n";
};
template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::declare_doctype_and_entities(    std::ostream& o, const string_t& name, const string_t& dtd) const {
  o << "<!DOCTYPE " << name << " SYSTEM \"" << dtd << '\"';
  if(external_entities.size() || internal_entities.size())
    print_all_entities(o);
  o << ">\n";
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_system_entity(std::ostream& o, const string_t& key, const string_t& value) const {
  o << "<!ENTITY " << key << " SYSTEM \"" << value << "\">";
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_entity(std::ostream& o, const string_t& key, const string_t& value) const {
  //o << "<!ENTITY " << key << " \"&" << value << ";\">";
  o << "<!ENTITY " << key << " \"" << value << "\">";
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_mapped_entity(std::ostream& o, const string_t enti) const {
#ifdef DEBUG
  std::cout << "[PROCESSING ENTITY \"" << enti << "\", ";
#endif
  if(internal_entities.contains(       enti))
  {
#ifdef DEBUG
    std::cout << "WHICH IS AN INTERNAL ENTITY.]";
#endif
    o << internal_entities.at(enti);
  }
  if(external_entities.contains(enti)) {
#ifdef DEBUG
    std::cout << "WHICH IS AN EXTERNAL ENTITY.]";
#endif
    std::ifstream ifs(external_entities.at(enti));
    if (ifs) {
    copy(ifs, o);
    ifs.close();
    }
    else
      std::cout << "\nOpening file \"" << enti << "\" has failed!\n";
  }

};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::print_transformed(std::ostream& o, const string_t text) const {
  for(int i = 0; i < text.length(); ++i) {
    std::string ent;
    switch (text[i]) {
      case '&':
        ent.clear();
        ++i;
        while(text[i] != ';') {
          ent += text[i];
          ++i;
        }
        print_mapped_entity(o, ent);
        break;
      default: o << text[i];
    }
  }
};

template <typename STRING, template <typename,typename> typename MAP>
void Entities<STRING,MAP>::copy(std::istream& is, std::ostream& os) {
  char c;
  while(true) {
    c = is.get();
    if(!is.good())
      break;
    os << static_cast<char>(c);
  }
};


#endif
