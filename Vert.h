/*
Adam Rilatt
19 October 2021
C++ Raster Engine -- Vector Class
*/

/*
TODO:
- (optional) Add a static variable to track the number of Vectors
- When complete, inline all member functions
*/

#ifndef VERT_H
#define VERT_H

#include <string>

class Vector {
/*
    A Vector is a point in 3-dimensional space. It consists of an x, y, and z
    coordinate, all of which are double-precision floating point numbers.
    It also includes an additional value w which is used for 3-dimensional
    manipulations using Matrices.
*/
public:

    // Constructors
    Vector() = default;
    Vector(const double x, const double y, const double z, const double w);
    Vector(const Vector& v);

    // Destructor
    ~Vector() = default;

    // Operator overloads
    Vector operator=(const Vector&);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    Vector operator*(const double);
    Vector operator/(const double);

    // Client I/O
    std::string to_string() const;

    // Data members
    double x {0.0};
    double y {0.0};
    double z {0.0};
    double w {1.0};

//private:
};

// Construct this Vector by-value.
Vector::Vector(const double x, const double y, const double z, const double w = 1.0)
    : x(x), y(y), z(z), w(w)
{ }

// Construct this Vector as a copy of Vector v.
Vector::Vector(const Vector& v)
    : x(v.x), y(v.y), z(v.z), w(v.w)
{ }

// Assignment operator, which returns the left-hand Vector.
Vector Vector::operator=(const Vector& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

// Adds Vector 2 to Vector 1 and returns a new resultant Vector.
Vector Vector::operator+(const Vector& v) {
    Vector temp;
    temp.x = x + v.x;
    temp.y = y + v.y;
    temp.z = z + v.z;
    return temp;
}

// Subtracts Vector 2 from Vector 1 and returns a new resultant Vector.
Vector Vector::operator-(const Vector& v) {
    Vector temp;
    temp.x = x - v.x;
    temp.y = y - v.y;
    temp.z = z - v.z;
    return temp;
}

// Multiplies a Vector by a scalar and returns a new resultant Vector.
Vector Vector::operator*(const double m) {
    Vector temp;
    temp.x = x * m;
    temp.y = y * m;
    temp.z = z * m;
    return temp;
}

// Divides a vector by a nonzero scalar and returns a new resultant Vector.
// If the scalar is zero, throws an invalid_argument exception.
Vector Vector::operator/(const double d) {
    Vector temp;
    if (d == 0) {
        throw std::invalid_argument("Attemped to divide a Vector::Vector by scalar 0.");
    }
    temp.x = x / d;
    temp.y = y / d;
    temp.z = z / d;
    return temp;
}

std::string Vector::to_string() const {
    std::string s = "Vector {" + std::to_string(x) + ", " +
                                 std::to_string(y) + ", " +
                                 std::to_string(z) + ", " +
                                 std::to_string(w) + "}";
    return s;
}

#endif
