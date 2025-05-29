/* File "load_string_with_file.test.cpp"
 */
#ifndef LOAD_STRING_WITH_FILE_H
#include "load_string_with_file.h"
#endif

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{

  std::string s;
  if(argc > 1) {

    load_string_with_file(s, argv[1], 3);
    std::cout << "\'s\' holds: " << s.c_str() << '\n';

    std::cout << "Type a word and press enter: ";
    std::cin  >> s;

    std::ifstream inf(argv[1]);
    inf.seekg(12);
    load_string_with_file(s, inf, true);
    std::cout << "After setting rewind, \'inf\' is at: " << inf.tellg() << '\n';
    inf.close();
    std::cout << "Now \'s\' holds: " << s.c_str() << '\n';

    return 0;



    std::cout << "loading/opening file \"" << argv[1] << "\"\n";
    std::size_t sz = std::filesystem::file_size(argv[1]);
    std::cout << "sz = " << sz << '\n';
    std::string content(sz, '\0');
    std::cout << "[0]\n";
    std::ifstream ifs(argv[1]);
    std::cout << "[1]\n";
    ifs.read(&content[0], sz);
    std::cout << "[2]\n";
    std::cout << "Now string \'content\' has size: " << content.size() << "and contents:\n";
    std::cout << "[3]\n";
    std::cout << content << '\n';
    ifs.close();


  } else {
    cout << "ERROR: no filename provided!\n";
  }



  return 0;
}
