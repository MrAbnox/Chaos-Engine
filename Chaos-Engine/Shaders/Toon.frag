#version 460

in vec3 vertexOut;
in vec3 normalOut;
in vec2 textureOut;

out vec4 FragColor;

struct LightInfo
{
	vec3 position;
	vec3 intensity;
};

struct Material
{
	vec3 diffuse; //Diffuse reflectivity
	vec3 ambient; //Ambient reflectivity
	vec3 color;
};

uniform Material material;
uniform LightInfo light;

uniform int toon;
uniform mat4 model;
uniform vec3 position;
uniform vec3 cameraPos;

vec3 outlineColor = vec3(0.0f, 0.0f, 0.0f);
float ambientLight = 0.6f;
float outlineLitThickness = 0.6f;
float outlineUnlitThickness = 0.6f;

uniform sampler2D textureImage1;

const int levels = 3;
const float scaleFactor = 1.0f / levels;

vec3 ToonShade()
{
	vec3 s = normalize(light.position.xyz - vertexOut.xyz);
	float cosine = max(0.0, dot(s, normalOut));
	vec3 diffuse = material.diffuse * floor(cosine * levels) * scaleFactor;

	return light.intensity * (material.ambient + diffuse);
}

vec3 ToonShadeTwo();

void main()
{
	if(toon == 1)
	{
		vec3 toon = ToonShade();
		FragColor = vec4(toon, 1.0f) * texture(textureImage1, textureOut);
	}
	else if(toon == 0)
	{
		vec3 toon = ToonShadeTwo();
		FragColor = vec4(toon, 1.0f) * texture(textureImage1, textureOut);
	}
}



vec3 ToonShadeTwo()
{
	float toonThresholds[2];
    toonThresholds[0] = 0.8;
    toonThresholds[1] = 0.05;

    float toonLevels[2];
    toonLevels[0] = 1.0;
    toonLevels[1] = 0.6;
    
	 // get outline treshold
	 vec3 worldPosition = (model * vec4(position, 1.0)).xyz;
	 vec3 worldNormal = normalize(vec3(model * vec4(normalOut, 0.0)));
	 vec3 lightVector = normalize(light.position - worldPosition);

	 float outlineTest = mix(
	     outlineUnlitThickness,
	     outlineLitThickness,
	     max(0.0, dot(worldNormal, lightVector)));
	 
	 // apply outline
	 if (dot(normalize(cameraPos), worldNormal) < outlineTest) 
	 {
	    return vec3(outlineColor);
	 }
	 else {

	     // get light direction vector
	     vec3 lightVectorW = normalize(vec3(vec4(light.position, 1.0) * model) - position);
	     
	     // diffuse lighting
	     float ndl = max(0.0, dot(normalOut, lightVectorW));
	     
	     // get toon level
	     float level = ambientLight;

	     for (int i = 0; i < 1; ++i)
		 {
	         if (ndl > toonThresholds[i]) 
			 {
	             level += toonLevels[i];
	             break;
	         }
	     }
	     
	vec3 color = material.color * level;

	return color;
	}
}