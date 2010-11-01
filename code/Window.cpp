/*
 * Window.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#include "Window.h"

AppWindow::AppWindow() {
	m_Width = 0;
	m_Height = 0;
	m_Bpp = 0;
	m_Fullscreen = false;
}

AppWindow::~AppWindow(void) {
	// do nothing
}

bool AppWindow::Create(int width, int height, int bpp, bool fullscreen, const char* title) {
	// initialize SDL Video and ensure there was no error
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Video has failed to initialize!\n";
		return false;
	}

	// setup fields
	m_Height = height;
	m_Width = width;
	m_Title = title;
	m_Fullscreen = fullscreen;
	m_Bpp = bpp;

	// enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// set the window title
	SDL_WM_SetCaption(title, title);

	// setup window type flags
	int flags = SDL_OPENGL;
	if (m_Fullscreen) {
		flags |= SDL_FULLSCREEN;
	}

	// create the window
	/*SDL_Surface* screen = */
	SDL_SetVideoMode(m_Width, m_Height, m_Bpp, flags);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// create a resize event to setup OpenGL
	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = m_Width;
	resizeEvent.resize.h = m_Height;
	SDL_PushEvent(&resizeEvent);

	return true;
}

void AppWindow::Destroy(void) {
	// clean up SDL Video
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void AppWindow::SetSize(int width, int height) {
	m_Height = height;
	m_Width = width;
}

int AppWindow::GetWidth(void) {
	return m_Width;
}

int AppWindow::GetHeight(void) {
	return m_Height;
}
