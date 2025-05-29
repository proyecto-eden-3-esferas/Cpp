/* File "tokenizer.test.cpp" */



#include <iostream>
#include <regex>
#include <string>
#include <string_view>

#ifndef TOKENIZER_H
#include "tokenizer.h"
#endif
#ifndef TOKENIZER_CPP
#include "tokenizer.cpp"
#endif

std::string wd_test{R"([a-zA-Z]+)"};
std::regex  wd_regex(wd_test);

std::string id_test{R"([_\w][_\w0-9]*)"};
std::regex  id_regex(id_test);
std::smatch sm;

typedef tokenizer<char> tokenizer_t;

tokenizer_t tk0;

using namespace std;

int main(int argc, char** argv)
{

  string s;
  string key;
  int pos;

  while(true) {

    cout << "Type a string with no spaces to be tested for word or number or ...\n";
    cin >> s;

    cout << "Type a string to choose which regular expression to test for.\n";
    cout << "Choose among: { ";
    for(auto & p : tk0.name_to_regex_string)
      cout << p.first << ' ';
    cout << " }\n";
    cin >> key;

    cout << "Type a position whence to start reading your string (negative to exit): ";
    cin  >> pos;
    if(pos < 0)
      break;

    cout << "matches for " << key << "? " << boolalpha << tk0.matches(    s, pos, key) << "\n";
    cout << "has length "                              << tk0.starts_with(s, pos, key) << "\n";
  }

  return 0;
}
