#ifndef NAMESPACES_H
#define NAMESPACES_H

#ifndef CASCADE_MAP_H
#include "CascadeMap.h"
#endif

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#ifndef ENTITIES_H
#include "Entities.h"
#endif

/* Class Namespaces<> may hold both a default namespace and several named namespaces
 *
 */

template <typename STRING=std::string,
          template<typename,typename> typename MAP = std::map,
          PrintTransformer PT = DefaultPrintTransformer,
          typename LEVEL = Level<signed int>
        >
class Namespaces : public CascadeMap<STRING,STRING,MAP>, public XMLnode<PT,LEVEL> {
public:
  typedef CascadeMap<STRING,STRING,MAP> CascadeMap_t;
  typedef std::string string_t;
  typedef Namespaces<STRING,MAP,PT,LEVEL> Namespaces_t;
  //using CascadeMap_t::ptr_to_above;
  using typename CascadeMap_t::value_type;
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
  const string_t& get_default_namespace() const {return default_namespace;};
  bool            has_namespace(const string_t& ns) const;
  const string_t& get_namespace(const string_t&) const;
  //
  void print_default_namespace(std::ostream& o) const;
  void print_namespace(        std::ostream& o, const string_t& k, const string_t& v) const;
  void print(std::ostream& o, LEVEL l = LEVEL(0)) const override;
  // Constructors and destructor
  Namespaces() = default;
  template <typename ITER>
  Namespaces(                     ITER be, ITER en) : CascadeMap_t(be,en) {};
  template <typename ITER>
  Namespaces(const string_t& dns, ITER be, ITER en) : CascadeMap_t(be,en), default_namespace(dns) {};
  Namespaces(                     std::initializer_list<value_type> il) : CascadeMap_t(il) {};
  Namespaces(const string_t& dns, std::initializer_list<value_type> il) : CascadeMap_t(il), default_namespace(dns) {};
  Namespaces(const string_t& dns) : default_namespace(dns) {};
  /*
  Namespaces_t& operator=(Namespaces_t&& cm); // move assignment
  CascadeMap(             Namespaces_t&& cm); // move constructor
  */
  virtual ~Namespaces() = default;
};

// Implementation of member functions:

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
bool Namespaces<STRING,MAP,PT,LEVEL>::has_default_namespace() const {
  return default_namespace.length();
};

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
void Namespaces<STRING,MAP,PT,LEVEL>::set_default_namespace(const string_t& ns) {
  default_namespace = ns;
};

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
bool Namespaces<STRING,MAP,PT,LEVEL>::has_namespace(const string_t& ns) const {
  return at(ns);
};

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
const std::string& Namespaces<STRING,MAP,PT,LEVEL>::get_namespace(const string_t& key) const {
  return at(key);
};

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
void Namespaces<STRING,MAP,PT,LEVEL>::print_namespace(std::ostream& o,
                                                        const string_t& key,
                                                        const string_t& value) const {
  o << " xmlns:" << key << "=\"" << value << '\"';
};

template <typename STRING,
          template<typename,typename> typename MAP,
          PrintTransformer PT,
          typename LEVEL>
void Namespaces<STRING,MAP,PT,LEVEL>::print(std::ostream& o, LEVEL l) const {
  if(has_default_namespace())
    o << " xmlns=\"" << default_namespace;
  for (auto  be = map_t::cbegin(); be != map_t::end(); ++be) {
    print_namespace(o, be->first, be->second);
  }
};

#endif
