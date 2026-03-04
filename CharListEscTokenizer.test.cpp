/* File "CharListEscTokenizer.test.cpp" */

#ifndef CHARLISTESC_TOKENIZER_H
#include "CharListEscTokenizer.h"
#endif

#include <fstream>
#include <sstream>

using namespace std;

int main()
{

  string s0("{\"name\": \"Dell\", \"sizes\": [43,44]}");
  cout << "\nTokenize \"" << s0 << "\" with CharListEscTokenizer:\n";
  stringstream ss0(s0);
  CharListEscTokenizer clet0(ss0, ",.:{}[]", true);
  clet0.tokenize();

  string s1("...an utter \'unknown\', and nothing more");
  cout << "\nTokenize \"" << s1 << "\" with CharListEscTokenizer(STRINGSTREAM,\",.:{}[]\", false,false).\n";
  cout << "We make both \'skip_leading_space\' and \'skip_trailing_space\' false due to the nature of the string.\n";
  stringstream ss1(s1);
  CharListEscTokenizer clet1(ss1, ",.:{}[]", false,false);
  clet1.tokenize();

  string s2("she uttered: \"Ada soon\\\"there\", she did.");
  cout << "\nTokenize \"" << s2 << "\" with CharListEscTokenizer(STRINGSTREAM,\",.:{}[]\", true,true).\n";
  cout << "We make both \'skip_leading_space\' and \'skip_trailing_space\' false due to the nature of the string.\n";
  stringstream ss2(s2);
  CharListEscTokenizer clet2(ss2, ",.:{}[]", false,false);
  clet2.tokenize();

  return 0;
}
