#ifndef ENTITIES_H
#include "Entities.h"
#endif

using namespace std;

int main() {

  Entities es;
  cout << "First, declare doctype and entities given a doctype and a DTD:\n";
  es.declare_doctype_and_entities(cout,
                                  "book",
                                  "/home/francisco/Documents/docbook.dtd");


  cout << "\n\nNext add some entities and SISTEM entities, then print again:\n";
  es.add_entity(       "nbsp", "&#160;");
  es.add_entity(       "date", "January 22nd, 1999");
  es.add_system_entity("posibilidad", "texts/posibilidad.xml");
  es.add_system_entity("result_file", "../result.txt");
  es.declare_doctype_and_entities(cout,
                                  "book",
                                  "/home/francisco/Documents/docbook.dtd");

  cout << "Let us now test print_transformed(OSTREAM&, TEXT):\n";
  string str0("Do not break&nbsp;this space!.\n");
  string str1("Made in &date;.\n");
  string str2("Computations have produced:\n &result_file;\n, much to our full satisfaction.\n");
  es.print_transformed(cout, str0);
  es.print_transformed(cout, str1);
  es.print_transformed(cout, str2);

  return 0;
}

