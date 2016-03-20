#include<iostream>
#include<vector>
#include<cctype>

#include "graph.hpp"
#include "doubleton.hpp"


int main()
{
  graph g = 100; // create graph on 10 verts
  
  g.add_vertex(1);
  g.add_vertex(2);
  g.add_vertex(3);
  g.add_edge(2,3);
    
  for (auto i = 0; i < 5; ++i) 
    g.add_vertex();
  
  g.add_edge(3,4);
  g.add_edge(3,6);
  g.add_edge(3,7);
  
  g.add_edge(2,5);
  g.add_edge(2,8);
  g.add_edge(2,7);
  
  g.add_edge(1,5);
  g.add_edge(1,9);
  
  g.print_vertices();
  g.print_edges();

  if (g.is_connected())
    std::cout << "g is connected" << std::endl;
  else
    std::cout << "g is disconnected" << std::endl;
}
