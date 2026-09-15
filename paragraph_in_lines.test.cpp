#include "paragraph_in_lines.h"

#include <iostream>
using namespace std;

paragraph_in_lines<double,std::vector> pil0;

int main() {

  pil0.push_back("It did not happen");
  pil0.push_back("the way you think it did.");

  for(const auto & l : pil0)
    cout << l << '\n';

  return 0;
}
