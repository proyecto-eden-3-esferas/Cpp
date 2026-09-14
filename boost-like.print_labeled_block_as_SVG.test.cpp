#include "boost-like.print_as_SVG.h"

#include <vector>


typedef unsigned int index_type;
typedef double float_type;
typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef        Degree<float_type>                         angle_type;
typedef         block<float_type, point_type, angle_type> block_type;
typedef labeled_block<float_type, point_type, angle_type> labeled_block_type;

point_type    min(100.0, 100.0), max(200.0, 300.0);
point_type farmin(400.0, 400.0), farmax(480.0, 480.0);

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
labeled_block_type farbl6(farmin, farmax, 2, 2, 2, 2);

typedef print_as_SVG<float_type> print_as_SVG_type;


#include <iostream>
#include <string>
#include <vector>
using namespace std;

std::vector<std::string> vecOfStrings{"one", "two", "three", "four", "five", "six", "seven", "eit", "nine", "ten", "elf", "twelf", "13", "14", "15", "16", "17", "18", "19", "twenty", "21", "22", "23"};

int main() {

  print_as_SVG_type p(std::cout);

  // Print a labeled_block<> (bl6) with id attribute = "bl6":
  p(bl6, "bl6");

  // Test public member function 'print_as_SVG_type::make_vertical_label_angle_steeper()'
#ifdef TEST_MAKE_VERTICAL_LABEL_STEEPER
  cout << "Do you want member variable \'vertical_label_angle\' to be made steeper? Type \'y\' or \'n\'\n";
  char q;
  cin >> q;
  if(q=='y') {
    cout << "\'vertical_label_angle\' has been made steeper.\n";
    p.make_vertical_label_angle_steeper();
  }
#else
  p.make_vertical_label_angle_steeper();
#endif

  for( index_type idx = 0; idx < bl6.size(); ++idx)
    p.print_external_label_on_block_at_port(vecOfStrings[idx], bl6, idx, 6, 6);


  // Draw 'farbl6' and make its area a local link to 'bl6':
  p.open_locallink("bl6");
    p(farbl6);
  p.close_link();

  return 0;
}
