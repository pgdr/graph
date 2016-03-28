/*
 * graph.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: pgd
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstddef>
#include <set>
#include <vector>

#include "doubleton.hpp"

/// Undirected simple graph
class graph {
public:

    /// constructs new graph
    graph();

    /// constructs new graph, reserves size s for vertices
    graph(std::size_t s);

    graph(const graph&);

    ~graph();

    const graph shallow_copy();

    /// adds a new vertex with new vacant index
    int add_vertex();

    /// adds a vertex with name v
    bool add_vertex(int v);

    /// adds edge between u and v, adds vertices if not there already
    bool add_edge(int u, int v);

    /// adds the edge the input doubleton represents
    bool add_edge(doubleton edge);

    /// returns true iff (v,u) is an edge iff (u,v) is an edge
    bool has_edge(int v, int u);

    /// true iff this is connected, false if no vertices
    bool is_connected();

    /// gets the open neighborhood of v
    std::set<int> get_neighborhood(int v);

    /// deletes edge between v and u if exists, return true if exists
    bool delete_edge(int v, int u);

    /// deletes given edge if exists, return true if exists
    bool delete_edge(doubleton e);

    bool delete_vertex(int v);

    void print_vertices();

    void print_edges();

    /// returns the number of connected components, and 0 if empty vertex set
    int connected_components();

    /// return number of vertices
    std::size_t size() const;
private:
    std::vector<int> vertices;
    std::vector<doubleton> edges;
    int vertex_count;
    void add_to_vertices_if_not(int v); /// adds v to vertices if not there
};

#endif /* GRAPH_HPP_ */
