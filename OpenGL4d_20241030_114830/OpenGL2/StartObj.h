#include"Game.h"
#include"Structures4D.h"

void Game::startObjects(int level,const char* filePath)
{
	this->camera.fit_direction(3);
	this->exposure = 0.25f;
	cameraDirText = 'W';
	if (filePath == "")
	{
		switch (level)
		{
		case 1:
		{
			this->skybox4D->switch_mode(0, this->wallTexs3D[CHESSBOARD], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.95f, 64.15f, 0.f, 0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, PURE_RED_GREEN, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.25f),SPHERE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.05f, 64.15f, 0.f, 0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, PURE_RED_GREEN, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.25f),SPHERE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.95f, 64.15f, 0.f, -0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, PURE_RED_GREEN, glm::vec4(1.f),glm::vec4(1.f, 1.f, 1.f, 0.25f), SPHERE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(3.05f, 64.15f, 0.f, -0.45f), alg::bivec4(), glm::vec4(0.5f), 1.265f, 0.f, true, PURE_RED_GREEN, glm::vec4(1.f),glm::vec4(1.f, 1.f, 1.f, 0.25f), SPHERE4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.5f, 1.f, 6.f, 1.5f) / 2.f), glm::vec4(3.5f, 64.5f, 0.5f, 0.f), alg::bivec4(), glm::vec4(1.5f, 0.2f, 6.f, 1.5f), 50.f, 150.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WOODY, glm::vec4(1.f), glm::vec4(0.f), BOX4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 65.65f, 2.f, 0.f), alg::bivec4(), glm::vec4(0.5f), 100.f, 33.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_RED, glm::vec4(1.f), glm::vec4(0.f), BOX4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 67.65f, -1.25f, 0.f), alg::bivec4(), glm::vec4(0.5f), 150.f, 50.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WHITECONCRETE, glm::vec4(1.f),glm::vec4(1.f, 1.f, 1.f, 0.5f), BOX4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f) / 2.f), glm::vec4(3.5f, 67.65f, -1.75f, 0.f), alg::bivec4(), glm::vec4(0.5f), 150.f, 50.f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WHITECONCRETE, glm::vec4(1.f),glm::vec4(1.f, 1.f, 1.f, 0.5f), BOX4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(1.f) / 2.f), glm::vec4(10.f, 64.5f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 100.f, 66.7f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f), glm::vec4(0.f), MESH4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(1.f) / 2.f), glm::vec4(12.f, 64.5f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 100.f, 66.7f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f), glm::vec4(0.f), MESH4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(1.f) / 2.f), glm::vec4(11.f, 65.2f, 0.f, 0.f), alg::bivec4(), glm::vec4(3.f,0.2f,1.f,1.f), 60.f, 166.7f, 1.265f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f), glm::vec4(0.f), BOX4D, WALLD4));
			//hs.push_back(HingeConstraint4D(glm::vec4(), glm::vec4(0.f, -0.7f, 0.f, 0.f), glm::vec4(0.f), this->rigidBodies4D.size() - 1, this->rigidBodies4D.size() - 3));
			this->hingeConstraintsVec.push_back({
			new HingeConstraint4D(glm::vec4(), glm::vec4(-1.f, -0.7f, 0.5f, 0.5f), glm::vec4(0.f, 0.f, 0.5f, 0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 3,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(-1.f, -0.7f, 0.5f, -0.5f), glm::vec4(0.f, 0.f, 0.5f, -0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 3,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(-1.f, -0.7f, -0.5f, 0.5f), glm::vec4(0.f, 0.f, -0.5f, 0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 3,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(-1.f, -0.7f, -0.5f, -0.5f), glm::vec4(0.f, 0.f, -0.5f, -0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 3,true)) });
			this->hingeConstraintsVec.push_back({
			new HingeConstraint4D(glm::vec4(), glm::vec4(1.f, -0.7f, 0.5f, 0.5f), glm::vec4(0.f, 0.f, 0.5f, 0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 2,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(1.f, -0.7f, 0.5f, -0.5f), glm::vec4(0.f, 0.f, 0.5f, -0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 2,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(1.f, -0.7f, -0.5f, 0.5f), glm::vec4(0.f, 0.f, -0.5f, 0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 2,true)),
			new HingeConstraint4D(glm::vec4(), glm::vec4(1.f, -0.7f, -0.5f, -0.5f), glm::vec4(0.f, 0.f, -0.5f, -0.5f), this->rigidBodies4D.size() - 1, new VectorIndex(this->rigidBodies4D.size() - 2,true)) });
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(), glm::vec4(3.5f, 66.85f, -1.25f, -0.25f), alg::bivec4(), glm::vec4(0.5f), 1.f, 1.f, 1.265f, 0.f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WHITECONCRETE, 0.5f, glm::vec4(1.f), BOX4D, true, WALLD4));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(), glm::vec4(3.5f, 66.85f, -1.75f, -0.25f), alg::bivec4(), glm::vec4(0.5f), 1.f, 1.f, 1.265f, 0.f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WHITECONCRETE, 0.5f, glm::vec4(1.f), SPHERE4D, true, WALLD4));
			this->walls4D.push_back(new Wall4D("Portal", Hypersphere(glm::vec4(1.f) / 2.f), glm::vec4(-2.f, 64.8f, -2.f, 0.f), alg::bivec4(), glm::vec4(1.f), 0.7f, 1.f, true, PURE_BLACK, glm::vec4(2.f, 2.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), SPHERE4D, EMITD4));
			generate_room4D(glm::vec4(0.f, 64.f, 0.f, 0.f), glm::vec4(12, 7, 16, 12), 0, 0, 0, 0, 0, 0, true, true, CHESSBOARD, glm::vec4(1), WALLD4, true, GROUND, glm::vec4(0.f, 0.f, 0.f, 0.5f), WALLD4, false, STARS, glm::vec4(1), WALLD4, true, CEIL2, glm::vec4(1), WALLD4, &this->walls4D);
			this->walls4D.push_back(new Wall4D("Hypersphere", Hyperspherecol(glm::vec4(2.f)), glm::vec4(0.f, 65.f, 0.f, 0.f), alg::bivec4(), glm::vec4(40.f), 1.265f, 0.f, false, STARS_SKY, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.25f), NONE, EMITD4));
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(10000.f, 17.f, 10000.f, 10000.f) / 2.f), glm::vec4(0.f, 55.8f, 0.f, 0.f), alg::bivec4(), glm::vec4(10000.f, 16.f, 10000.f, 10000.f), 0.7f, 0.25f, false, GRASS, glm::vec4(1.f), glm::vec4(0.f), BOX4D, WALLD4));

			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(1.f, 70.5f, 0.f, 0),new VectorIndex(0.f,false), this->pointLights4D.size(), 50.f, glm::vec3(0.2f, 0.54f, 0.77f)));
			for (int i = 0; i < 256; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(10*i, 66.f, 0, 0),new VectorIndex(0.f,false), this->pointLights4D.size(), 2.f, glm::vec3(rand() % 256, rand() % 256, rand() % 256)/256.f,5.f));
				}
			}
			//this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(), glm::vec4(1.f, 66.f, 1.f, 2.f), alg::bivec4(), glm::vec4(0.2f), 1.265f, 0.25f, true, PURE_WHITE, 0.f, glm::vec3(0.2f, 0.54f, 0.77f) * 4.f, NONE, EMITD4));
			this->directionLight4D->type = EARTH;
			this->worldTime = 150.f;
			break;
		}
		case 2:
		{
			this->skybox4D->switch_mode(0, this->wallTexs3D[CHESSBOARD], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f),glm::vec4(1.f,1.f,1.f,0.f), CAPSULE4D, WALLD4));
			generate_room4D(glm::vec4(0.f, 64.f, 0.f, 5.f), glm::vec4(24, 6, 16, 24), 4, 0, 0, 0, 0, 0, true, true, WHITECONCRETE, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1), WALLD4, false, CEIL2, glm::vec4(1), WALLD4, &this->walls4D);
			generate_door4D(glm::vec4(0.f, 64, 0, 5.f), glm::vec4(24, 6, 16, 24), glm::vec4(0, 0, 0, 0), glm::vec2(0.8f, 1.9f), 4, 1, true, 0.f, true, WHITECONCRETE, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(1.f), WALLD4, true, true, WOODY, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);
			generate_door4D(glm::vec4(0.f, 64.f, 0.f, 5.f), glm::vec4(24, 6, 16, 24), glm::vec4(0, 0, 0, 0), glm::vec2(0.5f, 1.7f), 4, 0, true, 0.f, true, WHITECONCRETE, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(1.f), WALLD4, true, true, WOODY, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);
			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f, 1.7f, 0.5f, 0.05f) / 2.f), glm::vec4(0.f, 64.85f, 0.f, 17.025f), alg::bivec4(), glm::vec4(0.5f, 1.7f, 0.5f, 0.05f), 0.f, 0.f, 0.7f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WOODY, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->rigidBodies4D[this->rigidBodies4D.size() - 1]->animatePosition4D = glm::vec4(0.f, 0.f, 0.25f, -0.025f);
			this->openDoors4D.push_back(new OpenDoor4D(glm::vec4(0.f, 64.85f, 0.25f, 17.05f),0.75f,0.f,alg::bivec4(0.f,0.f,0.f,0.f,0.f,90.f),alg::rotor4(), 0, this->rigidBodies4D.size() - 1));
			generate_walkway4D(glm::vec4(0, 64.f, 0, 17.55f), glm::vec4(0.825f, 3.f, 0.825f, 0.9f), 4, true, true, STARS, glm::vec4(1.f), WALLD4, true, STARS, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, true, STARS, glm::vec4(1.f), WALLD4, false, CEIL2, glm::vec4(1.f), WALLD4, &this->walls4D);
			generate_room4D(glm::vec4(0, 64.f, 0, 18.5), glm::vec4(1, 3, 1, 1), 1, 8, 0, 0, 0, 0, true, true, STARS, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(0.f,0.f,0.f,1.f), WALLD4, true, STARS, glm::vec4(1), WALLD4, false, CEIL2, glm::vec4(1), WALLD4, &this->walls4D);
			generate_walkway4D(glm::vec4(1.95f, 64.f, 0, 18.5f), glm::vec4(2.9f, 3.f, 0.825f, 0.825f), 1, true, true, STARS, glm::vec4(1.f), WALLD4, true, STARS, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, true, STARS, glm::vec4(1.f), WALLD4, false, CEIL2, glm::vec4(1.f), WALLD4, &this->walls4D);

			generate_door4D(glm::vec4(13.5f, 64.f, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(0, 0, 0, -6), glm::vec2(0.8f, 1.9f), 5, 0, true, 0.f, true, GROUND, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(1.f), WALLD4, true, true, STARS, glm::vec4(1.f), EMITD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);
			generate_room4D(glm::vec4(13.5f, 64.f, 0, 24.5f), glm::vec4(20, 6, 15, 14), 5, 3, 0, 0, 0, 0, true, true, GROUND, glm::vec4(1), WALLD4, true, GROUND, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1), WALLD4, false, CEIL2, glm::vec4(1), WALLD4, &this->walls4D);
			generate_floor4D(glm::vec4(13.5f, 67.f, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(2, 0, 0.75f, 1), glm::vec4(1, 0, 3.5f, 1), true, false, CEIL2, glm::vec4(1.f), WALLD4, true, GROUND, glm::vec4(1.f), WALLD4, false, GROUND, glm::vec4(1.f), WALLD4, &this->walls4D);
			generate_door4D(glm::vec4(13.5f, 64.f, 0, 24.5f), glm::vec4(20, 6, 15, 14), glm::vec4(0, 0, 0, 4), glm::vec2(0.8f, 1.9f), 3, 0, true, 0.f, true, GROUND, glm::vec4(1), WALLD4, true, PURE_WHITE, glm::vec4(1.f), WALLD4, true, true, STARS, glm::vec4(1.f), EMITD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);

			generate_table4D(glm::vec4(13.5f + 2 - 10 - 0.7, 64, 0, 24.5f - 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, C1, true, PURE_WHITE, &this->walls4D, WALLD4);
			generate_table4D(glm::vec4(13.5f + 2 - 10 - 0.7, 64, 0, 24.5f), glm::vec4(1, 1.2f, 3, 2), 1.f, true, C1, true, PURE_WHITE, &this->walls4D, WALLD4);
			for (int i = 0; i < 5; i++) {
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f), glm::vec4(1, 1.2f, 3, 2), 1.f, true, PURE_BLUE, true, PURE_WHITE, &this->walls4D, WALLD4);
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f - 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, PURE_BLUE, true, PURE_WHITE, &this->walls4D, WALLD4);
				generate_table4D(glm::vec4(13.5f + 10 - 1 - i * 4, 64, 0, 24.5f + 4), glm::vec4(1, 1.2f, 3, 2), 1.f, true, PURE_BLUE, true, PURE_WHITE, &this->walls4D, WALLD4);
			}
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, -3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, YELLOWMARBLE, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, -3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, STARS, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, 3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C1, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, 3, 24.5f - 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C2, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, -3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C3, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, -3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C4, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f + 3, 67, 3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C5, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(1, 6, 1, 1) / 2.f), glm::vec4(13.5f - 3, 67, 3, 24.5f + 3), alg::bivec4(), glm::vec4(1, 6, 1, 1), 0.7f, 0.25f, true, MARBLE_C2, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));

			generate_steps4D(glm::vec4(15.5f, 64.f, 3.f, 25.5f), glm::vec4(15.5f, 67.1f, -1.f, 25.5f), glm::vec4(1, 3.1f / 20.f, 0.6f, 1), 7, 20, false, PURE_WHITE, &this->walls4D, WALLD4);
			this->walls4D.push_back(new Wall4D("Pentatope", Pentachoron(glm::vec4(2) / 2.f), glm::vec4(11.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 0.7f, 0.25f, true, MARBLE_C1, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), MESH4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(2) / 2.f), glm::vec4(13.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 0.7f, 0.25f, true, MARBLE_C1, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), MESH4D, WALLD4));
			this->walls4D.push_back(new Wall4D("TriPrism", TriPrism(glm::vec4(2) / 2.f), glm::vec4(15.5f, 68.1f, 3, 24.5), alg::bivec4(), glm::vec4(2), 0.7f, 0.25f, true, MARBLE_C1, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), MESH4D, WALLD4));

			this->walls4D.push_back(new Wall4D("Portal", Hypersphere(glm::vec4(1.f) / 2.f), glm::vec4(13.5f, 65.6f, 24, 42.5f), alg::bivec4(), glm::vec4(1.f), 0.7f, 1.f, true, PURE_BLACK, glm::vec4(2.f, 2.f, 2.f, 1.f),glm::vec4(1.f,1.f,1.f,0.f), SPHERE4D, EMITD4));
			this->walls4D.push_back(new Wall4D("Portal", Hypersphere(glm::vec4(1.f) / 2.f), glm::vec4(13.5f, 65.6f, 24, 19.5f), alg::bivec4(), glm::vec4(1.f), 0.7f, 1.f, true, PURE_BLACK, glm::vec4(2.f, 2.f, 2.f, 1.f),glm::vec4(1.f,1.f,1.f,0.f), SPHERE4D, EMITD4));
			generate_door4D(glm::vec4(5.4f, 64, 0, 24.5f), glm::vec4(20, 3, 15, 14), glm::vec4(0, 0, 0, 4), glm::vec2(0.8f, 1.9f), 1, 1, true, 0.f, true, GROUND, glm::vec4(1), WALLD4, true, GROUND, glm::vec4(1.f), WALLD4, true, true, GLASS, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);
			generate_walkway4D(glm::vec4(13.5f, 64.1f, 15.05, 28.5f), glm::vec4(3.f, 3.f, 14.9f, 3.f), 3, true, true, CHESSBOARDMARBLE, glm::vec4(1.f), WALLD4, false, GRASS, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, false, CEIL2, glm::vec4(1.f), WALLD4, &this->walls4D);
			//generate_walkway4D(glm::vec4(13.5f, 64.1f, 24, 38.75f), glm::vec4(3.f, 3.f, 3.f, 17.5f), 4, true, false, GRASS, glm::vec4(1.f), WALLD4, false, GRASS, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, true, GLASS, glm::vec4(1.f), WALLD4, &this->walls4D);
			//this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(3, 0.2f, 3, 3) / 2.f), glm::vec4(13.5f, 63.9, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(3, 0.2f, 3, 3), 0.7f, 0.25f, false, WHITEWALL, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			//this->walls4D.push_back(new Wall4D("Glass4D", Hypercube(glm::vec4(3.f, 0.2f, 3.f, 3.f) / 2.f), glm::vec4(13.5f, 67.2, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(3, 0.2f, 3, 3), 0.7f, 0.25f, true, GLASS, glm::vec4(1.f), glm::vec4(1.f,1.f,1.f,0.75f), BOX4D, WALLD4));
			//this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(3, 3.2f, 0.2f, 3) / 2.f), glm::vec4(13.5f, 65.5f, 15 + 7.5f + 3.1, 28.5f), alg::bivec4(), glm::vec4(3, 3.2f, 0.2f, 3), 0.7f, 0.25f, false, WHITEWALL, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			//this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, 3.2f, 3, 3) / 2.f), glm::vec4(13.5f + 3 / 2 + 0.6f, 65.5f, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 3, 3), 0.7f, 0.25f, false, WHITEWALL, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			//this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, 3.2f, 3, 3) / 2.f), glm::vec4(13.5f - 3 / 2 - 0.6f, 65.5f, 15 + 7.5f + 3 / 2 + 0.5f, 28.5f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 3, 3), 0.7f, 0.25f, false, WHITEWALL, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));
			//generate_walkway4D(glm::vec4(13.5f, 64.1f, 24, 23.25f), glm::vec4(3, 3, 3, 7.5f), 4, true, false, GRASS, glm::vec4(1.f), WALLD4, false, GRASS, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, true, GLASS, glm::vec4(1.f), WALLD4, &this->walls4D);
			this->walls4D.push_back(new Wall4D("Ground", Hypercube(glm::vec4(1000.f, 17.f, 1000.f, 1000.f) / 2.f), glm::vec4(0, 55.8f, 0, 0), alg::bivec4(), glm::vec4(1000.f, 16.f, 1000.f, 1000.f), 0.7f, 0.25f, false, GRASS, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, WALLD4));

			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(1.f, 66.f, 1.f, 2.f),new VectorIndex(0.f,false), this->pointLights4D.size(), 50.f, glm::vec3(0.2f, 0.54f, 0.77f)));
			this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.2f)), glm::vec4(1.f, 66.f, 1.f, 2.f), alg::bivec4(), glm::vec4(0.2f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(0.2f, 0.54f, 0.77f, 1.f) * 4.f, glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(4.f, 66, 0, 19.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 20.f, glm::vec3(0.2f, 0.5f, 0.2f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 0, 24.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 5.f, glm::vec3(0.8f, 0.1f, 0.1f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 70, 0, 24.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 5.f, glm::vec3(0.4f, 0.1f, 1.f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 15 - 9.f, 28.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 15, 28.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 15 + 9.f, 28.5f),new VectorIndex(0.f,false), this->pointLights4D.size(), 20.0f, glm::vec3(0.4f, 0.6f, 0.8f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 15 + 7.5f + 3 / 2, 28.5f - 5),new VectorIndex(0.f,false), this->pointLights4D.size(), 10.f, glm::vec3(0.8f, 0.4f, 0.4f)));
			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(13.5f, 66, 15 + 7.5f + 3 / 2, 28.5f + 10),new VectorIndex(0.f,false), this->pointLights4D.size(), 16.f, glm::vec3(0.8f, 0.7f, 0.4f)));
			this->directionLight4D->type = EARTH;
			this->worldTime = 150.f;
			break;
		}
		case 3:
		{
			this->skybox4D->switch_mode(0, this->wallTexs3D[STARS], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Glass4D", Hypersphere(glm::vec4(0.5f)), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f + 6.f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.5f), 0.7f, 1.f, true, PURE_HARFRED_GREEN, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), SPHERE4D, WALLD4));
			this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(1.f)), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f + 6.f, 5.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1000.f, 500.f, 0.7f, 1.f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, WHITECONCRETE, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.25f), SPHERE4D, WALLD4));
			this->sticks4D.push_back(new Stick4D(glm::vec4(0.f), 1, new VectorIndex(3,true), 5.f, WHITECONCRETE, glm::vec4(1.f), WALLD4));

			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(10.f, 0.2f, 10.f, 10.f) / 2.f), glm::vec4(0.f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.f, 0.2f, 10.f, 10.f), 0.7f, 0.25f, true, WOODZ, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("X", Hypercube(glm::vec4(0.2f, 3.2f, 10.f, 10.f) / 2.f), glm::vec4(5.1f, 64.f + 1.4f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 3.2f, 10.f, 10.f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			generate_door4D(glm::vec4(0.f, 64.f, 0.f, 0.f), glm::vec4(10.f, 3.f, 10.f, 10.f), glm::vec4(0.f), glm::vec2(0.8f, 1.7f), 5, 0, false, 0.f, true, WOODZ, glm::vec4(1.f, 1.f, 1.f, 1.f), WALLD4, true, PURE_WHITE, glm::vec4(0.f, 1.f, 1.f, 1.f), WALLD4, false, true, PURE_WHITE, glm::vec4(0.f, 1.f, 1.f, 1.f), WALLD4, true, PURE_WHITE, glm::vec4(0.f, 1.f, 1.f, 1.f), WALLD4, &this->walls4D);
			//this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(0.2f, 0.2f, 0.8f, 0.8f) / 2.f), glm::vec4(-5.1f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 0.2f, 0.8f, 0.8f), 0.7f, 0.25f, false, WOODZ, 0.f, glm::vec4(1.f), BOX4D, WALLD4));
			//this->walls4D.push_back(new Wall4D("Can-Be-Destroyed", Hypercube(glm::vec4(0.2f, 1.7f, 0.8f, 0.8f) / 2.f), glm::vec4(-5.1f, 64.f + 1.7f/2.f, 0.f, 0.f), alg::bivec4(), glm::vec4(0.2f, 1.7f, 0.8f, 0.8f), 0.7f, 0.25f, true, PURE_WHITE, 0.f, glm::vec4(1.f, 0.f, 0.f, 1.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Z", Hypercube(glm::vec4(10.4f, 3.2f, 0.2f, 10.f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 5.1f, 0.f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 0.2f, 10.f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(1.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("-Z", Hypercube(glm::vec4(10.4f, 3.2f, 0.2f, 10.f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, -5.1f, 0.f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 0.2f, 10.f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("W", Hypercube(glm::vec4(10.4f, 3.2f, 10.4f, 0.2f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 0.f, 5.1f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 10.4f, 0.2f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("-W", Hypercube(glm::vec4(10.4f, 3.2f, 10.4f, 0.2f) / 2.f), glm::vec4(0.f, 64.f + 1.4f, 0.f, -5.1f), alg::bivec4(), glm::vec4(10.4f, 3.2f, 10.4f, 0.2f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Ceil", Hypercube(glm::vec4(10.4f, 0.2f, 10.4f, 10.4f) / 2.f), glm::vec4(0.f, 67.1f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.4f, 0.2f, 10.4f, 10.4f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));

			this->rigidBodies4D.push_back(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(-10.3f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(10.f, 0.2f, 1.f, 1.f), 0.f, 0.f, 0.7f, 0.25f, false, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->rigidBodies4D[2]->animatePosition4D = glm::vec4(-5, 0, 0, 0);
			this->shifts4D.push_back(new Shift4D(new glm::vec4[5] {glm::vec4(-10.3f, 63.9f, 0.f, 0.f), glm::vec4(-10.3f, 66.9f, 0.f, 0.f), glm::vec4(-10.3f, 66.9f, 3.f, 0.f), glm::vec4(-13.3f, 66.9f, 3.f, 0.f), glm::vec4(-10.3f, 63.9f, 0.f, 0.f)}, new float[4] {1.f, 2.f, 5.f, 4.f}, 5, 2));
			this->rotates4D.push_back(new Rotate4D(glm::vec4(-10.3f, 63.9f, 0.f, 0.f), glm::vec4(), alg::bivec4(), alg::bivec4(0.f, 0.f, 0.f, 1.f, 0.f, 0.f), true, 2, new VectorIndex(0,false)));

			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(-12.3f, 3.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 0.7f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), MESH4D, WALLD4));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(-12.3f, 3.9f, 2.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 0.7f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), MESH4D, WALLD4));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(-10.3f, 3.9f, 4.f, 0.f), alg::bivec4(), glm::vec4(1.f), 1.f, 1.f, 0.7f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), SPHERE4D, WALLD4));
			//this->rigidBodies4D.push_back(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(1.5f, 1.5f, 2.f, 1.5f)), glm::vec4(-8.3f, 3.9f, 4.f, 0.f), alg::bivec4(), glm::vec4(1.5f, 1.5f, 2.f, 1.5f), 1.f, 1.f, 0.7f, 0.25f, true, true, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, PURE_WHITE, 0.f, glm::vec4(1.f, 1.f, 0.f, 1.f), CAPSULE4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(2.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f, 63.9f, 0.f, 0.f), alg::bivec4(), glm::vec4(2.f, 0.2f, 1.f, 1.f), 0.7f, 0.25f, false, PURE_WHITE, glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(12.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 4.f - 1.f, 63.9f + 12.f / 4.f, 0.f, 0.f), alg::bivec4(-30.f), glm::vec4(12.f, 0.2f, 1.f, 1.f), 0.7f, 0.25f, false, WHITECONCRETE, glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(2.f, 0.2f, 1.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f, 63.9f + 12.f / 2.f, 0.f, 0.f), alg::bivec4(), glm::vec4(2.f, 0.2f, 1.f, 1.f), 0.7f, 0.25f, false, PURE_WHITE, glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 7.5f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f / 2.f - 0.5f, 0.f), alg::bivec4(), glm::vec4(1.f, 0.2f, 7.5f, 1.f), 0.7f, 0.25f, false, WHITECONCRETE, glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 2.f, 1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f - 1.5f, 0.f), alg::bivec4(), glm::vec4(1.f, 0.2f, 2.f, 1.f), 0.7f, 0.25f, false, PURE_WHITE, glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Floor", Hypercube(glm::vec4(1.f, 0.2f, 1.f, 7.5f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f, -7.5f - 2.f, 7.5f / 2.f + 0.5f), alg::bivec4(), glm::vec4(1.f, 0.2f, 1.f, 7.5f), 0.7f, 0.25f, false, WHITECONCRETE, glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, WALLD4));
			this->walls4D.push_back(new Wall4D("Portal", Hypersphere(glm::vec4(1.f) / 2.f), glm::vec4(-16.5f - sqrt(3.f) * 12.f / 2.f - 2.f - 0.5f, 63.9f + 12.f / 2.f + 1.1f, -7.5f - 2.f, 7.5f), alg::bivec4(), glm::vec4(1.f), 0.7f, 1.f, true, PURE_BLACK, glm::vec4(2.f, 2.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), SPHERE4D, EMITD4));

			this->pointLights4D.push_back(new PointLight4D(PARTICLE1, glm::vec4(0.f, 66.f, 0.f, 0.f), new VectorIndex(0,false), this->pointLights4D.size(), 20.f, glm::vec3(1.f, 1.f, 1.f)));
			this->walls4D.push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(0.f, 66.f, 0.f, 0.f), alg::bivec4(), glm::vec4(1.f), 0.7f, 0.25f, true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f) * 4.f, glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
			this->directionLight4D->type = EARTH;
			this->worldTime = 150.f;
			break;
		}
		case 4:
		{
			this->skybox4D->switch_mode(0, this->wallTexs3D[STARS], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4));
			generate_terrain4D(16, glm::ivec4(16, 0, 16, 16), &this->terrains4D, TERRAIND4);
			this->waters4D.push_back(new Water4D("Water", Quad4d(glm::vec4(10000.f, 40000.f, 10000.f, 10000.f)), glm::vec4(0, 55.5f, 0, 0), glm::vec4(10000.f, 40000.f, 10000.f, 10000.f), NONE, WATERD4));
			this->walls4D.push_back(new Wall4D("WaterFloor", Waterbox4d(glm::vec4(1.f)), glm::vec4(0.f,55.5f,0.f,0.f), alg::bivec4(), glm::vec4(9999.f, 55.5f, 9999.f, 9999.f), 0.7f, 0.25f, false, PURE_WHITE, glm::vec4(0.72f * 0.28, 0.72f * 0.28, 0.72f * 0.28, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
			this->directionLight4D->type = EARTH;
			this->worldTime = 150.f;
			break;
		}
		case 5:
		{
			this->skybox4D->switch_mode(0, this->wallTexs3D[STARS], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->rigidBodies4D.push_back(new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4));
			generate_window4D(glm::vec4(-1.3f, 64.f, 0.f, 0.f), glm::vec4(5.6f, 3.f, 3.f, 3.f), glm::vec4(0.f, 1.5f, 0.f, 0.f), glm::vec2(1.25f, 1.25f), 1, 0, true, 0.f, true, GROUND, glm::vec4(0.f, 0.f, 0.f, 1.f), WALLD4, true, true, PURE_WHITE, glm::vec4(1.f), WALLD4, true, GLASS, glm::vec4(1.f), WALLD4, false, WHITEWALL, glm::vec4(1.f), WALLD4, &this->walls4D);
			this->directionLight4D->type = EARTH;
			this->worldTime = 150.f;
			break;
		}
		case 6:
		{
			this->skybox4D->switch_mode(1, this->wallTexs3D[STARS], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
			this->directionLight4D->type = SPACE;
			this->worldTime = 150.f;
			break;
		}
		}
	}
	else
	{
		this->skybox4D->switch_mode(0, this->wallTexs3D[CHESSBOARD], glm::vec3(1.f), glm::vec4(1.f), this->shaders[this->skybox4D->shaderIndex]);
		load_file(filePath, &this->rigidBodies4D, &this->walls4D, &this->dynamiteIndices, &this->terrains4D,&this->waters4D,&this->sticks4D, &this->springs4D, &this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D, &this->hingeConstraintsVec,&this->pointLights4D,&this->worldTime);
		this->directionLight4D->type = EARTH;
    }
	//for (size_t i(0); i < this->dynamiteIndices.size(); i++){
	//	DynamiteIndex* d(this->dynamiteIndices[i]);
	//	find_object4d(this->rigidBodies4D, this->walls4D, d->index)->componentsVector[DYNAMITE4D].push_back(i);}
	//for (size_t i(0); i < this->sticks4D.size(); i++) { 
	//	Stick4D* s(this->sticks4D[i]); 
	//	if(s->index1!=nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *s->index1)->componentsVector[STICK_JOINT].push_back(i); 
	//	if(s->index2!=nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *s->index2)->componentsVector[STICK_JOINT].push_back(i);
	//}
	//for (size_t i(0); i < this->springs4D.size(); i++) {
	//	Spring4D* s(this->springs4D[i]);
	//	if (s->index1 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *s->index1)->componentsVector[SPRING_JOINT].push_back(i);
	//	if (s->index2 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *s->index2)->componentsVector[SPRING_JOINT].push_back(i);
	//}
	//for (size_t i(0); i < this->hingeConstraintsVec.size(); i++) {
	//	std::vector<HingeConstraint4D*> hs(this->hingeConstraintsVec[i]);
	//	if (hs[0]->index1 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *hs[0]->index1)->componentsVector[HINGE_CONSTRAINT].push_back(i);
	//	if (hs[0]->index2 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *hs[0]->index2)->componentsVector[HINGE_CONSTRAINT].push_back(i);
	//}
	//for (size_t i(0); i < this->pointLights4D.size(); i++) {
	//	PointLight4D* p(this->pointLights4D[i]);
	//	if (p->index != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *p->index)->componentsVector[POINT_LIGHT4D].push_back(i);
	//}
	//for (size_t i(0); i < this->shifts4D.size(); i++) {
	//	Shift4D* s(this->shifts4D[i]);
	//	find_object4d(this->rigidBodies4D, this->walls4D, s->index)->componentsVector[SHIFT4D_ANIMATION].push_back(i);
	//}
	//for (size_t i(0); i < this->floats4D.size(); i++) {
	//	Float4D* f(this->floats4D[i]);
	//	find_object4d(this->rigidBodies4D, this->walls4D, f->index)->componentsVector[FLOAT4D_ANIMATION].push_back(i);
	//}
	//for (size_t i(0); i < this->rotates4D.size(); i++) {
	//	Rotate4D* r(this->rotates4D[i]);
	//	if (r->index1 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *r->index1)->componentsVector[ROTATE4D_ANIMATION].push_back(i);
	//	if (r->index2 != nullptr)find_object4d(this->rigidBodies4D, this->walls4D, *r->index2)->componentsVector[ROTATE4D_ANIMATION].push_back(i);
	//}
	//for (size_t i(0); i < this->openDoors4D.size(); i++) {
	//	OpenDoor4D* o(this->openDoors4D[i]);
	//	find_object4d(this->rigidBodies4D, this->walls4D, o->index)->componentsVector[OPENDOOR4D_ANIMATION].push_back(i);
	//}
	pack_group(&this->groups, &this->walls4D, &this->terrains4D, &this->pointLights4D);
}