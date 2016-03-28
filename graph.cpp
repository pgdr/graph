/*
 * graph.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: pgd
 */

#include "graph.hpp"

#include <algorithm>    // std::find
#include <iostream>
#include <iterator>
#include <map>
#include <utility>

//#include <vector>

//#include "doubleton.hpp"

graph::graph() :
        vertex_count(0) {
    graph(10);
}

graph::graph(std::size_t size) :
        vertex_count(0) {
    vertices = std::vector<int>();
    vertices.reserve(size);
    edges = std::vector<doubleton>();
    edges.reserve(2 * size);
}

graph::graph(const graph& g) :
        vertex_count(0) {
    vertices = g.vertices;
    edges = g.edges;
}

graph::~graph() {
//    delete &edges;
//    delete &vertices;
}

std::vector<doubleton> graph::get_edges() {
    return edges;
}

std::size_t graph::size() const {
    return vertices.size(); // TODO cache
}

int graph::add_vertex() {
    int v = ++vertex_count;
    add_vertex(v);
    //std::cout << "Added new vertex labelled " << v << std::endl;
    return v;
}

bool graph::add_vertex(int v) {
    vertices.push_back(v);
    if (v > vertex_count)
        vertex_count = v;
    return true;
}

void graph::add_to_vertices_if_not(int a) {
    std::vector<int>::iterator it = find(vertices.begin(), vertices.end(), a);
    if (it == vertices.end())
        add_vertex(a);
}

bool graph::add_edge(int u, int v) {
    add_to_vertices_if_not(u);
    add_to_vertices_if_not(v);
    doubleton d(u, v);
    edges.push_back(d);
    return true;
}

bool graph::add_edge(doubleton edge) {
    return add_edge(edge.first, edge.second);
}

bool graph::delete_edge(int u, int v) {
    doubleton e(u, v);
    // TODO does this return the correct value?
    return edges.erase(std::remove(edges.begin(), edges.end(), e), edges.end())
            == edges.end();
}

bool graph::delete_edge(doubleton e) {
    return delete_edge(e.first, e.second);
}

bool graph::delete_vertex(int v) {
    std::vector<int>::iterator position = std::find(vertices.begin(),
            vertices.end(), v);
    if (position == vertices.end())
        return false;

    std::set<int> nv = get_neighborhood(v);
    for (std::set<int>::iterator it = nv.begin(); it != nv.end(); ++it) {
        delete_edge(v, *it);
    }
    return true;
}

bool has_vertex_cover_rec(graph &g, std::size_t vc) {
    if (vc == 0)
        return g.get_edges().empty();
    doubleton edge = *g.get_edges().begin();

    int v = edge.first;
    int u = edge.second;

    graph gv = g.shallow_copy();
    gv.delete_vertex(v);
    if (has_vertex_cover_rec(gv, vc - 1))
        return true;
    graph gu = g.shallow_copy();
    gu.delete_vertex(u);
    if (has_vertex_cover_rec(gu, vc - 1))
        return true;

    return false;
}

bool graph::has_vertex_cover(std::size_t vc) {
    return has_vertex_cover_rec(*this, vc);
}

const graph graph::shallow_copy() {
    graph xg(size());
    for (std::vector<doubleton>::iterator it = edges.begin(); it != edges.end();
            ++it)
        xg.add_edge(*it);
    return xg;
}

bool graph::has_edge(int v, int u) {
    return doubleton(v, u) % edges;
}

std::set<int> graph::get_neighborhood(int v) {
    std::set<int> nv;
    for (std::vector<doubleton>::iterator it = edges.begin(); it != edges.end();
            ++it) {
        if (it->contains(v)) {
            nv.insert(it->get_other(v));
        }
    }
    return nv;
}

int graph::connected_components() {
    int cc = 0;
    if (vertices.size() == 0)
        return 0;
    if (vertices.size() == 1)
        return 1;

    std::set<int> visited;
    std::set<int> queue;
    std::vector<int> remaining(vertices);
    while (visited.size() < size()) {
        queue.insert(remaining[0]);
        ++cc;
        while (queue.size() != 0) {
            int v = *queue.begin();
            std::set<int> nv = get_neighborhood(v);
            for (std::set<int>::iterator it = nv.begin(); it != nv.end();
                    ++it) {
                if (visited.find(*it) == visited.end()) {
                    queue.insert(*it);
                }
            }
            visited.insert(v);
            queue.erase(v);
        }
    }
    return cc;
}

bool graph::is_connected() {
    std::set<int> visited;
    std::set<int> queue;
    if (vertices.size() == 0)
        return false;

    queue.insert(vertices[0]);
    while (queue.size() != 0) {
        int v = *queue.begin();
        std::set<int> nv = get_neighborhood(v);
        for (std::set<int>::iterator it = nv.begin(); it != nv.end(); ++it) {
            if (visited.find(*it) == visited.end()) {
                queue.insert(*it);
            }
        }
        visited.insert(v);
        queue.erase(v);
    }
    return visited.size() == vertices.size();
}

void graph::print_vertices() {
    std::cout << "V: ";
    for (std::vector<int>::iterator it = vertices.begin(); it != vertices.end();
            ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void graph::print_edges() {
    std::cout << "E: ";
    for (std::vector<doubleton>::iterator it = edges.begin(); it != edges.end();
            ++it) {
        std::cout << "(" << it->first << "," << it->second << ")  ";
    }
    std::cout << std::endl;
}

