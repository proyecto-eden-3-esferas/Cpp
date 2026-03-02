#ifndef JSON_PARSER_H
#include "JSONParser.h"
#endif

/*
#ifndef JSON_H
#include "json.h"
#endif
using namespace j;
*/

typedef JSONParser<> JSONParser_t;

using namespace std;


int main() {

  std::ifstream sayings("../../JSON_files/sayings.array.json");

  JSONParser_t jsonp0(sayings);
  cout << "\n\"result_string\" has length: " << jsonp0.result_string.length() << " byte(s).\n";
  jsonp0.run();

  cout << "\nNow \"result_string\" has length: " << jsonp0.result_string.length() << " byte(s).\n";

  sayings.close();

  return 0;

}
