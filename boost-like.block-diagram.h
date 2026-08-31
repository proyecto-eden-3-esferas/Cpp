#ifndef BOOSTLIKE_BLOCK_DIAGRAM_H
#define BOOSTLIKE_BLOCK_DIAGRAM_H

#include "NamedType.h"

#ifndef BOOSTLIKE_POINT_H
#include "boost-like.point.h"
#endif

/* Should a getter return a non-const reference?
 * Should a setter be provided instead?
 */

/* Class indexable<> is an interface class
 * with pure virtual functions get<INDEX>() and set<INDEX>(VALUE),
 * which return the x and y coordinates of a point on the outline
 * given an index ranging 0 to N - 1
 */
template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F> >
class indexable {
public:
  typedef   INT index_type;
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
  // Getters and setters:
  virtual const point_type & operator[](index_type idx) const = 0;
  virtual angle_type          get_angle(index_type idx) const = 0;
};

/* Class angular<> is an interface class
 */
template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename ANGLE = Degree<F> >
class angular {
public:
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
  // Member variables:
protected:
  point_type center;
public:
  // Getters and setters:
        point_type& get_center()       {return center;};
  const point_type& get_center() const {return center;};
  void              set_center(const point_type & pt) {center = pt;};
  virtual const point_type & operator()(angle_type ang) const = 0;
  // Constructors and destructor:
  angular(const point_type& pt) : center(pt) {};
  angular(F x=0.0, F y=0.0)     : center(x,y) {};
};


#endif
