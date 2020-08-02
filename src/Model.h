#ifndef ENTITIY_H
#define ENTITIY_H

#include <cglm/cglm.h>

struct Mesh;
typedef float vec3[3];

typedef struct Model {
    struct Mesh* mesh;
    unsigned int shader_program;
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Model;

Model* create_model(struct Mesh* mesh);
void draw_model(Model* entity, mat4 projView);

#endif // ENTITY_H
