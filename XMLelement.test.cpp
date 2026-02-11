#ifndef XMLELEMENT_H
#include "XMLelement.h"
#endif


#include <string>
#include <iostream>

typedef XMLelement<> XMLelement_t;
typedef typename XMLelement_t::display display;
typedef typename XMLelement_t::Namespaces_t Namespaces_t;
typedef typename XMLelement_t::Attributes_t Attributes_t;

using namespace std;


int main() {

  const string doctype1{"HTML"};
  const string    name1{"html"};

  Attributes_t attrs0;
  Namespaces_t ns0("http://docbook.org/ns/docbook");

  XMLelement_t xmle0(ns0, name1);
  cout << "\'xmle0\' has been initialized with default namespace: " << xmle0.get_default_namespace() << '\n';


  XMLelement_t xmleh(ns0, "head", display::block_of_blocks);
  XMLelement_t xmleb(ns0, "body", display::block_of_blocks);
  xmle0.add(&xmleh);
  xmle0.add(&xmleb);

  XMLelement_t xmles(ns0, "section", display::block_of_blocks);
  xmleb.add(&xmles);

  XMLelement_t xmleh2(ns0, "h2", display::inline_of_inlines);
  xmles.add(&xmleh2);

  xmleb.attributes["lang"] = "es";

  xmle0.print(cout, Level(0));

  cout << "By the way, the size of a pretty empty XMLelement                 is " << sizeof(xmleh2) << " bytes,\n";
  cout << "The size of XMLelement for html (holding two children references) is " << sizeof(xmle0)  << " bytes,\n";
  int * pInt;
  cout << "whereas the size of a pointer is just " << sizeof(pInt) << " bytes.\n";
  cout << "We shouldn\'t worry over adding a couple of pointers to class XMLelement!\n";
  cout << "The size of an Attributes<> instance is " << sizeof(Attributes_t) << " bytes\n";
  cout << "The size of an Namespaces<> instance is " << sizeof(Namespaces_t) << " bytes\n";
  cout << "The size of an XMLnode<> instance is " << sizeof(typename XMLelement_t::XMLnode_t) << " bytes\n";

  return 0; }
