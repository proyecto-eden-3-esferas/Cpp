#ifndef BIJECTION_CPP
#define BIJECTION_CPP

#ifndef BIJECTION_H
#include "Bijection.h"
#endif

// Implementations:

template <typename T1, typename T2, template <typename,typename> typename MAP>
void Bijection<T1,T2,MAP>::set(T1 key, T2 val) {
  // Prevent 'backward_map' from mapping to values that 'forward_map' does not contain:
  /*
  forward_map. emplace(key,val);
  backward_map.emplace(val,key);
  */
  if(forward_map.contains(key))
    backward_map.erase(backward_map.find( forward_map.at(key)));
  forward_map[ key] = val;
  backward_map[val] = key;
};

template <typename T1, typename T2, template <typename,typename> typename MAP>
bool Bijection<T1,T2,MAP>::erase(const key_type& key) {
  if( forward_map.contains(key.get())) {
    // erase      same in 'backward_map':
    //std::cout << "First tackling \'backward_map\'...\n" << std::flush;
    backward_map.erase(backward_map.find( forward_map.at(key.get())));
    // erase key-value in ' forward_map':
    //std::cout << "Then tackling \'forward_map\'...\n" << std::flush;
    forward_map.erase( forward_map.find(key.get()));
    return true;
  }
  else
    return false;
};


template <typename T1, typename T2, template <typename,typename> typename MAP>
const T2 & Bijection<T1,T2,MAP>::at(const key_type& key) const {
  return  forward_map.at(   key.get());
};
template <typename T1, typename T2, template <typename,typename> typename MAP>
const T1 &  Bijection<T1,T2,MAP>::at(const mapped_type& mapped) const {
  return backward_map.at(mapped.get());
};


template <typename T1, typename T2, template <typename,typename> typename MAP>
void Bijection<T1,T2,MAP>::clear() {
  forward_map.clear(); backward_map.clear();
};
/*
template <typename T1, typename T2, template <typename,typename> typename MAP>
void Bijection<T1,T2,MAP>::
 */

#endif
