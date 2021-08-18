#include "mvp.h"
#include<iostream>

MVP::MVP(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionPerspectiveMatrix):
	m_modelMatrix(modelMatrix), m_viewMatrix(viewMatrix), m_projectionPerspectiveMatrix(projectionPerspectiveMatrix) {

	std::cout << "MVP constructor." << std::endl;

	m_renderMatrix = m_projectionPerspectiveMatrix * m_viewMatrix * m_modelMatrix;
}

MVP::~MVP() {
	std::cout << "MVP destructor." << std::endl;
}

glm::mat4 MVP::getModelMatrix() const {
	return m_modelMatrix;
}

glm::mat4 MVP::getViewMatrix() const {
	return m_viewMatrix;
}

glm::mat4 MVP::getProjectionPerspectiveMatrix() const {
	return m_projectionPerspectiveMatrix;
}

glm::mat4 MVP::getRenderMatrix() const {
	return m_renderMatrix;
}

void MVP::setModelMatrix(const glm::mat4& modelMatrix) {
	m_modelMatrix = modelMatrix;
}
