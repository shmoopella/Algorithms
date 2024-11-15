#include "mazesolver.h"

void MazeSolver::SolveMaze(int startX, int startY, int endX, int endY) {
  Clear();

  if (maze_ == nullptr) return;

  try {
    // fill mazeSolution default values == -1
    for (int i = 0; i < (int) maze_->walls.size(); i++) {
      maze_solution.push_back(-1);
    }

    // convert start & end coordinates to wall's indexes
    int startI = ConvertXYtoI(startX, startY);
    int endI = ConvertXYtoI(endX, endY);

    // current cell & step
    int currentI;
    maze_solution[startI] = 0;
    int step = 1;

    std::list<int> listLastSteps;
    std::list<int> temporaryList;

    // add start point to listLastSteps
    listLastSteps.push_back(startI);

    // looking for endI
    while (maze_solution[endI] == -1) {
      while (!listLastSteps.empty()) {
        currentI = listLastSteps.back();
        listLastSteps.pop_back();
        temporaryList = NeighborCellsCheck(currentI, step, temporaryList);
      }
      step++;
      listLastSteps = temporaryList;

      if (listLastSteps.empty()) {
        std::cerr << "Подан некорректный файл (listLastSteps.isEmpty())";
        return;
      }

      temporaryList.clear();
    }
  } catch (...) {
    std::cerr << "Подан некорректный файл (seg fault)";
  }
}

void MazeSolver::Clear() {
  maze_solution.clear();
  shortest_solution_path.clear();
}

int MazeSolver::ConvertXYtoI(int x, int y) {
  if (x == 0) {
    return y;
  } else {
    return x * maze_->getCols() + y;
  }
}

std::pair<int, int> MazeSolver::ConvertItoXY(int i) {
  if (i < maze_->getCols()) {
    return {0, i};
  } else {
    return {i / maze_->getCols(), i % maze_->getCols()};
  }
}

std::list<int> MazeSolver::NeighborCellsCheck(int currentI, int step,
                                          std::list<int> list) {
  int currentX = ConvertItoXY(currentI).first;
  int currentY = ConvertItoXY(currentI).second;
  int onLeft;
  int onRight;
  int onUp;
  int onDown;

  onLeft = ConvertXYtoI(currentX, currentY - 1);
  if ((currentI != 0) && (currentI % maze_->getCols() != 0) &&
      (maze_->walls[currentI - 1] != RightWall) &&
      (maze_->walls[currentI - 1] != RightAndBottomWalls) &&
      (maze_solution[onLeft] == -1)) {
    maze_solution[onLeft] = step;
    list.push_back(onLeft);
  }

  onRight = ConvertXYtoI(currentX, currentY + 1);
  if ((maze_->walls[currentI] != RightWall) &&
      (maze_->walls[currentI] != RightAndBottomWalls) &&
      ((currentI + 1) % maze_->getCols() != 0) &&
      (maze_solution[onRight] == -1)) {
    maze_solution[onRight] = step;
    list.push_back(onRight);
  }

  onUp = ConvertXYtoI(currentX - 1, currentY);
  if ((currentI >= maze_->getCols()) &&
      (maze_->walls[currentI - maze_->getCols()] != BottomWall) &&
      (maze_->walls[currentI - maze_->getCols()] != RightAndBottomWalls) &&
      (maze_solution[onUp] == -1)) {
    maze_solution[onUp] = step;
    list.push_back(onUp);
  }

  onDown = ConvertXYtoI(currentX + 1, currentY);
  if ((maze_->walls[currentI] != BottomWall) &&
      (maze_->walls[currentI] != RightAndBottomWalls) &&
      (currentI < ((int) maze_->walls.size() - maze_->getCols())) &&
      (maze_solution[onDown] == -1)) {
    maze_solution[onDown] = step;
    list.push_back(onDown);
  }

  return list;
}

void MazeSolver::FillShortestSolutionPath(int endX, int endY) {
  if (endX >= maze_->getRows() || endY >= maze_->getCols()) {
    return;
  }

  for (int i = 0; i < (int) maze_solution.size(); i++) {
    shortest_solution_path.push_back(NoPathLine);
  }

  int endI = ConvertXYtoI(endX, endY);
  int currentI = endI;
  int currentX;
  int currentY;
  int onLeft;
  int onRight;
  int onUp;
  int onDown;
  int step = maze_solution[currentI];

  while (step > 0) {
    currentX = ConvertItoXY(currentI).first;
    currentY = ConvertItoXY(currentI).second;

    onLeft = ConvertXYtoI(currentX, currentY - 1);
    if ((currentI != 0) && (currentI % maze_->getCols() != 0) &&
        (maze_->walls[currentI - 1] != RightWall) &&
        (maze_->walls[currentI - 1] != RightAndBottomWalls) &&
        (maze_solution[onLeft] == step - 1)) {
      shortest_solution_path[onLeft] = LeftHorizontalPathLine;
      currentI = onLeft;
      step--;
      continue;
    }

    onRight = ConvertXYtoI(currentX, currentY + 1);
    if ((maze_->walls[currentI] != RightWall) &&
        (maze_->walls[currentI] != RightAndBottomWalls) &&
        (maze_solution[onRight] == step - 1)) {
      shortest_solution_path[onRight] = RightHorizontalPathLine;
      currentI = onRight;
      step--;
      continue;
    }

    onUp = ConvertXYtoI(currentX - 1, currentY);
    if ((currentI >= maze_->getCols()) &&
        (maze_->walls[currentI - maze_->getCols()] != BottomWall) &&
        (maze_->walls[currentI - maze_->getCols()] != RightAndBottomWalls) &&
        (maze_solution[onUp] == step - 1)) {
      shortest_solution_path[onUp] = UpVerticalPathLine;
      currentI = onUp;
      step--;
      continue;
    }

    onDown = ConvertXYtoI(currentX + 1, currentY);
    if ((maze_->walls[currentI] != BottomWall) &&
        (maze_->walls[currentI] != RightAndBottomWalls) &&
        (maze_solution[onDown] == step - 1)) {
      shortest_solution_path[onDown] = DownVerticalPathLine;
      currentI = onDown;
      step--;
      continue;
    }
  }
}
