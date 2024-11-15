#ifndef A2_SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_
#define A2_SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_

#include <vector>
#include <queue>

#include "stack/s21_stack.h"
#include "queue/s21_queue.h"
#include "s21_ant.h"


enum class Color {
    w, g, b
};
// белый —  мы ещё не посещали и даже не встречали этот узел;
// серый —  мы встречали этот узел в качестве соседа и уже добавили его в nodes_storage, но ещё не посещали его;
// чёрный  —  этот узел посещён и больше не нуждается в анализе.

class GraphAlgorithms {
public:
    GraphAlgorithms() = default;

    ~GraphAlgorithms() = default;

    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

    std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

    int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);

    std::vector <std::vector<double>> GetShortestPathsBetweenAllVertices(Graph &graph);

    std::vector <std::vector<int>> GetLeastSpanningTree(Graph &graph);

    TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};

#endif  // A2_SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_
