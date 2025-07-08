#include"Game.h"
void Game::updateObjects()
{
	this->judgetime2 += this->dt;
	if (this->judgetime2 > 0.5f)
	{
		update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
		this->judgetime2 = 0.f;
	}
	if (this->isFixedTime)
	{
	    for (Rotate4D* i : this->rotates4d)
	    {
			RigidBody4D* a(this->rigidBodies4d[i->index1]);
	    	if (!i->index2.isValid)
	    	{
	    		i->rotating(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    	}
			else if (i->index2.n<this->rigidBodies4d.size())
			{
				RigidBody4D* b(this->rigidBodies4d[i->index2.n]);
				i->rotating(a, b, fixedUpdate::fixedCurTime, 1.f / 60.f);
			}
	    }
	    for (Shift4D* i : this->shifts4d)
	    {
			RigidBody4D* a(this->rigidBodies4d[i->index]);
	    	i->shifting(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    }
	    for (Float4D* i : this->floats4d)
	    {
			RigidBody4D* a(this->rigidBodies4d[i->index]);
	    	i->floating(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    }
	    for (OpenDoor4D* i : this->openDoors4d)
	    {
			RigidBody4D* a(this->rigidBodies4d[i->index]);
	    	i->animate(a, 1.f / 60.f);
	    }
		phy::update_physic4D(this->rigidBodies4d,this->groupIndices, this->groups,this->walls4d,this->terrains4d, this->waters4d,&this->collisionsVec,&this->constraintsVec, this->sticks4d, this->springs4d,this->hingeConstraintsVec, 1 / 60.f);
	}
}

void Game::updateCollider() 
{
	for (Rotate4D* i : this->rotates4d)
	{
		RigidBody4D* a(this->rigidBodies4d[i->index1]);
		a->set_position4D(i->position4DAfter);
		a->set_rotation4D(i->rotation4DAfter);
		a->pPosition4D = a->position4d;
	}
	for (Shift4D* i : this->shifts4d)
	{
		RigidBody4D* a(this->rigidBodies4d[i->index]);
		a->set_position4D(i->position4DAfter);
		a->pPosition4D = a->position4d;
	}
	for (Float4D* i : this->floats4d)
	{
		RigidBody4D* a(this->rigidBodies4d[i->index]);
		a->set_position4D(i->position4DAfter);
		a->pPosition4D = a->position4d;
	}
	for (OpenDoor4D* i : this->openDoors4d)
	{
		RigidBody4D* a(this->rigidBodies4d[i->index]);
		a->set_position4D(i->position4DAfter);
		a->set_rotation4D(i->rotation4DAfter);
		a->pPosition4D = a->position4d;
	}
	if (this->isFixedTime)
	{
		this->camera.isGround = this->camera.isContact = false;
		if (this->collisionsVec.size()>0)
		{
			this->camera.isContact = true;
			for (std::vector<Collision> collisions : this->collisionsVec)
			{
				for (Collision collision : collisions)
				{
					if (collision.index1 == 0)
					{
						if (collision.collisionManifold.normal.y < -0.5f)
						{
							this->camera.isGround = true;
							this->rigidBodies4d[0]->isGravity = true;
						}
						if (collision.index2 > -1)
						{
							Object4D* o(find_object4d(this->rigidBodies4d, this->walls4d, collision.index2));
							if (o->objectName == "Portal")
							{
								this->startLevel(this->level += 1, "");
								snprintf(levelText, 255, "Level %i", this->level);
								//break;
							}
							else if (o->objectName == "Obstacle")
							{
								this->rigidBodies4d[0]->mu = 5.7143f;
								this->pageType = GAMEOVER;
								glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
								glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
								isGroundTextureUI = false, isObjectTextureUI = false, this->editMode = false;
								//snprintf(levelText, 255, "Level %i", this->level);
								//break;
							}
							else if (o->objectName == "Candy")
							{
								delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, collision.index2);
							}
						}
					}
				}
			}
		}
	}
}
void Game::updateDynamites()
{
	if (this->isFixedTime)
	{
		for (size_t i(0); i < this->dynamiteIndices.size();i++) {
			DynamiteIndex* d(this->dynamiteIndices[i]);
			if (d->isExploding)
			{
				Object4D* o(find_dynamite4d(this->rigidBodies4d, this->walls4d, d));
				for (size_t j(0); j < this->rigidBodies4d.size(); j++)
				{
					if (length(this->rigidBodies4d[j]->position4d - o->position4d) < 10.f)
					{
						float distance(length(this->rigidBodies4d[j]->position4d - o->position4d));
						this->rigidBodies4d[j]->forceSystems4D.push_back(new ForceSystem4D(3000.f * normalize(this->rigidBodies4d[j]->position4d - o->position4d) / (distance * distance), glm::vec4(0.f)));
						if (this->rigidBodies4d[j]->objectName == "Can-Be-Destroyed" || this->rigidBodies4d[j]->objectName == "Glass4D")
						{
							delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, j);
							j--;
						}
					}
				}
				for (DynamiteIndex* d2 : this->dynamiteIndices)
				{
					Object4D* o2(find_dynamite4d(this->rigidBodies4d, this->walls4d, d2));
					if (length(o2->position4d - o->position4d) < 3.f)
					{
						d2->isExploding = true;
					}
				}
				
				for (size_t j(0); j < this->walls4d.size(); j++)
				{
					if (this->walls4d[j]->objectName == "Can-Be-Destroyed" || this->walls4d[j]->objectName == "Glass4D")
					{
						if (length(this->walls4d[j]->position4d - o->position4d) < 3.f)
						{
							delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, j + this->rigidBodies4d.size());
							j--;
						}
					}
				}
				delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, d->index);
				i--;
				this->sounds[rand() % 4]->play(length(this->camera.position4d - o->position4d), this->soundVolume);
				this->emitters4d.push_back(new Emitter4D(0, o->position4d, glm::vec4(0.f), 10.f));
            }
		}
	}
}

