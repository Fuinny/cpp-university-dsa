#include "graph.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    Graph graph(10);

    graph.add(5, 3);
    graph.add(5, 8);
    graph.add(5, 9);
    graph.add(3, 7);
    graph.add(3, 4);
    graph.add(4, 2);
    graph.add(2, 6);
    graph.add(8, 1);

    std::vector<std::size_t> dfs_order = graph.DFS(5);
    std::cout << "DFS: ";
    for (std::size_t v : dfs_order) {
        std::cout << v << " ";
    }

    std::vector<std::size_t> bfs_order = graph.BFS(5);
    std::cout << "\nBFS: ";
    for (std::size_t v : bfs_order) {
        std::cout << v << " ";
    }

    return 0;
}
