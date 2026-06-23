#include "graph.hpp"

int main () {
    Graph graph(7); // Vertices from 1 to 6 (0 is unused in this example).

    graph.add_edge(1, 2, 20);
    graph.add_edge(1, 4, 30);
    graph.add_edge(1, 5, 70);
    graph.add_edge(1, 6, 30);

    graph.add_edge(2, 1, 20);
    graph.add_edge(2, 4, 20);
    graph.add_edge(2, 5, 100);

    graph.add_edge(3, 6, 20);
    graph.add_edge(3, 5, 40);
    graph.add_edge(3, 4, 70);

    graph.add_edge(4, 2, 20);
    graph.add_edge(4, 1, 30);
    graph.add_edge(4, 3, 70);

    graph.add_edge(5, 1, 70);
    graph.add_edge(5, 2, 100);
    graph.add_edge(5, 6, 30);
    graph.add_edge(5, 3, 40);

    graph.add_edge(6, 5, 30);
    graph.add_edge(6, 1, 30);
    graph.add_edge(6, 3, 20);

    graph.prim(5);

    return 0;
}
