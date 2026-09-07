#ifndef BOOSTLIKE_INTER_POLYLINE_H
#define BOOSTLIKE_INTER_POLYLINE_H

#ifndef BOOSTLIKE_POINT_H
#include "boost-like.point.h"
#endif

#include <initializer_list>
#include <vector>

/*
 * What about extreme or all points being const references?
 * Well, next you will demand for some point coordinates to be references,
   the others to be values
 */

template<typename F = double,
         std::size_t DIM = 2,
         typename CoordinateSystem = boost::geometry::cs::cartesian,
         //typename POINT = point<F,2, CoordinateSystem>,
         template <typename> typename VECTOR = std::vector
        >
class inter_polyline {
public:
  typedef point<F,DIM,CoordinateSystem> point_type;
  typedef VECTOR<point_type> container_type;

  point_type start, stop;
  container_type interpoints;

  inter_polyline(const point_type & st, const point_type & sp) : start(st), stop(sp) {};
  inter_polyline(const point_type & st,
                 const point_type & sp,
                 std::initializer_list<point_type> il)
  : start(st), stop(sp), interpoints(il) {};
};

#endif
