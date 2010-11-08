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

class GLSLProgram;
class AppWindow;
class TestObject;
class Texture;
class Level;


#include "Application.h"
#include "Input.h"
#include "Level.h"
#include "md2model.h"
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
#define WINDOW_RESOLUTION_X	600
#define WINDOW_RESOLUTION_Y	600
#define WINDOW_BPP			16
#define WINDOW_TITLE		"Title"

#define LEVEL_SIZE_X			50.0
#define LEVEL_SIZE_Y			50.0
#define LEVEL_DISTANCE			50.0
#define LEVEL_TEXTURE_REPEATS_X	4.0
#define LEVEL_TEXTURE_REPEATS_Y	4.0

#define TEXTURE_GROUND			"data/textures/ground.bmp"

#define VSHADER_GROUND			"data/shaders/ground.vp"
#define FSHADER_GROUND			"data/shaders/ground.fp"



#endif /* INCLUDES_H_ */
