#include "Application3D.h"
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <GLFW\glfw3.h>

Application3D::Application3D()
{
	
}


Application3D::~Application3D()
{
}

int Application3D::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f, 1.0f);

	aie::Gizmos::create(64000, 10000, 64000, 10000);
	
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_viewMatrix = view;
	m_camera.setViewMatrix(view);

	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
	m_projectionMatrix = projection;
	m_camera.setProjectionMatrix(projection);

	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return -1;
	}

	m_quadMesh.initialiseQuad();
	m_quadTransform = { 10, 0, 0, 0,
						0, 10, 0, 0,
						0, 0, 10, 0,
						0, 0, 0, 1 };

	return 0;
}

void Application3D::update(float deltaTime)
{
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_W) == true)
	{
		m_camera.translate(m_camera.m_forward * deltaTime * -m_moveSpeed);
		m_viewMatrix = m_camera.getViewMatrix();
	}
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_S) == true)
	{
		m_camera.translate(m_camera.m_forward * deltaTime * m_moveSpeed);
		m_viewMatrix = m_camera.getViewMatrix();
	}
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_A) == true)
	{
		m_camera.translate(m_camera.m_right * deltaTime * -m_moveSpeed);
		m_camera.lookAt({ 0, 0, 0 });
		m_viewMatrix = m_camera.getViewMatrix();
	}
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_D) == true)
	{
		m_camera.translate(m_camera.m_right * deltaTime * m_moveSpeed);
		m_camera.lookAt({ 0, 0, 0 });
		m_viewMatrix = m_camera.getViewMatrix();
	}

	if (hasWindowSizeChanged())
	{
		m_projectionMatrix = m_camera.getProjectionMtrix();
	}
}

void Application3D::draw()
{
	clearScreen();

	m_shader.bind();
	auto pvm = m_camera.getProjectionView() * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	m_quadMesh.draw();

	aie::Gizmos::clear();

	aie::Gizmos::addTransform(glm::mat4(1));

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}
	
	aie::Gizmos::draw(m_camera.getProjectionView());
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

void Application3D::shutdown()
{
}
