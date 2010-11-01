/*
 * TestObject.cpp
 *
 *  Created on: Oct 30, 2010
 *      Author: covertcj
 */

#include "TestObject.h"

typedef struct SVertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vertex;

typedef struct SColor {
	GLfloat r;
	GLfloat g;
	GLfloat b;
} Color;

TestObject::TestObject(void) {
	angle = 0.0f;
}

TestObject::~TestObject(void) {
}

void TestObject::Draw(void) {
	Vertex verts[3];
	verts[0].x = -1.5; verts[0].y =  0.0; verts[0].z =  0.0;
	verts[1].x =  0.0; verts[1].y =  1.5; verts[1].z =  0.0;
	verts[2].x =  0.0; verts[2].y =  0.0; verts[2].z =  1.5;

	glRotatef(angle, 1.0, 1.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLES);
		glVertex3fv((GLfloat*)&(verts[0]));
		glVertex3fv((GLfloat*)&(verts[1]));
		glVertex3fv((GLfloat*)&(verts[2]));
	glEnd();
}

void TestObject::Update(void) {
	float sec = Timer::GetDT();

	angle = angle + sec * 15;
	if (angle >= 360.0f) {
		angle = 0.0f;
	}
}
