#ifndef BIJECTION_H
#define BIJECTION_H

/* class Bijection<T1,T2,MAP> implements a reversible map,
 * that is, a data structure that maps forwards and backwards.
 * Perhaps Bijection<>::erase(T1 key) does not make much sense,
 * so the first to-do item is mute.
 * TODO s:
   [ ] Bijection<>::erase(T1 key) does not erase
       all matching entries in the backwards map
 */

#ifndef NAMED_TYPE_H
#include "NamedType.h"
#endif

#include <map>
#include <string>

template <typename T1=std::string,
          typename T2=std::string,
          template <typename,typename> typename MAP=std::map>
class Bijection {
public:
  typedef MAP<T1,T2> map_type; // forward map_type
  typedef            map_type::value_type value_type;
  /* We define specializations of NamedType<TYPE,TAG>
   * in case T1 == T2 (as in the default)
   */
  struct fwd_tag {};
  struct bwd_tag {};
  typedef NamedType<T1,fwd_tag>    key_type;
  typedef NamedType<T2,bwd_tag> mapped_type;
  //
  std::map<T1,T2>  forward_map;
  std::map<T2,T1> backward_map;
  // getters and setters:
  void set(T1 key, T2 val);
  bool erase(const key_type& key);
  void clear();
  // Non-const references must not be returned: therefore do not declare operator[]
  /*
        T2 & operator[] (const    key_type& key)       {return  forward_map[   key.get()];};
  const T2 & operator[] (const    key_type& key) const {return  forward_map[   key.get()];};
        T1 & operator[] (const mapped_type& key)       {return (backward_map.find(key.get()))->second;};
  const T1 & operator[] (const mapped_type& key) const {return (backward_map.find(key.get()))->second;};
  */
  const T2 & at (const    key_type& key) const;
  const T1 & at (const mapped_type& key) const;
};

#ifndef SEPARATE_COMPILATION
#include "Bijection.cpp"
#endif

#endif
