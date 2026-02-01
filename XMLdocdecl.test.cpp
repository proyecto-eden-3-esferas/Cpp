#ifndef XMLDOCDECL_H
#include "XMLdocdecl.h"
#endif

#ifndef XMLDOCDECL_CPP
#include "XMLdocdecl.cpp"
#endif

XMLdocdecl<std::map> xmldoc0("life");
XMLdocdecl<std::map> xmldoc1("catalog",
{
  {"nbsp",  "#160"},
  {"ndash",  "#8211"},
  {"mdash",  "#8212"},
  {"deg",  "#176"}
});

using namespace std;

int main() {

  cout << "\nxmldoc0.print():\n";
  xmldoc0.print(std::cout);

  cout << "\nxmldoc1.print():\n";
  xmldoc1.print(std::cout);

  return 0;
}
