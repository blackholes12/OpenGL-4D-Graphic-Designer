#pragma once
#include"body.h"
#include"colliderPhy.h"
#include"collision.h"
#include"gjk.h"
static float inverse_mass_term(RigidBody4D* body,
	glm::vec4 normal,
	glm::vec4 bodyContact)
{
	// n' = ~R n R
	glm::vec4 bodyNormal(world_vec_to_body(body, normal));

	// n . (R x . I_b^-1(x /\ n') ~R)
	return dot(bodyNormal,
			left_contract_bv(
				alg::vec4(bodyContact),
				inverse_moment_of_inertia(body,
					wedge_v(
						alg::vec4(bodyContact),
						alg::vec4(bodyNormal)
					)
				)
			).transform()
	    );
}

static float inverse_mass_term0(RigidBody4D* body,
	glm::vec4 normal,
	glm::vec4 contact)
{
	// n' = ~R n R
	glm::vec4 bodyNormal(world_vec_to_body(body, normal));
	glm::vec4 bodyContact(world_pos_to_body(body, contact));

	// n . (R x . I_b^-1(x /\ n') ~R)
	return dot(normal,
		body_vec_to_world(body,
			left_contract_bv(
				alg::vec4(bodyContact),
				inverse_moment_of_inertia(body,
					wedge_v(
						alg::vec4(bodyContact),
						alg::vec4(bodyNormal)
					)
				)
			).transform()
		)
	);
}

static float inverse_mass_term2(RigidBody4D* body,
	glm::vec4 normal,
	glm::vec4 bodyContact)
{
	// n' = ~R n R
	glm::vec4 bodyNormal(world_vec_to_body(body, normal));

	// n . (R x . I_b^-1(x /\ n') ~R)
	return dot(bodyNormal,
		left_contract_bv(
			alg::vec4(bodyContact - body->massCenter),
			wedge_v(
				alg::vec4(bodyContact - body->massCenter),
				alg::vec4(bodyNormal)
			)
		).transform()
	);
}

