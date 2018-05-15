#pragma once
#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning( pop )
class Camera
{
public:
	void setPosition(float a_x, float a_y, float a_z)
	{
		m_worldTransform[3][0] = a_x;
		m_worldTransform[3][1] = a_y;
		m_worldTransform[3][2] = a_z;
	}
	void setPosition(glm::vec4 a_postion)
	{
		m_worldTransform[3] = a_postion;
	}
	void translate(glm::vec4 a_positionModifier)
	{
		m_worldTransform[3] += a_positionModifier;
	}
	void setTransform(glm::mat4 a_transform)
	{
		m_worldTransform += a_transform;
	}
	void setProjectionMatrix(glm::mat4 a_projectionMatrix)
	{
		m_hasSetProjectionMatrix = true;
		m_projectionMatrix = a_projectionMatrix;
	}
	void setViewMatrix(glm::mat4 a_viewMatrix)
	{
		m_worldTransform = glm::inverse(a_viewMatrix);
	}
	void lookAt(glm::vec3 a_position)
	{
		auto view = glm::lookAt(glm::vec3(m_worldTransform[3]), a_position, glm::vec3(m_worldUp));
		m_worldTransform = glm::inverse(view);
	}
	glm::mat4 getViewMatrix() const
	{
		if (m_hasSetViewMatrix)
		{
			return m_worldTransform;
		}
		else
		{
			return glm::inverse(m_worldTransform);
		}
	}
	const glm::mat4 getTransform() const
	{
		return m_worldTransform;
	}
	const glm::mat4 getProjectionMtrix() const
	{
		assert(m_hasSetProjectionMatrix == true);
		return m_projectionMatrix;
	}
	glm::mat4 getTransform()
	{
		return m_worldTransform;
	}
	glm::mat4 getProjectionView()
	{
		return getProjectionMtrix() * getViewMatrix();
	}
	glm::vec4 getPosition() const
	{
		return m_worldTransform[3];
	}

	//virtual void update(float a_deltaTime) = 0;

	glm::vec4& m_forward = m_worldTransform[2];
	glm::vec4& m_right = m_worldTransform[0];
	glm::vec4& m_up = m_worldTransform[1];
	glm::vec4 m_worldForward = glm::vec4( 0, 0, -1, 0 );
	glm::vec4 m_worldRight = glm::vec4(1, 0, 0, 0);
	glm::vec4 m_worldUp = glm::vec4(0, 1, 0, 0);
private:
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_projectionMatrix = glm::mat4(1);

	bool m_hasSetProjectionMatrix = false;
	bool m_hasSetViewMatrix = false;

	


};
