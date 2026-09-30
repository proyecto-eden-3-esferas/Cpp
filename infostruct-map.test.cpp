#ifndef INFOSTRUCT_MAP_H
#include "infostruct-map.h"
#endif

#include <iostream>
using namespace std;

int main() {

  for(const auto & entry : is0) {
    cout << "Text: \"" << entry.text << "\" has metadata: \"" << entry.metadata << "\"\n";
  }

  return 0;
}
