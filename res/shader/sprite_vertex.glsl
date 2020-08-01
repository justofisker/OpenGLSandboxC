#version 460

layout(location = 0) in vec4 v_Position;

out vec2 TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * v_Position;
    TexCoord = vec2(v_Position.x, v_Position.y);
}
