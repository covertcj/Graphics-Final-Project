/*
 * Rocket.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: covertcj
 */

#include "Rocket.h"

Rocket::Rocket(float x, float y, float rot, Texture* tex) {
	m_XPos = x;
	m_YPos = y;
	m_Rotation = rot;

	m_Duration = 0;
	m_HasColided = false;

	m_Texture = tex;
	m_Model = new MD2Model(VSHADER_ROCKET, FSHADER_ROCKET);
	m_Model->load(MODEL_ROCKET);
	m_Model->setAnimation(Animation::IDLE);
}

Rocket::~Rocket(void) {
	delete m_Model;
}

void Rocket::Draw(void) {
	m_Texture->Bind();
	//std::cout << "Draw rocket (" << m_XPos << ", " << m_YPos << ") : " << m_Duration << "\n";

	glPushMatrix();
		glTranslatef(m_XPos, m_YPos, 0.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(m_Rotation, 0.0, 1.0, 0.0);

		m_Model->render();
	glPopMatrix();
}

void Rocket::Update(void) {
	float seconds = Timer::GetDT();

	float xc = ROCKET_VELOCITY * cos(degreesToRadians(m_Rotation)) * seconds;
	float yc = ROCKET_VELOCITY * sin(degreesToRadians(m_Rotation)) * seconds;

	//std::cout << "Update rocket (" << m_XPos << ", " << m_YPos << ") -> (" << xc << ", " << yc << ") : " << m_Duration << "\n";

	m_XPos += xc;
	m_YPos += yc;

	m_Duration += seconds;

	m_Model->update(seconds);
}

bool Rocket::IsDead(void) {
	return (m_HasColided || m_Duration > ROCKET_LIFE_DURATION);
}

float Rocket::GetX(void) {
	return m_XPos;
}

float Rocket::GetY(void) {
	return m_YPos;
}

void Rocket::Kill(void) {
	m_HasColided = true;
}
