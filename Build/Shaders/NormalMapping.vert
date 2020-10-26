#version 460
in vec3 vertexIn;
in vec3 normalIn;
in vec2 textureIn;
in vec3 tangentIn;
in vec3 bitangentIn;

out vec2 textureOut;
out vec3 vertexOut;
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
    
    //Using normal Method
//    mat3 normalMatrix = transpose(inverse(mat3(model)));
//    vec3 T = normalize(normalMatrix * tangentIn);
//    vec3 N = normalize(normalIn * normalMatrix);
//    T = normalize(T - dot(T, N) * N);
//    vec3 B = cross(N, T);
//    
//    mat3 TBN = transpose(mat3(T, B, N));    

    vec3 T = normalize(mat3(model) * tangentIn);
    vec3 B = normalize(mat3(model) * bitangentIn);
    vec3 N = normalize(mat3(model) * normalIn);
    
    mat3 TBN = transpose(mat3(T, B, N));


//    //Using the Gram-Schmidt process
//    vec3 T = normalize(vec3(model * vec4(tangentIn, 0.0)));
//    vec3 N = normalize(vec3(model * vec4(normalIn, 0.0)));
//    // re-orthogonalize T with respect to N
//    T = normalize(T - dot(T, N) * N);
//    // then retrieve perpendicular vector B with the cross product of T and N
//    vec3 B = cross(N, T);
//    
//    mat3 TBN = mat3(T, B, N);
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * FragPos;
        
    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}