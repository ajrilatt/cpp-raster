/*
Adam Rilatt
21 October 2021
C++ Raster Engine -- Mesh Class
*/

/*
TODO:
- (optional) Add a static variable to track the number of Meshes
- When complete, inline all member functions
*/

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Vert.h"
#include "Tri.h"

class Mesh {
/*
    A Mesh represents an object in the game world, and is composed of several
    Triangles.
*/
public:
    
    // Constructors
    Mesh() = default;
    Mesh(const std::string& filepath);
    Mesh(const std::string& mesh_name, std::vector<Triangle> ts);
    
    // Destructor
    ~Mesh() = default;
    
    // Operator overloads
    Mesh operator=(const Mesh&);
    
    // Client I/O
    std::string to_string() const;
    
    // Data members
    std::vector<Triangle> tris { };
    std::string name { "" };
    
//private:
};

// Constructs a new Mesh from the .obj file at the specified filepath.
Mesh::Mesh(const std::string& filepath) {
    
    std::ifstream obj_file { filepath };
    name = filepath.substr(0, filepath.size() - 4);
    
    // Check to make sure the file actually exists
    if (!obj_file)
        throw ("Object file " + filepath + " could not be found.");
    
    // forgive me Father for I have sinned
    std::vector<Vector> obj_vecs;
    
    std::string obj_line;
    while (getline(obj_file, obj_line)) {
        
        // Ignore empty lines
        if (obj_line.size() < 0)
            continue;
            
        std::istringstream obj_line_stream( obj_line );
        char line_type = obj_line_stream.get();
        
        if (line_type == 'v') {
            
            double x, y, z;
            obj_line_stream >> x >> y >> z;
            Vector v { x, y, z };
            obj_vecs.push_back(v);
            
        }
        else if (line_type == 'f') {
            
            int a, b, c;
            obj_line_stream >> a >> b >> c;
            Triangle t { obj_vecs[a - 1], obj_vecs[b - 1], obj_vecs[c - 1] };
            tris.push_back(t);
            
        }
        
        // Ignore anything that isn't a vector or a face
        
    }
    
}

// Construct a new Mesh from a vector of Triangles.
Mesh::Mesh(const std::string& mesh_name, std::vector<Triangle> ts)
    : name(mesh_name), tris(ts)
{ }

// Assignment operator, which returns the left-hand Mesh.
Mesh Mesh::operator=(const Mesh& m) {
    tris = m.tris;
    name = m.name;
    return *this;
}

std::string Mesh::to_string() const {
    std::string s = "Mesh from " + name + ":\n";
    for (Triangle t : tris)
        s += "\t" + t.to_string() + "\n";
    return s;
}

#endif