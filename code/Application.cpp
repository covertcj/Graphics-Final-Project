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

	m_Window = new AppWindow();
	m_Window->Create(WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y, WINDOW_BPP,
			WINDOW_FULLSCREEN, WINDOW_TITLE);

	m_obj = new TestObject();
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

	m_Window->Destroy();
	delete m_Window;
	delete m_obj;

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
	//std::cout << "Draw()\n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -20.0);

	m_obj->Draw();

	SDL_GL_SwapBuffers();
}

void Application::Update(void) {
	// TODO Update the program
	Timer::Update();
	Input::Update();

	m_obj->Update();
}

void Application::Resize(int x, int y) {
	if (y <= 0) {
		y = 1;
	}

	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat) x / (GLfloat) y, 1.0f, 100.0f);

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
			break;

		default:
			break;
		}
	}

	// all events are handled, continue on
	return true;
}
