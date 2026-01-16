/*
#ifndef XML_H
#include "XML.h"
#endif
*/


#ifndef XML_H
#include "XML.h"
#endif

#ifndef XML_PRINTABLE_H
#include "XMLprintable.h"
#endif

#include <string>
#include <iostream>

using namespace std;


int main() {

  const string doctype1{"HTML"};
  const string    name1{"html"};

  XMLdoc doc1{doctype1};
  cout << "\'doc1\'    has DOCTYPE: " << doc1.get_doctype() << '\n';
  // Test entities:

  cout << "Does \'doc1\' define entity \"&apos;\"? " << boolalpha << doc1.has_entity("apos") << '\n';
  if( doc1.has_entity("apos") )
    cout << "\'doc1\' defines entity \"&apos;\" as " << doc1.get_entity("apos") << "\n";

  doc1.set_entity("mdash", "#8212");
  cout << "Does \'doc1\' define entity \"&mdash;\"? " << boolalpha << doc1.has_entity("mdash") << '\n';
  if( doc1.has_entity("mdash") )
    cout << "\'doc1\' defines entity \"&mdash;\" as " << doc1.get_entity("mdash") << "\n\n";

  cout << "Define an XMLroot object.\n";
  XMLroot xmlroot{doc1};
  cout << "Define an XMLelement object taking the XMLdoc object and a name (\"" << name1 << "\").\n";
  XMLelement xmlel1{doc1, name1};
  cout << "\'xmlel1\'  has (inherited) DOCTYPE: " << xmlel1.get_doctype() << " and name: \"" << xmlel1.get_name() << "\"\n";
  cout << "\'xmlroot\' has (inherited) DOCTYPE: " << xmlroot.get_doctype() << " and name: \"" << xmlroot.get_name() << "\"\n";

  cout << "sizeof(xmlel1) is as many as " << sizeof(xmlel1) << " bytes\n";

  xmlel1.add_element("body");
  cout << "sizeof(xmlel1.children[0]) is as many as " << sizeof(xmlel1.children[0]) << " bytes\n";

  cout << "\nPrint \'xmlel1\' as XML:\n";
  xmlel1.attributes["class"] = "general";
  xmlel1.print_element(cout);

  cout << "\nPrint last child as XML:\n";
  if(xmlel1.children[0].index() == 4)
    get<4>(xmlel1.children[0]).print_element(cout);

  return 0;
}
