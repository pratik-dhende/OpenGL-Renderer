#include<iostream>
#include "display.h"
#include "shaders.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "mvp.h"

int main() {
	Display display(800, 600, "my title");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0, 0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0.5, 1.0)) };

	Shaders shaders("E:\\Visual Studio 2019\\source\\repos\\Test OpenGL (SDL2)\\Test OpenGL (SDL2)\\Src\\Shaders\\shader");
	Mesh mesh(vertices, 6);
	Texture texture("E:\\Visual Studio 2019\\source\\repos\\Test OpenGL (SDL2)\\Test OpenGL (SDL2)\\Src\\Textures\\awesomeface.png");
	Transform transform;
	Camera camera(glm::vec3(0, 0, 1), 70.0f, 1.0f, 1000.0f, display);

	glm::mat4 model = transform.getTransformedMatrix();
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projectionPerspective = camera.getProjectionPerspectiveMatrix();
	MVP mvp(model, view, projectionPerspective);

	float tick = 0;

	while (!display.isClosed()) {
		//Rendering
		display.background(0, 0, 0, 1);
		
		shaders.useShaders();

		//transform.transform();
		model = transform.getTransformedMatrix();
		mvp.setModelMatrix(model);
		shaders.updateCamera(mvp);

		texture.bind(0);
		mesh.draw(true);

		tick += 0.001;

		//Handle events.
		display.update();
	}

	return 0;
}