#ifndef MESH_H
#define MESH_H

typedef unsigned int GLenum;
struct Texture;

typedef struct Mesh {
    unsigned int vertex_array_object;
    unsigned int vertex_buffer;
    unsigned int index_buffer;
    struct Texture* texture;

    unsigned int index_count;
    GLenum index_type;
} Mesh;

Mesh* create_cube_mesh();
Mesh* create_cylinder_mesh(unsigned int detail);
void free_mesh(Mesh* mesh);

#endif // MESH_H
