#include "transform.h"
#include<iostream>

Transform::Transform() {
	std::cout << "Transform constructor." << std::endl;
	transform();
}

Transform::~Transform() {
	std::cout << "Transform destructor." << std::endl;
}

void Transform::translate(glm::vec3 translationVec) {
	translatedMatrix = glm::translate(translationVec);
}

void Transform::rotate(glm::vec3 rotationVec) {
	glm::mat4 rotatedXMatrix;
	glm::mat4 rotatedYMatrix;
	glm::mat4 rotatedZMatrix;

	rotatedXMatrix = glm::rotate(rotationVec.x, glm::vec3(1.0, 0.0, 0.0));
	rotatedYMatrix = glm::rotate(rotationVec.y, glm::vec3(0.0, 1.0, 0.0));
	rotatedZMatrix = glm::rotate(rotationVec.z, glm::vec3(0.0, 0.0, 1.0));

	rotatedMatrix = rotatedZMatrix * rotatedYMatrix * rotatedXMatrix;
}

void Transform::scale(glm::vec3 scalingVec) {
	scaledMatrix = glm::scale(scalingVec);
}

void Transform::transform(glm::vec3 translationVec, glm::vec3 rotationVec, glm::vec3 scalingVec) {
	translate(translationVec);
	rotate(rotationVec);
	scale(scalingVec);

	transformedMatrix = translatedMatrix * rotatedMatrix * scaledMatrix;
}

glm::mat4 Transform::getTransformedMatrix(){
	return transformedMatrix;
}