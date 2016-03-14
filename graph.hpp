
#ifndef LIB_GRAPH_HPP
#define LIB_GRAPH_HPP

#include <vector>
#include <set>
#include "doubleton.hpp"


/// Undirected simple graph
class graph {
public:
  
  /// constructs new graph, reserves size s for vertices
  graph(int s);

  ~graph();
  
  /// adds a new vertex with new vacant index
  int add_vertex();
  
  /// adds a vertex with name v
  bool add_vertex(int v);
  
  // boolean remove_vertex();
  bool add_edge(int u, int v);

  /// returns true iff (v,u) is an edge iff (u,v) is an edge
  bool has_edge(int v, int u);

  /// true iff this is connected, false if no vertices
  bool is_connected();

  /// gets the open neighborhood of v
  std::set<int> get_neighborhood(int v);

private:
  std::vector<int> vertices;
  std::vector<doubleton> edges;
  int vertex_count = 0;
};


#endif // LIB_GRAPH_HPP
