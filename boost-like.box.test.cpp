#ifndef BOOSTLIKE_BOX_H
#include "boost-like.box.h"
#endif

#include <iostream>
point<double,2> pmin(0.0, 0.0), pmax(40.0, 30.0);
box<double,2> box0;
box<double,2> box2(pmin, pmax);

using namespace std;

int main() {


  cout << "\'pmax\' has coordinates: " << pmax.get<0>() << " and " << pmax.get<1>() << "\n";

  cout << "box2.max_corner has coordinates: " << box2.max_corner().get<0>() << " and " << box2.max_corner().get<1>() << "\n";

  return 0;
}
