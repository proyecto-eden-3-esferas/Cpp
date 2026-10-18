#ifndef METADATA_BASE_H
#include "metadata_base.h"
#endif

typedef metadata_map<std::map> metadata_map_t;

metadata_map_t mdp0("Welcome to yourself, to begin with.");
metadata_map_t mdp1({{"type", "definition"}},
                    "the process of coming into view, starting to exist, or becoming known.");

#include <iostream>
using namespace std;

int main() {

  cout << "The contents of \'mdp0\' is: " << mdp0.get_contents() << ',' << '\n';

  cout << "which is of type ";
  if(mdp0.get_fileformat() == metadata_base::fileformat::plaintext)
    cout << "plain text\n";
  else
    cout << "unknown\n";

  mdp0["importance"] = "low";
  cout << "mdp0\'s importance is: " << mdp0.at("importance") << '\n';

  cout << "mdp0 has size: " << mdp0.size() << '\n';
  cout << "mdp1 has size: " << mdp1.size() << '\n';

  metadata_map_t mdp2(std::move(mdp1));
  cout << "After move-constructing mdp2 from mdp1, mdp1 has size: " << mdp1.size() << '\n';
  cout << "mdp2 has size: " << mdp2.size() << '\n';



  return 0;
}
