/*
Adam Rilatt
22 October 2021
C++ Raster Engine -- Matrix
*/

/*
TODO:
- When complete, inline all applicable member functions
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

#include "Vert.h"

class Matrix {
/*
    A Matrix is a specific implementation of a mathematical matrix.
    They perform useful linear operation on Vectors, including the translation
    from world space to screen space.
*/
public:
    
    // Constructors
    Matrix(int n_cols, int n_rows, const vector<double>& data);
    Matrix(const Matrix&);
    
    // Destructor
    ~Mesh() = default;
    
    // Operator overloads
    Matrix operator=(const Matrix&);
    
    // Client I/O
    std::string to_string() const;
    
    // Data members
    int n_rows;
    int n_cols;
    vector<double> data;
//private:
};

// Constructs a n_col-by-n_row Matrix with the given entries.
Matrix::Matrix(int cols, int rows, const vector<double>& d)
: n_cols(cols), n_rows(rows), data(d)
{ }

// Constructs a Matrix by copying another Matrix.
Matrix::Matrix(const Matrix& m)
: n_cols(m.n_cols), n_rows(m.n_rows), data(m.data)
{ }

// Assignment / copy operator overload.
Matrix Matrix::operator=(const Matrix& m) {
    
    return Matrix(m.n_cols, m.n_rows, m.data);
    
}

// Default destructor used.

std::string Matrix::to_string() const {
    std::string s = "Matrix:\n";
}

#endif