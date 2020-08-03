#include "Mesh.h"
#include "Util.h"
#include "Texture.h"
#include <glad/glad.h>
#include <cglm/cglm.h>

Mesh *create_cube_mesh()
{
    typedef struct vertex
    {
        float x, y, z;
        float r, g, b;
        float tex_x, tex_y;
    } Vertex;

    static Vertex verticies[] = {
        { -1.f, -1.f,  1.f  ,  0.f, 0.f, 1.f  ,  0.f, 0.f },
        {  1.f, -1.f,  1.f  ,  1.f, 0.f, 1.f  ,  1.f, 0.f },
        {  1.f,  1.f,  1.f  ,  1.f, 1.f, 1.f  ,  1.f, 1.f },
        { -1.f,  1.f,  1.f  ,  0.f, 1.f, 1.f  ,  0.f, 1.f },
        { -1.f, -1.f, -1.f  ,  0.f, 0.f, 0.f  ,  0.f, 1.f },
        {  1.f, -1.f, -1.f  ,  1.f, 0.f, 0.f  ,  1.f, 1.f },
        {  1.f,  1.f, -1.f  ,  1.f, 1.f, 0.f  ,  1.f, 0.f },
        { -1.f,  1.f, -1.f  ,  0.f, 1.f, 0.f  ,  0.f, 0.f },
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

Mesh *create_cylinder_mesh(unsigned int detail)
{
    typedef struct Vertex {
        float x, y, z;
        float r, g, b;
        float tex_x, tex_y;
    } Vertex;

    size_t verticies_size = sizeof(Vertex) * (detail * 2 + 2);
    Vertex *verticies = malloc(verticies_size);

    int i;
    for(int i = 0; i < detail; ++i)
    {
        float theta = GLM_PI * 2 / detail * i;
        float x = cosf(theta);
        float y = sinf(theta);

        verticies[i].x = x;
        verticies[i].y = y;
        verticies[i].z = -.5f;
        verticies[i].r = (x + 1) / 2;
        verticies[i].g = (y + 1) / 2;
        verticies[i].b = 0;
        verticies[i].tex_x = theta / (2 * GLM_PI);
        verticies[i].tex_y = 0.f;
        verticies[i + detail].x = x;
        verticies[i + detail].y = y;
        verticies[i + detail].z = .5f;
        verticies[i + detail].r = (x + 1) / 2;
        verticies[i + detail].g = (y + 1) / 2;
        verticies[i + detail].b = 1;
        verticies[i + detail].tex_x = theta / (2 * GLM_PI);
        verticies[i + detail].tex_y = 1.f;
    }
    verticies[detail * 2].x = 0;
    verticies[detail * 2].y = 0;
    verticies[detail * 2].z = -0.5f;
    verticies[detail * 2].r = 0;
    verticies[detail * 2].g = 0;
    verticies[detail * 2].b = 0;
    verticies[detail * 2].tex_x = 0.f;
    verticies[detail * 2].tex_y = 0.f;
    verticies[detail * 2 + 1].x = 0;
    verticies[detail * 2 + 1].y = 0;
    verticies[detail * 2 + 1].z = 0.5f;
    verticies[detail * 2 + 1].r = 0;
    verticies[detail * 2 + 1].g = 0;
    verticies[detail * 2 + 1].b = 1;
    verticies[detail * 2 + 1].tex_x = 1.f;
    verticies[detail * 2 + 1].tex_y = 1.f;

    typedef unsigned int Index;

    size_t indicies_size = sizeof(Index) * (detail * 12);
    Index *indicies = malloc(indicies_size);

    for(int i = 0; i < detail; ++i)
    {
        indicies[i * 6 + 0] = (0 + i);
        indicies[i * 6 + 1] = (1 + i) % detail;
        indicies[i * 6 + 2] = (1 + i) % detail + detail;
        indicies[i * 6 + 3] = (1 + i) % detail + detail;
        indicies[i * 6 + 4] = (0 + i)          + detail;
        indicies[i * 6 + 5] = (0 + i);
    }
    for(int i = 0; i < detail; ++i)
    {
        indicies[(detail + i) * 6 + 0] = detail * 2;
        indicies[(detail + i) * 6 + 1] = (1 + i) % detail;
        indicies[(detail + i) * 6 + 2] = (0 + i);
        indicies[(detail + i) * 6 + 3] = (0 + i)          + detail;
        indicies[(detail + i) * 6 + 4] = (1 + i) % detail + detail;
        indicies[(detail + i) * 6 + 5] = detail * 2 + 1;
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

    mesh->index_count = detail * 12;
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
