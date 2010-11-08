/*
 * Input.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#include "Input.h"

// initialize the static variables
// first the keyboard vars
unsigned char* Input::m_KeyState = 0;
unsigned char* Input::m_OldKeyState = 0;
int Input::m_KeyCount = 0;
// then the mouse vars
int Input::m_MouseDX = 0;
int Input::m_MouseDY = 0;
int Input::m_MouseX = 0;
int Input::m_MouseY = 0;
unsigned int Input::m_MouseState = 0;
unsigned int Input::m_OldMouseState = 0;

Input::Input(void) {
	// do nothing
}

Input::~Input(void) {
	// do nothing
}

void Input::Destroy(void) {
	delete[] m_OldKeyState;
	delete[] m_KeyState;
}

void Input::Initialize(void) {
	// initialize the keyboard data
	unsigned char* tempKeyState = SDL_GetKeyState(&Input::m_KeyCount);

	Input::m_KeyState = new unsigned char[Input::m_KeyCount];
	Input::m_OldKeyState = new unsigned char[Input::m_KeyCount];

	memcpy(Input::m_OldKeyState, Input::m_KeyState, sizeof(unsigned char) * Input::m_KeyCount);
	memcpy(Input::m_KeyState, tempKeyState, sizeof(unsigned char) * Input::m_KeyCount);

	// initialize the mouse button data
	Input::m_MouseDX = Input::m_MouseDY = 0;
	Input::m_MouseState = SDL_GetRelativeMouseState(&Input::m_MouseDX, &Input::m_MouseDY);
	Input::m_OldMouseState = Input::m_MouseState;

	Input::m_MouseX = Input::m_MouseY = 0;
	SDL_GetMouseState(&Input::m_MouseX, &Input::m_MouseY);

	// push SDL events onto the SDL event queue
	SDL_PumpEvents();
	SDL_PumpEvents();
}

void Input::Update(void) {
	// push SDL events onto the SDL event queue
	SDL_PumpEvents();

	unsigned char* tempKeyState = SDL_GetKeyState(&Input::m_KeyCount);

	// set the mouse data
	Input::m_OldMouseState = m_MouseState;
	Input::m_MouseState = SDL_GetRelativeMouseState(&m_MouseDX, &m_MouseDY);
	SDL_GetMouseState(&Input::m_MouseX, &Input::m_MouseY);

	// set the keyboard data
	// TODO currently, both keystates are updated to current instead of current and last
	memcpy(Input::m_OldKeyState, Input::m_KeyState, sizeof(unsigned char) * Input::m_KeyCount);
	memcpy(Input::m_KeyState, tempKeyState, sizeof(unsigned char) * Input::m_KeyCount);
}
