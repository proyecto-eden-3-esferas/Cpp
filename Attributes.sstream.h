#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>

// Forward declaration of class Attributes<CONT>
template <template<typename,typename> typename CONT>
class Attributes;

template <template<typename,typename> typename CONT = std::map>
class Attributes {
public:
  typedef Attributes<CONT> Attributes_t;
  typedef std::string string_t;
  typedef CONT<string_t,string_t> AttributesMap_t;
//protected:
  AttributesMap_t AttributesMap;
  const Attributes_t* ptr_to_above;
  std::stringstream attrs_ss;
public:
  /* member set(KEY,VALUE) sets an attribute in the class's map
   * member contains(KEY) returns whether a key is found in the class or its ancestors
   * member       at(KEY) returns the value   as defined in the class or its ancestors
   */
  void set(const string_t& key, const string_t& value) {
    AttributesMap[key] = value;
    add_to_ss(key,value);
  };
  bool      contains(const string_t& key) const;
//      string_t& at(const string_t& key);
  const string_t& at(const string_t& key) const;
  // Print only this->AttributesMap:
  std::ostream& print_map(std::ostream& o, char sep='\"') const;
  void add_to_ss(                                     char sep='\"');
  void add_to_ss(const string_t& k, const string_t v, char sep='\"');
  string_t get_attributes_string(char sep='\"') {return attrs_ss.str();};
  void load_attributes(string_t& str, char sep='\"') const;
  // Constructor(s) and destructor:
  Attributes(const Attributes_t& ats) : ptr_to_above(&ats) {}
  Attributes()                        : ptr_to_above(nullptr) {}
};

// Implementations:

template <template<typename,typename> typename CONT>
void Attributes<CONT>::load_attributes(string_t& str, char sep) const {
  str.clear();
  for(const auto& p: AttributesMap) {
    str += ' ';
    str += p.first;
    str += '=';
    str += sep;
    str += p.second;
    str += sep;
  }
};

template <template<typename,typename> typename CONT>
bool Attributes<CONT>::contains(const string_t& key) const {
  if(ptr_to_above==nullptr)
    return AttributesMap.contains(key);
  else {
    return AttributesMap.contains(key) || ptr_to_above->contains(key);
  }
};
/*
template <template<typename,typename> typename CONT>
      std::string& Attributes<CONT>::at(const string_t& key) {
  if(AttributesMap.contains(key))
    return AttributesMap.at(key);
  else {
    return ptr_to_above->at(key);
  }
};
*/
template <template<typename,typename> typename CONT>
const std::string& Attributes<CONT>::at(const string_t& key) const {
  if(AttributesMap.contains(key))
    return AttributesMap.at(key);
  else {
    return ptr_to_above->at(key);
  }
};

template <template<typename,typename> typename CONT>
std::ostream& Attributes<CONT>::print_map(std::ostream& o, char sep) const {
  for(const auto & p : AttributesMap) {
    o << ' ' << p.first << '=' << sep << p.second << sep;
  }
  return o;
};

template <template<typename,typename> typename CONT>
void Attributes<CONT>::add_to_ss(char sep) {
  attrs_ss.str("");
  for(const auto& p: AttributesMap) {
    attrs_ss << ' ';
    attrs_ss << p.first;
    attrs_ss << '=';
    attrs_ss << sep;
    attrs_ss << p.second;
    attrs_ss << sep;
  }
};
template <template<typename,typename> typename CONT>
void Attributes<CONT>::add_to_ss(const string_t& k, const string_t v, char sep) {
  attrs_ss << ' ';
    attrs_ss << k;
    attrs_ss << '=';
    attrs_ss << sep;
    attrs_ss << v;
    attrs_ss << sep;
};

#endif
