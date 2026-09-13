#ifndef BOOSTLIKE_PRINT_AS_SVG_H
#define BOOSTLIKE_PRINT_AS_SVG_H

#include "boost-like.box.h"
#include "boost-like.labeled_block.h"

#include "XMLprint.h"

/* Class print_as_SVG<> is in charge of printing [all] SVG objects
 * It is assumed that the angle class is Degree<FLOAT>
 * as SVG takes sexagesimal degrees as angle units.
 * TODO
 * [ ] draw up a scheme for including id attributes into graphic elements
       such as box, block, labeled_block,
       as well as prospective circle, diamond, polygon
   [ ] void open_hyperlink(const string_type& page), and
       void open_hyperlink(const string_type& page, const string_type& fragment)
       should  include a 'target' attribute in the opening tag, my.
   [ ] print_internal_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY)
       has not been implemented yet.
       It should be easy to implement
       by analogy with the body of already working 'print_external_label_on_block_at_port(...)'

   [v] Remove double indenting
         indent();
         indent();
       in member print_label(...)
   [ ] print_as_SVG::void operator() (const labeled_block_type& lb);
       should be implemented as
       (1) print(static_cast<BLOCK>(lb)), then
       (2) calling
           - print_internal_label_on_block_at_port(), and
           - print_external_label_on_block_at_port()
           on each of its (lb's) ports
   [v] make void print_as_SVG<>::print_points_in(CONTAINER_OF_POINTS) protected
   [ ] Write fitting entries in file Makefile
   [v] Implement SVG hyperlinks
 *
 */

template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename ANGLE = Degree<F>,
           template <typename,typename> typename  MAP=std::map
         >
class print_as_SVG : protected XMLprint<MAP> {
public:

  typedef POINT point_type;
  typedef           box<F, 2, boost::geometry::cs::cartesian, point_type> box_type;
  typedef         block<F,                                    point_type,ANGLE> block_type;
  typedef labeled_block<F,    boost::geometry::cs::cartesian, point_type> labeled_block_type;
  //typedef labeled_block_type::
  typedef block_type::side side; // an enum class: topside, leftside, bottomside, rightside

  typedef unsigned int index_type;
  typedef Degree<F>   degree_type;

  typedef XMLprint<MAP> XMLprint_type;
  using                 XMLprint_type::out;
  using                 XMLprint_type::stack_of_names;
  using        typename XMLprint_type::ostream_type;
  using        typename XMLprint_type::string_type;
  using        typename XMLprint_type::string_map_type;
  using                 XMLprint_type::open_opening_tag;
  using                 XMLprint_type::close_opening_tag;
  using                 XMLprint_type::close_standalone_tag;
  using                 XMLprint_type::close_element;
  using                 XMLprint_type::add_style;

public:
  /* The Level<SINT> interface
     is good for indenting code */
  Level<unsigned int> level;
  void go_in()  {++level;};
  void go_out() {--level;};
  void indent() {level.print(out);};

  /* Angle to the X axis to print a label on a vertical port:
   * and correction factors
   * for printing labels on top (top_dx_k) and bottom (bot_dx_k) side of a block.
   * They depend heavily on 'vertical_label_angle'
   * Therefore, if 'vertical_label_angle' is changed (to 90 or very close, say)
   * the value of 'top_dx_k' and 'bot_dx_k' should be made (near to) 1
   * ideally through a member like 'set_vertical_label_angle_to()'
   */
  F vertical_label_angle = 45;
  F top_dx_k{0.0};
  F bot_dx_k{2.0};
  // Width and height of the SVG element containing all shapes:
  F width, height;

  virtual void make_vertical_label_angle_steeper();

  string_map_type style{
    {"fill", "white"},
    {"stroke", "black"},
    {"stroke-width", "2"},
    {"fill-opacity", "0.3"},
    {"stroke-opacity", "0.9"},
    {"transform", "scale(1,-1)"} // invert around the X axis
  };

  void open_hyperlink(const string_type& page);
  void open_hyperlink(const string_type& page, const string_type& fragment);
  void open_locallink(const string_type& fragment);
  void close_link();

  void operator() (const box_type& b);
  enum class text_anchor {start, middle, end};
  void operator() (const block_type& b) {operator() (static_cast<const box_type &>(b));};

  /* Printing elements with labels, such as labeled_block<>
     relies on helper function:
       void print_label(POINT... LABEL ...);
     eventually to be declared protected
   * Also, print_label_on_block_at_port(LABEL,BLOCK,INDEX)
     is useful for defining virtual members:
     - print_external_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY), and
     - print_internal_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY)
     where anchor and tilt are worked out inside their bodies.
   * print_internal_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY), and
     print_external_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY)
     make it very straightforward to implement
     a member function printing a labeled_block<>'s shape and labels.
   */
  void print_label(
    const point_type & pt,
    const string_type & label,
    F dx = 0.0, F dy = 0.0, // X and Y displacements
    text_anchor anchor = text_anchor::start,
    degree_type deg = 0
  );
  void print_label_on_block_at_port(
    const string_type & label,
    const  block_type &   blk,
           index_type     idx,
    F dx = 0.0, F dy = 0.0, // X and Y displacements
    text_anchor anchor = text_anchor::start,
    degree_type deg = 0
  );
  virtual void print_external_label_on_block_at_port(const string_type & label,
    const  block_type &   blk,
           index_type     idx,
    F dx = 0.0, F dy = 0.0);
  virtual void print_internal_label_on_block_at_port(const string_type & label,
    const  block_type &   blk,
           index_type     idx,
    F dx = 0.0, F dy = 0.0);
  void operator() (const labeled_block_type& lb);

  /* Members for printing a sequence of points
     rely on print_points_in(CONTAINER_OF_POINTS)
     and print the sequence either as a polyline or a polygon
   */
protected:
  template <typename CONTAINER_OF_POINTS>
  void print_points_in(const CONTAINER_OF_POINTS & container_of_points);
public:
  template <typename CONTAINER_OF_POINTS>
  void print_as_polyline(const CONTAINER_OF_POINTS & container_of_points,
                         const string_type& strk="black",
                         const string_type& fll="none");
  template <typename CONTAINER_OF_POINTS>
  void print_as_polygon( const CONTAINER_OF_POINTS & container_of_points,
                         const string_type& strk="black",
                         const string_type& fll="none");

  // Constructors:
  print_as_SVG(ostream_type & o,                              F w=500.0, F h=500.0);
  print_as_SVG(ostream_type & o, const string_map_type & sty, F w=500.0, F h=500.0);
};

// Implementation of template member functions:

template < typename     F,
           typename POINT,
           typename ANGLE,
           template <typename,typename> typename MAP
         >
template <typename CONTAINER_OF_POINTS>
void print_as_SVG<F,POINT,ANGLE,MAP>::print_points_in(const CONTAINER_OF_POINTS & container_of_points) {
  bool first = true;
  for(const auto & pt : container_of_points) {
    if(first)
      first = false;
    else
      out << ' ';
    pt.print(out, ",");
  }
};



#ifndef SEPARATE_COMPILATION
  #ifndef BOOSTLIKE_PRINT_AS_SVG_CPP
    #include "boost-like.print_as_SVG.cpp"
  #endif
#endif

#endif
