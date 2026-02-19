/* File "Reversible.test.cpp"
 * tests concept Reversible and class ReversibleSequential<Reversible>
 * A 'reversible_for_testing' struct satisfying 'Reversible' is declared
 * Then a ReversibleSequential<reversible_for_testing> is constructed
   and reversible_for_testing objects are pushed and popped;
 */


#ifndef REVERSIBLE_H
#include "Reversible.h"
#endif

#include <iostream>
#include <stack>

typedef char char_type;

struct reversible_for_testing {
  void effect()  {std::cout << "[effect()]";};
  void reverse() {std::cout << "[reverse()]";};
};


//typedef TrivialReversible      reversible_t;
typedef reversible_for_testing reversible_t;

using namespace std;


int main()
{

  ReversibleSequential<reversible_t> trs1;
  cout << "After construction, \'trs1\' has size: " << trs1.size() << '\n';

  reversible_t r0, r1;
  cout << "Pushing two reversible objects: ";
  trs1.push_change(r0);
  trs1.push_change(r1);
  trs1.emplace_change();

#ifdef TEST_REDO_CHANGE
  cout << "\nCall trs1.redo_change() should cause an error condition, possibly an exception." << flush;
  trs1.redo_change();
#endif

  cout << "\n\'trs1\' has now size " << trs1.size() << ". Let\'s pop/reverse all the changes... ";

  while(! trs1.empty())
    trs1.undo_change();

#ifdef TEST_UNDO_CHANGE
  cout << "\n\nLast, call undo_change() when there is no change to be undone.\n";
  cout << "Cursor is " << trs1.get_cursor() << ". Just wait and see. It\'s Going to be painfull.\n" << flush;
  trs1.undo_change();
#endif

  return 0;
}
