#include "generationperfectmaze.h"

void PerfectMaze::makeRandomSequence() {
    std::random_device rd; // генерация случайного стартового значения
    std::mt19937 gen(rd()); // создание рандомного генератора Mersenne Twister
    std::uniform_int_distribution<> distrib(0, 1); // использование генератора для создания последовательности
    size_t sequenceLength = (cols_-1)*rows_ + (rows_-1)*cols_;
    for (size_t i = 0; i < sequenceLength; ++i) {
        randomSequence.push_back(distrib(gen));
    }
}

void PerfectMaze::generateMaze(std::vector<std::vector<cell>> &walls) {
    makeRandomSequence();
    int set_counter = 1;
    for (size_t row = 0, col = 0; col < cols_; col++, set_counter++) { // назначаем множества для первой строки
        walls[row][col].set = set_counter;
    }

    for (size_t row = 0, randNum = 0; row < rows_; row++) {
        generateRight(walls, row, randNum);
        for (size_t col = 0; col < cols_; col++) {
            generateBottom(walls, row, col, randNum);
        }
        if (row == rows_ - 1) { //если строка последняя
            for (size_t i = 0; i < cols_ - 1; i++) {
                if (walls[row][i].set != walls[row][i + 1].set) {
                    walls[row][i].right = 0;
                    int curSet = walls[row][i + 1].set;
                    for (size_t j = 0; j < cols_; j++) { // объединение множества ячейки
                        if (walls[row][j].set == curSet) {
                            walls[row][j].set = walls[row][i].set;
                        }
                    }
                }
            }
        } else { // если после будем генерировать еще одну строку
            for (size_t i = row + 1, j = 0; j < cols_; j++ ) {
                walls[i][j].set = walls[row][j].set;
                if (walls[row][j].bottom) {
                    walls[i][j].set = set_counter;
                    set_counter++;
                }
            }
        }
    }
}

void PerfectMaze::generateRight(std::vector<std::vector<cell>> &walls, size_t &row, size_t &randNum) {
    for (size_t col = 0; col < cols_; col++) { // правая стенка
        if (col == cols_ - 1) {
            walls[row][col].right = 1;
        } else {
            randNum = randomSequence.back();
            randomSequence.pop_back();
            if (randNum) {
                walls[row][col].right = 1;
            } else {
                if (walls[row][col].set == walls[row][col + 1].set) {
                    walls[row][col].right = 1;
                } else {
                    int curSet = walls[row][col + 1].set;
                    for (size_t j = 0; j < cols_; j++) { // объединение множества ячейки
                        if (walls[row][j].set == curSet) {
                            walls[row][j].set = walls[row][col].set;
                        }
                    }
                }
            }
        }
    }
}

void PerfectMaze::generateBottom(std::vector<std::vector<cell>> &walls, size_t &row, size_t &col, size_t &randNum) {
    if (row == rows_ - 1) {
        walls[row][col].bottom = 1;
    } else {
        randNum = randomSequence.back();
        randomSequence.pop_back();
        if (randNum) {
            int cntBottomWall = 0;
            for (size_t j = 0; j < cols_; j++) {
                if (walls[row][col].set == walls[row][j].set && !walls[row][j].bottom) {
                    cntBottomWall++;
                }
            }
            if (cntBottomWall > 1) {
                walls[row][col].bottom = 1;
            }
        }
    }
}

  void PerfectMaze::generateMazeFile() {
    std::vector<std::vector<cell>> walls(rows_, std::vector<cell>(cols_));
    generateMaze(walls);
    std::ofstream out;
    std::string cur_dir = getenv("HOME");
    out.open(cur_dir + "/mazeFile.txt", std::ios::out);
    if (out.is_open()) {
        out << rows_ << " " << cols_ << std::endl;
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                out << walls[row][col].right << " ";
            }
            out << std::endl;
        }
        out << std::endl;
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                out << walls[row][col].bottom<< " ";
            }
            out << std::endl;
        }
    }
    out.close();
}


