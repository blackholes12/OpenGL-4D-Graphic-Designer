#include"Game.h"
void Game::updateObjects()
{
	if (this->isFixedTime)
	{
		phy::update_physic4D(this->rigidBodies4D,this->dynamites4D2, this->groups,this->walls4D,this->dynamites4D, this->waters4D,&this->collisions, this->sticks4D, this->springs4D,this->hingeConstraints, 1 / 60.f);
	}
	for (Rotate4D* i : this->rotates4D)
	{
		if (i->index2 == -1)
		{
			i->rotating(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->index1), this->curTime);
		}
	}
	for (Shift4D* i : this->shifts4D)
	{
		i->shifting(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->index), this->curTime);
	}
	for (Float4D* i : this->floats4D)
	{
		i->floating(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->index), this->curTime);
	}
	for (Rotate4D* i : this->rotates4D)
	{
		if (i->index2 != -1)
		{
			i->rotating(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->index1), find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->index2), this->curTime);
		}
	}
}

void Game::updateCollider() 
{
	if (this->isFixedTime)
	{
		this->isGround = false;
		for (Collision collision : this->collisions)
		{
			if (collision.index1 == 0)
			{
				if (collision.collisionManifold.normal.y > 0.5f)
				{
					this->isGround = true;
					this->rigidBodies4D[0]->isGravity = true;
				}
				if (collision.index2>=0)
				if (find_object4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, collision.index2)->objectName == "Portal")
				{
					this->startLevel(this->level+=1, "");
					snprintf(levelText, 255, "Level %i", this->level);
					break;
				}
			}
		}
		this->collisions.clear();
	}
}
void Game::updateDynamites()
{
	if (this->isFixedTime)
	{
		for (size_t i(0); i < size_of_objects4d(this->dynamites4D2, this->dynamites4D); i++) {
			if (find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->objectName == "Exploding Dynamite")
			{
				for (size_t j(0); j < size_of_objects4d(this->rigidBodies4D,this->dynamites4D2); j++)
				{
					if (length(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, j)->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D) < 10.f)
					{
						float distance(length(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, j)->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D));
						find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, j)->forceSystems4D.push_back(new ForceSystem4D(3000.f * normalize(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, j)->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D) / (distance * distance), glm::vec4(0.f)));
					}
				}
				for (size_t j(0); j < size_of_objects4d(this->dynamites4D2, this->dynamites4D); j++)
				{
					if (i != j)
					{
						if (length(find_dynamite4d(this->dynamites4D, this->dynamites4D2, j)->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D) < 3.f)
						{
							find_dynamite4d(this->dynamites4D, this->dynamites4D2, j)->objectName = "Exploding Dynamite";
						}
					}
				}
				for (size_t j(1); j < this->rigidBodies4D.size(); j++)
				{
					if (this->rigidBodies4D[j]->objectName == "Can-Be-Destroyed"||this->rigidBodies4D[j]->objectName == "Glass4D")
					{
						if (length(this->rigidBodies4D[j]->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D) < 3.f)
						{
							erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, j);
							shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, j,-1);
							erase_joint4d(&this->sticks4D, &this->springs4D,&this->hingeConstraints, j);
							shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, j,-1);
							erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], j);
							shift_point_light4d(this->pointLights4D, j, -1);
							this->rigidBodies4D.erase(this->rigidBodies4D.begin()+j);
							update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
						}
					}
				}
				for (unsigned j(0); j < size_of_walls4d(this->groups); j++)
				{
					if (find_wall4d(this->groups,j)->objectName == "Can-Be-Destroyed"|| find_wall4d(this->groups, j)->objectName == "Glass4D")
					{
						if (length(find_wall4d(this->groups, j)->position4D - find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D) < 3.f)
						{
							erase_joint4d(&this->sticks4D, &this->springs4D,&this->hingeConstraints, j + size_of_objects4d(this->rigidBodies4D,this->dynamites4D2));
							shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, j + size_of_objects4d(this->rigidBodies4D, this->dynamites4D2), -1);
							erase_wall4d(this->groups, j);
							update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
						}
					}
				}
				this->emitters4D.push_back(new Emitter4D(0,find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D,glm::vec4(0.f),10.f));
				if (i < this->dynamites4D.size())
				{
					erase_joint4d(&this->sticks4D, &this->springs4D,&this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2,this->groups) + i);
					shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2,this->groups) + i,-1);
				}
				if (i >= this->dynamites4D.size())
				{
					erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, this->rigidBodies4D.size() + i - this->dynamites4D.size());
					shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->rigidBodies4D.size() + i - this->dynamites4D.size(),-1);
					erase_joint4d(&this->sticks4D, &this->springs4D,&this->hingeConstraints, this->rigidBodies4D.size() + i - this->dynamites4D.size());
					shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, this->rigidBodies4D.size() + i - this->dynamites4D.size(),-1);
					erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->rigidBodies4D.size() + i - this->dynamites4D.size());
					shift_point_light4d(this->pointLights4D, this->rigidBodies4D.size() + i - this->dynamites4D.size(), -1);
				}
				this->sounds[rand() % 4]->play(length(this->camera.position4D-find_dynamite4d(this->dynamites4D, this->dynamites4D2, i)->position4D), this->soundVolume);
				erase_dynamite4d(&this->dynamites4D, &this->dynamites4D2, i);
				update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
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
						this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE2], this->emitters4D[i]->position4D, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 1.f, 1.f, 0.5f, 1.f, 1, 0));
						this->emitters4D[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4D[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->position4D, this->emitters4D[i]->velocity4D / 10.f + (float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f), true, 0.5f, 1.f, 0.9f, 0.4f, 1, 0));
						}
					}
				}

				if (this->emitters4D[i]->time == 0.f)
				{
					for (int k(0); k < 6; k++)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->position4D + (float)(rand() % 3 + 5) / 15.5f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4D[i]->velocity4D / 30.f + (float)(rand() % 3 + 5) / 6.35f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), 4.f / 4.35f, 7.f / 4.35f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, (float)(rand() % 100) / 50.f + 1.5f, 0.f, 0.f, 1.f, 1, 1));
					}
					for (int k(0); k < 4; k++)
					{
						this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->position4D + (float)(rand() % 3 + 5) / 17.5f * normalize(glm::vec4(rand() % 100 - 50))
							, this->emitters4D[i]->velocity4D / 30.f + (float)(rand() % 3 + 5) / 10.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 70 + 35, rand() % 100 - 50, rand() % 100 - 50)), ((float)(rand() % 100) / 50.f + 3.f) / 5.5f, ((float)(rand() % 100) / 50.f + 4.f) / 5.5f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, (float)(rand() % 100) / 50.f + 8.f, 0.f, 0.f, 0.5f, 1, 2));
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
							this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->particles4D[j]->position4D+0.2f*normalize(glm::vec4(rand()%100-50, rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50)), this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
								+ glm::vec4(0.f) * (1.f - this->emitters4D[i]->particles4D[j]->retention), 0.8f / 5.f, 1.2f / 3.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.0f, 0.24f, 0.1f, 1.f, 2, 0));
							this->emitters4D[i]->particles4D[j]->emitTime = 0.f;
						}
					}

					if (this->emitters4D[i]->particles4D[j]->level == 2 && this->emitters4D[i]->particles4D[j]->index == 0)
					{

						if (this->emitters4D[i]->particles4D[j]->emitTime >= this->emitters4D[i]->particles4D[j]->duration / (float)emitCount2 * timeShift)
						{
							timeShift = ((float)(rand() % 100) / 100.f + 0.5f);
							this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->particles4D[j]->position4D, this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
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
						this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE2], this->emitters4D[i]->position4D, 8.f * normalize(glm::vec4(rand() % 100 - 50, rand() % 160, rand() % 100 - 50, 0.f)), 1.f, 1.f, glm::vec4(1.f, 0.65f, 0.12f, 1.f), glm::vec4(1.f, 0.65f, 0.12f, 0.f), true, 1.f, 1.f, 0.5f, 1.f, 1, 0));
						this->emitters4D[i]->emitTime = 0.f;
					}
				}
				else
				{
					if (this->emitters4D[i]->time == 0.f)
					{
						for (int k(0); k < emitCount00; k++)
						{
							this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->position4D, this->emitters4D[i]->velocity4D / 10.f + 0.5f*(float)(rand() % 3 + 6) * normalize(glm::vec4(rand() % 100 - 50, rand() % 75 + 30, rand() % 100 - 50, rand() % 100 - 50)), 1.f / 5.f, 1.f / 5.f, glm::vec4(0.35f, 0.35f, 0.35f, 1.f), glm::vec4(0.15f, 0.15f, 0.15f, 0.f), false, 3.f/18.f, 1.f, 0.5f, 0.4f, 1, 0));
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
							this->emitters4D[i]->particles4D.push_back(new Particle4D(this->particleTexs3D[PARTICLE3], this->emitters4D[i]->particles4D[j]->position4D, this->emitters4D[i]->particles4D[j]->velocity4D * this->emitters4D[i]->particles4D[j]->retention
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