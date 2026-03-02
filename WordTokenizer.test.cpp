/* File "WordTokenizer.test.cpp" */

#include <fstream>
#include <sstream>

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif


using namespace std;

int main()
{

  ifstream ifs("README.txt");
  WordTokenizer wt0(ifs);
  wt0.tokenize();

  string s("Cream, some brown sugar, and half a lemon.");
  stringstream ss(s);
  WordTokenizer wt1(ss);
  wt1.tokenize();

  return 0;
}
