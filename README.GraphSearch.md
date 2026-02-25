# Graph Search Code

Class `GraphSearch` is the abstract parent of `BFGraphSearch` (for Breadth-First Search) and `DFGraphSearch` (for Depth-First Search).

Each instance holds a reference to a graph, which is set upon construction. The type of the graph (`graph_t`) is determined by the class's template parameters and is just `NODES<EDGES<DESC>>`, essentially an adjacency matrix or container of containers of descriptors (either unsigned integers or pointers).

A big design decision is whether to make this graph reference constant. Changing it to non-const would change the signature of many other member functions.

Nodes (the rows in the adjacency matrix representation) are identified by "descriptors". By that a mean that we may get to a node (as a set of edges in this philosophy) either by providing its index into an array or index-addressable data structure, or through a pointer.

## Class `GraphSearch`

`GraphSearch` has pure virtual method:
```
virtual void search(descriptor_t d) = 0;
```
which is the *engine* of each derived class.



It also holds three member variables:
- a (constant) reference to a graph;
- visited_nodes, possibly as a `std::set<DESC>`
- a queue (a node sequence), possibly as a `std::queue<DESC>`


## Classes `BFGraphSearch` and `DFGraphSearch`

These are derived from `GraphSearch`.

They limit themselves to implementing the said `search(NODE)` member function,
which, again, is pure virtual in their parent class.


## Functions in *BeFS.geeksforgeeks.cpp*

I have copyied an implementation advanced in the GeeksForGeeks site for Best-First Search. It is very straightforward code consisting of two functions. It is not set in a class, much less a class hierarchy. This is left for the client programmer as an exercise.


## Motivation

This project arose while writing class `DependencyManager<>`, which performs a Topological Sort to establish the order of inclusion of files (as for my PostScript project, read README.PostScript.md).

Topological Sort relies on Depth-First Search. In a Directed Acyclic Graph (DAG) of dependencies, one should include files as they are backtracked from.
