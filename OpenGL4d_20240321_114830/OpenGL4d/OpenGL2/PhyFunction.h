#pragma once
#include"body.h"
#include"colliderPhy.h"
#include"collision.h"
#include"gjk.h"

static float inverse_mass_term(RigidBody4D* body,
	glm::vec4 normal,
	glm::vec4 contact) 
{
	// n' = ~R n R
	glm::vec4 bodyNormal = world_vec_to_body(body,normal);
	glm::vec4 bodyContact = world_pos_to_body(body,contact);

	// n . (R x . I_b^-1(x /\ n') ~R)
	float normalf = dot(normal,
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
	return normalf;
}

static CollisionConstraint collisionConstraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float mass_adjustment_a,
	float a_mu,
	RigidBody4D* b,
	float mass_adjustment_b,
	float b_mu) {
	CollisionConstraint collisionConstraint0;
	float e = min(a->restitution, b->restitution);
	float mu = min(a_mu, b_mu);
	glm::vec4 tangents[3];
	orthonormal_basis(manifold.normal, &tangents[0], &tangents[1], &tangents[2]);
	glm::vec4 relVel = vel_at(b,manifold.contacts) - vel_at(a,manifold.contacts);
	float relVelNormal = dot(relVel, manifold.normal);

	float slop = 0.f;
	float baumgarte = 0.42f;
	float bias = -baumgarte * 60.f * min((slop - manifold.depth), 0.f) + (relVelNormal < -1.f ?-e * relVelNormal: 0.f);
	float invAMass = a->mass > 0.f ?mass_adjustment_a / a->mass :0.f;
	float invBMass = b->mass > 0.f ?mass_adjustment_b / b->mass :0.f;

	float invLA =
		mass_adjustment_a * inverse_mass_term(a, manifold.normal, manifold.contacts);
	float invLB =
		mass_adjustment_b * inverse_mass_term(b, manifold.normal, manifold.contacts);

	float normalMass =
		1.0 / (invAMass + invBMass + invLA + invLB);

	float tangentMass[3] = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < 3; i++) {
		float invLTA = mass_adjustment_a
			* inverse_mass_term(a, tangents[i], manifold.contacts);
		float invLTB = mass_adjustment_b
			* inverse_mass_term(b, tangents[i], manifold.contacts);

		tangentMass[i] =
			1.0 / (invAMass + invBMass + invLTA + invLTB);
	}
	collisionConstraint0.contacts.contactPos = manifold.contacts;
	collisionConstraint0.contacts.bias = bias;
	collisionConstraint0.contacts.normalMass = normalMass;
	collisionConstraint0.contacts.normalImpulse = 0.f;
	collisionConstraint0.contacts.tangentMass[0] = tangentMass[0];
	collisionConstraint0.contacts.tangentMass[1] = tangentMass[1];
	collisionConstraint0.contacts.tangentMass[2] = tangentMass[2];
	collisionConstraint0.contacts.tangentImpulse[0] = 0.f;
	collisionConstraint0.contacts.tangentImpulse[1] = 0.f;
	collisionConstraint0.contacts.tangentImpulse[2] = 0.f;
	collisionConstraint0.normal = manifold.normal;
	collisionConstraint0.tangents[0] = tangents[0];
	collisionConstraint0.tangents[1] = tangents[1];
	collisionConstraint0.tangents[2] = tangents[2];
	collisionConstraint0.mu = mu;
	return collisionConstraint0;
}

