#include "Application.h"
#include <Gizmos.h>
#include <stdexcept>
#include <iostream>


Application::Application()
{
}

Application::~Application()
{
}

void Application::run(int a_screenWidth, int a_screenHeight, const char * a_windowName)
{
	if (createWindow(a_screenWidth, a_screenHeight, a_windowName) == 0 && startup() == 0)
	{
		double prevTime = glfwGetTime();
		double currTine = 0;
		double deltaTime = 0;
		unsigned int frames = 0;
		double fpsInterval = 0;

		aie::Gizmos::create(32000, 1800, 32000, 1800);
		m_view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
		m_projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);

		while (true)
		{
			currTine = glfwGetTime();
			deltaTime = currTine - prevTime;
			prevTime = currTine;

			if (glfwWindowShouldClose(m_window) == true || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == true)
			{
				break;
			}

			frames++;
			fpsInterval += deltaTime;
			if (fpsInterval >= 1.0f)
			{
				m_fps = frames;
				frames = 0;
				fpsInterval -= 1.0f;
			}
			
			glfwPollEvents();

			update(float(deltaTime));

			draw();
			
			//Buffer we reading to printing and printing to reading
			glfwSwapBuffers(m_window);
		}
	}

	shutdown();
	destroyWindow();
}

void Application::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Application::createWindow(int a_screenWidth, int a_screenHeight, const char * a_windowName)
{
	//If something is broken does launch program, missing graphics card, missing monitor
	if (glfwInit() == false)
	{
		return -1;
	}

	//Creates a window with size, name, default monitor and no screen hijacking
	m_window = glfwCreateWindow(a_screenWidth, a_screenHeight, a_windowName, nullptr, nullptr);
	//If window isnt created properly closes program
	if (m_window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	//The current thread is the one we are working on
	//Opengl is only single threaded
	glfwMakeContextCurrent(m_window);

	//Setup OpenGL, if opengl failed in setting up pointer functions, destroys window
	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH);

	return 0;
}

void Application::destroyWindow()
{
	aie::Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
