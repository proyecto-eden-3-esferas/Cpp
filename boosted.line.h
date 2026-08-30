#include <boost/geometry.hpp>
namespace bg = boost::geometry;


template <typename F = double,
          typename POINT = bg::model::point<F, 2, bg::cs::cartesian>,
          typename ANGLE = Degree<F> >
class line {
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
protected:
  // Member variables:
  point_type be,en;

public:
  virtual float_type get_beg_angle() const = 0;
  virtual float_type get_end_angle() const = 0;

};
