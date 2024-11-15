#include "mazewidget.h"

MazeWidget::MazeWidget(QWidget *parent) : QWidget{parent} {
  setFixedSize(500, 500);
  setStyleSheet("background-color:black;");
}

void MazeWidget::SetMaze(Maze *maze) {
  this->maze_ = maze;
  update();  //  call paintEvent's method to redraw MazeWidget
}

void MazeWidget::SetMazeSolver(MazeSolver *mazeSolver) {
  this->maze_solver_ = mazeSolver;
  update();  //  call paintEvent's method to redraw MazeWidget
}

void MazeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  if (maze_ == nullptr) {
    return;
  }

  // set maze's color & width
  QPen penMaze(Qt::yellow);
  penMaze.setWidth(2);

  // draw maze's outside boundaries and walls
  QPainter painterMaze(this);
  painterMaze.setPen(penMaze);

  QStyleOption opt;
  opt.initFrom(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painterMaze, this);

  // draw maze's walls
  DrawMazeWalls(&painterMaze);

  // set solution's color & width
  QPen penSolution(Qt::green);
  penSolution.setWidth(2);

  // draw solution
  QPainter painterSolution(this);
  painterSolution.setPen(penSolution);
  DrawSolution(&painterSolution);
}

void MazeWidget::DrawMazeWalls(QPainter *painter) {
  if (maze_->getRows() > 0 and maze_->getCols() > 0) {
    painter->drawLine(0, 0, width(), 0);
    painter->drawLine(0, 0, 0, height());
    painter->drawLine(0, height(), width(), height());

    double cellWidth = (width() * 1.0) / maze_->getCols();
    double cellHeight = (height() * 1.0) / maze_->getRows();

    int rowsCoefficient;
    int colsCoefficient;

    for (int i = 0; i < (int) maze_->walls.size(); i++) {
      if (i >= maze_->getCols()) {
        rowsCoefficient = i / maze_->getCols();
        colsCoefficient = i % maze_->getCols();
      } else {
        rowsCoefficient = 0;
        colsCoefficient = i;
      }

      if ((maze_->walls[i] == RightWall) or
          (maze_->walls[i] == RightAndBottomWalls)) {
        painter->drawLine((colsCoefficient + 1) * cellWidth,
                          rowsCoefficient * cellHeight,
                          (colsCoefficient + 1) * cellWidth,
                          (rowsCoefficient + 1) * cellHeight);
      }

      if ((maze_->walls[i] == BottomWall) or
          (maze_->walls[i] == RightAndBottomWalls)) {
        painter->drawLine(colsCoefficient * cellWidth,
                          (rowsCoefficient + 1) * cellHeight,
                          (colsCoefficient + 1) * cellWidth,
                          (rowsCoefficient + 1) * cellHeight);
      }
    }
  }
}

void MazeWidget::DrawSolution(QPainter *painter) {
  if (maze_->getRows() > 0 and maze_->getCols() > 0 and
      (maze_solver_ != nullptr) and
      (maze_solver_->shortest_solution_path.size() > 0)) {
      double cellWidth = (width() * 1.0) / maze_->getCols();
      double cellHeight = (height() * 1.0) / maze_->getRows();

    int rowsCoefficient;
    int colsCoefficient;

    for (int i = 0; i < (int) maze_solver_->shortest_solution_path.size(); i++) {
      if (i >= maze_->getCols()) {
        rowsCoefficient = i / maze_->getCols();
        colsCoefficient = i % maze_->getCols();
      } else {
        rowsCoefficient = 0;
        colsCoefficient = i;
      }

      if (maze_solver_->shortest_solution_path[i] == DownVerticalPathLine) {
        painter->drawLine(
            -0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            -0.5 * cellHeight + rowsCoefficient * cellHeight,
            -0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            -0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight);
      }

      if (maze_solver_->shortest_solution_path[i] == UpVerticalPathLine) {
        painter->drawLine(
            -0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            0.5 * cellHeight + rowsCoefficient * cellHeight,
            -0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight);
      }

      if (maze_solver_->shortest_solution_path[i] == RightHorizontalPathLine) {
        painter->drawLine(
            -0.5 * cellWidth + colsCoefficient * cellWidth,
            -0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight,
            -0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            -0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight);
      }

      if (maze_solver_->shortest_solution_path[i] == LeftHorizontalPathLine) {
        painter->drawLine(
            0.5 * cellWidth + colsCoefficient * cellWidth,
            -0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight,
            0.5 * cellWidth + (colsCoefficient + 1) * cellWidth,
            -0.5 * cellHeight + (rowsCoefficient + 1) * cellHeight);
      }
    }
  }
}
