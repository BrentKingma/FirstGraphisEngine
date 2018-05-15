#pragma once
#include <glm\glm.hpp>
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 m_position;
		glm::vec4 m_normal;
		glm::vec2 m_texCoord;
	};

	void initialiseQuad();

	virtual void draw();

protected:
	unsigned int triCount = 0;
	unsigned int vao, vbo, ibo = 0;
};

