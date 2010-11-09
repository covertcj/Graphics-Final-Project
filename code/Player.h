/*
 * Player.h
 *
 *  Created on: Nov 8, 2010
 *      Author: covertcj
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "includes.h"

class Player {
public:
	Player(Texture* playerTexture);
	virtual ~Player(void);

	void Draw(void);
	void Update(void);

	float GetX(void);
	float GetY(void);

private:
	float m_XPos;
	float m_YPos;

	float m_Rotation;

	AnimationEnum m_CurrentAnimation;

	MD2Model* m_Model;
	Texture* m_Texture;
	GLSLProgram* m_Shader;
};

#endif /* PLAYER_H_ */
