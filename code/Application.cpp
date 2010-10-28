/*
 * Application.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: covertcj
 */

#include "Application.h"

Application::Application(void) {
	// do nothing
}

Application::~Application(void) {
	// do nothing
}

void Application::Initialize(void) {
	// startup the input handler
	//g_InputTask = new Input();
	InitSDL();

	Input::Initialize();
	Timer::Initialize();

	m_Window = new Window();
	m_Window->CreateWindow(800, 600, 16, false, "Title");
}

void Application::InitSDL(void) {
	// do nothing
}

void Application::InitOpenGL(void) {
	// TODO Enable parts of OpenGL
}

void Application::Terminate(void) {
	Input::Destroy();
	Timer::Destroy();

	delete m_Window;

	SDL_Quit();
}

void Application::Run(void) {
	while (ProcessEvents()) {
		Update();
		Draw();
	}
}

void Application::Draw(void) {
	// TODO Draw the program
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void Application::Update(void) {
	// TODO Update the program
	Timer::Update();
	Input::Update();
}

void Application::Resize(int x, int y) {
	if (y <= 0) {
		y = 1;
	}

	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)x / (GLfloat)y, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool Application::ProcessEvents(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// return false to end the game loop
			case SDL_QUIT:
				return false;

			case SDL_VIDEORESIZE:
				Resize(event.resize.w, event.resize.h);

			default:
				break;
		}
	}

	// all events are handled, continue on
	return true;
}
