/* File "comma_separated_array_of_strings.test.cpp"
 *
 *
 */

#include <iostream>
#include <set>
#include <vector>

#ifndef COMMA_SEPARATED_ARRAY_OF_STRINGS_H
#include "write_comma_separated_array_of_strings.h"
#endif



using namespace std;

set<string> elems{"term", "lang", "definition", "notes"};

int main()
{

  string res("my results");
  write_comma_separated_array_of_strings(res, elems);

  cout << "results: " << res << '\n';

  return 0;
}
