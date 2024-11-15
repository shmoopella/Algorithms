#include <QApplication>

#include "filehandler.h"
#include "mainwindow.h"
#include "maze.h"
#include "mazesolver.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Maze maze = Maze();
  FileHandler file_handler = FileHandler(&maze);
  MazeSolver maze_solver = MazeSolver(&maze);
  MainWindow w(&maze, &file_handler, &maze_solver);
  w.show();
  return a.exec();
}
