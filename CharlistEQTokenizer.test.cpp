/* File "CharlistEQTokenizer.test.cpp" */

#ifndef CHARLIST_EQ_TOKENIZER_H
#include "CharlistEQTokenizer.h"
#endif


class JSONtokenizer : public CharlistEQTokenizer {
public:
  JSONtokenizer(std::istream & i)
  : CharlistEQTokenizer(i,",.:{}[]", true,true, '\\', '\"') {};
};

#include <fstream>
#include <sstream>

using namespace std;

int main()
{

#ifndef TEST_JSON

  string s0("said: \"Ada soon\\\"there\", then what?");
  cout << "\nTokenize \"" << s0 << "\" with CharlistEQTokenizer:\n";
  stringstream ss0(s0);
  CharlistEQTokenizer clet0(ss0, ",.:{}[]", true);
  clet0.tokenize();

  string s1("...an utter \'unknown\', and nothing more");
  cout << "\nTokenize \"" << s1 << "\" with CharlistEQTokenizer(STRINGSTREAM,\",.:{}[]\", false,false).\n";
  cout << "We make both \'skip_leading_space\' and \'skip_trailing_space\' false due to the nature of the string.\n";
  stringstream ss1(s1);
  CharlistEQTokenizer clet1(ss1, ",.:{}[]", false,false);
  clet1.tokenize();

#else

  string s2("{\"name\": \"Dell\", \"sizes\": [43,44]}");
  cout << "\nTokenize \"" << s2 << "\" with CharlistEQTokenizer(STRINGSTREAM,\",.:{}[]\", true,true).\n";
  cout << "We make both \'skip_leading_space\' and \'skip_trailing_space\' false due to the nature of the string.\n";
  stringstream ss2(s2);
  CharlistEQTokenizer clet2(ss2, ",.:{}[]", false,false);
  clet2.tokenize();

  string s3("{\"name\": \"Plain\", \"claim\" :\"an\\\"pa\"}");
  cout << "\nTokenize \"" << s3 << "\" with CharlistEQTokenizer(STRINGSTREAM,\",.:{}[]\", true,true).\n";
  cout << "We make both \'skip_leading_space\' and \'skip_trailing_space\' true.\n";
  stringstream ss3(s3);
  //CharlistEQTokenizer clet3(ss3, ",.:{}[]", false,false);
  JSONtokenizer clet3(ss3);
  clet3.tokenize();

#endif

  return 0;
}
