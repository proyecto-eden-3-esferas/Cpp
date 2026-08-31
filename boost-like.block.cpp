#ifndef BOOSTLIKE_BLOCK_CPP
#define BOOSTLIKE_BLOCK_CPP

#ifndef BOOSTLIKE_BLOCK_H
#include "boost-like.block.h"
#endif


template < typename F, typename POINT, typename INT, typename ANGLE>
void block<F,POINT,INT,ANGLE>::initialize_ports() {
  ports.resize(number_of_ports());
  /* initialize each point in block<>::ports
     starting at the top right corner, anticlockwise
   */

  float_type x, y, spacing;

  // initialize the top side:

  x = max_corner(). template get<0>();
  y = max_corner(). template get<1>();
  spacing = (max_corner(). template get<0>() - min_corner(). template get<0>()) / top;
  x -= spacing / 2;
  for(int i = 0; i < top; ++i) {
    ports[i]. template set<0>(x);
    ports[i]. template set<0>(y);
    x -= spacing;
  }

  // initialize the left side:
  x = min_corner(). template get<0>();
  y = max_corner(). template get<1>();
  spacing = (max_corner(). template get<1>() - min_corner(). template get<1>()) / left;
  y -= spacing / 2;
  for(int i = top; i < left + top; ++i) {
    ports[i]. template set<0>(x);
    ports[i]. template set<1>(y);
    y -= spacing;
  }

  // initialize the bottom side:
  x = min_corner(). template get<0>();
  y = min_corner(). template get<1>();
  spacing = (max_corner(). template get<0>() - min_corner(). template get<0>()) / bottom;
  x += spacing / 2;
  for(int i = left + top; i < bottom + left + top; ++i) {
    ports[i]. template set<0>(x);
    ports[i]. template set<1>(y);
    x += spacing;
  }

  // initialize the right side:
  x = max_corner(). template get<0>();
  y = min_corner(). template get<1>();
  spacing = (max_corner(). template get<1>() - min_corner(). template get<1>()) / right;
  y += spacing / 2;
  for(int i = bottom + left + top; i < right + bottom + left + top; ++i) {
    ports[i]. template set<0>(x);
    ports[i]. template set<1>(y);
    y += spacing;
  }
};

template < typename F, typename POINT, typename INT, typename ANGLE>
typename block<F,POINT,INT,ANGLE>::side
block<F,POINT,INT,ANGLE>::which_side(index_type idx) const {
  if(idx < top)
    return side::topside;
  else {
    if(idx < top + left)
      return side::leftside;
    else {
      if(idx < bottom + top + left)
        return side::bottomside;
      else
        return side::rightside;
    }
  }
};

template < typename F, typename POINT, typename INT, typename ANGLE>
const POINT & block<F,POINT,INT,ANGLE>::operator[](index_type idx) const {
  side sd = which_side(idx);
  return ports[idx];
};
template < typename F, typename POINT, typename INT, typename ANGLE>
typename block<F,POINT,INT,ANGLE>::angle_type
block<F,POINT,INT,ANGLE>::get_angle(index_type idx) const {
  side sd = which_side(idx);
  switch (sd) {
    case side::topside:
      return angle_type(degree_type(90));
      break;
    case side::leftside:
      return angle_type(degree_type(180));
      break;
    case side::bottomside:
      return angle_type(degree_type(270));
      break;
    case side::rightside:
      return angle_type(degree_type(0));
      break;
    default:
      return angle_type(degree_type(0));
      break;
  }
};

// Constructors:

template < typename F, typename POINT, typename INT, typename ANGLE>
block<F,POINT,INT,ANGLE>::block()
{};

template < typename F, typename POINT, typename INT, typename ANGLE>
block<F,POINT,INT,ANGLE>::block(const point_type & min, const point_type & max) : box_type(min,max)
{};

template < typename F, typename POINT, typename INT, typename ANGLE>
block<F,POINT,INT,ANGLE>::block(const point_type & min, const point_type & max,
                                index_type t, index_type l, index_type b, index_type r) :
  box_type(min,max), top(t), left(l), bottom(b), right(r), ports(number_of_ports())
{initialize_ports();};


#ifdef SEPARATE_COMPILATION
// #include "boost-like.block.ins"
template class block<float,
                     point<float, 2, bg::cs::cartesian>,
                     unsigned int,
                     Degree<float> >;
template class block<double,
                     point<double, 2, bg::cs::cartesian>,
                     unsigned int,
                     Degree<double> >;
template class block<long double,
                     point<long double, 2, bg::cs::cartesian>,
                     unsigned int,
                     Degree<long double> >;
#endif


#endif
