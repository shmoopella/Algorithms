#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <list>
#include <vector>
#include <iostream>

#include "maze.h"

enum SolutionPathLines {
  NoPathLine = 0,
  LeftHorizontalPathLine = 1,
  RightHorizontalPathLine = 2,
  UpVerticalPathLine = 3,
  DownVerticalPathLine = 4
};

class MazeSolver {
 private:
  Maze *maze_;

 public:
  MazeSolver(Maze *maze) : maze_(maze) {}

  std::vector<int> maze_solution{};
  std::vector<int> shortest_solution_path{};

  void SolveMaze(int starX, int startY, int endX, int endY);
  void Clear();
  int ConvertXYtoI(int x, int y);
  std::pair<int, int> ConvertItoXY(int i);
  std::list<int> NeighborCellsCheck(int currentI, int step, std::list<int> list);
  void FillShortestSolutionPath(int endX, int endY);
};

#endif  // MAZESOLVER_H
