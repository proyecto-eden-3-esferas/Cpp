// Code for testing the implementation of a UDC (Universal Decimal Classification) class:

#include "UDC.h"

typedef float float_t;
typedef std::string string_t;
typedef basic_UDC<char> basic_UDC_t;
typedef UDC<unsigned long int, float_t, char> UDC_t;

using namespace std;
int main()
{
  UDC_t udc1("24");

  cout << "\'udc1\' is " << udc1 << '\n';
  cout << "Code 24 matches description: " << udc1.get_description() << '\n';
  cout << "Is decimal code \"2\" contained? " << boolalpha << basic_UDC_t::contains("2") << '\n';
  string_t res, aUDCcode("245.22.3(32)\"alpha\"");
  basic_UDC_t::set_digit_string(aUDCcode, res);
  cout << "The decimal prefix of \"" << aUDCcode << "\" is \"" << res << '\"';
  cout << ", and its float value is " << fixed << UDC_t::get_digit_float(aUDCcode) << '\n';
  cout << "Is \"234\" included in \"23(44)\"? " << boolalpha << basic_UDC_t::included_in("234", "23(44)") << '\n';

  return 0;
}
