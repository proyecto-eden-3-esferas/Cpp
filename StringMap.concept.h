#ifndef STRINGMAP_CONCEPT_H
#define STRINGMAP_CONCEPT_H

#include <map>
#include <string>

template <typename SM>
concept StringMap = requires (SM stringmap, std::string key1, std::string key2, std::string mapped) {
  {stringmap[key1]} -> std::convertible_to<std::string>;
  stringmap.insert(std::make_pair(key2,mapped));
};
#endif
