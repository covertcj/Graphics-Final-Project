/*
 * Level.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#include "Level.h"

Level::Level(void) {
	// TODO Auto-generated constructor stub

}

Level::~Level(void) {
	// TODO Auto-generated destructor stub
}

void Level::Initialize(Texture* groundTexture) {
	m_GroundTexture = groundTexture;
	m_GroundShader = new GLSLProgram(VSHADER_GROUND, FSHADER_GROUND);
}

void Level::Destroy(void) {
	m_GroundShader->unload();
	delete m_GroundShader;
}

void Level::Draw(void) {
	DrawLevelPlane();
}

void Level::Update(void) {

}

void Level::DrawLevelPlane(void) {
	Vertex verts[4];

	verts[0].x = 0.0;
	verts[0].y = 0.0;
	verts[0].z = 0.0;

	verts[1].x = LEVEL_SIZE_X;
	verts[1].y = 0.0;
	verts[1].z = 0.0;

	verts[2].x = LEVEL_SIZE_X;
	verts[2].y = LEVEL_SIZE_Y;
	verts[2].z = 0.0;

	verts[3].x = 0.0;
	verts[3].y = LEVEL_SIZE_Y;
	verts[3].z = 0.0;

    static float modelviewMatrix[16];
    static float projectionMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

	m_GroundTexture->Bind();

	m_GroundShader->bindShader();
	m_GroundShader->sendUniform4x4("modelview_matrix", modelviewMatrix);
	m_GroundShader->sendUniform4x4("projection_matrix", projectionMatrix);
	m_GroundShader->sendUniform("texture0", 0);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv((const GLfloat*) &(verts[0]));
		glTexCoord2f(LEVEL_TEXTURE_REPEATS_X, 0.0);
		glVertex3fv((const GLfloat*) &(verts[1]));
		glTexCoord2f(LEVEL_TEXTURE_REPEATS_X, LEVEL_TEXTURE_REPEATS_Y);
		glVertex3fv((const GLfloat*) &(verts[2]));
		glTexCoord2f(0.0, LEVEL_TEXTURE_REPEATS_Y);
		glVertex3fv((const GLfloat*) &(verts[3]));
	glEnd();
}
