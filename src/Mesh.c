#include "Mesh.h"
#include "Util.h"
#include "Texture.h"
#include <glad/glad.h>
#include <cglm/cglm.h>

Mesh *create_cube_mesh(float size)
{
    typedef struct vertex
    {
        vec3 position;
        vec2 uv;
        vec3 normal;
    } Vertex;

    Vertex verticies[] = {
        {-0.5f * size, -0.5f * size,  0.5f * size  ,  0.0f, 0.0f  ,  0.0f,  0.0f,  1.0f},
        { 0.5f * size, -0.5f * size,  0.5f * size  ,  1.0f, 0.0f  ,  0.0f,  0.0f,  1.0f},
        { 0.5f * size,  0.5f * size,  0.5f * size  ,  1.0f, 1.0f  ,  0.0f,  0.0f,  1.0f},
        {-0.5f * size,  0.5f * size,  0.5f * size  ,  0.0f, 1.0f  ,  0.0f,  0.0f,  1.0f},
        { 0.5f * size, -0.5f * size,  0.5f * size  ,  0.0f, 0.0f  ,  1.0f,  0.0f,  0.0f},
        { 0.5f * size, -0.5f * size, -0.5f * size  ,  1.0f, 0.0f  ,  1.0f,  0.0f,  0.0f},
        { 0.5f * size,  0.5f * size, -0.5f * size  ,  1.0f, 1.0f  ,  1.0f,  0.0f,  0.0f},
        { 0.5f * size,  0.5f * size,  0.5f * size  ,  0.0f, 1.0f  ,  1.0f,  0.0f,  0.0f},
        { 0.5f * size,  0.5f * size, -0.5f * size  ,  0.0f, 0.0f  ,  0.0f,  0.0f, -1.0f},
        { 0.5f * size, -0.5f * size, -0.5f * size  ,  1.0f, 0.0f  ,  0.0f,  0.0f, -1.0f},
        {-0.5f * size, -0.5f * size, -0.5f * size  ,  1.0f, 1.0f  ,  0.0f,  0.0f, -1.0f},
        {-0.5f * size,  0.5f * size, -0.5f * size  ,  0.0f, 1.0f  ,  0.0f,  0.0f, -1.0f},
        {-0.5f * size,  0.5f * size, -0.5f * size  ,  0.0f, 0.0f  , -1.0f,  0.0f,  0.0f},
        {-0.5f * size, -0.5f * size, -0.5f * size  ,  1.0f, 0.0f  , -1.0f,  0.0f,  0.0f},
        {-0.5f * size, -0.5f * size,  0.5f * size  ,  1.0f, 1.0f  , -1.0f,  0.0f,  0.0f},
        {-0.5f * size,  0.5f * size,  0.5f * size  ,  0.0f, 1.0f  , -1.0f,  0.0f,  0.0f},
        { 0.5f * size, -0.5f * size, -0.5f * size  ,  0.0f, 0.0f  ,  0.0f, -1.0f,  0.0f},
        { 0.5f * size, -0.5f * size,  0.5f * size  ,  1.0f, 0.0f  ,  0.0f, -1.0f,  0.0f},
        {-0.5f * size, -0.5f * size,  0.5f * size  ,  1.0f, 1.0f  ,  0.0f, -1.0f,  0.0f},
        {-0.5f * size, -0.5f * size, -0.5f * size  ,  0.0f, 1.0f  ,  0.0f, -1.0f,  0.0f},
        { 0.5f * size,  0.5f * size,  0.5f * size  ,  0.0f, 0.0f  ,  0.0f,  1.0f,  0.0f},
        { 0.5f * size,  0.5f * size, -0.5f * size  ,  1.0f, 0.0f  ,  0.0f,  1.0f,  0.0f},
        {-0.5f * size,  0.5f * size, -0.5f * size  ,  1.0f, 1.0f  ,  0.0f,  1.0f,  0.0f},
        {-0.5f * size,  0.5f * size,  0.5f * size  ,  0.0f, 1.0f  ,  0.0f,  1.0f,  0.0f},
    };

    typedef unsigned char Index;

    static Index indicies[] = {
        0 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0, 2 + 4 * 0, 3 + 4 * 0, 0 + 4 * 0,
        0 + 4 * 1, 1 + 4 * 1, 2 + 4 * 1, 2 + 4 * 1, 3 + 4 * 1, 0 + 4 * 1,
        0 + 4 * 2, 1 + 4 * 2, 2 + 4 * 2, 2 + 4 * 2, 3 + 4 * 2, 0 + 4 * 2,
        0 + 4 * 3, 1 + 4 * 3, 2 + 4 * 3, 2 + 4 * 3, 3 + 4 * 3, 0 + 4 * 3,
        0 + 4 * 4, 1 + 4 * 4, 2 + 4 * 4, 2 + 4 * 4, 3 + 4 * 4, 0 + 4 * 4,
        0 + 4 * 5, 1 + 4 * 5, 2 + 4 * 5, 2 + 4 * 5, 3 + 4 * 5, 0 + 4 * 5,
    };

    Mesh *mesh = malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->vertex_array_object);
    glBindVertexArray(mesh->vertex_array_object);

    glGenBuffers(1, &mesh->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

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
        vec3 position;
        vec2 uv;
        vec3 normal;
    } Vertex;
                                                                    // V for top and bottom faces
                                                                // V for last 2 side verticies
                                                            // V for top and bottom center vertex
    size_t verticies_size = sizeof(Vertex) * (_verticies * (2 + 2) + 6);
    Vertex *verticies = malloc(verticies_size);

    int verticie_count = _verticies + 1;
    int i;
    for(i = 0; i < _verticies + 1; ++i)
    {
        float theta = GLM_PIf * 2 / _verticies * i;
        float x_unscaled = cosf(theta);
        float y_unscaled = sinf(theta);
        float x = x_unscaled * radius;
        float y = y_unscaled * radius;

        // Sides [0 -> verticies_count * 2 - 1]
        verticies[i].position[0] = x;
        verticies[i].position[1] = y;
        verticies[i].position[2] = -.5f * depth;
        verticies[i].normal[0] = x_unscaled;
        verticies[i].normal[1] = y_unscaled;
        verticies[i].normal[2] = 0;
        verticies[i].uv[0] = theta / (2 * GLM_PIf);
        verticies[i].uv[1] = 0.f;

        verticies[i + verticie_count].position[0] = x;
        verticies[i + verticie_count].position[1] = y;
        verticies[i + verticie_count].position[2] = .5f * depth;
        verticies[i + verticie_count].normal[0] = x_unscaled;
        verticies[i + verticie_count].normal[1] = y_unscaled;
        verticies[i + verticie_count].normal[2] = 0;
        verticies[i + verticie_count].uv[0] = theta / (2 * GLM_PIf);
        verticies[i + verticie_count].uv[1] = 1.f;

        // Top / Bottom Faces [verticies_count * 2 -> verticies_count * 4 - 1]
        verticies[i + verticie_count * 2].position[0] = x;
        verticies[i + verticie_count * 2].position[1] = y;
        verticies[i + verticie_count * 2].position[2] = -.5f * depth;
        verticies[i + verticie_count * 2].uv[0] = x_unscaled * 0.5f + 0.5f;
        verticies[i + verticie_count * 2].uv[1] = y_unscaled * 0.5f + 0.5f;
        verticies[i + verticie_count * 2].normal[0] = 0.0f;
        verticies[i + verticie_count * 2].normal[1] = -1.0f;
        verticies[i + verticie_count * 2].normal[2] = 0.0f;

        verticies[i + verticie_count * 3].position[0] = x;
        verticies[i + verticie_count * 3].position[1] = y;
        verticies[i + verticie_count * 3].position[2] = .5f * depth;
        verticies[i + verticie_count * 3].uv[0] = x_unscaled * 0.5f + 0.5f;
        verticies[i + verticie_count * 3].uv[1] = y_unscaled * 0.5f + 0.5f;
        verticies[i + verticie_count * 3].normal[0] = 0.0f;
        verticies[i + verticie_count * 3].normal[1] = 1.0f;
        verticies[i + verticie_count * 3].normal[2] = 0.0f;

    }
    {
        // Center vertex for Top / Bottom Faces

        verticies[verticie_count * 4 + 0].position[0] = 0;
        verticies[verticie_count * 4 + 0].position[1] = 0;
        verticies[verticie_count * 4 + 0].position[2] = -0.5f * depth;
        verticies[verticie_count * 4 + 0].normal[0] = 0.0f;
        verticies[verticie_count * 4 + 0].normal[1] = 0.0f;
        verticies[verticie_count * 4 + 0].normal[2] = -1.0f;
        verticies[verticie_count * 4 + 0].uv[0] = 0.5f;
        verticies[verticie_count * 4 + 0].uv[1] = 0.5f;
        verticies[verticie_count * 4 + 1].position[0] = 0;
        verticies[verticie_count * 4 + 1].position[1] = 0;
        verticies[verticie_count * 4 + 1].position[2] = 0.5f * depth;
        verticies[verticie_count * 4 + 1].normal[0] = 0.0f;
        verticies[verticie_count * 4 + 1].normal[1] = 0.0f;
        verticies[verticie_count * 4 + 1].normal[2] = 1.0f;
        verticies[verticie_count * 4 + 1].uv[0] = 0.5f;
        verticies[verticie_count * 4 + 1].uv[1] = 0.5f;
    }

    typedef unsigned int Index;

    size_t indicies_size = sizeof(Index) * (_verticies * (6 + 6) + 2);
    Index *indicies = malloc(indicies_size);

    for(i = 0; i < _verticies; ++i)
    {
        int offset = i * 6;
        indicies[offset + 0] = i + 0;
        indicies[offset + 1] = i + verticie_count + 1;
        indicies[offset + 2] = i + verticie_count;
        indicies[offset + 3] = indicies[offset + 0];
        indicies[offset + 4] = i + 1;
        indicies[offset + 5] = indicies[offset + 1];
    }
    for(i = 0; i < _verticies; ++i)
    {
        int offset = 6 * _verticies + i * 6;
        indicies[offset + 0] = verticie_count * 3 + 0 + i;
        indicies[offset + 1] = verticie_count * 3 + 1 + i;
        indicies[offset + 2] = verticie_count * 4 + 1;
        indicies[offset + 3] = verticie_count * 4 + 0;
        indicies[offset + 4] = verticie_count * 2 + 1 + i;
        indicies[offset + 5] = verticie_count * 2 + 0 + i;
    }

    Mesh* mesh = malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->vertex_array_object);
    glBindVertexArray(mesh->vertex_array_object);

    glGenBuffers(1, &mesh->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, verticies_size, verticies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

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
