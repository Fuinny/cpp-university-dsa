#include "graph.hpp"

#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

Graph::Graph(std::size_t size) : adjacency_list(size) {};

void Graph::add_edge(std::size_t from_vertex, std::size_t to_vertex, int weight) {
    if (from_vertex > adjacency_list.size() || weight < 0) {
        return;
    }

    Graph::edge new_edge {weight, to_vertex};
    adjacency_list[from_vertex].push_back(new_edge);
}

void Graph::prim(std::size_t start_vertex) const {
    std::vector<bool> is_already_in_mst(adjacency_list.size(), false);
    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> edges_to_visit;

    int total_weight {};
    edges_to_visit.push({0, start_vertex});

    while (!edges_to_visit.empty()) {
        int current_vertex_weight {edges_to_visit.top().first};
        std::size_t current_vertex {edges_to_visit.top().second};
        edges_to_visit.pop();

        if (is_already_in_mst[current_vertex]) {
            continue;
        }

        is_already_in_mst[current_vertex] = true;
        total_weight += current_vertex_weight;

        std::cout << "Vertex " << current_vertex << " added to MST with weight " << current_vertex_weight << '\n';

        for (Graph::edge next_edge : adjacency_list[current_vertex]) {
            std::size_t next_vertex {next_edge.second};

            if (!is_already_in_mst[next_vertex]) {
                edges_to_visit.push(next_edge);
            }
        }
    }

    std::cout << "Total weight of MST: " << total_weight << '\n';
}

struct KEdge {
    std::size_t from;
    std::size_t to;
    int weight;
};

static std::size_t find_set(std::size_t v, std::vector<std::size_t>& parent) {
    if (parent[v] != v) {
        parent[v] = find_set(parent[v], parent);
    }
    return parent[v];
}

static void union_sets(std::size_t a, std::size_t b, std::vector<std::size_t>& parent, std::vector<std::size_t>& rank) {

    a = find_set(a, parent);
    b = find_set(b, parent);

    if (a != b) {
        if (rank[a] < rank[b]) {
            std::swap(a, b);
        }

        parent[b] = a;

        if (rank[a] == rank[b]) {
            rank[a]++;
        }
    }
}

void Graph::kruskal() const {
    std::vector<KEdge> edges;

    for (std::size_t u = 0; u < adjacency_list.size(); ++u) {
        for (const auto& e : adjacency_list[u]) {
            edges.push_back({u, e.second, e.first});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
        return a.weight < b.weight;
    });

    std::vector<std::size_t> parent(adjacency_list.size());
    std::vector<std::size_t> rank(adjacency_list.size(), 0);

    for (std::size_t i = 0; i < parent.size(); ++i) {
        parent[i] = i;
    }

    int total_weight = 0;

    for (const auto& e : edges) {
        std::size_t root_u = find_set(e.from, parent);
        std::size_t root_v = find_set(e.to, parent);

        if (root_u != root_v) {
            std::cout << "Edge " << e.from << " - " << e.to << " with weight " << e.weight << " added to MST\n";

            total_weight += e.weight;
            union_sets(root_u, root_v, parent, rank);
        }
    }

    std::cout << "Total weight of MST: " << total_weight << '\n';
}
