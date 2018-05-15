#include "Application.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <Gizmos.h>
#include "Camera.h"
#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning( pop )
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
		
		unsigned int frames = 0;
		double fpsInterval = 0;

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

void Application::setBackgroundColour(float a_r, float a_g, float a_b, float a_a)
{
	glClearColor(a_r, a_g, a_b, a_a);
}

void Application::setShowCursor(bool a_visible)
{
	ShowCursor(a_visible);
}

void Application::setVSync(bool a_enabled)
{
	glfwSwapInterval(a_enabled ? 1 : 0);
}

unsigned int Application::getWindowWidth() const 
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return w;
}

unsigned int Application::getWindowHeight() const
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return h;
}

float Application::getTime() const
{
	return (float)glfwGetTime();
}

float Application::getDeltaTime() const
{
	return (float)deltaTime;
}

bool Application::hasWindowSizeChanged()
{
	if (windowWidth != getWindowWidth() || windowHeight != getWindowHeight())
	{
		windowWidth = getWindowWidth();
		windowHeight = getWindowHeight();

		return true;
	}
	return false;
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

	glClearColor(0, 0, 0, 1.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	windowWidth = a_screenWidth;
	windowHeight = a_screenHeight;

	return 0;
}

void Application::destroyWindow()
{
	aie::Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
