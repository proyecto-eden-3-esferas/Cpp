#ifndef GRAPH_SEARCH_CPP
#define GRAPH_SEARCH_CPP

#ifndef GRAPH_SEARCH_H
#include "GraphSearch.h"
#endif

template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void GraphSearch<EDGES,QUEUE,NODES,SET,DESC>::empty_queue() {
  while(queue.size())
    queue.pop();
};

template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void GraphSearch<EDGES,QUEUE,NODES,SET,DESC>::process_queue() {
  std::cout << "Into process_queue():\n";
  while(queue.size()) {
    std::cout << "Processing node " << queue.front()  << '\n';
    queue.pop();
  }
  std::cout << '\n';
};





template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void GraphSearch<EDGES,QUEUE,NODES,SET,DESC>::make_visited(descriptor_t desc) {
  visited_nodes.emplace(desc);
};

template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
bool GraphSearch<EDGES,QUEUE,NODES,SET,DESC>::is_visited(descriptor_t desc) const {
  return visited_nodes.contains(desc);
};







template <
  template<typename> typename EDGES,
  template<typename> typename QUEUE,
  template<typename> typename NODES,
  template<typename> typename   SET,
                     typename  DESC
>
void GraphSearch<EDGES,QUEUE,NODES,SET,DESC>::push(descriptor_t d) {
  queue.push(d);
  push_action(d);
};

#endif
