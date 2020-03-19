#version 460

out vec4 FragColor;

in vec3 normalOut;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    vec3 I = normalize(FragPos - cameraPos);
    vec3 R = reflect(I, normalize(normalOut));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}