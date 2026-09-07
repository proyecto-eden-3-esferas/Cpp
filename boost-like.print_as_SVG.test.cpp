#include "boost-like.print_as_SVG.h"


typedef unsigned int index_type;
typedef double float_type;

typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef   box< float_type, 2>   box_type;
typedef Degree<float_type> angle_type;
typedef block< float_type, point_type, index_type, angle_type> block_type;

point_type min(5.0, 5.0), max(45.0, 35.0);
/* Define 3 points:
   'b0' is default-constructed
   'b2' only defines min_corner and max_corner and is incomplete
 *
 */
block_type block0;
block_type block2(min, max);
block_type block6(min, max, 4, 3, 2, 6);


int main() {


  point_type pmin(10,10), pmax(40,80);

  box_type box1(pmin,pmax);

  print_as_SVG<> p(std::cout);
  p(box1);
  p(block6);

  return 0;
}
