#include "Level.h"

#ifndef LEVELER_CONCEPT_H
#include "Leveler.h"
#endif

#include <iostream>

using namespace std;

// design a dumb function with a template parameter satisfying Leveler concept
template <Leveler LEVEL>
void foo(LEVEL & l) { ++l;};


typedef signed int sint_t;
typedef Level<sint_t> level_t;

int main() {

  level_t l0, l1(0), l2;
  ++l1;
  l2 = l1;
  l2++;
  level_t l3(l2);
  cout << "\'l3\' holds " << l3.get() << ", for a short while, wait and see...\n";
  l3 = 3;
  level_t & l1ref = l1;

  cout << "Print contents of Level objects by calling the get() method on each:\n";
  cout << "\'l0\' holds " << l0.get() << '\n';
  cout << "\'l1\' holds " << l1.get() << '\n';
  cout << "\'l2\' holds " << l2.get() << '\n';
  cout << "\'l3\' holds " << l3.get() << '\n';

  cout << "\nCan you decrement a Level object below level==0?\n";
  --l0;
  cout << "After decrementing \'l0\', it holds " << l0.get() << ". There you are!\n";

  cout << "\nNext, test Level::print(OSTREAM&), which just prints level*static_width indentation spaces.\n";
  cout << l1ref << "Indented by \'l1ref\'.\n";
  cout << ++l1ref << "Indented by \'++l1ref\'.\n";

  cout << "Let\'s call foo(LEVEL& l1). \'l1\' starts holding value " << l1.get();
  foo(l1);
  cout << ". After the call, \'l1\' holds " << l1.get() << '\n';

  // The following won\'t compile as int does not satisfy concept Leveler:
  /*
  cout << "Let\'s next call foo(int& i).\n";
  int i{3};
  foo(i);
   */


  cout << "\nLast, try incrementing a Level until its static \'max_level\' is reached,\n";
  cout << "(only for 100 iterations) hoping for the check mechanism to detect overstepping the limit\n";
  cout << "WARNING: this may raise an exception which, if uncaught, will terminate the program abruptly.\n";
  for(int i = 0; i < 100; ++i)
  {
    ++l3;
    cout << '[' << l3.get() << ']' << flush;
  }


  cout << "Bye!\n";

  return 0;
}
