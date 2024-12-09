#include"Game.h"
void Game::updateObjects()
{
	this->judgetime2 += this->dt;
	if (this->judgetime2 > 1.f)
	{
		update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
		this->judgetime2 = 0.f;
	}
	if (this->isFixedTime)
	{
	    for (Rotate4D* i : this->rotates4D)
	    {
			RigidBody4D* a(this->rigidBodies4D[i->index1]);
	    	if (!i->index2.isValid)
	    	{
	    		i->rotating(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    	}
			else if (i->index2.n<this->rigidBodies4D.size())
			{
				RigidBody4D* b(this->rigidBodies4D[i->index2.n]);
				i->rotating(a, b, fixedUpdate::fixedCurTime, 1.f / 60.f);
			}
	    }
	    for (Shift4D* i : this->shifts4D)
	    {
			RigidBody4D* a(this->rigidBodies4D[i->index]);
	    	i->shifting(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    }
	    for (Float4D* i : this->floats4D)
	    {
			RigidBody4D* a(this->rigidBodies4D[i->index]);
	    	i->floating(a, fixedUpdate::fixedCurTime, 1.f / 60.f);
	    }
	    for (OpenDoor4D* i : this->openDoors4D)
	    {
			RigidBody4D* a(this->rigidBodies4D[i->index]);
	    	i->animate(a, 1.f / 60.f);
	    }
		phy::update_physic4D(this->rigidBodies4D,this->groupIndices, this->groups,this->walls4D,this->terrains4D, this->waters4D,&this->collisionsVec,&this->constraintsVec, this->sticks4D, this->springs4D,this->hingeConstraintsVec, 1 / 60.f);
		for (Rotate4D* i : this->rotates4D)
		{
			RigidBody4D* a(this->rigidBodies4D[i->index1]);
			a->set_position4D(i->position4DAfter);
			a->set_rotation4D(i->rotation4DAfter);
			a->pPosition4D = a->position4D;
		}
		for (Shift4D* i : this->shifts4D)
		{
			RigidBody4D* a(this->rigidBodies4D[i->index]);
			a->set_position4D(i->position4DAfter);
			a->pPosition4D = a->position4D;
		}
		for (Float4D* i : this->floats4D)
		{
			RigidBody4D* a(this->rigidBodies4D[i->index]);
			a->set_position4D(i->position4DAfter);
			a->pPosition4D = a->position4D;
		}
		for (OpenDoor4D* i : this->openDoors4D)
		{
			RigidBody4D* a(this->rigidBodies4D[i->index]);
			a->set_position4D(i->position4DAfter);
			a->set_rotation4D(i->rotation4DAfter);
			a->pPosition4D = a->position4D;
		}
	}
}

void Game::updateCollider() 
{
	if (this->isFixedTime)
	{
		this->camera.isGround = false;
		if (this->collisionsVec.size()>0)
		{
			for (Collision collision : this->collisionsVec[0])
			{
				if (collision.index1 == 0)
				{
					if (collision.collisionManifold.normal.y < -0.5f)
					{
						this->camera.isGround = true;
						this->rigidBodies4D[0]->isGravity = true;
					}
					if(collision.index2 > -1)
					if (find_object4d(this->rigidBodies4D, this->walls4D, collision.index2)->objectName == "Portal")
					{
						this->startLevel(this->level += 1, "");
						snprintf(levelText, 255, "Level %i", this->level);
						break;
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
				Object4D* o(find_dynamite4d(this->rigidBodies4D, this->walls4D, d));
				for (size_t j(0); j < this->rigidBodies4D.size(); j++)
				{
					if (length(this->rigidBodies4D[j]->position4D - o->position4D) < 10.f)
					{
						float distance(length(this->rigidBodies4D[j]->position4D - o->position4D));
						this->rigidBodies4D[j]->forceSystems4D.push_back(new ForceSystem4D(3000.f * normalize(this->rigidBodies4D[j]->position4D - o->position4D) / (distance * distance), glm::vec4(0.f)));
						if (this->rigidBodies4D[j]->objectName == "Can-Be-Destroyed" || this->rigidBodies4D[j]->objectName == "Glass4D")
						{
							delete_object4d(&this->rigidBodies4D, &this->walls4D, &this->groupIndices, this->groups, this->camera.position4D, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, &this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D, j);
							j--;
						}
					}
				}
				for (DynamiteIndex* d2 : this->dynamiteIndices)
				{
					Object4D* o2(find_dynamite4d(this->rigidBodies4D, this->walls4D, d2));
					if (length(o2->position4D - o->position4D) < 3.f)
					{
						d2->isExploding = true;
					}
				}
				
				for (size_t j(0); j < this->walls4D.size(); j++)
				{
					if (this->walls4D[j]->objectName == "Can-Be-Destroyed" || this->walls4D[j]->objectName == "Glass4D")
					{
						if (length(this->walls4D[j]->position4D - o->position4D) < 3.f)
						{
							delete_object4d(&this->rigidBodies4D, &this->walls4D, &this->groupIndices, this->groups, this->camera.position4D, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, &this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D, j + this->rigidBodies4D.size());
							j--;
						}
					}
				}
				delete_object4d(&this->rigidBodies4D, &this->walls4D, &this->groupIndices, this->groups, this->camera.position4D, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, &this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D, d->index);
				i--;
				this->sounds[rand() % 4]->play(length(this->camera.position4D - o->position4D), this->soundVolume);
				this->emitters4D.push_back(new Emitter4D(0, o->position4D, glm::vec4(0.f), 10.f));
            }
		}
	}
}

void Game::updateParticles()
{
	if (this->isFixedTime)
	{
		for (size_t i(0); i < this->emitters4D.size(); i++) {
			//Emitter
			if (this->emitters4D[i]->type == 0)
			{
				float emitTime00(0.f);
				unsigned int emitCount00(20);
				if (emitTime00 / (float)emitCount00 >= 1.f / 60.f)
				{
					if ((this->emitters4D[i]->emitTime >= emitTime00 / (float)(emitCount00 - 1) && this->emitters4D[i]->time <= emitTime00) ||
						this->emitters4D[i]->time == 0.f)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE2, this->emitters4D[i]->position4D, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 0.f, 0.f, 0.5f, 1.f, 1, 0));
						this->emitters4D[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4D[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->position4D, this->emitters4D[i]->velocity4D / 10.f + (float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 0.5f, 1.f, 0.9f, 0.4f, 1, 0));
						}
					}
				}

				if (this->emitters4D[i]->time == 0.f)
				{
					for (int k(0); k < 6; k++)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->position4D + (float)(rand() % 3 + 5) / 15.5f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4D[i]->velocity4D / 30.f + (float)(rand() % 3 + 5) / 6.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), 3.25f / 4.35f, 5.375f / 4.35f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, (float)(rand() % 100) / 50.f + 1.5f, 0.f, 0.f, 4.f, 1, 1));
					}
					for (int k(0); k < 4; k++)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->position4D + (float)(rand() % 3 + 5) / 35.f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4D[i]->velocity4D / 30.f + (float)(rand() % 3 + 5) / 10.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), ((float)(rand() % 100) / 50.f + 3.f) / 5.75f, ((float)(rand() % 100) / 50.f + 4.f) / 5.5f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, (float)(rand() % 100) / 50.f + 8.f, 0.f, 0.f, 1.f, 1, 2));
					}
				}
				//
				//Particles
				unsigned int emitCount1(9);
				unsigned int emitCount2(2);
				float timeShift(0.f);
				for (size_t j(0); j < this->emitters4D[i]->particles4D.size(); j++) {

					if (this->emitters4D[i]->particles4D[j]->level == 1 && this->emitters4D[i]->particles4D[j]->index == 0)
					{
						if (this->emitters4D[i]->particles4D[j]->emitTime >= this->emitters4D[i]->particles4D[j]->duration / (float)emitCount1)
						{
							//std::cout << "emit" << "\n";

								//std::cout << "emit particle 2: "<< "\n";
							this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->particles4D[j]->position4D+0.2f*normalize(glm::vec4(rand()%100-50, rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50)), this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4D[i]->particles4D[j]->retention), 0.8f / 5.f, 1.2f / 3.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.0f, 0.24f, 0.1f, 1.f, 2, 0));
							this->emitters4D[i]->particles4D[j]->emitTime = 0.f;
						}
					}

					if (this->emitters4D[i]->particles4D[j]->level == 2 && this->emitters4D[i]->particles4D[j]->index == 0)
					{

						if (this->emitters4D[i]->particles4D[j]->emitTime >= this->emitters4D[i]->particles4D[j]->duration / (float)emitCount2 * timeShift)
						{
							timeShift = ((float)(rand() % 100) / 100.f + 0.5f);
							this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->particles4D[j]->position4D, this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4D[i]->particles4D[j]->retention), ((float)(rand() % 100) / 150.f + 0.8f - 0.5f) / 3.f, ((float)(rand() % 100) / 150.f + 1.2f - 0.5f) / 3.f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, (float)(rand() % 100) / 50.f + 4.f, 0.f, 0.f, 1.f, 3, 0));
							this->emitters4D[i]->particles4D[j]->emitTime = 0.f;
						}
					}
				}
				//
			}
			if (this->emitters4D[i]->type == 1)
			{
				float emitTime00(0.f);
				unsigned int emitCount00(4);
				if (emitTime00 / (float)emitCount00 >= 1.f / 60.f)
				{
					if ((this->emitters4D[i]->emitTime >= emitTime00 / (float)(emitCount00 - 1) && this->emitters4D[i]->time <= emitTime00) ||
						this->emitters4D[i]->time == 0.f)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE2, this->emitters4D[i]->position4D, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.f, 1.f, 0.5f, 1.f, 1, 0));
						this->emitters4D[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4D[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->position4D, this->emitters4D[i]->velocity4D / 10.f + 0.5f*(float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, 3.f/18.f, 1.f, 0.5f, 0.4f, 1, 0));
						}
					}
				}
				//
				//Particles
				unsigned int emitCount1(3);
				for (size_t j(0); j < this->emitters4D[i]->particles4D.size(); j++) {
					if (this->emitters4D[i]->particles4D[j]->level == 1 && this->emitters4D[i]->particles4D[j]->index == 0)
					{
						if (this->emitters4D[i]->particles4D[j]->emitTime >= this->emitters4D[i]->particles4D[j]->duration / (float)emitCount1)
						{
							//std::cout << "emit" << "\n";

								//std::cout << "emit particle 2: "<< "\n";
							this->emitters4D[i]->particles4D.push_back(new Particle4D0(PARTICLE3, this->emitters4D[i]->particles4D[j]->position4D, this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4D[i]->particles4D[j]->retention), 0.8f / 5.f, 1.2f / 3.f, glm::vec4(0.35f, 0.35f, 0.35f, 0.75f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, 5.f/6.f, 0.24f, 0.1f, 1.f, 2, 0));
							this->emitters4D[i]->particles4D[j]->emitTime = 0.f;
						}
					}
				}
				//
			}
			this->emitters4D[i]->time += 1.f / 60.f;
			this->emitters4D[i]->emitTime += 1.f / 60.f;
			if (this->emitters4D[i]->time > this->emitters4D[i]->duration)
			{
				this->emitters4D.erase(this->emitters4D.begin() + i);
			}
			for (size_t j(0); j < this->emitters4D[i]->particles4D.size(); j++) 
			{
				this->emitters4D[i]->particles4D[j]->velocity4D += (
					glm::vec4(0.f, -9.8f, 0.f, 0.f) * this->emitters4D[i]->particles4D[j]->gravity -
					this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->friction) * 1.f / 60.f;
				this->emitters4D[i]->particles4D[j]->set_position4D(this->emitters4D[i]->particles4D[j]->position4D + this->emitters4D[i]->particles4D[j]->velocity4D * 1.f / 60.f);
				this->emitters4D[i]->particles4D[j]->time += 1.f / 60.f;
				this->emitters4D[i]->particles4D[j]->emitTime += 1.f / 60.f;
				if (this->emitters4D[i]->particles4D[j]->time > this->emitters4D[i]->particles4D[j]->duration)
				{
					this->emitters4D[i]->particles4D.erase(this->emitters4D[i]->particles4D.begin() + j);
				}
			}
		}
	}
}