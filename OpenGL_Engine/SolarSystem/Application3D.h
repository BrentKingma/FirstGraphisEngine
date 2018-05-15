#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <Camera.h>
#include <Mesh.h>
#include <Shader.h>

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

	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	aie::ShaderProgram m_shader;
};

