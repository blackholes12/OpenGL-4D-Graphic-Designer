#pragma once
#include "colliderPhy.cu"

__device__ static struct _d_ContactState
{
	vec4 contactPosA;
	vec4 contactPosB;
	float bias;
	mat4x3 orthonormalBasisInv;
	vec4 orthonormalBasisImpulse;
};

__device__ static struct _d_CollisionConstraint
{
	mat4 orthonormalBasis;
	_d_ContactState contacts;
	float mu;
};

__device__ static struct _d_Constraint
{
	int index1;
	int index2;//-1 collide with edge
	_d_CollisionConstraint collisionConstraint;
	vec4 impulse;
	float momentInertiaScalarA;
	float momentInertiaScalarB;
	float impulseMagAdd;
	float maxImpulseAdd;
	//__device__ explicit {int index1, int index2, _d_CollisionConstraint collisionConstraint)
	//{
	//	this->index1 = index1;
	//	this->index2 = index2;
	//	this->collisionConstraint = collisionConstraint;
	//	this->impulses.x = vec4(0.f);
	//	this->impulses.y = vec4(0.f);
	//	this->impulses.z = vec4(0.f);
	//	this->impulses.w = vec4(0.f);
	//	this->momentInertiaScalarA = 0.f;
	//	this->momentInertiaScalarB = 0.f;
	//	this->impulseMag = 0.f;
	//	this->maxImpulse = 0.f;
	//}
};

__device__ static float inverse_mass_term(_d_RigidBody4D body,
	vec4 normal,
	vec4 bodyContact)
{
	// n' = ~R n R
	vec4 bodyNormal(world_vec_to_body(body, normal));

	// n . (R x . I_b^-1(x /\ n') ~R)
	return dot(bodyNormal,
		left_contract_bv(
			bodyContact - body.massCenter,
			wedge_v(
				bodyContact - body.massCenter,
				bodyNormal
			)
		)
	);
}

