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
	m_Model->setAnimation(Animation::IDLE);
	m_CurrentAnimation = IDLE;
	m_Model->load(MODEL_ENEMY);

	m_XPos    = 0.0f;
	m_YPos    = 0.0f;
	m_XTarget = 0.0f;
	m_YTarget = 0.0f;
	m_IsDead = false;
}

Enemy::~Enemy(void) {
	// TODO Auto-generated destructor stub
	delete m_Model;
}

void Enemy::Draw(void) {

	glPushMatrix();
		// translate to the player position
		// offset vertically by half the player so as to not be underground
		glTranslatef(m_XPos, m_YPos, m_Model->getRadius());

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

	// ensure stays in X bounds
	if (m_XPos > LEVEL_SIZE_X - m_Model->getRadius()) {
		m_XPos = LEVEL_SIZE_X - m_Model->getRadius();
	}
//	else if (m_XPos < m_Model->getRadius()) {
//		m_XPos = m_Model->getRadius();
//	}

	// ensure stays in Y bounds
	if (m_YPos > LEVEL_SIZE_Y - m_Model->getRadius()) {
		m_YPos = LEVEL_SIZE_Y - m_Model->getRadius();
	}
//	else if (m_YPos < m_Model->getRadius()) {
//		m_YPos = m_Model->getRadius();
//	}

	m_Model->setAnimation(Animation::IDLE);
	m_CurrentAnimation = IDLE;

	// set the rotation of the player
	float mouseX = player->GetX();
	float mouseY = player->GetY();
	float dx = m_XPos * LEVEL_TO_SCREEN_SCALE_X - mouseX;
	float dy = m_YPos * LEVEL_TO_SCREEN_SCALE_Y - mouseY;
	m_Rotation = rad2Deg(atan2(dy, dx)) + 180.0;

	// update the animation
	m_Model->update(dt);
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

bool Enemy::IsDead(void) {
	return m_IsDead;
}

void Enemy::Kill(void) {
	m_IsDead = true;
}
