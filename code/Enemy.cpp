/*
 * Enemy.cpp
 *
 *  Created on: Nov 8, 2010
 *      Author: covertcj
 */

#include "Enemy.h"

Enemy::Enemy(Texture* enemyTexture) {
	// TODO Auto-generated constructor stub

	m_Texture = enemyTexture;

	m_Model = new MD2Model(VSHADER_ENEMY, FSHADER_ENEMY);
	m_Model->setAnimation(Animation::RUN);
	m_CurrentAnimation = RUN;
	m_Model->load(MODEL_ENEMY);

	m_XPos      	= 0.0f;
	m_YPos      	= 0.0f;
	m_XTarget   	= 0.0f;
	m_YTarget   	= 0.0f;
	m_DecayTimer	= 0.0f;
	m_IsDecayed 	= false;
	m_IsDead    	= false;
	m_IsMoving  	= false;
	m_IsCelebrating	= false;
}

Enemy::~Enemy(void) {
	// TODO Auto-generated destructor stub
	delete m_Model;
}

void Enemy::Draw(void) {

	glPushMatrix();
		// translate to the player position
		// offset vertically by half the player so as to not be underground
		glTranslatef(m_XPos, m_YPos, m_Model->getRadius() + 0.2);

		// bind the texPlayerture
		m_Texture->Bind();

		// rotate the player so he is standing up rather than laying sideways
		glRotatef(90.0, 1.0, 0.0, 0.0);
		// rotate the player towards the mouse
		glRotatef(m_Rotation, 0.0, 1.0, 0.0);

		// render the model
		m_Model->render();
	glPopMatrix();
}

void Enemy::Update(Player* player) {
	float dt = Timer::GetDT();

	// update the animation
	m_Model->update(dt);

	if (m_IsDead) {
		m_DecayTimer += dt;

		if (m_DecayTimer >= ENEMY_DECAY_TIMER) {
			m_IsDecayed = true;
		}

		return;
	}

	if (player->isDead()) {
		if (!m_IsCelebrating) {
			m_Model->setAnimation(Animation::FLIP_OFF);
			m_IsCelebrating = true;
		}

		return;
	}

	checkTarget(player);
	move(player);

	// ensure stays in X bounds
	if (m_XPos > LEVEL_SIZE_X - m_Model->getRadius()) {
		m_XPos = LEVEL_SIZE_X - m_Model->getRadius();
	}
	else if (m_XPos < m_Model->getRadius()) {
		m_XPos = m_Model->getRadius();
	}

	// ensure stays in Y bounds
	if (m_YPos > LEVEL_SIZE_Y - m_Model->getRadius()) {
		m_YPos = LEVEL_SIZE_Y - m_Model->getRadius();
	}
	else if (m_YPos < m_Model->getRadius()) {
		m_YPos = m_Model->getRadius();
	}



	// set the rotation angle
	m_Rotation = rad2Deg(atan2(m_YPos-player->GetY(), m_XPos-player->GetX()))+180.0;
}

void Enemy::SetX(float x) {
	m_XPos = x;
}

void Enemy::SetY(float y) {
	m_YPos = y;
}

void Enemy::SetTargetX(float x) {
	m_XTarget = x;
}

void Enemy::SetTargetY(float y) {
	m_YTarget = y;
}

float Enemy::GetX(void) {
	return m_XPos;
}

float Enemy::GetY(void) {
	return m_YPos;
}

float Enemy::GetRotation(void) {
	return m_Rotation;
}

float Enemy::GetRadius(void) {
	return m_Model->getRadius();
}

bool Enemy::IsDecayed(void) {
	return m_IsDecayed;
}

void Enemy::Kill(void) {
	m_IsDead = true;

	int r = rand() % 3;

	if (r == 0) {
		m_Model->setAnimation(Animation::DEATH1);
	}
	else if (r == 1) {
		m_Model->setAnimation(Animation::DEATH2);
	}
	else if (r == 2) {
		m_Model->setAnimation(Animation::DEATH3);
	}
}

void Enemy::checkTarget(Player* player) {
	m_XTarget = player->GetX();
	m_YTarget = player->GetY();
}

void Enemy::move(Player* player) {
	if (!player->isDead())
	{
		float dt  = Timer::GetDT();
		float dir = 180.0f/M_PI*atan2(m_XTarget-m_XPos, -m_YTarget+m_YPos);

		if (dir < 0)
			dir += 360;

		if (dir > 360)
			dir -= 360;

		m_IsMoving = true;
		m_XPos    -= cos((dir+90)*M_PI/180)*dt*player->getEnemySpeed();
		m_YPos    -= sin((dir+90)*M_PI/180)*dt*player->getEnemySpeed();
	}
	else
		m_IsMoving = false;
}

bool Enemy::IsDead(void) {
	return m_IsDead;
}
