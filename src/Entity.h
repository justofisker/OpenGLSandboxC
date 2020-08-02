#ifndef ENTITIY_H
#define ENTITIY_H

#include <cglm/cglm.h>

struct Mesh;
typedef float vec3[3];

typedef struct Entity {
    struct Mesh* mesh;
    unsigned int ShaderProgram;
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Entity;

Entity* create_entity_from_mesh(struct Mesh* mesh);
void draw_entity(Entity* entity, mat4 projView);

#endif // ENTITY_H
