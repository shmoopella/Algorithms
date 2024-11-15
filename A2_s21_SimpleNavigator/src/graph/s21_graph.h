#ifndef A2_SIMPLE_NAVIGATOR_GRAPH_S21_GRAPH_H_
#define A2_SIMPLE_NAVIGATOR_GRAPH_S21_GRAPH_H_


#include <string>
#include <ios>
#include <iostream>
#include <fstream>
#include<vector>

#include "matrix/s21_matrix_oop.h"

class Graph {
public:
    Graph() : adjacency_matrix_ptr_(nullptr), size_(0), direction_(false), weight_(false) {};

    ~Graph() {
        CleanGraph();
    };

    double operator()(int src, int dest) const;

    double &operator()(int src, int dest);

    void CleanGraph();

    const S21Matrix &get_adjacency_matrix() const; // нужен только в тестах

    void set_direction(bool direction) { direction_ = direction; };

    void set_weight(bool weight) { weight_ = weight; };

    bool get_direction() { return direction_; };

    bool get_weight() { return weight_; };

    std::vector<double> GetAdjacencyVertices(int numVertex);

    int Size() { return size_; };

    void LoadGraphFromFile(std::string filename); // загрузка графа из файла в формате матрицы смежности
    void ExportGraphToDot(std::string filename); // выгрузка графа в файл в формате dot

private:
    S21Matrix *adjacency_matrix_ptr_;
    int size_;
    bool direction_;
    bool weight_;

    void IsGraphWeighted();
};

#endif  // A2_SIMPLE_NAVIGATOR_GRAPH_S21_GRAPH_H_
