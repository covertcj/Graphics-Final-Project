/*
 * Rocket.h
 *
 *  Created on: Nov 9, 2010
 *      Author: covertcj
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#include "includes.h"

class Rocket {
public:
	Rocket(float x, float y, float rot, Texture* tex);
	virtual ~Rocket(void);

	void Draw(void);
	void Update(void);

	bool IsDead(void);

private:
	float m_XPos;
	float m_YPos;
	float m_Rotation;

	float m_Duration;

	bool m_HasColided;

	Texture* m_Texture;
	MD2Model* m_Model;
};

#endif /* ROCKET_H_ */
