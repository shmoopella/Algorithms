#include <gtest/gtest.h>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(GraphTest, ConstructorTest) {
    Graph graph;
    EXPECT_FALSE(graph.get_direction());
    EXPECT_FALSE(graph.get_weight());
}

TEST(GraphTest, SetTest) {
    Graph graph;
    graph.set_direction(true);
    graph.set_weight(true);
    EXPECT_TRUE(graph.get_direction());
    EXPECT_TRUE(graph.get_weight());
}

TEST(GraphTest, LoadFileTest) {
    Graph graph;
    S21Matrix expected_matrix(3, 3);
    expected_matrix(0, 0) = 0;
    expected_matrix(0, 1) = 1;
    expected_matrix(0, 2) = 1;
    expected_matrix(1, 0) = 1;
    expected_matrix(1, 1) = 0;
    expected_matrix(1, 2) = 0;
    expected_matrix(2, 0) = 1;
    expected_matrix(2, 1) = 0;
    expected_matrix(2, 2) = 0;
    EXPECT_ANY_THROW(graph.LoadGraphFromFile("assets/graph_example.txt"));
    EXPECT_ANY_THROW(graph.LoadGraphFromFile("assets/wrong_num_vert.txt"));
    EXPECT_ANY_THROW(graph.LoadGraphFromFile("assets/wrong_data.txt"));
    EXPECT_ANY_THROW(graph.LoadGraphFromFile("assets/empty_file.txt"));
    graph.LoadGraphFromFile("assets/graph2.txt");
    EXPECT_TRUE(graph.get_adjacency_matrix().EqMatrix(expected_matrix));
    EXPECT_EQ(graph.Size(), 3);
    EXPECT_FALSE(graph.get_direction());
    EXPECT_FALSE(graph.get_weight());
}

TEST(GraphTest, ExportFileTest) {
    Graph graph;
    EXPECT_ANY_THROW(graph.ExportGraphToDot("test.dot"));
    graph.LoadGraphFromFile("assets/graph2.txt");
    EXPECT_NO_THROW(graph.ExportGraphToDot("test.dot"));
    std::ifstream exported_dot_stream("test.dot");
    std::stringstream exported_dot_content;
    exported_dot_content << exported_dot_stream.rdbuf();
    const std::string expected_dot_content = "graph graphname {\n1 -- 2;\n1 -- 3;\n2 -- 1;\n3 -- 1;\n}";
    EXPECT_EQ(exported_dot_content.str(), expected_dot_content);
}

TEST(GraphTest, ExportDirFileTest) {
    Graph graph;
    graph.LoadGraphFromFile("assets/weighted_graph3.txt");
    graph.ExportGraphToDot("test2.dot");
    std::ifstream exported_dot_stream("test2.dot");
    std::stringstream exported_dot_content;
    exported_dot_content << exported_dot_stream.rdbuf();
    const std::string expected_dot_content = "graph graphname {\n1 -- 2[label=5];\n1 -- 3[label=2];\n2 -- 1[label=1];\n3 -- 1[label=3];\n}";
    EXPECT_EQ(exported_dot_content.str(), expected_dot_content);
}

TEST(AlgorithmsTest, DepthFirstSearchTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    std::vector<int> expected_res {1, 5, 4, 2, 3, 7, 6};
    EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 5));
    graph.LoadGraphFromFile("assets/graph7.txt");
    EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 8));
    EXPECT_ANY_THROW(algorithms.DepthFirstSearch(graph, 0));
    EXPECT_EQ(expected_res, algorithms.DepthFirstSearch(graph, 1));
}

TEST(AlgorithmsTest, BreadthFirstSearchTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    std::vector<int> expected_res {1, 2, 3, 4, 5, 6, 7};
    EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 5));
    graph.LoadGraphFromFile("assets/graph7.txt");
    EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 10));
    EXPECT_ANY_THROW(algorithms.BreadthFirstSearch(graph, -2));
    EXPECT_EQ(expected_res, algorithms.BreadthFirstSearch(graph, 1));
}

TEST(AlgorithmTest, GetShortestPathBetweenVerticesTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 1, 3));
    graph.LoadGraphFromFile("assets/weighted_graph7.txt");
    EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 0, 2));
    EXPECT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 2, 9));
    EXPECT_EQ(algorithms.GetShortestPathBetweenVertices(graph, 4, 6), 10);
}

TEST(AlgorithmTest, GetShortestPathsBetweenAllVerticesTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    std::vector<std::vector<double>> expected_res {
        {0, 5, 10, 8}, {5, 0, 5, 3}, {3, 8, 0, 11}, {2, 7, 5, 0}
    };
    std::vector<std::vector<double>> expected_res2 {
        {0, 3, 5, 7, 8, 11, 20}, {3, 0, 2, 6, 5, 10, 19}, {5, 2, 0, 8, 7, 12, 21}, {7, 6, 8, 0, 1, 4, 13}, 
        {8, 5, 7, 1, 0, 5, 14}, {11, 10, 12, 4, 5, 0, 9}, {20, 19, 21, 13, 14, 9, 0}
    };

    graph.LoadGraphFromFile("assets/weighted_graph4.txt");
    graph.set_direction(true);
    EXPECT_EQ(expected_res, algorithms.GetShortestPathsBetweenAllVertices(graph));
    graph.LoadGraphFromFile("assets/weighted_graph.txt");
    EXPECT_FALSE(graph.get_direction());
    EXPECT_TRUE(graph.get_weight());
    graph.set_direction(true);
    EXPECT_EQ(expected_res2, algorithms.GetShortestPathsBetweenAllVertices(graph));
}

TEST(AlgorithmTest, GetLeastSpanningTreeTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    std::vector<std::vector<int>> expected_res { {0, 1, 0, 0}, {1, 0, 2, 2}, {0, 2, 0, 0}, {0, 2, 0, 0} };
    graph.LoadGraphFromFile("assets/weighted_undir_graph4.txt");
    EXPECT_EQ(expected_res, algorithms.GetLeastSpanningTree(graph));
    graph.LoadGraphFromFile("assets/weighted_disconnected_graph4.txt");
    EXPECT_ANY_THROW(algorithms.GetLeastSpanningTree(graph));
}

TEST(AlgorithmTest, SolveAntTest) {
    Graph graph;
    GraphAlgorithms algorithms;
    graph.LoadGraphFromFile("assets/graph.txt");
    EXPECT_NO_THROW(algorithms.SolveTravelingSalesmanProblem(graph));
}