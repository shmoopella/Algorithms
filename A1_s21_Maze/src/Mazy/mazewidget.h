#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

#include "filehandler.h"
#include "maze.h"
#include "mazesolver.h"

class MazeWidget : public QWidget {
  Q_OBJECT

 private:
  Maze *maze_;
  MazeSolver *maze_solver_;
  void DrawMazeWalls(QPainter *painter);
  void DrawSolution(QPainter *painter);

 protected:
  void paintEvent(QPaintEvent *event) override;

 public:
  explicit MazeWidget(QWidget *parent = nullptr);
  void SetMaze(Maze *maze);
  void SetMazeSolver(MazeSolver *maze_solver_);
  void LoadMaze(const QString &filePath, const std::string &currentDir);
};

#endif  // MAZEWIDGET_H
