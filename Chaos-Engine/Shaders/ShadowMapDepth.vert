#version 460
in vec3 vertexIn;
in vec2 textureIn;

out vec2 textureOut;

void main()
{
    textureOut = textureIn;

    gl_Position = vec4(vertexIn, 1.0);
}