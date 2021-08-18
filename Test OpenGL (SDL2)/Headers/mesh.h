#pragma once
#include<glm.hpp>
#include<GL/glew.h>

class Vertex {
public:
	Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texture) {
		this->position = position;
		this->color = color;
		this->texture = texture;
	}
	~Vertex() {};

	glm::vec3 getPosition() const {
		return position;
	}

	glm::vec4 getColor() const {
		return color;
	}

	glm::vec2 getTexture() const {
		return texture;
	}

private:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texture;
};

class Mesh {
public:
	Mesh(Vertex* veritces, const unsigned int NUM_VERTICES); //Will take an array of vertices.
	~Mesh();

	void draw(bool useShaders);

private:
	enum VBO {
		VBO_POSITION_BUF,
		VBO_COLOR_BUF,
		VBO_TEXTURE_BUF,

		VBO_NUM_BUF
	};

	enum VAO {
		VAO_CONFIG_1,

		VAO_NUM_VAO
	};

	GLuint m_vertexArrayObjects[VAO_NUM_VAO];
	GLuint m_vertexArrayBuffers[VBO_NUM_BUF];

	unsigned int m_NUM_DRAWING_VERTICES;
};