/* File "sense.test.cpp" */


#ifndef SENSE_H
#include "sense.h"
#endif

#include <string>
#include <string_view>
#include <iostream>
#include <variant>

typedef sense<std::string,0> non_quote;
typedef sense<std::string,1>     quote;
typedef std::variant<non_quote,quote> text_variant_t;

using namespace std;

int main(int argc, char** argv)
{

  quote      q("Go ahead!");
  non_quote nq(", said she.");
  cout << "\'nq\': " << nq << '\n';
  cout << "\'q\' : " <<  q << '\n';
  text_variant_t tv0(non_quote(", said Marion."));
  text_variant_t tv1(    quote("You should go ahead now"));

  if(tv0.index() == 0)
    cout << "\'tv0\' holds a non-quote and runs: " << get<0>(tv0) << '\n';
  if(tv1.index() == 1)
    cout << "\'tv1\' holds a     quote and runs: " << get<1>(tv1) << '\n';

  return 0;
}
