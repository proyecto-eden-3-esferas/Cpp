#ifndef POSTSCRIPT_FILE_CPP
#define POSTSCRIPT_FILE_CPP

#ifndef POSTSCRIPT_FILE_H
#include "PostScriptFile.h"
#endif


// Implementations

template <typename CHAR, typename F>
void PostScriptFile<CHAR,F>::define_procedure(const string_t& name) {
  if(procedures.contains(name)) {
    if(!defined_procedures.contains(name)) {
      ofs << '\n' << '/' << name << " {\n" << procedures[name] << "\n} def\n";
      defined_procedures.insert(name);
    } else
      std::cout << "PROCEDURE " << name << " HAS ALREADY BEEN DEFINED!!!\n";
  } else
    std::cout << "PROCEDURE " << name << " IS NOT FOUND IN MEMBER VARIABLE procedures!!!\n";
};

template <typename CHAR, typename F>
void PostScriptFile<CHAR,F>::print_bb(pos_type pos) {
  ofs.seekp(pos);
  ofs << "%%BoundingBox: " << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
};

// constructors and destructor

template <typename CHAR, typename F>
void PostScriptFile<CHAR,F>::set_margins() {
  ofs << "/lm " << xmin + margin << " def\n";
  ofs << "/rm " << xmax - margin << " def\n";
  ofs << "/tm " << ymax - margin << " def\n";
  ofs << "/bm " << ymin + margin << " def\n";
};

template <typename CHAR, typename F>
PostScriptFile<CHAR,F>::PostScriptFile(const string_t& filename, margin_t m)
: ofs(filename), xmin(0), xmax(595), ymin(0), ymax(842), margin(m) {
  ofs << "%!PS-Adobe-2.0" << '\n';
  print_bb(ofs.tellp());
  ofs << "%%Pages: 1" << '\n';
  ofs << "%%Encoding: UTF-8" << '\n';
  ofs << "%%EndComments\n\n";
  set_margins();
};
template <typename CHAR, typename F>
PostScriptFile<CHAR,F>::~PostScriptFile() {
  ofs << "\n\nshowpage";
  ofs.close();
};

#endif
