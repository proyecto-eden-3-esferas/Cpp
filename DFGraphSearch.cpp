#ifndef GRAPH_DFSEARCH_CPP
#define GRAPH_DFSEARCH_CPP

#ifndef GRAPH_DFSEARCH_H
#include "DFGraphSearch.h"
#endif


// Implementations of DFGraphSearch members:

template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void DFGraphSearch<EDGES,QUEUE,NODES,SET,DESC>::search(descriptor_t d) {
  /*
DFS_iterative(start):
    create an empty stack
    push start node onto stack
    create an empty set for visited nodes
   */
  empty_queue();
  visited_nodes.clear();
  gray_stack.push(d);

  /*
    while stack is not empty:
        node = pop from stack
        if node is not visited:
            mark node as visited
            process node (e.g., print)
            for each neighbor in node's adjacency list (in reverse order if needed):
                if neighbor is not visited:
                    push neighbor onto stack
   */
  descriptor_t current_descriptor;
  while( ! gray_stack.empty()) {
    current_descriptor = gray_stack.top();
    gray_stack.pop();
    if( ! is_visited(current_descriptor)) {
      make_visited(current_descriptor);
      push(current_descriptor);
      for(auto desc : get_node(current_descriptor)) {
        if( ! is_visited(desc))
          gray_stack.push(desc);
      } // for
    } // if
  } // while

};

#endif
