#ifndef BOOSTLIKE_BOX_H
#define BOOSTLIKE_BOX_H

#ifndef BOOSTLIKE_POINT_H
#include "boost-like.point.h"
#endif

/* TODO
 [ ] rename box to boostlike_box
 [ ] rename point to boostlike_point
 [ ] derive class boostlike_labeled_block from boostlike_block
 [ ] develop boostlike.* and boosted.* in parallel:
     all you need is to use your slim point class
     instead of juggernaut boost::geometry::model::point
     and so on, analogously
 *
 */

template<typename F = double,
         std::size_t DIM = 2,
         typename CoordinateSystem = boost::geometry::cs::cartesian,
         typename POINT = point<F,DIM,CoordinateSystem>
        >
class box
{
  POINT min, max;
public:
  typedef POINT point_type;
public:
        POINT & min_corner()       {return min;};
        POINT & max_corner()       {return max;};
  const POINT & min_corner() const {return min;};
  const POINT & max_corner() const {return max;};
  const F  width() const {return max_corner(). template get<0>() - min_corner(). template get<0>();};
  const F height() const {return max_corner(). template get<1>() - min_corner(). template get<1>();};
  // Constructors
  box() {};
  box(const POINT& pmin, const POINT& pmax) : min(pmin), max(pmax) {};
};

#endif
