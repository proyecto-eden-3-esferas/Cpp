#ifndef BOOSTLIKE_PRINT_AS_SVG_H
#define BOOSTLIKE_PRINT_AS_SVG_H

#include "boost-like.box.h"
#include "boost-like.labeled_block.h"

#include "XMLprint.h"

/* Extremely ambitious class print_as_SVG<>
 * TODO
   [ ] print_external_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY), and
       print_internal_label_on_block_at_port(LABEL,BLOCK,INDEX,DX,DY)
       have not yet been implemented
   [ ] print_as_SVG::void operator() (const labeled_block_type& lb);
       should be implemented as
       (1) print(static_cast<BLOCK>(lb)), then
       (2) calling print_internal_label_on_block_at_port() and
           print_external_label_on_block_at_port()
           on each of its (lb's) ports
   [v] make void print_as_SVG<>::print_points_in(CONTAINER_OF_POINTS) protected
   [?] is it OK to move templatized member functions into implementation file?
   [ ] Write entries in file Makefile
   [ ] Implement SVG hyperlinks
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
  using block_type::side; // an enum class: topside, leftside, bottomside, rightside

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

  // angle to the X axis
  // at which a label on a vertical port is to be printed:
  F vertical_label_angle = 45;
  // Width and height of the SVG element containing all shapes:
  F width, height;
  string_map_type style{
    {"fill", "white"},
    {"stroke", "black"},
    {"stroke-width", "2"},
    {"fill-opacity", "0.3"},
    {"stroke-opacity", "0.9"},
    {"transform", "scale(1,-1)"} // invert around the X axis
  };

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
  print_as_SVG(ostream_type & o,                              F w=100.0, F h=100.0);
  print_as_SVG(ostream_type & o, const string_map_type & sty, F w=100.0, F h=100.0);
};


#ifndef SEPARATE_COMPILATION
  #ifndef BOOSTLIKE_PRINT_AS_SVG_CPP
    #include "boost-like.print_as_SVG.cpp"
  #endif
#endif

#endif
