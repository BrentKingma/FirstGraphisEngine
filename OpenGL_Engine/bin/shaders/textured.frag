#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec4 vPosition;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 LightDirection;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 cameraPosition;

uniform sampler2D diffuseTexture;

out vec4 FragColour;

void main() 
{
	//Ensures that the normal and light direction is normalised
	vec3 normalNormalised = normalize(vNormal);
	vec3 lightDirectionNormalised = normalize(LightDirection);
	
	//Calculates the lambert term( negate light direction)
	float lambertTerm = max( 0, min( 1, dot( normalNormalised, -lightDirectionNormalised)));
	
	vec3 viewVector = normalize(cameraPosition - vPosition.xyz);
	vec3 reflectionVector = reflect( lightDirectionNormalised, normalNormalised);
	
	float specularTerm = pow(max(0, dot(reflectionVector, viewVector)), specularPower);
	
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 ambient = Ia * Ka;
	vec3 specular = Is * Ks * specularTerm;

	FragColour =  vec4(ambient + diffuse + specular, 1);// * texture( diffuseTexture, vTexCoord);
}