static CollisionConstraint collision_constraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float massAdjustmentA,
	float a_friction,
	RigidBody4D* b,
	float massAdjustmentB,
	float b_friction) {
	float e(a->restitution * b->restitution);
	float friction(a_friction * b_friction);
	glm::mat4x4 orthonormalBasis;
	orthonormal_basis(orthonormalBasis[3] = manifold.normal, &orthonormalBasis[0], &orthonormalBasis[1], &orthonormalBasis[2]);
	glm::vec4 relVel(vel_at(b, manifold.contactPosB) - vel_at(a, manifold.contactPosA));
	float relVelNormal(alg::dot(relVel, manifold.normal));
	float slop(0.005f);
	float baumgarte(0.5775f);
	float bias(baumgarte * 60.f * alg::max(manifold.depth - slop, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass(a->mass > 0.f ? massAdjustmentA / a->mass : 0.f);
	float invBMass(b->mass > 0.f ? massAdjustmentB / b->mass : 0.f);
	glm::mat4x3 orthonormalBasisInv;
	for (int i(0); i < 4; i++) {
		float invLA(massAdjustmentA * inverse_mass_term2(a, orthonormalBasis[i], manifold.contactPosA));
		float invLB(massAdjustmentB * inverse_mass_term2(b, orthonormalBasis[i], manifold.contactPosB));
		orthonormalBasisInv[i] = glm::vec3(invAMass + invBMass, invLA, invLB);
	}
	ContactState contactState;
	contactState.contactPosA = manifold.contactPosA, contactState.contactPosB = manifold.contactPosB, contactState.bias = bias, contactState.orthonormalBasisInv = orthonormalBasisInv, contactState.orthonormalBasisImpulse = glm::vec4(0.f);
	CollisionConstraint collisionConstraint;
	collisionConstraint.orthonormalBasis = orthonormalBasis, collisionConstraint.contacts = contactState, collisionConstraint.mu = friction;
	return collisionConstraint;
}

static CollisionConstraint collision_constraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float massAdjustmentA,
	float a_friction,
	float b_friction,
	float b_restitution) {
	float e(a->restitution * b_restitution);
	float friction(a_friction * b_friction);
	glm::mat4x4 orthonormalBasis;
	orthonormal_basis(orthonormalBasis[3] = manifold.normal, &orthonormalBasis[0], &orthonormalBasis[1], &orthonormalBasis[2]);
	glm::vec4 relVel(-vel_at(a, manifold.contactPosA));
	float relVelNormal(alg::dot(relVel, manifold.normal));
	float slop(0.005f);
	float baumgarte(0.5775f);
	float bias(baumgarte * 60.f * alg::max(manifold.depth - slop, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass(a->mass > 0.f ? massAdjustmentA / a->mass : 0.f);
	glm::mat4x3 orthonormalBasisInv;
	for (int i(0); i < 4; i++) {
		float invLA(massAdjustmentA * inverse_mass_term2(a, orthonormalBasis[i], manifold.contactPosA));
		orthonormalBasisInv[i] = glm::vec3(invAMass, invLA, 0.f);
	}
	ContactState contactState;
	contactState.contactPosA = manifold.contactPosA, contactState.contactPosB = manifold.contactPosB, contactState.bias = bias, contactState.orthonormalBasisInv = orthonormalBasisInv, contactState.orthonormalBasisImpulse = glm::vec4(0.f);
	CollisionConstraint collisionConstraint;
	collisionConstraint.orthonormalBasis = orthonormalBasis, collisionConstraint.contacts = contactState, collisionConstraint.mu = friction;
	return collisionConstraint;
}

static void solve(std::vector <Constraint*>* cs, RigidBody4D* a, RigidBody4D* b, bool isInverseResolve)
{
	for (unsigned int i(0); i < cs->size(); i++)
	{
		Constraint* c;
		if (isInverseResolve)c = (*cs)[cs->size() - i - 1];
		else c = (*cs)[i];
		CollisionConstraint* cC = &c->collisionConstraint;
		glm::vec4 relVel(vel_at(b, cC->contacts.contactPosB) - vel_at(a, cC->contacts.contactPosA));
		glm::vec4 newImpulses;
		c->momentInertiaScalarA = get_moment_inertia_scalar(a, a->angularVelocity4D);
		c->momentInertiaScalarB = get_moment_inertia_scalar(b, b->angularVelocity4D);
		glm::vec4 orthonormalBasisLambda;
		orthonormalBasisLambda[0] = alg::dot(-relVel, cC->orthonormalBasis[0]) / (cC->contacts.orthonormalBasisInv[0].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[0].y / c->momentInertiaScalarA : 0.f) + (c->momentInertiaScalarB > 0.f ? cC->contacts.orthonormalBasisInv[0].z / c->momentInertiaScalarB : 0.f));
		orthonormalBasisLambda[1] = alg::dot(-relVel, cC->orthonormalBasis[1]) / (cC->contacts.orthonormalBasisInv[1].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[1].y / c->momentInertiaScalarA : 0.f) + (c->momentInertiaScalarB > 0.f ? cC->contacts.orthonormalBasisInv[1].z / c->momentInertiaScalarB : 0.f));
		orthonormalBasisLambda[2] = alg::dot(-relVel, cC->orthonormalBasis[2]) / (cC->contacts.orthonormalBasisInv[2].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[2].y / c->momentInertiaScalarA : 0.f) + (c->momentInertiaScalarB > 0.f ? cC->contacts.orthonormalBasisInv[2].z / c->momentInertiaScalarB : 0.f));
		orthonormalBasisLambda[3] = (alg::dot(-relVel, cC->orthonormalBasis[3]) + cC->contacts.bias) / (cC->contacts.orthonormalBasisInv[3].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[3].y / c->momentInertiaScalarA : 0.f) + (c->momentInertiaScalarB > 0.f ? cC->contacts.orthonormalBasisInv[3].z / c->momentInertiaScalarB : 0.f));
		newImpulses[0] = cC->contacts.orthonormalBasisImpulse[0] + orthonormalBasisLambda[0];
		newImpulses[1] = cC->contacts.orthonormalBasisImpulse[1] + orthonormalBasisLambda[1];
		newImpulses[2] = cC->contacts.orthonormalBasisImpulse[2] + orthonormalBasisLambda[2];
		newImpulses[3] = alg::max(cC->contacts.orthonormalBasisImpulse[3] + orthonormalBasisLambda[3], 0.f);
		float maxImpulse(alg::abs(cC->mu * cC->contacts.orthonormalBasisImpulse[3]));
		float impulseMag(alg::length(glm::vec3(newImpulses)));
		c->impulseMagAdd += impulseMag;
		c->maxImpulseAdd += maxImpulse;
		if (impulseMag > maxImpulse)
		{
			float factor(maxImpulse / impulseMag);
			for (int j(0); j < 3; j++)
			{
				newImpulses[j] *= factor;
			}
		}
		float prevImpulse(cC->contacts.orthonormalBasisImpulse[3]);
		cC->contacts.orthonormalBasisImpulse[3] = alg::max(prevImpulse + orthonormalBasisLambda[3], 0.f);
		glm::mat4 impulses;
		impulses[0] = cC->orthonormalBasis[0] * (newImpulses[0] - cC->contacts.orthonormalBasisImpulse[0]);
		impulses[1] = cC->orthonormalBasis[1] * (newImpulses[1] - cC->contacts.orthonormalBasisImpulse[1]);
		impulses[2] = cC->orthonormalBasis[2] * (newImpulses[2] - cC->contacts.orthonormalBasisImpulse[2]);
		impulses[3] = cC->orthonormalBasis[3] * (cC->contacts.orthonormalBasisImpulse[3] - prevImpulse);
		c->impulses = impulses;
		for (int j(0); j < 4; j++) {
			cC->contacts.orthonormalBasisImpulse[j] = newImpulses[j];
		}
		resolve_impulse(a, -impulses[0] - impulses[1] - impulses[2] - impulses[3], cC->contacts.contactPosA, c->momentInertiaScalarA);
		resolve_impulse(b, impulses[0] + impulses[1] + impulses[2] + impulses[3], cC->contacts.contactPosB, c->momentInertiaScalarB);
	}
}

