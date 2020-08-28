#version 460 core
layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec2 v_UV;
layout (location = 2) in vec3 v_Normal;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    FragPos = vec3(u_Model * vec4(v_Position, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * v_Normal;  
    UV = v_UV;
    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}
