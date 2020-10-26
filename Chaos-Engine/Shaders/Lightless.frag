#version 460

out vec4 FragColor;

in vec2 textureOut;
in vec3 colorOut;

uniform int isTextured;

uniform sampler2D textureImage1;

void main()
{
	if(isTextured == 1)
	{
		FragColor = vec4(colorOut, 1.0)* texture(textureImage1, textureOut); // set all 4 vector values to 1.0
	}
	else
	{
		FragColor = vec4(colorOut, 1.0);
	}
}