#ifndef REGISTERED_KEY_MAP_HEALTH_CPP
#define REGISTERED_KEY_MAP_HEALTH_CPP

#ifndef REGISTERED_KEY_MAP_HEALTH_H
#include "registered_key_map.health.h"
#endif

// Define some initializer_list<string>'s for maps from string:
std::initializer_list<std::string> allowil  =
  {"author", "term", "source", "date", "description", "UDC", "contents"};
std::initializer_list<std::string> compDesc =
  {                                    "description"                   };
std::initializer_list<std::string> compUDC  = {       "UDC", "contents"};

registered_key_t regDesc{allowil, compDesc};
registered_key_t regUDC{ allowil, compUDC };


std::vector<registered_key_map_t> healthVector{
  {
    regDesc,
    { {"term", "osteopathy"},
      {"source", "Britannica"},
      {"description", "health care profession that emphasizes the relationship between the musculoskeletal structure and organ function"},
      {"contents", "Osteopathic physicians develop skill in recognizing and correcting structural problems through manipulative therapy and other treatments."},
      {"discussion", "Osteopathic research studies include anatomy and function of nerve-and-muscle junctions, transmission of nervous impulses, somatic reflex functions, renal (kidney) growth and function, and blood-flow dynamics. There are also clinical studies of structural findings in hospitalized patients, the effects of manipulation under anesthesia for specific orthopedic problems, the effect of osteopathic manipulation on hypertension, and management of chronic obstructive lung disease by regular medical means, with and without osteopathic manipulation."}
    }
  },
  {
    regDesc,
    { {"term", "calisthenics"}, {"description", ""}}
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
