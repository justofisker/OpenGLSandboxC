#ifndef ENTITIY_H
#define ENTITIY_H

#include <cglm/cglm.h>

typedef struct _Mesh Mesh;
typedef float vec3[3];

typedef struct _Model {
    Mesh *mesh;
    unsigned int shader_program;
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Model;

Model* create_model(Mesh *mesh);
void draw_model(Model *entity);

#endif // ENTITY_H
