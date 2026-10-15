#ifndef REGEX_MAP_CPP
#define REGEX_MAP_CPP

#ifndef REGEX_MAP_H
#include "regex_map.h"
#endif

template <template <typename K, typename M> typename MAP>
bool regex_map<MAP>::matches(string_view_t str, string_view_t regex_name) const {
  return std::regex_match(str, at(regex_name));
};
/*
template <template <typename K, typename M> typename MAP>
void regex_map<MAP>:: {
};
template <template <typename K, typename M> typename MAP>
void regex_map<MAP>:: {
};
*/

#endif
