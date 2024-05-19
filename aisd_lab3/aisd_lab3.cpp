// aisd_lab3.cpp: определяет точку входа для приложения.
//

#include "aisd_lab3.h"

using namespace std;

int main()
{
    Graph<char, int> graph;

    // Добавление вершин и ребер в граф
    graph.add_vertex('A');
    graph.add_vertex('B');
    graph.add_vertex('C');
    graph.add_edge('A', 'B', 1);
    graph.add_edge('B', 'C', 2);
    graph.add_edge('A', 'C', 3);

    // Вызов метода обхода в глубину
    auto dfs_result = graph.walk('A');

    // Вывод результатов обхода
    for (const auto& vertex : dfs_result)
    {
        std::cout << vertex << " ";
    }
}
