/*
 * Application.h
 *
 *  Created on: Oct 27, 2010
 *      Author: covertcj
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "includes.h"

class Application {
public:
	Application(void);
	virtual ~Application(void);

	void Initialize(void);
	void Run(void);
	void Terminate(void);

private:
	void InitSDL(void);
	void InitOpenGL(void);

	bool ProcessEvents(void);
	void Resize(int x, int y);

	void Draw(void);
	void Update(void);

	Window* m_Window;
};

#endif /* APPLICATION_H_ */
