#include "NamedType.h"

/* Class indexable<> is an interface class
 * with pure virtual functions get_x(INDEX) and get_y(INDEX),
 * which return the x and y coordinates of a point on the outline
 * given an index ranging 0 to N - 1
 */
template < typename   F = double,
           typename INT = unsigned int>
class indexable {
public:
  typedef INT index_type;
  typedef   F float_type;
  virtual get_x(index_type idx) const = 0;
  virtual get_y(index_type idx) const = 0;
};

/* Class angular<> is an interface class
 * with pure virtual functions get_x(ANGLE) and get_y(ANGLE),
 * which return the x and y coordinates of a point on the outline
 * given an angle, usually in radians or sexagesimal degress (default)
 */
template < typename     F = double,
           typename ANGLE = Degree<F> >
class angular {
public:
  typedef     F float_type;
  typedef ANGLE angle_type;
  virtual get_x(angle_type idx) const = 0;
  virtual get_y(angle_type idx) const = 0;
};

template <typename F = double
          typename ANGLE = Degree<F> >
class arrowhead {
public:
  virtual F get_tip_x() const = 0;
  virtual F get_tip_y() const = 0;
  virtual F get_butt_x() const = 0;
  virtual F get_butt_y() const = 0;
  ANGLE get_angle() const = 0;
  virtual F get_length() const = 0;
};

template <typename F = double
          typename ANGLE = Degree<F> >
class line {
public:
  virtual get_beg_angle() const = 0;
  virtual get_end_angle() const = 0;

};

/* Class addressable<INT,ANGLE,F> is a pure interface
   with no member variables or implemented member functions.
   derived from both indexable<> and angular<>
 * Often enough, developers will be implemented
   either an indexable<> or an angular interface<>
 */
template < typename     F = double,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F>
         >
class addressable : public indexable<F,INT>, public angular<F,ANGLE> {
public:
  using indexable<  F,INT>::get_x, indexable<F,INT>::get_y;
  using   angular<F,ANGLE>::get_x, angular<F,ANGLE>::get_y;

};
