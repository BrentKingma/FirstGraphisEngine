#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 LightDirection;

struct Light
{
	vec3 m_direction;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;	
};
#define NR_LIGHTS 2
uniform Light lights[NR_LIGHTS];

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 cameraPosition;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

out vec4 FragColour;

vec3 CalcDirLight(Light light, vec3 a_normalNormalised, vec3 a_viewVector)
{
	vec3 lightDir = normalize(light.m_direction);

	//Calculates the lambert term( negate light direction)
	float lambertTerm;

	lambertTerm = max( 0, min( 1, dot( a_normalNormalised, lightDir)));	
	
	vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
	vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;

	vec3 reflectionVector = reflect( lightDir, a_normalNormalised);
	
	float specularTerm = pow(max(0, dot(reflectionVector, a_viewVector)), specularPower);
	
	vec3 diffuse = light.m_diffuse * Kd * texDiffuse * lambertTerm;
	vec3 ambient = light.m_ambient * Ka;
	vec3 specular = light.m_specular * Ks * texSpecular * specularTerm;
	
	return(diffuse + ambient + specular);
}

void main() 
{
	//Ensures that the inputs are normalised
	vec3 normalNormalised = normalize(vNormal);
	vec3 tangentNormalised = normalize(vTangent);
	vec3 biTangentNormalised = normalize(vBiTangent);
	//vec3 lightDirectionNormalised = normalize(LightDirection);
	
	mat3 tbn = mat3( tangentNormalised, biTangentNormalised, normalNormalised );	
	
		vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	normalNormalised = tbn * (texNormal * 2 - 1);
	
	vec3 viewVector = normalize(cameraPosition - vPosition.xyz);
	
	vec3 resualt;
	for(int i = 0; i < NR_LIGHTS; i ++)
	{
		resualt += CalcDirLight(lights[i], normalNormalised, viewVector);
	}
	FragColour =  vec4(resualt, 1);///texture( diffuseTexture, vTexCoord));//vec4(ambient + diffuse + specular, 1);// ;
}