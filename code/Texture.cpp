/*
 * Texture.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#include "Texture.h"

Texture::Texture() {
	// TODO Auto-generated constructor stub

}

Texture::~Texture() {
	// TODO Auto-generated destructor stub
}

bool Texture::Load(const char* filename) {
	SDL_Surface* image;
	GLenum texture_format;
	GLint numColors;

	// load the file into an SDL image
	if (!(image = SDL_LoadBMP(filename))) {
		std::cout << "Error loading image: " << filename << "\n";
		return false;
	}

	// setup the color channels/texture format
	numColors = image->format->BytesPerPixel;
	if (numColors == 4) {
		if (image->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else if (numColors == 3) // no alpha channel
	{
		if (image->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}
	else {
		std::cout << "Warning: The image: '" << filename << "' is not true-color.\n";
	}

	// generate a texture handle
	glGenTextures(1, &textureID);

	// bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// setup the texture
	glTexImage2D(GL_TEXTURE_2D, 0, numColors, image->w, image->h, 0, texture_format,
			GL_UNSIGNED_BYTE, image->pixels);

	glFlush();

	// cleanup the SDL image
//	SDL_FreeSurface(image);

	return true;
}

void Texture::Destroy(void) {
	glDeleteTextures(1, &textureID);
}

void Texture::Bind(void) {
	glBindTexture(GL_TEXTURE_2D, textureID);
}
