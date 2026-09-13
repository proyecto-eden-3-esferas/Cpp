#include "boost-like.print_as_SVG.h"

#include <vector>


typedef unsigned int index_type;
typedef double float_type;

typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef Degree<float_type> angle_type;
typedef block< float_type, point_type/*, index_type, angle_type*/> block_type;

typedef print_as_SVG<float_type> print_as_SVG_type;

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



  p.print_label(pmax, "label",
                1, 2, print_as_SVG_type::text_anchor::start,
                typename print_as_SVG_type::degree_type(45));

  return 0;
}
