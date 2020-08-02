#include "Texture.h"
#include <glad/glad.h>
#include <stdlib.h>
#include <stb/stb_image.h>

Texture* generate_texture_from_file(const char* file_path, int texture_wrap)
{
    Texture* texture = malloc(sizeof(Texture));

    unsigned char *localbuffer;

    stbi_set_flip_vertically_on_load(1);
    localbuffer = stbi_load(file_path, &texture->Width, &texture->Height, &texture->BBP, 4);

    glGenTextures(1, &texture->TextureID);
    glBindTexture(GL_TEXTURE_2D, texture->TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->Width, texture->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    if(localbuffer)
        stbi_image_free(localbuffer);

    return texture;
}

void bind_texture(Texture* texture, unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->TextureID);
}
