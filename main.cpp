/*
 * main.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: pgd
 */

#include <cstddef>
#include <iostream>

#include "graph.hpp"

int main() {
    graph g = 100; // create graph on 10 verts

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_edge(2, 3);

    for (int i = 0; i < 5; ++i)
        g.add_vertex();

    g.add_edge(4, 3); // shits'n'giggles
    g.add_edge(3, 6);
    g.add_edge(3, 7);

    g.add_edge(2, 5);
    g.add_edge(2, 8);
    g.add_edge(2, 7);

    g.add_edge(1, 5);
    g.add_edge(1, 9);

    g.print_vertices();
    g.print_edges();

    if (g.is_connected())
        std::cout << "g is connected" << std::endl;
    else
        std::cout << "g is disconnected" << std::endl;

    std::cout << "computing vertex cover ... [0, " << g.size() << "]"
            << std::endl;
    for (std::size_t i = 0; i < g.size(); ++i) {
        if (g.has_vertex_cover(i)) {
            std::cout << "    g has vertex cover of size " << i << std::endl
                    << "terminating vc" << std::endl;
            i = g.size() + 1;
        } else {
            std::cout << "    g has no vertex cover of size " << i << std::endl;
        }
    }

    std::cout << "delete 3" << std::endl;
    g.delete_vertex(3);

    if (g.is_connected())
        std::cout << "g is connected" << std::endl;
    else
        std::cout << "g is disconnected" << std::endl;

    //	delete &g;
}

