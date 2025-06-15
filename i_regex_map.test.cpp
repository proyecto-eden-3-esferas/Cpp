/* File "regex_map.test.cpp" */



#include <iostream>
#include <string>
#include <string_view>

#ifndef I_REGEX_MAP_H
#include "i_regex_map.h"
#endif

#ifndef SEPARATE_COMPILATION
#ifndef I_REGEX_MAP_CPP
#include "i_regex_map.cpp"
#endif
#endif

/*
#ifndef TOKEN_EATER_H
#include "token_eater.h"
#endif
*/


typedef i_regex_map<char> tokenizer_t;

tokenizer_t tk0;

using namespace std;

int main(int argc, char** argv)
{

  for(const auto& pr : tk0) {
    cout << "key: \"" << pr.first << "\" is mapped to value: \"" << pr.second << "\"\n";
  }

  string s;
  string key;
  int pos;

  while(true) {

    cout << "Type a string with no spaces to be tested for word or number or ...\n";
    cin >> s;

    cout << "Type a string to choose which regular expression out of " << tk0.size() << " to test for.\n";
    cout << "Choose among: { ";
    for(auto & p : tk0)
      cout << p.first << ' ';
    cout << " }\n";
    cin >> key;

    cout << "Type a position whence to start reading your string (negative to exit): ";
    cin  >> pos;
    if(pos < 0)
      break;

    cout << "how many characters are matched for key \"" << key << "\"? ";
    cout << tk0.count(s,key,pos) << " in \"" << tk0.get_string_view(s,key,pos) << "\"\n";
    cout << "(All the same, the longest match was for key: \"" << tk0.get_key_for_longest_match(s,pos) << "\")\n\n";
  }

  return 0;
}