static void solve(std::vector <Constraint*>* cs, RigidBody4D* a, bool isInverseResolve)
{
	for (unsigned int i(0); i < cs->size(); i++)
	{
		Constraint* c;
		if (isInverseResolve)c = (*cs)[cs->size() - i - 1];
		else c = (*cs)[i];
		CollisionConstraint* cC = &c->collisionConstraint;
		glm::vec4 relVel(-vel_at(a, cC->contacts.contactPosA));
		glm::vec4 newImpulses;
		c->momentInertiaScalarA = get_moment_inertia_scalar(a, a->angularVelocity4D);
		glm::vec4 orthonormalBasisLambda;
		orthonormalBasisLambda[0] = alg::dot(-relVel, cC->orthonormalBasis[0]) / (cC->contacts.orthonormalBasisInv[0].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[0].y / c->momentInertiaScalarA : 0.f) + cC->contacts.orthonormalBasisInv[0].z);
		orthonormalBasisLambda[1] = alg::dot(-relVel, cC->orthonormalBasis[1]) / (cC->contacts.orthonormalBasisInv[1].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[1].y / c->momentInertiaScalarA : 0.f) + cC->contacts.orthonormalBasisInv[1].z);
		orthonormalBasisLambda[2] = alg::dot(-relVel, cC->orthonormalBasis[2]) / (cC->contacts.orthonormalBasisInv[2].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[2].y / c->momentInertiaScalarA : 0.f) + cC->contacts.orthonormalBasisInv[2].z);
		orthonormalBasisLambda[3] = (alg::dot(-relVel, cC->orthonormalBasis[3]) + cC->contacts.bias) / (cC->contacts.orthonormalBasisInv[3].x + (c->momentInertiaScalarA > 0.f ? cC->contacts.orthonormalBasisInv[3].y / c->momentInertiaScalarA : 0.f) + cC->contacts.orthonormalBasisInv[3].z);
		newImpulses[0] = cC->contacts.orthonormalBasisImpulse[0] + orthonormalBasisLambda[0];
		newImpulses[1] = cC->contacts.orthonormalBasisImpulse[1] + orthonormalBasisLambda[1];
		newImpulses[2] = cC->contacts.orthonormalBasisImpulse[2] + orthonormalBasisLambda[2];
		newImpulses[3] = alg::max(cC->contacts.orthonormalBasisImpulse[3] + orthonormalBasisLambda[3], 0.f);
		float maxImpulse(alg::abs(cC->mu * cC->contacts.orthonormalBasisImpulse[3]));
		float impulseMag(alg::length(glm::vec3(newImpulses[0], newImpulses[1], newImpulses[2])));
		c->impulseMagAdd += impulseMag;
		c->maxImpulseAdd += maxImpulse;
		if (impulseMag > maxImpulse)
		{
			float factor(maxImpulse / impulseMag);
			for (int j(0); j < 3; j++)
			{
				newImpulses[j] *= factor;
			}
		}
		float prevImpulse(cC->contacts.orthonormalBasisImpulse[3]);
		cC->contacts.orthonormalBasisImpulse[3] = alg::max(prevImpulse + orthonormalBasisLambda[3], 0.f);
		glm::mat4 impulses;
		impulses[0] = cC->orthonormalBasis[0] * (newImpulses[0] - cC->contacts.orthonormalBasisImpulse[0]);
		impulses[1] = cC->orthonormalBasis[1] * (newImpulses[1] - cC->contacts.orthonormalBasisImpulse[1]);
		impulses[2] = cC->orthonormalBasis[2] * (newImpulses[2] - cC->contacts.orthonormalBasisImpulse[2]);
		impulses[3] = cC->orthonormalBasis[3] * (cC->contacts.orthonormalBasisImpulse[3] - prevImpulse);
		c->impulses = impulses;
		//if (_isnan(alg::length(cC->orthonormalBasis[3])))std::cout << "error" << '\n';
		//if (_isnan(alg::length(impulses[0])))std::cout << "error2" << '\n';
		//if (_isnan(alg::length(impulses[1])))std::cout << "error3" << '\n';
		//if (_isnan(alg::length(impulses[2])))std::cout << "error4" << '\n';
		//if (_isnan(alg::length(impulses[3])))std::cout << "error5" << '\n';
		for (int j(0); j < 4; j++) {
			cC->contacts.orthonormalBasisImpulse[j] = newImpulses[j];
		}
		resolve_impulse(a, -impulses[0] - impulses[1] - impulses[2] - impulses[3], cC->contacts.contactPosA, c->momentInertiaScalarA);
	}
}

