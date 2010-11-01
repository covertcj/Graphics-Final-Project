/*
 * TestObject.h
 *
 *  Created on: Oct 30, 2010
 *      Author: covertcj
 */

#ifndef TESTOBJECT_H_
#define TESTOBJECT_H_

#include "includes.h"

class TestObject {
public:
	TestObject(void);
	virtual ~TestObject(void);

	void Draw(void);
	void Update(void);

private:
	float angle;

	unsigned int m_vaoID[2];
	unsigned int m_vboID[3];
};

#endif /* TESTOBJECT_H_ */
