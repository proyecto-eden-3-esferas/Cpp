#ifndef BOOSTLIKE_POINT_H
#define BOOSTLIKE_POINT_H

#include <array>
#include <boost/geometry/core/cs.hpp>

/* TODO
 [ ] rename point to boostlike_point
 */

template<typename F = double,
         std::size_t DIM = 2,
         typename CoordinateSystem = boost::geometry::cs::cartesian
        >
class point
{
public:
  typedef point<F,DIM,CoordinateSystem> point_type;

  // The Boost.Geometry Point Interface:
  std::array<F, DIM> coordinates;
  template <std::size_t IDX>
  F    get()      const {return coordinates[IDX];};
  template <std::size_t IDX>
  void set(F val)       {       coordinates[IDX] = val;};

  /* The Shifting Interface
   * is useful for reshaping multilines connecting ports on blocks
   */
  void shift_horizontally_by(F h) {coordinates[0] += h;};
  void shift_vertically_by(  F v) {coordinates[1] += v;};
  void shift_by(F h, F v) {
    shift_horizontally_by(h);
    shift_vertically_by(  v);
  };
  void shift_by(const point_type & pt) {
    shift_horizontally_by(pt.coordinates[0]);
    shift_vertically_by(  pt.coordinates[1]);
  };

  // Constructors
  point()         : coordinates{0.0, 0.0} {};
  point(F x)      : coordinates{  x, 0.0} {};
  point(F x, F y) : coordinates{  x,   y} {};
};

#endif
