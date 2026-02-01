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
  es.add_entity(       "nbsp", "#160");
  es.add_system_entity("posibilidad", "texts/posibilidad.xml");
  es.declare_doctype_and_entities(cout,
                                  "book",
                                  "/home/francisco/Documents/docbook.dtd");

  return 0;
}

