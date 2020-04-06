#version 460

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight 
{
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight
{    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec4 FragPosLightSpace;

uniform int numberSpotLights;
uniform int numberPointLights;
uniform int isDirectionalLight;

#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform DirLight dirLight;
uniform Material material;
uniform SpotLight spotLight; 


uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform int isTextured;
uniform int isDoubleTextured;

uniform sampler2D textureImage1;
uniform sampler2D textureImage2;

uniform sampler2D normalMap;
uniform sampler2D heightMap;

uniform sampler2D shadowMap;

out vec4 FragColor;

out vec3 Ambient;
out vec3 Diffuse;
out vec3 Specular;
 
in vec3 FragPos;
in vec3 normalOut;
in vec3 vertexOut;
in vec2 textureOut;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform float heightScale;
uniform int isNormalMapped;
uniform int isShadowMapped;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

//----------------------------------------------------------------
//Main
//----------------------------------------------------------------
void main()
{
      // properties
    vec3 viewDir;
    vec3 norm = normalize(normalOut);

    if(isNormalMapped == 1)
    {
          // offset texture coordinates with Parallax Mapping
        viewDir = normalize(TangentViewPos - TangentFragPos);
    }
    else
    {
        viewDir = normalize(cameraPos - FragPos);
    }

    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result;
    
    if(isDirectionalLight > 0)
    {
        result += CalcDirLight(dirLight, norm, viewDir);
    }

    // phase 2: point lights

    if(numberPointLights > 0)
    {
        for(int i = 0; i < numberPointLights; i++)
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // phase 3: spot light
    if(numberSpotLights > 0)
    { 
        for(int i = 0; i < numberPointLights; i++)
            result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    }

    //Check if it is Textured
	if(isTextured == 1)
	{
		if(isDoubleTextured == 1)
		{
			FragColor = vec4(result, 1.0)* mix(texture(textureImage1, textureOut),
											   texture(textureImage2, textureOut), 0.3f);
		}
		else
		{
			FragColor = vec4(result, 1.0);
		}
	}
    else
    {
        FragColor = vec4(result, 1.0);
    }
}

//----------------------------------------------------------------
// calculates the color when using a directional light.
//----------------------------------------------------------------
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    if(isNormalMapped == 1)
    {
        vec3 color = texture(textureImage1, textureOut).rgb;

        vec2 texCoords = textureOut;
        
        texCoords = ParallaxMapping(textureOut,  viewDir);       
        if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
            discard;
        
        // obtain normal from normal map
        vec3 normals = texture(normalMap, texCoords).rgb;
        normals = normalize(normals * 2.0 - 1.0);
	    //ambient
	    vec3 ambient;
        vec3 tdiffuse;
        vec3 diffuse;
	    //diffuse
        vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
        float diff = max(dot(lightDir, normals), 0.0);
        if(isShadowMapped == 1)
        {
	        ambient = light.ambient * material.ambient;
            tdiffuse = light.diffuse * diff * material.diffuse;
            diffuse = tdiffuse * diff;
        }
        else
        {
            ambient = 0.1 * color;
            diffuse = diff * color;
        }
	    //specular
        vec3 reflectDir = reflect(-lightDir, normals);
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(normals, halfwayDir), 0.0), material.shininess);


        vec3 specular = vec3(0.2) * spec;

        vec3 lighting;

        if(isShadowMapped == 1)
        {
            //Calculate Shadows
            float shadow = ShadowCalculation(FragPosLightSpace);
            lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
        }
        else if (isShadowMapped == 0);
        {
            lighting = (ambient + diffuse + specular);
        }

        return (lighting);
    }
    else //it it is not normal mapped
    {
        vec3 lightDir = normalize(-light.direction);
        vec3 color = texture(textureImage1, textureOut).rgb;
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);

        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // combine results

	    //ambient
	    vec3 ambient = light.ambient * material.ambient;

	    //diffuse
	    vec3 diffuse = light.diffuse * (diff * material.diffuse);

	    //specular
        vec3 specular = Specular = light.specular * (spec * material.specular); 
        vec3 lighting;

        if(isShadowMapped == 1)
        {
            //Calculate Shadows
            float shadow = ShadowCalculation(FragPosLightSpace);
            lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
        }
        else
        {
            lighting = (ambient + diffuse + specular);
        }

         return (lighting);

    }
}

//----------------------------------------------------------------
// calculates the color when using a point light.
//----------------------------------------------------------------
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // combine results

	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
    vec3 specular = Specular = light.specular * (spec * material.specular); 

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

//----------------------------------------------------------------
// calculates the color when using a spot light.
//----------------------------------------------------------------
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results

	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
    vec3 specular = Specular = light.specular * (spec * material.specular); 

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
//----------------------------------------------------------------
// calculates the color when using a spot light.
//----------------------------------------------------------------
float ShadowCalculation(vec4 fragPosLightSpace)
{
    //Perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    //Transform to [0,1] range
    projCoords = projCoords * 0.5f + 0.5f;

    //Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    //Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    //Check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
//    float height =  texture(heightMap, texCoords).r;     
//    return texCoords - viewDir.xy * (height * heightScale);  
//    
//
    //Ambient Occlusion Parallax Mapping
       // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(heightMap, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(heightMap, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(heightMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}
