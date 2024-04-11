#pragma once
#include<vec4.hpp>
#include<algorithm>
#include"Object.h"
#include"mod.h"
#include"body.h"
class Shift4D
{
	glm::vec4 velocity4D;
	unsigned int stepIndex;
	float period;
	float time_of_steps(unsigned int steps)
	{
		float timeCount = 0.f;
		for (unsigned int i = 0; i < steps; i++)
		{
			timeCount += this->dt[i];
		}
		return timeCount;
	}
public:
	glm::vec4* positions4D;
	float* dt;
	unsigned int index;
	unsigned int size;
	Shift4D(glm::vec4* positions4D,float* dt,unsigned int size, unsigned int index)
	{
		this->positions4D = positions4D;
		this->velocity4D = glm::vec4(0.f);
		this->dt = dt;
		this->size = size;
		this->stepIndex = -1;
		this->period = time_of_steps(this->size - 1);
		this->index = index;
	}
	~Shift4D() {
		delete[] this->positions4D;
		this->positions4D = nullptr;
		delete[] this->dt;
		this->dt=nullptr;
	}
	void shifting(RigidBody4D* rigidBody4D, float curTime)
	{
		if (!rigidBody4D->is_static())
		{
			float animationTime = this->period * fract(curTime / this->period);
			for (unsigned int i = 0; i < this->size; i++)
			{
				if (time_of_steps(i) < animationTime && time_of_steps(i + 1) > animationTime)
				{
					if (this->stepIndex != i)
					{
						this->stepIndex = i;
						this->velocity4D = (positions4D[i + 1] - positions4D[i]) / this->dt[i];
					}
				}
			}
			if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
			{
				rigidBody4D->set_position4D(mix(positions4D[this->stepIndex], positions4D[this->stepIndex + 1],
					(animationTime - time_of_steps(this->stepIndex)) / this->dt[this->stepIndex]));
				rigidBody4D->velocity4D = this->velocity4D;
			}
			else
			{
				rigidBody4D->set_position4D(mix(positions4D[this->stepIndex], positions4D[this->stepIndex + 1],
					(animationTime - time_of_steps(this->stepIndex)) / this->dt[this->stepIndex]) - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D));
				glm::vec4 rotVel = body_vec_to_world(rigidBody4D, left_contract_bv(alg::vec4(-rigidBody4D->animatePosition4D), rigidBody4D->angularVelocity4D).transform());
				rigidBody4D->velocity4D = rotVel + this->velocity4D;
			}
		}
	}
};

class Float4D
{
	float wave(float x)
	{
		return cos(x * glm::pi<float>());
	}
	float wave_speed(float x, float speed)
	{
		return -sin(x * glm::pi<float>()) * glm::pi<float>()* speed;
	}
public:
	glm::vec4 position4D;
	float distance;
	float speed;
	unsigned int direction4D;
	int index;
	Float4D(glm::vec4 position4D, float distance, float speed, const unsigned int direction4D, unsigned int index)
	{
		this->position4D=position4D;
		this->index = index;
		this->distance = distance;
		this->speed = speed;
		this->direction4D = direction4D;
	}
	~Float4D() {}
	void floating(RigidBody4D* rigidBody4D, float curTime)
	{
		if (!rigidBody4D->is_static())
		{
			glm::vec4 shift = glm::vec4(0.f);
			glm::vec4 shiftVelocity4D = glm::vec4(0.f);
			shift[this->direction4D - 1] = this->distance * wave(this->speed * curTime / this->distance);
			shiftVelocity4D[this->direction4D - 1] = wave_speed(this->speed * curTime / this->distance, this->speed);
			if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
			{
				rigidBody4D->set_position4D(this->position4D + shift);
				rigidBody4D->velocity4D = shiftVelocity4D;
			}
			else
			{
				rigidBody4D->set_position4D(this->position4D + shift - body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D));
				glm::vec4 rotVel = body_vec_to_world(rigidBody4D, left_contract_bv(alg::vec4(-rigidBody4D->animatePosition4D), rigidBody4D->angularVelocity4D).transform());
				rigidBody4D->velocity4D = rotVel + shiftVelocity4D;
			}
		}
	}
};

