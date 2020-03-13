#version 460
in vec3 vertexIn;
in vec3 normalIn;
in vec2 textureIn;

out vec3 FragPos;
out vec3 normalOut;
out vec2 textureOut;

out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    textureOut = textureIn;

    FragPos = vec3(model * vec4(vertexIn, 1.0));
    normalOut = mat3(transpose(inverse(model))) * normalIn;  
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);    

    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}