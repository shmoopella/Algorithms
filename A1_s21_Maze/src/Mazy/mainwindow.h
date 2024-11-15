#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "filehandler.h"
#include "maze.h"
#include "mazesolver.h"
#include "generationperfectmaze.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 private slots:
  void on_LoadButton_clicked();

  void on_SolveButton_clicked();

  void on_GenerateButton_clicked();

private:
  Maze *maze_;
  FileHandler *file_handler_;
  MazeSolver *maze_solver_;
  Ui::MainWindow *ui_;

 public:
  MainWindow(Maze *maze, FileHandler *file_handler, MazeSolver *maze_solver,
             QWidget *parent = nullptr);
  ~MainWindow();
};
#endif  // MAINWINDOW_H
