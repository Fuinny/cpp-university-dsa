#pragma once

#include <cstddef>
#include <vector>

class Graph {
public:
    explicit Graph(std::size_t size);
    void add(std::size_t from_vertex, std::size_t to_vertex);
    std::vector<std::size_t> DFS(std::size_t start) const;
    std::vector<std::size_t> BFS(std::size_t start) const;
private:
    std::vector<std::vector<std::size_t>> adjacency_list;
};
