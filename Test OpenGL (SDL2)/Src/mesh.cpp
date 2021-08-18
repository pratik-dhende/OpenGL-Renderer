#include "mesh.h"
#include "shaders.h"
#include<iostream>
#include<vector>

Mesh::Mesh(Vertex* vertices, const unsigned int NUM_VERTICES) {
	std::cout << "Mesh constructor." << std::endl;

	m_NUM_DRAWING_VERTICES = NUM_VERTICES;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec4> color;
	std::vector<glm::vec2> texCord;

	positions.reserve(NUM_VERTICES);
	color.reserve(NUM_VERTICES);
	texCord.reserve(NUM_VERTICES);

	for (unsigned int i = 0; i < NUM_VERTICES; i++) {
		positions.push_back(vertices[i].getPosition());
		color.push_back(vertices[i].getColor());
		texCord.push_back(vertices[i].getTexture());
	}

	// Generate space for VertexArrayObject in GPU.
	glGenVertexArrays(VAO_NUM_VAO, m_vertexArrayObjects);

	// Bind our configs with vertexBufferArray.
	glBindVertexArray(m_vertexArrayObjects[VAO_CONFIG_1]);

	// Generate space for vertexArrayBuffers in the GPU.
	glGenBuffers(VBO_NUM_BUF, m_vertexArrayBuffers);

	// Bind that object to a target/object of a context.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[VBO_POSITION_BUF]);

	// Put data in the buffer.
	glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	// Setting attribute for VBO_POSITION_BUF.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	//VBO_COLOR_BUF.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[VBO_COLOR_BUF]);
	glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * sizeof(color[0]), &color[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	// VBO_TEXTURE_BUF.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[VBO_TEXTURE_BUF]);
	glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * sizeof(texCord[0]), &texCord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	// Enable the attribute.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//Stop VAO from pointing to our configs.
	glBindVertexArray(0);
}

Mesh::~Mesh() {

	glDeleteBuffers(1, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, m_vertexArrayObjects);

	std::cout << "Mesh destructor." << std::endl;
}

void Mesh::draw(bool useShaders) {
	// Bind the VAO back to use it.
	glBindVertexArray(m_vertexArrayObjects[VAO_CONFIG_1]);

	// Draw the points according to the specified configs in the VAO.
	glDrawArrays(GL_LINES, 0, m_NUM_DRAWING_VERTICES);

	// Unbind the VAO.
	glBindVertexArray(0);

	// Disable the attribute.
	glDisableVertexAttribArray(0);

	// Unbind the buffer to restore GL back to its original state.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}