#ifndef TEXTOID_H
#include "textoid.h"
#endif

/* This file only tests class textoid<>, derived from class fileless_textoid<>
 *
 * TODO:
-[ ] This file demands that "io.text" be an existing file
 [x] It can be touch'ed into existence in a Makefile entry
 */

typedef  std::basic_fstream<char>  fstream_t;
typedef std::basic_ofstream<char> ofstream_t;
typedef std::basic_ifstream<char> ifstream_t;
typedef             textoid<char>  textoid_t;


using namespace std;
int main()
{

  string s1("A string.");
  fstream_t fs("io.text");

  //textoid_t textoid1; textoid1 = s1;

  // Declare an empty textoid<char>
  textoid_t textoid0;
  // then set its FSTREAM and 'offset'
  textoid0(fs,0);
  // alternatively: textoid0.set_file_and_offset(fs,0);
  // alternatively: textoid0.set(                fs,0);

  // Declare a complete textoid object: textoid1
  textoid_t textoid1(fs,0,s1);

  // print the size of 'textoid1' in RAM and compare to the sizes of std::string and void*
  void* void_ptr;
  cout << "The size of \'textoid1\' is : " << sizeof(textoid1) << " bytes, whereas a std::string is ";
  cout << sizeof(s1) << " bytes, and the size of void* is " << sizeof(void_ptr) << ".\n\n";

  // check that textoid1 holds STRING and print it:
  cout << "textoid1 has text: " << textoid1.get_text() << '\n';

  textoid1 = "A literal";

  cout << "After loading a literal, textoid1 has text: " << textoid1.get_text() << '\n';

  // check that changing the referenced string causes get_text() to output the new value:
  s1 = "A different one";
  textoid1 = s1;
  cout << "After setting \'s1\' to \"A diff...\", textoid1 has text: ";
  cout <<  textoid1.get_text() << '\n';

  // Declare textoid<char> 'textoid2' with no string attached:
  textoid_t textoid2(fs,0);
  cout << "Is textoid2 loaded: "    << boolalpha << textoid2.is_loaded() << '\n';
  // Now declare a string and assign it to 'textoid2':
  string s2 = "four";
  textoid2 = s2;
  // Last, store the string held by 'textoid2':
  cout << "Store the contents of \'textoid2\' into file \'fs\': " << boolalpha << textoid2.store() << '\n';

  // 'textoid3' is declared with no STRING, then made to load one:
  cout << "\'textoid3\' is declared with no STRING, then made to load one and print its text:";
  textoid_t textoid3(fs,0);
  textoid3.load();
  cout << '\"' << textoid3.get_text() << '\"' << "\n\n";

  cout << "Test struct textoid<char>::print_visitor," << endl;
  cout << "which holds operator() (variant_type v) functions" << endl;
  cout << "and is meant to be used by std::visit(FUNCTION_OBJECT,VARIANT_ELEM):" << endl;
  vector<textoid_t::variant_t> vec_of_varnt;
  string num2("two, ");
  string num3("three, ");
  reference_wrapper<string> rw3(num3);
  vec_of_varnt.push_back(num2);
  vec_of_varnt.push_back(rw3);
  vec_of_varnt.push_back(textoid3);
  typename textoid_t::print_visitor pv(cout);
  for(auto & e : vec_of_varnt)
    std::visit(pv,e);

  fs.close();

  return 0;
}
