#ifndef REGISTERED_KEY_MAP_HEALTH_H
#define REGISTERED_KEY_MAP_HEALTH_H

#include <vector>

#ifndef REGISTERED_KEY_MAP_H
#include "registered_key_map.h"
#endif


typedef std::string key_type;
typedef std::string mapped_type;
typedef registered_key<    key_type>                        registered_key_t;
typedef registered_key_map<key_type, mapped_type, std::map> registered_key_map_t;


#ifdef SEPARATE_COMPILATION

// Declare/Define some initializer_list<string>'s for maps from string:
extern std::initializer_list<std::string> allowil, compDesc, compUDC;
extern registered_key_t regDesc, regUDC;
extern std::vector<registered_key_map_t> healthVector;

#else

  #ifndef REGISTERED_KEY_MAP_HEALTH_CPP
  #include "registered_key_map.health.cpp"
  #endif

#endif


#endif
