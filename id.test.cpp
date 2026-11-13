#define DEBUG

#include <iostream>

#ifndef ID_H
#include "id.h"
#endif

using namespace std;

int main() {
  id i0;
  cout << "\'i0\' has id: " << i0.get_id() << endl;

  id* pi1 = new id();
  cout << "\'pi1\' on the heap has id: " << pi1->get_id() << endl;
  id* pi2 = new id();
  cout << "\'pi2\' on the heap has id: " << pi2->get_id() << endl;

  id i3, i4;
  cout << "\'i3\' has id: " << i3.get_id() << endl;
  cout << "\'i4\' has id: " << i4.get_id() << endl;

  cout << "Delete \'i1\' so that its id becomes available to next id object\n";
  delete pi1;
  cout << "Delete \'i2\' so that its id becomes available to next id object\n";
  delete pi2;

  id i5, i6;
  cout << "\'i5\' has id: " << i5.get_id() << endl;
  cout << "\'i6\' has id: " << i6.get_id() << endl;

  return 0;
};
