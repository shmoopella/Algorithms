#include "s21_graph.h"

const S21Matrix &Graph::get_adjacency_matrix() const {
    if (!adjacency_matrix_ptr_) {
        throw std::logic_error("Adjacency matrix is not initialized");
    }
    return *adjacency_matrix_ptr_;
}

std::vector<double> Graph::GetAdjacencyVertices(int numVertex) {
    if (!adjacency_matrix_ptr_) {
        throw std::logic_error("The graph is empty!");
    }
    std::vector<double> adjacency_vertices;
    for (int i = 0; i < size_; i++) {
        adjacency_vertices.push_back((*adjacency_matrix_ptr_)(numVertex - 1, i));
    }
    return adjacency_vertices;
}

void Graph::IsGraphWeighted() {
    for (int row = 0; row < size_; row++) {
        for (int col = 0; col < size_; col++) {
            if ((*adjacency_matrix_ptr_)(row, col) != 1 && (*adjacency_matrix_ptr_)(row, col) != 0) {
                this->weight_ = true;
                return;
            }
        }
    }
}

void Graph::CleanGraph() {
    if (this->adjacency_matrix_ptr_) {
        delete this->adjacency_matrix_ptr_;
        this->size_ = 0;
        this->direction_ = false;
        this->weight_ = false;
        this->adjacency_matrix_ptr_ = nullptr;
    }
}


double Graph::operator()(int src, int dest) const {
    if (src <= 0 || src > size_ || dest <= 0 || dest > size_) {
        throw std::logic_error("The vertex is incorrect!");
    }
    return (*this->adjacency_matrix_ptr_)(src - 1, dest - 1);
}


double &Graph::operator()(int src, int dest) {
    if (src <= 0 || src > size_ || dest <= 0 || dest > size_) {
        throw std::logic_error("The vertex is incorrect!");
    }
    return (*this->adjacency_matrix_ptr_)(src - 1, dest - 1);
}


void Graph::LoadGraphFromFile(std::string filename) {
    std::ifstream input_stream;
    int input_num;
    input_stream.open(filename, std::ios::in);
    if (!input_stream.is_open()) {
        throw std::ios_base::failure("Couldn`t open the file");
    }
    if (this->adjacency_matrix_ptr_) {
        CleanGraph();
    }
    input_stream >> size_;
    if (!input_stream.good()) {
        throw std::ios_base::failure("Wrong file format or the file is empty");
    }
    adjacency_matrix_ptr_ = new S21Matrix(size_, size_);
    for (int row = 0; row < size_; row++) {
        for (int col = 0; col < size_; col++) {
            input_stream >> input_num;
            if (input_stream.fail()) {
                CleanGraph();
                throw std::ios_base::failure("Wrong file format");
            } else {
                (*adjacency_matrix_ptr_)(row, col) = input_num;
            }
        }
    }
    this->IsGraphWeighted();
    input_stream.close();
}


void Graph::ExportGraphToDot(std::string filename) {
    if (!adjacency_matrix_ptr_) {
        throw std::logic_error("The graph is empty!");
    }
    std::ofstream output_stream(filename, std::ios::app);
    if (!output_stream.is_open()) {
        throw std::ios_base::failure("Couldn`t open the file");
    }

    output_stream << (this->direction_ ? "digraph " : "graph ") << "graphname {\n";

    for (int row = 0; row < size_; row++) {
        for (int col = 0; col < size_; col++) {
            if ((*adjacency_matrix_ptr_)(row, col)) {
                output_stream << row + 1;
                output_stream << (this->direction_ ? " -> " : " -- ") << col + 1;
                if (this->weight_) {
                    output_stream << "[label=" << (*adjacency_matrix_ptr_)(row, col) << "];\n";
                } else {
                    output_stream << ";\n";
                }
            }
        }
    }
    output_stream << "}";
    output_stream.close();
}
