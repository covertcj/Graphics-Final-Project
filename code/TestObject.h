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

	Texture* texture;
	MD2Model* model;
};

#endif /* TESTOBJECT_H_ */
