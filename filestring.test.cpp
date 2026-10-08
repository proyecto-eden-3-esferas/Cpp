/* File "filestring.test.cpp" */


#ifndef FILESTRING_H
#include "filestring.h"
#endif


#include <iostream>
using namespace std;

int main (int argc, const char** argv) {

  std::fstream fs("test.txt");

  filestring_container<std::vector> fc(fs,200);
  fc.emplace_back("very first");
  fc.emplace_back("second");

  cout << "\'fc\' has " << fc.size() << " element(s).\n";

  return 0;

}
