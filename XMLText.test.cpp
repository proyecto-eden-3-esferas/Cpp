#ifndef XMLTEXT_H
#include "XMLText.h"
#endif


#include <iostream>
#include <string>

typedef XMLText<>    text_t;
typedef text_t::Entities_t Entities_t;
typedef XMLComment<> comment_t;
typedef XMLCDATA<>   cdata_t;
//typedef XMLText<Level<signed int>> text_t;

using namespace std;

int main() {

  text_t t0("My favourite entity is <HTML>, as of &date;.");
  cout << "\nPrint \"" << t0 << "\" through member print: ";
  t0.print(cout, Level(0));
  cout << "\n\nPrint \"" << t0 << "\" through member print_transformed: ";
  t0.print_transformed(cout);

  Entities_t es;
  es.internal_entities.insert({"date", "January 22nd, 1999"});
  cout << "\n\nPrint \"" << t0 << "\" through member print_transformed() and an entity that transforms &date;";
  t0.print_transformed(cout,es);


  cout << '\n' << '\n';

  cout << "Print string \"Not to be ignored.\" as a comment:\n";
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
