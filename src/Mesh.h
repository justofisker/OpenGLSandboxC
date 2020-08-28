#ifndef MESH_H
#define MESH_H

typedef unsigned int GLenum;
typedef struct _Texture Texture;

typedef struct _Mesh {
    unsigned int vertex_array_object;
    unsigned int vertex_buffer;
    unsigned int index_buffer;
    Texture *texture;

    unsigned int index_count;
    GLenum index_type;
} Mesh;

Mesh* create_cube_mesh(float size);
Mesh* create_cylinder_mesh(int verticies, float radius, float depth);
void free_mesh(Mesh *mesh);

#endif // MESH_H
