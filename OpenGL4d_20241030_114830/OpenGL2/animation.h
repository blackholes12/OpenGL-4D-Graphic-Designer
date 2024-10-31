#pragma once
//#include<vec4.hpp>
//#include<algorithm>
//#include"Object.h"
//#include"mod.h"
//#include"body.h"
class Shift4D
{
	unsigned int stepIndex;
	float period;
	float time_of_steps(unsigned int steps)
	{
		float timeCount(0.f);
		for (unsigned int i(0); i < steps; i++)
		{
			timeCount += this->dt[i];
		}
		return timeCount;
	}
public:
	glm::vec4 position4DAfter;
	glm::vec4* positions4D;
	float* dt;
	size_t index;
	unsigned int size;
	Shift4D(glm::vec4* positions4D,float* dt,unsigned int size, size_t index)
	{
		this->positions4D = positions4D;
		this->dt = dt;
		this->size = size;
		this->stepIndex = -1;
		this->period = time_of_steps(this->size - 1);
		this->index = index;
	}
	~Shift4D() {
		delete[] this->positions4D,this->positions4D = nullptr;
		delete[] this->dt,this->dt=nullptr;
	}
	void shifting(RigidBody4D* rigidBody4D, float curTime, const float dt)
	{
		if (!rigidBody4D->is_static())
		{
			float animationTime(alg::fmod(curTime , this->period));
			for (unsigned int i(0); i < this->size; i++)
			{
				if (time_of_steps(i) < animationTime && time_of_steps(i + 1) > animationTime)
				{
					if (this->stepIndex != i)
					{
						this->stepIndex = i;
					}
				}
			}
			if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
			{
				this->position4DAfter = mix(positions4D[this->stepIndex], positions4D[this->stepIndex + 1],
					(animationTime - time_of_steps(this->stepIndex)) / this->dt[this->stepIndex]);
				rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
			}
			else
			{
				this->position4DAfter = mix(positions4D[this->stepIndex], positions4D[this->stepIndex + 1],
					(animationTime - time_of_steps(this->stepIndex)) / this->dt[this->stepIndex]) - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D);
				rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
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
	glm::vec4 position4D;
	float distance;
	float speed;
	unsigned int direction4D;
	size_t index;
	Float4D(glm::vec4 position4D, float distance, float speed, const unsigned int direction4D, size_t index)
	{
		this->position4D=position4D;
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
				this->position4DAfter = this->position4D + shift;
				rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
			}
			else
			{
				this->position4DAfter = this->position4D + shift - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D);
				rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
			}
		}
	}
};

