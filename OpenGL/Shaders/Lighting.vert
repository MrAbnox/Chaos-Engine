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
	normalOut = mat3(transpose(inverse(model))) * normalIn;

	FragPos = vec3(model * vec4(vertexIn, 1.0f));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);

	gl_Position = projection * view * vec4(FragPos, 1.0);
}