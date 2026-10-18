/* count-and-zero-stringmap.test.cpp */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>

template <typename SM>
concept StringMap = requires (SM stringmap, std::string key1, std::string key2, std::string mapped) {
  {stringmap[key1]} -> std::convertible_to<std::string>;
  stringmap.insert(std::make_pair(key2,mapped));
};

/* Functions:
   count_and_zero_serialize(  OFSTREAM, const MAP& m)
   count_and_zero_deserialize(IFSTREAM,       MAP& m)
   store and load a map of strings to strings from
   (1) the total number of entries, space separated from
   (2) a key, zero terminated, followed by a mapped value, zero-terminated, too
 */
template <StringMap MAP>
void count_and_zero_serialize(std::ofstream& ofs, const MAP& m) {
  ofs << m.size() << ' ';
  for( const auto& p : m)
    ofs << p.first << '\0' << p.second << '\0';
};
template <StringMap MAP>
bool count_and_zero_deserialize(std::ifstream& ifs, MAP& m) {
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

typedef std::map<std::string, std::string> map_t;

map_t en2es{
  {"black", "negro"},
  {"white", "blanco"},
  {"red",   "rojo"},
  {"green", "verde"}
};

#include <iostream>

using namespace std;

int main() {

  std::ofstream testout("test.text", std::fstream::out | std::fstream::trunc);
  count_and_zero_serialize(testout, en2es);
  testout.close();

  en2es.clear();

  cout << "Now \'en2es\' has " << en2es.size() << " element(s).\n";

  std::ifstream testin("test.text", std::fstream::in);
  count_and_zero_deserialize(testin, en2es);
  testin.close();

  cout << "After deserializing, \'en2es\' has " << en2es.size() << " element(s).\n";

  return 0;
}
