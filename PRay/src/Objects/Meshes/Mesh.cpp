#include "Objects/Meshes/Mesh.h"

Mesh::Mesh() :
    num_of_triangles(0),
    num_of_vertices(0)
{}

Mesh::Mesh(const Mesh& aMesh) :
    vertices(aMesh.vertices),
    normals(aMesh.normals),
    vertex_faces(aMesh.vertex_faces),
    num_of_triangles(aMesh.num_of_triangles),
    num_of_vertices(aMesh.num_of_vertices)
{}

Mesh& Mesh::operator=(const Mesh &aMesh)
{
    if(this == &aMesh)
        return *this;

    vertices = aMesh.vertices;
    normals  = aMesh.normals;
    vertex_faces = aMesh.vertex_faces;
    num_of_triangles = aMesh.num_of_triangles;
    num_of_vertices = aMesh.num_of_vertices;
}

Mesh::~Mesh()
= default;



