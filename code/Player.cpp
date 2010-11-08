/*
 * Player.cpp
 *
 *  Created on: Nov 8, 2010
 *      Author: covertcj
 */

#include "Player.h"

Player::Player(Texture* playerTexture) {
	// TODO Auto-generated constructor stub

	m_Texture = playerTexture;

	m_Model = new MD2Model(VSHADER_PLAYER, FSHADER_PLAYER);
	m_Model->setAnimation(Animation::IDLE);
	m_CurrentAnimation = IDLE;
	m_Model->load(MODEL_PLAYER);

	m_XPos = LEVEL_SIZE_X / 2.0;
	m_YPos = LEVEL_SIZE_Y / 2.0;

	m_Rotation = 0.0;
}

Player::~Player(void) {
	// TODO Auto-generated destructor stub
	delete m_Model;
}

void Player::Draw(void) {

	glPushMatrix();
		// translate to the player position
		// offset vertically by half the player so as to not be underground
		glTranslatef(m_XPos, m_YPos, m_Model->getRadius());

		// bind the texture
		m_Texture->Bind();

		// rotate the player so he is standing up rather than laying sideways
		glRotatef(90.0, 1.0, 0.0, 0.0);
		// rotate the player towards the mouse
		glRotatef(m_Rotation, 0.0, 1.0, 0.0);

		// render the model
		m_Model->render();
	glPopMatrix();
}

void Player::Update(void) {
	float dt = Timer::GetDT();

	// find out what directions the player is moving
	bool movingLeft = Input::IsKeyDown(SDLK_a);
	bool movingRight = Input::IsKeyDown(SDLK_d);
	bool movingDown = Input::IsKeyDown(SDLK_s);
	bool movingUp = Input::IsKeyDown(SDLK_w);

	// move the player
	if (movingLeft) {
		m_XPos -= PLAYER_VELOCITY * dt;
	}

	if (movingRight) {
		m_XPos += PLAYER_VELOCITY * dt;
	}

	if (movingDown) {
		m_YPos -= PLAYER_VELOCITY * dt;
	}

	if (movingUp) {
		m_YPos += PLAYER_VELOCITY * dt;
	}

	// change animation based on whether we are moving or not
	// we don't want to reset the animation if we are already in that state
	if ((movingDown || movingLeft || movingRight || movingUp) && m_CurrentAnimation != RUN) {
		m_Model->setAnimation(Animation::RUN);
		m_CurrentAnimation = RUN;
	}
	else if (!(movingDown || movingLeft || movingRight || movingUp) && m_CurrentAnimation != IDLE) {
		m_Model->setAnimation(Animation::IDLE);
		m_CurrentAnimation = IDLE;
	}

	// find mouse coords and convert them to screen coords
	float mouseX = Input::m_MouseX;
	float mouseY = WINDOW_RESOLUTION_Y - Input::m_MouseY;
	// set the rotation of the player
	float dx = m_XPos * LEVEL_TO_SCREEN_SCALE_X - mouseX;
	float dy = m_YPos * LEVEL_TO_SCREEN_SCALE_Y - mouseY;
	m_Rotation = rad2Deg(atan2(dy, dx)) + 180.0;

	m_Model->update(dt);
}

