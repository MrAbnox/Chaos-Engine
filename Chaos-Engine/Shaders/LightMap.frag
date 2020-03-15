#version 460

struct Material 
{
    float shininess;
}; 

uniform sampler2D diffuse;
uniform sampler2D specular;    

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;  
in vec3 normalOut;
in vec2 textureOut;
  
uniform vec3 cameraPos;

uniform Light light;
uniform Material material;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(diffuse, textureOut).rgb;
  	
    // diffuse 
    vec3 norm = normalize(normalOut);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(diffuse, textureOut).rgb;  
    
    // specular
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(specular, textureOut).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 