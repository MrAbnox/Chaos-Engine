#version 460

vec3 position;

uniform mat4 Model;
uniform mat4 Proj;
uniform mat4 View;

void main()
{
	gl_Position =  Model * View * Proj * vec4(position, 1.0);
}
