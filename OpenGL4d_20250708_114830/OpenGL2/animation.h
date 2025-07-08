#pragma once
//#include<vec4.hpp>
//#include<algorithm>
//#include"Object.h"
//#include"mod.h"
//#include"body.h"
static struct PT
{
	glm::vec4 positions4D;
	float dt;
};
class Shift4D
{
	float period;
	float time_of_steps(size_t steps)
	{
		float timeCount(0.f);
		for (size_t i(0); i < steps; i++)
		{
			timeCount += this->pTs[i].dt;
		}
		return timeCount;
	}
public:
	glm::vec4 position4DAfter;
	std::vector< PT >pTs;
	size_t index;
	Shift4D(std::vector <PT> pTs,size_t index)
	{
		this->pTs = pTs;
		this->period = time_of_steps(this->pTs.size() - 1);
		this->index = index;
	}
	~Shift4D() {
	}
	void update_period()
	{
		this->period = time_of_steps(this->pTs.size() - 1);
	}
	void shifting(RigidBody4D* rigidBody4D, float curTime, const float dt)
	{
		if (!rigidBody4D->is_static())
		{
			if (this->pTs.size() == 1)
			{
				this->position4DAfter = this->pTs[0].positions4D;
				rigidBody4D->velocity4d = glm::vec4(0.f);
			}
			else if (this->pTs.size() > 1)
			{
				float animationTime(alg::fmod(curTime, this->period));
				float timeCount(0.f);
				for (size_t i(0); i < this->pTs.size() - 1; i++)
				{
					timeCount += this->pTs[i].dt;
					if (timeCount > animationTime)
					{
						if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
						{
							this->position4DAfter = mix(this->pTs[i].positions4D, this->pTs[i + 1].positions4D,
								1.f + (animationTime - timeCount) / this->pTs[i].dt);
						}
						else
						{
							this->position4DAfter = mix(this->pTs[i].positions4D, this->pTs[i + 1].positions4D,
								1.f + (animationTime - timeCount) / this->pTs[i].dt) - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D);
						}
						rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D) / dt;
						break;
					}
				}
			}
		}
	}
};

class Float4D
{
	float wave(float x)
	{
		return cos(x * PI);
	}
	float wave_speed(float x, float speed)
	{
		return -sin(x * PI) * PI* speed;
	}
public:
	glm::vec4 position4DAfter;
	glm::vec4 position4d;
	float distance;
	float speed;
	int direction4D;
	size_t index;
	Float4D(glm::vec4 position4d, float distance, float speed, const int direction4D, size_t index)
	{
		this->position4d=position4d;
		this->index = index;
		this->distance = distance;
		this->speed = speed;
		this->direction4D = direction4D;
	}
	~Float4D() {}
	void floating(RigidBody4D* rigidBody4D, float curTime, const float dt)
	{
		if (!rigidBody4D->is_static())
		{
			glm::vec4 shift(glm::vec4(0.f));
			shift[this->direction4D - 1] = this->distance * wave(this->speed * curTime / this->distance);
			if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
			{
				this->position4DAfter = this->position4d + shift;
				rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
			}
			else
			{
				this->position4DAfter = this->position4d + shift - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D);
				rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
			}
		}
	}
};

