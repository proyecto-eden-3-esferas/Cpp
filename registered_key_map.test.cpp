/* File "registered_key_map.test.cpp"
   tests classes registered_key<KEY>, and registered_key_map<KEY,VAL,MAP>
 */

#include <iostream>

#ifndef REGISTERED_KEY_MAP_H
#include "registered_key_map.h"
#endif

using namespace std;

typedef std::string key_type;
typedef std::string mapped_type;
typedef registered_key<    key_type>                        registered_key_t;
typedef registered_key_map<key_type, mapped_type, std::map> registered_key_map_t;

// Define some initializer_list<string>'s for maps from string:
std::initializer_list<std::string> allowil = {"author", "date", "description"};
std::initializer_list<std::string> compuil = {                  "description"};

registered_key_t reg0{allowil, compuil};

registered_key_map_t info0{reg0, {{"date","1966"}, {"description", "momentous event"}}};
registered_key_map_t info1(reg0, {                 {"description", "composer"}});

int main (int argc, const char** argv) {

  info1["author"] = "Coltrane";
  cout << "info1.author=" << info1[ "author"] << '\n';
  cout << "info1.author=" << info1[ "author"] << '\n';
  cout << "info0.description=" << info0[ "description"] << '\n';

  // cout << "info1.date="   << info1.at("date") << '\n'; // no such key


  // Use an unregistered key to elicit an out_of_range exception:
  // info1["genre"]  = "composition";                     // "genre" not allowed

  info1["date"] = "1966";

  cout << "\nNow copy \'info1\' to so far empty \'info0\' and query for \"author\":\n";
  info0 = info1;
  cout << "info0.author=" << info0[ "author"] << '\n';

  cout << '\n';


  return 0;

}
