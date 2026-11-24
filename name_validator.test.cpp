/* File "name_validator.test.cpp" */

#ifndef NAME_VALIDATOR_H
#include "name_validator.h"
#endif
#ifndef NAME_VALIDATOR_CPP
#include "name_validator.cpp"
#endif

typedef name_validator<char> name_validator_type;
name_validator_type n0;

#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  string test_string;
  while(true) {
    cout << "Type a(nother) string, then press enter. (Press ! to leave): ";
    cin  >> test_string;
    if(test_string[0] == '!') {
      cout << "Invalid string. Bye\n";
      break;
    }
    cout << "Is string \"" << test_string << "\" is a valid name? ";
    cout << boolalpha << n0(test_string) << '\n';
  }
  return 0;
}
