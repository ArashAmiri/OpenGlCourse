#version 330											

in vec4 vCol;											
in vec2 TexCoord;
in vec3 Normal;	
in vec3 FragPos;													

out vec4 color;	

struct DirectionLight 
{
    vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material
{
    float specularIntensity;
	float shininess;
};

uniform sampler2D theTexture;										
uniform DirectionLight directionLight;
uniform Material material;

uniform vec3 eyePosition;

void main()												
{
    vec4 ambientColor = vec4(directionLight.color, 1.0f) * directionLight.ambientIntensity;
    
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionLight.direction)), 0.0f);
    vec4 diffuseColor = vec4(directionLight.color, 1.0f) * directionLight.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0, 0, 0, 0);
	
	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(directionLight.direction, normalize(Normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(directionLight.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	color = texture(theTexture, TexCoord) * (ambientColor + diffuseColor + specularColor);	
}