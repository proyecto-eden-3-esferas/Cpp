#ifndef REGEX_MAP_H
#include "regex_map.h"
#endif

typedef regex_map<std::map> regex_map_t;

regex_map_t rxm0;

/*
template <...>
void list_stored_regex(std::ostream & o, const regex_map<CONT> & m) {

}
 */

#include <iostream>
using namespace std;

int main() {


  char q{'y'};
  std::string next_name, next_regex_string;
  while(q == 'y') {
    cout << "Would you like to add another {name,regex}? Type \'y\' for yes, \'n\' for no: ";
    cin  >> q;
    if(q != 'y' && q != 'Y')
      break;
    cout << "Type the name of the regular expression you want to add: ";
    cin  >> next_name;
    cout << "Type the regular expression you want to add: ";
    cin  >> next_regex_string;
    rxm0.emplace(next_name, next_regex_string);
    cout << "Now \'rxm0\' holds " << rxm0.size() << " pair(s).\n";
    // add regex:
  } // while

  cout << "Which would you like next? Type the letter in brackets and press ENTER.\n";
  cout << "List all regex\'s stored so far?                           (l)\n";
  cout << "Add yet ahother named regex?                              (d)\n";
  cout << "Test a given regex against a string you will type?        (t)\n";
  cout << "Test all stored regex\'s against a string of your choice?  (a)\n";
  cout << "Clear all stored regex\'s                                  (c)\n";
  cin >> q;

  switch (q) {
    case 'l':
              break;
    case 'd':
              cout << "Type the name of the regular expression you want to add: ";
              cin  >> next_name;
              cout << "Type the regular expression you want to add: ";
              cin  >> next_regex_string;
              rxm0.emplace(next_name, next_regex_string);
              break;
    case 't':
              break;
    case 'a':
              break;
    case 'c':
              cout << "\'rxm0\' holds " << rxm0.size() << " pair(s), then";
              rxm0.clear();
              cout << " it holds " << rxm0.size() << " pair(s).\n";
              break;
    default:
              break;
  }




  return 0;
}
