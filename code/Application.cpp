/*
 * Application.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: covertcj
 */

#include "includes.h"

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

	AppFinished = false;
}

void Application::InitSDL(void) {
	// initialize SDL Video and ensure there was no error
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Video has failed to initialize!\n";
	}

	if (SDL_Init(SDL_INIT_TIMER) != 0) {
			std::cout << "SDL Timer has failed to initialize!\n";
	}

	// enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// create a window and a handle to it
	/*SDL_Surface* screen = */SDL_SetVideoMode(800, 600, 16, SDL_OPENGL);
}

void Application::InitOpenGL(void) {
	// TODO Enable parts of OpenGL
}

void Application::Terminate(void) {
	Input::Destroy();
	Timer::Destroy();
	SDL_Quit();
}

void Application::Run(void) {
	while (!AppFinished) {
		Update();
		Draw();
	}
}

void Application::Draw(void) {
	// TODO Draw the program
}

void Application::Update(void) {
	// TODO Update the program
	Timer::Update();
	Input::Update();

	if (Input::IsKeyDown(SDLK_ESCAPE)) {
		AppFinished = true;
	}
}