class Rotate4D
{
public:
	glm::vec4 position4DAfter;
	alg::rotor4 rotation4DAfter;
	glm::vec4 position4D;
	glm::vec4 bodyPosition4D;
	alg::rotor4 rotation4D;
	alg::bivec4 rotateAngle4D;
	alg::bivec4 angularVelocity4D;
	bool isPositionFixed;
	size_t index1;
	VectorIndex* index2;
	Rotate4D(glm::vec4 position4D, glm::vec4 bodyPosition4D, alg::bivec4 rotateAngle4D ,alg::bivec4 angularVelocity4D, bool isPositionFixed, size_t index1, VectorIndex* index2)
	{
		this->position4D = position4D;
		this->bodyPosition4D = bodyPosition4D;
		this->rotateAngle4D = rotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);
		this->angularVelocity4D = angularVelocity4D;
		this->isPositionFixed = isPositionFixed;
		this->index1 = index1;
		this->index2 = index2;
	}
	Rotate4D(glm::vec4 position4D, glm::vec4 bodyPosition4D, alg::rotor4 rotation4D, alg::bivec4 angularVelocity4D, bool isPositionFixed, size_t index1, VectorIndex* index2)
	{
		this->position4D = position4D;
		this->bodyPosition4D = bodyPosition4D;
		this->rotation4D = rotation4D;
		this->angularVelocity4D = angularVelocity4D;
		this->isPositionFixed = isPositionFixed;
		this->index1 = index1;
		this->index2 = index2;
	}
	~Rotate4D(){
		this->index2 = nullptr, delete this->index2;
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
					this->position4DAfter = this->position4D;
					rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
				}
				else
				{
					glm::vec4 bodyVec4DToWorld = body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D);
					this->position4DAfter = this->position4D - bodyVec4DToWorld;
					glm::vec4 rotVel = body_vec_to_world(this->rotation4DAfter, left_contract_bv(alg::vec4(-rigidBody4D->animatePosition4D), rigidBody4D->angularVelocity4D).transform());
					rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
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
					rigidBody4D1->velocity4D = (this->position4DAfter - rigidBody4D1->pPosition4D)/dt;
				}
				else
				{
					glm::vec4 bodyVec4DToWorld1(body_vec_to_world(rigidBody4D1, rigidBody4D1->animatePosition4D));
					glm::vec4 bodyPos4DToWorld2(body_pos_to_world(rigidBody4D2, this->bodyPosition4D));
					this->position4DAfter = bodyPos4DToWorld2 - bodyVec4DToWorld1;
					rigidBody4D1->velocity4D = (this->position4DAfter - rigidBody4D1->pPosition4D)/dt;
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
	glm::vec4 position4D;
	float duringTime;
	float curTime;
	alg::bivec4 rotateAngle4D;
	alg::rotor4 startRotation4D;
	unsigned char state;
	size_t index;
	OpenDoor4D(glm::vec4 position4D, float duringTime, float curTime, alg::bivec4 rotateAngle4D, alg::rotor4 startRotation4D, unsigned char state, size_t index)
	{
		this->position4D = position4D;
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
		this->position4DAfter = this->position4D - bodyVec4DToWorld;
		rigidBody4D->angularVelocity4D = alg::bivec4();
		rigidBody4D->velocity4D = glm::vec4(0.f);
	}

	void open(RigidBody4D* rigidBody4D, const float dt)
	{
		rigidBody4D->angularVelocity4D = this->rotateAngle4D.radians() / this->duringTime;
		this->rotation4DAfter = update(this->startRotation4D, rigidBody4D->angularVelocity4D * this->curTime);
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = position4D - bodyVec4DToWorld;
		rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
	}

	void end(RigidBody4D* rigidBody4D)
	{
		this->rotation4DAfter = update(this->startRotation4D, this->rotateAngle4D.radians());
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = this->position4D - bodyVec4DToWorld;
		rigidBody4D->angularVelocity4D = alg::bivec4();
		rigidBody4D->velocity4D = glm::vec4(0.f);
	}

	void close(RigidBody4D* rigidBody4D, const float dt)
	{
		rigidBody4D->angularVelocity4D = this->rotateAngle4D.radians() / -this->duringTime;
		this->rotation4DAfter = update(this->startRotation4D, rigidBody4D->angularVelocity4D * -this->curTime);
		glm::vec4 bodyVec4DToWorld(body_vec_to_world(this->rotation4DAfter, rigidBody4D->animatePosition4D));
		this->position4DAfter = position4D - bodyVec4DToWorld;
		rigidBody4D->velocity4D = (this->position4DAfter - rigidBody4D->pPosition4D)/dt;
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

static void erase_animation4D(std::vector <Shift4D*>* shifts4D, std::vector <Float4D*>* floats4D,std::vector <Rotate4D*>* rotates4D, std::vector < OpenDoor4D*>* openDoors4D,size_t index0)
{
	for (size_t k(0); k < shifts4D->size(); k++)
	{
		if ((*shifts4D)[k]->index == index0)
		{
			shifts4D->erase(shifts4D->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < floats4D->size(); k++)
	{
		if ((*floats4D)[k]->index == index0)
		{
			floats4D->erase(floats4D->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < rotates4D->size(); k++)
	{
		if ((*rotates4D)[k]->index1 == index0|| (*rotates4D)[k]->index2->n == index0)
		{
			rotates4D->erase(rotates4D->begin() + k);
			k--;
		}
	}

	for (size_t k(0); k < openDoors4D->size(); k++)
	{
		if ((*openDoors4D)[k]->index == index0)
		{
			openDoors4D->erase(openDoors4D->begin() + k);
			k--;
		}
	}
}

static void shift_animation4D(std::vector <Shift4D*> shifts4D, std::vector <Float4D*> floats4D, std::vector <Rotate4D*> rotates4D, std::vector < OpenDoor4D*> openDoors4D,size_t index0,int count)
{
	for (Shift4D* shift4D : shifts4D)
	{
		if (shift4D->index >= index0)
		{
			shift4D->index += count;
		}
	}

	for (Float4D* float4D : floats4D)
	{
		if (float4D->index >= index0)
		{
			float4D->index += count;
		}
	}

	for (Rotate4D* rotate4D : rotates4D)
	{
		if (rotate4D->index1 >= index0)
		{
			rotate4D->index1 += count;
		}
		if(rotate4D->index2->isValid)
		if (rotate4D->index2->n >= index0)
		{
			rotate4D->index2->n += count;
		}
	}

	for (OpenDoor4D* openDoor4D : openDoors4D)
	{
		if (openDoor4D->index >= index0)
		{
			openDoor4D->index += count;
		}
	}
}
