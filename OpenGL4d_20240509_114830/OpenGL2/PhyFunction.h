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

static CollisionConstraint collisionConstraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float massAdjustmentA,
	float a_mu,
	RigidBody4D* b,
	float massAdjustmentB,
	float b_mu) {
	float e(max(a->restitution, b->restitution));
	float mu(a_mu * b_mu);
	Tangents tangents;
	orthonormal_basis(manifold.normal, &tangents.t1, &tangents.t2, &tangents.t3);
	glm::vec4 relVel(vel_at(b, manifold.contacts) - vel_at(a, manifold.contacts));
	float relVelNormal(dot(relVel, manifold.normal));
	float slop(0.01f);
	float baumgarte(0.42f);
	float bias( - baumgarte * 60.f * min(slop - manifold.depth, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass(a->mass > 0.f ? massAdjustmentA / a->mass : 0.f);
	float invBMass(b->mass > 0.f ? massAdjustmentB / b->mass : 0.f);
	float invLA(massAdjustmentA * inverse_mass_term(a, manifold.normal, manifold.contacts));
	float invLB(massAdjustmentB * inverse_mass_term(b, manifold.normal, manifold.contacts));
	float normalMass(1.f / (invAMass + invBMass + invLA + invLB));
	glm::vec3 tangentMass(glm::vec3(0.f));
	for (int i(0); i < 3; i++) {
		float invLTA(massAdjustmentA* inverse_mass_term(a, tangents.tangent(i), manifold.contacts));
		float invLTB(massAdjustmentB* inverse_mass_term(b, tangents.tangent(i), manifold.contacts));
		tangentMass[i] = 1.f / (invAMass + invBMass + invLTA + invLTB);
	}
	return CollisionConstraint(manifold.normal, tangents, ContactState(manifold.contacts, bias, normalMass, 0.f, tangentMass, glm::vec3(0.f)), mu);
}

static CollisionConstraint collisionConstraint(
	CollisionManifold manifold,
	RigidBody4D* a,
	float massAdjustmentA,
	float b_mu,float b_restitution) {
	float e(max(a->restitution,b_restitution));
	float mu(a->mu * b_mu);
	Tangents tangents;
	orthonormal_basis(manifold.normal, &tangents.t1, &tangents.t2, &tangents.t3);
	glm::vec4 relVel(vel_at(a, manifold.contacts));
	float relVelNormal(dot(relVel, manifold.normal));
	float slop(0.01f);
	float baumgarte(0.42f);
	float bias( - baumgarte * 60.f * min(slop - manifold.depth, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass( a->mass > 0.f ? massAdjustmentA / a->mass : 0.f);
	float invLA( massAdjustmentA * inverse_mass_term(a, manifold.normal, manifold.contacts));
	float normalMass( 1.f / (invAMass + invLA));
	glm::vec3 tangentMass(glm::vec3(0.f));
	for (int i(0); i < 3; i++) {
		float invLTA( massAdjustmentA * inverse_mass_term(a, tangents.tangent(i), manifold.contacts));
		tangentMass[i] = 1.f / (invAMass + invLTA);
	}
	return CollisionConstraint(manifold.normal, tangents, ContactState(manifold.contacts, bias, normalMass, 0.f, tangentMass, glm::vec3(0.f)),mu);
}

static void solve(CollisionConstraint* c, RigidBody4D* a, RigidBody4D* b, float dt)
{
	glm::vec4 relVel(vel_at(b, c->contacts.contactPos) - vel_at(a, c->contacts.contactPos));
	float newImpulses[3];
	for (int i(0); i < 3; i++)
	{
		float lambda(dot(-relVel, c->tangents.tangent(i)) * c->contacts.tangentMass[i]);
		newImpulses[i] = c->contacts.tangentImpulse[i] + lambda;
	}
	float max_impulse(abs(c->mu * c->contacts.normalImpulse));
	float impulseMag2(0.f);
	for (int i(0); i < 3; i++)
	{
		impulseMag2 += newImpulses[i] * newImpulses[i];
	}
	float impulseMag(sqrt(impulseMag2));
	if (impulseMag > max_impulse)
	{
		float factor(max_impulse / impulseMag);
		for (int i(0); i < 3; i++)
		{
			newImpulses[i] *= factor;
		}
	}
	for (int i(0); i < 3; i++)
	{
		glm::vec4 impulse(c->tangents.tangent(i) * (newImpulses[i] - c->contacts.tangentImpulse[i]));
		c->contacts.tangentImpulse[i] = newImpulses[i];
		resolve_impulse(a, -impulse, c->contacts.contactPos, dt);
		resolve_impulse(b, impulse, c->contacts.contactPos, dt);
	}
	// calculate normal impulse
	float relVelNormal(dot(relVel, c->normal));
	float lambda0(c->contacts.normalMass * (-relVelNormal + c->contacts.bias));
	float prevImpulse(c->contacts.normalImpulse);
	c->contacts.normalImpulse = max(prevImpulse + lambda0, 0.f);
	glm::vec4 impulse(c->normal * (c->contacts.normalImpulse - prevImpulse));
	resolve_impulse(a, -impulse, c->contacts.contactPos, dt);
	resolve_impulse(b, impulse, c->contacts.contactPos, dt);
}

static void solve(CollisionConstraint* c, RigidBody4D* b, float dt)
{
	
	glm::vec4 relVel(vel_at(b, c->contacts.contactPos));
	float newImpulses[3];
	for (int i(0); i < 3; i++)
	{
		float lambda(dot(-relVel, c->tangents.tangent(i)) * c->contacts.tangentMass[i]);
		newImpulses[i] = c->contacts.tangentImpulse[i] + lambda;
	}
	float max_impulse(abs(c->mu * c->contacts.normalImpulse));
	float impulseMag2(0.f);
	for (int i(0); i < 3; i++)
	{
		impulseMag2 += newImpulses[i] * newImpulses[i];
	}
	float impulseMag(sqrt(impulseMag2));
	if (impulseMag > max_impulse)
	{
		float factor(max_impulse / impulseMag);
		for (int i(0); i < 3; i++)
		{
			newImpulses[i] *= factor;
		}
	}
	for (int i(0); i < 3; i++)
	{
		glm::vec4 impulse(c->tangents.tangent(i) * (newImpulses[i] - c->contacts.tangentImpulse[i]));
		c->contacts.tangentImpulse[i] = newImpulses[i];
		resolve_impulse(b, impulse, c->contacts.contactPos, dt);
	}
	// calculate normal impulse
	float relVelNormal(dot(relVel, c->normal));
	float lambda0(c->contacts.normalMass * (-relVelNormal + c->contacts.bias));
	float prevImpulse(c->contacts.normalImpulse);
	c->contacts.normalImpulse = max(prevImpulse + lambda0, 0.f);
	glm::vec4 impulse(c->normal * (c->contacts.normalImpulse - prevImpulse));
	resolve_impulse(b, impulse, c->contacts.contactPos, dt);
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	RigidBody4D* b,
	Collision collision,
	std::vector<Constraint*>* constraints)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		constraints->push_back(new Constraint(index1,index2,collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, a->mu, b, collision.massAdjustmentB, b->mu)));
	}
}

static void solve_rigidbody_rigidbody(RigidBody4D* a,
	RigidBody4D* b,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, b, a, dt);
}

