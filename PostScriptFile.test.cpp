/* File "PostScriptFile.test.cpp"
 */

#ifndef POSTSCRIPT_FILE_H
#include "PostScriptFile.h"
#endif

#include <iostream>
using namespace std;

typedef  char   char_type;
typedef double float_type;
typedef PostScriptFile<char_type,float_type> PostScriptFile_t;

int main() {

  PostScriptFile_t psf0("myFirst.ps");
  psf0.define_procedure("showpar");
  cout << "\'procedures\' has size: " << PostScriptFile_t::procedures.size() << '\n';
  cout << PostScriptFile_t::procedures["showpar"] << '\n';

  return 0;
}
