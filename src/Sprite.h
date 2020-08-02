#ifndef SPRITE_H
#define SPRITE_H

struct Texture;
typedef float vec2[2];

typedef struct Sprite {
    struct Texture* texture;
    vec2 position;
    vec2 scale;
    float rotation;
} Sprite;

Sprite* create_sprite(struct Texture *sprite);
void draw_sprite(Sprite *sprite);

#endif // SPRITE_H