static void update_billiards(RigidBody4D* a,
	RigidBody4D* b,
	Collision collision,
	float dt)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		//if (a->objectName == "Billiard" && b->objectName == "Billiard")
		glm::vec4 normalAtoB = collision.collisionManifold.normal;
		glm::vec4 averageV = (a->velocity4D * a->mass + b->velocity4D * b->mass) / (a->mass + b->mass);
		glm::vec4 va = a->velocity4D - averageV;
		glm::vec4 vb = b->velocity4D - averageV;
		float offsetVa = dot(normalAtoB, va);
		float offsetVb = dot(-normalAtoB, vb);
		if (offsetVb > 0.f)
		{
			float offsetV = offsetVa + offsetVb;
			glm::vec4 v0DivideMass = (1.f + max(a->restitution, b->restitution)) * offsetV * normalAtoB / (a->mass + b->mass);
			a->velocity4D -= b->mass * v0DivideMass;
			b->velocity4D += a->mass * v0DivideMass;
		}
	}
}

static void get_constraint(
	int index1,
    int index2,
	RigidBody4D* a,
	Object4D* b,
	Collision collision,
	std::vector<Constraint*>* constraints)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		constraints->push_back(new Constraint(index1, index2,collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, b->mu, b->restitution)));
	}
}

