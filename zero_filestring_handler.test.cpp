/* File "zero_filestring_handler.test.cpp"
 * tests class zero_filestring_handler<CONTAINER>
 */

#ifndef ZERO_FILESTRING_HANDLER_H
#include "zero_filestring_handler.h"
#endif

#include <iostream>

typedef zero_filestring_handler<std::vector> zero_filestring_handler_t;

using namespace std;

int main (int argc, const char** argv) {

  std::fstream fs0("test.text", std::fstream::out | std::fstream::trunc);
  fs0 << "erste" << '\0';
  fs0 << "zweite" << '\0';
  fs0 << "dritte" << '\0';
  fs0.close();

  zero_filestring_handler_t zfh0("test.text", true);

  cout << "\'zfh0\' has size = " << zfh0.size() << ", and is:\n" << zfh0 << '\n';

  zfh0.emplace_back("fierte");
  zfh0.emplace_back("fünfte");
  zfh0.emplace_back("sechste");


  cout << "After duely emplacing back...\n";
  cout << "\'zfh0\' has size = " << zfh0.size() << ", and is:\n" << zfh0 << '\n';

  return 0;

}
