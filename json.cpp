#include <iostream>
#include <string_view>

#include "json.h"

using namespace j;
using namespace std;

int main() {
  // build and test some jarray<>'s:
  jarray<int,double,string_view> ja0({nullopt, 2, false}); // a string_view obj would fail
  jarray<int,double,string> ja1;
  ja1.emplace_back("pato");
  ja1.emplace_back(1727);
  //ja1.emplace_back(nullopt_t);
  ja1.emplace_back("bliss");
  ja1.emplace_back(true);
  for( auto& e : ja1) {
    //cout << e.index() << endl;
    print_variant(std::cout, e);
  }

  // build and test a jdoc<>
  jdoc jd1(
            {
              {"nombre", "Fatima"},
              //{"children", ["Ali", "Muhammad"]},
              {"clave", std::nullopt}
            }
          );
  jd1.insert({"casada", true});
  jd1.insert({"peso", 59.9});
  jd1.insert({"my-array", ja1});
  //jd1["edad"]
  cout << "\n\nThe size of \'jd1\' is " << jd1.size() << endl;

  cout << "\'jd1\' is\n{\n";
  std::size_t i(0);
  for(auto& e : jd1 ) {
    if(i > 0)
      cout << ",\n";
    ++i;
    print_pair<int,double,std::string> (cout, e, 1);
  }

  cout << "\n}\n";

  return 0;
}
