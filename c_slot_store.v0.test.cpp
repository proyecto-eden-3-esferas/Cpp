#ifndef  C_SLOT_STORE_H
#include "c_slot_store.v0.h"
#endif

#ifndef  C_SLOT_STORE_CPP
#include "c_slot_store.v0.cpp"
#endif

#include <iostream>
#include   <string>

typedef c_slot_store<char> c_slot_store_t;

using namespace std;
string filename{"io.text"};
c_slot_store_t ncss0(filename.data(), 100, 5);
c_slot_store_t ncss1(filename.data(), 100, 5);

char  cstr0[]{"One Love, One Heart"}; // 19 chars excluding '\0'
char* cstr1;
char** ppCh= new char*;

int main() {

  cout << "String \'cstr0\': \"" << cstr0 << "\" has size: " << sizeof(cstr0) << '\n';

  ncss0.write(0, cstr0);
  //ncss0.write(0, cstr0, sizeof(cstr0) - 1);
  //ncss0.~slot_store();
  ncss0.flush();

  ncss1.read( 0, ppCh);
  cstr1 = *ppCh;
  cout << "String \'cstr1\' has size=" << sizeof(cstr1) <<  " and is: \"" << cstr1 << "\"\n";

  string_view sv0 = ncss1.get_string_view(0);
  string_view sv1(cstr1);
  cout << "string_view from \'ncss1.get_string_view(0)\' has length " << sv0.length() << " and  is \"" << sv0.data() << "\" or \"" << sv0 << "\"\n";

  /*
  for(auto c : sv0)
    cout << static_cast<int>(c) << '-';

  cout << "\nstring_view sv1(cstr1) has length " << sv1.length() << " and  is \"" << sv1.data() << "\"\n";
  for(auto c : sv1)
    cout << static_cast<int>(c) << '-';
  */

  return 0;
}
