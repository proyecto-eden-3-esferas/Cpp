#include "Level.h"

#include <iostream>

using namespace std;

int main() {

  Level l0, l1, l2;
  ++l1;

  cout << "First, test conversion operator:\n";
  cout << "\'l0\' holds " << l0.get() << '\n';
  cout << "\'l1\' holds " << l1.get() << '\n';
  cout << "\'l2\' holds " << l2.get() << '\n';

  cout << "First, test Level::get() method:\n";
  cout << "\'l0\' holds " << l0.get() << '\n';
  cout << "\'l1\' holds " << l1.get() << '\n';
  cout << "\'l2\' holds " << l2.get() << '\n';

  return 0;
}
