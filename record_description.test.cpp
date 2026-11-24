/* Test compilation unit 'record_description' */

typedef signed int int_t;
typedef      float float_t;
typedef simple_record_description<int_t,float_t> simple_record_description_t;

simple_record_description_t srd0;


#ifndef RECORD_DESCRIPTION_H
#include "record_description.h"
#endif

#include <iostream>
using namespace std;

int main() {




  return 0;
}
