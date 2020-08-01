#ifndef SPRITE_H
#define SPRITE_H

struct Texture;

typedef struct Sprite {
    struct Texture* texture;
} Sprite;

Sprite* create_sprite_from_file(const char* file_path);
void draw_sprite(Sprite* sprite, unsigned int x, unsigned int y);

#endif // SPRITE_H
