#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct Texture {
    unsigned int texture_id;
    unsigned int width, height;
    unsigned int bpp;
} Texture;

Texture* create_texture(const char* file_path, int texture_min_filter, int texture_mag_filter, int texture_wrap);
void bind_texture(Texture* texture, unsigned int slot);

#endif // TEXTURE_H
