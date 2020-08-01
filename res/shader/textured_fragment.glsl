#version 460

in vec4 Color;
in vec2 TexCoord;

layout(location = 0) out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = Color;
    FragColor = texture(u_Texture, TexCoord) * Color;
}