static CollisionConstraint collisionConstraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float mass_adjustment_a,
	float b_mu) {
	CollisionConstraint collisionConstraint0;
	float e = a->restitution;
	float mu = min(a->mu, b_mu);
	glm::vec4 tangents[3];
	orthonormal_basis(manifold.normal, &tangents[0], &tangents[1], &tangents[2]);

	glm::vec4 relVel = vel_at(a, manifold.contacts);
	float relVelNormal = dot(relVel, manifold.normal);

	float slop = 0.f;
	float baumgarte = 0.42f;
	float bias = -baumgarte * 60.f * min((slop - manifold.depth), 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f);
	float invAMass = a->mass > 0.f ? mass_adjustment_a / a->mass : 0.f;

	float invLA =
		mass_adjustment_a * inverse_mass_term(a, manifold.normal, manifold.contacts);

	float normalMass =
		0.5 / (invAMass + invLA);

	float tangentMass[3] = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < 3; i++) {
		float invLTA = mass_adjustment_a
			* inverse_mass_term(a, tangents[i], manifold.contacts);

		tangentMass[i] =
			0.5 / (invAMass + invLTA);
	}
	collisionConstraint0.contacts.contactPos = manifold.contacts;
	collisionConstraint0.contacts.bias = bias;
	collisionConstraint0.contacts.normalMass = normalMass;
	collisionConstraint0.contacts.normalImpulse = 0.f;
	collisionConstraint0.contacts.tangentMass[0] = tangentMass[0];
	collisionConstraint0.contacts.tangentMass[1] = tangentMass[1];
	collisionConstraint0.contacts.tangentMass[2] = tangentMass[2];
	collisionConstraint0.contacts.tangentImpulse[0] = 0.f;
	collisionConstraint0.contacts.tangentImpulse[1] = 0.f;
	collisionConstraint0.contacts.tangentImpulse[2] = 0.f;
	collisionConstraint0.normal = manifold.normal;
	collisionConstraint0.tangents[0] = tangents[0];
	collisionConstraint0.tangents[1] = tangents[1];
	collisionConstraint0.tangents[2] = tangents[2];
	collisionConstraint0.mu = mu;
	return collisionConstraint0;
}

