/* File "jq.test.cpp"
 */

#ifndef JQ_H
#include "jq.h"
#endif


typedef jq<char,std::vector>  jq_t;
typedef typename jq_t::path path_t;

using namespace std;

int main (int argc, const char** argv) {

  for(int i=0; i < argc; ++i) {
    std::cout << i << "th command line argument is: \"" << argv[i] << "\"\n";
  }
  if(argc < 3) {
    std::cout << "USAGE: <FILE.json> <field>\n";
    return 0;
  }


  // Initialize jq::path with the first command line argument (a file):
  jq_t jq0(argv[1]);

  // Initialize string 'term' with either the 2nd command line argument or a default:
  string term;
  if(argc >=3)
    term = argv[2];
  else
    term = "term";


  char c; // a variable for holding user input:
          // either y/Y for "yes" or any other character for "no"
  cout << "Do you want to call jq0.map(\"" << term << "\") on file \'" << argv[1] << "\'?\n";
  cout << "Type y(es) or n(o): ";
  cin >> c;
  if( c=='y' || c=='Y') {
    cout << '\n';
    jq0.map("term");
  }

  cout << "Do you want to call jq0.pretty() on file \'"                << argv[1] << "\'?\n";
  cout << "Type y(es) or n(o): ";
  cin >> c;
  if( c=='y' || c=='Y') {
    cout << '\n';
    jq0.pretty();
  }

  path_t p0;
  cout << "Do you want to test jq<>::path?\n";
  cout << "Type y(es) or n(o): ";
  cin >> c;
  if( tolower(c)=='n')
    return 0;

  cout << "\nDeclare a path and build it by adding an index and a name.\n";
  cout << "(So as to reach field <name> at position <index> in an array of objects.)";
  unsigned int idx;
  string      name;
  cout << "Type a non-negative integer: ";
  cin >> idx;
  cout << "Type a word: ";
  cin >> name;
  p0.add(idx);
  p0.add(name);

  cout << "Print the path in jq format.\n";
  p0.print(std::cout);

  cout << "\nGet to value through path: ";
  p0.print(cout);
  cout << '\n';
  jq0.get_value(p0);

  cout << '\n';



  return 0;

}
