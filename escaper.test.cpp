#include "escaper.h"

#include <iostream>
using namespace std;
typedef backslasher<char>::pair_t pair_t;

int main() {


  backslasher<char> json_escaper; // UNIMPLEMENTED
  xml_escaper<char> my_xml_escaper;
  sql_escaper<char> my_sql_escaper;

  //my_sql_escaper.ch_to_str.insert({'\'', R"('')"});

  cout << "To SQL: \"A\'ab\": "                                    << my_sql_escaper(string(R"(A'ab)")) << endl;

  cout << "To XML: \"A <em>momentous</em> \"decision\" & scheme: " << my_xml_escaper(string(R"(A <em>momentous</em> "decision" & scheme)")) << endl;


  return 0;
}
