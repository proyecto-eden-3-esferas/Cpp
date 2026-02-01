#ifndef XMLDOC_H
#include "XMLdoc.h"
#endif

typedef XMLdocdecl<std::map, Level<signed int> > XMLdocdecl_t;
typedef XMLelement<Level<signed int>,std::vector,std::map> XMLelement_t;

using namespace std;

int main() {

  // First, build a XMLdocdecl_t object:
  XMLdocdecl_t myDocDecl("HTML");
               myDocDecl.add_entity("nbsp", "#160");
               myDocDecl.add_system_entity("ch01", "Foundations.xml");

  // Then, build an XMLelement_t object:
  XMLelement_t myRoot("html",true,false);
  XMLelement_t myHead("head",true,false);
    myRoot.add(myHead);
  XMLelement_t myBody("body",true,false);
    myRoot.add(myBody);
  XMLelement_t p1("p",true,true);
      myBody.add(p1);
  XMLText txt10("We had better acknowledge the convenience of clarity. ");
        p1.add(txt10);
  XMLelement_t i11("i",false,true);
        p1.add(i11);
  XMLText txt11("(Adam Ant)");
          i11.add(txt11);

  // Finally, initialize a XMLdoc with both:
  XMLdoc myXMLdoc(&myDocDecl, &myRoot);
  // Add a stylesheet:
  myXMLdoc.add_stylesheet("common-stylesheet.css");
  // And print it:
  myXMLdoc.print(cout, Level(0));

  /*
  cout << "\nNow call print on \'myDocDecl\':\n";
  myDocDecl.print(cout, Level(0));
  cout << "\nYet again, call print on \'myDocDecl\', which seems to cause a segmentation fault:\n";
  myXMLdoc.pdocdecl->print(cout, Level(1));
  */

  return 0;
}
