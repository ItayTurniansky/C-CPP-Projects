#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <cmath>
#define MIN_PROB 0.1
// Constructors and destructor
Matrix::Matrix( int rows,  int cols) : rows(rows), cols(cols), data{new float[rows*cols]} { // constructor
    if ( rows <= 0 || cols <= 0 ) {
        delete[] data;
        throw std::invalid_argument("invalid matrix size");
    }
    for ( int i = 0; i < rows*cols; i++ ) {
        data[i] = 0;
    }
}

Matrix::Matrix() : rows{1}, cols{1}, data{new float{1}} {
    data[0] = 0;
} //default constructor

Matrix::Matrix(const Matrix& m) : rows(m.rows), cols{m.cols}, data {new float[rows * cols]}{ //copy constructor
    for (int i = 0; i < rows * cols; i++) {
        data[i] = m.data[i];
    }
}

Matrix::~Matrix() { // destructor
    delete[] data;
}

// Getters
int Matrix::get_cols() const {
    return cols;
}

int Matrix::get_rows() const {
    return rows;
}

// functions
Matrix& Matrix::transpose() { // transpose a matrix
    auto* new_data = new float[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            new_data[j * rows + i] = data[i * cols + j];
        }
    }
    float* tmp = data;
    data = new_data;
    delete[] tmp;
    std::swap(rows, cols);
    return *this;
}

Matrix& Matrix::vectorize() { // vectorize a matrix
    rows *= cols;
    cols = 1;
    return *this;
}

void Matrix::plain_print() const { // simple print all matrix numbers
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix &mul) const
{
    if (rows != mul.rows || cols != mul.cols)
    {
        throw std::invalid_argument("wrong matrix size");
    }
    Matrix return_matrix{rows, cols};
    for (int i = 0; i < rows * cols; i++)
    {
        return_matrix.data[i] = data[i] * mul.data[i];
    }
    return return_matrix;
}

float Matrix::norm() { // return a matrix Frobenius norm
    float sum = 0;
    for (int i = 0; i < rows * cols; i++) {
        sum += pow(data[i],2);
    }
    return std::sqrt(sum);
}

Matrix Matrix::rref() const {
    // Create a copy of the matrix to work on
    Matrix result(*this);
    int lead_col = 0;  // This keeps track of the column we're working on

    // Loop through each row of the matrix
    for (int row = 0; row < result.rows; ++row) {

        // If we've reached the end of the columns, stop
        if (lead_col >= result.cols) {
            return result;
        }

        // Find the first non-zero element in the current column
        int current_row = row;
        while (result.data[current_row * result.cols + lead_col] == 0) {
            current_row++;
            if (current_row == result.rows) {
                current_row = row;
                lead_col++;
                if (lead_col == result.cols) {
                    return result;
                }
            }
        }

        // Swap the rows if needed to get a non-zero entry at the current lead position
        std::swap(result.data[current_row * result.cols + lead_col], result.data[row * result.cols + lead_col]);

        // Divide the current row by the leading value to make it 1
        float pivot = result.data[row * result.cols + lead_col];
        for (int col = 0; col < result.cols; ++col) {
            result.data[row * result.cols + col] /= pivot;
        }

        // Eliminate the values in the current column (except for the pivot)
        for (int other_row = 0; other_row < result.rows; ++other_row) {
            if (other_row != row) {
                float factor = result.data[other_row * result.cols + lead_col];
                for (int col = 0; col < result.cols; ++col) {
                    result.data[other_row * result.cols + col] -= factor * result.data[row * result.cols + col];
                }
            }
        }

        // Move to the next column
        lead_col++;
    }

    return result;
}

int Matrix::argmax() const { // return the matrix's highest value
    float max = data[0];
    int max_index = 0;
    for (int i = 0; i < rows * cols; i++) {
        if (data[i] > max) {
            max = data[i];
            max_index = i;
        }
    }
    return max_index;
}

float Matrix::sum() const { // returns the sum of all the matrix's values
    float sum = 0;
    for (int i = 0; i < rows * cols; i++) {
        sum += data[i];
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix& other) { // adds a matrix to a given matrix
    if (cols != other.cols || rows != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    for (int i = 0; i < rows * cols; i++) {
        data[i] += other.data[i];
    }
    return *this;
}

Matrix Matrix::operator+( const Matrix& other) const{ // add two matrices to a new matrix
    if (other.rows != rows || other.cols != cols) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(*this);
    result +=other;
    return result;
}

Matrix& Matrix::operator=( const Matrix& other) { // assign matrix to a given matrix
    if (this == &other) {
        return *this;
    }
    auto* new_data = new float[other.rows * other.cols];
    for (int i = 0; i < other.rows * other.cols; i++) {
        new_data[i] = other.data[i];
    }
    float* tmp = data;
    data = new_data;
    delete[] tmp;
    rows = other.rows;
    cols = other.cols;
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");
    }

    Matrix m{rows, other.cols}; // Resulting matrix

    for (int l = 0; l < rows; l++) {
        for (int j = 0; j < other.cols; j++) {
            m.data[l * m.cols + j] = 0;
            for (int i = 0; i < cols; i++)
            {
                m.data[l * m.cols + j] += data[l * cols + i]
                * other.data[i * other.cols + j];
            }
        }
    }

    return m;
}
Matrix Matrix::operator*(float scalar) const
{
    Matrix m(rows, cols);

    for (int i = 0; i< rows * cols; i++)
    {
        m.data[i] = data[i] * scalar;
    }
    return m;
}

Matrix operator*(float c, const Matrix& m)
{
    return m * c;
}
float& Matrix::operator()( int row,  int col){ // access matrix elements by (row, col)
    if (row >= rows || col >= cols || row < 0 || col < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[row * cols + col];
}

float Matrix::operator()(int row, int col) const {
    if (row >= rows || col >= cols || row < 0 || col < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[row * cols + col];
}

float& Matrix::operator[](const int index) { // access matrix elements by index
    if (index >= rows * cols || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

float Matrix::operator[](const int index) const{ // access matrix elements by index
    if (index >= rows * cols || index < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

std::ostream& operator<<(std::ostream& os,  Matrix& mat) { // stream output for matrix
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            if(mat(i,j)>MIN_PROB) {
                os <<"**";
            }
            else {
                os<<"  ";
            }
        }
        os << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix)
{
    std::streamsize buffer_size = matrix.rows * matrix.cols* sizeof(float);
    if (!is.read(reinterpret_cast<char *>(matrix.data), buffer_size))
    {
        throw std::length_error("not enough elements");
    }
    return is;
}
