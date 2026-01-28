#ifndef ATTRIBUTES_H
#include "Attributes.h"
#endif

typedef Attributes<std::map> Attributes_t;

#include <iostream>

using namespace std;

int main() {

  Attributes_t attrs0('\'');
  Attributes_t attrs1(attrs0, '\'');

  cout << boolalpha;
  cout << "Is attrs0.ptr_to_above nullptr? "  <<  (attrs0.ptr_to_above == nullptr) << '\n';
  cout << "Is attrs1.ptr_to_above nullptr? "  <<  (attrs1.ptr_to_above == nullptr) << '\n' << '\n';

  cout << "attrs0.ptr_to_above nullptr is "  <<  attrs0.ptr_to_above << '\n';
  cout << "attrs1.ptr_to_above nullptr is "  <<  attrs1.ptr_to_above << '\n' << '\n';

  cout << "Does \'attrs0\' have key \"date\"? " << attrs0.contains("date") << '\n';
  cout << "Does \'attrs1\' have key \"date\"? " << attrs1.contains("date") << '\n' << '\n';

  cout << "Adding attribute \"date\", \"class\" and \"subclass\" in \'attrs0\'...\n";
  attrs0.set("date", "1966");
  attrs0.set("class", "event");
  attrs0.set("subclass", "birth");

  cout << "Does \'attrs0\' have key \"date\"? " << attrs0.contains("date") << '\n';
  cout << "Does \'attrs1\' have key \"date\"? " << attrs1.contains("date") << '\n';
  cout << "Indeed, \"date\" maps to \"" << attrs1.at("date") << "\"\n\n";

  cout << "A member up-to-date string holds attributes as: \"" << attrs0.get_attributes_string() << "\"\n\n";

  Attributes_t attrs2(std::move(attrs0));
  cout << "After move constructing \'attrs2\' with \'attrs0\'...\n";
  cout << "Does \'attrs0\' have key \"date\"? " << attrs0.contains("date") << '\n';
  cout << "Does \'attrs1\' have key \"date\"? " << attrs1.contains("date") << '\n';
  cout << "Does \'attrs2\' have key \"date\"? " << attrs2.contains("date") << '\n';

  Attributes_t attrs3;
  attrs3 = std::move(attrs2);
  cout << "After move assignment from \'attrs2\' to new \'attrs3\'...\n";
  cout << "Does \'attrs2\' have key \"date\"? " << attrs2.contains("date") << '\n';
  cout << "Does \'attrs3\' have key \"date\"? " << attrs3.contains("date") << '\n';

  return 0;
}
