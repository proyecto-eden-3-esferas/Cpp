/* File "Bijection.test.cpp"
 * TODO
   [ ] Final erase fails painfully:
       double free or corruption (out)
       Aborted (core dumped)
 * [ ]
 */

#ifndef BIJECTION_H
#include "Bijection.h"
#endif


typedef std::string KEY;
typedef std::string MAPPED;
typedef Bijection<KEY,MAPPED> Bijection_t;
typedef                           Bijection_t::key_type key_type;
typedef                           Bijection_t::mapped_type mapped_type;

#include <iostream>
using namespace std;

/* overload extractor std::ostream& operator<<(ostream& o, const T& t)
 * for a map (of printable objects) and for a Bijection object
 */
template <typename T1 = key_type, typename T2 = mapped_type>
std::ostream& operator<<(std::ostream& o, const std::map<T1,T2>& m) {
  o << "Map has " << m.size() << " key-value pairs:\n";
  for(const auto& p : m)
    o << "  key: " << p.first << ", value: " << p.second << '\n';
  return o;
}
template <typename T1 = key_type, typename T2 = mapped_type>
std::ostream& operator<<(std::ostream& o, const Bijection<T1,T2>& rm) {
  o << "Forward  " << rm.forward_map;
  o << "Backward " << rm.backward_map << '\n';
  return o;
}


int main() {

  Bijection_t spanish_to_english;
  cout << "Inserting {\"ojo\",\"iye\"}, {\"ojo\",\"eye\"}, and {\"ojos\",\"eyes\"}...\n";
  spanish_to_english.set("ojo",  "iye");
  spanish_to_english.set("ojo",  "eye");
  spanish_to_english.set("ojos", "eyes");
  cout << '\n' << spanish_to_english; cout << flush;

  cout << "The English for \"ojo\" is \"" << spanish_to_english.at(   key_type("ojo")) << "\"\n" << flush;
  cout << "The Spanish for \"eye\" is \"" << spanish_to_english.at(mapped_type("eye")) << "\"\n" << flush;

  cout << "\nErasing \"ojos\":\n";
  spanish_to_english.erase(key_type("ojos"));
  cout << spanish_to_english << flush;

  cout << "\nErasing \"ojo\", which has mapped to two diferent English words:\n";
  spanish_to_english.erase(key_type("ojo"));
  cout << spanish_to_english << flush;

  return 0;
}
