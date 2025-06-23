#ifndef FILELESS_TEXTOID_H
#include "fileless_textoid.h"
#endif

#ifndef FILELESS_TEXTOID_CPP
#include "fileless_textoid.cpp"
#endif


typedef  std::basic_fstream<char>  fstream_t;
typedef std::basic_ofstream<char> ofstream_t;
typedef std::basic_ifstream<char> ifstream_t;

typedef fileless_textoid<char> fileless_textoid_t;


using namespace std;
int main()
{

  string s1("A string.");
  fstream_t fs("io.text");

  fileless_textoid_t textoid0;

  fs.close();

  return 0;
}
