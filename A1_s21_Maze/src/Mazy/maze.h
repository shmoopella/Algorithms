#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>

enum Walls {
  NoWalls = 0,
  RightWall = 1,
  BottomWall = 2,
  RightAndBottomWalls = 3
};

class Maze {
 private:
  int rows_;
  int cols_;

 public:
  Maze() : rows_(0), cols_(0){};
  Maze(int rows, int cols) {
    if (rows > 50 || cols > 50) {
      throw std::invalid_argument("Maze size exceeds the maximum limit of 50x50\n");
    }
  };

  std::vector<int> walls{};

  int getRows() { return rows_; }
  int getCols() { return cols_; }
  void setRows(int rows) { rows_ = rows; }
  void setCols(int cols) { cols_ = cols; }
  void Clear();
};

#endif  // MAZE_H
