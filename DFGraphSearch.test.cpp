#ifndef GRAPH_SEARCH_H
#include "GraphSearch.h"
#endif

#ifndef GRAPH_BFSEARCH_H
#include "DFGraphSearch.h"
#endif

typedef DFGraphSearch<> DFGraphSearch_t;
typedef typename DFGraphSearch_t::nodes_t graph_core_t;

graph_core_t gc0{
  {1,2,5}, // 0
  {3,4},   // 1
  {5,0},   // 2
  {6},     // 3
  {0},     // 4
  {1},     // 5
  {2}      // 6
};

using namespace std;

DFGraphSearch_t dfs0(gc0);

int main() {

  cout << "\'gc0\' has  " << gc0.size()  << " node(s)\n";
  cout << "\'dfs0\' has " << dfs0.size() << " node(s)\n";

  dfs0.search(0);

  cout << "\nNow process the thus built queue:\n";
  dfs0.process_queue();

  return 0;
}
