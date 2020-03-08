#version 460

in vec3 position;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
	gl_Position =  model * lightSpaceMatrix * vec4(position, 1.0);
}
