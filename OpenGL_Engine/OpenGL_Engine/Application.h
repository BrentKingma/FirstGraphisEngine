#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Application
{
public:
	Application();
	~Application();

	void run(int a_screenWidth, int a_screenHeight, const char* a_windowName);

	virtual int startup() = 0;
	virtual void update(float a_deltaTime) = 0;
	virtual void draw() = 0;
	virtual void shutdown() = 0;

	void clearScreen();
	glm::mat4 getView() { return m_view; };
	glm::mat4 getProjection() { return m_projection; };

protected:
	virtual int createWindow(int a_screenWidth, int a_screenHeight, const char* a_windowName);
	void destroyWindow();

private:
	GLFWwindow* m_window;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	unsigned int m_fps = 0;
};