static void solve_rigidbody_wall(
	RigidBody4D* a,
	Object4D* b,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, a, dt);
}

static void update_billiards(
	RigidBody4D* a,
	Object4D* b,
	Collision collision,
	float dt)
{
	//if (a->objectName == "Billiard" && b->objectName == "Billiard")
	glm::vec4 normalAtoB = collision.collisionManifold.normal;
	glm::vec4 vb = a->velocity4D;
	float offsetVb = dot(-normalAtoB, vb);
	if (offsetVb > 0.f)
	{
		a->velocity4D += (1.f + (b->restitution == 0.f ? 0.f : max(a->restitution, b->restitution))) * offsetVb * normalAtoB;
		a->set_position4D(a->position4D + collision.collisionManifold.depth * normalAtoB);
	}
}

static void get_constraint(
	int index1,
	RigidBody4D* a,
	Collision collision,
	std::vector<Constraint*>* constraints)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		constraints->push_back(new Constraint(index1, -1, collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, 1.6f, 0.25f)));
	}
}

static void solve_rigidbody_edge(RigidBody4D* a,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, a, dt);
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	RigidBody4D* b,
	HingeConstraint4D* hingeConstraint,
	std::vector<Constraint*>* constraints)
{
	glm::vec4 worldPosition1(body_pos_to_world(a, hingeConstraint->bodyPosition4D1));
	glm::vec4 worldPosition2(body_pos_to_world(b, hingeConstraint->bodyPosition4D2));
	glm::vec4 normal4D0(worldPosition1 - worldPosition2);
	glm::vec4 normal4D(normalize(normal4D0));
	float depth(length(normal4D0));
	if (depth > 0.f)
	{
		glm::vec4 contacts((worldPosition1 + worldPosition2) / 2.f);
		constraints->push_back(new Constraint(index1, index2,collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, b, 1.f, INFINITY)));
	}
}

static void solve_rigidbody_rigidbody2(
	RigidBody4D* a,
	RigidBody4D* b,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, a, b, dt);
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	Object4D* b,
	HingeConstraint4D* hingeConstraint,
	std::vector<Constraint*>* constraints,
	bool isInverse)
{
	glm::vec4 normal4D0;
	glm::vec4 worldPosition1;
	glm::vec4 worldPosition2;
	if (!isInverse)
	{
		worldPosition1 = body_pos_to_world(b, hingeConstraint->bodyPosition4D2);
		worldPosition2 = body_pos_to_world(a, hingeConstraint->bodyPosition4D1);
	}	
	if (isInverse)
	{
		worldPosition1 = body_pos_to_world(b, hingeConstraint->bodyPosition4D1);
		worldPosition2 = body_pos_to_world(a, hingeConstraint->bodyPosition4D2);
	}
	normal4D0 = worldPosition1 - worldPosition2;
	float depth(length(normal4D0));
	if (depth > 0.f)
	{
		glm::vec4 normal4D(normalize(normal4D0));
		glm::vec4 contacts((worldPosition1 + worldPosition2)/2.f);
		constraints->push_back(new Constraint(index1, index2, collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, 0.f)));
	}
}

static void solve_rigidbody_wall2(RigidBody4D* a,
	Object4D* b,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, a, dt);
}

static void get_constraint(
	int index1,
	RigidBody4D* a,
	HingeConstraint4D* hingeConstraint,
	std::vector<Constraint*>* constraints)
{
	glm::vec4 worldPosition4D2(body_pos_to_world(a, hingeConstraint->bodyPosition4D1));
	glm::vec4 normal4D0(hingeConstraint->worldPosition4D - worldPosition4D2);
	float depth(length(normal4D0));
	if (depth > 0.f)
	{
		glm::vec4 normal4D(normalize(normal4D0));
		glm::vec4 contacts((hingeConstraint->worldPosition4D+ worldPosition4D2)/2.f);
		constraints->push_back(new Constraint(index1, -1, collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, 0.f)));
	}
}

static void solve_rigidbody2(RigidBody4D* a,
	Constraint* constraint,
	float dt)
{
	solve(&constraint->collisionConstraint, a, dt);
}

