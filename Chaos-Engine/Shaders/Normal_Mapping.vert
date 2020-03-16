#version 460
in vec3 vertexIn;
in vec3 normalIn;
in vec2 textureIn;
in vec3 tangentIn;

out vec2 textureOut;
out vec3 vertexOut;
out vec3 normalOut;
out vec3 FragPos;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    FragPos = vec3(model * vec4(vertexIn, 1.0));   
    textureOut = textureIn;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangentIn);
    vec3 N = normalize(normalIn * normalMatrix);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * FragPos;
        
    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}