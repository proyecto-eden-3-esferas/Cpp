/* File "WordTrimTokenizer.test.cpp" */

#include <fstream>
#include <sstream>

#ifndef WORD_TRIM_TOKENIZER_H
#include "WordTrimTokenizer.h"
#endif


using namespace std;


string s1("Cream, some brown sugar, and half a lemon.");
string s2("\"Did he?\" he replied.");
string s3("Did he?--he replied.");
stringstream ss;

int main()
{

  ifstream ifs("README.txt");
  WordTrimTokenizer wt0(ifs);
  wt0.tokenize();

  cout << "\nTokenizing: \"" << s1 << "\" with a WordTrimTokenizer object:\n";
  ss.clear();
  ss.str(s1);
  WordTrimTokenizer wt1(ss);
  wt1.tokenize();

  cout << "\nTokenizing: \"" << s2 << "\" with a WordTrimTokenizer object:\n";
  ss.clear();
  ss.str(s2);
  WordTrimTokenizer wt2(ss);
  wt2.tokenize();

  cout << "\nTokenizing: \"" << s3 << "\" with a WordTrimTokenizer object:\n";
  ss.clear();
  ss.str(s3);
  WordTrimTokenizer wt3(ss);
  wt3.tokenize();

  return 0;
}
