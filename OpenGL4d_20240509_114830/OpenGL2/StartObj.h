#include"Game.h"
#include"Structures4D.h"

void Game::startObjects(int level,const char* filePath)
{
	this->camera.fit_direction(3);
	cameraDirText = "W";
	if (filePath == "")
	{
		switch (level)
		{
		case 1:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			generate_room4D(glm::vec4(-998.5f, 64.f, 0.f, 0.f), glm::vec4(2000.f, 3.f, 3.f, 3.f), 1, 5, 7, 0, 0, 0, true,true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			generate_window4D(glm::vec4(-1.3f, 64.f, 0.f, 0.f), glm::vec4(5.6f, 3.f, 3.f, 3.f),glm::vec4(0.f,1.5f,0.f,0.f),glm::vec2(1.25f, 1.25f),1,0,true,0.f,true,this->wallTexs3D[GROUND],glm::vec4(0.f,0.f,0.f,1.f),this->shaders[WALLD4],true,true, this->wallTexs3D[PURE_WHITE],glm::vec4(1.f), this->shaders[WALLD4],true,this->wallTexs3D[GLASS], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4],&this->walls4D);
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(5.8f, 3.2f, 0.2f, 3.f)/2.f), glm::vec4(-1.2f, 65.4f, -1.6f, 0.f), alg::bivec4(), glm::vec4(5.8f, 3.2f, 0.2f, 3.f), 1.265f, 0.f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(12.f, 0.1f, 0.01f, 3.f) / 2.f), glm::vec4(-4.5f, 64.05f, -1.495f, 0.f), alg::bivec4(), glm::vec4(12.f, 0.1f, 0.01f, 3.f), 1.265f, 0.f, true, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(0.f, 0.f, 0.f, 1.f), NONE, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1985.f, 3.2f, 0.2f, 3.f)/2.f), glm::vec4(-1006.f, 65.4f, -1.6f, 0.f), alg::bivec4(), glm::vec4(1985.f, 3.2f, 0.2f, 3.f), 1.265f, 0.f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1985.f, 0.1f, 0.01f, 3.f) / 2.f), glm::vec4(-1006.f, 64.05f, -1.495f, 0.f), alg::bivec4(), glm::vec4(1985.f, 0.1f, 0.01f, 3.f), 1.265f, 0.f, true, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(0.f, 0.f, 0.f, 1.f), NONE, this->shaders[WALLD4]));
			generate_room4D(glm::vec4(-12.f, 64.f, -1001.5f, 0.f), glm::vec4(3.f, 3.f, 2000.f, 3.f), 1, 3, 7, 0, 0, 0, true,true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, 3.2f, 1987.6f, 3.f) / 2.f), glm::vec4(-10.4f, 65.4f, -1007.7f, 0.f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 1987.6f, 3.f), 1.265f, 0.f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, 1987.8f, 3.f) / 2.f), glm::vec4(-10.505f, 64.05f, -1007.6f, 0.f), alg::bivec4(), glm::vec4(0.01f, 0.1f, 1987.8f, 3.f), 1.265f, 0.f, true, this->wallTexs3D[GROUND], 0.f, glm::vec4(0.f, 0.f, 0.f, 1.f), NONE, this->shaders[WALLD4]));
			generate_room4D(glm::vec4(-7.3f, 64.f, -7.7f, 0.f), glm::vec4(6.f, 3.f, 12.f, 8.f), 4, 5, 0, 0, 0, 0, true,true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_door4D(glm::vec4(-10.4f, 64.f, -7.7f, 0.f), glm::vec4(6.f, 3.f, 12.f, 8.f), glm::vec4(0, 0, -1.9f, 0.f), glm::vec2(0.8f, 1.9f), 1, 1, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(0.2f, 0.2f, 0.8f, 0.8f) / 2.f), glm::vec4(-10.4f, 63.9f, -9.6f, 0.f), alg::bivec4(), glm::vec4(0.2f, 0.2f, 0.8f, 0.8f), 1.265f, 0.25f, true, this->wallTexs3D[GROUND], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			generate_door4D(glm::vec4(-7.3f, 64.f, -7.7f, 0.f), glm::vec4(6.4f, 3.2f, 12.4f, 8.f), glm::vec4(0, 0, 3.f, 4.7f), glm::vec2(6.f, 3.2f), 4, 0, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_walkway4D(glm::vec4(-7.3f, 64.f, -4.7f,4.7f), glm::vec4(6.f, 3.f, 6.f, 1.f), 4, true, true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_door4D(glm::vec4(-7.3f, 64.f, -4.7f, 4.7f), glm::vec4(6.4f, 3.2f, 6.4f, 1.f), glm::vec4(0, 0, 0.f, 0.f), glm::vec2(0.8f, 1.9f), 4, 0, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4],true, true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_walkway4D(glm::vec4(-7.3f, 64.f, -4.7f, 10.4f), glm::vec4(1.f, 3.f, 1.f, 10.f), 4, true, true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(1.f, 3.f, 1.f, 0.2f) / 2.f), glm::vec4(-7.3f, 65.5f, -4.7f, 15.5f), alg::bivec4(), glm::vec4(1.f, 3.f, 1.f, 0.2f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(10000.f, 17.f, 10000.f, 10000.f) / 2.f), glm::vec4(0, 55.8f, 0, 0), alg::bivec4(), glm::vec4(10000.f, 16.f, 10000.f, 10000.f), 1.265f, 0.25f, false, this->wallTexs3D[GRASS], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			//this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(), 2, 1.f, glm::vec3(1.f), 0, 0, 1, 0));
			//for (int i = 0; i < 11; i++)
			//{
			//	this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(14 * i - 14 * 5, 66.7875f, 0.f, 0.f), -1, 1.f, glm::vec3(1.f), 0, 0, 1, 0));
			//	//this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(), glm::vec4(1.f, 66.f, 1.f, 2.f), alg::bivec4(), glm::vec4(0.2f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec3(0.2f, 0.54f, 0.77f) * 4.f, NONE, this->shaders[EMITD4]));
			//}
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15 + 7.5f + 3 / 2, 28.5f - 5), 0, 1.f, glm::vec3(1.f),5.f));
			this->worldTime = 150.f;
			break;
		}
		case 2:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.95f, 64.15f, 0.f, 0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, this->wallTexs3D[PURE_RED_GREEN], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.05f, 64.15f, 0.f, 0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, this->wallTexs3D[PURE_RED_GREEN], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.95f, 64.15f, 0.f, -0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, this->wallTexs3D[PURE_RED_GREEN], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.05f, 64.15f, 0.f, -0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, this->wallTexs3D[PURE_RED_GREEN], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.5f, 1.f, 6.f, 1.5f) / 2.f), glm::vec4(3.5f, 64.9f, 0.5f, 0.f), alg::bivec4(), glm::vec4(1.5f, 1.f, 6.f, 1.5f), 3.f, 4.5f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WOODY], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 65.65f, 2.f, 0.f), alg::bivec4(), glm::vec4(0.5f), 1.f, 0.33f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_RED], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 67.65f, -1.25f, 0.f), alg::bivec4(), glm::vec4(0.5f), 1.5f, 0.5f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WHITECONCRETE], 0.5f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 67.65f, -1.75f, 0.f), alg::bivec4(), glm::vec4(0.5f), 1.5f, 0.5f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WHITECONCRETE], 0.5f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(), glm::vec4(3.5f, 66.85f, -1.25f, -0.25f), alg::bivec4(), glm::vec4(0.5f), 1.f, 1.f, 1.265f, 0.f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WHITECONCRETE], 0.5f, glm::vec4(1.f), BOX4D, true, this->shaders[WALLD4]));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(), glm::vec4(3.5f, 66.85f, -1.75f, -0.25f), alg::bivec4(), glm::vec4(0.5f), 1.f, 1.f, 1.265f, 0.f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WHITECONCRETE], 0.5f, glm::vec4(1.f), SPHERE4D, true, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(1.f, 2.f, 1.f, 1.f) / 2.f), glm::vec4(-2.f, 64.8f, -2.f, 0.f), alg::bivec4(), glm::vec4(1.f, 2.f, 1.f, 1.f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			generate_room4D(glm::vec4(0.f, 64.f, 0.f, 0.f), glm::vec4(12, 7, 16, 12), 0, 0, 0, 0, 0, 0,true, true, this->wallTexs3D[CHESSBOARD], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 0.5f), this->shaders[WALLD4], true, this->wallTexs3D[CHESSBOARD], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[CHESSBOARD], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Hypersphere", Hyperspherecol(glm::vec4(2.f)), glm::vec4(0.f, 65.f, 0.f, 0.f), alg::bivec4(), glm::vec4(40.f), 1.265f, 0.f, false, this->wallTexs3D[STARS_SKY], 0.25f, glm::vec4(1.f), NONE, this->shaders[EMITD4]));
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(10000.f, 17.f, 10000.f, 10000.f) / 2.f), glm::vec4(0.f, 55.8f, 0.f, 0.f), alg::bivec4(), glm::vec4(10000.f, 16.f, 10000.f, 10000.f), 1.265f, 0.25f, false, this->wallTexs3D[GRASS], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));

			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(1.f, 70.5f, 0.f, 0), -1, 50.f, glm::vec3(0.2f, 0.54f, 0.77f)));
			//this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(), glm::vec4(1.f, 66.f, 1.f, 2.f), alg::bivec4(), glm::vec4(0.2f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec3(0.2f, 0.54f, 0.77f) * 4.f, NONE, this->shaders[EMITD4]));
			this->worldTime = 150.f;
			break;
		}
		case 3:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			generate_room4D(glm::vec4(0.f, 64.f, 0.f, 5.f), glm::vec4(24, 6, 16, 24), 4, 0, 0, 0, 0, 0,true, true, this->wallTexs3D[WHITECONCRETE], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			generate_door4D(glm::vec4(0.f, 64, 0, 5.f), glm::vec4(24, 6, 16, 24), glm::vec4(0, 0, 0, 0), glm::vec2(0.8f, 1.9f), 4, 1, true, 0.f, true, this->wallTexs3D[WHITECONCRETE], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[WHITECONCRETE], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_door4D(glm::vec4(0.f, 64.f, 0.f, 5.f), glm::vec4(24, 6, 16, 24), glm::vec4(0, 0, 0, 0), glm::vec2(0.5f, 1.7f), 4, 0, true, 0.f, true, this->wallTexs3D[WHITECONCRETE], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[WHITECONCRETE], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f, 1.7f, 0.5f, 0.05f) / 2.f), glm::vec4(0.f, 64.85f, 0.f, 17.025f), alg::bivec4(), glm::vec4(0.5f, 1.7f, 0.5f, 0.05f), 1.f, 1.f, 0.f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WOODY], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->hingeConstraints.push_back(new HingeConstraint4D(glm::vec4(-0.25f, 63.85f, 0.25f, 17.05f), glm::vec4(-0.25f, -1.f, 0.25f, -0.025f), glm::vec4(), this->rigidBodies4D.size() - 1, -1));
			this->hingeConstraints.push_back(new HingeConstraint4D(glm::vec4(-0.25f, 65.85f, 0.25f, 17.05f), glm::vec4(-0.25f, 1.f, 0.25f, -0.025f), glm::vec4(), this->rigidBodies4D.size() - 1, -1));
			this->hingeConstraints.push_back(new HingeConstraint4D(glm::vec4(0.25f, 63.85f, 0.25f, 17.05f), glm::vec4(0.25f, -1.f, 0.25f, -0.025f), glm::vec4(), this->rigidBodies4D.size() - 1, -1));
			this->hingeConstraints.push_back(new HingeConstraint4D(glm::vec4(0.25f, 65.85f, 0.25f, 17.05f), glm::vec4(0.25f, 1.f, 0.25f, -0.025f), glm::vec4(), this->rigidBodies4D.size() - 1, -1));
			generate_walkway4D(glm::vec4(0, 64.f, 0, 17.55f), glm::vec4(0.825f, 3.f, 0.825f, 0.9f), 4, true, true, this->wallTexs3D[WOODX], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[WOODY], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_room4D(glm::vec4(0, 64.f, 0, 18.5), glm::vec4(1, 3, 1, 1), 1, 8, 0, 0, 0, 0,true, true, this->wallTexs3D[WOODX], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, this->wallTexs3D[WOODY], glm::vec4(1), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			generate_walkway4D(glm::vec4(1.95f, 64.f, 0, 18.5f), glm::vec4(2.9f, 3.f, 0.825f, 0.825f), 1, true, true, this->wallTexs3D[WOODX], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[WOODY], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, this->wallTexs3D[WOODY], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);

			generate_door4D(glm::vec4(13.5f, 64, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(0, 0, 0, -6), glm::vec2(0.8f, 1.9f), 5, 0, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[WHITE], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[STARS], glm::vec4(1.f), this->shaders[EMITD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_room4D(glm::vec4(13.5f, 64, 0, 24.5f), glm::vec4(20, 6, 15, 14), 5, 3, 0, 0, 0, 0, true,true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			generate_floor4D(glm::vec4(13.5f, 67, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(2, 0, 0.75f, 1), glm::vec4(1, 0, 3.5f, 1), true, false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GROUND], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], &this->walls4D);
			generate_door4D(glm::vec4(13.5f, 64, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(0, 0, 0, 4), glm::vec2(0.8f, 1.9f), 3, 0, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[WHITE], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[STARS], glm::vec4(1.f), this->shaders[EMITD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);

			generate_table4D(glm::vec4(13.5f + 2 - 10 - 0.7, 64, 0, 24.5f - 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, this->wallTexs3D[C1], true, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
			generate_table4D(glm::vec4(13.5f + 2 - 10 - 0.7, 64, 0, 24.5f), glm::vec4(1, 1.2f, 3, 2), 1.f, true, this->wallTexs3D[C1], true, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
			for (int i = 0; i < 5; i++) {
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f), glm::vec4(1, 1.2f, 3, 2), 1.f, true, this->wallTexs3D[PURE_BLUE], true, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f - 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, this->wallTexs3D[PURE_BLUE], true, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f + 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, this->wallTexs3D[PURE_BLUE], true, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
			}
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, -3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[YELLOWMARBLE], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, -3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, 3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C1], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, 3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C2], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, -3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C3], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, -3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C4], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, 3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C5], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, 3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C2], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));

			generate_steps4D(glm::vec4(15.5f, 64.f, 3.f, 25.5f), glm::vec4(15.5f, 67.1f, -1.f, 25.5f), glm::vec4(1, 3.1f / 20.f, 0.6f, 1), 7, 20, false, this->wallTexs3D[PURE_WHITE], &this->walls4D, this->shaders[WALLD4]);
			this->walls4D.push_back(new Wall4D("Pentatope", Pentachoron(glm::vec4(2) / 2.f), glm::vec4(11.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C1], 0.f, glm::vec4(1.f), MESH4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(2) / 2.f), glm::vec4(13.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C1], 0.f, glm::vec4(1.f), MESH4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("TriPrism", TriPrism(glm::vec4(2) / 2.f), glm::vec4(15.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 1.265f, 0.25f, true, this->wallTexs3D[MARBLE_C1], 0.f, glm::vec4(1.f), MESH4D, this->shaders[WALLD4]));

			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(3.f, 3.f, 3.f, 0.2f) / 2.f), glm::vec4(13.5f, 65.6f, 24, 42.5f), alg::bivec4(), glm::vec4(3.f, 3.f, 3.f, 0.2f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(3.f, 3.f, 3.f, 0.2f) / 2.f), glm::vec4(13.5f, 65.6f, 24, 19.5f), alg::bivec4(), glm::vec4(3.f, 3.f, 3.f, 0.2f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			generate_door4D(glm::vec4(5.4f, 64, 0, 24.5f), glm::vec4(20, 3, 15, 14), glm::vec4(0, 0, 0, 4), glm::vec2(0.8f, 1.9f), 1, 1, true, 0.f, true, this->wallTexs3D[GROUND], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[WHITE], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], true, true, this->wallTexs3D[GLASS], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_walkway4D(glm::vec4(13.5f, 64.1f, 15.05, 28.5f), glm::vec4(3.f, 3.f ,14.9f, 3.f), 3, true, true, this->wallTexs3D[CHESSBOARDMARBLE], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[GRASS], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[CEIL2], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			generate_walkway4D(glm::vec4(13.5f, 64.1f, 24, 38.75f), glm::vec4(3.f, 3.f, 3.f, 17.5f), 4, true, false, this->wallTexs3D[GRASS], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[GRASS], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GLASS], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(3, 0.2f, 3, 3) / 2.f), glm::vec4(13.5f, 63.9, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(3, 0.2f, 3, 3), 1.265f, 0.25f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Glass4D", Hypercube(glm::vec4(3.f, 0.2f, 3.f, 3.f) / 2.f), glm::vec4(13.5f, 67.2, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(3, 0.2f, 3, 3), 1.265f, 0.25f, true, this->wallTexs3D[GLASS], 0.75f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(3, 3.2f, 0.2f, 3) / 2.f), glm::vec4(13.5f, 65.5f, 15 + 7.5f + 3.1, 28.5f), alg::bivec4(), glm::vec4(3, 3.2f, 0.2f, 3), 1.265f, 0.25f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, 3.2f, 3, 3) / 2.f), glm::vec4(13.5f + 3 / 2 + 0.6f, 65.5f, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 3, 3), 1.265f, 0.25f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, 3.2f, 3, 3) / 2.f), glm::vec4(13.5f - 3 / 2 - 0.6f, 65.5f, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 3, 3), 1.265f, 0.25f, false, this->wallTexs3D[WHITEWALL], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			generate_walkway4D(glm::vec4(13.5f, 64.1f, 24, 23.25f), glm::vec4(3, 3, 3, 7.5f), 4, true, false, this->wallTexs3D[GRASS], glm::vec4(1.f), this->shaders[WALLD4], false, this->wallTexs3D[GRASS], glm::vec4(0.f, 0.f, 0.f, 1.f), this->shaders[WALLD4], false, this->wallTexs3D[WHITEWALL], glm::vec4(1.f), this->shaders[WALLD4], true, this->wallTexs3D[GLASS], glm::vec4(1.f), this->shaders[WALLD4], &this->walls4D);
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(10000.f, 17.f, 10000.f, 10000.f) / 2.f), glm::vec4(0, 55.8f, 0, 0), alg::bivec4(), glm::vec4(10000.f, 16.f, 10000.f, 10000.f), 1.265f, 0.25f, false, this->wallTexs3D[GRASS], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));

			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(1.f, 66.f, 1.f, 2.f), -1, 50.f, glm::vec3(0.2f, 0.54f, 0.77f)));
			this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.2f)), glm::vec4(1.f, 66.f, 1.f, 2.f), alg::bivec4(), glm::vec4(0.2f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.2f, 0.54f, 0.77f, 1.f) * 4.f, NONE, this->shaders[EMITD4]));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(4.f, 66, 0, 19.5f), -1, 20.f, glm::vec3(0.2f, 0.5f, 0.2f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 0, 24.5f), -1, 5.f, glm::vec3(0.8f, 0.1f, 0.1f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 70, 0, 24.5f), -1, 5.f, glm::vec3(0.4f, 0.1f, 1.f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15 - 9.f, 28.5f), -1, 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15, 28.5f), -1, 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15 + 9.f, 28.5f), -1, 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15 + 7.5f + 3 / 2, 28.5f - 5), -1, 10.f, glm::vec3(0.8f, 0.4f, 0.4f)));
			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(13.5f, 66, 15 + 7.5f + 3 / 2, 28.5f + 10), -1, 16.f, glm::vec3(0.8f, 0.7f, 0.4f)));
			this->worldTime = 150.f;
			break;
		}
		case 4:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			//this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(1.f, 2.f, 1.f, 1.f) / 2.f), glm::vec4(-2.f, 60.4f, -2.f, 0.f), alg::bivec4(), glm::vec4(1.f, 2.f, 1.f, 1.f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			//generate_terrain4D(8, glm::ivec4(8, 0, 8, 8), &this->terrains4D, this->shaders[TERRAIND4]);
			//this->waters4D.push_back(new Water4D("Water", Waterbox4d(glm::vec4(400.f, 40000.f, 400.f, 400.f)), glm::vec4(0, 55.5f, 0, 0), glm::vec4(400.f, 40000.f, 400.f, 400.f), NONE, this->shaders[WATERD4]));
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					for (int k = 0; k < 10; k++)
					{
						for (int l = 0; l < 10; l++)
						{
							this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1.f) / 2.f), glm::vec4(8 * i, 8*l+0.5f, 8 * j, 8 * k), alg::bivec4(), glm::vec4(1.f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
						}
					}
				}
			}
			this->worldTime = 150.f;
			break;
		}
		case 5:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(4.f, 0.5f, 0.5f, 0.5f) / 2.f), glm::vec4(-7.5f, 75.5f, 2, 0), alg::bivec4(), glm::vec4(4.f, 0.5f, 0.5f, 0.5f), 65.f, 130.f, 1.265f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f), true, this->wallTexs3D[PURE_RED_GREEN], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D[1]->animatePosition4D = glm::vec4(-2.f, 0, 0, 0);
			this->floats4D.push_back(new Float4D(glm::vec4(-9.5f, 75.5f, 2, 0), 1.f, 0.5f, 1, 1));
			this->rotates4D.push_back(new Rotate4D(glm::vec4(-9.5f, 75.5f, 2, 0), glm::vec4(), alg::bivec4(), alg::bivec4(1.f, 0.f, 0.f, 0.f, 0.f, 0.f), true, 1, -1));

			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.5f, 0.5f, 4.f, 0.5f) / 2.f), glm::vec4(-3.5f, 75.5f, 2, 0), alg::bivec4(), glm::vec4(1.5f, 0.5f, 4.f, 0.5f), 65.f, 130.f, 1.265f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f), true, this->wallTexs3D[PURE_RED_GREEN], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D[2]->animatePosition4D = glm::vec4(0, 0, 0, 0);
			this->rotates4D.push_back(new Rotate4D(glm::vec4(), glm::vec4(2.f, 0.f, 0.f, 0.f), alg::bivec4(), alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f), true, 2, 1));

			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1.f, 3.f, 1.f, 1.f) / 2.f), glm::vec4(0, 66.f, -10.f, 0), alg::bivec4(), glm::vec4(1.f, 3.f, 1.f, 1.f), 1.265f, 0.25f, true, this->wallTexs3D[YELLOWMARBLE], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			generate_pool4D(glm::vec4(0.f, 65.7f, 0.f, 0.f), glm::vec4(6.f, 1.5f, 9.f, 4.5f), true, this->wallTexs3D[YELLOWCONCRETE], glm::vec4(1), this->shaders[WALLD4], true, this->wallTexs3D[YELLOWCONCRETE], glm::vec4(1), this->shaders[WALLD4], &this->walls4D);
			this->waters4D.push_back(new Water4D("Water", DoubleQuads4d(glm::vec4(6.01f, 3.01f, 9.01f, 4.51f)), glm::vec4(0, 65.45f, 0, 0), glm::vec4(6.01f, 3.01f, 9.01f, 4.51f), WATER4D, this->shaders[WATERD4]));
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 1; k++)
					{
						generate_billiard4D(glm::vec4(10.f - 0.5f + (float)i / 5.f, 65.21f, 2.f - 1.1f + (float)j / 5.f, -0.5f + (float)k / 5.f), glm::vec4(0.f), alg::bivec4(), this->wallTexs3D[PURE_RED + (int)(7.f + 7.f * sin(12.f * (float)(i + j + k)))], &this->rigidBodies4D, true, 0.f, glm::vec4(1.f), this->shaders[WALLD4]);
					}
				}
			}
			generate_pool_table4D(glm::vec4(10.f, 64.11f, 2.f, 0.f), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, this->wallTexs3D[WOODX], true, this->wallTexs3D[GRASS], true, this->wallTexs3D[WOODY], &this->walls4D, this->shaders[WALLD4]);

			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.f, 1.f, 1.f, 1.f) / 2.f), glm::vec4(-3.f, 71.265f, -10.f, 0.f), alg::bivec4(0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f), glm::vec4(1.f, 1.f, 1.f, 1.f), 1.f, 0.5f, 1.265f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WOODY], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.f, 1.f, 1.f, 1.f) / 2.f), glm::vec4(1.5f, 110.6f, -10.f, 0.f), alg::bivec4(), glm::vec4(1.f, 1.f, 1.f, 1.f), 10.f, 5.f, 1.265f, 0.25f, true, true, glm::vec4(0, -35.f, 0, 0), alg::bivec4(), true, this->wallTexs3D[WOODY], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(8.f, 1.f, 6.f, 6.f) / 2.f), glm::vec4(0.f, 68.5f, -10.f, 0.f), alg::bivec4(-0.02f, -0.02f, -0.02f, -0.02f, -0.02f, -0.02f), glm::vec4(8.f, 1.f, 6.f, 6.f), 10.f, 25.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WOODY], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));

			this->walls4D.push_back(new Wall4D("Glass4D", Hyperpot(glm::vec4(0.4f)), glm::vec4(0.f, 64.2f, -9.f, 0.f), alg::bivec4(), glm::vec4(0.4f), 1.265f, 0.25f, false, this->wallTexs3D[YELLOWCONCRETE], 0.f, glm::vec4(0.9f * 2.1f, 0.55f * 2.1f, 0.45f * 2.1f, 1.f), MESH4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(1.f, 2.f, 1.f, 1.f) / 2.f), glm::vec4(-20.f, 65.f, -2.f, 0.f), alg::bivec4(), glm::vec4(1.f, 2.f, 1.f, 1.f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(10000.f, 17.f, 10000.f, 10000.f) / 2.f), glm::vec4(0, 55.8f, 0, 0), alg::bivec4(), glm::vec4(10000.f, 16.f, 10000.f, 10000.f), 1.265f, 0.25f, false, this->wallTexs3D[GRASS], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			//this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(120000000000000000000000000000.f)/2.f), glm::vec4(280000000000000000000000000000.f, 380000000000000000000000000000.f, 180000000000000000000000000000.f, 0), alg::bivec4(), glm::vec4(120000000000000000000000000000.f), 1.265f, 0.25f, true,this->wallTexs3D[GROUND], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			
			this->worldTime = 150.f;
			break;
		}
		case 6:
		{
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 2.5f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Glass4D", Hypersphere(glm::vec4(0.5f)), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f + 6.f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 1.f, true, this->wallTexs3D[PURE_HARFRED_GREEN], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(1.f)), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f + 6.f, 5.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1000.f, 500.f, 1.265f, 1.f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[WHITECONCRETE], 0.25f, glm::vec4(1.f), SPHERE4D, this->shaders[WALLD4]));
			this->sticks4D.push_back(new Stick4D(glm::vec4(0.f), 1, 3, 5.f, this->wallTexs3D[WHITECONCRETE], glm::vec4(1.f), this->shaders[WALLD4]));

			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(10.f, 0.2f, 10.f, 10.f) / 2.f), glm::vec4(0.f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.f, 0.2f, 10.f, 10.f), 1.265f, 0.25f, true, this->wallTexs3D[WOODZ], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("X", Hypercube(glm::vec4(0.2f, 3.2f, 10.f, 10.f) / 2.f), glm::vec4(5.1f, 64.f + 1.4f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 10.f, 10.f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.f, 0.f, 1.f, 1.f), BOX4D, this->shaders[WALLD4]));
			generate_door4D(glm::vec4(0.f, 64.f, 0.f, 0.f), glm::vec4(10.f, 3.f, 10.f, 10.f), glm::vec4(0.f), glm::vec2(0.8f, 1.7f), 5, 0, false, 0.f, true, this->wallTexs3D[WOODZ], glm::vec4(1.f, 1.f, 1.f, 1.f), this->shaders[WALLD4], true, this->wallTexs3D[PURE_WHITE], glm::vec4(0.f, 1.f, 1.f, 1.f), this->shaders[WALLD4], false, true, this->wallTexs3D[PURE_WHITE], glm::vec4(0.f, 1.f, 1.f, 1.f), this->shaders[WALLD4], true, this->wallTexs3D[PURE_WHITE], glm::vec4(0.f, 1.f, 1.f, 1.f), this->shaders[WALLD4], &this->walls4D);
			//this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(0.2f, 0.2f, 0.8f, 0.8f) / 2.f), glm::vec4(-5.1f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 0.2f, 0.8f, 0.8f), 1.265f, 0.25f, false, this->wallTexs3D[WOODZ], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));
			//this->walls4D.push_back(new Wall4D("Can-Be-Destroyed", Hypercube(glm::vec4(0.2f, 1.7f, 0.8f, 0.8f) / 2.f), glm::vec4(-5.1f, 64.f + 1.7f/2.f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 1.7f, 0.8f, 0.8f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 0.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Z", Hypercube(glm::vec4(10.4f, 3.2f, 0.2f, 10.f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 5.1f, 0.f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 0.2f, 10.f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("-Z", Hypercube(glm::vec4(10.4f, 3.2f, 0.2f, 10.f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, -5.1f, 0.f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 0.2f, 10.f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 0.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("W", Hypercube(glm::vec4(10.4f, 3.2f, 10.4f, 0.2f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 0.f, 5.1f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 10.4f, 0.2f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("-W", Hypercube(glm::vec4(10.4f, 3.2f, 10.4f, 0.2f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 0.f, -5.1f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 10.4f, 0.2f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Ceil", Hypercube(glm::vec4(10.4f, 0.2f, 10.4f, 10.4f) / 2.f), glm::vec4(0.f, 67.1f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.4f, 0.2f, 10.4f, 10.4f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f), BOX4D, this->shaders[WALLD4]));

			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(-10.3f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.f, 0.2f, 1.f, 1.f), 65.f, 0.f, 1.265f, 0.25f, false, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->rigidBodies4D[this->rigidBodies4D.size() - 1]->animatePosition4D = glm::vec4(-5, 0, 0, 0);
			glm::vec4* positions4D(new glm::vec4[5]);
			float* dt(new float[4]);
			positions4D[0] = glm::vec4(-10.3f, 63.9f, 0.f, 0.f), positions4D[1] = glm::vec4(-10.3f, 66.9f, 0.f, 0.f), positions4D[2] = glm::vec4(-10.3f, 66.9f, 3.f, 0.f), positions4D[3] = glm::vec4(-13.3f, 66.9f, 3.f, 0.f), positions4D[4] = glm::vec4(-10.3f, 63.9f, 0.f, 0.f);
			dt[0] = 1.f, dt[1] = 2.f, dt[2] = 5.f, dt[3] = 4.f;
			this->shifts4D.push_back(new Shift4D(positions4D, dt, 5, 2));
			this->rotates4D.push_back(new Rotate4D(glm::vec4(-10.3f, 63.9f, 0.f, 0.f), glm::vec4(), alg::bivec4(), alg::bivec4(0.f, 1.f, 0.f, 0.f, 0.f, 0.f), false, 2, -1));

			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(-12.3f, 3.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), MESH4D, this->shaders[WALLD4]));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(-12.3f, 3.9f, 2.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), MESH4D, this->shaders[WALLD4]));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(-10.3f, 3.9f, 4.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 1.265f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), SPHERE4D, this->shaders[WALLD4]));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(1.5f, 1.5f, 2.f, 1.5f)), glm::vec4(-8.3f, 3.9f, 4.f, 0.f), alg::bivec4(), glm::vec4(1.5f, 1.5f, 2.f, 1.5f), 1.f, 1.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), CAPSULE4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(2.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(2.f, 0.2f, 1.f, 1.f), 1.265f, 0.25f, false, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.f, 0.f, 1.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(12.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 4.f - 1.f, 63.9f + 12.f / 4.f, 0.f, 0.f), alg::bivec4(-30.f), glm::vec4(12.f, 0.2f, 1.f, 1.f), 1.265f, 0.25f, false, this->wallTexs3D[WHITECONCRETE], 0.f, glm::vec4(0.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(2.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f, 0.f, 0.f), alg::bivec4(), glm::vec4(2.f, 0.2f, 1.f, 1.f), 1.265f, 0.25f, false, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.f, 0.f, 1.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 7.5f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f / 2.f - 0.5f, 0.f), alg::bivec4(), glm::vec4(1.f, 0.2f, 7.5f, 1.f), 1.265f, 0.25f, false, this->wallTexs3D[WHITECONCRETE], 0.f, glm::vec4(0.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 2.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f - 1.5f, 0.f), alg::bivec4(), glm::vec4(1.f, 0.2f, 2.f, 1.f), 1.265f, 0.25f, false, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(0.f, 0.f, 1.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 1.f, 7.5f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f - 2.f, 7.5f / 2.f + 0.5f), alg::bivec4(), glm::vec4(1.f, 0.2f, 1.f, 7.5f), 1.265f, 0.25f, false, this->wallTexs3D[WHITECONCRETE], 0.f, glm::vec4(0.f, 1.f, 0.f, 1.f), BOX4D, this->shaders[WALLD4]));
			this->walls4D.push_back(new Wall4D("Portal", Hypercube(glm::vec4(1.f, 2.f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f+1.1f, -7.5f - 2.f, 7.5f), alg::bivec4(), glm::vec4(1.f, 2.f, 1.f, 1.f), 1.265f, 1.f, true, this->wallTexs3D[STARS], 0.f, glm::vec4(2.f, 2.f, 2.f, 1.f), BOX4D, this->shaders[EMITD4]));

			this->pointLights4D.push_back(new PointLight4D(this->particleTexs3D[PARTICLE1], glm::vec4(0.f, 66.f, 0.f, 0.f), -1, 20.f, glm::vec3(1.f, 1.f, 1.f)));
			this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(0.f, 66.f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.265f, 0.25f, true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 1.f) * 4.f, NONE, this->shaders[EMITD4]));
			this->worldTime = 150.f;
			break;
		}
		}
	}
	else
	{
		load_file(filePath, this->wallTexs3D, this->particleTexs3D, this->shaders, &this->rigidBodies4D, &this->dynamites4D2, &this->walls4D, &this->dynamites4D, &this->terrains4D,&this->waters4D,&this->sticks4D, &this->springs4D, &this->shifts4D, &this->floats4D, &this->rotates4D, &this->hingeConstraints,&this->pointLights4D,&this->worldTime);
	}
}