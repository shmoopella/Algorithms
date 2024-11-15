#include "s21_matrix_oop.h"


S21Matrix::S21Matrix() {  //конструктор создания объекта (без параметров)
    rows_ = 3;
    cols_ = 3;
    this->AllocateMemory();
}

S21Matrix::S21Matrix(int rows,
                     int cols) {  //конструктор создания объекта (с параметрами)
    if (rows <= 0 || cols <= 0) {
        throw std::logic_error("Rows and cols must be more then 0");
    }
    rows_ = rows;
    cols_ = cols;
    this->AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {  //конструктор копирования
    this->AllocateMemory();
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) : rows_(other.rows_), cols_(other.cols_),
                                          matrix_(other.matrix_) {  //конструктор перемещения
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {  //деструктор
    if (matrix_) {
        this->CleanMemory();
    }
}

void S21Matrix::CleanMemory() {  // очистка памяти
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
}

void S21Matrix::AllocateMemory() {  // выделение памяти
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

void S21Matrix::set_rows(int rows) {  // изменение количества строк
    if (rows <= 0) {
        throw std::logic_error("Count of rows must be more then zero");
    }
    int count_r = rows_;
    if (rows_ > rows) {
        count_r = rows;
    }
    S21Matrix tmp = std::move(*this);
    rows_ = rows;
    this->AllocateMemory();
    for (int i = 0; i < count_r; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = tmp.matrix_[i][j];
        }
    }
}

void S21Matrix::set_cols(int cols) {  // изменение количества столбцов
    if (cols <= 0) {
        throw std::logic_error("Count of cols must be more then zero");
    }
    int count_c = cols_;
    if (cols_ > cols) {
        count_c = cols;
    }
    S21Matrix tmp = std::move(*this);
    cols_ = cols;
    this->AllocateMemory();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < count_c; j++) {
            matrix_[i][j] = tmp.matrix_[i][j];
        }
    }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {  // сравнение матриц
    bool res = true;
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        for (int i = 0; i < rows_ && res; i++) {
            for (int j = 0; j < cols_ && res; j++) {
                if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
                    res = false;
                }
            }
        }
    } else {
        res = false;
    }
    return res;
}

void S21Matrix::SumMatrix(
        const S21Matrix &other) {  // прибавление матрицы к матрице
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Couldn't to sum matrixes: not equal rows or columns.");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(
        const S21Matrix &other) {  // вычитание одной матрицы из другой
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Couldn't to sub matrixes: not equal rows or columns.");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num) {  // умножение матрицы на число
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = num * matrix_[i][j];
        }
    }
}

void S21Matrix::MulMatrix(
        const S21Matrix &other) {  // умножение матрицы на матрицу
    if (cols_ != other.rows_) {
        throw std::logic_error("Couldn't to mult matrixes: columns of the first matrix doesn't "
                               "match rows of the second.");
    }
    S21Matrix tmp(rows_, other.cols_);
    for (int i = 0; i < tmp.rows_; i++) {
        for (int j = 0; j < tmp.cols_; j++) {
            tmp.matrix_[i][j] = 0;
            for (int k = 0; k < cols_; k++) {
                tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = std::move(tmp);
}

S21Matrix S21Matrix::Transpose() {  // транспонирование
    S21Matrix result(this->cols_, this->rows_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            result.matrix_[i][j] = this->matrix_[j][i];
        }
    }
    return result;
}

S21Matrix S21Matrix::MatrixForMinor(
        int row, int col) {  // вспомогательная матрица для нахождения миноров
    int row_res = 0;
    int col_res = 0;
    S21Matrix res(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; i++) {
        if (i == row) {
            continue;
        }
        for (int j = 0; j < cols_; j++) {
            if (j == col) {
                continue;
            } else {
                res.matrix_[row_res][col_res] = matrix_[i][j];
                col_res++;
            }
        }
        col_res = 0;
        row_res++;
    }
    return res;
}

double S21Matrix::Determinant() {  // нахождение детерминанта матрицы
    double res = 0;
    double minor = 0;
    double algeb_compl = 0;
    S21Matrix tmp_matrix_for_minor;
    if (rows_ != cols_) {
        throw std::logic_error("Rows aren't equal cols!");
    }
    if (rows_ == 1) {
        res = **matrix_;
    } else if (rows_ == 2) {
        res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
        res = 0;
        for (int j = 0; j < cols_; j++) {
            tmp_matrix_for_minor = this->MatrixForMinor(0, j);
            minor = tmp_matrix_for_minor.Determinant();
            algeb_compl = pow(-1, 0 + j) * minor;
            res += matrix_[0][j] * algeb_compl;
        }
    }
    return res;
}

S21Matrix
S21Matrix::CalcComplements() {  // нахождение матрицы алгебраических дополнений
    if (rows_ != cols_ || rows_ == 1) {
        throw std::logic_error("Rows can't equal cols and rows must be more then 1");
    }
    S21Matrix res(rows_, cols_);
    S21Matrix tmp_matrix_for_minor;
    double algeb_compl = 0;
    double minor = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            tmp_matrix_for_minor = this->MatrixForMinor(i, j);
            minor = tmp_matrix_for_minor.Determinant();
            algeb_compl = pow(-1, i + j) * minor;
            res.matrix_[i][j] = algeb_compl;
        }
    }
    return res;
}

