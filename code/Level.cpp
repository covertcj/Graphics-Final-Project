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
	int numVerts = 4;

	m_GroundTexture = groundTexture;
	m_GroundShader = new GLSLProgram(VSHADER_GROUND, FSHADER_GROUND);
	m_GroundShader->initialize();

	m_PlayerTexture = new Texture();
	m_PlayerTexture->Load(TEXTURE_PLAYER);
	m_Player = new Player(m_PlayerTexture);

	Vertex verts[numVerts];
	verts[0].x = 0.0;			verts[0].y = 0.0; 			verts[0].z = 0.0;
	verts[1].x = LEVEL_SIZE_X; 	verts[1].y = 0.0; 			verts[1].z = 0.0;
	verts[2].x = LEVEL_SIZE_X; 	verts[2].y = LEVEL_SIZE_Y; 	verts[2].z = 0.0;
	verts[3].x = 0.0; 			verts[3].y = LEVEL_SIZE_Y; 	verts[3].z = 0.0;

	Vertex norms[numVerts];
	norms[0].x = 0.0; norms[0].y = 0.0; norms[0].z = 1.0;
	norms[1].x = 0.0; norms[1].y = 0.0; norms[1].z = 1.0;
	norms[2].x = 0.0; norms[2].y = 0.0; norms[2].z = 1.0;
	norms[3].x = 0.0; norms[3].y = 0.0; norms[3].z = 1.0;

	TexCoord texCoords[numVerts];
	texCoords[0].s = 0.0; 						texCoords[0].t = 0.0;
	texCoords[1].s = LEVEL_TEXTURE_REPEATS_X; 	texCoords[1].t = 0.0;
	texCoords[2].s = LEVEL_TEXTURE_REPEATS_X;	texCoords[2].t = LEVEL_TEXTURE_REPEATS_Y;
	texCoords[3].s = 0.0; 						texCoords[3].t = LEVEL_TEXTURE_REPEATS_Y;

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numVerts, &verts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * numVerts, &texCoords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_normalsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numVerts, &norms[0], GL_STATIC_DRAW);

	m_PlayerLight.position.x = 0.0;
	m_PlayerLight.position.y = 0.0;
	m_PlayerLight.position.z = -LEVEL_DISTANCE + 1.0;

	m_PlayerLight.ambient.x = LIGHT0_AMBIENT_R;
	m_PlayerLight.ambient.y = LIGHT0_AMBIENT_G;
	m_PlayerLight.ambient.z = LIGHT0_AMBIENT_B;

	m_PlayerLight.diffuse.x = LIGHT0_DIFFUSE_R;
	m_PlayerLight.diffuse.y = LIGHT0_DIFFUSE_G;
	m_PlayerLight.diffuse.z = LIGHT0_DIFFUSE_B;

	m_PlayerLight.specular.x = LIGHT0_SPECULAR_R;
	m_PlayerLight.specular.y = LIGHT0_SPECULAR_G;
	m_PlayerLight.specular.z = LIGHT0_SPECULAR_B;
}

void Level::Destroy(void) {
	m_GroundShader->unload();
	delete m_GroundShader;

	// cleanup the player
	m_PlayerTexture->Destroy();
	delete m_PlayerTexture;
	delete m_Player;
}

void Level::Draw(void) {
	glPushMatrix();
		DrawLevelPlane();
	glPopMatrix();

	glFlush();

	glPushMatrix();
		m_Player->Draw();
	glPopMatrix();
}

void Level::Update(void) {
	m_Player->Update();
	m_PlayerLight.position.x = -(LEVEL_SIZE_X / 2.0) + m_Player->GetX();
	m_PlayerLight.position.y = -(LEVEL_SIZE_Y / 2.0) + m_Player->GetY();
}

void Level::DrawLevelPlane(void) {

    static float modelviewMatrix[16];
    static float projectionMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

	m_GroundTexture->Bind();

	m_GroundShader->bindShader();
	m_GroundShader->sendUniform4x4("modelview_matrix", modelviewMatrix);
	m_GroundShader->sendUniform4x4("projection_matrix", projectionMatrix);
	m_GroundShader->sendUniform("ambientLight", LIGHT_AMBIENT_R, LIGHT_AMBIENT_G, LIGHT_AMBIENT_B);
	m_GroundShader->sendUniform("light0Position", m_PlayerLight.position.x, m_PlayerLight.position.y, m_PlayerLight.position.z);
	m_GroundShader->sendUniform("light0Ambient", m_PlayerLight.ambient.x, m_PlayerLight.ambient.y, m_PlayerLight.ambient.z);
	m_GroundShader->sendUniform("light0Diffuse", m_PlayerLight.diffuse.x, m_PlayerLight.diffuse.y, m_PlayerLight.diffuse.z);
	m_GroundShader->sendUniform("light0ConstantAttenuation", 0.35f);
	m_GroundShader->sendUniform("light0LinearAttenuation", 0.050f);
	m_GroundShader->sendUniform("light0QuadraticAttenuation", 0.025f);
	m_GroundShader->sendUniform("texture0", 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
	glVertexAttribPointer((GLint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
	glVertexAttribPointer((GLint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	/*glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv((const GLfloat*) &(verts[0]));
		glTexCoord2f(LEVEL_TEXTURE_REPEATS_X, 0.0);
		glVertex3fv((const GLfloat*) &(verts[1]));
		glTexCoord2f(LEVEL_TEXTURE_REPEATS_X, LEVEL_TEXTURE_REPEATS_Y);
		glVertex3fv((const GLfloat*) &(verts[2]));
		glTexCoord2f(0.0, LEVEL_TEXTURE_REPEATS_Y);
		glVertex3fv((const GLfloat*) &(verts[3]));
	glEnd();*/
}
