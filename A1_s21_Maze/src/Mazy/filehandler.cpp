#include "filehandler.h"

void FileHandler::ParseMazeFromFile(const std::string &fileName,
                                    const std::string currentDir) {
  (void)currentDir;

  maze_->Clear();

  std::ifstream file(fileName);
  std::vector<std::string> file_lines_vector;

  if (!file.is_open()) {
    std::cout << "Не удалось открыть файл\n";
    std::cout << std::filesystem::current_path().string();
    return;
  }

  try {
    std::string line;
    while (std::getline(file, line)) {
        file_lines_vector.push_back(line);
    }

    file.close();
    int rows = 0;
    int cols = 0;
    std::istringstream current_line { file_lines_vector[0] };
      current_line >> rows;
      current_line >> cols;

    if (rows > 50 || cols > 50) {
      throw std::invalid_argument(
          "Matrix size exceeds the maximum limit of 50x50");
    }

    maze_->setRows(rows);
    maze_->setCols(cols);

    ParseRightAndBottomMatrixes(file_lines_vector, rows);
  } catch(...) {
    return;
  }
}

void FileHandler::ParseRightAndBottomMatrixes(std::vector<std::string> fileLinesVector,
                                              int rows) {
  try {
    std::string substring;
    int num;
    for (int i = 1; i <= rows; i++) {
      std::istringstream current_line_right { fileLinesVector[i] };
      while (current_line_right >> num) {
        if (num== 1) {
          maze_->walls.push_back(RightWall);
        } else if (num == 0) {
          maze_->walls.push_back(NoWalls);
        }
      }
    }

    int cellsCounter = 0;
    for (int i = rows + 2; i < (int) fileLinesVector.size() - 1; i++) {
      std::istringstream current_line_bottom { fileLinesVector[i] };
      if (maze_->walls.empty()) {
          return;
        }
      while (current_line_bottom >> substring) {
          if (substring == "1") {
            if (maze_->walls[cellsCounter] == NoWalls) {
              maze_->walls[cellsCounter] = BottomWall;
            } else {
              maze_->walls[cellsCounter] = RightAndBottomWalls;
            }
          }
          cellsCounter++;
        }
    }
  } catch(...) {
      return;
  }
}
