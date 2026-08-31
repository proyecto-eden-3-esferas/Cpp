#ifndef BOOSTLIKE_LABELED_BLOCK_H
#include "boost-like.labeled_block.h"
#endif


typedef unsigned int index_type;
typedef double float_type;
typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef           Degree<float_type> angle_type;
typedef block< float_type, point_type, index_type, angle_type> block_type;
typedef labeled_block< float_type, point_type, index_type, angle_type> labeled_block_type;

point_type min(0.0, 0.0), max(40.0, 30.0);

/* Define several labeled_block's:
   'bl0' is default-constructed
   'bl2' only defines min_corner and max_corner and is incomplete
 *
 */
labeled_block_type bl0;
labeled_block_type bl2(min, max);
labeled_block_type bl6(min, max, 4, 3, 2, 6);
labeled_block_type bl7(min, max, 4, 3, 2, 6,
                       {
                         {"input0", "P0"},
                         {"input1", "P1"},
                         {"",       "Clk"}
                       });

#include <iostream>
using namespace std;

int main() {

  cout << "\'bl2\' has min_corner = (" << bl2.min_corner().get<0>() << ',';
  cout <<                                bl2.min_corner().get<1>() << ")\n";
  cout << "\'bl2\' has max_corner = (" << bl2.max_corner().get<0>() << ',';
  cout <<                                bl2.max_corner().get<1>() << ")\n\n";

  index_type idx;
  cout << "Type an index smaller that " << bl6.number_of_ports() << " and press ENTER: ";
  cin >> idx;
  cout << "Port " << idx << " on \'bl6\' has coordinates (";
  cout << bl6[idx].get<0>() << ',' << bl6[idx].get<1>();
  cout << ")\n";
  cout << "Port " << idx << " has angle / faces " << bl6.get_angle(idx).get() << "\n\n";

  cout << "bl7.top=" << bl7.top << '\n';
  cout << "bl7.left=" << bl7.left << '\n';
  cout << "bl7.bottom=" << bl7.bottom << '\n';
  cout << "bl7.right=" << bl7.right << "\n\n";

  cout << "Now print all the ports.\n";
  for(int i = 0; i < bl7.number_of_ports(); i++) {
    cout << "port " << i << " = (" << bl7[i].get<0>() << ',' << bl7[i].get<1>() << ")\n";
  }

  for(const auto & bilabel : bl7.bilabels) {
    cout << "inside: \"" << bilabel.first << "\", outside: \"" << bilabel.second << "\"\n";
  }


  return 0;
}
