#include "Application3D.h"
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <GLFW\glfw3.h>
#include <imgui.h>
#include <Light.h>

Application3D::Application3D()
{
	
}


Application3D::~Application3D()
{

}

std::vector<Light*> Light::m_lights;

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

	if (m_vertShader == m_fragShader)
	{
		printf("Vert and Frag shaders are the same file");
		return -1;
	}

	//Loadshader compiles the shaders and gives it to the graphics card
	m_bunnyShader.loadShader(aie::eShaderStage::VERTEX, m_vertShader);
	m_bunnyShader.loadShader(aie::eShaderStage::FRAGMENT, m_fragShader);
	
	m_quadShader.loadShader(aie::eShaderStage::VERTEX, m_quadVertShader);
	m_quadShader.loadShader(aie::eShaderStage::FRAGMENT, m_quadFragShader);

	m_swordShader.loadShader(aie::eShaderStage::VERTEX, m_quadVertShader);
	m_swordShader.loadShader(aie::eShaderStage::FRAGMENT, m_quadFragShader);

	Light::AddLight(new Light({ 0, 0, 0 }, { 0.25f, 0.25f, 0.25f }, { 1, 1, 0 }, { 1, 1, 0 }));
	Light::AddLight(new Light({ 0, 0, 0 }, { 0.25f, 0.25f, 0.25f }, { 1, 1, 0 }, { 1, 1, 0 }));

	/*m_light->diffuse = { 1, 1, 0 };
	m_light->specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };*/

	materialAmbientLight = { 1.0f, 1.0f, 1.0f };
	materialDiffuse = { 1.0f, 1.0f, 1.0f };
	materialSpecular = { 1.0f, 1.0f, 1.0f };
	materialSpecturalPower = 1.0f;

	/*if (m_bunnyShader.link() == false)
	{
		printf("Shader Error: %s\n", m_bunnyShader.getLastError());
		return -2;
	}
	if (m_bunnyMesh.load("./objects/bunny.obj") == false)
	{
		printf("Object didnt load \n");
		return -3;
	}*/
	if (m_quadShader.link() == false)
	{
		printf("Shader Error: %s\n", m_quadShader.getLastError());
		return -5;
	}
	if (m_swordMesh.load("./objects/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Object didnt load \n");
		return -3;
	}
	
	if (m_swordShader.link() == false)
	{
		printf("Shader Error: %s\n", m_swordShader.getLastError());
		return -2;
	}
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Grid texture failed");
		return -4;
	}
	

	unsigned char texelData[4] = { 0, 255, 255, 0 };
	m_texture.create(2, 2, aie::Texture::RED, texelData);

	m_quadMesh.initialiseQuad();
	
	m_quadTransform = { 10, 0, 0, 0,
						0, 10, 0, 0,
						0, 0, 10, 0,
						0, 0, 0, 1 };

	m_bunnyTransform = { 0.5f, 0, 0, 0,
						 0, 0.5f, 0, 0,
						 0, 0, 0.5f, 0,
						 0, 0, 0, 1 };

	m_swordTransform = { 1, 0, 0, 0,
						 0, 1, 0, 0,
						 0, 0, 1, 0,
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
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_E) == true)
	{
		m_camera.translate(m_camera.m_worldUp * deltaTime * m_moveSpeed);
		m_camera.lookAt({ 0.0f, 0.0f, 0.0f });
	}
	if (glfwGetKey(getWindowPointer(), GLFW_KEY_Q) == true)
	{
		m_camera.translate(m_camera.m_worldUp * deltaTime * -m_moveSpeed);
		m_camera.lookAt({ 0.0f, 0.0f, 0.0f });
	}

	if (hasWindowSizeChanged())
	{
		m_projectionMatrix = m_camera.getProjectionMtrix();
	}

	float time = getTime();
	ImGUI();
	*Light::m_lights[0]->GetDirection() = glm::normalize(glm::vec3( xDir1, yDir1, zDir1 ));
	*Light::m_lights[1]->GetDirection() = glm::normalize(glm::vec3(xDir2, yDir2, zDir2));
}

void Application3D::draw()
{
	clearScreen();
	
	m_swordShader.bind();
	//Binds light
	for (int i = 0; i < Light::m_lights.size(); i++)
	{
		std::string directionName = "lights[" + std::to_string(i) + "].m_direction";
		std::string ambientName = "lights[" + std::to_string(i) + "].m_ambient";
		std::string diffuseName = "lights[" + std::to_string(i) + "].m_diffuse";
		std::string specularName = "lights[" + std::to_string(i) + "].m_specular";

		m_swordShader.bindUniform(directionName.c_str(), *Light::m_lights[i]->GetDirection());
		m_swordShader.bindUniform(ambientName.c_str(), *Light::m_lights[i]->GetAmbient());
		m_swordShader.bindUniform(diffuseName.c_str(), *Light::m_lights[i]->GetDiffuse());
		m_swordShader.bindUniform(specularName.c_str(), *Light::m_lights[i]->GetSpecular());
	}
	
		//m_swordShader.bindUniform("LightDirection", *Light::m_lights[i]->GetDirection());	

	/*m_swordShader.bindUniform("Ka", materialAmbientLight);
	m_swordShader.bindUniform("Kd", materialDiffuse);
	m_swordShader.bindUniform("Ks", materialSpecular);
	m_swordShader.bindUniform("specularPower", materialSpecturalPower);*/
	//-------------------------------------------------------------
	m_swordShader.bindUniform("ProjectionViewModel", m_camera.getProjectionView() * m_swordTransform);
	m_swordShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_swordTransform)));
	m_swordShader.bindUniform("cameraPosition", m_camera.getPosition());
	
	m_swordMesh.draw();

	m_quadShader.bind();

	m_quadMesh.draw();

	////Binding tells graphics card to use this selected shader
	//m_swordShader.bind();
	////Links the given value to the appropriate uniform value in the shader
	//m_swordShader.bindUniform("ProjectionViewModel", m_camera.getProjectionView() * m_swordTransform);
	//m_swordShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_swordTransform)));
	////Draw links the texture of the object (location within .obj) and then draws it
	//m_swordMesh.draw();

	aie::Gizmos::clear();

	aie::Gizmos::addTransform(glm::mat4(1));

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}
	for (int i = 0; i < Light::m_lights.size(); i++)
	{
		aie::Gizmos::addSphere(*Light::m_lights[i]->GetDirection(), 0.2, 32, 32, { 1, 0, 0, 1 });
	}
	
	aie::Gizmos::draw(m_camera.getProjectionView());
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

	
}

void Application3D::shutdown()
{
}

void Application3D::ImGUI()
{
	ImGui::Begin("Light 1 Direction");

	ImGui::InputFloat("X Direction: ", &xDir1, 1);
	ImGui::InputFloat("Y Direction: ", &yDir1, 1);
	ImGui::InputFloat("Z Direction: ", &zDir1, 1);

	ImGui::End();

	ImGui::Begin("Light 2 Direction");

	ImGui::InputFloat("X Direction: ", &xDir2, 1);
	ImGui::InputFloat("Y Direction: ", &yDir2, 1);
	ImGui::InputFloat("Z Direction: ", &zDir2, 1);

	ImGui::End();
}
