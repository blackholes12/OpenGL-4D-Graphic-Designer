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

static void solve(std::vector <Constraint*>* cs, RigidBody4D* a, RigidBody4D* b)
{
	for (Constraint* c : *cs)
	{
		CollisionConstraint* c2 = &c->collisionConstraint;
		glm::vec4 relVel(vel_at(b, c2->contacts.contactPos) - vel_at(a, c2->contacts.contactPos));
		float newImpulses[3];
		for (int i(0); i < 3; i++)
		{
			float lambda(dot(-relVel, c2->tangents.tangent(i)) * c2->contacts.tangentMass[i]);
			newImpulses[i] = c2->contacts.tangentImpulse[i] + lambda;
		}
		float max_impulse(abs(c2->mu * c2->contacts.normalImpulse));
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
			glm::vec4 impulse(c2->tangents.tangent(i) * (newImpulses[i] - c2->contacts.tangentImpulse[i]));
			c2->contacts.tangentImpulse[i] = newImpulses[i];
			resolve_impulse0(a, -impulse, c2->contacts.contactPos);
			resolve_impulse0(b, impulse, c2->contacts.contactPos);
		}
		// calculate normal impulse
		float relVelNormal(dot(relVel, c2->normal));
		float lambda0(c2->contacts.normalMass * (-relVelNormal + c2->contacts.bias));
		float prevImpulse(c2->contacts.normalImpulse);
		c2->contacts.normalImpulse = max(prevImpulse + lambda0, 0.f);
		glm::vec4 impulse(c2->normal * (c2->contacts.normalImpulse - prevImpulse));
		resolve_impulse0(a, -impulse, c2->contacts.contactPos);
		resolve_impulse0(b, impulse, c2->contacts.contactPos);
	}
}

static void solve(std::vector <Constraint*>* cs, RigidBody4D* b)
{
	for (Constraint* c : *cs)
	{
		CollisionConstraint* c2 = &c->collisionConstraint;
	    glm::vec4 relVel(vel_at(b, c2->contacts.contactPos));
	    float newImpulses[3];
	    for (int i(0); i < 3; i++)
	    {
	    	float lambda(dot(-relVel, c2->tangents.tangent(i)) * c2->contacts.tangentMass[i]);
	    	newImpulses[i] = c2->contacts.tangentImpulse[i] + lambda;
	    }
	    float max_impulse(abs(c2->mu * c2->contacts.normalImpulse));
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
	    	glm::vec4 impulse(c2->tangents.tangent(i) * (newImpulses[i] - c2->contacts.tangentImpulse[i]));
	    	c2->contacts.tangentImpulse[i] = newImpulses[i];
	    	resolve_impulse0(b, impulse, c2->contacts.contactPos);
	    }
	    // calculate normal impulse
	    float relVelNormal(dot(relVel, c2->normal));
	    float lambda0(c2->contacts.normalMass * (-relVelNormal + c2->contacts.bias));
	    float prevImpulse(c2->contacts.normalImpulse);
	    c2->contacts.normalImpulse = max(prevImpulse + lambda0, 0.f);
	    glm::vec4 impulse(c2->normal * (c2->contacts.normalImpulse - prevImpulse));
	    resolve_impulse0(b, impulse, c2->contacts.contactPos);
	}
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	RigidBody4D* b,
	std::vector < Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for(Collision collision: collisions)
		constraints.push_back(new Constraint(index1,index2,collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, a->mu, b, collision.massAdjustmentB, b->mu)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c=nullptr,free(c);
	}
}

static void solve_rigidbody_rigidbody(RigidBody4D* a,
	RigidBody4D* b,
	std::vector<Constraint*>* constraint)
{
	solve(constraint, b, a);
}

static void update_billiards(RigidBody4D* a,
	RigidBody4D* b,
	Collision collision)
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
	std::vector < Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for (Collision collision : collisions)
		constraints.push_back(new Constraint(index1, index2,collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, b->mu, b->restitution)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c = nullptr, free(c);
	}
}

static void solve_rigidbody_wall(
	RigidBody4D* a,
	Object4D* b,
	std::vector<Constraint*>* constraints)
{
	solve(constraints, a);
}

