#ifndef POSTSCRIPT_BASE_H
#define POSTSCRIPT_BASE_H

/* File PostScript_base has no file member variable
 * TODO
   [ ] default constructor doesn't get compiled,
       something to do with std::begin() and std::end() in statement:
      "DependencyManager_t::insert( std::begin(dependencies), std::end(dependencies));"
   [ ] add a DependencyManager<> member variable and some code around it
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

#ifndef DEPENDENCY_MANAGER_H
#include "DependencyManager.h"
#endif

template <typename CHAR = char, typename F = double>
class PostScript_base : public DependencyManager<std::basic_string<CHAR>, std::list> {
public:
  typedef std::basic_string<  CHAR>   string_t;
  typedef std::map<string_t,string_t> dictionary_t;
  typedef std::basic_ostream<CHAR> ostream_t;
  typedef DependencyManager<string_t, std::list> DependencyManager_t;
  //typedef typename DependencyManager_t::value_type dependency_type;
  typedef std::pair<string_t, std::list<string_t> > dependency_type;

  dictionary_t procedures;        // maps procedure names to procedure bodies
  //static dependency_type dependencies[];

  // Member functions to do with 'dependencies':
  void execute_on_backtracking(ostream_t& o, const string_t& name) override;
  void define_procedure(ostream_t& o, const string_t& name);
  void insert_dependency(const dependency_type& d);
  template <typename ITER>
  void insert_dependencies(ITER first, ITER last)  {DependencyManager_t::insert(first,last);};
  template <typename ITER>
  void insert_procedures(ITER first, ITER last)  {          procedures.insert(first,last);};

  /* Members for handling paths */
  void open_path(ostream_t& o, F x=0, F y=0) {o << "newpath\n  " << x << ' ' << y << " moveto\n";};
  void   fill(  ostream_t& o)       {o << "gsave\n  fill\ngrestore\n";};
  void   fill(  ostream_t& o, F gr) {o << "gsave\n  " << gr << " setgray\n  fill\ngrestore\n";};
  void   fill_close(ostream_t& o)   {o << "fill\n";};   // erases current path
  void stroke(ostream_t& o)         {o << "gsave\n  stroke\ngrestore\n";};
  void stroke(ostream_t& o, F lw)   {o << "gsave\n  " << lw << " setlinewidth\n  stroke\ngrestore\n";};
  void stroke_close(ostream_t& o)   {o << "stroke\n";}; // erases current path
  void  close_path( ostream_t& o)   {o << "closepath\n";}; // draw a line from current point to first
  /* Member variables for handling text */
  void set_font(ostream_t& o, const string_t& name, F scale);
  PostScript_base();
};

/* Initialization of static Member Variables.
 * These member variables will not be compiled into an object file.
 * Therefore they are found in this/a header file.
 */

/* Two arrays used for standard construction:
 * 'global_dependencies' and 'global_procedures'
 * They should be enlarged jointly:
 * whenever a procedure is added, its dependencies should be added, too.
 * Some more pairs of dependencies-procedures arrays could be defined,
 * then inserted...
 */

std::pair<std::string, std::list<std::string> > global_dependencies [] = {
  // { "", {"", ""} },
  { "showpar", {"newline", "rm"} },
  { "lead", {"leadk"} },
  { "newline", {"lead", "bm", "lm", "turnpage"} },
  { "movetostart", {"lm", "tm"} },
  { "turnpage", {"movetostart", "lead"} }
};

std::pair<std::string, std::string> global_procedures [] = {
  /*
  {"", ""},
  {"", ""},
  {"showpage", "show"},
  */
  {"movetostart", "lm tm moveto"},
  {"fontscale", "12"},
  {"turnpage", "showpage\n\
movetostart\n\
0 lead neg rmoveto % account for font height"},
  {"leadk", "1"},
  {"lead", "fontscale leadk mul"},
  {"newline", "0 lead neg rmoveto\n\
currentpoint\n\
dup bm lt {pop pop turnpage}\n\
          {exch pop lm exch moveto}\n\
          ifelse"
  },
  {"showpar", "  ( )\n\
  {\n\
    search\n\
    {\n\
      dup stringwidth pop currentpoint pop add rm gt {newline} if\n\
      show ( ) show\n\
    }\n\
    {\n\
      dup stringwidth pop currentpoint pop add rm gt {newline} if\n\
      show\n\
      exit\n\
    }\n\
    ifelse\n\
  } loop"}
};

#ifndef SEPARATE_COMPILATION
#include "PostScript_base.cpp"
#endif


#endif
