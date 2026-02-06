#include "XML.h"

#include <iostream>
#include <string>

typedef XMLText<>    text_t;
typedef XMLComment<> comment_t;
typedef XMLCDATA<>   cdata_t;
//typedef XMLText<Level<signed int>> text_t;

using namespace std;

int main() {

  text_t t0("My favourite entity is <HTML>.");
  t0.print(cout, Level(0));

  cout << '\n' << '\n';

  comment_t c0("Not to be ignored.");
  c0.print(cout, Level(0));

  cout << '\n' << '\n';

  cdata_t d0("int i;\n\
if(i > 0)\n\
  std::cout << \"\'i\' initialized to positive number!\"\n");
  d0.print(cout, Level(0));

  cout << '\n' << '\n';

  return 0;
}
