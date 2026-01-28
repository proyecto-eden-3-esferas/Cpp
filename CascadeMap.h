#ifndef CASCADE_MAP_H
#define CASCADE_MAP_H

#include <iostream>
#include <map>
#include <string>

/* Class CascadeMap holds a map and a pointer to its parent
 * It keeps a container that maps keys (string's) to values
 * It holds a pointer to the next Attribute above, its only parent,
   as this mirrors inheritance of attributes the way XML works
   (a cascade, as in CSS: the most immediate version overrides those above)
 * It can print the contents of such a map (low-priority goal, though).
 * It can add new (key,value) pairs: set(KEY,VALUE).
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
          typename VALUE=std::string,
          template<typename,typename> typename CONT = std::map>
class CascadeMap : public CONT<KEY,VALUE> {
public:
  typedef CONT<KEY,VALUE>   container_t; // actually, its parent, typically std::map<K,V>
  typedef CascadeMap<KEY,VALUE,CONT> CascadeMap_t;
  typedef KEY key_type;
  typedef VALUE value_type;
  typedef CONT<key_type,value_type> map_t;
//protected:
  const CascadeMap_t* ptr_to_above;
public:
  virtual void set(     const key_type& key, const value_type& value);
  virtual bool contains(const key_type& key) const;
//      string_t& at(const string_t& key);
  virtual const value_type& at(const key_type& key) const;
  // Constructors and virtual destructor:
  CascadeMap(const CascadeMap_t& ats) : ptr_to_above(&ats)    {};
  CascadeMap()                        : ptr_to_above(nullptr) {};
  template <typename ITER>
  CascadeMap(const CascadeMap_t& ats, ITER be, ITER en)
  : container_t(be,en), ptr_to_above(&ats)
  {};
  template <typename ITER>
  CascadeMap(                         ITER be, ITER en)
  : container_t(be,en), ptr_to_above(nullptr) {};
  virtual ~CascadeMap() = default;
};

// Implementations:

template <typename KEY, typename VALUE, template<typename,typename> typename CONT>
void CascadeMap<KEY,VALUE,CONT>::set(const key_type& key, const value_type& value) {

};

template <typename KEY, typename VALUE, template<typename,typename> typename CONT>
bool CascadeMap<KEY,VALUE,CONT>::contains(const key_type& key) const {
  if(ptr_to_above==nullptr)
    return container_t::contains(key);
  else {
    return container_t::contains(key) || ptr_to_above->contains(key);
  }
};

template <typename KEY, typename VALUE, template<typename,typename> typename CONT>
const VALUE& CascadeMap<KEY,VALUE,CONT>::at(const key_type& key) const {
  if(container_t::contains(key))
    return container_t::at(key);
  else {
    return ptr_to_above->at(key);
  }
};

#endif
