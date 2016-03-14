
#include <vector>
#include <set>

#include "graph.hpp"
#include "doubleton.hpp"


graph::graph(int size) {
  vertices = std::vector<int>( size );
  edges = std::vector<doubleton>( );
}

graph::~graph() {
  //delete edges;
  //delete vertices;
}

int graph::add_vertex() {
  int v = ++vertex_count;
  add_vertex(v);
  return v;
}

bool graph::add_vertex(int v) {
  vertices.push_back(v);
  if ( v > vertex_count) vertex_count = v;
  return true;
}

bool graph::add_edge(int u, int v) {
  doubleton d(u,v);
  edges.push_back(d);
  return true;
}

bool graph::has_edge(int v , int u)
{
  return doubleton(v,u)%edges;
}

std::set<int> graph::get_neighborhood(int v)
{
  std::set<int> nv;
  for(std::vector<doubleton>::iterator it = edges.begin(); it != edges.end(); ++it) {
    if (it->contains(v)) {
      nv.insert(it->get_other(v));
    }
  }
  return nv;
}


bool graph::is_connected() {
  std::set<int> visited;
  std::set<int> queue;
  if (vertices.size() == 0) {
    return false;
  }

  queue.insert(vertices[0]);
  while (queue.size() != 0) {
    int v = *queue.begin();
    std::set<int> nv = get_neighborhood(v);
    for(std::set<int>::iterator it = nv.begin(); it != nv.end(); ++it) {
      if (visited.find(*it) != visited.end()) {
        queue.insert(*it);
      }
    }
    visited.insert(v);
  }
  return visited.size() == vertices.size();
}
