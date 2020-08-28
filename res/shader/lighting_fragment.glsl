#version 460 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 UV;  

uniform vec3 u_LightPos; 
uniform vec3 u_ViewPos; 
uniform vec3 u_LightColor;
uniform sampler2D u_Texture;

void main()
{
    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * u_LightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;  
        
    vec3 result = (ambient + diffuse + specular) * texture(u_Texture, UV).rgb;
    FragColor = vec4(result, 1.0);
}
