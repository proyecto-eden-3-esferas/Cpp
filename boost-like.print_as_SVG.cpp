#ifndef BOOSTLIKE_PRINT_AS_SVG_CPP
#define BOOSTLIKE_PRINT_AS_SVG_CPP

#ifndef BOOSTLIKE_PRINT_AS_SVG_H
#include "boost-like.print_as_SVG.h"
#endif

template < typename     F,
           typename POINT,
           typename   INT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,INT,ANGLE,MAP>::operator() (const box_type& b) {
  out << "<rect";
  out << " x=\"" << b.min_corner(). template get<0>() << "\"";
  out << " y=\"" << b.min_corner(). template get<1>() << "\"";
  out << " width=\""  << b.width()  << "\"";
  out << " height=\"" << b.height() << "\"";
  //out << " style=\"fill:white; stroke:black; stroke-width: 2; fill-opacity: 0.3; stroke-opacity: 0.9\"";
  out << "/>\n";
};

template < typename     F,
           typename POINT,
           typename   INT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,INT,ANGLE,MAP>::operator() (const labeled_block_type& lb) {
  this->operator() (lb);
};


/* Constructors
 */

template < typename     F,
           typename POINT,
           typename   INT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
print_as_SVG<F,POINT,INT,ANGLE,MAP>::print_as_SVG(ostream_type & o,
                                                  F w, F h)
: XMLprint_type(o), width(w), height(h)
{
  stack_of_names.push("svg");
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\"";
  out <<  " width=\"" <<  width << '\"';
  out << " height=\"" << height << '\"';
  add_style(style);
  out << ">\n";
};

template < typename     F,
           typename POINT,
           typename   INT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
print_as_SVG<F,POINT,INT,ANGLE,MAP>::print_as_SVG(ostream_type & o,
                                                  const string_map_type & sty,
                                                  F w, F h)
: XMLprint_type(o), width(w), height(h)
{
  stack_of_names.push("svg");
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\"";
  out <<  " width=\"" <<  width << '\"';
  out << " height=\"" << height << '\"';
  add_style(sty);
  out << ">\n";
};


#endif
