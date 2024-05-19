// aisd_lab3.cpp: определяет точку входа для приложения.
//

#include "aisd_lab3.h"

using namespace std;

int main()
{
    Graph<char, int> graph;

    // Добавление вершин
    graph.add_vertex('A');
    graph.add_vertex('B');
    graph.add_vertex('C');
    graph.add_vertex('D');
    graph.add_vertex('E');

    // Добавление ребер
    graph.add_edge( 'A', 'B', 5 );
    graph.add_edge( 'A', 'C', 3 );
    graph.add_edge('B', 'D', 2 );
    graph.add_edge('C', 'B', 1);
    graph.add_edge( 'C', 'D', 7 );
    graph.add_edge( 'D', 'E', 4);

    // Нахождение кратчайшего пути от вершины 'A' до вершины 'E'
    auto shortest_path = graph.shortest_path('A', 'E');

    // Вывод кратчайшего пути
    std::cout << "Shortest Path from A to E:" << std::endl;
    for (const auto& edge : shortest_path) {
        std::cout << edge.source << " -> " << edge.destination << " : " << edge.weight << std::endl;
    }

    return 0;
}
