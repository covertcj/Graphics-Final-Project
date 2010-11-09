/*
 * Level.h
 *
 *  Created on: Nov 7, 2010
 *      Author: covertcj
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "includes.h"

typedef struct SVec3 {
	float x;
	float y;
	float z;
} Vec3;

typedef struct SLight {
	Vec3 position;
	Vec3 diffuse;
	Vec3 ambient;
	Vec3 specular;
} Light;

class Level {
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(Texture* groundTexture);
	void Destroy(void);

	void Update(void);
	void Draw(void);

private:
	void DrawLevelPlane(void);

	Light m_PlayerLight;

	GLSLProgram* m_GroundShader;
	Texture* m_GroundTexture;

	Player* m_Player;
	Texture* m_PlayerTexture;

    GLuint m_vertexBuffer;
    GLuint m_texCoordBuffer;
    GLuint m_normalsBuffer;
};

#endif /* LEVEL_H_ */
