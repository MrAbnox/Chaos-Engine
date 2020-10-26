#version 460

in vec3 vertexIn;
in vec3 normalIn;
in vec2 textureIn;

out vec3 vertexOut;
out vec3 normalOut;
out vec2 textureOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	textureOut = textureIn;
	vertexOut = vertexIn;
	normalOut = normalIn;

	gl_Position = projection * view * model * vec4(vertexIn, 1.0f);
}