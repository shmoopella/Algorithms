#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <sstream>

#include <filesystem>

#include "maze.h"

class FileHandler {
 private:
  Maze *maze_;

 public:
  FileHandler(Maze *maze) : maze_(maze) {}
  void ParseMazeFromFile(const std::string &fileName, const std::string currentDir);
  void ParseRightAndBottomMatrixes(std::vector<std::string> fileLinesList, int rows);
};

#endif  // FILEHANDLER_H
