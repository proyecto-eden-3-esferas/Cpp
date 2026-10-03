/* File "printing-as-binary-and-identifying-multibyte-utf8.test.cpp"
 */

#include <iostream>
#include <string>
/*
#include <string_view>
*/

void print_char_as_binary(char c) {
  for (int i = 0; i < 8; i++) {
    std::cout << !!(c & 0x80);
    c <<= 1;
  }
};
void print_chars_in_string_as_binary(const std::string& str) {
  for (int i = 0; i < str.length(); i++) {
    if(i != 0)
      std::cout << ' ';
    print_char_as_binary(str[i]);
  }
};

bool leads_2B_utf8(char c) {
  const char mask_l2B(128 + 64);
  if((c & mask_l2B) && !(c & 32))
    return true;
  else
    return false;
};
bool follows_multibyte_utf8_leader(char c) {
  const char mask_l2B(128 + 64);
  if((c & 128) && !(c & 64))
    return true;
  else
    return false;
}
bool leads_3B_utf8(char c) {
  const char mask_l3B(128 + 64 + 32);
  if((c & mask_l3B) && !(c & 16))
    return true;
  else
    return false;
};
bool leads_4B_utf8(char c) {
  const char mask_l4B(128 + 64 + 32 + 16);
  if((c & mask_l4B) && !(c & 8))
    return true;
  else
    return false;
};




using namespace std;
string ny("ñ"), aa("á"), ag("à"), adm("¡");

int main (int argc, const char** argv) {


  cout << "Character \'" << ny << "\' has binary representation: ";
  print_chars_in_string_as_binary(ny);
  cout << '\n';

  cout << "Character \'" << aa << "\' has binary representation: ";
  print_chars_in_string_as_binary(aa);
  cout << '\n';

  cout << "Character \'" << ag << "\' has binary representation: ";
  print_chars_in_string_as_binary(ag);
  cout << '\n';

  cout << "Character \'" << adm << "\' has binary representation: ";
  print_chars_in_string_as_binary(adm);
  cout << '\n' << '\n';

  cout << boolalpha;
  cout << "Does ñ[0] lead a 2-byte utf-8 character? " << leads_2B_utf8(ny[0]) << '\n';
  cout << "Does ñ[1] lead a 2-byte utf-8 character? " << leads_2B_utf8(ny[1]) << '\n';
  cout << "Does ñ[0] follow in a 2-byte utf-8 character? " << follows_multibyte_utf8_leader(ny[0]) << '\n';
  cout << "Does ñ[1] follow in a 2-byte utf-8 character? " << follows_multibyte_utf8_leader(ny[1]) << '\n';

  cout << '\n';


  return 0;

}
