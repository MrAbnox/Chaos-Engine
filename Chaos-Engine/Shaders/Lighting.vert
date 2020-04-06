#version 460

in vec3 vertexIn;
in vec3 normalIn;
in vec2 textureIn;
in vec3 tangentIn;
in vec3 bitangentIn;

out vec3 FragPos;
out vec3 vertexOut;
out vec3 normalOut;
out vec2 textureOut;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{

	vertexOut = vertexIn;
	textureOut = textureIn;
	normalOut = mat3(transpose(inverse(model))) * normalIn;

	
    vec3 T = normalize(mat3(model) * tangentIn);
    vec3 B = normalize(mat3(model) * bitangentIn);
    vec3 N = normalize(mat3(model) * normalIn);
    
    mat3 TBN = transpose(mat3(T, B, N));

	TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * cameraPos;
    TangentFragPos  = TBN * FragPos;

	FragPos = vec3(model * vec4(vertexIn, 1.0f));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);

	gl_Position = projection * view * vec4(FragPos, 1.0f);
}