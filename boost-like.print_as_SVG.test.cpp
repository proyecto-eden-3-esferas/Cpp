#include "boost-like.print_as_SVG.h"

#include <vector>


typedef unsigned int index_type;
typedef double float_type;

typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef   box< float_type, 2>   box_type;
typedef Degree<float_type> angle_type;
typedef block< float_type, point_type, index_type, angle_type> block_type;
typedef std::vector<point_type> container_type;

point_type min(5.0, 5.0), max(45.0, 35.0);
/* Define 3 points:
   'block0' is default-constructed
   'block2' only defines min_corner and max_corner yet has no ports defined
 *
 */
block_type block0;
block_type block2(min, max);
block_type block6(min, max, 4, 3, 2, 6);


int main() {


  point_type pmin(10,10), pmax(40,80);

  box_type box1(pmin,pmax);

  print_as_SVG<> p(std::cout);
  p.go_in(); // go down one level, therefore indent once

  p(box1);
  p(block6);

  // Now print a sequence container of points as a polyline:
  container_type poly{min, pmin, pmax, max};
  p.print_as_polyline(poly);

  return 0;
}
