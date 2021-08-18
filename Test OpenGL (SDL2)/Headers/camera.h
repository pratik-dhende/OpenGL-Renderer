#pragma once

#include<glm.hpp>
#include<gtx/transform.hpp>
#include "display.h"

class Camera {
private:
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_directionVec;
	glm::vec3 m_right;

	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionPerspectiveMatrix;

public:
	Camera(const glm::vec3& position, const float& fov, const float& nearPlane, const float& farPlane, const Display& display);
	~Camera();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionPerspectiveMatrix() const;
};