/*
 * Level.h
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "includes.h"

class Level {
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(Texture* groundTexture);
	void Destroy(void);

	void Update(void);
	void Draw(void);

private:
	void DrawLevelPlane(void);

	GLSLProgram* m_GroundShader;
	Texture* m_GroundTexture;
};

#endif /* LEVEL_H_ */