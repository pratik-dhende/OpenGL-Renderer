#include "shaders.h"
#include<SDL.h>
#include<glm.hpp>
#include<gtx/transform.hpp>

Shaders::Shaders(const std::string& filename) {
	std::cout << "Shaders constructor." << std::endl;

	//Initialize glew functions.
	m_glewStatus = glewInit();

	//Check if it has initialized correctly.
	if (m_glewStatus != GLEW_OK) {
		std::cerr << "GLEW FAILED TO INITIALIZE." << std::endl;
		exit(0);
	}

	//Create a shader and attach the source file to them and return their ids.
	shaders[ShaderName_vertexShader] = CreateShader(filename + ".vs", GL_VERTEX_SHADER);
	shaders[ShaderName_fragmentShader] = CreateShader(filename + ".fs", GL_FRAGMENT_SHADER);

	//Initialize program.
	m_program = glCreateProgram();

	//Attach the shaders to program.
	for (int shadersIndex = 0; shadersIndex < NUM_SHADERS; shadersIndex++) {
		glAttachShader(m_program, shaders[shadersIndex]);
	}

	//Link the program.
	glLinkProgram(m_program);

	//Check if the program linked successfully.
	checkError(m_program, false, "ERROR: FAILED TO LINK THE PROGRAM:\n");
}

Shaders::~Shaders() {
	//Detach Shaders from the program.
	for (int shadersIndex = 0; shadersIndex < NUM_SHADERS; shadersIndex++) {
		glDetachShader(m_program, shaders[shadersIndex]);
	}

	//Delete the program.
	glDeleteProgram(m_program);

	std::cout << "Shaders destructor." << std::endl;
}

void Shaders::useShaders() {
	glUseProgram(m_program);
}

GLuint Shaders::CreateShader(const std::string& shaderName, GLenum ShaderType) {
	//Declared the shader type.
	GLuint shader = glCreateShader(ShaderType);

	//Checked if shader was created successfully.
	if (shader == 0)
		std::cerr << "ERROR:FAILED TO CREATE THE SHADER" << std::endl;

	//Declared the arrays to store the source code strings and their lengths.
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceLengths[1] = {0};

	//Initialized them with their respective source strings and their lengths.
	std::string shaderSourceString = loadShader(shaderName);
	shaderSourceStrings[0] = shaderSourceString.c_str();
	shaderSourceLengths[0] = (GLint)shaderSourceString.length();

	//Finally provided the source code to the shader id.
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceLengths);

	//Compile the shader.
	glCompileShader(shader);

	//Check if the shader compiled correctly.
	checkError(shader, true, "ERROR: FAILED TO COMPILE THE SHADER: " + shaderName);

	return shader;
}

std::string Shaders::loadShader(const std::string& filename) {
	std::ifstream fin(filename.c_str());

	std::string line;
	std::string shaderString;

	if (fin.is_open()) {
		while (fin.good()) {
			std::getline(fin, line);
			shaderString.append(line + "\n");
		}
	}
	else {
		std::cerr << "ERROR: COULDN'T OPEN FILE: " << filename << std::endl;
	}

	fin.close();

	return shaderString;
}

void Shaders::checkError(GLuint source, bool isShader, const std::string& errorMsg) {
	GLint success;
	char infoLog[512];

	if (isShader)
		glGetShaderiv(source, GL_COMPILE_STATUS, &success);
	else
		glGetProgramiv(source, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(source, 512, NULL, infoLog);
		std::cerr << errorMsg << std::endl;
	}
}

void Shaders::updateCamera(const MVP& mvp) {
	GLint model_uniformLoc = glGetUniformLocation(m_program, "modelMatrix");
	GLint view_uniformLoc = glGetUniformLocation(m_program, "viewMatrix");
	GLint projectionPerspective_uniformLoc = glGetUniformLocation(m_program, "projectionPerspectiveMatrix");

	if (model_uniformLoc >= 0 && view_uniformLoc >= 0 && projectionPerspective_uniformLoc >= 0) {
		glUniformMatrix4fv(model_uniformLoc, 1, GL_FALSE, &mvp.getModelMatrix()[0][0]);
		glUniformMatrix4fv(view_uniformLoc, 1, GL_FALSE, &mvp.getViewMatrix()[0][0]);
		glUniformMatrix4fv(projectionPerspective_uniformLoc, 1, GL_FALSE, &mvp.getProjectionPerspectiveMatrix()[0][0]);
	}
	else {
		std::cerr << "ERROR: FAILED TO LOCATE THE CAMERA UNIFORMS.";
	}
}