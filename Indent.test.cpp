#include "Indent.h"

using namespace std;

typedef signed int sint_t;

Indent<sint_t>          i3val(0, 3);
Indent<sint_t>          i4val(0, 4);
Indent<sint_t>&         i4(i4val);

int main() {

  cout <<   '\n'   << "No indent\n";
  cout <<    i4++  << "Still no Indent (using \'i4++\')\n";
  cout <<    i4    << "Indent by resulting \'i4\'\n";
  cout <<  ++i4    << "Indent by, again, preincremented \'i4\'\n";

  return 0;
}