class Rotate4D
{
public:
	glm::vec4 position4DAfter;
	alg::rotor4 rotation4DAfter;
	glm::vec4 position4d;
	glm::vec4 bodyPosition4D;
	alg::rotor4 rotation4D;
	alg::bivec4 rotateAngle4D;
	alg::bivec4 angularVelocity4D;
	bool isPositionFixed;
	size_t index1;
	VectorIndex index2;
	Rotate4D(glm::vec4 position4d, glm::vec4 bodyPosition4D, alg::bivec4 rotateAngle4D ,alg::bivec4 angularVelocity4D, bool isPositionFixed, size_t index1, VectorIndex index2)
	{
		this->position4d = position4d;
		this->bodyPosition4D = bodyPosition4D;
		this->rotateAngle4D = rotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);
		this->angularVelocity4D = angularVelocity4D;
		this->isPositionFixed = isPositionFixed;
		this->index1 = index1;
		this->index2 = index2;
	}
	Rotate4D(glm::vec4 position4d, glm::vec4 bodyPosition4D, alg::rotor4 rotation4D, alg::bivec4 angularVelocity4D, bool isPositionFixed, size_t index1, VectorIndex index2)
	{
		this->position4d = position4d;
		this->bodyPosition4D = bodyPosition4D;
		this->rotation4D = rotation4D;
		this->angularVelocity4D = angularVelocity4D;
		this->isPositionFixed = isPositionFixed;
		this->index1 = index1;
		this->index2 = index2;
	}
	~Rotate4D(){
	}
	void rotating(RigidBody4D* rigidBody4D, float curTime, const float dt)
	{
		if (!rigidBody4D->is_static())
		{
			rigidBody4D->angularVelocity4D = this->angularVelocity4D;
			this->rotation4DAfter = update(this->rotation4D, this->angularVelocity4D * curTime);
			if (this->isPositionFixed)
			{
				if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
				{
					this->position4DAfter = this->position4d;
					rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
				}
				else
				{
					glm::vec4 bodyVec4DToWorld = body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D);
					this->position4DAfter = this->position4d - bodyVec4DToWorld;
					glm::vec4 rotVel = body_vec_to_world(this->rotation4DAfter, left_contract_bv(alg::vec4(-rigidBody4D->animatePosition4D), rigidBody4D->angularVelocity4D).transform());
					rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
				}
			}
		}
	}
	void rotating(RigidBody4D* rigidBody4D1, RigidBody4D* rigidBody4D2, float curTime, const float dt)
	{
		if (!rigidBody4D1->is_static())
		{
			rigidBody4D1->angularVelocity4D = this->angularVelocity4D;
			this->rotation4DAfter = update(this->rotation4D, this->angularVelocity4D * curTime);
			if (this->isPositionFixed)
			{
				if (rigidBody4D1->animatePosition4D == glm::vec4(0.f))
				{
					glm::vec4 bodyVec4DToWorld2(body_pos_to_world(rigidBody4D2, this->bodyPosition4D));
					this->position4DAfter = bodyVec4DToWorld2;
					rigidBody4D1->velocity4d = (this->position4DAfter - rigidBody4D1->pPosition4D)/dt;
				}
				else
				{
					glm::vec4 bodyVec4DToWorld1(body_vec_to_world(rigidBody4D1, rigidBody4D1->animatePosition4D));
					glm::vec4 bodyPos4DToWorld2(body_pos_to_world(rigidBody4D2, this->bodyPosition4D));
					this->position4DAfter = bodyPos4DToWorld2 - bodyVec4DToWorld1;
					rigidBody4D1->velocity4d = (this->position4DAfter - rigidBody4D1->pPosition4D)/dt;
				}
			}
		}
	}
};

class OpenDoor4D
{
public:
	glm::vec4 position4DAfter;
	alg::rotor4 rotation4DAfter;
	glm::vec4 position4d;
	float duringTime;
	float curTime;
	alg::bivec4 rotateAngle4D;
	alg::rotor4 startRotation4D;
	unsigned char state;
	size_t index;
	OpenDoor4D(glm::vec4 position4d, float duringTime, float curTime, alg::bivec4 rotateAngle4D, alg::rotor4 startRotation4D, unsigned char state, size_t index)
	{
		this->position4d = position4d;
		this->duringTime = duringTime;
		this->curTime = curTime;
		this->rotateAngle4D = rotateAngle4D;
		this->startRotation4D = startRotation4D;
		this->state = state;
		this->index = index;
	}

