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

void Level::Initialize(Texture* groundTexture, Texture* lightTexture) {
	int numVerts = 4;

	m_GroundTexture = groundTexture;
	m_GroundShader = new GLSLProgram(VSHADER_GROUND, FSHADER_GROUND);
	m_GroundShader->initialize();
	m_GroundShader->bindAttrib(0, "a_Vertex");
	m_GroundShader->bindAttrib(1, "a_TexCoord0");
	m_GroundShader->bindAttrib(2, "a_Normal");
	m_GroundShader->linkProgram();

	m_LightTexture = lightTexture;
	/*m_LightShader = new GLSLProgram(VSHADER_LIGHT, FSHADER_LIGHT);
	m_LightShader->initialize();
	m_LightShader->bindAttrib(0, "a_Vertex");
	m_LightShader->bindAttrib(1, "a_TexCoord0");
	m_LightShader->linkProgram();*/
	m_LightModel = new MD2Model(VSHADER_LIGHT, FSHADER_LIGHT);
	m_LightModel->load(MODEL_LIGHT);

	m_PlayerTexture = new Texture();
	m_PlayerTexture->Load(TEXTURE_PLAYER);
	m_Player = new Player(m_PlayerTexture);

	m_EnemyTexture = new Texture();
	m_EnemyTexture->Load(TEXTURE_ENEMY);

	m_RocketTexture = new Texture();
	m_RocketTexture->Load(TEXTURE_ROCKET);

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
	m_PlayerLight.position.z = -LEVEL_DISTANCE + 3.0;

	m_PlayerLight.ambient.x = LIGHT0_AMBIENT_R;
	m_PlayerLight.ambient.y = LIGHT0_AMBIENT_G;
	m_PlayerLight.ambient.z = LIGHT0_AMBIENT_B;

	m_PlayerLight.diffuse.x = LIGHT0_DIFFUSE_R;
	m_PlayerLight.diffuse.y = LIGHT0_DIFFUSE_G;
	m_PlayerLight.diffuse.z = LIGHT0_DIFFUSE_B;

	m_PlayerLight.specular.x = LIGHT0_SPECULAR_R;
	m_PlayerLight.specular.y = LIGHT0_SPECULAR_G;
	m_PlayerLight.specular.z = LIGHT0_SPECULAR_B;

	m_PlayerLight.rotation = 0.0f;

	m_EnemyTimer = 0.0;
	m_EnemyTimeBetween = ENEMY_SPAWN_COOL;

	m_Scoreboard = new Scoreboard();
	m_Scoreboard->Initialize();
}

void Level::Destroy(void) {
	m_GroundShader->unload();
	delete m_GroundShader;

	delete m_LightModel;

	// cleanup the player
	m_PlayerTexture->Destroy();
	delete m_PlayerTexture;
	delete m_Player;

	m_Scoreboard->Destroy();
	delete m_Scoreboard;
}

void Level::Draw(void) {
	DrawLevelPlane();

	//m_Enemy->Draw();
	m_Player->Draw();
	DrawLight();

	// draw all of the rockets
	std::list<Rocket*>::iterator rocket_it;
	for (rocket_it = m_Rockets.begin() ; rocket_it != m_Rockets.end(); rocket_it++) {
		(*rocket_it)->Draw();
	}

	std::list<Enemy*>::iterator enemy_it;
	for (enemy_it = m_Enemies.begin() ; enemy_it != m_Enemies.end(); enemy_it++) {
		(*enemy_it)->Draw();
	}

	if (Input::IsKeyDown(SDLK_TAB)) {
		m_Scoreboard->Draw();
	}
}