static void get_constraint(
	RigidBody4D* a,
	RigidBody4D* b,
	std::vector < Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for(Collision collision: collisions)
		constraints.push_back(new Constraint(collision.index1, collision.index2,collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY: a->mu , b, collision.massAdjustmentB, collision.type == 0 ? INFINITY: b->mu)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c=nullptr,free(c);
	}
}

static void solve_rigidbody_rigidbody(RigidBody4D* a,
	RigidBody4D* b,
	std::vector<Constraint*>* constraint,
	bool isInverseResolve)
{
	solve(constraint, a, b, isInverseResolve);
}

static void update_billiards(RigidBody4D* a,
	RigidBody4D* b,
	std::vector < Collision> collisions)
{
	if (a->colType != NONE || b->colType != NONE)
	{
		for (Collision collision : collisions)
		{
			a->isSleep = false;
			b->isSleep = false;
			if (collision.collisionManifold.depth > 0.f)
			{
				//if (a->objectName == "Billiard" && b->objectName == "Billiard")
				glm::vec4 normalAtoB = collision.collisionManifold.normal;
				glm::vec4 averageV = (a->velocity4d * a->mass + b->velocity4d * b->mass) / (a->mass + b->mass);
				glm::vec4 va = a->velocity4d - averageV;
				glm::vec4 vb = b->velocity4d - averageV;
				float offsetVa = dot(normalAtoB, va);
				float offsetVb = dot(-normalAtoB, vb);
				if (offsetVb < 0.f)
				{
					float offsetV = offsetVa + offsetVb;
					glm::vec4 v0DivideMass = (1.f + alg::max(a->restitution, b->restitution)) * offsetV * normalAtoB / (a->mass + b->mass);
					a->velocity4d -= b->mass * v0DivideMass;
					b->velocity4d += a->mass * v0DivideMass;
				}
			}
		}
	}
}

static void get_constraint(
	RigidBody4D* a,
	Object4D* b,
	std::vector < Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for (Collision collision : collisions)
			constraints.push_back(new Constraint(collision.index1, collision.index2, collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY: a->mu,collision.type == 0 ? INFINITY : b->mu , b->restitution)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c = nullptr, free(c);
	}
}

static void solve_rigidbody_wall(
	RigidBody4D* a,
	Object4D* b,
	std::vector<Constraint*>* constraints,
	bool isInverseResolve)
{
	solve(constraints, a, isInverseResolve);
}

