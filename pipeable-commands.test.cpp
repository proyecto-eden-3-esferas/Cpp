/* File "pipeable-commands.test.cpp"
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

/*
std::string & operator|(std::string & l, const std::string& r) {
  l.append(" | ");
  l += r;
  return l;
};
*/

std::string operator|(const std::string & l, const std::string& r) {
  return l + " | " + r;
};


using namespace std;

int main (int argc, const char** argv) {

  string ls("ls");
  string grep("grep \'.h\'");

  cout << "Print \"ls | grep\", where \'ls\' and \'grep\' are atomic commands to be chained:\n";
  cout << (ls | grep) << '\n';

  cout << "Now execute \"ls | grep\":\n";
  system( (ls | grep).data() );


  return 0;

}
