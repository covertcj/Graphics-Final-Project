/*
 * Scoreboard.cpp
 *
 *  Created on: Nov 11, 2010
 *      Author: covertcj
 */

#include "Scoreboard.h"

Scoreboard::Scoreboard() {
	// TODO Auto-generated constructor stub

}

Scoreboard::~Scoreboard() {
	// TODO Auto-generated destructor stub
}

void Scoreboard::Initialize(void) {
	TTF_Init();

	if(!(m_Font = TTF_OpenFont(FONT_PATH, 20))) {
		printf("Error loading font: %s", TTF_GetError());
		exit(1);
	}

	m_SecondsAlive = 0.0f;
	m_ShotsFired = 0;
	m_EnemiesKilled = 0;
}

void Scoreboard::Destroy(void) {
	TTF_CloseFont(m_Font);
	TTF_Quit();
}

void glEnable2D()
{
	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void glDisable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Scoreboard::Draw(void) {
	// setup the text to draw
	std::stringstream secondsAlive;
	secondsAlive << "Seconds Alive: " << m_SecondsAlive;
	std::stringstream shotsFired;
	shotsFired << "Shots Fired: " << m_ShotsFired;
	std::stringstream enemiesKilled;
	enemiesKilled << "Enemies Killed: " << m_EnemiesKilled;
	std::stringstream accuracy;
	if (m_ShotsFired > 0) {
		accuracy << "Accuracy: " << ((float)m_EnemiesKilled / (float)m_ShotsFired) * 100.0f << "%";
	}
	else {
		accuracy << "Accuracy: N/A";
	}
	std::stringstream fps;
	fps << "FPS: " << m_FPS;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	SDL_Rect position;
	position.x = WINDOW_RESOLUTION_X / 3;
	position.y = WINDOW_RESOLUTION_Y / 1.5;

	/*glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_QUADS);
			glVertex3f(5.0, 5.0, -5.0);
			glVertex3f(10.0, 5.0, -5.0);
			glVertex3f(10.0, 10.0, -5.0);
			glVertex3f(5.0, 10.0, -5.0);
		glEnd();
	glPopMatrix();*/

	// allow you to draw text in 2D mode
	glEnable2D();
	glDisable(GL_DEPTH_TEST);
	// render text
	RenderText(secondsAlive.str().c_str(), m_Font, color, &position);
	position.y -= position.h;
	RenderText(shotsFired.str().c_str(), m_Font, color, &position);
	position.y -= position.h;
	RenderText(enemiesKilled.str().c_str(), m_Font, color, &position);
	position.y -= position.h;
	RenderText(accuracy.str().c_str(), m_Font, color, &position);
	position.x = 0;
	position.y = 0;
	RenderText(fps.str().c_str(), m_Font, color, &position);

	// exit 2D mode
	glEnable(GL_DEPTH_TEST);
	glDisable2D();
}

void Scoreboard::KillEnemy(void) {
	m_EnemiesKilled++;
}

void Scoreboard::Shoot(void) {
	m_ShotsFired++;
}

void Scoreboard::Update(bool isPlayerDead) {
	float dt = Timer::GetDT();
	if (!isPlayerDead) {
		m_SecondsAlive += dt;
	}

	// find average FPS
	m_FPS = 0.0;
	for (int i = 1; i < FPS_AVERAGE_COUNT; i++) {
		m_DTs[i] = m_DTs[i - 1];
		m_FPS += m_DTs[i];
	}
	m_DTs[0] = dt;
	m_FPS += dt;
	m_FPS = FPS_AVERAGE_COUNT / m_FPS;
}

int nextpoweroftwo(int x)
{
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}

void Scoreboard::RenderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location)
{
	glUseProgram(0);

	SDL_Surface *initial;
	SDL_Surface *intermediary;
	//SDL_Rect rect;
	int w,h;
	GLuint texture = 0;

	/* Use SDL_TTF to render our text */
	initial = TTF_RenderText_Blended(font, text, color);

	/* Convert the rendered text to a known format */
	w = nextpoweroftwo(initial->w);
	h = nextpoweroftwo(initial->h);

	intermediary = SDL_CreateRGBSurface(0, w, h, 32,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(initial, 0, intermediary, 0);

	/* Tell GL about our new texture */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA,
			GL_UNSIGNED_BYTE, intermediary->pixels );

	/* GL_NEAREST looks horrible, if scaled... */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* prepare to render our texture */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);

	/* Draw a quad at location */
	glBegin(GL_QUADS);
		/* Recall that the origin is in the lower-left corner
		   That is why the TexCoords specify different corners
		   than the Vertex coors seem to. */
		glTexCoord2f(0.0f, 1.0f);
			glVertex2f(location->x    , location->y);
		glTexCoord2f(1.0f, 1.0f);
			glVertex2f(location->x + w, location->y);
		glTexCoord2f(1.0f, 0.0f);
			glVertex2f(location->x + w, location->y + h);
		glTexCoord2f(0.0f, 0.0f);
			glVertex2f(location->x    , location->y + h);
	glEnd();

	/* Bad things happen if we delete the texture before it finishes */
	glFinish();

	/* return the deltas in the unused w,h part of the rect */
	location->w = initial->w;
	location->h = initial->h;

	/* Clean up */
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture);
}

