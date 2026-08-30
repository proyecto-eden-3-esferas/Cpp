#ifndef BOOSTED_BLOCK_H
#define BOOSTED_BLOCK_H

#ifndef BOOSTED_BLOCK_DIAGRAM_H
#include "boosted.block_diagram.h"
#endif

#include <boost/geometry/geometries/box.hpp>
/* Class block<> implements interface indexable<>
 */
template < typename     F = double,
           typename POINT = bg::model::point<F, 2, bg::cs::cartesian>,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F> >
class block : public bg::model::box<POINT>, // a box made of two describing points
              public indexable<F,POINT,INT,ANGLE>
{
public:
  typedef   INT index_type;
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
  typedef Degree<F> degree_type;

  typedef bg::model::box<POINT> box_type;
  typedef indexable<F,POINT,INT,ANGLE> indexable_type;
  using box_type::min_corner, box_type::max_corner;
  using indexable_type::operator[], indexable_type::get_angle;

//protected:
  /* The port interface
     holds variables: top, left, bottom, right
     which mean how many ports are found on each side
   * Helper function top_total() tells the maximum index on side 'top' + 1
   */

  std::vector<point_type> ports;
  index_type top, left, bottom, right;
  enum class side {topside, leftside, bottomside, rightside};
  virtual void initialize_ports();

public:
  index_type total() const {return top + left + bottom + right;};
  side which_side(index_type idx) const;

  // (Non-virtual) Getters and setters:
  const point_type & operator[](index_type idx) const override;
  angle_type          get_angle(index_type idx) const override;

  // Constructors:
  block() {};
  block(const point_type & min, const point_type & max) : box_type(min,max) {};
  block(const point_type & min, const point_type & max,
        index_type t, index_type l, index_type b, index_type r) :
    box_type(min,max), top(t), left(l), bottom(b), right(r), ports(total())
    {initialize_ports();};
};

#ifndef BOOSTED_BLOCK_CPP
#include "boosted.block.cpp"
#endif

#endif
