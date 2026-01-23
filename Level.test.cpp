#include "Level.h"

#include <iostream>

using namespace std;

int main() {

  typedef signed int sint_t;
  Level<sint_t> l0, l1(0), l2;
  ++l1;
  l2 = l1;
  l2++;
  Level<sint_t> l3(l2);
  cout << "\'l3\' holds " << l3.get() << ", for a short while, wait and see...\n";
  l3 = 3;
  Level<sint_t> & l1ref = l1;

  cout << "Print contents of Level objects by calling the get() method on each:\n";
  cout << "\'l0\' holds " << l0.get() << '\n';
  cout << "\'l1\' holds " << l1.get() << '\n';
  cout << "\'l2\' holds " << l2.get() << '\n';
  cout << "\'l3\' holds " << l3.get() << '\n';


  cout << "\nNext, print contents of Level objects by calling conversion operator \"operator int_t ()\" on each:\n";
  cout << "\'l0\' holds " << l0 << '\n';
  cout << "\'l1\' holds " << l1 << '\n';
  cout << "\'l2\' holds " << l2 << '\n';
  cout << "\'l3\' holds " << l3 << '\n';

  cout << "\nCan you decrement a Level object below level==0?\n";
  --l0;
  cout << "After decrementing \'l0\', it holds " << l0.get() << ". There you are!\n";

  cout << "\nNext, test Level::print(OSTREAM&), which just prints level*static_width indentation spaces.\n";
  cout << l1ref << "Indented by \'l1ref\'.\n";
  cout << ++l1ref << "Indented by \'++l1ref\'.\n";

  cout << "Bye!\n";

  return 0;
}
