#ifndef NAMESPACES_H
#define NAMESPACES_H

#ifndef CASCADE_MAP_H
#include "CascadeMap.h"
#endif

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

/* Class Namespaces<>
 *
 * Should a Namespaces object match an namespace to an alias
 * or the reverse?
 *
 */

template <typename KEY=std::string,
          typename MAPPED=std::string,
          template<typename,typename> typename CONT = std::map,
          typename LEVEL = Level<signed int> >
class Namespaces : public CascadeMap<KEY,MAPPED,CONT>, public XMLnode<LEVEL> {
public:
  typedef CascadeMap<KEY,MAPPED,CONT> CascadeMap_t;
  typedef std::string string_t;
  //using CascadeMap_t::ptr_to_above;
  using CascadeMap_t::contains;
  using CascadeMap_t::at, CascadeMap_t::operator[], CascadeMap_t::insert;
  using CascadeMap_t::has, CascadeMap_t::get;
  using CascadeMap_t::ptr_to_above;
  using typename CascadeMap_t::map_t;
  using CascadeMap_t::CascadeMap;
  //
  string_t default_namespace;
  //
  bool has_default_namespace() const;
  void set_default_namespace(const string_t& ns);
  bool            has_namespace(const string_t& ns) const;
  const string_t& get_namespace(const string_t&) const;
  //
  void print_default_namespace(std::ostream& o) const;
  void print_namespace(        std::ostream& o, const string_t& k, const string_t& v) const;
  void print(std::ostream& o, LEVEL l = LEVEL(0)) const override;
  // Constructors and destructor
  Namespaces() = default;
  Namespaces(const string_t& dns) : default_namespace(dns) {};
};

// Implementation of member functions:

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
bool Namespaces<KEY,MAPPED,CONT,LEVEL>::has_default_namespace() const {
  return default_namespace.length();
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
void Namespaces<KEY,MAPPED,CONT,LEVEL>::set_default_namespace(const string_t& ns) {
  default_namespace = ns;
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
bool Namespaces<KEY,MAPPED,CONT,LEVEL>::has_namespace(const string_t& ns) const {
  return at(ns);
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
const std::string& Namespaces<KEY,MAPPED,CONT,LEVEL>::get_namespace(const string_t& key) const {
  return at(key);
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
void Namespaces<KEY,MAPPED,CONT,LEVEL>::print_namespace(std::ostream& o,
                                                        const string_t& key,
                                                        const string_t& value) const {
  o << " xmlns:" << key << "=\"" << value << '\"';
};

template <typename KEY, typename MAPPED,
          template<typename,typename> typename CONT,
          typename LEVEL>
void Namespaces<KEY,MAPPED,CONT,LEVEL>::print(std::ostream& o, LEVEL l) const {
  if(has_default_namespace())
    o << " xmlns=\"" << default_namespace;
  for (auto  be = map_t::cbegin(); be != map_t::end(); ++be) {
    print_namespace(o, be->first, be->second);
  }
};

#endif
