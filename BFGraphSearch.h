#ifndef GRAPH_BFSEARCH_H
#define GRAPH_BFSEARCH_H

/* class BFGraphSearch<> implements a Breadth-First Search
 * TODO:
 */

#ifndef GRAPH_SEARCH_H
#include "GraphSearch.h"
#endif

template <
  template<typename> typename EDGES = std::list,
  template<typename> typename QUEUE = std::queue,
  template<typename> typename NODES = std::vector, // index-addressable container
  template<typename> typename   SET = std::set,
                     typename  DESC = unsigned int // descriptor
>
class BFGraphSearch : public GraphSearch<EDGES,QUEUE,NODES,SET,DESC> {
public:
  typedef   SET<DESC>      set_t;
  typedef QUEUE<DESC>    queue_t;
  typedef EDGES<DESC>    edges_t;
  typedef NODES<edges_t> nodes_t;
  typedef  DESC     descriptor_t;
  typedef   GraphSearch<EDGES,QUEUE,NODES,SET,DESC>   GraphSearch_t;
  typedef BFGraphSearch<EDGES,QUEUE,NODES,SET,DESC> BFGraphSearch_t;
  //
  using GraphSearch_t::graph;
  using GraphSearch_t::visited_nodes;
  using GraphSearch_t::  is_visited;
  using GraphSearch_t::make_visited;
  using GraphSearch_t::queue;
  using GraphSearch_t::empty_queue;
  mutable queue_t gray_queue;
  //
  using GraphSearch_t::get_node;
  using GraphSearch_t::push_action;
  using GraphSearch_t::push;
  using GraphSearch_t::process_queue;
  void search(descriptor_t d) override;

  // Constructors and destructor:
  BFGraphSearch(const nodes_t& n) : GraphSearch_t(n) {};
};

#ifndef SEPARATE_COMPILATION
#include "BFGraphSearch.cpp"
#endif

#endif
