#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct Texture {
    unsigned int TextureID;
    unsigned int Width, Height;
    unsigned int BBP;
} Texture;

Texture* generate_texture_from_file(const char* file_path, int texture_wrap);
void bind_texture(Texture* texture, unsigned int slot);

#endif // TEXTURE_H
