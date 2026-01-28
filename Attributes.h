#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <iostream>
#include <map>
#include <string>

/* Class Attributes holds and handles XML attributes.
 * It keeps a container that maps keys (string's) to values (string's)
 * It holds a pointer to the next Attribute above, its only parent,
   as this mirrors inheritance of attributes the way XML works
   (a cascade, as in CSS: the most immediate version overrides those above)
 * It can print the contents of such a map.
 * It can add new (key,value) pairs: set(KEY,VALUE).
 * It can query the map: contains(KEY) and at(KEY)
 * Many of its member functions are virtual because I don't think the implementation is definitive.
 * (May be derived classes will make do without 'attrs_string' and its related code
 * TODO s
 [ ] Write a copy constructor
 [ ] Write a copy assignment operator
 [ ] Write an interface parent class (so as to avoid std::string 'attrs_string').
 [ ] Write a parent Entities which will lack:
     - a pointer to a parent Entity and associated cascading code
 */

/*
// Forward declaration of class Attributes<CONT>
template <template<typename,typename> typename CONT>
class Attributes;
 */

template <template<typename,typename> typename CONT = std::map>
class Attributes {
public:
  typedef Attributes<CONT> Attributes_t;
  typedef std::string string_t;
  typedef CONT<string_t,string_t> AttributesMap_t;
//protected:
  AttributesMap_t     AttributesMap;
  const Attributes_t* ptr_to_above;
  char sep;
  std::string         attrs_string;
public:
  virtual void set(     const string_t& key, const string_t& value);
  virtual bool contains(const string_t& key) const;
//      string_t& at(const string_t& key);
  virtual const string_t& at(const string_t& key) const;
  // Print only this->AttributesMap:
  virtual std::ostream& print_map(std::ostream& o)         const {return print_map(o,sep);};
  virtual std::ostream& print_map(std::ostream& o, char s) const;
  virtual void    set_attrs_string(string_t& res)         const {set_attrs_string(res,sep);};
  virtual void    set_attrs_string(string_t& res, char s) const;
  virtual void    set_attrs_string()       {set_attrs_string(attrs_string,sep);};
  virtual void    set_attrs_string(char s) {set_attrs_string(attrs_string,s  );};
  virtual void add_to_attrs_string(string_t& str, const string_t& k, const string_t v) const;
  virtual void add_to_attrs_string(               const string_t& k, const string_t v);
  virtual const string_t& get_attributes_string() const {return attrs_string;};
  // Constructor(s) and destructor:
  Attributes_t& operator=(const Attributes_t&  ats) = default; // unnecessary
  Attributes_t& operator=(      Attributes_t&& ats) = default; // unnecessary
               Attributes(      Attributes_t&& ats) = default; // unnecessary
  Attributes(const Attributes_t& ats, char s)      : ptr_to_above(&ats),    sep(s)       {};
  Attributes(const Attributes_t& ats)              : ptr_to_above(&ats),    sep(ats.sep) {};
  Attributes(                         char s='\"') : ptr_to_above(nullptr), sep(s)       {};
  template <typename ITER>
  Attributes(const Attributes_t& ats, ITER be, ITER en)
  : AttributesMap(be,en), ptr_to_above(&ats),    sep(ats.sep)
  {};
  template <typename ITER>
  Attributes(const Attributes_t& ats, ITER be, ITER en, char s)
  : AttributesMap(be,en), ptr_to_above(&ats),    sep(s)
  {};
  template <typename ITER>
  Attributes(                         ITER be, ITER en, char s='\"')
  : AttributesMap(be,en), ptr_to_above(nullptr), sep(s) {}
};

// Implementations:

template <template<typename,typename> typename CONT>
void Attributes<CONT>::set(const string_t& key, const string_t& value) {
  AttributesMap[key] = value;
  add_to_attrs_string(key,value);
};

template <template<typename,typename> typename CONT>
bool Attributes<CONT>::contains(const string_t& key) const {
  if(ptr_to_above==nullptr)
    return AttributesMap.contains(key);
  else {
    return AttributesMap.contains(key) || ptr_to_above->contains(key);
  }
};

template <template<typename,typename> typename CONT>
const std::string& Attributes<CONT>::at(const string_t& key) const {
  if(AttributesMap.contains(key))
    return AttributesMap.at(key);
  else {
    return ptr_to_above->at(key);
  }
};

template <template<typename,typename> typename CONT>
std::ostream& Attributes<CONT>::print_map(std::ostream& o, char s) const {
  for(const auto & p : AttributesMap) {
    o << ' ' << p.first << '=' << sep << p.second << sep;
  }
  return o;
};

template <template<typename,typename> typename CONT>
void Attributes<CONT>::set_attrs_string(string_t& str, char s) const {
  str.clear();
  for(const auto& p: AttributesMap)
    add_to_attrs_string(str, p.first, p.second);
};
template <template<typename,typename> typename CONT>
void Attributes<CONT>::add_to_attrs_string(string_t& str, const string_t& k, const string_t v) const {
  str += ' ';
  str += k;
  str += '=';
  str += sep;
  str += v;
  str += sep;
};
template <template<typename,typename> typename CONT>
void Attributes<CONT>::add_to_attrs_string(const string_t& k, const string_t v) {
  add_to_attrs_string(attrs_string,k,v);
};

#endif
