#include "camera.h"
#include<iostream>

Camera::Camera(const glm::vec3& position, const float& fov, const float& nearPlane, const float& farPlane, const Display& display) {
	std::cout << "Camera constructor." << std::endl;

	m_position = position;
	m_fov = fov;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_viewMatrix = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
	m_projectionPerspectiveMatrix = glm::perspective(fov, (float)(display.getDisplayWidth() / display.getDisplayHeight()), nearPlane, farPlane);
}

Camera::~Camera() {
	std::cout << "Camera destructor." << std::endl;
}

glm::mat4 Camera::getViewMatrix() const {
	return m_viewMatrix;
}

glm::mat4 Camera::getProjectionPerspectiveMatrix() const {
	return m_projectionPerspectiveMatrix;
}