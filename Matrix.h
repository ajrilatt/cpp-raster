/*
Adam Rilatt
22 October 2021
C++ Raster Engine -- Matrix
*/

/*
TODO:
- If it would be advantageous, add a rotation(x, y, z)
- Optimize matrix-matrix and matrix-vector multiplication routine if possible
- When complete, inline all applicable member functions
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <cmath>

#include "Vert.h"

class Matrix {
/*
    A Matrix is a specific implementation of a mathematical matrix.
    They perform useful linear operation on Vectors, including the translation
    from world space to screen space.
*/
public:

    // Constructors
    Matrix() = default;
    Matrix(const std::vector< std::vector<double> >& data);
    Matrix(const Matrix&);

    // Destructor
    ~Matrix() = default;

    // Operator overloads
    Matrix operator=(const Matrix&);
    Vector operator*(const Vector&);
    Matrix operator*(const Matrix&);

    // Client I/O
    std::string to_string() const;

    Matrix identity();
    Matrix rotation_x(double angle_rad);
    Matrix rotation_y(double angle_rad);
    Matrix rotation_z(double angle_rad);
    Matrix translation(double x, double y, double z);

    // Data members
    std::vector< std::vector<double> > data { { 0., 0., 0., 0. },
                                              { 0., 0., 0., 0. },
                                              { 0., 0., 0., 0. },
                                              { 0., 0., 0., 0. } };
//private:
};

// Default constructor used.
// Default destructor used.

// Constructs a n_col-by-n_row Matrix with the given entries.
Matrix::Matrix(const std::vector< std::vector<double> >& d)
: data(d)
{ }

// Constructs a Matrix by copying another Matrix.
Matrix::Matrix(const Matrix& m)
: data(m.data)
{ }

// Assignment / copy operator overload.
Matrix Matrix::operator=(const Matrix& m) {

    Matrix t { m.data };
    return t;

}

// Multiply a Vector by a Matrix and return the resulting Vector.
// Because every Vector used in the rasterization engine uses a 4x4 Matrix,
// this function does not need to be generalizable.
//NOTE: This is a moderately expensive operation.
Vector Matrix::operator*(const Vector& v) {

    Vector t;
    t.x = v.x * data[0][0] + v.y * data[0][1] + v.z * data[0][2] + v.w * data[0][3];
    t.y = v.x * data[1][0] + v.y * data[1][1] + v.z * data[1][2] + v.w * data[1][3];
    t.z = v.x * data[2][0] + v.y * data[2][1] + v.z * data[2][2] + v.w * data[2][3];
    t.w = v.x * data[3][0] + v.y * data[3][1] + v.z * data[3][2] + v.w * data[3][3];
    return t;

}

// Multiply a Matrix by another Matrix and return the result.
// NOTE: This is an extremely expensive operation.
Matrix Matrix::operator*(const Matrix& m) {

    Matrix t;
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            t.data[k][i] = data[k][0] * m.data[0][i] +
                           data[k][1] * m.data[1][i] +
                           data[k][2] * m.data[2][i] +
                           data[k][3] * m.data[3][i];

    return t;

}

// Generates and returns a 4 x 4 identity Matrix.
static Matrix identity() {

    Matrix m;
    for (int i = 0; i < 4; ++i)
        m.data[i][i] = 1.0;
    return m;

}

// Constructs and returns a rotation matrix for the X axis based on a radian
// angle.
static Matrix rotation_x(double angle_rad) {

    Matrix m;
    m.data[0][0] = 1.0;
    m.data[1][1] = std::cos(angle_rad);
    m.data[1][2] = std::sin(angle_rad);
    m.data[2][1] = -std::sin(angle_rad);
    m.data[2][2] = std::cos(angle_rad);
    m.data[3][3] = 1.0;
    return m;

}

// Constructs and returns a rotation matrix for the Y axis based on a radian
// angle.
static Matrix rotation_y(double angle_rad) {

    Matrix m;
    m.data[0][0] = std::cos(angle_rad);
    m.data[0][2] = std::sin(angle_rad);
    m.data[1][1] = 1.0;
    m.data[2][0] = -std::sin(angle_rad);
    m.data[2][2] = std::cos(angle_rad);
    m.data[3][3] = 1.0;
    return m;

}

// Constructs and returns a rotation matrix for the Z axis based on a radian
// angle.
static Matrix rotation_z(double angle_rad) {

    Matrix m;
    m.data[0][0] = std::cos(angle_rad);
    m.data[0][1] = std::sin(angle_rad);
    m.data[1][0] = -std::sin(angle_rad);
    m.data[1][1] = std::cos(angle_rad);
    m.data[2][2] = 1.0;
    m.data[3][3] = 1.0;
    return m;

}

// Constructs and returns a matrix that will move a Vector by the specified
// units in x, y, and z.
static Matrix translation(double x, double y, double z) {

    //TODO: will the compiler accept identity() as an initializer like this?
    Matrix m { identity() };
    m.data[3][0] = x;
    m.data[3][1] = y;
    m.data[3][2] = z;
    return m;

}

std::string Matrix::to_string() const {

    std::string s = "Matrix:";
    for (int i = 0; i < 4; ++i) {
        s += "\n";
        for (int k = 0; k < 4; ++k)
            s += std::to_string(data[i][k]) + " ";
    }

    return s;

}

#endif
