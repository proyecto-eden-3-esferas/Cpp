#ifndef XML_H
#include "XML.h"
#endif


#include <string>
#include <iostream>

using namespace std;


int main() {

  const string doctype1{"HTML"};
  const string    name1{"html"};

  XMLelement xmle0(name1);
  XMLelement xmleh("head", true,false);
  XMLelement xmleb("body", true,false);
  xmle0.add(&xmleh);
  xmle0.add(&xmleb);

  XMLelement xmles("section", true,false);
  xmleb.add(&xmles);

  XMLelement xmleh2("h2", true,true);
  xmles.add(&xmleh2);

  xmleb.attributes["lang"] = "es";

  xmle0.print(cout, Level(0));

  return 0; }