static void solve(CollisionConstraint c, RigidBody4D* a, float a_bounce, RigidBody4D* b, float b_bounce,float dt)
{
	{
		glm::vec4 relVel = vel_at(b, c.contacts.contactPos) - vel_at(a, c.contacts.contactPos);
		float newImpulses[3];
		for (int i = 0; i < 3; i++)
		{
			float lambda = dot(-relVel, c.tangents[i]) * c.contacts.tangentMass[i];

			newImpulses[i] = c.contacts.tangentImpulse[i] + lambda;
		}

		float max_impulse = abs(c.mu * c.contacts.normalImpulse);

		float impulseMag2 = 0.f;
		for (int i = 0; i < 3; i++)
		{
			impulseMag2 += newImpulses[i] * newImpulses[i];
		}
		float impulseMag = sqrt(impulseMag2);
		if (impulseMag > max_impulse)
		{
			float factor = max_impulse / impulseMag;
			for (int i = 0; i < 3; i++)
			{
				newImpulses[i] *= factor;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			c.contacts.tangentImpulse[i] = newImpulses[i];
		}

		// calculate normal impulse
		float relVelNormal = dot(relVel, c.normal);
		float lambda = c.contacts.normalMass * (-relVelNormal + c.contacts.bias);
		float prevImpulse = c.contacts.normalImpulse;
		c.contacts.normalImpulse = max(prevImpulse + lambda, 0.f);
	}
	
	{
		glm::vec4 relVel = vel_at(b, c.contacts.contactPos) - vel_at(a, c.contacts.contactPos);
		float newImpulses[3];
		for (int i = 0; i < 3; i++)
		{
			float lambda = dot(-relVel, c.tangents[i]) * c.contacts.tangentMass[i];

			newImpulses[i] = c.contacts.tangentImpulse[i] + lambda;
		}

		float max_impulse = abs(c.mu * c.contacts.normalImpulse);

		float impulseMag2 = 0.f;
		for (int i = 0; i < 3; i++)
		{
			impulseMag2 += newImpulses[i] * newImpulses[i];
		}
		float impulseMag = sqrt(impulseMag2);
		if (impulseMag > max_impulse)
		{
			float factor = max_impulse / impulseMag;
			for (int i = 0; i < 3; i++)
			{
				newImpulses[i] *= factor;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			glm::vec4 impulse = (1.f + (a_bounce + b_bounce) / 2.f) * (c.tangents[i] * (newImpulses[i] - c.contacts.tangentImpulse[i]));
			c.contacts.tangentImpulse[i] = newImpulses[i];
			resolve_impulse(a, -impulse/2.f, c.contacts.contactPos, dt);
			resolve_impulse(b, impulse/2.f, c.contacts.contactPos, dt);
		}

		// calculate normal impulse
		if (a->objectName != "Billiard" || b->objectName != "Billiard")
		{
			float relVelNormal = dot(relVel, c.normal);
			float lambda = c.contacts.normalMass * (-relVelNormal + c.contacts.bias);
			float prevImpulse = c.contacts.normalImpulse;
			c.contacts.normalImpulse = max(prevImpulse + lambda, 0.f);
			glm::vec4 impulse = (1.f + (a_bounce + b_bounce) / 2.f) * c.normal * (c.contacts.normalImpulse - prevImpulse);
			resolve_impulse(a, -impulse/2.f, c.contacts.contactPos, dt);
			resolve_impulse(b, impulse/2.f, c.contacts.contactPos, dt);
		}
	}
}

static void solve(CollisionConstraint c, RigidBody4D* b, float a_bounce, const char* objectNameA, float dt)
{
	{
		glm::vec4 relVel = vel_at(b, c.contacts.contactPos);
		float newImpulses[3];
		for (int i = 0; i < 3; i++)
		{
			float lambda = dot(-relVel, c.tangents[i]) * c.contacts.tangentMass[i];

			newImpulses[i] = c.contacts.tangentImpulse[i] + lambda;
		}

		float max_impulse = abs(c.mu * c.contacts.normalImpulse);

		float impulseMag2 = 0.f;
		for (int i = 0; i < 3; i++)
		{
			impulseMag2 += newImpulses[i] * newImpulses[i];
		}
		float impulseMag = sqrt(impulseMag2);
		if (impulseMag > max_impulse)
		{
			float factor = max_impulse / impulseMag;
			for (int i = 0; i < 3; i++)
			{
				newImpulses[i] *= factor;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			c.contacts.tangentImpulse[i] = newImpulses[i];
		}

		// calculate normal impulse
		float relVelNormal = dot(relVel, c.normal);
		float lambda = c.contacts.normalMass * (-relVelNormal + c.contacts.bias);
		float prevImpulse = c.contacts.normalImpulse;
		c.contacts.normalImpulse = max(prevImpulse + lambda, 0.f);
	}

	{
		glm::vec4 relVel = vel_at(b, c.contacts.contactPos);
		float newImpulses[3];
		for (int i = 0; i < 3; i++)
		{
			float lambda = dot(-relVel, c.tangents[i]) * c.contacts.tangentMass[i];

			newImpulses[i] = c.contacts.tangentImpulse[i] + lambda;
		}

		float max_impulse = abs(c.mu * c.contacts.normalImpulse);

		float impulseMag2 = 0.f;
		for (int i = 0; i < 3; i++)
		{
			impulseMag2 += newImpulses[i] * newImpulses[i];
		}
		float impulseMag = sqrt(impulseMag2);
		if (impulseMag > max_impulse)
		{
			float factor = max_impulse / impulseMag;
			for (int i = 0; i < 3; i++)
			{
				newImpulses[i] *= factor;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			glm::vec4 impulse = (1.f + (a_bounce + b->bounce) / 2.f) * c.tangents[i] * (newImpulses[i] - c.contacts.tangentImpulse[i]);
			c.contacts.tangentImpulse[i] = newImpulses[i];
			resolve_impulse(b, impulse, c.contacts.contactPos, dt);
		}

		// calculate normal impulse
		if (objectNameA!="Billiard"||b->objectName != "Billiard")
		{
			float relVelNormal = dot(relVel, c.normal);
			float lambda = c.contacts.normalMass * (-relVelNormal + c.contacts.bias);
			float prevImpulse = c.contacts.normalImpulse;
			c.contacts.normalImpulse = max(prevImpulse + lambda, 0.f);
			glm::vec4 impulse = (1.f + (a_bounce + b->bounce) / 2.f) * c.normal * (c.contacts.normalImpulse - prevImpulse);
			resolve_impulse(b, impulse, c.contacts.contactPos, dt);
		}
	}
}

static void solve_and_shift(RigidBody4D* a,
	RigidBody4D* b,
	Collision* collision,
	float dt)
{
	if (collision->collisionManifold.depth > 0.f)
	{
		solve(collisionConstraint(collision->collisionManifold, a, collision->massAdjustmentA,a->mu, b, collision->massAdjustmentB,b->mu), a,a->bounce, b,b->bounce, dt);
		if (a->objectName == "Billiard" && b->objectName == "Billiard")
		{
			glm::vec4 normalAtoB = collision->collisionManifold.normal;
			glm::vec4 averageV = (a->velocity4D * a->mass + b->velocity4D * b->mass) / (a->mass + b->mass);
			glm::vec4 va = vel_at(a, collision->collisionManifold.contacts) - averageV;
			glm::vec4 vb = vel_at(b, collision->collisionManifold.contacts) - averageV;
			float offsetVa = dot(normalAtoB, va);
			float offsetVb = dot(-normalAtoB, vb);
			float offsetV = offsetVa + offsetVb;
			glm::vec4 v0DivideMass = (1.f + (a->bounce + b->bounce) / 2.f) * offsetV * normalAtoB / (a->mass + b->mass);
			a->velocity4D -= b->mass * v0DivideMass;
			b->velocity4D += a->mass * v0DivideMass;
		}
	}
}

static void solve_and_shift(
	RigidBody4D* a,
	Object4D* b,
	Collision* collision,
	float dt)
{
	if (collision->collisionManifold.depth > 0.f)
	{
		solve(collisionConstraint(collision->collisionManifold, a, collision->massAdjustmentA, b->mu), a, b->bounce, b->objectName, dt);
		if (a->objectName == "Billiard" && b->objectName == "Billiard")
		{
			glm::vec4 normalAtoB = collision->collisionManifold.normal;
			glm::vec4 vb = vel_at(a, collision->collisionManifold.contacts);
			float offsetVb = dot(-normalAtoB, vb);
			a->velocity4D += (1.f + (a->bounce + b->bounce) / 2.f) * offsetVb * normalAtoB;
		}
	}
}

static void solve_and_shift(RigidBody4D* a,
	Collision* collision,
	float dt)
{
	if (collision->collisionManifold.depth > 0.f)
	{
		solve(collisionConstraint(collision->collisionManifold, a, collision->massAdjustmentA, 1.6f), a, 0.25f, "Ground", dt);
	}
}

static void solve_and_shift(
	RigidBody4D* a,
	RigidBody4D* b,
	HingeConstraint4D* hingeConstraint,
	float dt)
{
	glm::vec4 normal4D0 = body_pos_to_world(a, hingeConstraint->bodyPosition4D1) - body_pos_to_world(b, hingeConstraint->bodyPosition4D2);
	glm::vec4 normal4D = normalize(normal4D0);
	float depth = length(normal4D0);
	if (depth > 0.f)
	{
		glm::vec4 contacts = (body_pos_to_world(b, hingeConstraint->bodyPosition4D2) + body_pos_to_world(a, hingeConstraint->bodyPosition4D1)) / 2.f;
		solve(collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f,INFINITY, b, 1.f, INFINITY), a,0.f, b,0.f, dt);
	}
}

static void solve_and_shift(RigidBody4D* a,
	Object4D* b,
	HingeConstraint4D* hingeConstraint,
	float dt,bool isInverse)
{
	glm::vec4 normal4D0;
	if(!isInverse)
		normal4D0= body_pos_to_world(b, hingeConstraint->bodyPosition4D2) - body_pos_to_world(a, hingeConstraint->bodyPosition4D1);
	if (isInverse)
		normal4D0 = body_pos_to_world(b, hingeConstraint->bodyPosition4D1) - body_pos_to_world(a, hingeConstraint->bodyPosition4D2);
	float depth = length(normal4D0);
	if (depth > 0.f)
	{
		glm::vec4 normal4D = normalize(normal4D0);
		glm::vec4 contacts;
		if (!isInverse)
			contacts = body_pos_to_world(a, hingeConstraint->bodyPosition4D1);
		if (isInverse)
			contacts = body_pos_to_world(b, hingeConstraint->bodyPosition4D1);
		solve(collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY), a, -a->bounce, "Hinge Constraint", dt);
	}
}

static void solve_and_shift(RigidBody4D* a,
	HingeConstraint4D* hingeConstraint,
	float dt)
{
	glm::vec4 normal4D0 = hingeConstraint->worldPosition4D - body_pos_to_world(a, hingeConstraint->bodyPosition4D1);
	float depth = length(normal4D0);
	if (depth > 0.f)
	{
		glm::vec4 normal4D = normalize(normal4D0);
		glm::vec4 contacts = body_pos_to_world(a, hingeConstraint->bodyPosition4D1);
		solve(collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY), a, -a->bounce, "Hinge Constraint", dt);
	}
}

inline static void solve_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b, Collision* collision,const float dt)
{
	solve_and_shift(b, a, collision, dt);
}
inline static void solve_rigidbody_wall(RigidBody4D* a, Object4D* b, Collision* collision, const float dt)
{
	solve_and_shift(a, b, collision, dt);
}
inline static void solve_rigidbody_edge(RigidBody4D* a, Collision* collision, const float dt)
{
	solve_and_shift(a, collision, dt);
}


