#ifndef BOOSTLIKE_BOX_H
#include "boost-like.box.h"
#endif

#include <iostream>
point<double,2> pmin(0.0, 0.0), pmax(40.0, 30.0), center3(22.0, 33.0);
box<double,2> box0;
box<double,2> box2(pmin, pmax);
box<double,2> box3(center3, 4, 6);


using namespace std;

int main() {


  cout << "\'pmax\' has coordinates: " << pmax.get<0>() << " and " << pmax.get<1>() << "\n";

  cout << "\'pmin\' has coordinates: ";
  pmin.print(std::cout, ", ", "{", "}");


  cout << "\nbox2.max_corner has coordinates: " << box2.max_corner().get<0>() << " and " << box2.max_corner().get<1>() << "\n";
  cout << "or, relying on point<>::print(): ";
  box2.max_corner().print(cout, ", ");

  cout << "\nFinally, box2 has its stated center at: ";
  box2.center().print(cout, ", ");
  cout << '\n';

  cout << "box3 has center at "; box3.center().print(cout, ", ", "(", ")");
  cout << ",     min_corner at "; box3.min_corner().print(cout, ", ", "(", ")");
  cout << ", and max_corner at "; box3.max_corner().print(cout, ", ", "(", ")");

  cout << '\n';

  return 0;
}
