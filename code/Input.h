/*
 * Input.h
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#include "includes.h"

#ifndef INPUT_H_
#define INPUT_H_

class Input {
public:
	Input(void);
	virtual ~Input(void);

	void static Initialize(void);
	void static Update(void);
	void static Destroy(void);

	/*!
	 * The state of the keyboard keys this frame.
	 */
	static unsigned char *m_KeyState;
	/*!
	 * The state of the keyboard keys last frame.
	 */
	static unsigned char *m_OldKeyState;
	/*!
	 * The number of keys available to the user. This is used
	 * to size the key arrays.
	 */
	static int m_KeyCount;

	/*!
	 * The change in position of the mouse in the x direction
	 * since the last update.
	 */
	static int m_MouseDX;
	/*!
	 * The change in position of the mouse in the y direction
	 * since the last update.
	 */
	static int m_MouseDY;
	/*!
	 * The state of the mouse buttons this frame.
	 */
	static unsigned int m_MouseState;
	/*!
	 * The state of the mouse buttons last frame.
	 */
	static unsigned int m_OldMouseState;

	/*
	 * @param index The key to retreive information on.
	 * @return True if the given key is down now.
	 */
	static bool inline IsKeyDown(int index) {
		return (m_KeyState[index] != 0);
	}
	/*
	 * @param index The key to retreive information on.
	 * @return True if the given key was down in the last update.
	 */
	static bool inline WasKeyDown(int index) {
		return (m_OldKeyState[index] != 0);
	}

	/*
	 * @param index The key to retreive information on.
	 * @return True if the given key was not down in the last update, but now is.
	 */
	static bool inline IsKeyNewlyDown(int index) {
		return (IsKeyDown(index)) && (!WasKeyDown(index));
	}
	/*
	 * @param index The key to retreive information on.
	 * @return True if the given key was not up in the last update, but now is.
	 */
	static bool inline IsKeyNewlyUp(int index) {
		return (!IsKeyDown(index)) && (WasKeyDown(index));
	}

	/*
	 * @param button The mouse button to retreive information on.
	 * @return True if the given mouse button was up in the last update.
	 */
	static bool inline IsButtonDown(int button) {
		return (m_MouseState & SDL_BUTTON(button)) != 0;
	}
	/*
	 * @param button The mouse button to retreive information on.
	 * @return True if the given mouse button was down in the last update.
	 */
	static bool inline WasButtonDown(int button) {
		return (m_OldMouseState & SDL_BUTTON(button)) != 0;
	}

	/*
	 * @param button The mouse button to retreive information on.
	 * @return True if the given mouse button is down now but was not in the last update.
	 */
	static bool inline IsButtonNewlyDown(int button) {
		return (IsButtonDown(button)) && (!WasButtonDown(button));
	}
	/*
	 * @param button The mouse button to retreive information on.
	 * @return True if the given mouse button is up now but was not in the last update.
	 */
	static bool inline IsButtonNewlyUp(int button) {
		return (!IsButtonDown(button)) && (WasButtonDown(button));
	}
};

#endif /* INPUT_H_ */
