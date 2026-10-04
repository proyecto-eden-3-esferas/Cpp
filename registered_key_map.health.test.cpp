/* This file uses classes registered_key<KEY>, and registered_key_map<KEY,VAL,MAP>
   to develop a health database.
 * Health data items of class registered_key_map<STRING,STRING,MAP>
   could be held in a container that gets:
   - extern-declared in file "registered_key_map.health.h", and
   - defined in file "registered_key_map.health.cpp"
   (in a separate compilation scheme)
 *
 */

#include <iostream>

#ifndef REGISTERED_KEY_MAP_H
#include "registered_key_map.h"
#endif

#ifndef REGISTERED_KEY_MAP_HEALTH_H
#include "registered_key_map.health.h"
#endif

typedef std::string key_type;
typedef std::string mapped_type;
typedef registered_key<    key_type>                        registered_key_t;
typedef registered_key_map<key_type, mapped_type, std::map> registered_key_map_t;

// Define some initializer_list<string>'s for maps from string:
std::initializer_list<std::string> allowil = {"author", "date", "description", "UDC", "contents"};
std::initializer_list<std::string> compDesc = {                 "description",        "contents"};
std::initializer_list<std::string> compUDC  = {                                "UDC", "contents"};

registered_key_t regDesc{allowil, compDesc};
registered_key_t regUDC{ allowil, compUDC };

using namespace std;

int main (int argc, const char** argv) {


  cout << "Test a container of dataitems as objects of type registered_key_map<STRING,STRING,MAP>\n";
  cout << "(A scheme for separate compilation of large container objects is hinted.)\n";


  return 0;

}