__device__ static _d_CollisionConstraint collision_constraint(
	_d_CollisionManifold manifold,
	_d_RigidBody4D a,
	float massAdjustmentA,
	float a_friction,
	_d_RigidBody4D b,
	float massAdjustmentB,
	float b_friction) {
	float e(a.restitution * b.restitution);
	float friction(a_friction * b_friction);
	mat4 orthonormalBasis;
	orthonormal_basis(orthonormalBasis.w = manifold.normal, &orthonormalBasis.x, &orthonormalBasis.y, &orthonormalBasis.z);
	vec4 relVel(vel_at(b, manifold.contactPosB) - vel_at(a, manifold.contactPosA));
	float relVelNormal(dot(relVel, manifold.normal));
	float slop(0.005f);
	float baumgarte(0.5775f);
	float bias(baumgarte * 60.f * _d_max(manifold.depth - slop, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass(a.mass > 0.f ? massAdjustmentA / a.mass : 0.f);
	float invBMass(b.mass > 0.f ? massAdjustmentB / b.mass : 0.f);
	mat4x3 orthonormalBasisInv;
	for (int i(0); i < 4; i++) {
		float invLA(massAdjustmentA * inverse_mass_term(a, orthonormalBasis[i], manifold.contactPosA));
		float invLB(massAdjustmentB * inverse_mass_term(b, orthonormalBasis[i], manifold.contactPosB));
		orthonormalBasisInv.value(i, vec3(invAMass + invBMass, invLA, invLB));
	}
	return { orthonormalBasis, {manifold.contactPosA, manifold.contactPosB, bias, orthonormalBasisInv, vec4(0.f)}, friction };
}

__device__ static _d_CollisionConstraint collision_constraint(
	_d_CollisionManifold manifold,
	_d_RigidBody4D a,
	float massAdjustmentA,
	float a_friction,
	float b_friction,
	float b_restitution) {
	float e(a.restitution * b_restitution);
	float friction(a_friction * b_friction);
	mat4 orthonormalBasis;
	orthonormal_basis(orthonormalBasis.w = manifold.normal, &orthonormalBasis.x, &orthonormalBasis.y, &orthonormalBasis.z);
	vec4 relVel(-vel_at(a, manifold.contactPosA));
	float relVelNormal(dot(relVel, manifold.normal));
	float slop(0.005f);
	float baumgarte(0.5775f);
	float bias(baumgarte * 60.f * _d_max(manifold.depth - slop, 0.f) + (relVelNormal < -1.f ? -e * relVelNormal : 0.f));
	float invAMass(a.mass > 0.f ? massAdjustmentA / a.mass : 0.f);
	mat4x3 orthonormalBasisInv;
	for (int i(0); i < 4; i++) {
		float invLA(massAdjustmentA * inverse_mass_term(a, orthonormalBasis[i], manifold.contactPosA));
		orthonormalBasisInv.value(i, vec3(invAMass, invLA, 0.f));
	}
	return { orthonormalBasis ,{manifold.contactPosA, manifold.contactPosB, bias, orthonormalBasisInv, vec4(0.f)}, friction };
}

__device__ static void solve(float* cF, int index, _d_RigidBody4D a, int index1, _d_RigidBody4D b, int index2, float* velocitys4D, float* angularVelocitys4D)
{
	vec4 relVel(vel_at(b, index2, velocitys4D, angularVelocitys4D, vec4(cF[index + 20], cF[index + 21], cF[index + 22], cF[index + 23])) - vel_at(a, index1, velocitys4D, angularVelocitys4D, vec4(cF[index + 16], cF[index + 17], cF[index + 18], cF[index + 19])));
	vec4 newImpulses;
	cF[index + 46] = get_moment_inertia_scalar(a, bivec4(angularVelocitys4D[6 * index1], angularVelocitys4D[6 * index1 + 1], angularVelocitys4D[6 * index1 + 2], angularVelocitys4D[6 * index1 + 3], angularVelocitys4D[6 * index1 + 4], angularVelocitys4D[6 * index1 + 5]));
	cF[index + 47] = get_moment_inertia_scalar(b, bivec4(angularVelocitys4D[6 * index2], angularVelocitys4D[6 * index2 + 1], angularVelocitys4D[6 * index2 + 2], angularVelocitys4D[6 * index2 + 3], angularVelocitys4D[6 * index2 + 4], angularVelocitys4D[6 * index2 + 5]));
	vec4 orthonormalBasisLambda;
	orthonormalBasisLambda.x = dot(-relVel, vec4(cF[index], cF[index + 1], cF[index + 2], cF[index + 3])) / (cF[index + 25] + (cF[index + 46] > 0.f ? cF[index + 26] / cF[index + 46] : 0.f) + (cF[index + 47] > 0.f ? cF[index + 27] / cF[index + 47] : 0.f));
	orthonormalBasisLambda.y = dot(-relVel, vec4(cF[index + 4], cF[index + 5], cF[index + 6], cF[index + 7])) / (cF[index + 28] + (cF[index + 46] > 0.f ? cF[index + 29] / cF[index + 46] : 0.f) + (cF[index + 47] > 0.f ? cF[index + 30] / cF[index + 47] : 0.f));
	orthonormalBasisLambda.z = dot(-relVel, vec4(cF[index + 8], cF[index + 9], cF[index + 10], cF[index + 11])) / (cF[index + 31] + (cF[index + 46] > 0.f ? cF[index + 32] / cF[index + 46] : 0.f) + (cF[index + 47] > 0.f ? cF[index + 33] / cF[index + 47] : 0.f));
	orthonormalBasisLambda.w = (dot(-relVel, vec4(cF[index + 12], cF[index + 13], cF[index + 14], cF[index + 15])) + cF[index + 24]) / (cF[index + 34] + (cF[index + 46] > 0.f ? cF[index + 35] / cF[index + 46] : 0.f) + (cF[index + 47] > 0.f ? cF[index + 36] / cF[index + 47] : 0.f));
	newImpulses.x = cF[index + 37] + orthonormalBasisLambda.x;
	newImpulses.y = cF[index + 38] + orthonormalBasisLambda.y;
	newImpulses.z = cF[index + 39] + orthonormalBasisLambda.z;
	newImpulses.w = _d_max(cF[index + 40] + orthonormalBasisLambda.w, 0.f);
	float maxImpulse(_d_abs(cF[index + 41] * cF[index + 40]));
	float impulseMag(length(vec3(newImpulses.x, newImpulses.y, newImpulses.z)));
	cF[index + 48] = cF[index + 48] + impulseMag;
	cF[index + 49] = cF[index + 49] + 1.05f * maxImpulse;
	if (impulseMag > maxImpulse)
	{
		float factor(maxImpulse / impulseMag);
		for (int j(0); j < 3; j++)
		{
			newImpulses.value(j, newImpulses[j] * factor);
		}
	}
	float prevImpulse(cF[index + 40]);
	cF[index + 40] = _d_max(prevImpulse + orthonormalBasisLambda.w, 0.f);
	vec4 impulse = vec4(cF[index], cF[index + 1], cF[index + 2], cF[index + 3]) * (newImpulses.x - cF[index + 37]);
	impulse = impulse + vec4(cF[index + 4], cF[index + 5], cF[index + 6], cF[index + 7]) * (newImpulses.y - cF[index + 38]);
	impulse = impulse + vec4(cF[index + 8], cF[index + 9], cF[index + 10], cF[index + 11]) * (newImpulses.z - cF[index + 39]);
	impulse = impulse + vec4(cF[index + 12], cF[index + 13], cF[index + 14], cF[index + 15]) * (cF[index + 40] - prevImpulse);
	cF[index + 42] = impulse.x, cF[index + 43] = impulse.y, cF[index + 44] = impulse.z, cF[index + 45] = impulse.w;
	for (int j(0); j < 4; j++) {
		cF[index + 37 + j] = newImpulses[j];
	}
	resolve_impulse(a, index1, velocitys4D, angularVelocitys4D, -impulse, vec4(cF[index + 16], cF[index + 17], cF[index + 18], cF[index + 19]), cF[index + 46]);
	resolve_impulse(b, index2, velocitys4D, angularVelocitys4D, impulse, vec4(cF[index + 20], cF[index + 21], cF[index + 22], cF[index + 23]), cF[index + 47]);
}

__device__ static void solve(float* cF, int index, _d_RigidBody4D a, int index1, float* velocitys4D,float* angularVelocitys4D)
{
	vec4 relVel(-vel_at(a, index1, velocitys4D, angularVelocitys4D, vec4(cF[index + 16], cF[index + 17], cF[index + 18], cF[index + 19])));
	vec4 newImpulses;
	cF[index + 46] = get_moment_inertia_scalar(a, bivec4(angularVelocitys4D[6 * index1], angularVelocitys4D[6 * index1 + 1], angularVelocitys4D[6 * index1 + 2], angularVelocitys4D[6 * index1 + 3], angularVelocitys4D[6 * index1 + 4], angularVelocitys4D[6 * index1 + 5]));
	vec4 orthonormalBasisLambda;
	orthonormalBasisLambda.x = dot(-relVel, vec4(cF[index], cF[index + 1], cF[index + 2], cF[index + 3])) / (cF[index + 25] + (cF[index + 46] > 0.f ? cF[index + 26] / cF[index + 46] : 0.f));
	orthonormalBasisLambda.y = dot(-relVel, vec4(cF[index + 4], cF[index + 5], cF[index + 6], cF[index + 7])) / (cF[index + 28] + (cF[index + 46] > 0.f ? cF[index + 29] / cF[index + 46] : 0.f));
	orthonormalBasisLambda.z = dot(-relVel, vec4(cF[index + 8], cF[index + 9], cF[index + 10], cF[index + 11])) / (cF[index + 31] + (cF[index + 46] > 0.f ? cF[index + 32] / cF[index + 46] : 0.f));
	orthonormalBasisLambda.w = (dot(-relVel, vec4(cF[index + 12], cF[index + 13], cF[index + 14], cF[index + 15])) + cF[index + 24]) / (cF[index + 34] + (cF[index + 46] > 0.f ? cF[index + 35] / cF[index + 46] : 0.f));
	newImpulses.x = cF[index + 37] + orthonormalBasisLambda.x;
	newImpulses.y = cF[index + 38] + orthonormalBasisLambda.y;
	newImpulses.z = cF[index + 39] + orthonormalBasisLambda.z;
	newImpulses.w = _d_max(cF[index + 40] + orthonormalBasisLambda.w, 0.f);
	float maxImpulse(_d_abs(cF[index + 41] * cF[index + 40]));
	float impulseMag(length(vec3(newImpulses.x, newImpulses.y, newImpulses.z)));
	cF[index + 48] = cF[index + 48] + impulseMag;
	cF[index + 49] = cF[index + 49] + 1.05f*maxImpulse;
	if (impulseMag > maxImpulse)
	{
		float factor(maxImpulse / impulseMag);
		for (int j(0); j < 3; j++)
		{
			newImpulses.value(j, newImpulses[j] * factor);
		}
	}
	float prevImpulse(cF[index + 40]);
	cF[index + 40] = _d_max(prevImpulse + orthonormalBasisLambda.w, 0.f);
	vec4 impulse =      vec4(cF[index], cF[index + 1], cF[index + 2], cF[index + 3]) * (newImpulses.x - cF[index + 37]);
	impulse = impulse + vec4(cF[index + 4], cF[index + 5], cF[index + 6], cF[index + 7]) * (newImpulses.y - cF[index + 38]);
	impulse = impulse + vec4(cF[index + 8], cF[index + 9], cF[index + 10], cF[index + 11]) * (newImpulses.z - cF[index + 39]);
	impulse = impulse + vec4(cF[index + 12], cF[index + 13], cF[index + 14], cF[index + 15]) * (cF[index + 40] - prevImpulse);
	cF[index + 42] = impulse.x, cF[index + 43] = impulse.y, cF[index + 44] = impulse.z, cF[index + 45] = impulse.w;
	for (int j(0); j < 4; j++) {
		cF[index + 37 + j] = newImpulses[j];
	}
	resolve_impulse(a, index1, velocitys4D, angularVelocitys4D, -impulse, vec4(cF[index + 16], cF[index + 17], cF[index + 18], cF[index + 19]), cF[index + 46]);
}

__device__ static void get_constraint(
	_d_RigidBody4D a,
	_d_RigidBody4D b,
	_d_Collision collision,
	_d_Constraint* constraint)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		*constraint = { collision.index1, collision.index2, collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY : a.mu, b, collision.massAdjustmentB, collision.type == 0 ? INFINITY : b.mu) };
	}
}

