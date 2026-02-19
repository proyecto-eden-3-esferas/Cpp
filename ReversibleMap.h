#ifndef REVERSIBLE_MAP_H
#define REVERSIBLE_MAP_H

/* class ReversibleMap<T1,T2,MAP> implements a reversible map,
   that is, a data structure that maps forwards and backwards.
 * The third template parameter may be any of:
     std::map, std::multimap, std::unordered_map, std::unordered_multimap
 * I want first to implement "reversible" versions of standard setters and getters:
   insert, emplace...
 * Perhaps ReversibleMap<>::erase(T1 key) does not make much sense,
   so the first to-do item is mute.
 * These files are not quite ready for separate compilation of the implementations
   (possibly in file "ReversibleMap.cpp") into an object file ("ReversibleMap.o")
   because:
   (1) the first template arguments may be any type, unless you use the defaults, and
   (2) the third template argument may be any of the four STL map classes
 * TODO s:
   The main issue concern getting erase(x) to erase throroughly
   both for std::map and for std::multimap:
   [ ] It seems that "erase(KeyType k)"
       does not erase the entries in backward_map that map to k
   [ ] ReversibleMap<T1,T2,std::map>::erase(T1 key)
       does not erase all matching entries in the backwards map
   [ ] test fwd_erase(...) and bwd_erase(...)
 */

#ifndef NAMED_TYPE_H
#include "NamedType.h"
#endif

#include <iostream>
#include <map>
#include <string>

template <typename T1=std::string,
          typename T2=std::string,
          template <typename,typename> typename MAP=std::multimap>
class ReversibleMap {
public:
  typedef MAP<T1,T2>::value_type value_type;
  /* We define specializations of NamedType<TYPE,TAG>
     in case T1 == T2 (as in the default, where BOTH are std::string's)
   * The thus defined types are just typedef's of NamedType<T,TAG>
   * Note the camel notation: KeyType and MappedType
     to help with remembering
   */
  struct fwd_tag {};
  struct bwd_tag {};
  typedef NamedType<T1,fwd_tag>    KeyType;
  typedef NamedType<T2,bwd_tag> MappedType;
  typedef std::size_t size_t;
  //
  MAP<T1,T2>  forward_map;
  MAP<T2,T1> backward_map;
  /* Setters and getters with no iterators in their prototypes:
   * The STL prototypes are complied with whenever possible.
   * Still, even though insert and emplace return pair<iterator,bool>,
     I have deviated: when pair<iterator,bool> is returned by the STL version
     I return the bool that results from AND-ing the bool part in each returned result.
   */
  bool insert(const value_type& val);
  template <typename InputIterator>
  bool insert(InputIterator first, InputIterator last); // defined in header
  void emplace(const T1& key, const T2& mapped);
  void clear();
  //
  void set(T1 key, T2 val);
  /* Getters and setters using iterators.
   * Following STL semantics.
   * To wit: find(x), lower_bound(x), upper_bound(x), equal_range(x)
   * Always efore declaring the functions, some required typedef's are made
   */
  typedef MAP<T1,T2>::iterator       fwd_iterator;
  typedef MAP<T1,T2>::const_iterator fwd_const_iterator;
  typedef MAP<T2,T1>::iterator       bwd_iterator;
  typedef MAP<T2,T1>::const_iterator bwd_const_iterator;
  fwd_iterator       find(const    KeyType& key);
  fwd_const_iterator find(const    KeyType& key) const;
  bwd_iterator       find(const MappedType& mapped);
  bwd_const_iterator find(const MappedType& mapped) const;
  // lower_bound(KeyType/MappedType) [const]:
  fwd_iterator       lower_bound(const KeyType& key);
  fwd_const_iterator lower_bound(const KeyType& key) const;
  bwd_iterator       lower_bound(const MappedType& mapped);
  bwd_const_iterator lower_bound(const MappedType& mapped) const;
  // upper_bound(KeyType/MappedType) [const]:
  fwd_iterator        upper_bound(const KeyType& key);
  fwd_const_iterator  upper_bound(const KeyType& key) const;
  bwd_iterator        upper_bound(const MappedType& mapped);
  bwd_const_iterator  upper_bound(const MappedType& mapped) const;
  // Some PAIR<ITERATOR,ITERATOR> typedef's then PAIR equal_range(t):
  typedef std::pair<fwd_const_iterator,fwd_const_iterator> fwd_const_range_pair;
  typedef std::pair<      fwd_iterator,      fwd_iterator> fwd_range_pair;
  typedef std::pair<bwd_const_iterator,bwd_const_iterator> bwd_const_range_pair;
  typedef std::pair<      bwd_iterator,      bwd_iterator> bwd_range_pair;
  fwd_const_range_pair equal_range (const KeyType& key) const;
  fwd_range_pair       equal_range (const KeyType& key);
  bwd_const_range_pair equal_range (const MappedType& mapped) const;
  bwd_range_pair       equal_range (const MappedType& mapped);
  //
  /* Forward and backward erase() overloads.
   * "fwd_" and "bwd_" are needed because if T1 == T2 then:
     (1) fwd_iterator       == bwd_iterator
     (2) fwd_const_iterator == bwd_const_iterator
     and then the overload cannot be resolved.
   */
  void fwd_erase (fwd_const_iterator pos);
  bool     erase(const KeyType& key);
  void fwd_erase (fwd_const_iterator first, fwd_const_iterator last);
  void bwd_erase (bwd_const_iterator pos);
  bool     erase(const MappedType& key);
  void bwd_erase (bwd_const_iterator first, bwd_const_iterator last);

  /* std::multimap does not define at(KEY)
   * because by analogy with std::map, it should return a range,
   * so we should use instead either
   * (1) equal_range(x), or
   * (2) lower_bound(x) + upper_bound(x).
   * The implementations provided rely on find(x),
   * which is not correct for std::multimap */
  const T2 & at (const    KeyType& key) const;
  const T1 & at (const MappedType& key) const;
  //
  void print(std::ostream & o = std::cout) const; // should print inner state,
                                                  // specifically its data structures
  // Constructor(s) and virtual destructor:
  ReversibleMap() = default;
  virtual ~ReversibleMap() = default;
};

template <typename T1, typename T2, template <typename,typename> typename MAP>
template <typename InputIterator>
bool ReversibleMap<T1,T2,MAP>::insert(InputIterator first, InputIterator last) {
  bool res = true;
  for(; first != last; ++first) {
    res = insert(*first) && res;
  }
  return res;
};


#ifndef SEPARATE_COMPILATION
#include "ReversibleMap.cpp"
#endif

#endif
