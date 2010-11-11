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
	float GetRadius(void);
	float GetRotation(void);
	float getEnemySpeed(void);

	bool CanShoot(void);
	void Shoot(void);
	void Kill(void);
	bool isDead(void);
	void incKillCount(void);

private:
	bool m_IsDead;
	bool m_CanShoot;

	int m_Kills;
	int m_LevelKills;

	float m_ShotCooldown;
	float m_XPos;
	float m_YPos;
	float m_Rotation;
	float m_EnemySpeed;

	AnimationEnum m_CurrentAnimation;

	MD2Model* m_Model;
	Texture* m_Texture;
	GLSLProgram* m_Shader;
};

#endif /* PLAYER_H_ */
