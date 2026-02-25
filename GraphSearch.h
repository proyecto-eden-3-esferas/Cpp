#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <vector>

/* class GraphSearch<> implements a (breadth-first) search.
 * It remains an abstract class, as it doesn't implement a "search(DESC)"
 * I have chosen to work on a constant reference to a graph.
 * This sets the const-ness of many of its member variables and functions.
 * I have qualified some member variables as "mutable" so that constant members may change it/them
 * TODO:
 * [ ] As already mentioned, consider making member variable 'graph' non-constant
 *     and make all members in GraphSearch and children non-constant
 * [ ] Implement search_remaining() to reach all disconnected nodes
 * [ ] Implement a function to record and produce the edges that are walked across
 * [ ] Partial-specialize descriptor for NODES (3rd template parameter)
 *     not being index addressable: type pointer?
 */

template <
  template<typename> typename EDGES = std::list,
  template<typename> typename QUEUE = std::queue,
  template<typename> typename NODES = std::vector, // index-addressable container
  template<typename> typename   SET = std::set,
                     typename  DESC = unsigned int // descriptor
>
class GraphSearch {
public:
  typedef   SET<DESC>      set_t;
  typedef QUEUE<DESC>    queue_t;
  typedef EDGES<DESC>    edges_t;
  typedef NODES<edges_t> nodes_t;
  typedef  DESC     descriptor_t;
  typedef GraphSearch<EDGES,QUEUE,NODES,SET,DESC> GraphSearch_t;
  // Member variables:
  const nodes_t & graph;
  set_t   visited_nodes; // nodes in 'visited_nodes' must not be visited again
  mutable queue_t queue; // stores the node sequence (to be) visited
  // Member functions:
  void empty_queue();
  void process_queue();
  void make_visited(descriptor_t desc);
  bool   is_visited(descriptor_t desc) const;
  virtual void push_action(descriptor_t d) {std::cout << "PUSHING: " << d << '\n';};
  void         push(       descriptor_t d);
//      edges_t& get_node(descriptor_t d)       {return graph[d];};
  const edges_t& get_node(descriptor_t d) const {return graph[d];};
  std::size_t size() const {return graph.size();};
  virtual void search(descriptor_t d) = 0;
  // Constructors and destructor:
  GraphSearch(const nodes_t& n) : graph(n) {};
};

#ifndef SEPARATE_COMPILATION
#include "GraphSearch.cpp"
#endif

#endif
