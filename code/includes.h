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

#include <SDL/SDL.h>
#include <GL/glew.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

class MD2Model;
class Player;
class GLSLProgram;
class AppWindow;
class TestObject;
class Texture;
class Level;

enum AnimationEnum {
	IDLE,
	RUN
};

#include "Application.h"
#include "Input.h"
#include "Level.h"
#include "md2model.h"
#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "Timer.h"
#include "Window.h"
#include "TestObject.h"

using std::string;
using std::vector;
using std::map;
using std::ifstream;

#define WINDOW_FULLSCREEN	false
#define WINDOW_RESOLUTION_X	1024
#define WINDOW_RESOLUTION_Y	1024
#define WINDOW_BPP			16
#define WINDOW_TITLE		"Title"

#define LEVEL_SIZE_X			15.0
#define LEVEL_SIZE_Y			15.0
#define LEVEL_DISTANCE			13.0
#define LEVEL_TEXTURE_REPEATS_X	1.0
#define LEVEL_TEXTURE_REPEATS_Y	1.0
#define LEVEL_TO_SCREEN_SCALE_X	WINDOW_RESOLUTION_X / LEVEL_SIZE_X
#define LEVEL_TO_SCREEN_SCALE_Y	WINDOW_RESOLUTION_Y / LEVEL_SIZE_Y

#define PLAYER_VELOCITY			2.0

#define MODEL_PLAYER			"data/models/Ogro/tris.md2"
#define MODEL_ENEMY				"data/models/Ogro/tris.md2"
#define MODEL_LIGHT				"data/models/Ball/tris.md2"

#define TEXTURE_GROUND			"data/textures/ground.bmp"
#define TEXTURE_LIGHT			"data/textures/light.bmp"//"data/textures/light.bmp"
#define TEXTURE_PLAYER			"data/textures/Ogro/player.bmp"
#define TEXTURE_ENEMY			"data/textures/Ogro/enemy.bmp"

#define VSHADER_GROUND			"data/shaders/ground.vp"
#define FSHADER_GROUND			"data/shaders/ground.fp"
#define VSHADER_PLAYER			"data/shaders/model.vp"
#define FSHADER_PLAYER			"data/shaders/model.fp"
#define VSHADER_ENEMY			"data/shaders/model.vp"
#define FSHADER_ENEMY			"data/shaders/model.fp"
#define VSHADER_LIGHT			"data/shaders/model.vp"
#define FSHADER_LIGHT			"data/shaders/model.fp"

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

#define ANIMATION_DELAY_RUN		10

#endif /* INCLUDES_H_ */
