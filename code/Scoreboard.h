/*
 * Scoreboard.h
 *
 *  Created on: Nov 11, 2010
 *      Author: covertcj
 */

#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "includes.h"

class Scoreboard {
public:
	Scoreboard();
	virtual ~Scoreboard();

	void Initialize(void);
	void Destroy(void);

	void Draw(void);
	void KillEnemy(void);
	void Shoot(void);
	void Update(void);

private:
	void RenderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location);

	TTF_Font* m_Font;

	float m_SecondsAlive;
	int m_ShotsFired;
	int m_EnemiesKilled;
};

#endif /* SCOREBOARD_H_ */


