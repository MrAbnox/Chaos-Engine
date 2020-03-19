#version 460

in vec3 vertexIn;
in vec3 normalIn;

out vec3 normalOut;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    normalOut = mat3(transpose(inverse(model))) * normalIn;
    FragPos = vec3(model * vec4(vertexIn, 1.0));
    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}