static void update_billiards(
	RigidBody4D* a,
	Object4D* b,
	Collision collision)
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
	std::vector < Collision> collisions,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	if (collisions[0].collisionManifold.depth > 0.f)
	{
		std::vector<Constraint*> constraints;
		for (Collision collision : collisions)
		constraints.push_back(new Constraint(index1, -1, collisionConstraint(collision.collisionManifold, a, collision.massAdjustmentA, 1.6f, 0.25f)));
		constraintsVec->push_back(constraints);
		for (Constraint* c : constraints)c = nullptr, free(c);
	}
}

static void solve_rigidbody_edge(RigidBody4D* a,
	std::vector<Constraint*>* constraints)
{
	solve(constraints, a);
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	RigidBody4D* b,
	std::vector < HingeConstraint4D> hs,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	std::vector<Constraint*> constraints;
	for (HingeConstraint4D h : hs)
	{
		glm::vec4 worldPosition1(body_pos_to_world(a, h.bodyPosition4D1));
		glm::vec4 worldPosition2(body_pos_to_world(b, h.bodyPosition4D2));
		glm::vec4 normal4D0(worldPosition1 - worldPosition2);
		glm::vec4 normal4D(normalize(normal4D0));
		float depth(length(normal4D0));
		if (depth > 0.f)
		{
			glm::vec4 contacts((worldPosition1 + worldPosition2) / 2.f);
			constraints.push_back(new Constraint(index1, index2, collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, b, 1.f, INFINITY)));
		}
	}
	constraintsVec->push_back(constraints);
	for (Constraint* c : constraints)c = nullptr, free(c);
}

static void solve_rigidbody_rigidbody2(
	RigidBody4D* a,
	RigidBody4D* b,
	std::vector<Constraint*>* constraints)
{
	solve(constraints, a, b);
}

static void get_constraint(
	int index1,
	int index2,
	RigidBody4D* a,
	Object4D* b,
	std::vector < HingeConstraint4D> hs,
	std::vector <std::vector<Constraint*>>* constraintsVec,
	bool isInverse)
{
	std::vector<Constraint*> constraints;
	for (HingeConstraint4D h : hs)
	{
		glm::vec4 normal4D0;
		glm::vec4 worldPosition1;
		glm::vec4 worldPosition2;
		if (!isInverse)
		{
			worldPosition1 = body_pos_to_world(b, h.bodyPosition4D2);
			worldPosition2 = body_pos_to_world(a, h.bodyPosition4D1);
		}
		if (isInverse)
		{
			worldPosition1 = body_pos_to_world(b, h.bodyPosition4D1);
			worldPosition2 = body_pos_to_world(a, h.bodyPosition4D2);
		}
		normal4D0 = worldPosition1 - worldPosition2;
		float depth(length(normal4D0));
		if (depth > 0.f)
		{
			glm::vec4 normal4D(normalize(normal4D0));
			glm::vec4 contacts((worldPosition1 + worldPosition2) / 2.f);
			constraints.push_back(new Constraint(index1, index2, collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, 0.f)));
		}
	}
	constraintsVec->push_back(constraints);
	for (Constraint* c : constraints)c = nullptr, free(c);
}

static void solve_rigidbody_wall2(RigidBody4D* a,
	Object4D* b,
	std::vector<Constraint*>* constraints)
{
	solve(constraints, a);
}

static void get_constraint(
	int index1,
	RigidBody4D* a,
	std::vector < HingeConstraint4D> hs,
	std::vector <std::vector<Constraint*>>* constraintsVec)
{
	std::vector<Constraint*> constraints;
	for (HingeConstraint4D h : hs)
	{
		glm::vec4 worldPosition4D2(body_pos_to_world(a, h.bodyPosition4D1));
		glm::vec4 normal4D0(h.worldPosition4D - worldPosition4D2);
		float depth(length(normal4D0));
		if (depth > 0.f)
		{
			glm::vec4 normal4D(normalize(normal4D0));
			glm::vec4 contacts((h.worldPosition4D + worldPosition4D2) / 2.f);
			constraints.push_back(new Constraint(index1, -1, collisionConstraint(CollisionManifold(normal4D, depth, contacts), a, 1.f, INFINITY, 0.f)));
		}
	}
	constraintsVec->push_back(constraints);
	for (Constraint* c : constraints)c = nullptr, free(c);
}

