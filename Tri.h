/*
Adam Rilatt
20 October 2021
C++ Raster Engine -- Triangle Class
*/

/*
TODO:
- (optional) Add a static variable to track the number of Triangles
- When complete, inline all member functions
*/

#ifndef TRI_H
#define TRI_H

#include <string>
#include "Vert.h"

class Triangle {
/*
    A Triangle is a collection of three Vectors. They represent the simplest
    possible mesh that can be formed with 3D points. The Vectors are defined
    in clockwise order so that the normal to its face can be inferred, which
    allows for lighting effects based on lighting incidence angles; it also
    facilitates face culling, which saves processing time for Triangles out-
    of-view.
*/
public:
    
    // Constructors
    // No default initializer -- Triangles must have three points
    Triangle(const Vector& v1, const Vector& v2, const Vector& v3);
    Triangle(const Triangle& v);
    
    // Destructor
    ~Triangle() = default;
    
    // Operator overloads
    Triangle operator=(const Triangle&);
    Triangle operator+(const Triangle&);
    Triangle operator-(const Triangle&);
    Triangle operator*(const double);
    Triangle operator/(const double);
    
    // Client I/O
    std::string to_string() const;
    double average_z() const;
    
    // Data members
    Vector verts[3];
    
//private:
};

// Construct this Triangle by-value.
// Note that the Vectors should be listed in clockwise order so that its
// face normal will be correctly inferred.
Triangle::Triangle(const Vector& v1, const Vector& v2, const Vector& v3) {
    verts[0] = v1;
    verts[1] = v2;
    verts[2] = v3;
}

// Construct this Triangle as a copy of another Triangle.
Triangle::Triangle(const Triangle& t) {
    verts[0] = t.verts[0];
    verts[1] = t.verts[1];
    verts[2] = t.verts[2];
}

// Assignment operator, which returns the left-hand Triangle.
Triangle Triangle::operator=(const Triangle& t) {
    verts[0] = t.verts[0];
    verts[1] = t.verts[1];
    verts[2] = t.verts[2];
    return *this;
}

// Returns the average z component of this Triangle's Vectors.
// This can be used to cull rendered Triangles later.
double Triangle::average_z() const {
    return (verts[0].z + verts[1].z + verts[2].z) / 3.0;
}

std::string Triangle::to_string() const {
    std::string s = "Triangle <" + verts[0].to_string() + ", " +
                                   verts[1].to_string() + ", " +
                                   verts[2].to_string() + ">";
    return s;
}

#endif