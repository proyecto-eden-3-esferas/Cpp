/* File "jq.test.cpp"
 */

#ifndef JQ_H
#include "jq.h"
#endif




using namespace std;

int main (int argc, const char** argv) {

  for(int i=0; i < argc; ++i) {
    std::cout << i << "th command line argument is: \"" << argv[i] << "\"\n";
  }
  if(argc < 3) {
    std::cout << "USAGE: <FILE.json> <field>\n";
    return 0;
  }


  jq jq0(argv[1]);

  cout << "GENERATED COMMAND IS: " << jq0.map("term") << '\n';

  cout << "GENERATED COMMAND IS: " << jq0.pretty() << '\n';

  return 0;

}
