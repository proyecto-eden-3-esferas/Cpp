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
CascadeMap_t cmil{{"one", 1}, {"two", 2}}; // from std::initializer_list<>

int main() {

  cout << "Test member functions \'insert\', \'erase\', and \'size\':";
  cmil.insert({"three", 3});
  cout << "CascadeMap \'cmil\' was initialized from an initializer list";
  cout << " and has size: " << cmil.size() << '\n';
  cmil.erase("two");
  cout << "After cmil.erase(\"two\"), \'cmil\' has size: " << cmil.size() << '\n';

  cm0.set_parent(cmil);
  cout << boolalpha;
  cout << "Does cm0 contain \"three\"? " << cm0.contains("three") << '\n';
  cout << "Has  cm0         \"three\"? " << cm0.has("three") << '\n';

  cout << "Test copy constructing \'cmcopied0\' with \'cmil\':\n";
  CascadeMap_t cmcopied0(cmil); // two pairs should be copied in
  cout << "Does cmcopied0 contain \"three\"? " << cmcopied0.contains("three") << '\n';
  cout << "Has  cmcopied0         \"three\"? " << cmcopied0.has("three") << '\n';
  cout << "cmcopied0 holds: " << cmcopied0.size() << " elements.\n";

  cout << "Test copy constructing \'cmassigned0\' with \'cmil\':\n";
  CascadeMap_t cmassigned0;
  cmassigned0 = cmil; // two pairs should be copied in
  cout << "Does cmassigned0 contain \"three\"? " << cmassigned0.contains("three") << '\n';
  cout << "Has  cmassigned0         \"three\"? " << cmassigned0.has("three") << '\n';
  cout << "cmassigned0 holds: " << cmassigned0.size() << " elements.\n";


  cout << "\nBy the way, the sizes of objects cm0, cmil in memory are ";
  cout << "cm0: " << sizeof(cm0) << " (bytes), and cmil: " << sizeof(cmil) << " (bytes).\n";
  cout << "(\'ptr_to_above\' accounts for just 8 bytes.)\n";

  CascadeMap_t cm_move_constructed(std::move(cmassigned0));
  cout << "After move-constructing \'cm_move_constructed\' from \'cmassigned0\'...\n";
  cout << "Does cmassigned0 contain \"three\"? " << cmassigned0.contains("three") << '\n';
  cout << "Has  cmassigned0         \"three\"? " << cmassigned0.has("three") << '\n';
  cout << "cmassigned0 holds : " << cmassigned0.size() << " elements.\n";
  cout << "Does cm_move_constructed contain \"three\"? " << cm_move_constructed.contains("three") << '\n';
  cout << "Has  cm_move_constructed         \"three\"? " << cm_move_constructed.has("three") << '\n';
  cout << "cm_move_constructed holds: " << cm_move_constructed.size() << " elements.\n";


  return 0;
}


