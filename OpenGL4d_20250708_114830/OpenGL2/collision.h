#pragma once
#include<vec4.hpp>
#include"colliderPhy.h"
#include"body.h"
static struct ContactState
{
	glm::vec4 contactPosA;
	glm::vec4 contactPosB;
	float bias;
	glm::mat4x3 orthonormalBasisInv;
	glm::vec4 orthonormalBasisImpulse;
};

static struct CollisionConstraint
{
	glm::mat4x4 orthonormalBasis;
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
	glm::mat4 impulses;
	float momentInertiaScalarA;
	float momentInertiaScalarB;
	float impulseMagAdd;
	float maxImpulseAdd;
	explicit Constraint(int index1, int index2, CollisionConstraint collisionConstraint)
	{
		this->index1 = index1;
		this->index2 = index2;
		this->collisionConstraint = collisionConstraint;
		this->impulses = glm::mat4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		this->momentInertiaScalarA = 0.f;
		this->momentInertiaScalarB = 0.f;
		this->impulseMagAdd = 0.f;
		this->maxImpulseAdd = 0.f;
	}
};