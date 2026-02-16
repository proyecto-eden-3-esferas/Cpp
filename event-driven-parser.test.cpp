/* File "event-driven-parser.test.cpp"
 * tests class simple_xml_parser<CHAR,STRING>
 */



#ifndef SIMPLE_EVENT_DRIVEN_PARSER_H
#include "event-driven-parser.h"
#endif


using namespace std;

typedef char char_type;
typedef simple_xml_parser<char_type> simple_xml_parser_t;

int main()
{

  simple_xml_parser_t sp0("simple.xml");

  std::cout << "\nParse file as XML:\n";
  sp0.process();

  return 0;
}
