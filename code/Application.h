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

	void LoadTextures(void);

	bool ProcessEvents(void);
	void Resize(int x, int y);

	void Draw(void);
	void Update(void);

	AppWindow* m_Window;

	//TestObject* m_obj;
	Level* m_Level;

	Texture* m_GroundTexture;
};

#endif /* APPLICATION_H_ */
