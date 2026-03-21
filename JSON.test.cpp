/* File "JSON.test.cpp"
 * Simple JSON Representation:
 */

#ifndef JSON_H
#include "JSON.h"
#endif

#ifndef JSON_PRINTER_H
#include "JSON.printer.h"
#endif


typedef JSONarray<> JSONarray_t;
typedef   JSONobj<>   JSONobj_t;
typedef JSONprinter<> JSONprinter_t;

using namespace std;

int main () {

  JSONarray_t ja0;
  ja0.push_back("synergy");
  ja0.push_back(true);
  ja0.push_back(101);

  JSONarray_t ja1;
  ja1.push_back(1);
  ja1.push_back(2.0);

  JSONobj_t jo0;
  ja1.push_back(jo0);

  ja1.push_back("free");
  ja1.push_back(false);

  ja0.push_back(ja1);


  // Test JSONprinter on JSONarray:

  // std::visit(JSONprinter_t(cout), ja0);

  for(const auto & i : ja0.array)
    std::visit(JSONprinter_t(cout,1), i);



  // jo0.print();

  return 0;

}
