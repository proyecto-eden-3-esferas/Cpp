#ifndef LOAD_STRING_WITH_FILE_H
#define LOAD_STRING_WITH_FILE_H

#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

/* Function std::size_t load_string_with_file(...) returns number of characters read into STRING string
   and has overloads for a filename
   (1)  std::size_t load_string_with_file(STRING& str, const CHAR* filename, SIZE_T offset = 0)
   and for a std::ifstream
   (2)  std::size_t load_string_with_file(STRING& str, IFSTREAM& ifs)
   (3)  std::size_t load_string_with_file(STRING& str, IFSTREAM& ifs,        SIZE_T num)
 * Overloads (2) and (3) start reading into the string at the read cursor (tellg())
   and return the read cursor at its original position if last input param is set to true
 * The only change in (3). relative to (2) is that 'num' characters are red ('num' is an input parameter)
   instead of (sz - off), as in (2)
   unless num > (sz - off): this triggers num = sz - off
   and again num characters are read.
 */

// (1):
template <typename CHAR=char>
std::size_t load_string_with_file(std::basic_string<CHAR>& str, const CHAR* filename, std::size_t off = 0) {
  std::size_t sz = std::filesystem::file_size(filename);
  str.reserve(sz + 1 - off);
  str[sz - off] = '\0';
  std::ifstream ifs(filename);
  ifs.seekg(off);
  ifs.read(&str[0], sz - off);
  ifs.close();
  return sz - off;
};

// (2):
template <typename CHAR=char>
std::size_t load_string_with_file(std::basic_string<CHAR>& str,
                                  std::basic_ifstream<CHAR>& ifs,
                                  bool rewind = false) {
  std::size_t off = ifs.tellg();
  ifs.seekg(0, std::ios::end);
  std::size_t sz =  ifs.tellg();
  ifs.seekg(off);
  str.reserve(sz - off + 1);
  str[sz - off] = '\0';
  ifs.read(&str[0], sz - off);
  if(rewind)
    ifs.seekg(off);
  return sz - off;
};
// (3):
template <typename CHAR=char>
std::size_t load_string_with_file(std::basic_string<CHAR>& str,
                                  std::basic_ifstream<CHAR>& ifs,
                                  std::size_t num, bool rewind = false) {
  std::size_t off = ifs.tellg();
  ifs.seekg(0, std::ios::end);
  std::size_t sz =  ifs.tellg();
  if(sz - off < num)
    num = sz - off;
  ifs.seekg(off);
  str.reserve(num + 1);
  str[num] = '\0';
  ifs.read(&str[0], num);
  if(rewind)
    ifs.seekg(off);
  return num;
};

#endif
