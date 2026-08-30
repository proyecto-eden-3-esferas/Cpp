#include <boost/geometry.hpp>
namespace bg = boost::geometry;


template <typename F = double,
          typename POINT = bg::model::point<F, 2, bg::cs::cartesian>,
          typename ANGLE = Degree<F> >
class arrowhead {
public:
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
protected:
  // Member variables:
  point_type tip, butt;
  float_type length, width;
public:
  // Getters and Setters
  virtual       point_type & get_tip()        = 0;
  virtual const point_type & get_tip()  const = 0;
  virtual       point_type & get_butt()       = 0;
  virtual const point_type & get_butt() const = 0;
  ANGLE get_angle() const = 0;
  virtual float_type get_length() const = 0;
};
