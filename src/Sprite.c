#include "Sprite.h"
#include "Util.h"
#include "Texture.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

static int initialized = 0;
static unsigned int VertexArrayObject, VertexBuffer, IndexBuffer, ShaderProgram;
static unsigned int MVP_loc, Texture_loc;

typedef struct Vertex {
    float x, y;
    float tex_x, tex_y;
} Vertex;

static Vertex verticies[4] = {
    {-1.f, -1.f  ,  0.f, 0.f},
    { 1.f, -1.f  ,  1.f, 0.f},
    { 1.f,  1.f  ,  1.f, 1.f},
    {-1.f,  1.f  ,  0.f, 1.f},
};

typedef unsigned char Index;

static Index indicies[6] = {
    0, 1, 2,
    2, 3, 0,
};

Sprite* create_sprite(Texture *texture)
{
    Sprite *sprite = malloc(sizeof(Sprite));

    if(!initialized)
    {
        glGenVertexArrays(1, &VertexArrayObject);
        glBindVertexArray(VertexArrayObject);

        glGenBuffers(1, &VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), &verticies, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_x));

        glGenBuffers(1, &IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), &indicies, GL_STATIC_DRAW);

        ShaderProgram = compile_shader("res/shader/sprite_vertex.glsl", "res/shader/sprite_fragment.glsl");

        MVP_loc = glGetUniformLocation(ShaderProgram, "u_MVP");
        Texture_loc = glGetUniformLocation(ShaderProgram, "u_Texture");

        initialized = 1;
    }

    sprite->texture = texture;
    sprite->position[0] = 0.f;
    sprite->position[1] = 0.f;
    sprite->rotation = 0.f;

    return sprite;
}

void draw_sprite(Sprite* sprite)
{
    int Viewport[4];
    glGetIntegerv(GL_VIEWPORT, Viewport);

    glBindVertexArray(VertexArrayObject);
    glUseProgram(ShaderProgram);

    bind_texture(sprite->texture, 0);
    glUniform1i(Texture_loc, 0);

    mat4 proj = GLM_MAT4_IDENTITY_INIT;
    glm_ortho((float)Viewport[0], (float)Viewport[2], (float)Viewport[1], (float)Viewport[3], 0.f, 1.f, proj);
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){sprite->position[0] - (float)sprite->texture->width / 2, sprite->position[1] - (float)sprite->texture->height / 2, 0.f});
    glm_scale(model, (vec3){(float)sprite->texture->width, (float)sprite->texture->height, 0.f});

    mat4 mvp;
    glm_mat4_mul(proj, model, mvp);
    //glm_mat4_mulN((mat4 *[]){&proj, &view, &model}, 3, mvp);

    glUniformMatrix4fv(MVP_loc, 1, GL_FALSE, mvp[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
    
    glBindVertexArray(0);
}