void Game::updateParticles()
{
	if (this->isFixedTime)
	{
		for (size_t i(0); i < this->emitters4d.size(); i++) {
			//Emitter
			if (this->emitters4d[i]->type == 0)
			{
				float emitTime00(0.f);
				unsigned int emitCount00(20);
				if (emitTime00 / (float)emitCount00 >= 1.f / 60.f)
				{
					if ((this->emitters4d[i]->emitTime >= emitTime00 / (float)(emitCount00 - 1) && this->emitters4d[i]->time <= emitTime00) ||
						this->emitters4d[i]->time == 0.f)
					{
						this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE2, this->emitters4d[i]->position4d, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 0.f, 0.f, 0.5f, 1.f, 1, 0));
						this->emitters4d[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4d[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->position4d, this->emitters4d[i]->velocity4d / 10.f + (float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 0.5f, 1.f, 0.9f, 0.4f, 1, 0));
						}
					}
				}

				if (this->emitters4d[i]->time == 0.f)
				{
					for (int k(0); k < 6; k++)
					{
						this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->position4d + (float)(rand() % 3 + 5) / 15.5f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4d[i]->velocity4d / 30.f + (float)(rand() % 3 + 5) / 6.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), 3.25f / 4.35f, 5.375f / 4.35f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, (float)(rand() % 100) / 50.f + 1.5f, 0.f, 0.f, 4.f, 1, 1));
					}
					for (int k(0); k < 4; k++)
					{
						this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->position4d + (float)(rand() % 3 + 5) / 35.f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4d[i]->velocity4d / 30.f + (float)(rand() % 3 + 5) / 10.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), ((float)(rand() % 100) / 50.f + 3.f) / 5.75f, ((float)(rand() % 100) / 50.f + 4.f) / 5.5f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, (float)(rand() % 100) / 50.f + 8.f, 0.f, 0.f, 1.f, 1, 2));
					}
				}
				//
				//Particles
				unsigned int emitCount1(9);
				unsigned int emitCount2(2);
				float timeShift(0.f);
				for (size_t j(0); j < this->emitters4d[i]->particles4D.size(); j++) {

					if (this->emitters4d[i]->particles4D[j]->level == 1 && this->emitters4d[i]->particles4D[j]->index == 0)
					{
						if (this->emitters4d[i]->particles4D[j]->emitTime >= this->emitters4d[i]->particles4D[j]->duration / (float)emitCount1)
						{
							//std::cout << "emit" << "\n";

								//std::cout << "emit particle 2: "<< "\n";
							this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->particles4D[j]->position4d+0.2f*normalize(glm::vec4(rand()%100-50, rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50)), this->emitters4d[i]->particles4D[j]->velocity4d * this->emitters4d[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4d[i]->particles4D[j]->retention), 0.8f / 5.f, 1.2f / 3.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.0f, 0.24f, 0.1f, 1.f, 2, 0));
							this->emitters4d[i]->particles4D[j]->emitTime = 0.f;
						}
					}

					if (this->emitters4d[i]->particles4D[j]->level == 2 && this->emitters4d[i]->particles4D[j]->index == 0)
					{

						if (this->emitters4d[i]->particles4D[j]->emitTime >= this->emitters4d[i]->particles4D[j]->duration / (float)emitCount2 * timeShift)
						{
							timeShift = ((float)(rand() % 100) / 100.f + 0.5f);
							this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->particles4D[j]->position4d, this->emitters4d[i]->particles4D[j]->velocity4d * this->emitters4d[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4d[i]->particles4D[j]->retention), ((float)(rand() % 100) / 150.f + 0.8f - 0.5f) / 3.f, ((float)(rand() % 100) / 150.f + 1.2f - 0.5f) / 3.f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, (float)(rand() % 100) / 50.f + 4.f, 0.f, 0.f, 1.f, 3, 0));
							this->emitters4d[i]->particles4D[j]->emitTime = 0.f;
						}
					}
				}
				//
			}
			if (this->emitters4d[i]->type == 1)
			{
				float emitTime00(0.f);
				unsigned int emitCount00(4);
				if (emitTime00 / (float)emitCount00 >= 1.f / 60.f)
				{
					if ((this->emitters4d[i]->emitTime >= emitTime00 / (float)(emitCount00 - 1) && this->emitters4d[i]->time <= emitTime00) ||
						this->emitters4d[i]->time == 0.f)
					{
						this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE2, this->emitters4d[i]->position4d, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.f, 1.f, 0.5f, 1.f, 1, 0));
						this->emitters4d[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4d[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->position4d, this->emitters4d[i]->velocity4d / 10.f + 0.5f*(float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, 3.f/18.f, 1.f, 0.5f, 0.4f, 1, 0));
						}
					}
				}
				//
				//Particles
				unsigned int emitCount1(3);
				for (size_t j(0); j < this->emitters4d[i]->particles4D.size(); j++) {
					if (this->emitters4d[i]->particles4D[j]->level == 1 && this->emitters4d[i]->particles4D[j]->index == 0)
					{
						if (this->emitters4d[i]->particles4D[j]->emitTime >= this->emitters4d[i]->particles4D[j]->duration / (float)emitCount1)
						{
							//std::cout << "emit" << "\n";

								//std::cout << "emit particle 2: "<< "\n";
							this->emitters4d[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4d[i]->particles4D[j]->position4d, this->emitters4d[i]->particles4D[j]->velocity4d * this->emitters4d[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4d[i]->particles4D[j]->retention), 0.8f / 5.f, 1.2f / 3.f, glm::vec4(0.35f, 0.35f, 0.35f, 0.75f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, 5.f/6.f, 0.24f, 0.1f, 1.f, 2, 0));
							this->emitters4d[i]->particles4D[j]->emitTime = 0.f;
						}
					}
				}
				//
			}
			this->emitters4d[i]->time += 1.f / 60.f;
			this->emitters4d[i]->emitTime += 1.f / 60.f;
			if (this->emitters4d[i]->time > this->emitters4d[i]->duration)
			{
				this->emitters4d.erase(this->emitters4d.begin() + i);
			}
			for (size_t j(0); j < this->emitters4d[i]->particles4D.size(); j++) 
			{
				this->emitters4d[i]->particles4D[j]->velocity4d += (
					glm::vec4(0.f, -9.8f, 0.f, 0.f) * this->emitters4d[i]->particles4D[j]->gravity -
					this->emitters4d[i]->particles4D[j]->velocity4d * this->emitters4d[i]->particles4D[j]->friction) * 1.f / 60.f;
				this->emitters4d[i]->particles4D[j]->set_position4D(this->emitters4d[i]->particles4D[j]->position4d + this->emitters4d[i]->particles4D[j]->velocity4d * 1.f / 60.f);
				this->emitters4d[i]->particles4D[j]->time += 1.f / 60.f;
				this->emitters4d[i]->particles4D[j]->emitTime += 1.f / 60.f;
				if (this->emitters4d[i]->particles4D[j]->time > this->emitters4d[i]->particles4D[j]->duration)
				{
					this->emitters4d[i]->particles4D.erase(this->emitters4d[i]->particles4D.begin() + j);
				}
			}
		}
	}
}