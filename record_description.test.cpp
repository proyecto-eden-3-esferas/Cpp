/* Test compilation unit 'record_description' */



#ifndef RECORD_DESCRIPTION_H
#include "record_description.h"
#endif

typedef signed int int_t;
typedef      float float_t;
typedef simple_record_description<int_t,float_t> simple_record_description_t;

simple_record_description_t srd0;
typedef typename simple_record_description_t::extractor_visitor simple_extractor_visitor;

#include <iostream>
using namespace std;

int main() {

  /* Define a visitor to print a simple_record_description::variant_t.
   * Then print it.
   */
  simple_extractor_visitor sev0;
  simple_record_description_t::variant_t sv0("Hello!");

  std::visit(sev0, sv0);


  return 0;
}
