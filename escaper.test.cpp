#include "escaper.h"

#include <iostream>
using namespace std;
typedef map_escaper<char>::pair_t pair_t;

int main() {


  map_escaper<char> json_escaper; // UNIMPLEMENTED
  sql_escaper<char> my_sql_escaper_0;
  map_escaper<char> my_sql_escaper_1{{'\'', "\'\'"}
                                 // ,{}, {}, {}, {}, {}, {}
                                    };
  xml_escaper<char> my_xml_escaper;

  //my_sql_escaper_0.ch_to_str.insert({'\'', R"('')"});

  cout << "To SQL: \"A\'ab\": "                                    << my_sql_escaper_0.escape(string(R"(A'ab)")) << endl;
  cout << "To SQL: \"A\'ab\": "                                    << my_sql_escaper_1.escape(string(R"(A'ab)")) << endl;

  cout << "To XML: \"A <em>momentous</em> \"decision\" & scheme: " << my_xml_escaper.escape(string(R"(A <em>momentous</em> "decision" & scheme)")) << endl;

  my_sql_escaper_0.insert(cout, string(R"(A'ab)"));
  cout << endl;


  return 0;
}
