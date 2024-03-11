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