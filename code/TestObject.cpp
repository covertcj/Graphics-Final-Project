/*
 * TestObject.cpp
 *
 *  Created on: Oct 30, 2010
 *      Author: covertcj
 */

#include "TestObject.h"

TestObject::TestObject(void) {
	texture = new Texture();
	texture->Load("data/textures/ogrobase.bmp");

	model = new MD2Model("data/shaders/model.vp", "data/shaders/model.fp");
	model->setAnimation(Animation::IDLE);
	model->load("data/models/Ogro/tris.md2");

	angle = 0.0f;
}

TestObject::~TestObject(void) {
	texture->Destroy();
	delete texture;
	delete model;
}

void TestObject::Draw(void) {
	Vertex verts[3];
	verts[0].x = -1.5; verts[0].y =  0.0; verts[0].z =  0.0;
	verts[1].x =  0.0; verts[1].y =  1.5; verts[1].z =  0.0;
	verts[2].x =  0.0; verts[2].y =  0.0; verts[2].z =  1.5;

	glRotatef(angle, 1.0, 1.0, 1.0);

	texture->Bind();

	model->render();

	/*glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv((GLfloat*)&(verts[0]));
		glTexCoord2f(0.5, 1.0);
		glVertex3fv((GLfloat*)&(verts[1]));
		glTexCoord2f(1.0, 0.0);
		glVertex3fv((GLfloat*)&(verts[2]));
	glEnd();*/
}

void TestObject::Update(void) {
	float sec = Timer::GetDT();

	angle = angle + sec * 15;
	if (angle >= 360.0f) {
		angle = 0.0f;
	}

	model->update(Timer::GetDT());
}
