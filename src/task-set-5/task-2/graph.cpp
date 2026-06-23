#include "graph.hpp"

#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

Graph::Graph(std::size_t size) : adjacency_list(size) {};

void Graph::add_edge(std::size_t from_vertex, std::size_t to_vertex, int weight) {
    if (from_vertex > adjacency_list.size() || weight < 0) {
        return;
    }

    Graph::edge new_edge {weight, to_vertex};
    adjacency_list[from_vertex].push_back(new_edge);
}

void Graph::dijkstra(std::size_t start_vertex) const {
    std::vector<int> min_cost_to_vertex(adjacency_list.size(), INT_MAX);
    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> edges_to_visit;

    min_cost_to_vertex[start_vertex] = 0;
    edges_to_visit.push({0, start_vertex});

    while (!edges_to_visit.empty()) {
        int cost_to_reach_current {edges_to_visit.top().first};
        std::size_t current_vertex {edges_to_visit.top().second};
        edges_to_visit.pop();

        if (cost_to_reach_current > min_cost_to_vertex[current_vertex]) {
            continue;
        }

        for (Graph::edge next_edge : adjacency_list[current_vertex]) {
            int cost_to_reach_next {next_edge.first};
            std::size_t next_vertex {next_edge.second};

            int new_cost {min_cost_to_vertex[current_vertex] + cost_to_reach_next};

            if (new_cost < min_cost_to_vertex[next_vertex]) {
                min_cost_to_vertex[next_vertex] = new_cost;
                edges_to_visit.push({new_cost, next_vertex});
            }
        }
    }

    std::cout << "Shortest distances from vertex " << start_vertex << ":\n";
    for (std::size_t i {1}; i < adjacency_list.size(); ++i) {
        std::cout << "To " << i << " vertex: " << min_cost_to_vertex[i] << '\n';
    }
}
