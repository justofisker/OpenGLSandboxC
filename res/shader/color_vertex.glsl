#version 460

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec3 v_Color;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * v_Position;
    Color = vec4(v_Color, 1.f);
}
