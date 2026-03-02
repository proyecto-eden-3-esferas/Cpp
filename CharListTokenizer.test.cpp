/* File "CharListTokenizer.test.cpp" */

#ifndef CHARLIST_TOKENIZER_H
#include "CharListTokenizer.h"
#endif




#include <fstream>
#include <sstream>

using namespace std;

int main()
{

  ifstream ifs("README.txt");
  WordTokenizer wt0(ifs);
  wt0.tokenize();

  string s0("Cream, some brown sugar, and half a lemon.");
  cout << "\nTokenize \"" << s0 << "\" with CharListTokenizer:\n";
  stringstream ss0(s0);
  CharListTokenizer clt0(ss0, ",.");
  clt0.tokenize();

  string s1("...At all, and nothing more");
  cout << "\nTokenize \"" << s1 << "\" with CharListTokenizer:\n";
  stringstream ss1(s1);
  CharListTokenizer clt1(ss1, ",.");
  clt1.tokenize();

  return 0;
}