static void update_billiards(
	RigidBody4D* a,
	Wall4D* w)
{
	float radius(alg::min(a->scale4D.w, alg::min(a->scale4D.z, alg::min(a->scale4D.x, a->scale4D.y))) / 2.f);
	glm::vec4 pWA(a->position4d - w->position4d);
	glm::vec4 sW(w->scale4D / 2.f);
	if (abs(pWA.x) < sW.x + radius + 0.18f &&
		abs(pWA.y) < sW.y + radius + 0.1f &&
		abs(pWA.z) < sW.z + radius + 0.18f &&
		abs(pWA.w) < sW.w + radius + 0.18f)
	{
		if (pWA.x * a->velocity4d.x > 0.f && abs(pWA.x) > sW.x - radius)
		{
			a->velocity4d.x = -a->velocity4d.x;
		}
		if (pWA.z * a->velocity4d.z > 0.f && abs(pWA.z) > sW.z - radius)
		{
			a->velocity4d.z = -a->velocity4d.z;
		}
		if (pWA.w * a->velocity4d.w > 0.f && abs(pWA.w) > sW.w - radius)
		{
			a->velocity4d.w = -a->velocity4d.w;
		}
		if (pWA.y < sW.y + radius + 0.0001f)
		{
			if (length(glm::vec3(pWA.x - sW.x, pWA.z - sW.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z - sW.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x - sW.x, pWA.z + sW.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z + sW.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x - sW.x, pWA.z - sW.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z - sW.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x - sW.x, pWA.z + sW.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z + sW.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x - sW.x, pWA.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z, pWA.w - sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x - sW.x, pWA.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
			if (length(glm::vec3(pWA.x + sW.x, pWA.z, pWA.w + sW.w)) < 0.05f)
			{
				a->isFrozen = true;
				a->set_position4D(glm::vec4(a->position4d.x, a->position4d.y - 0.15f, a->position4d.z, a->position4d.w));
			}
		}
	}
}

static void get_constraint(
	RigidBody4D* a,
	std::vector <Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for (Collision collision : collisions)
		constraints.push_back(new Constraint(collision.index1, -1, collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY: a->mu, collision.type == 0 ? INFINITY: 0.7f, 0.25f)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c = nullptr, free(c);
	}
}

static void solve_rigidbody_edge(
	RigidBody4D* a,
	std::vector<Constraint*>* constraints,
	bool isInverseResolve)
{
	solve(constraints, a, isInverseResolve);
}

static std::vector<std::vector<Collision>> detect_rigidbody_or_wall(size_t index1, size_t index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (b->colType){
	    case SPHERE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = sphere_to_sphere(index1, index2, a, b, collisionsVec, false);break;}
	    	    case BOX4D:{collisionsVec = cube_to_sphere(index1, index2, a, b, collisionsVec, false);break;}
	    	    case STEP4D:{collisionsVec = cube_to_sphere(index1, index2, a, b, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_sphere(index1, index2, a, b, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_sphere(index1, index2, a, b, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case BOX4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = cube_to_sphere(index1, index2, b, a, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = cube_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	    case STEP4D:{collisionsVec = cube_to_cube(index1, index2, a, b, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case STEP4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = cube_to_sphere(index1, index2, b, a, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = cube_to_cube(index1, index2, b, a, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = cube_to_cube(index1, index2, a, b, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case MESH4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = mesh_to_sphere(index1, index2, b, a, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = mesh_to_cube(index1, index2, b, a, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = mesh_to_cube(index1, index2, b, a, collisionsVec, true);break;}
				case MESH4D:{collisionsVec = mesh_to_mesh(index1, index2, a, b, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(index1, index2, a, b, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case CAPSULE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = capsule_to_sphere(index1, index2, b, a, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = capsule_to_cube(index1, index2, b, a, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = capsule_to_cube(index1, index2, b, a, collisionsVec, true);break;}
				case MESH4D:{collisionsVec = capsule_to_mesh(index1, index2, b, a, collisionsVec, true);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_capsule(index1, index2, a, b, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	}
	return collisionsVec;
}

static std::vector<std::vector<Collision>> detect_rigidbody_terrain(size_t index1, RigidBody4D* a, Terrain4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (a->colType) {
	case SPHERE4D: { collisionsVec = terrain_to_sphere(index1, -1, b, a, collisionsVec); break; }
	case BOX4D: { collisionsVec = terrain_to_cube(index1, -1, b, a, collisionsVec); break; }
	case STEP4D: { collisionsVec = terrain_to_cube(index1, -1, b, a, collisionsVec); break; }
	case MESH4D: { collisionsVec = terrain_to_mesh(index1, -1, b, a, collisionsVec); break; }
	case CAPSULE4D: { collisionsVec = terrain_to_capsule(index1, -1, b, a, collisionsVec); break; }
	}
	return collisionsVec;
}

static std::vector<std::vector<Collision>> detect_rigidbody_edge(size_t index1, RigidBody4D* a, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (a->colType){
	case SPHERE4D:{collisionsVec = sphere_to_half_space(index1, -1, a, collisionsVec);break;}
	case BOX4D:{collisionsVec = cube_to_half_space(index1, -1, a, collisionsVec);break;}
	case STEP4D:{collisionsVec = cube_to_half_space(index1, -1, a, collisionsVec);break;}
	case MESH4D:{collisionsVec = mesh_to_half_space(index1, -1, a, collisionsVec);break;}
	case CAPSULE4D:{collisionsVec = capsule_to_half_space(index1, -1, a, collisionsVec);break;}
	}
	return collisionsVec;
}