inline static void solve_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b, HingeConstraint4D* hingeConstraint, const float dt)
{
	solve_and_shift(a, b,hingeConstraint, dt);
}

inline static void solve_rigidbody_wall(RigidBody4D* a, Object4D* b, HingeConstraint4D* hingeConstraint, const float dt, bool isInverse)
{
	solve_and_shift(a, b, hingeConstraint, dt, isInverse);
}

inline static void solve_rigidbody(RigidBody4D* a, HingeConstraint4D* hingeConstraint, const float dt)
{
	solve_and_shift(a, hingeConstraint, dt);
}

static vector<Collision*> detect_rigidbody_or_wall(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions)
{
	if (b->colType == SPHERE4D)
	{
		if (a->colType == SPHERE4D) {
			collisions = sphere_to_sphere(a, b, index1, index2, collisions, false);
		}
		if (a->colType == BOX4D|| a->colType == STEP4D) {
			collisions = cube_to_sphere(a, b, index1, index2, collisions, false);
		}
		if (a->colType == MESH4D) {
			collisions = mesh_to_sphere(a, b, index1, index2, collisions, false);
		}
		if (a->colType == CAPSULE4D) {
			collisions = capsule_to_sphere(a, b, index1, index2, collisions, false);
		}
	}
	if (b->colType == BOX4D|| b->colType == STEP4D)
	{
		if (a->colType == SPHERE4D) {
			collisions = cube_to_sphere(a, b, index1, index2, collisions, true);
		}
		if (a->colType == BOX4D||a->colType == STEP4D) {
			collisions = cube_to_cube(a, b, index1, index2, collisions, false);
		}
		if (a->colType == MESH4D) {
			collisions = mesh_to_cube(a, b, index1, index2, collisions, false);
		}
		if (a->colType == CAPSULE4D) {
			collisions = capsule_to_cube(a, b, index1, index2, collisions, false);
		}
	}
	if (b->colType == MESH4D)
	{
		if (a->colType == SPHERE4D) {
			collisions = mesh_to_sphere(a, b, index1, index2, collisions, true);
		}
		if (a->colType == BOX4D|| a->colType == STEP4D) {
			collisions = mesh_to_cube(a, b, index1, index2, collisions, true);
		}
		if (a->colType == MESH4D) {
			collisions = mesh_to_mesh(a, b, index1, index2, collisions, false);
		}
		if (a->colType == CAPSULE4D) {
			collisions = capsule_to_cube(a, b, index1, index2, collisions, false);
		}
	}
	if (b->colType == CAPSULE4D)
	{
		if (a->colType == SPHERE4D) {
			collisions = capsule_to_sphere(a, b, index1, index2, collisions, true);
		}
		if (a->colType == BOX4D||a->colType == STEP4D) {
			collisions = capsule_to_cube(a, b, index1, index2, collisions, true);
		}
		if (a->colType == MESH4D) {
			collisions = capsule_to_mesh(a, b, index1, index2, collisions, true);
		}
		if (a->colType == CAPSULE4D) {
			collisions = capsule_to_capsule(a, b, index1, index2, collisions, true);
		}
	}
	return collisions;
}

