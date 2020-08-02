#ifndef ENTITY_H
#define ENTITY_H

#include <cglm/types.h>

enum EntityType {
    ENTITY_TYPE_MODEL = 0,
    ENTITY_TYPE_SPRITE,
};

typedef struct Entity {
    enum EntityType type;
    void *drawable;
} Entity;

Entity *create_entity(void *drawable, enum EntityType type);
void draw_entity(Entity* entity, mat4 proj_view);

#endif // ENTITY_H
