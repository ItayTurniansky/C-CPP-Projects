#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

struct matrix_dims {
    int rows, cols;
};

class Matrix {
public:
    Matrix(int rows, int cols);  // constructor
    Matrix();  //default constructor
    Matrix(const Matrix& m);  // Copy constructor should be const reference
    ~Matrix();  // Destructor

    int get_rows() const;  // returns number of rows
    int get_cols() const;  // returns number of columns

    Matrix& transpose();  // transpose a matrix
    Matrix& vectorize();  // vectorize a matrix
    void plain_print() const;  // simple print all matrix numbers
    Matrix dot(const Matrix& m) const;  // Dot product of two matrices
    float norm() ;  // return a matrix Frobenius norm
    Matrix rref() const;  // reduced row echelon form of a matrix
    int argmax() const;  // returns the matrix's highest value
    float sum() const;  // returns the sum of all the matrix's values

    Matrix& operator+=(const Matrix& other);  // adds a matrix to a given matrix
    Matrix& operator=( const Matrix& other);  // assign matrix to a given matrix
    Matrix operator+( const Matrix& other) const;  // add two matrices to a new matrix
    Matrix operator*(float c) const;  // matrix multiplication
    Matrix operator*(const Matrix& m)const;  // multiply matrix with scalar
    float operator()(int row, int col) const;
    float& operator()(int row, int col);  // access matrix elements by (row, col)
    float operator[](int index) const;
    float& operator[](int index);  // access matrix elements by index
    friend std::ostream& operator<<(std::ostream& os,  Matrix& mat);  // stream output for matrix
    friend std::istream& operator>>(std::istream& is,  Matrix& mat);  // stream input for matrix

private:
    int rows;
    int cols;
    float* data;  // matrix data
};
Matrix operator*(float c, const Matrix& other); //multiply matrix by scalar c
#endif //MATRIX_H