class Rotate4D
{
public:
	glm::vec4 position4D;
	glm::vec4 bodyPosition4D;
	alg::rotor4 rotation4D;
	alg::bivec4 rotateAngle4D;
	alg::bivec4 angularVelocity4D;
	bool isPositionFixed;
	int index1;
	int index2;
	Rotate4D(glm::vec4 position4D, glm::vec4 bodyPosition4D, alg::bivec4 rotateAngle4D ,alg::bivec4 angularVelocity4D, bool isPositionFixed, unsigned int index1, unsigned int index2)
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
	Rotate4D(glm::vec4 position4D, glm::vec4 bodyPosition4D, alg::rotor4 rotation4D, alg::bivec4 angularVelocity4D, bool isPositionFixed, unsigned int index1, unsigned int index2)
	{
		this->position4D = position4D;
		this->bodyPosition4D = bodyPosition4D;
		this->rotation4D = rotation4D;
		this->angularVelocity4D = angularVelocity4D;
		this->isPositionFixed = isPositionFixed;
		this->index1 = index1;
		this->index2 = index2;
	}
	~Rotate4D(){}
	void rotating(RigidBody4D* rigidBody4D, float curTime)
	{
		if (!rigidBody4D->is_static())
		{
			rigidBody4D->angularVelocity4D = this->angularVelocity4D;
			rigidBody4D->set_rotation4D(update(this->rotation4D, this->angularVelocity4D * curTime));
			if (this->isPositionFixed)
			{
				if (rigidBody4D->animatePosition4D == glm::vec4(0.f))
				{
					rigidBody4D->set_position4D(this->position4D);
					rigidBody4D->velocity4D = glm::vec4(0.f);
				}
				else
				{
					glm::vec4 bodyVec4DToWorld = body_vec_to_world(rigidBody4D, rigidBody4D->animatePosition4D);
					rigidBody4D->set_position4D(this->position4D - bodyVec4DToWorld);
					glm::vec4 rotVel = body_vec_to_world(rigidBody4D, left_contract_bv(alg::vec4(-rigidBody4D->animatePosition4D), rigidBody4D->angularVelocity4D).transform());
					rigidBody4D->velocity4D = rotVel;
				}
			}
		}
	}
	void rotating(RigidBody4D* rigidBody4D1, RigidBody4D* rigidBody4D2, float curTime)
	{
		if (!rigidBody4D1->is_static())
		{
			rigidBody4D1->angularVelocity4D = this->angularVelocity4D;
			rigidBody4D1->set_rotation4D(update(this->rotation4D, this->angularVelocity4D * curTime));
			if (this->isPositionFixed)
			{
				if (rigidBody4D1->animatePosition4D == glm::vec4(0.f))
				{
					glm::vec4 bodyVec4DToWorld2 = body_pos_to_world(rigidBody4D2, this->bodyPosition4D);
					rigidBody4D1->set_position4D(bodyVec4DToWorld2);
					rigidBody4D1->velocity4D = rigidBody4D2->velocity4D + body_vec_to_world(rigidBody4D2, left_contract_bv(alg::vec4(this->bodyPosition4D), rigidBody4D2->angularVelocity4D).transform());
				}
				else
				{
					glm::vec4 bodyVec4DToWorld1 = body_vec_to_world(rigidBody4D1, rigidBody4D1->animatePosition4D);
					glm::vec4 bodyPos4DToWorld2 = body_pos_to_world(rigidBody4D2, this->bodyPosition4D);
					rigidBody4D1->set_position4D(bodyPos4DToWorld2 - bodyVec4DToWorld1);
					glm::vec4 rotVel1 = body_vec_to_world(rigidBody4D1, left_contract_bv(alg::vec4(-rigidBody4D1->animatePosition4D), rigidBody4D1->angularVelocity4D).transform());
					glm::vec4 rotVel2 = body_vec_to_world(rigidBody4D2, left_contract_bv(alg::vec4(this->bodyPosition4D), rigidBody4D2->angularVelocity4D).transform());
					rigidBody4D1->velocity4D = rigidBody4D2->velocity4D + rotVel2 + rotVel1;
				}
			}
		}
	}
};

static void erase_animation4D(std::vector <Shift4D*>* shifts4D, std::vector <Float4D*>* floats4D,std::vector <Rotate4D*>* rotates4D,unsigned int index0)
{
	for (size_t k = 0; k < shifts4D->size(); k++)
	{
		if (shifts4D[0][k]->index == index0)
		{
			shifts4D->erase(shifts4D->begin() + k);
			k--;
		}
	}

	for (size_t k = 0; k < floats4D->size(); k++)
	{
		if (floats4D[0][k]->index == index0)
		{
			floats4D->erase(floats4D->begin() + k);
			k--;
		}
	}

	for (size_t k = 0; k < rotates4D->size(); k++)
	{
		if (rotates4D[0][k]->index1 == index0|| rotates4D[0][k]->index2 == index0)
		{
			rotates4D->erase(rotates4D->begin() + k);
			k--;
		}
	}
}

static void shift_animation4D(std::vector <Shift4D*> shifts4D, std::vector <Float4D*> floats4D, std::vector <Rotate4D*> rotates4D, unsigned int index0,int count)
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
		if (rotate4D->index2 >= index0&& rotate4D->index2!=-1)
		{
			rotate4D->index2 += count;
		}
	}
}
