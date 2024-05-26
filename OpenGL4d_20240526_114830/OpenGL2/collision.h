#pragma once
#include<vec4.hpp>
#include"colliderPhy.h"
#include"body.h"
static struct ContactState
{
	glm::vec4 contactPos;
	float bias;
	float normalMass;
	float normalImpulse;
	glm::vec3 tangentMass;
	glm::vec3 tangentImpulse;
};

static struct Tangents
{
	glm::vec4 t1;
	glm::vec4 t2;
	glm::vec4 t3;
	glm::vec4 tangent(int index)
	{
		switch (index)
		{
		case 0: { return t1; break; }
		case 1: { return t2; break; }
		case 2: { return t3; break; }
		}
	}
};

static struct CollisionConstraint
{
	glm::vec4 normal;
	Tangents tangents;
	ContactState contacts;
	float mu;
	//explicit CollisionConstraint(glm::vec4 normal, Tangents tangents, glm::vec4 contactPos, float bias, float normalMass, float normalImpulse, glm::vec3 tangentMass, glm::vec3 tangentImpulse, float mu)
	//{
	//	this->normal = normal;
	//	this->tangents = tangents;
	//	this->contacts.contactPos = contactPos;
	//	this->contacts.bias = bias;
	//	this->contacts.normalMass = normalMass;
	//	this->contacts.normalImpulse = normalImpulse;
	//	this->contacts.tangentMass = tangentMass;
	//	this->contacts.tangentImpulse = tangentImpulse;
	//	this->mu = mu;
	//}
};

static struct Constraint
{
	int index1;
	int index2;//-1 collide with edge
	CollisionConstraint collisionConstraint;
	explicit Constraint(int index1, int index2, CollisionConstraint collisionConstraint)
	{
		this->index1 = index1;
		this->index2 = index2;
		this->collisionConstraint = collisionConstraint;
	}
};