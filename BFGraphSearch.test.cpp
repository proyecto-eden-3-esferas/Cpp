#ifndef GRAPH_SEARCH_H
#include "GraphSearch.h"
#endif

#ifndef GRAPH_BFSEARCH_H
#include "BFGraphSearch.h"
#endif

typedef BFGraphSearch<> BFGraphSearch_t;
typedef typename BFGraphSearch_t::nodes_t graph_core_t;

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

BFGraphSearch_t bfs0(gc0);

int main() {

  cout << "\'gc0\' has  " << gc0.size()  << " node(s)\n";
  cout << "\'bfs0\' has " << bfs0.size() << " node(s)\n";

  bfs0.search(0);

  cout << "\nNow process the thus built queue:\n";
  bfs0.process_queue();

  return 0;
}
