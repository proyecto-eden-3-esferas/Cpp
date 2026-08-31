#ifndef BOOSTLIKE_LABELED_BLOCK_H
#define BOOSTLIKE_LABELED_BLOCK_H

#ifndef BOOSTLIKE_BLOCK_H
#include "boost-like.block.h"
#endif

#include <string>
#include <initializer_list>
#include <utility>
#include <vector>

template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F> >
class labeled_block : public block<F,POINT,INT,ANGLE> {
public:
  typedef block<F,POINT,INT,ANGLE> block_type;
  using block_type::min_corner, block_type::max_corner;
  using block_type::number_of_ports;
  using block_type::get_angle;

  typedef   INT index_type;
  typedef     F float_type;
  typedef POINT point_type;
  typedef ANGLE angle_type;
  typedef Degree<F> degree_type;

  /* The bilabel interface:
   * the first string in a label pair is meant to be a label inside the block shape
   * the second string in a label pair is meant to be a label outside the block shape
   */
  typedef std::string label_type;
  typedef std::pair<  label_type,label_type> bilabel_type;
  typedef std::vector<bilabel_type> bilabel_container_type;
  //
  bilabel_container_type bilabels;
        label_type & get_inner_label_at(index_type idx);
  const label_type & get_inner_label_at(index_type idx) const;
  void               set_inner_label_at_to(index_type idx, const label_type & lbl);
        label_type & get_outer_label_at(index_type idx);
  const label_type & get_outer_label_at(index_type idx) const;
  void               set_outer_label_at_to(index_type idx, const label_type & lbl);

  // Constructors:
  labeled_block() {bilabels.resize(0);};
  labeled_block(const point_type & min, const point_type & max) : block_type(min,max)
                  {bilabels.resize(0);};
  labeled_block(const point_type & min, const point_type & max,
                index_type t, index_type l, index_type b, index_type r)
                : block_type(min,max,t,l,b,r)
                {bilabels.resize(number_of_ports());};
  labeled_block(const point_type & min, const point_type & max,
                index_type t, index_type l, index_type b, index_type r,
                std::initializer_list<bilabel_type> il)
                : block_type(min,max,t,l,b,r), bilabels(il)
                {bilabels.resize(number_of_ports());};

};

#ifndef SEPARATE_COMPILATION
  #ifndef BOOSTLIKE_LABELED_BLOCK_CPP
    #include "boost-like.labeled_block.cpp"
  #endif
#endif

#endif
