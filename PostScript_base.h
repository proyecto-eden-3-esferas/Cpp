#ifndef POSTSCRIPT_BASE_H
#define POSTSCRIPT_BASE_H

/* File PostScript_base has no file member variable
 */

#include <iostream>
#include <map>
#include <set>
#include <string>


template <typename CHAR = char, typename F = double>
class PostScript_base {
public:
  typedef std::basic_string<  CHAR>   string_t;
  typedef std::map<string_t,string_t> dictionary_t;
  static dictionary_t procedures;
};

// Implementations:

template <typename CHAR, typename F>
PostScript_base<CHAR,F>::dictionary_t PostScript_base<CHAR,F>::procedures{
  /*
  {"", ""},
  {"", ""},
  {"", ""},
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

#endif
