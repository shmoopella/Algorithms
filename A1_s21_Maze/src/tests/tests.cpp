#include <gtest/gtest.h>

#include <filesystem>

#include "../Mazy/filehandler.h"
#include "../Mazy/maze.h"
#include "../Mazy/mazesolver.h"
#include "../Mazy/generationperfectmaze.h"


TEST(MazeTest, Maze) {
    Maze maze = Maze();
    maze.setRows(1);
    maze.setCols(1);
    ASSERT_EQ(maze.getRows(), 1);
    ASSERT_EQ(maze.getCols(), 1);
    
    maze.Clear();
    ASSERT_EQ(maze.getRows(), 0);
    ASSERT_EQ(maze.getCols(), 0);
    ASSERT_ANY_THROW(Maze(51, 51));
    ASSERT_THROW(Maze(51, 51), std::invalid_argument);
}

TEST(MazeTest, FileHandler) {
    Maze maze = Maze();
    FileHandler file_handler = FileHandler(&maze);
    ASSERT_EQ(maze.getRows(), 0);
    ASSERT_EQ(maze.getCols(), 0);

    file_handler.ParseMazeFromFile("assets/44.txt", "");
    ASSERT_EQ(maze.getRows(), 4);
    ASSERT_EQ(maze.getCols(), 4);
    ASSERT_EQ(maze.walls[0], 2);
    ASSERT_EQ(maze.walls[9], 3);
}

 TEST(MazeTest, MazeSolver) {
     Maze maze = Maze();
     FileHandler file_handler = FileHandler(&maze);
     file_handler.ParseMazeFromFile("assets/44.txt", "");
     MazeSolver maze_solver = MazeSolver(&maze);

     maze_solver.SolveMaze(0, 0, 3, 3);
     maze_solver.FillShortestSolutionPath(3, 3);
     ASSERT_EQ(maze_solver.shortest_solution_path[0], 1);
     ASSERT_EQ(maze_solver.shortest_solution_path[4], 0);

     maze_solver.Clear();
     ASSERT_EQ(maze_solver.maze_solution.size(), 0);
     ASSERT_EQ(maze_solver.shortest_solution_path.size(), 0);
 }

TEST(PerfectMazeTests, RowColsTest) {
    PerfectMaze maze(3, 3);
    maze.generateMazeFile();
    ASSERT_EQ(maze.getRows(), 3);
    ASSERT_EQ(maze.getCols(), 3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
