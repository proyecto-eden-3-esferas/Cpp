#ifndef SEQUENCE_MATCHER_H
#include "sequence_matcher.h"
#endif

#include <iostream>

typedef sequence_matcher<2,char> utf8_2B_matcher;

using namespace std;

int main() {

  utf8_2B_matcher u2m0;

  u2m0.push_back('a');
  u2m0.push_back('b');

  cout << "\'u2m0\' holds " << u2m0.size() << " elements.\n";
  cout << "They are:";
  for (int idx = 0; idx < u2m0.size(); ++idx)
    cout << ' ' << u2m0[idx];

  cout << '\n';


  return 0;
}
