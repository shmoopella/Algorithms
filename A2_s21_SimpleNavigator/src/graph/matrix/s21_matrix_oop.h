#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#define EPS 1E-7

#include <math.h>
#include <stdio.h>
#include <stdexcept>

class S21Matrix {
public:
    S21Matrix();                        // Default constructor
    S21Matrix(int rows, int cols);      // Constructor with param
    S21Matrix(const S21Matrix &other);  // Copy constructor
    S21Matrix(S21Matrix &&other);       // Move constructor
    ~S21Matrix();                       // Destructor

    int get_rows() { return rows_; }

    int get_cols() { return cols_; }

    void set_rows(int rows);

    void set_cols(int cols);

    bool EqMatrix(const S21Matrix &other) const;

    void SumMatrix(const S21Matrix &other);

    void SubMatrix(const S21Matrix &other);

    void MulNumber(const double num);

    void MulMatrix(const S21Matrix &other);

    S21Matrix Transpose();

    double Determinant();

    S21Matrix CalcComplements();

    S21Matrix InverseMatrix();

    S21Matrix operator+(const S21Matrix &other);

    S21Matrix operator-(const S21Matrix &other);

    S21Matrix operator*(const double num);

    S21Matrix operator*(const S21Matrix &other);

    bool operator==(const S21Matrix &other);

    S21Matrix &operator=(const S21Matrix &other);

    S21Matrix &operator=(S21Matrix &&other);

    S21Matrix &operator+=(const S21Matrix &other);

    S21Matrix &operator-=(const S21Matrix &other);

    S21Matrix &operator*=(const double num);

    S21Matrix &operator*=(const S21Matrix &other);

    double operator()(int i, int j) const;

    double &operator()(int i, int j);

    void PrintMatrix();

private:
    int rows_, cols_;  // Rows and columns
    double **matrix_;  // Pointer to the memory where the matrix is allocated
    S21Matrix MatrixForMinor(int row, int col);

    void CleanMemory();

    void AllocateMemory();

    void FillMatrix(double num);

    void FillMatrixForDeter();

    void FillMatrixForCalc();
};

#endif  // SRC_S21_MATRIX_OOP_H_
