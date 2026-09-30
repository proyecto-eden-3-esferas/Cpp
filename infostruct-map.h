#ifndef INFOSTRUCT_MAP_H
#define INFOSTRUCT_MAP_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

/* We want to test separate compilation of large variables.
 * First, class/struct 'infostruct' is declared
   to hold information plus some metadata
 * Next a container of infostruct objects is declared
   with the extern keyword
   and meant to be defined in a separate-compilable file
 * TODO
 [ ] develop some class/struct metadata and
 [ ] include code from file "extract-UDC-facets.cpp"
 [ ] then test an instance of std::multimap<metadata,text>
 [ ] try reordering your multimap by some field of metadata's
 [ ] the same, but use std::unordered_multimap<> instead
 */

struct metadata {
  std::string author,
  int         date,
  std::string description
}

struct infostruct {
  std::string text;
  std::string metadata;
  infostruct() = default;
  infostruct(std::string_view t, std::string_view m="text") : text(t), metadata(m) {};
};

extern std::vector<infostruct> is0;



#endif
