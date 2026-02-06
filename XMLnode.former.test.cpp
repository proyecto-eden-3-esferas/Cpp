#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

#ifndef ENTITIES_H
#include "Entities.h"
#endif

typedef XMLnode<DefaultPrintTransformer> XMLnode_t;

using namespace std;

int main() {

  cout << "Print string: \"This is a &msg; for you.\":\n";
  DefaultPrintTransformer ptplain;
  ptplain.print_transformed(cout, "This is a &msg; for you:\n&result;\n");

  cout << "\n\nNow print the same string through an Entities<> object:\n";
  Entities<> ptent;
  ptent.get_internal_entities().insert({"msg", "message"});
  ptent.get_external_entities().insert({"result", "../result.txt"});
  ptent.print_transformed(cout, "This is a &msg; for you:\n&result;\n");

  return 0;
}
