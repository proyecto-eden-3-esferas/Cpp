#ifndef REGISTERED_KEY_MAP_HEALTH_CPP
#define REGISTERED_KEY_MAP_HEALTH_CPP

#ifndef REGISTERED_KEY_MAP_HEALTH_H
#include "registered_key_map.health.h"
#endif

// Define some initializer_list<string>'s for maps from string:
std::initializer_list<std::string> allowil  = {"author", "date", "description", "UDC", "contents"};
std::initializer_list<std::string> compDesc = {                  "description",        "contents"};
std::initializer_list<std::string> compUDC  = {                                 "UDC", "contents"};

registered_key_t regDesc{allowil, compDesc};
registered_key_t regUDC{ allowil, compUDC };


std::vector<registered_key_map_t> healthVector{
  {
    regDesc,
    { {"description", "DESCRIPTION"}, {"contents", "CONTENTS"}}
  },
  {
    regDesc,
    { {"description", "DESCRIPTION"}, {"contents", "CONTENTS"}}
  },
  {
    regDesc,
    { {"description", "DESCRIPTION"}, {"contents", "CONTENTS"}}
  },
  {
    regDesc,
    { {"description", "DESCRIPTION"}, {"contents", "CONTENTS"}}
  }
};



#endif
