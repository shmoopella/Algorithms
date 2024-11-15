#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

struct cell {
    int right = 0;
    int bottom = 0;
    int set = 0;
};

class PerfectMaze {
    public:
        PerfectMaze(size_t rows, size_t cols) : rows_(rows), cols_(cols) {};
        void generateMazeFile();
        size_t getCols() { 
            return cols_;
        };
        size_t getRows() {
            return rows_;
        };

    private:
        size_t rows_;
        size_t cols_;
        std::vector<int> randomSequence;

        void makeRandomSequence();
        void generateMaze(std::vector<std::vector<cell>> &walls);
        void generateRight(std::vector<std::vector<cell>> &walls, size_t &row, size_t&randNum);
        void generateBottom(std::vector<std::vector<cell>> &walls, size_t &row, size_t &col, size_t &randNum);
};

