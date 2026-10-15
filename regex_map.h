#ifndef REGEX_MAP_H
#define REGEX_MAP_H

/* Class regex_map holds/inherits a map from regex names to regex objects
 * Classes may be compiled separately as regex code takes so long to compile
 * TODO
 * [ ] Add entries in Makefile for ordinary build and for separate compilation build
 * [=] Develop scheme for separate compilation of useful such objects
 * [x] Rename to regex_map
 * [ ] Implement members
 * [ ] Settle for a regex type
 * [ ] Write a test that asks user to
 */

#include <map>
#include <regex>
#include <string>
#include <string_view>

template <template <typename K, typename M> typename MAP = std::map>
class regex_map : public MAP<std::string, std::regex> {
public:
  typedef std::string string_t;
  typedef std::string_view string_view_t;
  typedef std::regex regex_t;
  typedef MAP<std::string, std::regex> map_t;
  using map_t::MAP;
  using map_t::emplace, map_t::operator[], map_t::at, map_t::contains;
  using map_t::size, map_t::empty, map_t::clear;
  using map_t::begin,  map_t::end;
  using map_t::cbegin, map_t::cend;
  //
  //virtual void emplace(std::string_view s, std::string_view s);
  bool matches(string_view_t str, string_view_t regex_name) const;


};


#ifndef REGEX_MAP_CPP
  #ifndef SEPARATE_COMPILATION
    #include "regex_map.cpp"
  #endif
#endif

# endif