	void start(RigidBody4D* rigidBody4D)
	{
		this->rotation4DAfter = this->startRotation4D;
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, glm::vec4(0.f, 0.f, 0.25f, -0.025f)));
		this->position4DAfter = this->position4d - bodyVec4DToWorld;
		rigidBody4D->angularVelocity4D = alg::bivec4();
		rigidBody4D->velocity4d = glm::vec4(0.f);
	}

	void open(RigidBody4D* rigidBody4D, const float dt)
	{
		rigidBody4D->angularVelocity4D = this->rotateAngle4D.radians() / this->duringTime;
		this->rotation4DAfter = update(this->startRotation4D, rigidBody4D->angularVelocity4D * this->curTime);
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = position4d - bodyVec4DToWorld;
		rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
	}

	void end(RigidBody4D* rigidBody4D)
	{
		this->rotation4DAfter = update(this->startRotation4D, this->rotateAngle4D.radians());
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = this->position4d - bodyVec4DToWorld;
		rigidBody4D->angularVelocity4D = alg::bivec4();
		rigidBody4D->velocity4d = glm::vec4(0.f);
	}

	void close(RigidBody4D* rigidBody4D, const float dt)
	{
		rigidBody4D->angularVelocity4D = this->rotateAngle4D.radians() / -this->duringTime;
		this->rotation4DAfter = update(this->startRotation4D, rigidBody4D->angularVelocity4D * -this->curTime);
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = position4d - bodyVec4DToWorld;
		rigidBody4D->velocity4d = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
	}

	void animate(RigidBody4D* rigidBody4D,const float dt)
	{
		if (!rigidBody4D->is_static())
		{
			switch (this->state)
			{
			case 0:
			{
				this->start(rigidBody4D); break;
			}
			case 1:
			{
				this->curTime += dt;
				if (this->curTime < this->duringTime) { this->open(rigidBody4D,dt); }
				else { this->end(rigidBody4D); this->curTime = this->duringTime; this->state = 2; }
				break;
			}
			case 2:
			{
				this->end(rigidBody4D); break;
			}
			case 3:
			{
				this->curTime -= dt;
				if (this->curTime > 0.f) { this->close(rigidBody4D,dt); }
				else { this->start(rigidBody4D); this->curTime = 0.f; this->state = 0; }
				break;
			}
			}
		}
	}

	void switch_state()
	{
		switch (this->state)
		{
		case 0: {this->state = 1;break;}
		case 1: {this->state = 3;break;}
		case 2: {this->state = 3;break;}
		case 3: {this->state = 1;break;}
		}
	}
	~OpenDoor4D() {}
};

static void erase_animation4D(std::vector <Shift4D*>* shifts4d, std::vector <Float4D*>* floats4d,std::vector <Rotate4D*>* rotates4d, std::vector < OpenDoor4D*>* openDoors4d,size_t index0)
{
	for (size_t k(0); k < shifts4d->size(); k++)
	{
		if ((*shifts4d)[k]->index == index0)
		{
			shifts4d->erase(shifts4d->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < floats4d->size(); k++)
	{
		if ((*floats4d)[k]->index == index0)
		{
			floats4d->erase(floats4d->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < rotates4d->size(); k++)
	{
		if ((*rotates4d)[k]->index1 == index0|| (*rotates4d)[k]->index2.n == index0)
		{
			rotates4d->erase(rotates4d->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < openDoors4d->size(); k++)
	{
		if ((*openDoors4d)[k]->index == index0)
		{
			openDoors4d->erase(openDoors4d->begin() + k);
			k--;
		}
	}
}

static void shift_animation4D(std::vector <Shift4D*> shifts4d, std::vector <Float4D*> floats4d, std::vector <Rotate4D*> rotates4d, std::vector < OpenDoor4D*> openDoors4d,size_t index0,int count)
{
	for (Shift4D* shift4D : shifts4d)
	{
		if (shift4D->index >= index0)
		{
			shift4D->index += count;
		}
	}

	for (Float4D* float4D : floats4d)
	{
		if (float4D->index >= index0)
		{
			float4D->index += count;
		}
	}

	for (Rotate4D* rotate4D : rotates4d)
	{
		if (rotate4D->index1 >= index0)
		{
			rotate4D->index1 += count;
		}
		if(rotate4D->index2.isValid)
		if (rotate4D->index2.n >= index0)
		{
			rotate4D->index2.n += count;
		}
	}

	for (OpenDoor4D* openDoor4D : openDoors4d)
	{
		if (openDoor4D->index >= index0)
		{
			openDoor4D->index += count;
		}
	}
}
