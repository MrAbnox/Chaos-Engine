#version 460

in vec3 vertexIn;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = vertexIn;
    vec4 pos = projection * view * vec4(vertexIn, 1.0);
    gl_Position = pos.xyww;
}  