void Level::Update(void) {
	float dt = Timer::GetDT();

	m_Player->Update();
	m_PlayerLight.position.x = -(LEVEL_SIZE_X / 2.0) + m_Player->GetX();
	m_PlayerLight.position.y = -(LEVEL_SIZE_Y / 2.0) + m_Player->GetY();
	m_PlayerLight.rotation += LIGHT_ROTATION_SPEED * dt;
	if (m_PlayerLight.rotation >= 360.0) {
		m_PlayerLight.rotation -= 360.0;
	}

	//m_Enemy->Update(m_Player);
	// update all of the enemies
	std::list<Enemy*>::iterator enemy_it;
	for (enemy_it = m_Enemies.begin() ; enemy_it != m_Enemies.end(); enemy_it++) {
		// if dead, remove it from the list and delete it
		if ((*enemy_it)->IsDecayed()) {
			Enemy* tmp = (*enemy_it);
			enemy_it--;
			m_Enemies.remove(tmp);
			delete tmp;
		}
		// else, update it
		else {
			(*enemy_it)->Update(m_Player);
		}
	}

	// update all of the rockets
	std::list<Rocket*>::iterator rocket_it;
	for (rocket_it = m_Rockets.begin() ; rocket_it != m_Rockets.end(); rocket_it++) {
		// if dead, remove it from the list and delete it
		if ((*rocket_it)->IsDead()) {
			Rocket* tmp = (*rocket_it);
			rocket_it--;
			m_Rockets.remove(tmp);
			delete tmp;
		}
		// else, update it
		else {
			(*rocket_it)->Update();
		}
	}

	// if the user presses the left mouse, shoot a rocket
	if (Input::IsButtonDown(SDL_BUTTON_LEFT)) {
		if (m_Player->CanShoot()) {
			m_Rockets.push_back(new Rocket(m_Player->GetX(), m_Player->GetY(), m_Player->GetRotation(), m_RocketTexture));
			m_Player->Shoot();

			m_Scoreboard->Shoot();
		}
	}

	// check if the player is colliding with any enemies
	for (enemy_it = m_Enemies.begin(); enemy_it != m_Enemies.end(); enemy_it++) {
		if (!(*enemy_it)->IsDead()) {
			float dx = (*enemy_it)->GetX() - m_Player->GetX();
			float dy = (*enemy_it)->GetY() - m_Player->GetY();

			float dist = sqrt(dx * dx + dy * dy);
			float radii = m_Player->GetRadius();// + (*enemy_it)->GetRadius();

			// if the distance is less than the added radii, then a collision
			if (dist < radii) {
				m_Player->Kill();
			}
		}
	}

	// check if the enemies are colliding with any rockets
	for (enemy_it = m_Enemies.begin(); enemy_it != m_Enemies.end(); enemy_it++) {
		for (rocket_it = m_Rockets.begin(); rocket_it != m_Rockets.end(); rocket_it++) {
			if (!(*enemy_it)->IsDead()) {
				float dx = (*rocket_it)->GetX() - (*enemy_it)->GetX();
				float dy = (*rocket_it)->GetY() - (*enemy_it)->GetY();

				float dist = sqrt(dx * dx + dy * dy);
				float radii = (*enemy_it)->GetRadius();// + (*enemy_it)->GetRadius();

				// if the distance is less than the added radii, then a collision
				if (dist < radii) {
					m_Player->incKillCount();
					(*enemy_it)->Kill();
					(*rocket_it)->Kill();
					m_Scoreboard->KillEnemy();
				}
			}
		}
	}

	// enemy spawning
	if (!m_Player->isDead())
	{
		m_EnemyTimer += dt;
		if (m_EnemyTimer > m_EnemyTimeBetween) {
			// reset the timer
			m_EnemyTimer = 0.0;
			// make the next enemy spawn slightly faster
			m_EnemyTimeBetween -= ENEMY_SPAWN_COOL_RED;
			// make sure enemies don't spawn too fast
			if (m_EnemyTimeBetween < ENEMY_SPAWN_COOL_MIN) {
				m_EnemyTimeBetween = ENEMY_SPAWN_COOL_MIN;
			}

			// spawn the enemy
			Level::spawnEnemy();
		}
	}

	m_Scoreboard->Update();
}

void Level::DrawLevelPlane(void) {
	float lightx = m_PlayerLight.position.x;
	float lighty = m_PlayerLight.position.y;

	lightx += cos(degreesToRadians(m_PlayerLight.rotation)) * LIGHT_DISTANCE;
	lighty += sin(degreesToRadians(m_PlayerLight.rotation)) * LIGHT_DISTANCE;

    static float modelviewMatrix[16];
    static float projectionMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

	m_GroundTexture->Bind();

	m_GroundShader->bindShader();
	m_GroundShader->sendUniform4x4("modelview_matrix", modelviewMatrix);
	m_GroundShader->sendUniform4x4("projection_matrix", projectionMatrix);
	m_GroundShader->sendUniform("ambientLight", LIGHT_AMBIENT_R, LIGHT_AMBIENT_G, LIGHT_AMBIENT_B);
	m_GroundShader->sendUniform("light0Position", lightx, lighty, m_PlayerLight.position.z);
	m_GroundShader->sendUniform("light0Ambient", m_PlayerLight.ambient.x, m_PlayerLight.ambient.y, m_PlayerLight.ambient.z);
	m_GroundShader->sendUniform("light0Diffuse", m_PlayerLight.diffuse.x, m_PlayerLight.diffuse.y, m_PlayerLight.diffuse.z);
	m_GroundShader->sendUniform("light0ConstantAttenuation", 0.15f);
	m_GroundShader->sendUniform("light0LinearAttenuation", 0.010f);
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
}

void Level::DrawLight() {
	float x = m_PlayerLight.position.x + (LEVEL_SIZE_X / 2.0);
	float y = m_PlayerLight.position.y + (LEVEL_SIZE_X / 2.0);

	x += cos(degreesToRadians(m_PlayerLight.rotation)) * LIGHT_DISTANCE;
	y += sin(degreesToRadians(m_PlayerLight.rotation)) * LIGHT_DISTANCE;

	m_LightTexture->Bind();

	glPushMatrix();
		glTranslatef(x, y, 1.0);

		m_LightModel->render();
	glPopMatrix();
}

void Level::spawnEnemy(void)
{
	float x, y;
	int side = rand() % 4;

	// if the right side...
	if (side == 0) {
		x = LEVEL_SIZE_X;
		y = (rand() % (10 * (int)(LEVEL_SIZE_Y))) / 10.0;;
	}
	// if the top side...
	else if (side == 1) {
		x = (rand() % (10 * (int)(LEVEL_SIZE_X))) / 10.0;;
		y = LEVEL_SIZE_Y;
	}
	// if the left side...
	else if (side == 2) {
		x = 0;
		y = (rand() % (10 * (int)(LEVEL_SIZE_Y))) / 10.0;;
	}
	// if bottom side...
	else {
		x = (rand() % (10 * (int)(LEVEL_SIZE_X))) / 10.0;;
		y = 0;
	}

	Enemy* enemy = new Enemy(m_EnemyTexture);

	enemy->SetX(x);
	enemy->SetY(y);

	enemy->SetTargetX(m_Player->GetX());
	enemy->SetTargetY(m_Player->GetY());

	m_Enemies.push_back(enemy);
}
