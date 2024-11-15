#ifndef A2_SIMPLENAVIGATOR_V1_0_1_S21_ANT_H
#define A2_SIMPLENAVIGATOR_V1_0_1_S21_ANT_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include <random>
#include <algorithm>

#include "../graph/s21_graph.h"

struct TsmResult {
    std::vector<int> vertices;    // массив с искомым маршрутом (с порядком обхода вершин). Вместо int* можно использовать std::vector<int>
    double distance;  // длина этого маршрута
};

class Ant {
public:
    Ant();  // Default constructor
    Ant(int a, int b, double e, double ipv);  // Constructor with param
    void initPheromones(Graph &graph);

    void initMinTsmResult(Graph &graph);

    TsmResult iteration(Graph &graph);

private:
    int alpha;  //  coefficient alpha
    int beta;  //  coefficient beta
    double evaporation;  //  coefficient of evaporation
    std::vector <std::vector<double>> pheromones;
    double init_pheromone_value;


    void updatePheromones(Graph &graph);

    double averageDistanceBetweenVertices(Graph &graph);

    double sumOfProbabilityCoefficients(Graph &graph, std::vector<int> visited_vertexes, int current_start_vertex);

    double getRandomProbability();

    TsmResult minTsmResult;
};

#endif //A2_SIMPLENAVIGATOR_V1_0_1_S21_ANT_H
