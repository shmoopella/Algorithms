#include "s21_ant.h"

Ant::Ant() {
    alpha = 1;
    beta = 2;
    evaporation = 0.36;
    init_pheromone_value = 0.2;
}

Ant::Ant(int a, int b, double e, double ipv) {
    if (a <= 0 || b <= 0 || e <= 0 || e >= 1 || ipv <= 0 || ipv >= 1) {
        throw std::logic_error("Alpha and beta must be more then 0. "
                               "Evaporation and init pheromone value must be between 0 and 1.");
    }
    this->alpha = a;
    this->beta = b;
    this->evaporation = e;
    this->init_pheromone_value = ipv;
}

TsmResult Ant::iteration(Graph &graph) {
    for (int i = 0; i < graph.Size(); ++i) {  //  i == one ant
        TsmResult tsmResult;
        tsmResult.distance = 0;
        tsmResult.vertices.push_back(i + 1);  //  (i + 1) cos all vertexes counts from 1 not from 0
        std::vector<int> visited_vertexes;
        visited_vertexes.push_back(i + 1);  //  (i + 1) cos all vertexes counts from 1 not from 0
        int current_start_vertex = i;
        bool isBadPath;
        while (visited_vertexes.size() < (size_t) graph.Size() && !isBadPath) {  //  for one vertex of one ant
            double current_probability;
            double sum_of_previous_probabilities = 0.0;
            std::vector<double> probabilities_line;
            std::vector<int> probability_vertexes_line;
            isBadPath = true;
            double sum_of_probability_coefficients = sumOfProbabilityCoefficients(graph, visited_vertexes,
                                                                                  current_start_vertex);
            for (int j = 0; j < graph.Size(); ++j) {
                if (current_start_vertex == j || graph(current_start_vertex + 1, j + 1) == 0
                    || (std::find(visited_vertexes.begin(), visited_vertexes.end(), j + 1) !=
                        visited_vertexes.end()))  //  vertex is not visited yet
                    continue;
                isBadPath = false;
                double l = 1 / graph(i + 1, j + 1);
                current_probability = std::pow(pheromones[i][j], alpha) * std::pow(l, beta)
                                      / sum_of_probability_coefficients;
                probabilities_line.push_back(sum_of_previous_probabilities + current_probability);
                probability_vertexes_line.push_back(j);
            }
            if (isBadPath) break;
            double random_probability = getRandomProbability();
            for (size_t j = 0; j < probabilities_line.size(); ++j) {
                if (random_probability <= probabilities_line[j]) {
                    tsmResult.vertices.push_back(probability_vertexes_line[j] + 1);
                    tsmResult.distance += graph(current_start_vertex + 1, probability_vertexes_line[j] + 1);
                    visited_vertexes.push_back(probability_vertexes_line[j] + 1);
                    current_start_vertex = probability_vertexes_line[j];
                    break;
                }
            }
        }
        if (graph(visited_vertexes.back(), i + 1) == 0) {  //  cos all vertexes counts from 1 not from 0
            isBadPath = true;
            break;
        }
        tsmResult.vertices.push_back(i + 1);  //  cos all vertexes counts from 1 not from 0
        tsmResult.distance += graph(visited_vertexes.back(), i + 1);  //  cos all vertexes counts from 1 not from 0
        if (!isBadPath && (minTsmResult.distance == 0 || tsmResult.distance < minTsmResult.distance)) {
            for (size_t j = 0; j < tsmResult.vertices.size(); ++j) {
                minTsmResult.vertices[j] = tsmResult.vertices[j];
            }
            minTsmResult.distance = tsmResult.distance;
        }
    }
    updatePheromones(graph);
    return minTsmResult;
}

void Ant::initPheromones(Graph &graph) {
    std::vector<double> pheromones_row;
    for (int i = 0; i < graph.Size(); ++i) {
        pheromones_row.push_back(init_pheromone_value);
    }
    for (int i = 0; i < graph.Size(); ++i) {
        pheromones.push_back(pheromones_row);
        pheromones[i][i] = 0;
    }
}

double Ant::sumOfProbabilityCoefficients(Graph &graph, std::vector<int> visited_vertexes, int current_start_vertex) {
    double sum_of_probability_coefficients = 0.0;
    for (int j = 0; j < graph.Size(); ++j) {
        if (current_start_vertex == j || graph(current_start_vertex + 1, j + 1) == 0
            || (std::find(visited_vertexes.begin(), visited_vertexes.end(), j + 1) !=
                visited_vertexes.end()))   //  cos all vertexes counts from 1 not from 0
            continue;
        double l = 1 / graph(current_start_vertex + 1, j + 1);
        sum_of_probability_coefficients += std::pow(pheromones[current_start_vertex][j], alpha)
                                           * std::pow(l,
                                                      beta);    //  (probability_vertexes_line[j] + 1) cos all vertexes counts from 1 not from 0
    }
    return sum_of_probability_coefficients;
}

double Ant::getRandomProbability() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double generated_number = dis(gen);
    return generated_number;
}

void Ant::updatePheromones(Graph &graph) {
    double q = averageDistanceBetweenVertices(graph) / 10;
    for (size_t i = 0; i < pheromones.size(); ++i) {
        for (size_t j = 0; j < pheromones.size(); ++j) {
            if (i == j) {
                continue;
            }
            pheromones[i][j] *= 1 - evaporation;
            pheromones[i][j] += q / graph(i + 1, j + 1);
        }
    }
}

double Ant::averageDistanceBetweenVertices(Graph &graph) {
    double sum_of_distance_between_vertices = 0;
    int not_zero_vertices = 0;
    for (int i = 0; i < graph.Size(); ++i) {
        for (int j = 0; j < graph.Size(); ++j) {
            if (graph(i + 1, j + 1) != 0) {  //  cos all vertexes counts from 1 not from 0
                sum_of_distance_between_vertices += graph(i + 1, j + 1);
                not_zero_vertices++;
            }
        }
    }
    return sum_of_distance_between_vertices / not_zero_vertices;
}

void Ant::initMinTsmResult(Graph &graph) {
    for (int i = 0; i <= graph.Size(); ++i) {  //  <= graph.Size() cos we go back to first vertex
        minTsmResult.vertices.push_back(0);
    }
    minTsmResult.distance = 0;
}