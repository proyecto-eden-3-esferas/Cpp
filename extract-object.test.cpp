/* File "extract-object.test.cpp"
 * Two approaches:
   (1) JackLloyd's
   (2) class WrapReader
 * Also, you may issue statement: OSTREAM.setstate(std::ios::failbit);
   and its reverse:               OSTREAM.clear()
 */

#include <fstream>
#include <iostream>     // std::cin, std::cout
#include <string>

/* @JackLloyd, I usually write code like this for operator >>(in, custom_type& c):

if ((in >> member1) && (in >> member2)) {
  c = custom_type{move(member1), move(member2)};
} else {
  in.setstate(std::ios::failbit);
} return in;


When written like this, you could embed custom_type in another object and read with a similar implementation (it stacks up nicely).

The reason I like it, is because an 'if' is easier to write than a 'try/catch' block (for the client code) - it imposes less restrictions. */

template <typename T>
class WrapReader {
public:
  typedef std::ifstream ifstream_t;
  typedef std::ifstream::filepos filepos;
protected:
  filepos start;
  ifstream_t & ifs;
  bool try_to_initialize(T & t) {
    ifs >> t;
    return ifs.good();};
  //
public:
  bool initialize(T & t) {
    if(try_to_initialize(t)) {
      start = ifs.tellg();
      return true;
    }
    else {
      ifs.clear();
      ifs.seekg(start);
      return false;
    }
  }; // initialize
  //
  WrapReader(ifstream_t& i) : ifs(i), start(ifs.tellg()) {};
};

using namespace std;

int main () {


  return 0;

}
