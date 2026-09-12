#ifndef BOOSTLIKE_PRINT_AS_SVG_H
#define BOOSTLIKE_PRINT_AS_SVG_H

#include "boost-like.box.h"
#include "boost-like.labeled_block.h"

#include "XMLprint.h"

/*
 * TODO
 * [ ] print_as_SVG::void operator() (const labeled_block_type& lb);
 *     should print labels
 * [v] make void print_as_SVG<>::print_points_in(CONTAINER_OF_POINTS) protected
 * [?] move templatized member functions into implementation file
 */

template < typename     F = double,
           typename POINT = point<F, 2, boost::geometry::cs::cartesian>,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F>,
           template <typename,typename> typename  MAP=std::map
         >
class print_as_SVG : protected XMLprint<MAP> {
public:

  typedef           box<F, 2, boost::geometry::cs::cartesian, POINT> box_type;
  typedef         block<F,                                    POINT,INT,ANGLE> block_type;
  typedef labeled_block<F, INT, boost::geometry::cs::cartesian, POINT> labeled_block_type;
  //typedef labeled_block_type::

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
  void operator() (const block_type& b) {operator() (static_cast<const box_type &>(b));};
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
