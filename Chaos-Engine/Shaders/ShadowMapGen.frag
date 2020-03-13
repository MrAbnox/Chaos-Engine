#version 460

out vec4 FragColor;

void main()
{
	//THIS shouldn't be used in basic shadow generation
	
	FragColor = vec4(gl_FragCoord.z);
}