#include "Entity.h"
#include <stdlib.h>

#include "Model.h"
#include "Sprite.h"

Entity *create_entity(void *drawable, enum EntityType type)
{
    Entity *entity = malloc(sizeof(Entity));

    entity->drawable = drawable;
    entity->type = type;

    return entity;
}

void draw_entity(Entity *entity, mat4 proj_view)
{
    switch(entity->type)
    {
    case ENTITY_TYPE_MODEL:
        draw_model((Model*)entity->drawable, proj_view);
        break;
    case ENTITY_TYPE_SPRITE:
        draw_sprite((Sprite*)entity->drawable);
        break;
    }
}
