#ifndef REVERSIBLE_MAP_CPP
#define REVERSIBLE_MAP_CPP

#ifndef REVERSIBLE_MAP_H
#include "ReversibleMap.h"
#endif

// Implementations:


template <typename T1, typename T2, template <typename,typename> typename MAP>
bool ReversibleMap<T1,T2,MAP>::insert(const value_type& val) {
  auto fwd_res = insert(val);
  auto bwd_res = insert(std::make_pair(val.second, val.first));
  return fwd_res.second && bwd_res.second;
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::emplace(const T1& key, const T2& mapped) {
  forward_map.emplace(key,mapped);
  backward_map.emplace(mapped,key);
};

//


template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::set(T1 key, T2 val) {
  // Prevent 'backward_map' from mapping to values that 'forward_map' does not contain:
  if(forward_map.contains(key))
    backward_map.erase(backward_map.find( forward_map.at(key)));
  forward_map[ key] = val;
  backward_map[val] = key;
};

// ReversibleMap<T1,T2,MAP>::find(const KeyType/MappedType& x)

template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_iterator
ReversibleMap<T1,T2,MAP>::find(const KeyType& key) {
  return forward_map.find(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_const_iterator
ReversibleMap<T1,T2,MAP>::find(const KeyType& key) const {
  return forward_map.find(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_iterator
ReversibleMap<T1,T2,MAP>::find(const MappedType& mapped) {
  return backward_map.find(mapped.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_const_iterator
ReversibleMap<T1,T2,MAP>::find(const MappedType& mapped) const {
  return backward_map.find(mapped.get());
};

// ReversibleMap<T1,T2,MAP>::lower_bound(const KeyType/MappedType& t)

template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_iterator
ReversibleMap<T1,T2,MAP>::lower_bound(const KeyType& key) {
  return forward_map.lower_bound(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_const_iterator
ReversibleMap<T1,T2,MAP>::lower_bound(const KeyType& key) const {
  return forward_map.lower_bound(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_iterator
ReversibleMap<T1,T2,MAP>::lower_bound(const MappedType& mapped) {
  return backward_map.lower_bound(mapped.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_const_iterator
ReversibleMap<T1,T2,MAP>::lower_bound(const MappedType& mapped) const {
  return backward_map.lower_bound(mapped.get());
};

// ReversibleMap<T1,T2,MAP>::upper_bound(const KeyType/MappedType& t)

template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_iterator
ReversibleMap<T1,T2,MAP>::upper_bound(const KeyType& key) {
  return forward_map.upper_bound(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_const_iterator
ReversibleMap<T1,T2,MAP>::upper_bound(const KeyType& key) const {
  return forward_map.upper_bound(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_iterator
ReversibleMap<T1,T2,MAP>::upper_bound(const MappedType& mapped) {
  return backward_map.upper_bound(mapped.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_const_iterator
ReversibleMap<T1,T2,MAP>::upper_bound(const MappedType& mapped) const {
  return backward_map.upper_bound(mapped.get());
};

// ReversibleMap<T1,T2,MAP>::find(const KeyType& key)

template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_const_range_pair
ReversibleMap<T1,T2,MAP>::equal_range (const KeyType& key) const {
  return forward_map.equal_range(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::fwd_range_pair
ReversibleMap<T1,T2,MAP>::equal_range (const KeyType& key) {
  return forward_map.equal_range(key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_const_range_pair
ReversibleMap<T1,T2,MAP>::equal_range (const MappedType& mapped) const {
  return backward_map.equal_range(mapped.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
ReversibleMap<T1,T2,MAP>::bwd_range_pair
ReversibleMap<T1,T2,MAP>::equal_range (const MappedType& mapped) {
  return backward_map.equal_range(mapped.get());
};

// Implementations of forward erase() overloads:

template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::fwd_erase(fwd_const_iterator pos) {
  forward_map.erase( pos->first);
  backward_map.erase(pos->second);
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
bool ReversibleMap<T1,T2,MAP>::erase(const KeyType& key) {
  if( forward_map.contains(key.get())) {
    // delete entries in 'backward_map':
    auto it = backward_map.begin();
    while(it != backward_map.end()) {
      if(it->second == key.get()) {
#ifdef DEBUG
        std::cout << "erasing pair: (" << it->first << ", " << it->second << ") in backward_map.\n";
#endif
        backward_map.erase(it);
        it = backward_map.begin(); // reset 'it' against invalidation of iterators
      } else
        ++it;
    } // while
    // delete entry in 'forward_map':
    forward_map.erase(key.get());
    return true;
  }
  else
    return false;
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::fwd_erase (fwd_const_iterator first, fwd_const_iterator last) {
  for( ; first != last; ++first)
    erase(first);
};

// Implementations of backward erase() overloads:

template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::bwd_erase (bwd_const_iterator pos) {
  forward_map.erase( pos->second);
  backward_map.erase(pos->first);
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
bool ReversibleMap<T1,T2,MAP>::erase(const MappedType& mapped) {
  if( backward_map.contains(mapped.get())) {
    // delete entries in 'forward_map':
    auto it = forward_map.begin();
    while(it != forward_map.end()) {
      if(it->second == mapped.get()) {
#ifdef DEBUG
        std::cout << "erasing pair: (" << it->first << ", " << it->second << ") in forward_map.\n";
#endif
        forward_map.erase(it);
        it = forward_map.begin(); // reset 'it' against invalidation of iterators
      } else
        ++it;
    } // while
    // delete entry in 'backward_map':
    backward_map.erase(mapped.get());
    return true;
  }
  else
    return false;
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::bwd_erase (bwd_const_iterator first, bwd_const_iterator last) {
  for( ; first != last; ++first)
    erase(first);
};

//

template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::clear() {
  forward_map.clear();
  backward_map.clear();
};

template <typename T1, typename T2, template <typename,typename> typename MAP>
const T2 & ReversibleMap<T1,T2,MAP>::at(const KeyType& key) const {
  return  forward_map.find(key.get())->second;
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
const T1 &  ReversibleMap<T1,T2,MAP>::at(const MappedType& mapped) const {
  return backward_map.find(mapped.get())->second;
};


//

template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::print(std::ostream & o) const {
  o << "Forward map has " << forward_map.size() << " key-value pair(s):\n";
  for(const auto& p : forward_map)
    o << "  key: " << p.first << ", value: " << p.second << '\n';
  o << "Backward map map has " << forward_map.size() << " key-value pair(s):\n";
  for(const auto& p : backward_map)
    o << "  key: " << p.first << ", value: " << p.second << '\n' << std::flush;
};

/*
template <typename T1, typename T2, template <typename,typename> typename MAP>
void ReversibleMap<T1,T2,MAP>::
 */

#endif
