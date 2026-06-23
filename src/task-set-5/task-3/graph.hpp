#pragma once

#include <cstddef>
#include <utility>
#include <vector>

class Graph {
public:
    using edge = std::pair<int, std::size_t>;
    explicit Graph(std::size_t size);
    void add_edge(std::size_t from_vertex, std::size_t to_vertex, int weight);
    void prim(std::size_t start_vertex) const;
    void kruskal() const;
private:
    std::vector<std::vector<edge>> adjacency_list;
};
