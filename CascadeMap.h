#ifndef CASCADE_MAP_H
#define CASCADE_MAP_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>

/* Class CascadeMap holds a map and a pointer to its parent
 * It keeps a container that maps keys (string's) to values
 * It holds a pointer to the next Attribute above, its only parent,
   as this mirrors inheritance of attributes the way XML works
   (a cascade, as in CSS: the most immediate version overrides those above)
 * It can print the contents of such a map (low-priority goal, though).
 * It can add new (key,value) pairs: set(KEY,MAPPED).
 * It can query the map: contains(KEY) and at(KEY)
 * Many of its member functions are virtual because I don't think the implementation is definitive.
 * TODO s
 [ ] Write a copy constructor
 [ ] Write a copy assignment operator
 [ ] Write an interface parent class (so as to avoid std::string 'attrs_string').
 [ ] Write a parent Entities which will lack:
     - a pointer to a parent Entity and associated cascading code
 */


template <typename KEY=std::string,
          typename MAPPED=std::string,
          template<typename,typename> typename CONT = std::map>
class CascadeMap : public CONT<KEY,MAPPED> {
public:
  typedef CONT<KEY,MAPPED>   container_t; // actually, its parent, typically std::map<K,V>
  typedef CascadeMap<KEY,MAPPED,CONT> CascadeMap_t;
  typedef KEY key_type;
  typedef MAPPED mapped_type;
  typedef std::pair<key_type,mapped_type> value_type;
  typedef CONT<key_type,mapped_type> map_t;
  //
  //using container_t::contains;
  //using container_t::at;
//protected:
  const CascadeMap_t* ptr_to_above;
public:
  virtual bool contains(const key_type& key) const;
//      string_t& at(const string_t& key);
                mapped_type& at (const key_type& k) = delete;
  virtual const mapped_type& at(const key_type& key) const;
  /* Constructors and virtual destructor:
   * Always two versions are provided:
     (1) one taken a parent const CascadeMap<> reference, and
     (2) another one taken no const CascadeMap<> reference
   * The constructor pairs are:
   (1) those taking either a parent CascadeMap<> to be pointed to or none
   (2) those taking a pair of iterators to initiaze the parent map
   (3) those taking an initializer list
   * NOTE : No copy constructor, but constructor initializing a pointer to CascadeMap above
   */
  CascadeMap& operator=(const CascadeMap_t& ats) {ptr_to_above = &ats; return *this;};
  CascadeMap(const CascadeMap_t& ats) : ptr_to_above(&ats)    {};
  CascadeMap()                        : ptr_to_above(nullptr) {};
  template <typename ITER>
  CascadeMap(const CascadeMap_t& ats, ITER be, ITER en)
  : container_t(be,en), ptr_to_above(&ats)
  {};
  template <typename ITER>
  CascadeMap(                         ITER be, ITER en)
  : container_t(be,en), ptr_to_above(nullptr) {};
  CascadeMap(const CascadeMap_t& ats, std::initializer_list<value_type> il)
  : container_t(il.begin(),il.end()), ptr_to_above(&ats) {};
  CascadeMap(                         std::initializer_list<value_type> il)
  : container_t(il.begin(),il.end()), ptr_to_above(nullptr) {};
  virtual ~CascadeMap() = default;
};

// Implementations:

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
bool CascadeMap<KEY,MAPPED,CONT>::contains(const key_type& key) const {
  if(ptr_to_above==nullptr)
    return container_t::contains(key);
  else {
    return container_t::contains(key) || ptr_to_above->contains(key);
  }
};

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
const MAPPED& CascadeMap<KEY,MAPPED,CONT>::at(const key_type& key) const {
  if(container_t::contains(key))
    return container_t::at(key);
  else {
    return ptr_to_above->at(key);
  }
};

#endif
