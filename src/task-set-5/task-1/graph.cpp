#include "graph.hpp"

#include <cstddef>
#include <queue>
#include <stack>
#include <vector>

Graph::Graph(std::size_t size) : adjacency_list(size) {}

void Graph::add(std::size_t from_vertex, std::size_t to_vertex) {
    if (from_vertex < adjacency_list.size()) {
        adjacency_list[from_vertex].push_back(to_vertex);
    }
}

std::vector<std::size_t> Graph::DFS(std::size_t start) const {
    std::vector<bool> visited(adjacency_list.size(), false);
    std::vector<std::size_t> order;
    std::stack<std::size_t> stack;

    stack.push(start);

    while (!stack.empty()) {
        std::size_t current_vertex {stack.top()};
        stack.pop();

        if (!visited[current_vertex]) {
            visited[current_vertex] = true;
            order.push_back(current_vertex);

            for (std::size_t i {adjacency_list[current_vertex].size()}; i > 0; --i) {
                std::size_t next_vertex {adjacency_list[current_vertex][i - 1]};

                if (!visited[next_vertex]) {
                    stack.push(next_vertex);
                }
            }
        }
    }

    return order;
}

std::vector<std::size_t> Graph::BFS(std::size_t start) const {
    std::vector<bool> visited(adjacency_list.size(), false);
    std::vector<std::size_t> order;
    std::queue<std::size_t> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
        std::size_t current_vertex {queue.front()};
        queue.pop();
        order.push_back(current_vertex);

        for (std::size_t next_vertex : adjacency_list[current_vertex]) {
            if (!visited[next_vertex]) {
                visited[next_vertex] = true;
                queue.push(next_vertex);
            }
        }
    }

    return order;
}
