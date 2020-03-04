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

in vec2 textureOut;

uniform vec3 cameraPos;

uniform int isTextured;
uniform int isDoubleTextured;

uniform sampler2D textureImage1;
uniform sampler2D textureImage2;

out vec4 FragColor;

out vec3 Ambient;
out vec3 Diffuse;
out vec3 Specular;
 
in vec3 FragPos;
in vec3 normalOut;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//----------------------------------------------------------------
//Main
//----------------------------------------------------------------
void main()
{
    // properties
    vec3 norm = normalize(normalOut);
    vec3 viewDir = normalize(cameraPos - FragPos);
    
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
			FragColor = vec4(result, 1.0)* texture(textureImage1, textureOut);
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
    vec3 lightDir = normalize(-light.direction);

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

    return (ambient + diffuse + specular);
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