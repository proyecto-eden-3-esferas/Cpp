/* File "basic_tokenizer.test.cpp"
 */
#ifndef BASIC_TOKENIZER_H
#include "basic_tokenizer.h"
#endif
#ifndef BASIC_TOKENIZER_CPP
#include "basic_tokenizer.cpp"
#endif

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  ifstream in;
  string s;

  if(argc > 1) {
    in.open(argv[1]);
    while(in) {
      in >> s;
      cout << '\"' << s << "\"\n";
    }
    in.close();
  } else {
    cout << "Your first arg after \"" << argv[0];
    cout <<"\" must be the name of an existing text file to be tokenized.\n";
  }

  return 0;
}
