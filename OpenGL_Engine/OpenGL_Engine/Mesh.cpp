#include "Mesh.h"
#include <gl_core_4_4.h>


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	//The OpenGL library handles its cleanups with the call of glDelete#### functions
	//Deletes the vertex array object
	glDeleteVertexArrays(1, &vao);
	//Deletes the vertex buffer object
	glDeleteBuffers(1, &vbo);
	//Deletes the index buffer object
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	//Makes sure that the mesh hasnt been initialized already
	assert(vao == 0);

	//The OpenGL library handles its creation with the call of glGen#### functions
	//Generates the vertex buffer
	glGenBuffers(1, &vbo);
	//Generates the vertex array
	glGenVertexArrays(1, &vao);

	//Binds the vbo and ibo to the vao and sets them as active ands sends them off to the gpu
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Defines 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].m_position = { -1, 0, 1, 1 };
	vertices[1].m_position = { 1, 0, 1, 1 };
	vertices[2].m_position = { -1, 0, -1, 1 };

	vertices[3].m_position = { -1, 0, -1, 1 };
	vertices[4].m_position = { 1, 0, 1, 1 };
	vertices[5].m_position = { 1, 0, -1, 1 };

	//Fills the vertex buffer using 4 parameters
	//1: Type of buffer
	//2: Size of the data in bytes
	//3: Pointer to the data
	//4: Constant for if the data will change
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//Enables first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Unbinds the buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
