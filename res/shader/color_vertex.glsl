#version 460

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec3 v_Color;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * v_Position;
    Color = vec4(v_Color, 1.f);
}
