#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <Camera.h>
#include <Mesh.h>
#include <Shader.h>
#include <OBJMesh.h>

class Application3D : public Application
{
public:
	Application3D();
	virtual ~Application3D();

	virtual int startup();
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void shutdown();

private:
	Camera m_camera;

	float m_moveSpeed = 10;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;


	aie::ShaderProgram m_quadShader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	aie::Texture m_gridTexture;

	aie::ShaderProgram m_bunnyShader;
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	aie::Texture m_texture;

	aie::ShaderProgram m_swordShader;
	aie::OBJMesh m_swordMesh;
	glm::mat4 m_swordTransform;
	aie::Texture m_swordTexture;

	struct Light
	{
		glm::vec3 direction;//ld
		glm::vec3 diffuse;//ld
		glm::vec3 specular;//ls
	};
	Light m_light;
	glm::vec3 m_ambientLight;//la

	glm::vec3 materialDiffuse;
	glm::vec3 materialSpecular;
	glm::vec3 materialAmbientLight;
	float materialSpecturalPower;
	

	const char* m_vertShader = "./shaders/bunnyShader.vert";
	const char* m_fragShader = "./shaders/bunnyShader.frag";

	const char* m_quadVertShader = "./shaders/textured.vert";
	const char* m_quadFragShader = "./shaders/textured.frag";
};

