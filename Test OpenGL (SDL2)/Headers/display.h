#pragma once
#include<string>
#include<SDL.h>
#include<GL/glew.h>
#undef main

class Display {
private:
	SDL_Window* m_display;
	bool m_isClosed;
	SDL_GLContext m_glContext;
	GLenum m_status;

	int m_width;
	int m_height;
	std::string m_title;

public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void update();
	bool isClosed() const;
	void background(GLclampf r, GLclampf g, GLclampf b, GLclampf alpha);
	
	int getDisplayWidth() const;
	int getDisplayHeight() const;
};