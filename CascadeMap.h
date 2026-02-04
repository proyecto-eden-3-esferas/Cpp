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
  using container_t::contains;
  using container_t::at, container_t::operator[];
  using container_t::insert, container_t::erase;
  using container_t::begin,  container_t::end;
  using container_t::cbegin, container_t::cend;
//protected:
  const CascadeMap_t* ptr_to_above;
public:
  // Members for handling 'ptr_to_above':
  void set_parent(const CascadeMap_t &  cm) {ptr_to_above = &cm;};
  void set_parent(const CascadeMap_t * pcm) {ptr_to_above = pcm;};
  const CascadeMap_t& get_parent() const {return ptr_to_above;};
  /* has(KEY) and get(KEY) are const members that query the current object and its pointee:
   * If the local map does not contain the key,
   * ptr_to_above->has(key) or ptr_to_above->get(key) is called
   * which amount up to recursive behaviour up the inheritance tree.
   */
  virtual bool               has(const key_type& key) const;
  virtual const mapped_type& get(const key_type& key) const;
  /* (Non-moving) copy assignment, constructors and virtual destructor:
   * Member 'ptr_to_above' is not initialized upon construction (in my implementation)
     It is to be handled through set_parent(REF) and REF get_parent()
   * Otherwise the full set of constructors and virtual destructor is provided
   */
  CascadeMap& operator=(const CascadeMap_t& ats);
  CascadeMap(const CascadeMap_t& ats);
  CascadeMap(); // empty constructor: 'ptr_to_above' set to nullptr
  template <typename ITER>
  CascadeMap(                         ITER be, ITER en)
  : container_t(be,en), ptr_to_above(nullptr) {};
  CascadeMap(std::initializer_list<value_type> il);
  CascadeMap_t& operator=(CascadeMap_t&& cm); // move assignment
  CascadeMap(CascadeMap_t&& cm);              // move constructor
  virtual ~CascadeMap() = default;
};

// Implementations:

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
bool CascadeMap<KEY,MAPPED,CONT>::has(const key_type& key) const {
  if(ptr_to_above==nullptr)
    return contains(key);
  else {
    return contains(key) || ptr_to_above->has(key);
  }
};

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
const MAPPED& CascadeMap<KEY,MAPPED,CONT>::get(const key_type& key) const {
  if(container_t::contains(key))
    return container_t::at(key);
  else {
    return ptr_to_above->at(key);
  }
};

// Implementations of Move Constructors:

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>& CascadeMap<KEY,MAPPED,CONT>::operator=(CascadeMap_t&& cm)
{
  container_t::operator=( std::move(cm) );
  ptr_to_above = cm.ptr_to_above;
  cm.ptr_to_above = nullptr;
  return *this;
};
template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>::CascadeMap(CascadeMap_t&& cm) {
  container_t::operator=( std::move(cm) );
  ptr_to_above = cm.ptr_to_above;
  cm.ptr_to_above = nullptr;
};

// Implementations of Other Constructors:

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>&
CascadeMap<KEY,MAPPED,CONT>::operator=(const CascadeMap_t& ats) {
  container_t::operator=(ats);
  ptr_to_above = ats.ptr_to_above;
  return *this;
};

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>::CascadeMap(const CascadeMap_t& ats)
: container_t(ats), ptr_to_above(ats.ptr_to_above)
{};

template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>::CascadeMap()
: ptr_to_above(nullptr)
{};


template <typename KEY, typename MAPPED, template<typename,typename> typename CONT>
CascadeMap<KEY,MAPPED,CONT>::CascadeMap(std::initializer_list<value_type> il)
: container_t(il.begin(),il.end()), ptr_to_above(nullptr)
{};

#endif
