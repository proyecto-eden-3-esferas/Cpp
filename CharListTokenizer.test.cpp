/* File "CharListTokenizer.test.cpp" */

#ifndef CHARLIST_TOKENIZER_H
#include "CharListTokenizer.h"
#endif




#include <fstream>
#include <sstream>

using namespace std;

int main()
{

  string s0("Cream, some brown sugar, and half a lemon.");
  cout << "\nTokenize \"" << s0 << "\" with a CharListTokenizer:\n";
  stringstream ss0(s0);
  CharListTokenizer clt0(ss0, ",.");
  clt0.tokenize();

  string s1("He paused. \"It\'s not all that difficult\", he added.");
  cout << "\nTokenize \"" << s1 << "\" with a CharListTokenizer:\n";
  stringstream ss1(s1);
  CharListTokenizer clt1(ss1, ",.\"\'");
  clt1.tokenize();

  const string JSONstr{R"({"name": "Pelt"; "children": ["Cyl", "Lull"], "address": {"street": "Corner", "number": 11}})"};
  const string JSONpunct{"\"\',:{}[]"};
  cout << "\nTokenize \"" << JSONstr << "\", which holds a JSON object,";
  cout << " with a CharListTokenizer (special chars: " << JSONpunct << " )\n";
  stringstream ss2(JSONstr);
  CharListTokenizer JSONstrChListTok(ss2, JSONpunct);
  JSONstrChListTok.tokenize();

  return 0;
}
