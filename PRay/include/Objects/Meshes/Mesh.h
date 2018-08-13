//
// Created by Suraj on 20/6/18.
//

#ifndef PRAY_MESH_H
#define PRAY_MESH_H
#include <vector>
#include <Utils/Point3D.h>

class Mesh
{
public:

    std::vector<Point3D>            vertices;
    std::vector<Normal>             normals;
    std::vector<std::vector<int>>   vertex_faces;

    unsigned int num_of_triangles;
    unsigned int num_of_vertices;

    Mesh();
    Mesh(const Mesh& aMesh);
    ~Mesh();

    Mesh& operator=(const Mesh& aMesh);

};


#endif // PRAY_MESH_H

