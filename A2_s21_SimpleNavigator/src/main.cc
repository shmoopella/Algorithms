#include <cstdlib>
#include "graph_algorithms/s21_graph_algorithms.h"

void graphDownload(Graph &graph);

void depthSearch(Graph &graph);

void breadthSearch(Graph &graph);

void getShortestPathBetweenVertices(Graph &graph);

void getShortestPathsBetweenAllVertices(Graph &graph);

void getLeastSpanningTree(Graph &graph);

void solveTravelingSalesmanProblem(Graph &graph);

int main() {
    Graph graph = Graph();
    try {
        graphDownload(graph);
        depthSearch(graph);
        breadthSearch(graph);
        getShortestPathBetweenVertices(graph);
        getShortestPathsBetweenAllVertices(graph);
        getLeastSpanningTree(graph);
        solveTravelingSalesmanProblem(graph);
    } catch (...) {
        std::cout << "Поданы некорректные данные.\n";
    }

}

void graphDownload(Graph &graph) {
    std::cout << "\n1. Загрузка исходного графа из файла\n"
                 "Введите, пожалуйста путь к файлу от текущей директории (пример: assets/graph.txt).\n";
    std::string path;
    std::getline(std::cin, path);
    graph.LoadGraphFromFile(path);
    std::cout << "\nЗагрузка из файла завершена успешно!\n";
}

void depthSearch(Graph &graph) {
    std::cout << "\n2. Обход графа в ширину с выводом результата обхода в консоль\n"
                 "Введите, пожалуйста, значение вершины.\n";
    int vertex;
    std::cin >> vertex;
    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    std::vector<int> depthSearchResult = graphAlgorithms.DepthFirstSearch(graph, vertex);
    std::cout << "Результат:\n";
    for (int value: depthSearchResult) {
        std::cout << value << " ";
    }
}

void breadthSearch(Graph &graph) {
    std::cout << "\n3. Обход графа в глубину с выводом результата обхода в консоль\n"
                 "Введите, пожалуйста, значение вершины.\n";
    int vertex;
    std::cin >> vertex;
    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    std::vector<int> breadthSearchResult = graphAlgorithms.BreadthFirstSearch(graph, vertex);
    std::cout << "Результат:\n";
    for (int value: breadthSearchResult) {
        std::cout << value << " ";
    }
}

void getShortestPathBetweenVertices(Graph &graph) {
    std::cout << "\n4. Поиск кратчайшего пути между произвольными двумя вершинами с выводом результата в консоль\n"
                 "Введите, пожалуйста, значение вершины старта.\n";
    int startPoint;
    int endPoint;
    std::cin >> startPoint;
    std::cout << "Введите, пожалуйста, значение конечной вершины.\n";
    std::cin >> endPoint;

    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    int shortestPathBetweenVertices = graphAlgorithms.GetShortestPathBetweenVertices(graph, startPoint, endPoint);
    std::cout << "Результат: " << shortestPathBetweenVertices << "\n";
}

void getShortestPathsBetweenAllVertices(Graph &graph) {
    std::cout
            << "\n5. Поиск кратчайших путей между всеми парами вершин в графе с выводом результирующей матрицы в консоль\n"
               "Введите любой символ для старта.\n";
    int endPoint;
    std::cin >> endPoint;

    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    std::vector <std::vector<double>> resultMatrixShortestPaths = graphAlgorithms.GetShortestPathsBetweenAllVertices(
            graph);
    for (std::vector<double> value: resultMatrixShortestPaths) {
        for (double i: value) {
            std::cout << i << "  ";
        }
        std::cout << "\n";
    }
}

void getLeastSpanningTree(Graph &graph) {
    std::cout
            << "\n6. Поиск минимального остовного дерева в графе с выводом результирующей матрицы смежности в консоль\n"
               "Введите любой символ для старта.\n";
    int startPoint;
    std::cin >> startPoint;
    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    std::vector <std::vector<int>> resultMatrixSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    for (std::vector<int> value: resultMatrixSpanningTree) {
        for (int i: value) {
            std::cout << i << "  ";
        }
        std::cout << "\n";
    }
}

void solveTravelingSalesmanProblem(Graph &graph) {
    std::cout << "\n7. Решение задачи комивояжера с выводом результирующего маршрута и его длины в консоль\n"
                 "Введите, пожалуйста путь к файлу от текущей директории (пример: assets/graph.txt).\n";

    GraphAlgorithms graphAlgorithms = GraphAlgorithms();
    TsmResult tsmResult = graphAlgorithms.SolveTravelingSalesmanProblem(graph);
    if (tsmResult.distance != 0) {
        for (size_t i = 0; i < tsmResult.vertices.size(); ++i) {
            std::cout << "\nanswer: tsmResult.vertices[" << i << "] = " << tsmResult.vertices.at(i);
        }
        std::cout << "\nanswer: tsmResult.distance = " << tsmResult.distance << "\n";
    } else {
        std::cout << "При заданном графе решение задачи коммивояжёра невозможно.\n";
    }
}
