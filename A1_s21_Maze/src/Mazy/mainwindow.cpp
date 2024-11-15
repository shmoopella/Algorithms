#include "mainwindow.h"

MainWindow::MainWindow(Maze *maze, FileHandler *file_handler,
                       MazeSolver *maze_solver, QWidget *parent)
    : QMainWindow(parent),
      maze_(maze),
      file_handler_(file_handler),
      maze_solver_(maze_solver),
      ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_LoadButton_clicked() {

  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open File"), "", tr("Text Files (*.txt)"), 0,
      QFileDialog::DontUseNativeDialog);

  if (file_path == nullptr) return;

  try {
    file_handler_->ParseMazeFromFile(file_path.toStdString(), "");

    maze_solver_->Clear();

    ui_->maze_widget->SetMaze(maze_);
    ui_->maze_widget->update();
  } catch (...) {
    std::cerr << "Вылет из MainWindow";
  }
}

void MainWindow::on_SolveButton_clicked() {
  maze_solver_->Clear();
  ui_->maze_widget->update();

  if (maze_ == nullptr) {  // this case dont't exist cos maze_ is created
   std::cerr << "maze_ is nullptr!!!!!!!!!!!!!!";
    return;
  }

  if (maze_->walls.size() == 0) {  // this case when we didn't choose any file
    std::cerr << "maze_->walls is empty!!!!!!!!!!!!!!";
    return;
  }

  int startX = ui_->startX->value();
  int startY = ui_->startY->value();
  int endX = ui_->endX->value();
  int endY = ui_->endY->value();

  if (startX >= maze_->getRows() || startY >= maze_->getCols() ||
      endX >= maze_->getRows() || endY >= maze_->getCols()) {
    return;
  }

  maze_solver_->SolveMaze(startX, startY, endX, endY);
  maze_solver_->FillShortestSolutionPath(endX, endY);

  ui_->maze_widget->SetMazeSolver(maze_solver_);
  ui_->maze_widget->update();
}

void MainWindow::on_GenerateButton_clicked() {
  int rows = ui_->rows->value();
  int cols = ui_->columns->value();

  PerfectMaze perfectMaze(rows, cols);
  if (rows > 0 and cols > 0 and rows <= 50 and cols <= 50) {
    perfectMaze.generateMazeFile();
    maze_solver_->Clear();
    std::string cur_dir = getenv("HOME");
    file_handler_->ParseMazeFromFile(cur_dir + "/mazeFile.txt", "");
    ui_->maze_widget->SetMaze(maze_);
    ui_->maze_widget->update();
  }
}
