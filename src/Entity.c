#include "Entity.h"
#include "Mesh.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "Texture.h"

Entity* create_entity(struct Mesh* mesh)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->mesh = mesh;
    memset(entity->position, 0, sizeof(vec3) * 2);
    entity->scale[0] = 1.f;
    entity->scale[1] = 1.f;
    entity->scale[2] = 1.f;
    return entity;
}

void draw_entity(Entity* entity, mat4 projView)
{
    glBindVertexArray(entity->mesh->vertex_array_object);
    glUseProgram(entity->shader_program);

    int mvp_loc = glGetUniformLocation(entity->shader_program, "u_MVP");
    int texture_loc = glGetUniformLocation(entity->shader_program, "u_Texture");

    if(entity->mesh->texture)
    {
        bind_texture(entity->mesh->texture, 0);
        glUniform1i(texture_loc, 0);
    }

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, entity->position);
    glm_scale(model, entity->scale);
    glm_rotate_x(model, entity->rotation[0], model);
    glm_rotate_y(model, entity->rotation[1], model);
    glm_rotate_z(model, entity->rotation[2], model);

    mat4 mvp;
    glm_mul(projView, model, mvp);

    glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, mvp[0]);

    glDrawElements(GL_TRIANGLES, entity->mesh->index_count, entity->mesh->index_type, NULL);

    glBindVertexArray(0);
}
