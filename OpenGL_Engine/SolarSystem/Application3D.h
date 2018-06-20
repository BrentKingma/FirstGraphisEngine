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
	void ImGUI();

	Camera m_camera;

	float m_moveSpeed = 10;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	aie::ShaderProgram m_Shader;
	//Soul Spear
	aie::OBJMesh m_soulspearMesh;
	glm::mat4 m_soulspearTransform;
	aie::Texture m_soulspearTexture;
	//Bunny
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	aie::Texture m_bunnyTexture;
	//C3PO
	aie::OBJMesh m_c3poMesh;
	glm::mat4 m_c3poTransform;
	aie::Texture m_c3poTexture;

	glm::vec3 m_ambientLight;//la

	glm::vec3 materialDiffuse;
	glm::vec3 materialSpecular;
	glm::vec3 materialAmbientLight;
	float materialSpecturalPower;
	
	float xDir1, yDir1, zDir1 = 0.0f;
	float xDir2, yDir2, zDir2 = 0.0f;

	const char* m_vertShader = "./shaders/bunnyShader.vert";
	const char* m_fragShader = "./shaders/bunnyShader.frag";

	const char* m_quadVertShader = "./shaders/textured.vert";
	const char* m_quadFragShader = "./shaders/textured.frag";
};

