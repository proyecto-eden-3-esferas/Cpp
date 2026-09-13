#ifndef BOOSTLIKE_PRINT_AS_SVG_CPP
#define BOOSTLIKE_PRINT_AS_SVG_CPP

#ifndef BOOSTLIKE_PRINT_AS_SVG_H
#include "boost-like.print_as_SVG.h"
#endif


template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::make_vertical_label_angle_steeper() {
  vertical_label_angle = 77;
  top_dx_k = 0.5;
  bot_dx_k = 1.25;
};


template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::open_hyperlink(const string_type& page) {
  indent();
  out << "<a href=\"" << page << "\">\n";
  go_in();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::open_hyperlink(const string_type& page, const string_type& fragment) {
  indent();
  out << "<a href=\"" << page <<  '#' << fragment << "\">\n";
  go_in();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::open_locallink(const string_type& fragment) {
  indent();
  out << "<a href=\"" <<  '#' << fragment << "\">\n";
  go_in();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::close_link() {
  go_out();
  indent();
  out << "</a>\n";
};



template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const box_type& b) {
  indent();
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
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::print_label(
  const point_type & pt,
  const string_type & label,
  F dx, F dy, // X and Y displacements
  text_anchor anchor,
  degree_type deg
) {
  indent();
  out << "<text text-anchor=\"";
  switch (anchor) {
    case text_anchor::start:
      out << "start\"";
      break;
    case text_anchor::middle:
      out << "middle\"";
      break;
    case text_anchor::end:
      out << "end\"";
      break;
    default: break;
  }
  out << " x=\"" << dx << "\" y=\"" << - dy << "\"\n";
  indent();
  out << "fill=\"black\" stroke=\"none\" fill-opacity=\"1.0\"\n";
  indent();
  out << "transform=\"translate("; pt.print(out,",") ;
  out << ") rotate(" << deg.get() << " 0, 0) scale(1, -1)\">" << label << "</text>\n";
};


template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::print_label_on_block_at_port(
  const string_type & label,
  const  block_type &   blk,
         index_type     idx,
  F dx, F dy, // X and Y displacements
  text_anchor anchor,
  degree_type deg
) {
  print_label(blk[idx], label, dx, dy, anchor, deg);
};


template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::print_external_label_on_block_at_port(const string_type & label,
  const  block_type &   blk,
         index_type     idx,
  F dx, F dy) {
  //side sd = blk.which_side(idx);
  switch ( blk.which_side(idx) ) {
    case side::rightside:
      print_label_on_block_at_port(label, blk, idx, dx,          dy, text_anchor::start, degree_type(0.0) );
      indent(); std::cout << "<!-- index " << idx << " is rightside -->\n";
      break;
    case side::topside:
      print_label_on_block_at_port(label, blk, idx, dx*top_dx_k,  dy, text_anchor::start, degree_type(vertical_label_angle) );
      indent(); std::cout << "<!-- index " << idx << " is topside -->\n";
      break;
    case side::leftside:
      print_label_on_block_at_port(label, blk, idx, -dx,          dy, text_anchor::end,   degree_type(0.0) );
      indent(); std::cout << "<!-- index " << idx << " is leftside -->\n";
      break;
    case side::bottomside:
      print_label_on_block_at_port(label, blk, idx, -dx*bot_dx_k, dy, text_anchor::end,   degree_type(vertical_label_angle) );
      indent(); std::cout << "<!-- index " << idx << " is bottomside -->\n";
      break;
    default:
      //print_label_on_block_at_port(label, blk, idx, dx, dy, text_anchor::start, 0.0);
      break;
  }
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::print_internal_label_on_block_at_port(const string_type & label,
  const  block_type &   blk,
        index_type     idx,
  F dx, F dy) {
    //
};



template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const labeled_block_type& lb) {
  this->operator() (lb);
};


/* Members for printing a sequence of points
   rely on print_points_in(CONTAINER_OF_POINTS)
   and print the sequence either as a polyline or a polygon.
 * They rely on:
     void print_as_SVG<>::print_points_in(CONTAINER_OF_POINTS &),
   which, being a template member, is implemented in its header file
 */

template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
template <typename CONTAINER_OF_POINTS>
void print_as_SVG<F,POINT,ANGLE,MAP>::print_as_polyline(const CONTAINER_OF_POINTS & container_of_points,
                         const string_type& strk,
                         const string_type& fll) {
    indent();
    out << "<polyline points=\"";
    print_points_in(container_of_points);
    out << "\" stroke=\"" << strk << "\" fill=\"" << fll << "\"/>\n";
  };

template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
template <typename CONTAINER_OF_POINTS>
void print_as_SVG<F,POINT,ANGLE,MAP>::print_as_polygon(const CONTAINER_OF_POINTS & container_of_points,
                         const string_type& strk,
                         const string_type& fll) {
    indent();
    out << "<polygon points=\"";
    print_points_in(container_of_points);
    out << "\" stroke=\"" << strk << "\" fill=\"" << fll << "\"/>\n";
  };


/* Constructors
 */

template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
print_as_SVG<F,POINT,ANGLE,MAP>::print_as_SVG(ostream_type & o,
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
           typename ANGLE,
           template <typename,typename> typename MAP
         >
print_as_SVG<F,POINT,ANGLE,MAP>::print_as_SVG(ostream_type & o,
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
