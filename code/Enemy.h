/*
 * Enemy.h
 *
 *  Created on: Nov 8, 2010
 *      Author: covertcj
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "includes.h"

class Enemy {
public:
	Enemy(Texture* enemyTexture);
	virtual ~Enemy(void);

	void Draw(void);
	void Update(Player* player);

	void SetX(float x);
	void SetY(float y);
	void SetTargetX(float x);
	void SetTargetY(float y);
	float GetX(void);
	float GetY(void);
	float GetRotation(void);

private:
	float m_XPos;
	float m_YPos;
	float m_XTarget;
	float m_YTarget;
	float m_Rotation;

	AnimationEnum m_CurrentAnimation;

	MD2Model* m_Model;
	Texture* m_Texture;
	GLSLProgram* m_Shader;
};

#endif /* ENEMY_H_ */
