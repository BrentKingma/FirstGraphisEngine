#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
	//If something is broken does launch program, missing graphics card, missing monitor
	if (glfwInit() == false)
	{
		return -1;
	}

	//Creates a window with size, name, default monitor and no screen hijacking
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Graphics Engine", nullptr, nullptr);
	//If window isnt created properly closes program
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	//The current thread is the one we are working on
	//Opengl is only single threaded
	glfwMakeContextCurrent(window);

	//Setup OpenGL, if opengl failed in setting up pointer functions, destroys window
	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	std::cout << major << "." << minor << std::endl;

	///Do our drawing

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}