static void solve_rigidbody2(RigidBody4D* a,
	std::vector<Constraint*>* constraints)
{
	solve(constraints, a);
}

static std::vector<std::vector<Collision>> detect_rigidbody_or_wall(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (b->colType){
	    case SPHERE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = sphere_to_sphere(a, b, index1, index2, collisionsVec, false);break;}
	    	    case BOX4D:{collisionsVec = cube_to_sphere(a, b, index1, index2, collisionsVec, false);break;}
	    	    case STEP4D:{collisionsVec = cube_to_sphere(a, b, index1, index2, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_sphere(a, b, index1, index2, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_sphere(a, b, index1, index2, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case BOX4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = cube_to_sphere(b, a, index1, index2, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = cube_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	    case STEP4D:{collisionsVec = cube_to_cube(a, b, index1, index2, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case STEP4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = cube_to_sphere(b, a, index1, index2, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = cube_to_cube(b, a, index1, index2, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = cube_to_cube(a, b, index1, index2, collisionsVec, false);break;}
				case MESH4D:{collisionsVec = mesh_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case MESH4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = mesh_to_sphere(b, a, index1, index2, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = mesh_to_cube(b, a, index1, index2, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = mesh_to_cube(b, a, index1, index2, collisionsVec, true);break;}
				case MESH4D:{collisionsVec = mesh_to_mesh(a, b, index1, index2, collisionsVec, false);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_cube(a, b, index1, index2, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	    case CAPSULE4D:{
	    	switch (a->colType){
	    	    case SPHERE4D:{collisionsVec = capsule_to_sphere(b, a, index1, index2, collisionsVec, true);break;}
	    	    case BOX4D:{collisionsVec = capsule_to_cube(b, a, index1, index2, collisionsVec, true);break;}
	    	    case STEP4D:{collisionsVec = capsule_to_cube(b, a, index1, index2, collisionsVec, true);break;}
				case MESH4D:{collisionsVec = capsule_to_mesh(b, a, index1, index2, collisionsVec, true);break;}
	    	    case CAPSULE4D:{collisionsVec = capsule_to_capsule(a, b, index1, index2, collisionsVec, false);break;}
	    	}
	    	break;
	    }
	}
	return collisionsVec;
}

static std::vector<std::vector<Collision>> detect_rigidbody_terrain(RigidBody4D* a, Terrain4D* b, int index1, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (a->colType) {
	case SPHERE4D: { collisionsVec = terrain_to_sphere(b, a, index1, -1, collisionsVec); break; }
	case BOX4D: { collisionsVec = terrain_to_cube(b, a, index1, -1, collisionsVec); break; }
	case STEP4D: { collisionsVec = terrain_to_cube(b, a, index1, -1, collisionsVec); break; }
	case MESH4D: { collisionsVec = terrain_to_mesh(b, a, index1, -1, collisionsVec); break; }
	case CAPSULE4D: { collisionsVec = terrain_to_capsule(b, a, index1, -1, collisionsVec); break; }
	}
	return collisionsVec;
}

static std::vector<std::vector<Collision>> detect_rigidbody_edge(RigidBody4D* a, int index1, std::vector<std::vector<Collision>> collisionsVec)
{
	switch (a->colType){
	case SPHERE4D:{collisionsVec = sphere_to_half_space(a, index1, -1, collisionsVec);break;}
	case BOX4D:{collisionsVec = cube_to_half_space(a, index1, -1, collisionsVec);break;}
	case STEP4D:{collisionsVec = cube_to_half_space(a, index1, -1, collisionsVec);break;}
	case MESH4D:{collisionsVec = mesh_to_half_space(a, index1, -1, collisionsVec);break;}
	case CAPSULE4D:{collisionsVec = capsule_to_half_space(a, index1, -1, collisionsVec);break;}
	}
	return collisionsVec;
}