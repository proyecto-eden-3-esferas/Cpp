#ifndef DEPENDENCY_MANAGER_H
#include "DependencyManager.h"
#endif

#include <string>

typedef std::string token_t;
typedef DependencyManager<token_t> DependencyManager_t;



using namespace std;

int main() {

  DependencyManager_t dm0;
  dm0.add_dependency("showpar", "newline");
  dm0.add_dependency("showpar", "rm");
  dm0.add_dependency("lead", "leadk");
  dm0.add_dependency("newline", "lead");
  dm0.add_dependency("newline", "bm");
  dm0.add_dependency("newline", "lm");
  dm0.add_dependency("newline", "turnpage");
  dm0.add_dependency("movetostart", "lm");
  dm0.add_dependency("movetostart", "tm");
  dm0.add_dependency("turnpage", "showpage");
  dm0.add_dependency("turnpage", "movetostart");

  cout << "Call reset_and_satisfy(\"showpar\"):\n";
  dm0.reset_and_satisfy("showpar");

  return 0;
}
