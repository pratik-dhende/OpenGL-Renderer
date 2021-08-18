#pragma once
#include<iostream>
#include<string>
#include<GL\glew.h>
#include<fstream>
#include "transform.h"
#include "mvp.h"

class Shaders {
private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint shaders[NUM_SHADERS];

	enum ShaderName {
		ShaderName_vertexShader,
		ShaderName_fragmentShader
	};

	GLuint m_program;
	GLenum m_glewStatus;

	std::string loadShader(const std::string& filename);
	GLuint CreateShader(const std::string& filename, GLenum shaderType);
	void checkError(GLuint source, bool isShader, const std::string& errorMsg);

public:
	Shaders(const std::string& filename);
	~Shaders();

	void useShaders();
	void updateTransform(Transform& transform);
	void updateCamera(const MVP& mvp);
};
