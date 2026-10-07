/* This file uses classes registered_key<KEY>, and registered_key_map<KEY,VAL,MAP>
   to develop a health database.
 * Health data items of class registered_key_map<STRING,STRING,MAP>
   could be held in a container that gets:
   - extern-declared in file "registered_key_map.health.h", and
   - defined in file "registered_key_map.health.cpp"
   (in a separate compilation scheme)
 * UDC noteworthy classes:
   50 Generalities about the Pure Sciences
   51 Mathematics
   52 Astronomy. Astrophysics. Space Research Geodesy
   53 Physics
   54 Chemistry. Mineralogical Sciences
   55 Earth Science. Geology Mineralogy, etc.
   56 Palaeontology
   57 Biological Sciences in General
   58 Botany
   59 Zoology
 * TODO
   [ ] implement separate compilation (currently I am getting linking errors)
 */

#include <iostream>

#ifndef REGISTERED_KEY_MAP_H
#include "registered_key_map.h"
#endif

#ifndef REGISTERED_KEY_MAP_HEALTH_H
#include "registered_key_map.health.h"
#endif


using namespace std;

int main (int argc, const char** argv) {


  cout << "Test a container of dataitems as objects of type registered_key_map<STRING,STRING,MAP>\n";
  cout << "(A scheme for separate compilation of large container objects is hinted.)\n";

  cout << "healthVector has " << healthVector.size() << " element(s)\n";

  return 0;

}
