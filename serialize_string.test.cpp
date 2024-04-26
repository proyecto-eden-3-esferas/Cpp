#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "serialize_string.h"

/* When reading a generated text file like "sep_strings.txt" and "sized_strings.txt"
 * using command 'less' shows default separator == null character (\0) as "^@"
 */

int main() {

  string teststr;
  cout << "Testing deserialize_sized_string(std::cin, STRING&)...\n";
  cout << "Type a string size and a string, then ENTER: ";
  deserialize_sized_string(cin, teststr);
  cout << "Your string was: \"" << teststr << "\", of final size=" << teststr.length() << endl;
  cout << "serialize_sep_string(std::cout,teststr) = \"";
           serialize_sep_string(std::cout,teststr);
  cout << "\" (null character probably generated no output as it is not printable.) \n\n";


  string ms1("Allí\nHabía lo que tú sabes.");
  string ms2("Al anochecer\nAlmas en pena pululaban.");

  cout << "First we serialize_sized_string() two multiline strings to a file.\n";
  ofstream o("sized_strings.txt");
    o.seekp(0);
    serialize_sized_string(o, ms1);
    serialize_sized_string(o, ms2);
  o.close();

  string answer;
  cout << "Shall strings be deserialized through size? Type y[es] or n[o]. (You may now read \"sized_strings.txt\" so as to check serialization.)" << endl;
  cin >> answer;

  ifstream i("sized_strings.txt");
    string str;
    i.seekg(0);
    deserialize_sized_string(i,str);
    cout << "(size) deserialized string= \"" << str << '\"' << endl;
    deserialize_sized_string(i,str);
    cout << "(size) deserialized string= \"" << str << '\"' << endl;
  i.close();



  cout << endl << "Now we shall check serialize_sep_string() and deserialize_sep_string()." << endl;

  o.open("sep_strings.txt");
    o.seekp(0);
    serialize_sep_string(o, ms1);
    serialize_sep_string(o, ms2);
  o.close();


  cout << "Deserialize through sep(arator)? (You may now read \"sep_strings.txt\" so as to check serialization.)" << endl;
  cin >> answer;
  if( (answer.length() > 0) &&
      (answer[0] == 'n' ||
       answer[0] == 'N')
    ) return 0;

  i.open("sep_strings.txt");
    i.seekg(0);
    deserialize_sep_string(i,str);
    cout << "deserialized string= \"" << str << '\"' << endl;
    deserialize_sep_string(i,str);
    cout << "deserialized string= \"" << str << '\"' << endl;
  i.close();
  
  return 0;
};
