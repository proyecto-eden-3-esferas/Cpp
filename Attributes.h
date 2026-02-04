#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#ifndef CASCADE_MAP_H
#include "CascadeMap.h"
#endif

#ifndef LEVEL_H
#include "Level.h"
#endif

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#include <iostream>
#include <map>
#include <string>

/* Class Attributes holds and handles XML attributes.
 * It keeps a container that maps keys (string's) to values (string's)
 * It holds a pointer to the next Attribute above, its only parent,
   as this mirrors inheritance of attributes the way XML works
   (a cascade, as in CSS: the most immediate version of an attribute overrides those above)
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
// Forward declaration of class Attributes<KEY,MAPPED,CONT,LEVEL>
template <template<typename,typename> typename CONT>
class Attributes;
 */

template <typename KEY=std::string,
          typename MAPPED=std::string,
          template<typename,typename> typename CONT = std::map,
          typename LEVEL = Level<signed int> >
class Attributes : public CascadeMap<KEY,MAPPED,CONT>, public XMLnode<LEVEL> {
public:
  typedef Attributes<KEY,MAPPED,CONT,LEVEL> Attributes_t;
  typedef CONT<KEY,MAPPED>   container_t; // actually, its parent, typically std::map<K,V>
  typedef CascadeMap<KEY,MAPPED,CONT> CascadeMap_t;
  typedef KEY key_type;
  typedef MAPPED mapped_type;
  typedef std::pair<key_type,mapped_type> value_type;
  typedef CONT<key_type,mapped_type> map_t;
  //
  using container_t::contains;
  using container_t::at, container_t::operator[];
  using container_t::insert, container_t::erase;
  using container_t::begin,  container_t::end;
  using container_t::cbegin, container_t::cend;
  using CascadeMap_t::has, CascadeMap_t::get; // getters for (*this + *ptr_to_above)
  using CascadeMap_t::ptr_to_above;
  using CascadeMap_t::operator=, CascadeMap_t::CascadeMap;
//protected:
  char sep;
public:
  virtual std::ostream& print_map(std::ostream& o)         const {return print_map(o,sep);};
  virtual std::ostream& print_map(std::ostream& o, char s) const;
  void print(std::ostream& o, LEVEL l=LEVEL(0)) const override;
  // Constructor(s) and destructor:
  Attributes_t& operator=(const Attributes_t&  ats) = default; // unnecessary
  Attributes(const Attributes_t& ats, char s)      : CascadeMap_t(ats),    sep(s)       {};
  Attributes(const Attributes_t& ats)              : CascadeMap_t(ats),    sep(ats.sep) {};
  Attributes(                         char s='\"') :                       sep(s)       {};
  Attributes(std::initializer_list<value_type> il)         : CascadeMap_t(il), sep('\"') {};
  Attributes(std::initializer_list<value_type> il, char s) : CascadeMap_t(il), sep(s)    {};
  template <typename ITER>
  Attributes(ITER be, ITER en, char s='\"') : CascadeMap_t(be,en), sep(s) {}
  // Define move ctor and move assignment in terms of parent CascadeMap_t:
  Attributes_t& operator=(Attributes_t&& ats);
  Attributes(Attributes_t&& ats);
};

// Implementations:

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
std::ostream& Attributes<KEY,MAPPED,CONT,LEVEL>::print_map(std::ostream& o, char s) const {
  for(const auto & p : *this) {
    o << ' ' << p.first << '=' << sep << p.second << sep;
  }
  return o;
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
void Attributes<KEY,MAPPED,CONT,LEVEL>::print(std::ostream& o, LEVEL l) const {
  print_map(o,sep);
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
Attributes<KEY,MAPPED,CONT,LEVEL>&
Attributes<KEY,MAPPED,CONT,LEVEL>::operator=(Attributes_t&& ats) {
  CascadeMap_t::operator=(std::move(ats));
  return *this;
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
Attributes<KEY,MAPPED,CONT,LEVEL>::Attributes(Attributes_t&& ats)
: CascadeMap_t(std::move(ats))
{};

#endif
