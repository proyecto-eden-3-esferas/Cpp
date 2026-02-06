#ifndef ATTRIBUTES_H
#include "Attributes.former.h"
#endif

typedef Attributes<> Attributes_t;

#include <iostream>
#include <sstream>

using namespace std;

int main() {

  Attributes_t attrs0('\'');
  Attributes_t attrs1(attrs0, '\'');

  cout << boolalpha;
  cout << "Is attrs0.ptr_to_above nullptr? "  <<  (attrs0.ptr_to_above == nullptr) << '\n';
  cout << "Is attrs1.ptr_to_above nullptr? "  <<  (attrs1.ptr_to_above == nullptr) << '\n' << '\n';

  cout << "attrs0.ptr_to_above nullptr is "  <<  attrs0.ptr_to_above << '\n';
  cout << "attrs1.ptr_to_above nullptr is "  <<  attrs1.ptr_to_above << '\n' << '\n';

  cout << "Does \'attrs0\' contain key \"date\"? " << attrs0.contains("date") << '\n';
  cout << "Does \'attrs1\' contain key \"date\"? " << attrs1.contains("date") << '\n' << '\n';

  cout << "Adding attribute \"date\", \"class\" and \"subclass\" in \'attrs0\'...\n";
  attrs0.insert({"date", "1966"});
  attrs0.insert({"class", "event"});
  attrs0.insert({"subclass", "birth"});

  cout << "Does \'attrs0\' have key \"date\"? " << attrs0.has("date") << '\n';
  cout << "Does \'attrs1\' have key \"date\"? " << attrs1.has("date") << '\n';
  cout << "Indeed, \"date\" maps to \"" << attrs0.get("date") << "\" (through \'attrs0\')\n\n";
  // whereas "attrs0.get("date")" would cause a segmentation fault


  Attributes_t attrs2(std::move(attrs0));
  cout << "After move constructing \'attrs2\' with \'attrs0\'...\n";
  cout << "Does \'attrs0\' have key \"date\"? " << attrs0.has("date") << '\n';
  cout << "Does \'attrs1\' have key \"date\"? " << attrs1.has("date") << '\n';
  cout << "Does \'attrs2\' have key \"date\"? " << attrs2.has("date") << '\n';

  Attributes_t attrs3;
  attrs3 = std::move(attrs2);
  cout << "After move assignment from \'attrs2\' to new \'attrs3\'...\n";
  cout << "Does \'attrs2\' have key \"date\"? " << attrs2.has("date") << '\n';
  cout << "Does \'attrs3\' have key \"date\"? " << attrs3.has("date") << '\n';

  cout << "\nNow print attributes in \'attrs3\': ";
  attrs3.print_map(cout);
  cout << "\nequals: ";
  attrs3.print(cout, Level(0));

  cout << "Now try to load an std::stringstream with an attributes map...\n";
  std::stringstream ss;
  attrs3.load(ss);
  cout << "ss.str() is: \"" << ss.str() << "\"\n";

  return 0;
}
