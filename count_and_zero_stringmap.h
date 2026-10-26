#ifndef COUNT_AND_ZERO_STRINGMAP_H
#define COUNT_AND_ZERO_STRINGMAP_H

#ifndef STRINGMAP_CONCEPT_H
#include "StringMap.concept.h"
#endif

#include <iostream>
#include <string>
#include <map>
#include <utility>

/* Class count_and_zero_stringmap<STRINGMAP> ...
 * Choose an STL container among map, multimap, unordered_map, unordered_multimap
 * TODO
   [v] use std::[io]stream instead of std::[io]fstream
   [ ] writes SQL-conformant INSERT code
   [ ] checks for keys, as done in compilation unit registered_key_map
       (especially class registered_key)
   [ ] inherit from MAP<STRING,STRING>
 */

template <StringMap MAP = std::map<std::string,std::string> >
class count_and_zero_stringmap {
public:
  static void serialize(std::ostream& ofs, const MAP& m);
  static bool deserialize(std::istream& ifs, MAP& m);
  void   serialize(     const MAP& m) const {};              // UNIMPLEMENTED
  bool deserialize(           MAP& m)       {return false;}; // UNIMPLEMENTED
  std::size_t deserialize_all(MAP& m)       {return     0;}; // UNIMPLEMENTED)
};

#endif

#ifndef COUNT_AND_ZERO_STRINGMAP_CPP
#define COUNT_AND_ZERO_STRINGMAP_CPP

#ifndef COUNT_AND_ZERO_STRINGMAP_H
#include "count_and_zero_stringmap.h"
#endif

/*
template <StringMap MAP>
void count_and_zero_stringmap<MAP>::

template <StringMap MAP>
void count_and_zero_stringmap<MAP>::
*/

template <StringMap MAP>
void count_and_zero_stringmap<MAP>::serialize(std::ostream& ofs, const MAP& m) {
    ofs << m.size() << ' ';
    for( const auto& p : m)
      ofs << p.first << '\0' << p.second << '\0';
  };
template <StringMap MAP>
bool count_and_zero_stringmap<MAP>::deserialize(std::istream& ifs, MAP& m) {
    unsigned int cnt;
    std::string key, mapped;
    ifs >> cnt >> std::ws;
    if(ifs.good()) {
      m.clear();
      for(int i=0; i < cnt; ++i) {
        std::getline(ifs, key,    '\0');
        std::getline(ifs, mapped, '\0');
        m.insert(std::make_pair(key,mapped));
      }
      return true;
    } else
      return false;
  };
#endif
