#include "Mesh.h"
#include "Util.h"
#include "Texture.h"
#include <glad/glad.h>
#include <cglm/cglm.h>

Mesh *create_cube_mesh(float size)
{
    typedef struct vertex
    {
        float x, y, z;
        float r, g, b;
        float tex_x, tex_y;
    } Vertex;

    Vertex verticies[] = {
        { -0.5f * size, -0.5f * size,  0.5f * size  ,  0.f, 0.f, 1.f  ,  0.f, 0.f },
        {  0.5f * size, -0.5f * size,  0.5f * size  ,  1.f, 0.f, 1.f  ,  1.f, 0.f },
        {  0.5f * size,  0.5f * size,  0.5f * size  ,  1.f, 1.f, 1.f  ,  1.f, 1.f },
        { -0.5f * size,  0.5f * size,  0.5f * size  ,  0.f, 1.f, 1.f  ,  0.f, 1.f },
        { -0.5f * size, -0.5f * size, -0.5f * size  ,  0.f, 0.f, 0.f  ,  0.f, 1.f },
        {  0.5f * size, -0.5f * size, -0.5f * size  ,  1.f, 0.f, 0.f  ,  1.f, 1.f },
        {  0.5f * size,  0.5f * size, -0.5f * size  ,  1.f, 1.f, 0.f  ,  1.f, 0.f },
        { -0.5f * size,  0.5f * size, -0.5f * size  ,  0.f, 1.f, 0.f  ,  0.f, 0.f },
    };

    typedef unsigned char Index;

    static Index indicies[] = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        6, 5, 4,
        4, 7, 6,
        7, 4, 0,
        0, 3, 7,
        5, 1, 0,
        0, 4, 5,
        2, 6, 7,
        7, 3, 2,
    };

    Mesh *mesh = malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->vertex_array_object);
    glBindVertexArray(mesh->vertex_array_object);

    glGenBuffers(1, &mesh->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_x));

    glGenBuffers(1, &mesh->index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    mesh->index_count = sizeof(indicies) / sizeof(Index);
    mesh->index_type = GL_UNSIGNED_BYTE;

    mesh->texture = NULL;

    return mesh;
}

Mesh *create_cylinder_mesh(int _verticies, float radius, float depth)
{
    _verticies = max(_verticies, 3);

    typedef struct Vertex {
        float x, y, z;
        float r, g, b;
        float tex_x, tex_y;
    } Vertex;

    size_t verticies_size = sizeof(Vertex) * (_verticies * 2 + 2 + 2);
    Vertex *verticies = malloc(verticies_size);

    int i;
    for(i = 0; i < _verticies + 1; ++i)
    {
        float theta = GLM_PIf * 2 / _verticies * i;
        float x = cosf(theta) * radius;
        float y = sinf(theta) * radius;

        verticies[i].x = x;
        verticies[i].y = y;
        verticies[i].z = -.5f * depth;
        verticies[i].r = (x + 1) / 2;
        verticies[i].g = (y + 1) / 2;
        verticies[i].b = 0;
        verticies[i].tex_x = theta / (2 * GLM_PIf);
        verticies[i].tex_y = 0.f;
        verticies[i + (_verticies + 1)].x = x;
        verticies[i + (_verticies + 1)].y = y;
        verticies[i + (_verticies + 1)].z = .5f * depth;
        verticies[i + (_verticies + 1)].r = (x + 1) / 2;
        verticies[i + (_verticies + 1)].g = (y + 1) / 2;
        verticies[i + (_verticies + 1)].b = 1;
        verticies[i + (_verticies + 1)].tex_x = theta / (2 * GLM_PIf);
        verticies[i + (_verticies + 1)].tex_y = 1.f;
    }
    verticies[_verticies * 2 + 2].x = 0;
    verticies[_verticies * 2 + 2].y = 0;
    verticies[_verticies * 2 + 2].z = -0.5f * depth;
    verticies[_verticies * 2 + 2].r = 0;
    verticies[_verticies * 2 + 2].g = 0;
    verticies[_verticies * 2 + 2].b = 0;
    verticies[_verticies * 2 + 2].tex_x = 0.f;
    verticies[_verticies * 2 + 2].tex_y = 0.f;
    verticies[_verticies * 2 + 3].x = 0;
    verticies[_verticies * 2 + 3].y = 0;
    verticies[_verticies * 2 + 3].z = 0.5f * depth;
    verticies[_verticies * 2 + 3].r = 0;
    verticies[_verticies * 2 + 3].g = 0;
    verticies[_verticies * 2 + 3].b = 1;
    verticies[_verticies * 2 + 3].tex_x = 1.f;
    verticies[_verticies * 2 + 3].tex_y = 1.f;

    typedef unsigned int Index;

    size_t indicies_size = sizeof(Index) * (_verticies * 12 + 2);
    Index *indicies = malloc(indicies_size);

    for(i = 0; i < _verticies; ++i)
    {
        int offset = i * 6;
        indicies[offset + 0] = i + 0;
        indicies[offset + 1] = i + (_verticies + 1) + 1;
        indicies[offset + 2] = i + (_verticies + 1);
        indicies[offset + 3] = indicies[offset + 0];
        indicies[offset + 4] = i + 1;
        indicies[offset + 5] = indicies[offset + 1];
    }
    for(i = 0; i < _verticies; ++i)
    {
        indicies[(_verticies + i) * 6 + 0] = (_verticies + 1) + i;
        indicies[(_verticies + i) * 6 + 1] = (_verticies + 1) + 1 + i;
        indicies[(_verticies + i) * 6 + 2] = (_verticies + 1) * 2 + 1;
        indicies[(_verticies + i) * 6 + 3] = (_verticies + 1) * 2;
        indicies[(_verticies + i) * 6 + 4] = 1 + i;
        indicies[(_verticies + i) * 6 + 5] = i;
    }

    Mesh* mesh = malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->vertex_array_object);
    glBindVertexArray(mesh->vertex_array_object);

    glGenBuffers(1, &mesh->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, verticies_size, verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_x));

    glGenBuffers(1, &mesh->index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_size, indicies, GL_STATIC_DRAW);

    mesh->index_count = _verticies * 12;
    mesh->index_type = GL_UNSIGNED_INT;

    mesh->texture = NULL;

    free(verticies);
    free(indicies);

    return mesh;
}

void free_mesh(Mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->vertex_array_object);
    glDeleteBuffers(1, &mesh->vertex_buffer);
    glDeleteBuffers(1, &mesh->index_buffer);
    free(mesh);
}
