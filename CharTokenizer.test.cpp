/* File "CharTokenizer.test.cpp" */
#ifndef CHAR_TOKENIZER_H
#include "CharTokenizer.h"
#endif




#include <fstream>
#include <sstream>

using namespace std;

int main()
{


  string s0("Cream, some brown sugar, and half a lemon.");
  cout << "\nTokenize \"" << s0 << "\" with CharTokenizer:\n";
  stringstream ss0(s0);
  CharTokenizer ct0(ss0);
  ct0.tokenize();

  string s1("...At all, and \"nothing\" more");
  cout << "\nTokenize \"" << s1 << "\" with CharTokenizer:\n";
  stringstream ss1(s1);
  CharTokenizer ct1(ss1);
  ct1.tokenize();

  return 0;
}