__device__ static void solve_rigidbody_rigidbody(_d_RigidBody4D a,int index1,
	_d_RigidBody4D b, int index2, float* velocitys4D, float* angularVelocitys4D,
	float* cF, int index)
{
	solve(cF, index, a, index1, b, index2, velocitys4D, angularVelocitys4D);
}

__device__ static void get_constraint_of_wall(
	_d_RigidBody4D a,
	_d_RigidBody4D b,
	_d_Collision collision,
	_d_Constraint* constraint)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		*constraint = { collision.index1, collision.index2, collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY : a.mu, collision.type == 0 ? INFINITY : b.mu, b.restitution) };
	}
}

__device__ static void solve_rigidbody_wall(
	_d_RigidBody4D a, int index1, float* velocitys4D, float* angularvelocitys4D,
	float* cF, int index)
{
	solve(cF, index, a, index1, velocitys4D, angularvelocitys4D);
}

__device__ static void get_constraint(
	_d_RigidBody4D a,
	_d_Collision collision,
	_d_Constraint* constraint)
{
	if (collision.collisionManifold.depth > 0.f)
	{
		*constraint = { collision.index1, -1, collision_constraint(collision.collisionManifold, a, collision.massAdjustmentA, collision.type == 0 ? INFINITY : a.mu, collision.type == 0 ? INFINITY : 0.7f, 0.25f) };
	}
}

