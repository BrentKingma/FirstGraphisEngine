#include <iostream>
#include "Application.h"
#include <Gizmos.h>

class App : public Application
{
public:
	App() {}
	~App() {}

	virtual int startup()
	{
		return 0;
	}
	virtual void update(float deltaTime)
	{

	}
	virtual void draw()
	{
		clearScreen();

		aie::Gizmos::clear();

		aie::Gizmos::addTransform(glm::mat4(1));

		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 23; i++)
		{
			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}

		aie::Gizmos::draw(getProjection() * getView());
	}
	virtual void shutdown()
	{

	}
};

int main()
{
	App app = App();

	app.run(1280, 720, "Graphics Engine");

	return 0;
}


/*	*/