#include "boost-like.block.h"
#include "boost-like.inter_polyline.h"
#include "NamedType.h"

typedef unsigned int index_type;
typedef double float_type;

typedef point< float_type, 2, boost::geometry::cs::cartesian> point_type;
typedef Degree<float_type> angle_type;
typedef block< float_type, point_type, index_type, angle_type> block_type;

typedef inter_polyline<float_type,2> inter_polyline_type;

point_type min(5.0, 5.0), max(45.0, 35.0), third(45.0, 5.0), fourth(60.0, 20.0);
inter_polyline_type ipl2(min,max);
inter_polyline_type ipl4(min,max, {third,fourth});

/* define an inter_polyline<> between ports on block<> block8:*/
block_type block8(min,max, 2,2,2,2);
inter_polyline_type ipl6(block8[0], block8[1], {third,fourth});


int main() {

  return 0;
}