static vector<Collision> detect_rigidbody_or_wall(Object4D* a, Object4D* b, int index1, int index2, vector<Collision> collisions)
{
	switch (b->colType){
	    case SPHERE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisions = sphere_to_sphere(a, b, index1, index2, collisions, false);break;}
	    	    case BOX4D:{collisions = cube_to_sphere(a, b, index1, index2, collisions, false);break;}
	    	    case STEP4D:{collisions = cube_to_sphere(a, b, index1, index2, collisions, false);break;}
				case MESH4D:{collisions = mesh_to_sphere(a, b, index1, index2, collisions, false);break;}
	    	    case CAPSULE4D:{collisions = capsule_to_sphere(a, b, index1, index2, collisions, false);break;}
	    	}
	    	break;
	    }
	    case BOX4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisions = cube_to_sphere(b, a, index1, index2, collisions, true);break;}
	    	    case BOX4D:{collisions = cube_to_cube(a, b, index1, index2, collisions, false);break;}
	    	    case STEP4D:{collisions = cube_to_cube(a, b, index1, index2, collisions, false);break;}
				case MESH4D:{collisions = mesh_to_cube(a, b, index1, index2, collisions, false);break;}
	    	    case CAPSULE4D:{collisions = capsule_to_cube(a, b, index1, index2, collisions, false);break;}
	    	}
	    	break;
	    }
	    case STEP4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisions = cube_to_sphere(b, a, index1, index2, collisions, true);break;}
	    	    case BOX4D:{collisions = cube_to_cube(b, a, index1, index2, collisions, true);break;}
	    	    case STEP4D:{collisions = cube_to_cube(a, b, index1, index2, collisions, false);break;}
				case MESH4D:{collisions = mesh_to_cube(a, b, index1, index2, collisions, false);break;}
	    	    case CAPSULE4D:{collisions = capsule_to_cube(a, b, index1, index2, collisions, false);break;}
	    	}
	    	break;
	    }
	    case MESH4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisions = mesh_to_sphere(b, a, index1, index2, collisions, true);break;}
	    	    case BOX4D:{collisions = mesh_to_cube(b, a, index1, index2, collisions, true);break;}
	    	    case STEP4D:{collisions = mesh_to_cube(b, a, index1, index2, collisions, true);break;}
				case MESH4D:{collisions = mesh_to_mesh(a, b, index1, index2, collisions, false);break;}
	    	    case CAPSULE4D:{collisions = capsule_to_cube(a, b, index1, index2, collisions, false);break;}
	    	}
	    	break;
	    }
	    case CAPSULE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisions = capsule_to_sphere(b, a, index1, index2, collisions, true);break;}
	    	    case BOX4D:{collisions = capsule_to_cube(b, a, index1, index2, collisions, true);break;}
	    	    case STEP4D:{collisions = capsule_to_cube(b, a, index1, index2, collisions, true);break;}
				case MESH4D:{collisions = capsule_to_mesh(b, a, index1, index2, collisions, true);break;}
	    	    case CAPSULE4D:{collisions = capsule_to_capsule(a, b, index1, index2, collisions, false);break;}
	    	}
	    	break;
	    }
	}
	return collisions;
}

static vector<Collision> detect_rigidbody_terrain(RigidBody4D* a, Terrain4D* b, int index1, vector<Collision> collisions)
{
	switch (a->colType) {
	case SPHERE4D: { collisions = terrain_to_sphere(b, a, index1, -1, collisions); break; }
	case BOX4D: { collisions = terrain_to_cube(b, a, index1, -1, collisions); break; }
	case STEP4D: { collisions = terrain_to_cube(b, a, index1, -1, collisions); break; }
	case MESH4D: { collisions = terrain_to_mesh(b, a, index1, -1, collisions); break; }
	case CAPSULE4D: { collisions = terrain_to_capsule(b, a, index1, -1, collisions); break; }
	}
	return collisions;
}

static vector<Collision> detect_rigidbody_edge(RigidBody4D* a, int index1, vector<Collision> collisions)
{
	switch (a->colType){
	case SPHERE4D:{collisions = sphere_to_edge(a, index1, -1, collisions);break;}
	case BOX4D:{collisions = cube_to_edge(a, index1, -1, collisions);break;}
	case STEP4D:{collisions = cube_to_edge(a, index1, -1, collisions);break;}
	case MESH4D:{collisions = mesh_to_edge(a, index1, -1, collisions);break;}
	case CAPSULE4D:{collisions = capsule_to_edge(a, index1, -1, collisions);break;}
	}
	return collisions;
}