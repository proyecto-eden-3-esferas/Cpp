#ifndef FILELESS_TEXTOID_H
#include "fileless_textoid.h"
#endif
#ifndef FILELESS_TEXTOID_CPP
#include "fileless_textoid.cpp"
#endif

#ifndef TEXTOID_H
#include "textoid.h"
#endif
#ifndef TEXTOID_CPP
#include "textoid.cpp"
#endif

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

  // Declare an empty textoid<char>, then set its FSTREAM and 'offset'
  textoid_t textoid0;
  textoid0(fs,0);

  // Declare a complete textoid object: textoid1
  textoid_t textoid1(fs,0,s1);

  // print the size of 'textoid1' in RAM and compare to the sizes of std::string and void*
  void* void_ptr;
  cout << "The size of \'textoid1\' is : " << sizeof(textoid1) << " bytes, whereas a std::string is ";
  cout << sizeof(s1) << " bytes, and the size of void* is " << sizeof(void_ptr) << ".\n";

  // check that textoid1 holds STRING and print it:
  cout << "textoid1 has text: " << textoid1.get_text() << '\n';
  textoid1 = "A literal";
  cout << "After loading a literal, textoid1 has text: " << textoid1.get_text() << '\n';

  // check that changing the referenced string causes get_text() to output the new value:
  s1 = "A different one";
  textoid1 = s1;
  cout << "After setting \'s1\' to \"A diff...\" and setting textoid1 to s1, textoid1 has text: ";
  cout <<  textoid1.get_text() << '\n';

  // Declare textoid<char> 'textoid2' with no string attached:
  textoid_t textoid2(fs,0);
  cout << "Is textoid2 loaded: "    << boolalpha << textoid2.is_loaded() << '\n';
  // Now declare a string and assign it to 'textoid2':
  string s2 = "four";
  textoid2 = s2;
  // Last, store the string held by 'textoid2':
  cout << "Store the contents of \'textoid2\': " << boolalpha << textoid2.store() << '\n';

  // 'textoid3' is declared with no STRING, then made to load one:
  textoid_t textoid3(fs,0);
  textoid3.load();
  cout << "textoid3 was declared with no string, then loaded, so that it how holds text \"" << textoid3.get_text() << '\"' << '\n';

  /* Test struct textoid<char>::print_visitor,
   * which holds operator() (variant_type v) functions
   * and is meant to be used by std::visit(FUNCTION_OBJECT,VARIANT_ELEM)
   */
  cout << "\n\n(Now) test struct textoid<char>::print_visitor,\n";
  cout << "which holds operator() (variant_type v) functions\n";
  cout << "and is meant to be used by std::visit(FUNCTION_OBJECT,VARIANT_ELEM)\n";
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
