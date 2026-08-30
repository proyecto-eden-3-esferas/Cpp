#ifndef BOOSTED_BLOCK_CPP
#define BOOSTED_BLOCK_CPP

#ifndef BOOSTED_BLOCK_H
#include "boosted.block.h"
#endif

template < typename F, typename POINT, typename INT, typename ANGLE>
void block<F,POINT,INT,ANGLE>::initialize_ports() {
  ports.resize(total());
  /* initialize each point in block<>::ports
     starting at the top right corner, anticlockwise
   */

  float_type x, y, spacing;

  // initialize the top side:
  x = bg::get<0>(max_corner());
  y = bg::get<1>(max_corner());
  spacing = (bg::get<0>(max_corner()) - bg::get<0>(min_corner())) / top;
  x -= spacing / 2;
  for(int i = 0; i < top; ++i) {
    bg::set<0>(ports[i], x);
    bg::set<1>(ports[i], y);
    x -= spacing;
  }

  // initialize the left side:
  x = bg::get<0>(min_corner());
  y = bg::get<1>(max_corner());
  spacing = (bg::get<1>(max_corner()) - bg::get<1>(min_corner())) / left;
  y -= spacing / 2;
  for(int i = top; i < left + top; ++i) {
    bg::set<0>(ports[i], x);
    bg::set<1>(ports[i], y);
    y -= spacing;
  }

  // initialize the bottom side:
  x = bg::get<0>(min_corner());
  y = bg::get<1>(min_corner());
  spacing = (bg::get<0>(max_corner()) - bg::get<0>(min_corner())) / bottom;
  x += spacing / 2;
  for(int i = left + top; i < bottom + left + top; ++i) {
    bg::set<0>(ports[i], x);
    bg::set<1>(ports[i], y);
    x += spacing;
  }

  // initialize the right side:
  x = bg::get<0>(max_corner());
  y = bg::get<1>(min_corner());
  spacing = (bg::get<1>(max_corner()) - bg::get<1>(min_corner())) / right;
  y += spacing / 2;
  for(int i = bottom + left + top; i < right + bottom + left + top; ++i) {
    bg::set<0>(ports[i], x);
    bg::set<1>(ports[i], y);
    y += spacing;
  }
};

template < typename F, typename POINT, typename INT, typename ANGLE>
block<F,POINT,INT,ANGLE>::side block<F,POINT,INT,ANGLE>::which_side(index_type idx) const {
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
block<F,POINT,INT,ANGLE>::angle_type
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

#endif
