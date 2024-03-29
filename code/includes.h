/*
 * includes.h
 *
 *  Created on: Oct 28, 2010
 *      Author: covertcj
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <list>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

class Scoreboard;
class Rocket;
class MD2Model;
class Player;
class Enemy;
class GLSLProgram;
class AppWindow;
class Texture;
class Level;

enum AnimationEnum {
	IDLE,
	RUN
};

using std::string;
using std::vector;
using std::map;
using std::ifstream;

#define SQUARE_ROOT_2			1.41421356

#define WINDOW_FULLSCREEN		true
#define WINDOW_RESOLUTION_X		1024
#define WINDOW_RESOLUTION_Y		1024
#define WINDOW_BPP				16
#define WINDOW_TITLE			"Ogro Invasion"

#define FONT_PATH				"data/fonts/Abscissa.ttf"

#define LEVEL_SIZE_X			15.0
#define LEVEL_SIZE_Y			15.0
#define LEVEL_DISTANCE			13.0
#define LEVEL_TEXTURE_REPEATS_X	1.0
#define LEVEL_TEXTURE_REPEATS_Y	1.0
#define LEVEL_TO_SCREEN_SCALE_X	WINDOW_RESOLUTION_X / LEVEL_SIZE_X
#define LEVEL_TO_SCREEN_SCALE_Y	WINDOW_RESOLUTION_Y / LEVEL_SIZE_Y

#define ENEMY_VELOCITY			0.8
#define ENEMY_SPAWN_COOL		3.0
#define ENEMY_SPAWN_COOL_MIN	0.5
#define ENEMY_SPAWN_COOL_RED	0.1
#define ENEMY_DECAY_TIMER		30.0

#define PLAYER_VELOCITY			2.2
#define PLAYER_VELOCITY_DIAG	PLAYER_VELOCITY / SQUARE_ROOT_2
#define PLAYER_SHOT_COOLDOWN	0.35

#define ROCKET_VELOCITY			10.0
#define ROCKET_LIFE_DURATION	(LEVEL_SIZE_X + LEVEL_SIZE_Y) / ROCKET_VELOCITY

#define MODEL_PLAYER			"data/models/Ogro/tris.md2"
#define MODEL_ENEMY				"data/models/Ogro/tris.md2"
#define MODEL_LIGHT				"data/models/Ball/tris.md2"
#define MODEL_ROCKET			"data/models/Ball/tris.md2"

#define TEXTURE_GROUND			"data/textures/ground.bmp"
#define TEXTURE_GROUND2			"data/textures/ground2.bmp"
#define TEXTURE_GROUND3			"data/textures/ground3.bmp"
#define TEXTURE_LIGHT			"data/textures/light.bmp"
#define TEXTURE_PLAYER			"data/textures/Ogro/player.bmp"
#define TEXTURE_ENEMY			"data/textures/Ogro/enemy.bmp"
#define TEXTURE_ROCKET			"data/textures/rocket.bmp"

#define VSHADER_GROUND			"data/shaders/ground.vp"
#define FSHADER_GROUND			"data/shaders/ground.fp"
#define VSHADER_PLAYER			"data/shaders/model.vp"
#define FSHADER_PLAYER			"data/shaders/model.fp"
#define VSHADER_ENEMY			"data/shaders/model.vp"
#define FSHADER_ENEMY			"data/shaders/model.fp"
#define VSHADER_LIGHT			"data/shaders/model.vp"
#define FSHADER_LIGHT			"data/shaders/model.fp"
#define VSHADER_ROCKET			"data/shaders/model.vp"
#define FSHADER_ROCKET			"data/shaders/model.fp"

#define LIGHT_AMBIENT_R			0.20
#define LIGHT_AMBIENT_G			0.20
#define LIGHT_AMBIENT_B			0.20

#define LIGHT0_AMBIENT_R		0.00
#define LIGHT0_AMBIENT_G		0.00
#define LIGHT0_AMBIENT_B		0.00

#define LIGHT0_DIFFUSE_R		0.50
#define LIGHT0_DIFFUSE_G		0.50
#define LIGHT0_DIFFUSE_B		0.50

#define LIGHT0_SPECULAR_R		0.50
#define LIGHT0_SPECULAR_G		0.50
#define LIGHT0_SPECULAR_B		0.50

#define LIGHT_ROTATION_SPEED	90.0
#define LIGHT_DISTANCE			0.75

#define FPS_AVERAGE_COUNT		20

#include "Application.h"
#include "Input.h"
#include "Level.h"
#include "md2model.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "Scoreboard.h"
#include "Shader.h"
#include "Texture.h"
#include "Timer.h"
#include "Window.h"

#endif /* INCLUDES_H_ */