__device__ static void solve_rigidbody_edge(
	_d_RigidBody4D a, int index1, float* velocitys4D, float* angularvelocitys4D,
	float* cF, int index)
{
	solve(cF, index, a, index1, velocitys4D, angularvelocitys4D);
}

__device__ static void detect_rigidbody_or_wall(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size)
{
	if(b.colType == 3)//SPHERE4D: {
	{
		if(a.colType==3){ sphere_to_sphere(index1, index2, a, b, collisions, size, false); }
		else if(a.colType==1){ cube_to_sphere(index1, index2, a, b, collisions, size, false); }
		else if(a.colType==2){ cube_to_sphere(index1, index2, a, b, collisions, size, false); }
		else if(a.colType==4){ mesh_to_sphere(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==5){ capsule_to_sphere(index1, index2, a, b, collisions, size, false); }
	}
	else if (b.colType == 1)//BOX4D
	{
		if(a.colType==3){ cube_to_sphere(index1, index2, b, a, collisions, size, true); }
		else if(a.colType==1){ cube_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==2){ cube_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==4){ mesh_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==5){ capsule_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
	}
	else if (b.colType == 2)//STEP4D: {
	{
		if(a.colType==3){ cube_to_sphere(index1, index2, b, a, collisions, size, true); }
		else if(a.colType==1){ cube_to_cube(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==2){ cube_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==4){ mesh_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==5){ capsule_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
	}
    else if (b.colType == 4)//MESH4D: {
	{
		if(a.colType==3){ mesh_to_sphere(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==1){ mesh_to_cube(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==2){ mesh_to_cube(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==4){ mesh_to_mesh(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
		else if(a.colType==5){ capsule_to_cube(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
	}
	else if (b.colType == 5)//CAPSULE4D: {
	{
		if(a.colType==3){ capsule_to_sphere(index1, index2, b, a, collisions, size, true); }
		else if(a.colType==1){ capsule_to_cube(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==2){ capsule_to_cube(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==4){ capsule_to_mesh(index1, index2, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, true); }
		else if(a.colType==5){ capsule_to_capsule(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size, false); }
	}
}

__device__ static void detect_rigidbody_edge(int index1, _d_RigidBody4D a, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size)
{
	if(a.colType == 3){ sphere_to_half_space(index1, -1, a, collisions, size); }
	else if(a.colType == 1){ cube_to_half_space(index1, -1, a, collisions, size); }
	else if(a.colType == 2){ cube_to_half_space(index1, -1, a, collisions, size); }
	else if(a.colType == 4){ mesh_to_half_space(index1, -1, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, size); }
	else if(a.colType == 5){ capsule_to_half_space(index1, -1, a, collisions, size); }
}