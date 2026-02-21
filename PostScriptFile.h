#ifndef POSTSCRIPT_FILE_H
#define POSTSCRIPT_FILE_H

/* class PostScriptFile
 * A EPS version is be realized as a child
 * TODO
   [ ] complete initialization of 'procedures';
   [ ] write define_all_procedures()
   [ ] make 'define_procedure(TOKEN)' define TOKEN's dependencies first.
       to this end, DependencyManager<> is being developed
   [ ] 'bm' and 'lm' should equal 'margin'.
       Specifically, the origin is in the bottom-left hand corner.
   [ ]
 */

#ifndef POSTSCRIPT_BASE_H
#include "PostScript_base.h"
#endif

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

template <typename CHAR = char, typename F = double>
class PostScriptFile : public PostScript_base<CHAR,F> {
public:
  typedef PostScript_base<CHAR,F> PostScript_base_t;
  using PostScript_base_t::procedures;
  typedef std::basic_ofstream<CHAR> ofstream_t;
  typedef std::basic_ofstream<CHAR>::pos_type pos_type;
  typedef std::basic_string<  CHAR>   string_t;
  typedef std::size_t margin_t;
  enum class paper_size {A4, undecided};
  // Member variables:
  margin_t xmin, xmax, ymin, ymax, margin{33};
  mutable std::set<string_t> defined_procedures;
  //
  ofstream_t ofs;
  // Member functions:
  void define_procedure(const string_t& name);
  /* Members for handling the bounding box.
   * In an ordinary PostScript file, you define the bb in the Prolog.
   * In an Embedded PostScript file (EPS)
   * you keep track of how far left, right, top and bottom you have printed marks
   * then before closing the associated file (within the destructor)
   * you move the file cursor back to where the information belongs,
   * and print updated 'xmin', 'ymin', 'xmax' and 'ymax'
   */

  virtual void print_bb(pos_type pos);
  void set_margins();
  // constructors and virtual destructor:
//PostScriptFile(const string_t& filename, paper_size psz);
  PostScriptFile(const string_t& filename, margin_t m = 33);
  ~PostScriptFile();
};

#ifndef SEPARATE_COMPILATION
#include "PostScriptFile.cpp"
#endif

#endif
