#include "display.h"
#include<iostream>

Display::Display(int width, int height, const std::string& title) {
	m_width = width;
	m_height = height;
	m_title = title;

	//Initialize everything of SDL.
	SDL_Init(SDL_INIT_EVERYTHING);

	//Setting up some params for OpenGL.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // How much data will every pixel store.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	//Creating a window.
	m_display = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//Create context for our display to make out GPU access the window from the OS.
	m_glContext = SDL_GL_CreateContext(m_display);

	//Initializing isClosed.
	m_isClosed = false;

	//Initialize glew functions.
	m_status = glewInit();

	//Check if it has initialized correctly.
	if (m_status != GLEW_OK) {
		std::cerr << "GLEW FAILED TO INITIALIZE." << std::endl;
		exit(0);
	}

	std::cout << "Display Constructor" << std::endl;
}

Display::~Display() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_display);
	SDL_Quit();
	std::cout << "Display Destructor" << std::endl;
}

int Display::getDisplayWidth() const {
	return m_width;
}

int Display::getDisplayHeight() const {
	return m_height;
}

void Display::update() {
	//Swap buffer.
	SDL_GL_SwapWindow(m_display);

	//Handle events.
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_isClosed = true;
		}
	}
}

bool Display::isClosed() const {
	return m_isClosed;
}

void Display::background(GLclampf r, GLclampf g, GLclampf b, GLclampf alpha) {
	//Select the color of the background.
	glClearColor(r, g, b, alpha);

	//Apply that color to the window.
	glClear(GL_COLOR_BUFFER_BIT);
}



