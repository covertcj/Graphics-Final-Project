/*
 * Window.h
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "includes.h"

class AppWindow {
public:
	AppWindow(void);
	virtual ~AppWindow(void);

	bool Create(int width, int height, int bpp, bool fullscreen, const char* title);
	void Destroy(void);

	void SetSize(int width, int height);

	int GetWidth(void);
	int GetHeight(void);

private:
	int m_Width;
	int m_Height;
	int m_Bpp;

	bool m_Fullscreen;

	const char* m_Title;
};

#endif /* WINDOW_H_ */
