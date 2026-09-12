#ifndef BOOSTLIKE_BOX_H
#define BOOSTLIKE_BOX_H

#ifndef BOOSTLIKE_POINT_H
#include "boost-like.point.h"
#endif

/* Class box behaves much like Boost.Geometry model::box
 * While model::box has template parameters like:
     template<typename Point>
     class model::box { ... };
   I have chosen for my boost-like box
   to have the same template parameters as boost-like point plus a point parameter
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
  POINT min, max, cntr;
public:
  typedef POINT point_type;
public:
  // Boost.Geometry model::box interface:
        POINT & min_corner()       {return min;};
        POINT & max_corner()       {return max;};
  const POINT & min_corner() const {return min;};
  const POINT & max_corner() const {return max;};
  // Added member functions:
  const F  width() const {return max_corner(). template get<0>() - min_corner(). template get<0>();};
  const F height() const {return max_corner(). template get<1>() - min_corner(). template get<1>();};
  const POINT & center() const {return cntr;};
  // Constructors
  box();
  box(const POINT& pmin, const POINT& pmax);
  box(const POINT& center, F wide, F high);
};

#endif

#ifndef BOOSTLIKE_BOX_CPP
#define BOOSTLIKE_BOX_CPP


// Constructors:

template<typename F,
         std::size_t DIM,
         typename CoordinateSystem,
         typename POINT >
box<F,DIM,CoordinateSystem,POINT>::box() {};

template<typename F,
         std::size_t DIM,
         typename CoordinateSystem,
         typename POINT >
box<F,DIM,CoordinateSystem,POINT>::box(const POINT& center, F wide, F high)
: min(center. template get<0>() - wide / 2, center. template get<1>() - high / 2),
  max(center. template get<0>() + wide / 2, center. template get<1>() + high / 2),
  cntr(center)
{};

template<typename F,
         std::size_t DIM,
         typename CoordinateSystem,
         typename POINT >
box<F,DIM,CoordinateSystem,POINT>::box(const POINT& pmin, const POINT& pmax)
: min(pmin),
  max(pmax),
  cntr( ( min. template get<0>() + max. template get<0>()) / 2,
        ( min. template get<1>() + max. template get<1>()) / 2 )
{};

#endif
