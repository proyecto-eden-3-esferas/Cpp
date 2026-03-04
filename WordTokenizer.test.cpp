/* File "WordTokenizer.test.cpp" */

#include <fstream>
#include <sstream>

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif


using namespace std;


string s1("Cream, some brown sugar, and half a lemon.");
string s2("\"Did he?\" he replied.");
string s3("Did he?--he replied.");
stringstream ss;

int main()
{

  ifstream ifs("README.txt");
  WordTokenizer wt0(ifs);
  wt0.tokenize();

  cout << "\nTokenizing: \"" << s1 << "\" with a WordTokenizer object:\n";
  ss.str(s1);
  WordTokenizer wt1(ss);
  wt1.tokenize();

  cout << "\nTokenizing: \"" << s2 << "\" with a WordTokenizer object:\n";
  ss.clear();
  ss.str(s2);
  WordTokenizer wt2(ss);
  wt2.tokenize();

  cout << "\nTokenizing: \"" << s3 << "\" with a WordTokenizer object:\n";
  ss.clear();
  ss.str(s3);
  WordTokenizer wt3(ss);
  wt3.tokenize();

  return 0;
}
