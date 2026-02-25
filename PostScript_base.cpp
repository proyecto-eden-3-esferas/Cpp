#ifndef POSTSCRIPT_BASE_CPP
#define POSTSCRIPT_BASE_CPP

#ifndef POSTSCRIPT_BASE_H
#include "PostScript_base.h"
#endif


// Implementation of member functions to do with 'dependencies':

template <typename CHAR, typename F>
void PostScript_base<CHAR,F>::execute_on_backtracking(ostream_t& o, const string_t& name) {
  o << '\n' << '/' << name << " {\n" << procedures[name] << "\n} def\n";
};
template <typename CHAR, typename F>
void PostScript_base<CHAR,F>::define_procedure(ostream_t& o, const string_t& name) {
  reset_and_satisfy(o, name);
};
template <typename CHAR, typename F>
void PostScript_base<CHAR,F>::insert_dependency(const dependency_type& d) {
  DependencyManager_t::insert(d);
};

/*
template <typename CHAR, typename F>
void PostScript_base<CHAR,F>::
*/

// Implementation of member functions to do with text:

template <typename CHAR, typename F>
void PostScript_base<CHAR,F>::set_font(ostream_t& o, const string_t& name, F scale) {
  o << '/' <<  name << " findfont\n";
  o        << scale << " scalefont\n";
  o                 << "setfont\n";
};

/* Implementation of Constructors and Destructor:
 * Procedures and their dependencies are inserted into their matching members.
 * You can enlarge or erase global arrays 'global_dependencies' and 'global_dependencies'
 * as you see fitting.
 */

template <typename CHAR, typename F>
PostScript_base<CHAR,F>::PostScript_base()
{
  insert_dependencies( std::begin(::global_dependencies), std::end(::global_dependencies) );
  insert_procedures(   std::begin(::global_procedures),   std::end(::global_procedures) );
};


#endif