S21Matrix S21Matrix::InverseMatrix() {  // инверсия матрицы
    if (rows_ != cols_ || rows_ == 1) {
        throw std::logic_error("Couldn't inverse the matrix. Count of rows must equal to count of "
                               "cols and more then one");
    }
    double determ = 0;
    S21Matrix result_compl;
    S21Matrix result_transp;
    S21Matrix result_inverse;
    determ = Determinant();
    if (fabs(determ) < 1E-10) {
        throw std::logic_error("Couldn't inverse the matrix: determinant is zero");
    }
    result_compl = CalcComplements();
    result_transp = result_compl.Transpose();
    result_inverse = result_transp * (1 / determ);
    return result_inverse;
}

// перегрузка операторов

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.MulNumber(num);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
    return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(
        const S21Matrix &other) {  //присваивание копированием
    if (this == &other) {
        return *this;
    }
    this->CleanMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    this->AllocateMemory();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
    return *this;
}

S21Matrix &S21Matrix::operator=(
        S21Matrix &&other) {  //присваивание перемещением
    if (this == &other) {
        return *this;
    }
    this->CleanMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
    return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
    this->SumMatrix(other);
    return (*this);
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
    this->SubMatrix(other);
    return (*this);
}

S21Matrix &S21Matrix::operator*=(const double num) {
    this->MulNumber(num);
    return (*this);
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
    this->MulMatrix(other);
    return (*this);
}

double S21Matrix::operator()(int i, int j) const {
    if (i > rows_ - 1 || i < 0 || j > cols_ - 1 || j < 0) {
        throw std::logic_error("Index outside the matrix!");
    }
    return this->matrix_[i][j];
}

double &S21Matrix::operator()(int i, int j) {
    if (i > rows_ - 1 || i < 0 || j > cols_ - 1 || j < 0) {
        throw std::logic_error("Index outside the matrix!");
    }
    return this->matrix_[i][j];
}

void S21Matrix::FillMatrix(
        double num) {  // вспомогательная для заполнения матрицы
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = num;
            num++;
        }
    }
}

void S21Matrix::FillMatrixForDeter() {  // вспомогательная для наполнения
    // матрицы под тест на детерминант
    matrix_[0][0] = -1;
    matrix_[0][1] = 2;
    matrix_[0][2] = 3;
    matrix_[0][3] = 4;
    matrix_[1][0] = 5;
    matrix_[1][1] = 6;
    matrix_[1][2] = 7;
    matrix_[1][3] = 8;
    matrix_[2][0] = 9;
    matrix_[2][1] = 10;
    matrix_[2][2] = 11;
    matrix_[2][3] = 12;
    matrix_[3][0] = 13;
    matrix_[3][1] = 14;
    matrix_[3][2] = 15;
    matrix_[3][3] = -16;
}

void S21Matrix::FillMatrixForCalc() {  // вспомогательная для наполнения матрицы
    // под тест на алгеб доп
    matrix_[0][0] = 1;
    matrix_[0][1] = 2;
    matrix_[0][2] = 3;
    matrix_[1][0] = 0;
    matrix_[1][1] = 4;
    matrix_[1][2] = 2;
    matrix_[2][0] = 5;
    matrix_[2][1] = 2;
    matrix_[2][2] = 1;
}

void S21Matrix::PrintMatrix() {  // вспомогательная для вывода матрицы
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            printf("%f ", matrix_[i][j]);
        }
        printf("\n");
    }
}
