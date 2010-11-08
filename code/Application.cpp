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

	InitOpenGL();
	glewInit();

	m_obj = new TestObject();
}

void Application::InitSDL(void) {
	// do nothing
}

void Application::InitOpenGL(void) {
	// TODO Enable parts of OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -2.0);

	m_obj->Draw();

	SDL_GL_SwapBuffers();
}

void Application::Update(void) {
	Timer::Update();
	Input::Update();

	m_obj->Update();

	// quit when escape is pressed
	if (Input::IsKeyNewlyDown(SDLK_ESCAPE)) {
		SDL_Event ev;
		ev.type = SDL_QUIT;
		SDL_PushEvent(&ev);
	}
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
