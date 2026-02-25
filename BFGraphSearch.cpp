#ifndef GRAPH_BFSEARCH_CPP
#define GRAPH_BFSEARCH_CPP

#ifndef GRAPH_BFSEARCH_H
#include "BFGraphSearch.h"
#endif


// Implementations of BFGraphSearch members:

template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void BFGraphSearch<EDGES,QUEUE,NODES,SET,DESC>::search(descriptor_t d) {
  empty_queue();
  visited_nodes.clear();
  /*
    create a queue Q
    mark start_node as visited
    enqueue start_node into Q
   */
  push(d);
  gray_queue.push(d);
  make_visited(d);

  /*
    while Q is not empty:
        current_node = dequeue(Q)
        for each neighbor of current_node:
            if neighbor is not visited:
                mark neighbor as visited
                enqueue neighbor into Q
   */
  descriptor_t current_descriptor;
  while( ! gray_queue.empty())
  {
    current_descriptor = gray_queue.front();
    gray_queue.pop();
    for(auto & neigh : get_node(current_descriptor)) {
      if( ! is_visited(neigh)) {
        make_visited(neigh);
        push(neigh);
        gray_queue.push(neigh);
      }
    } // for
  } // while
};

#endif
