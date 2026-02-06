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
  es.internal_entities.insert({       "nbsp", "&#160;"});
  es.internal_entities.insert({       "date", "January 22nd, 1999"});
  es.external_entities.insert({"posibilidad", "texts/posibilidad.xml"});
  es.external_entities.insert({"result_file", "../result.txt"});
  es.declare_doctype_and_entities(cout,
                                  "book",
                                  "/home/francisco/Documents/docbook.dtd");

  cout << "Let us now test print_transformed(OSTREAM&, TEXT):\n";
  string str0("Do not break&nbsp;this space!.\n");
  string str1("Made in &date;.\n");
  string str2("Computations have produced:\n &result_file;\nmuch to our full satisfaction.\n");
  es.print_transformed(cout, str0);
  es.print_transformed(cout, str1);
  es.print_transformed(cout, str2);

  return 0;
}

