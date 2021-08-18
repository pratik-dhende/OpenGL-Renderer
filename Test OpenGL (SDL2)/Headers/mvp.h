#pragma once

#include<glm.hpp>
#include<gtx/transform.hpp>

class MVP {
private:
	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionPerspectiveMatrix;

	glm::mat4 m_renderMatrix;



public:
	MVP(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionPerspectiveMatrix);
	~MVP();

	glm::mat4 getModelMatrix() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionPerspectiveMatrix() const;

	glm::mat4 getRenderMatrix() const;


	void setModelMatrix(const glm::mat4& modelMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionPerspectiveMatrix(const glm::mat4& projectionPerspectiveMatrix);

};