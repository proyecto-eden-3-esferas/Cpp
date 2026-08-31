#ifndef BOOSTED_BLOCK_H
#include "boosted.block.h"
#endif

//#include "boosted.line.h"
//#include "boosted.arrowhead.h"

typedef unsigned int index_type;
typedef           double float_type;
typedef bg::model::point<float_type, 2, bg::cs::cartesian> point_type;
typedef           Degree<float_type> angle_type;
typedef block<float_type, point_type, index_type, angle_type> block_type;

point_type min(0.0, 0.0), max(40.0, 30.0);

/* Define 3 points:
   'b0' is default-constructed
   'b2' only defines min_corner and max_corner and is incomplete
 *
 */
block_type b0;
block_type b2(min, max);
block_type b6(min, max, 4, 3, 2, 6);

#include <iostream>
using namespace std;

int main() {

  cout << "\'b2\' has min_corner = (" << b2.min_corner().get<0>() << ',';
  cout <<                                b2.min_corner().get<1>() << ")\n";
  cout << "\'b2\' has max_corner = (" << b2.max_corner().get<0>() << ',';
  cout <<                                b2.max_corner().get<1>() << ")\n\n";

  index_type idx;
  cout << "Type an index smaller that " << b6.number_of_ports() << " and press ENTER: ";
  cin >> idx;
  cout << "Port " << idx << " on \'b6\' has coordinates (";
  cout << b6[idx].get<0>() << ',' << b6[idx].get<1>();
  cout << ")\n";
  cout << "Port " << idx << " has angle / faces " << b6.get_angle(idx).get() << "\n\n";

  cout << "b6.top=" << b6.top << '\n';
  cout << "b6.left=" << b6.left << '\n';
  cout << "b6.bottom=" << b6.bottom << '\n';
  cout << "b6.right=" << b6.right << "\n\n";

  cout << "Now print all the ports.\n";
  for(int i = 0; i < b6.number_of_ports(); i++) {
    cout << "port " << i << " = (" << b6[i].get<0>() << ',' << b6[i].get<1>() << ")\n";
  }


  return 0;
}
