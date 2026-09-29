#ifndef DIMTOKEN_H
#include "dimtoken.h"
#endif

#include <iostream>
#include <vector>

typedef float float_type;
typedef dimtoken<float_type, std::string> dimtoken_t;
typedef dimline<float_type, std::string> dimline_t;

typedef std::vector<dimtoken_t> dimtokens_t;
typedef std::vector<dimline_t>  dimlines_t;
const float_type max_width = 33.0;

/* The following functions takes a reference to a container of DIMTOKEN's,
 * that is, a container of objects satisfying the DIMTOKEN concept
 * as defined in the dimtoken compilation unit,
 * and adds them as lines not wider than a given maximum width (3rd parameter)
 */
template <template <DIMTOKEN T> typename TOKENS, // a container of DIMTOKEN's
                                typename LINES,  // a sequence container of dimlines<>
          typename F = double,
          DIMTOKEN T = dimtoken<F>
         >
void add_dimtokens_to_dimlines_with_max_width(const TOKENS<T>& tkns, LINES& dls, F mw) {
  dls.clear();
  dls.push_back(dimline_t(mw));
  int idx = 0;
  for(const auto & tkn : tkns) {
    if ( ! dls[idx].fits_token(tkn) ) {
      dls.push_back(dimline_t(mw));
      ++idx;
    }
    dls[idx].add_token(tkn);
  }
};

template <DIMTOKEN TKN>
void print(const TKN & tkn, std::ostream& o = std::cout) {
  o << "\"" << tkn.get_text() << '\"';
  o << " has width: "  << tkn.get_width();
  o << ", depth: "  << tkn.get_depth();
  o << ", and height: " << tkn.get_height() << '\n';
};


int main() {

  dimtoken_t dt0("Hello", 4.0);

  print<dimtoken_t>(dt0);

  dimline_t dl(max_width);

  /* Now test adding tokens to a dimline<> */

  dimtokens_t dts{
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0},
    {"Hello", 3.9},
    {"Kitty!", 5.0}
  };

  dimlines_t dls;

  add_dimtokens_to_dimlines_with_max_width(dts, dls, 33.0);

  /*
  dls.clear();
  dls.push_back(dimline_t(max_width));
  int idx = 0;
  for(const auto & tkn : dts) {
    if ( ! dls[idx].fits_token(tkn) ) {
      dls.push_back(dimline_t(max_width));
      ++idx;
    }
    dls[idx].add_token(tkn);
  }
  */
  std::cout << "Now \'dls\' holds " << dls.size() << " line(s).\n\n";



  return 0;
}
