#pragma once
#include <vector>
#include <glm\glm.hpp>
class Light
{
public:
	Light()
	{
		m_direction = { 0, 0, 0 };
		m_ambient = { 0, 0, 0 };
		m_diffuse = { 0, 0, 0 };
		m_specular = { 0, 0, 0 };
	}
	Light(glm::vec3 a_direction, glm::vec3 a_ambient, glm::vec3 a_diffuse, glm::vec3 a_specular)
	{
		m_direction = a_direction;
		m_ambient = a_ambient;
		m_diffuse = a_diffuse;
		m_specular = a_specular;
	}

	static std::vector<Light*> m_lights;
	static void AddLight(Light* a_light)
	{
		m_lights.push_back(a_light);
	}

	glm::vec3* GetDirection() { return &m_direction; }
	glm::vec3* GetAmbient() { return &m_ambient; }
	glm::vec3* GetDiffuse() { return &m_diffuse; }
	glm::vec3* GetSpecular() { return &m_specular; }

protected:
	glm::vec3 m_direction;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;	
};
