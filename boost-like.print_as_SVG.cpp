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
  open_opening_tag("a");
  add_attribute("href", page);
  close_opening_tag();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::open_hyperlink(const string_type& page, const string_type& fragment) {
  open_opening_tag("a");
  out << " href=\"" << page << '#' << fragment << '\"';
  close_opening_tag();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::open_locallink(const string_type& fragment) {
  open_opening_tag("a");
  out << " href=\"#" << fragment << '\"';
  close_opening_tag();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::close_link() {
  close_element();
};



template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const box_type& b) {
  open_opening_tag("rect");
  out << " x=\"" << b.min_corner(). template get<0>() << "\"";
  out << " y=\"" << b.min_corner(). template get<1>() << "\"";
  add_attribute("width",  std::to_string(b.width()));
  add_attribute("height", std::to_string(b.height()));
  //out << " style=\"fill:white; stroke:black; stroke-width: 2; fill-opacity: 0.3; stroke-opacity: 0.9\"";
  close_standalone_tag();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const box_type& b, const string_type& id) {
  open_opening_tag("rect");
  out << " x=\"" << b.min_corner(). template get<0>() << "\"";
  out << " y=\"" << b.min_corner(). template get<1>() << "\"";
  add_attribute("width",  std::to_string(b.width()));
  add_attribute("height", std::to_string(b.height()));
  add_attribute("id", id);
  //out << " style=\"fill:white; stroke:black; stroke-width: 2; fill-opacity: 0.3; stroke-opacity: 0.9\"";
  close_standalone_tag();
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const block_type& b) {
  operator() (static_cast<const box_type &>(b));
};
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const block_type& b, const string_type& id) {
  operator() (static_cast<const box_type &>(b), id);
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
  open_opening_tag("text");
  out << " text-anchor=\"";
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
  out << ") rotate(" << deg.get() << " 0, 0) scale(1, -1)\">";
  out << label;
  close_element();
  // out << '\n';
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
      //indent(); std::cout << "<!-- index " << idx << " is rightside -->\n";
      break;
    case side::topside:
      print_label_on_block_at_port(label, blk, idx, dx*top_dx_k,  dy, text_anchor::start, degree_type(vertical_label_angle) );
      //indent(); std::cout << "<!-- index " << idx << " is topside -->\n";
      break;
    case side::leftside:
      print_label_on_block_at_port(label, blk, idx, -dx,          dy, text_anchor::end,   degree_type(0.0) );
      //indent(); std::cout << "<!-- index " << idx << " is leftside -->\n";
      break;
    case side::bottomside:
      print_label_on_block_at_port(label, blk, idx, -dx*bot_dx_k, dy, text_anchor::end,   degree_type(vertical_label_angle) );
      //indent(); std::cout << "<!-- index " << idx << " is bottomside -->\n";
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
template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
void print_as_SVG<F,POINT,ANGLE,MAP>::operator() (const labeled_block_type& lb,
                                                  const string_type& id )
{
  this->operator() (lb,id);
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
    open_opening_tag("polyline");
    out << " points=\"";
    print_points_in(container_of_points);
    out << '\"';
    add_attribute("stroke", strk);
    add_attribute("fill", fll);
    close_standalone_tag();
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
    open_opening_tag("polygon");
    out << " points=\"";
    print_points_in(container_of_points);
    add_attribute("stroke", strk);
    add_attribute("fill", fll);
    close_standalone_tag();
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
  open_opening_tag("svg");
  add_attribute("xmlns", "http://www.w3.org/2000/svg");
  add_attribute("width",  std::to_string(width)  );
  add_attribute("height", std::to_string(height) );
  add_style(style);
  close_opening_tag();
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
  open_opening_tag("svg");
  add_attribute("xmlns", "http://www.w3.org/2000/svg");
  add_attribute("width",  std::to_string(width)  );
  add_attribute("height", std::to_string(height) );
  add_style(sty);
  close_opening_tag();
};


#endif
