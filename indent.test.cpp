/** Automating indentation through manipulators
 *  Two approaches:
 *  (1) manipulators that depend on global variables
        'indent_level' and 'indent_spaces'
        (code borrowed from 'NewGraphic01/Logic' compilation unit
 *  (2) an indentation<CH> class with member variables
        'indent_level' and 'indent_spaces'.
        Defined separately in "indent.h".
 */

#include "indent.h"
#include <iostream>

unsigned int indent_level = 0;
unsigned int indent_spaces = 2;
std::ostream&       indent(std::ostream& o) {
  for(int i = 0; i < indent_level; ++i)
    for(int j = 0; j <   indent_spaces; ++j)
      o << ' ';
  return o;
};
std::ostream& reset_indent(std::ostream& o) {indent_level=0; return o;};
std::ostream&  into_indent(std::ostream& o) {
  ++indent_level;
  return o;
};
std::ostream& outof_indent(std::ostream& o) {
  --indent_level;
  return o;
};
std::ostream& newline_indent(std::ostream& o) {
  o << std::endl << indent;
  for(unsigned int i = 0; i < indent_spaces; i++)
    o << ' ';
  return o;
};


using namespace std;

int main() {

  cout << "Test manipulators \'into_indent\', \'outof_indent\' etc.\n";

  cout << indent << "<section>" << into_indent << endl;
  cout << indent <<   "<title>A sample, a test</title>" << endl;
  cout << indent <<   "<para>The point of helping Chris" << endl;
  cout << indent <<   "was to save Helen.</para>" << outof_indent << endl;
  cout << indent << "</section>" << endl << endl;

  cout << "Test class indentation<> with some XML\n";
  indentation<char> ind3(3);
  cout <<   ind3 << "<section>" << endl;
  cout << ++ind3 <<   "<title>A sample, a test</title>" << endl;
  cout <<   ind3 <<   "<para>The point of helping Chris" << endl;
  cout <<   ind3 <<   "was to save Helen.</para>" << endl;
  cout << --ind3 << "</section>" << endl << endl;

  return 0;
}
