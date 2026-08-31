#ifndef BOOSTLIKE_BLOCK_H
#define BOOSTLIKE_BLOCK_H

#ifndef BOOSTLIKE_BLOCK_DIAGRAM_H
#include "boost-like.block-diagram.h"
#endif

#ifndef BOOSTLIKE_BOX_H
#include "boost-like.box.h"
#endif

#include <vector>

/* Class block<> implements interface indexable<>
 */
template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F> >
class block : public box<F, 2, boost::geometry::cs::cartesian, POINT>, // a box made of two describing points
              public indexable<F,POINT,INT,ANGLE>
{
public:
  typedef   INT index_type;
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
  typedef Degree<F> degree_type;

  typedef box<F, 2, boost::geometry::cs::cartesian, POINT> box_type;
  typedef indexable<F,POINT,INT,ANGLE> indexable_type;
  using box_type::min_corner, box_type::max_corner;
  using indexable_type::operator[], indexable_type::get_angle;

//protected:
  /* The port interface
     holds variables: top, left, bottom, right
     which mean how many ports are found on each side
   * Helper function top_number_of_ports() tells the maximum index on side 'top' + 1
   */
  std::vector<point_type> ports;
  index_type top, left, bottom, right;
  enum class side {topside, leftside, bottomside, rightside};
  virtual void initialize_ports();

public:
  index_type number_of_ports() const {return top + left + bottom + right;};
  side which_side(index_type idx) const;

  // (Non-virtual) Getters and setters:
  const point_type & operator[](index_type idx) const override;
  angle_type          get_angle(index_type idx) const override;

  // Constructors:
  block();
  block(const point_type & min, const point_type & max);
  block(const point_type & min, const point_type & max,
        index_type t, index_type l, index_type b, index_type r);
};

#ifndef SEPARATE_COMPILATION
  #ifndef BOOSTLIKE_BLOCK_CPP
    #include "boost-like.block.cpp"
  #endif
#endif

#endif
