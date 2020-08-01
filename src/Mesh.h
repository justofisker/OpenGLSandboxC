#ifndef MESH_H
#define MESH_H

typedef unsigned int GLenum;
struct Texture;

typedef struct Mesh {
    unsigned int VertexArrayObject;
    unsigned int VertexBuffer;
    unsigned int IndexBuffer;
    unsigned int ShaderProgram;
    struct Texture* texture;

    unsigned int IndexCount;
    GLenum IndexType;
} Mesh;

Mesh* get_cube_mesh();
Mesh* get_cylinder_mesh(unsigned int detail);
void free_mesh(Mesh* mesh);

#endif // MESH_H
