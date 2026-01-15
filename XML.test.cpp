#ifndef XML_H
#include "XML.h"
#endif

#include <string>
#include <iostream>

using namespace std;


int main() {

  const string doctype1{"HTML"};
  const string    name1{"html"};

  XMLdoc doc1{doctype1};
  XMLroot xmlroot{doc1};
  XMLelement xmlel1{doc1, name1};

  cout << "\'doc1\'    has DOCTYPE: " << doc1.get_doctype() << '\n';
  cout << "\'xmlel1\'  has DOCTYPE: " << xmlel1.get_doctype() << " and name: \"" << xmlel1.get_name() << "\"\n";
  cout << "\'xmlroot\' has DOCTYPE: " << xmlroot.get_doctype() << " and name: \"" << xmlroot.get_name() << "\"\n";

  cout << "sizeof(xmlel1) is as many as " << sizeof(xmlel1) << " bytes\n";

  xmlel1.add_element("body");
  cout << "sizeof(xmlel1.children[0]) is as many as " << sizeof(xmlel1.children[0]) << " bytes\n";

  return 0;
}
