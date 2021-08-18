#pragma once
#include<iostream>
#include<GL/glew.h>

class Texture {
private:
	GLuint m_texture;
public:
	Texture(const std::string& textureImage);
	~Texture();

	void bind(GLenum unit);
};
