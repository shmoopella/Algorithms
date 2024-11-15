#include "s21_graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
    if (start_vertex > graph.Size() || start_vertex <= 0) {
        throw std::logic_error("The start vertex is wrong!");
    }
    std::vector<int> dfs_result;
    s21::stack<int> stack;
    std::vector<Color> visited(graph.Size(), Color::w);
    int current_vertex;
    stack.push(start_vertex);

    while (!stack.empty()) {
        current_vertex = stack.top();
        if (visited[current_vertex - 1] == Color::w) {
            std::vector<double> adj_vertices = graph.GetAdjacencyVertices(current_vertex);
            dfs_result.push_back(current_vertex);
            visited[current_vertex - 1] = Color::g;

            for (std::size_t neighbor = 0; neighbor < adj_vertices.size(); neighbor++) {
                if (adj_vertices[neighbor] && visited[neighbor] == Color::w) {
                    stack.push(neighbor + 1);
                }
            }
        } else if (visited[current_vertex - 1] == Color::g) {
            visited[current_vertex - 1] = Color::b;
            stack.pop();
        } else if (visited[current_vertex - 1] == Color::b) {
            stack.pop();
        }
    }
    return dfs_result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int start_vertex) { //doesn`t work!!!!!!!!!!!!!!!!!
    if (start_vertex > graph.Size() || start_vertex <= 0) {
        throw std::logic_error("The start vertex is wrong!");
    }
    std::vector<int> bfs_result;
    s21::queue<int> queue;
    std::vector<Color> visited(graph.Size(), Color::w);
    int current_vertex;
    queue.push(start_vertex);

    while (!queue.empty()) {
        current_vertex = queue.front();
        if (visited[current_vertex - 1] == Color::w) {
            std::vector<double> adj_vertices = graph.GetAdjacencyVertices(current_vertex);
            bfs_result.push_back(current_vertex);
            visited[current_vertex - 1] = Color::g;

            for (std::size_t neighbor = 0; neighbor < adj_vertices.size(); neighbor++) {
                if (adj_vertices[neighbor] && visited[neighbor] == Color::w) {
                    queue.push(neighbor + 1);
                }
            }
        } else if (visited[current_vertex - 1] == Color::g) {
            visited[current_vertex - 1] = Color::b;
            queue.pop();
        } else if (visited[current_vertex - 1] == Color::b) {
            queue.pop();
        }
    }
    return bfs_result;
}


int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    int graph_size = graph.Size();
    if (!graph_size) {
        throw std::logic_error("The graph is empty!");
    }
    if (vertex1 <= 0 || vertex1 > graph_size || vertex2 <= 0 || vertex2 > graph_size) {
        throw std::logic_error("The vertex is incorrect!");

    }

    graph_size++; // для корректной работы с вершинами от 1
    std::vector<float> distances(graph_size, INFINITY);
    distances[vertex1] = 0;
    std::vector<bool> used(graph_size, false);
    float min_dist = 0;
    float min_vertex = vertex1;
    while (min_dist < INFINITY) {
        int i = min_vertex;
        std::vector<double> adj_vertices = graph.GetAdjacencyVertices(i);
        used[i] = true;
        for (int j = 1; j < graph_size; ++j) {
            if (adj_vertices[j - 1]) {
                if (distances[i] + graph(i, j) < distances[j])
                    distances[j] = distances[i] + graph(i, j);
            }
        }
        min_dist = INFINITY;
        for (int j = 1; j < graph_size; ++j)
            if (!used[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                min_vertex = j;
            }
    }
    return distances[vertex2];
}

std::vector<std::vector<double>> GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
    int graph_size = graph.Size();
    std::vector<std::vector<double>> shortest_paths(graph_size, std::vector<double>(graph_size, INFINITY));
    for (int src = 1; src <= graph_size; src++) {
        for (int dest = 1; dest <= graph_size; dest++) {
            if (src == dest) {
                shortest_paths[src - 1][dest - 1] = 0;
            } else if (graph(src, dest)) {
                shortest_paths[src - 1][dest - 1] = graph(src, dest);
            }
        }
    }

    for (int k = 0; k < graph_size; k++) {
        for (int src = 0; src < graph_size; src++) {
            for (int dest = 0; dest < graph_size; dest++) {
                if (shortest_paths[src][k] < INFINITY && shortest_paths[k][dest] < INFINITY)
                    if (shortest_paths[src][dest] > shortest_paths[src][k] + shortest_paths[k][dest]) {
                        shortest_paths[src][dest] = shortest_paths[src][k] + shortest_paths[k][dest];
                    }
            }
        }
    }
    return shortest_paths;
}


std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
    int graph_size = graph.Size();
    if (!graph_size) {
        throw std::logic_error("The graph is empty!");
    }

    std::vector<bool> visited(graph_size, false);
    std::vector<std::vector<int>> spanning_tree(graph_size, std::vector<int>(graph_size, 0));
    int count_added_vertices = 1;
    float min_edge;
    int pos_i = 0;
    int pos_j = 0;
    visited[0] = true;

    while (count_added_vertices < graph_size) {
        bool flag = false;
        min_edge = INFINITY;
        for (int i = 1; i <= graph_size; i++) {
            for (int j = 1; j <= graph_size; j++) {
                if (graph(i, j) && visited[i - 1] && !visited[j - 1] && graph(i, j) < min_edge) {
                    flag = true;
                    min_edge = graph(i, j);
                    pos_i = i - 1;
                    pos_j = j - 1;
                }
            }
        }
        if (flag) {
            spanning_tree[pos_i][pos_j] = min_edge;
            spanning_tree[pos_j][pos_i] = min_edge;
            count_added_vertices++;
            visited[pos_j] = true;
        } else {
            throw std::logic_error("The graph is disconnected!");
        }
    }
    return spanning_tree;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
    TsmResult tsmResult;
    int a = 1;
    int b = 1;
    double e = 0.5;
    double ipv = 0.001;
    try {
        Ant ant = Ant(a, b, e, ipv);

        ant.initPheromones(graph);
        ant.initMinTsmResult(graph);

        double previous_iteration_tsm_result = 0;
        int tsm_unchange_counter = 0;
        while (true) {
            tsmResult = ant.iteration(graph);
            if (previous_iteration_tsm_result == tsmResult.distance)
                tsm_unchange_counter++;
            if (tsm_unchange_counter == 100)
                break;
            previous_iteration_tsm_result = tsmResult.distance;
        }
    } catch (...) {
        std::cout << "Поданы некорректные данные в GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph).\n";
    }

    return tsmResult;
}