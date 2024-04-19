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
	float tangentMass[3];
	float tangentImpulse[3];
};

static struct CollisionConstraint
{
	glm::vec4 normal;
	glm::vec4 tangents[3];
	ContactState contacts;
	float mu;
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