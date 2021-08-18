#pragma once
#include<glm.hpp>
#include<gtx/transform.hpp>

class Transform {
private:
	glm::mat4 translatedMatrix;
	glm::mat4 rotatedMatrix;
	glm::mat4 scaledMatrix;
	glm::mat4 transformedMatrix;

	void translate(glm::vec3 translationVec);
	void rotate(glm::vec3 rotationVec);
	void scale(glm::vec3 scalingVec);

public:
	Transform();
	~Transform();

	void transform(glm::vec3 translationVec = glm::vec3(), glm::vec3 rotationVec = glm::vec3(), glm::vec3 scalingVec = glm::vec3(1.0, 1.0, 1.0));
	glm::mat4 getTransformedMatrix();
};