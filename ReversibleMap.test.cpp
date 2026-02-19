/* File "ReversibleMap.test.cpp"
 * TODO
 * [ ]
 */

/* This will include the implementation file, too,
 * unless "SEPARATE_COMPILATION" has been defined
 */
#ifndef REVERSIBLE_MAP_H
#include "ReversibleMap.h"
#endif

typedef std::string KEY;
typedef std::string MAPPED;
#ifdef USE_MAP
typedef ReversibleMap<KEY,MAPPED,std::map> ReversibleMap_t;
#else
typedef ReversibleMap<KEY,MAPPED,std::multimap> ReversibleMap_t;
#endif
  typedef ReversibleMap_t::KeyType KeyType;
  typedef ReversibleMap_t::MappedType MappedType;

#include <iostream>
using namespace std;

/* Overload extractor std::ostream& operator<<(ostream& o, const T& t)
 * for a map (of printable objects) and for a ReversibleMap object.
 * WARNING : I have stopped developing and calling this function.
 *           It raises long compiler error messages.
 *           Failure to compile might be due to template argument deduction.
 *           (I am especially suspicious of the third template parameter.)
 *           Try cueing it with suitable template parameters, then.
 */
#ifdef TEST_EXTRACTOR
template <typename T1, typename T2, template <typename,typename> typename MAP = std::multimap>
std::ostream& operator<<(std::ostream& o, const MAP<T1,T2>& m) {
  o << "Map has " << m.size() << " key-value pairs:\n";
  for(const auto& p : m)
    o << "  key: " << p.first << ", value: " << p.second << '\n';
  return o;
};
template <typename T1 = KeyType, typename T2 = MappedType, template <typename,typename> typename MAP = std::multimap>
std::ostream& operator<<(std::ostream& o, const ReversibleMap<T1,T2,MAP>& rm) {
  o << "Forward  " << rm.forward_map;
  o << "Backward " << rm.backward_map << '\n';
  return o;
};
#endif


int main() {


  ReversibleMap_t spanish_to_english;
  spanish_to_english.emplace("ojo",  "ie");
  spanish_to_english.emplace("ojo",  "eye");
  spanish_to_english.emplace("ojos", "eyes");
  spanish_to_english.emplace("plomo",     "lead");
  spanish_to_english.emplace("encabezar", "lead");
#ifdef TEST_EXTRACTOR
  cout << '\n' << spanish_to_english; cout << flush;
#else
  spanish_to_english.print(cout);
#endif

  cout << "The English for \"ojo\" is \"" << spanish_to_english.at(   KeyType("ojo")) << "\"\n" << flush;
  cout << "The Spanish for \"eye\" is \"" << spanish_to_english.at(MappedType("eye")) << "\"\n" << flush;

  cout << "\nErasing \"ojos\":\n";
  spanish_to_english.erase(KeyType("ojos"));
#ifdef TEST_EXTRACTOR
  cout << '\n' << spanish_to_english; cout << flush;
#else
  spanish_to_english.print(cout);
#endif

  cout << "\nErasing \"ojo\", which after all mapped to two distinct English words:\n";
  spanish_to_english.erase(KeyType("ojo"));
#ifdef TEST_EXTRACTOR
  cout << '\n' << spanish_to_english; cout << flush;
#else
  spanish_to_english.print(cout);
#endif

  cout << "\nFinally, the \"mapped\" entry: lead will be erased, then the ReversibleMap<> printed:\n";
  spanish_to_english.erase(MappedType("lead"));
#ifdef TEST_EXTRACTOR
  cout << '\n' << spanish_to_english; cout << flush;
#else
  spanish_to_english.print(cout);
#endif

  return 0;
}