static vector<Collision*> detect_rigidbody_terrain(RigidBody4D* a, Terrain4D* b, int index1, vector<Collision*> collisions)
{
	if (a->colType == SPHERE4D) {
		collisions = terrain_to_sphere(b,a, index1, -1, collisions);
	}
	if (a->colType == BOX4D|| a->colType == STEP4D) {
		collisions = terrain_to_cube(b, a, index1, -1, collisions);
	}
	if (a->colType == MESH4D) {
		collisions = terrain_to_mesh(b, a, index1, -1, collisions);
	}
	if (a->colType == CAPSULE4D) {
		collisions = terrain_to_capsule(b, a, index1, -1, collisions);
	}
	return collisions;
}

static vector<Collision*> detect_rigidbody_edge(RigidBody4D* a, int index1, vector<Collision*> collisions)
{
	if (a->colType == SPHERE4D) {
		collisions = sphere_to_edge(a, index1, -1, collisions);
	}
	if (a->colType == BOX4D|| a->colType == STEP4D) {
		collisions = cube_to_edge(a, index1, -1, collisions);
	}
	if (a->colType == MESH4D) {
		collisions = mesh_to_edge(a, index1, -1, collisions);
	}
	if (a->colType == CAPSULE4D) {
		collisions = capsule_to_edge(a, index1, -1, collisions);
	}
	return collisions;
}