#ifndef REGISTERED_KEY_MAP_H
#define REGISTERED_KEY_MAP_H

/* Files "registered_key_map.h" and "registered_key_map.cpp"
   define classes:
 (1) registered_key<KEY>,
     which manages a set of allowed keys
     and a set of compulsory keys
 (2) registered_key_map<KEY,VAL,MAP>,
     which is a map from keys to values
     additionally with a const reference to a registered_key object.
     Its 3rd template param. allows choosing an (STL) associative container:
     std::map and std::multimap, or their hash versions (std::unordered_(multi)map)
 *
 */

#include <initializer_list>
#include <map>
#include <set>
#include <string>

/*
 * Keys must be unregistered or an exception gets thrown upon access
 * Registered keys are just allowed attributes or properties
 * TODO
   [ ] add member function   registered_key::register_key(std::string_view newkey)
   [ ] add member function unregistered_key(std::string_view newkey)
 *
 */
template <typename KEY = std::string>
class registered_key {
public:
  typedef          KEY  key_t;
  typedef std::set<KEY> set_t;
  // Set 'allowed_keys' must be a superset of set 'compulsory_keys'
  std::set<key_t> allowed_keys;
  std::set<key_t> compulsory_keys;
  bool allowed(const key_t & k) const;
  //
  registered_key() = default;
  registered_key(std::initializer_list<key_t> allo);
  registered_key(std::initializer_list<key_t> allo, std::initializer_list<key_t> comp);
};
// Implementations of registered_key<KEY> member functions:
template <typename KEY>
bool registered_key<KEY>::allowed(const key_t & k) const {
  if(allowed_keys.contains(k))
    return true;
  else
    return false;
};
template <typename KEY>
registered_key<KEY>::registered_key(std::initializer_list<key_t> allo)
: allowed_keys(allo)
{};
template <typename KEY>
registered_key<KEY>::registered_key(std::initializer_list<key_t> allo,
                                            std::initializer_list<key_t> comp)
: allowed_keys(allo), compulsory_keys(comp)
{};


/* Class registered_key_map is a map<KEY,MAPPED>
 * holding a reference to a registered_key<> object
 */
template <typename KEY = std::string,
          typename VAL = std::string,
          template <typename K,typename M> typename MAP = std::map
          >
class registered_key_map : public std::map<KEY,VAL> {
public:
  typedef KEY key_t;
  typedef VAL mapped_type;
  typedef      MAP<KEY,VAL> map_t;
  typedef std::set<KEY>     set_t;
  typedef registered_key<KEY>                      registered_key_t;
  typedef registered_key_map<KEY,VAL,MAP> registered_key_map_t;
  using map_t::map;
  using map_t::begin, map_t::end;
  // Member variables:
  const registered_key_t& registered_key_ref;
  // Member functions:
  bool allowed(const key_t& k) const {return registered_key_ref.allowed(k);};
  void check_compulsory_keys() const;
  /* Accessors throw std::out_of_range exception
   * if a key not contained in 'allowed_keys' is requested */
        auto & operator[] (const key_t& k);
  const auto & at(         const key_t& k) const;
  // Copy constructor and constructors:
  registered_key_map_t& operator=(const registered_key_map_t& rkm);
  registered_key_map(const registered_key_t & rk) : registered_key_ref(rk) {};
  registered_key_map(const registered_key_t & rk,
                     std::initializer_list<typename map_t::value_type> il)
                   : registered_key_ref(rk), map_t(il)
                   {check_compulsory_keys();};
};
// Implementations:

template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
void registered_key_map<KEY,VAL,MAP>::check_compulsory_keys() const {
  for(const auto & e : registered_key_ref.compulsory_keys) {
    if(! map_t::contains(e))
      throw std::exception();
  } // for
};
template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
auto & registered_key_map<KEY,VAL,MAP>::operator[] (const key_t& k) {
  if(! allowed(k)) {
    throw std::out_of_range("key not present in \'allowed_keys\'");
  }
  return map_t::operator[](k);
};
template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
registered_key_map<KEY,VAL,MAP>& registered_key_map<KEY,VAL,MAP>::operator=(const registered_key_map_t& rkm) {
  const_cast<registered_key_t &>(registered_key_ref) = rkm.registered_key_ref;
  map_t::clear();
  map_t::insert(rkm.begin(), rkm.end());
  return *this;
};
template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
const auto & registered_key_map<KEY,VAL,MAP>::at(const key_t& k) const {
  if(! allowed(k)) {
    throw std::out_of_range("key not present in \'allowed_keys\'");
  }
  return map_t::at(k);
};

#ifndef SEPARATE_COMPILATION
  #ifndef REGISTERED_KEY_MAP_CPP
  #include "registered_key_map.cpp"
  #endif
#endif

#endif
