#ifndef SPECIFIC_OSTREAM_CPP
#define SPECIFIC_OSTREAM_CPP


#ifndef SPECIFIC_OSTREAM_H
#include "specific_ostream.h"
#endif

// Implementation of members:
void LaTex_ostream::output_prefix() {
  os << "\\documentclass{" << doctype << "}\n";
  os << "\\begin{" << doctype << "}\n";;
};
void LaTex_ostream::output_postfix() {
  os << "\\end{" << doctype << "}\n";
};

#endif
