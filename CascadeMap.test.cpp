#ifndef CASCADE_MAP_H
#include "CascadeMap.h"
#endif

/* Test class CascadeMap...
 */

#include <iostream>
#include <string>

using namespace std;

typedef std::string key_type;
typedef  signed int mapped_type;
typedef CascadeMap<key_type,mapped_type,std::map> CascadeMap_t;
typedef CascadeMap_t::value_type value_type;

CascadeMap_t cm0;
CascadeMap_t cmil{{"one", 1}, {"two", 2}};

int main() {

  cmil.insert({"three", 3});
  cout << "CascadeMap \'cmil\' is initialized from an initializer list";
  cout << " and has size: " << cmil.size() << '\n';
  cmil.erase("two");
  cout << "After cmil.erase(\"two\"), \'cmil\' has size: " << cmil.size() << '\n';




  return 0;
}


