#include <iostream>
#include <string>
#include <vector>

#include "Vert.h"
#include "Matrix.h"

using namespace std;

/*
TODO:
- Test default constructor
- Test constructor from 2D vector
- Test constructor by copy
- Test assignent overload
- Test matrix-vector multiplication
- Test matrix-matrix multiplication
- Test identity matrix generation
- Test rotation matrix generation
- Test translation matrix generation
*/

int main() {

    // Default constructor
    Matrix m1;
    cout << m1.to_string() << endl;

    // Constructor from vector of vectors
    vector< vector<double> > ds =
    {
        {1., 2., 3., 4.},
        {5., 6., 7., 8.},
        {9., 0., .1, .2},
        {.3, .4, .5, .6}
    };
    Matrix m2 { ds };
    cout << m2.to_string() << endl;

    // Constructor by copy
    Matrix m3 { m2 };
    cout << m3.to_string() << endl;

    // Assignment overload
    Matrix m4 = m3;
    cout << m4.to_string() << endl;

    // Matrix-vector multiplication
    Vector v1 { 1.0, 0.0, 0.0 };
    Vector v2 = m4 * v1;
    cout << v2.to_string() << endl;

    //TODO:
    //WARNING:
    // Everything but the matrix-vector multiplication
    // is flipped! Every calculation needs to be transposed!
    // Apparently I used row-first ordering in the Java
    // implementation.

    return 0;

}
