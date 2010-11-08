/*
 * Texture.h
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "includes.h"

class Texture {
public:
	Texture();
	virtual ~Texture();

	bool Load(const char* filename);
	void Destroy(void);

	void Bind(void);

private:
	GLuint textureID;
};

#endif /* TEXTURE_H_ */
