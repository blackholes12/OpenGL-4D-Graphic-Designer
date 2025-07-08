#pragma once
#include "Game.h"
#include "phyFunction.cu"
__device__ static _d_RigidBody4D copy_data_to_rigid_body(
	int index,
	bool isRigidBody,
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	bool* isGravitys,
	bool* isStatics,
	bool* isSleeps,
	bool* isContinueSleeps,
	int* sizesOfForces,
	int* forceStartIndices,
	float* masss,
	float* momentInertiaScalars,
	float* restitutions,
	float* mus,
	float* massCenters,
	float* velocitys4D,
	float* angularVelocitys4D,
	int* colTypes,
	int* primitiveIds
)
{
	if (isRigidBody)
	{
		vec4 position4d = vec4(positions4D[4 * index], positions4D[4 * index + 1], positions4D[4 * index + 2], positions4D[4 * index + 3]);
		rotor4 rotation4D = rotor4(rotations4D[8 * index], bivec4(rotations4D[8 * index + 1], rotations4D[8 * index + 2], rotations4D[8 * index + 3], rotations4D[8 * index + 4], rotations4D[8 * index + 5], rotations4D[8 * index + 6]), quadvec4(rotations4D[8 * index + 7]));
		vec4 scale4D = vec4(scales4D[4 * index], scales4D[4 * index + 1], scales4D[4 * index + 2], scales4D[4 * index + 3]);
		bool isGravity = isGravitys[index];
		bool isStatic = isStatics[index];
		bool isSleep = isSleeps[index];
		bool isContinueSleep = isContinueSleeps[index];
		int sizeOfForces = sizesOfForces[index];
		int forcesStartIndex = forceStartIndices[index];
		float mass = masss[index];
		float momentInertiaScalar = momentInertiaScalars[index];
		float restitution = restitutions[index];
		float mu = mus[index];
		vec4 massCenter = vec4(massCenters[4 * index], massCenters[4 * index + 1], massCenters[4 * index + 2], massCenters[4 * index + 3]);
		vec4 velocity4d = vec4(velocitys4D[4 * index], velocitys4D[4 * index + 1], velocitys4D[4 * index + 2], velocitys4D[4 * index + 3]);
		bivec4 angularVelocity4D = bivec4(angularVelocitys4D[6 * index], angularVelocitys4D[6 * index + 1], angularVelocitys4D[6 * index + 2], angularVelocitys4D[6 * index + 3], angularVelocitys4D[6 * index + 4], angularVelocitys4D[6 * index + 5]);
		int colType = colTypes[index];
		int primitiveId = primitiveIds[index];
		return _d_RigidBody4D(position4d, rotation4D, scale4D, isGravity, isStatic, isSleep, isContinueSleep, sizeOfForces, forcesStartIndex, mass, momentInertiaScalar, restitution, mu, massCenter, velocity4d, angularVelocity4D, colType, primitiveId);
	}
	else
	{
		vec4 position4d = vec4(positions4D[4 * index], positions4D[4 * index + 1], positions4D[4 * index + 2], positions4D[4 * index + 3]);
		rotor4 rotation4D = rotor4(rotations4D[8 * index], bivec4(rotations4D[8 * index + 1], rotations4D[8 * index + 2], rotations4D[8 * index + 3], rotations4D[8 * index + 4], rotations4D[8 * index + 5], rotations4D[8 * index + 6]), quadvec4(rotations4D[8 * index + 7]));
		vec4 scale4D = vec4(scales4D[4 * index], scales4D[4 * index + 1], scales4D[4 * index + 2], scales4D[4 * index + 3]);
		float restitution = restitutions[index];
		float mu = mus[index];
		int colType = colTypes[index];
		int primitiveId = primitiveIds[index];
		return _d_RigidBody4D(position4d, rotation4D, scale4D, restitution, mu, colType, primitiveId);
	}
}

__device__ static _d_RigidBody4D copy_data_to_wall(
	int index,
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	float* restitutions,
	float* mus,
	int* colTypes,
	int* primitiveIds
)
{
	vec4 position4d = vec4(positions4D[4 * index], positions4D[4 * index + 1], positions4D[4 * index + 2], positions4D[4 * index + 3]);
	rotor4 rotation4D = rotor4(rotations4D[8 * index], bivec4(rotations4D[8 * index + 1], rotations4D[8 * index + 2], rotations4D[8 * index + 3], rotations4D[8 * index + 4], rotations4D[8 * index + 5], rotations4D[8 * index + 6]), quadvec4(rotations4D[8 * index + 7]));
	vec4 scale4D = vec4(scales4D[4 * index], scales4D[4 * index + 1], scales4D[4 * index + 2], scales4D[4 * index + 3]);
	float restitution = restitutions[index];
	float mu = mus[index];
	int colType = colTypes[index];
	int primitiveId = primitiveIds[index];
	return _d_RigidBody4D(position4d, rotation4D, scale4D, restitution, mu, colType, primitiveId);
}

__device__ static void move_data_from_rigid_body(
	int index,
	_d_RigidBody4D a,
	float* positions4D,
	float* rotations4D,
	bool* isSleeps,
	bool* isContinueSleeps,
	float* velocitys4D,
	float* angularVelocitys4D
)
{
	positions4D[4 * index] = a.position4d.x, positions4D[4 * index + 1] = a.position4d.y, positions4D[4 * index + 2] = a.position4d.z, positions4D[4 * index + 3] = a.position4d.w;
	rotations4D[8 * index] = a.rotation4D.s, rotations4D[8 * index + 1] = a.rotation4D.b.xy, rotations4D[8 * index + 2] = a.rotation4D.b.xz, rotations4D[8 * index + 3] = a.rotation4D.b.xw, rotations4D[8 * index + 4] = a.rotation4D.b.yz, rotations4D[8 * index + 5] = a.rotation4D.b.yw, rotations4D[8 * index + 6] = a.rotation4D.b.zw, rotations4D[8 * index + 7] = a.rotation4D.q.xyzw;
	isSleeps[index] = a.isSleep;
	isContinueSleeps[index] = a.isContinueSleep;
	velocitys4D[4 * index] = a.velocity4d.x, velocitys4D[4 * index + 1] = a.velocity4d.y, velocitys4D[4 * index + 2] = a.velocity4d.z, velocitys4D[4 * index + 3] = a.velocity4d.w;
	angularVelocitys4D[6 * index] = a.angularVelocity4D.xy, angularVelocitys4D[6 * index + 1] = a.angularVelocity4D.xz, angularVelocitys4D[6 * index + 2] = a.angularVelocity4D.xw, angularVelocitys4D[6 * index + 3] = a.angularVelocity4D.yz, angularVelocitys4D[6 * index + 4] = a.angularVelocity4D.yw, angularVelocitys4D[6 * index + 5] = a.angularVelocity4D.zw;
}

__device__ static void move_velocity_data_from_rigid_body(
	int index,
	_d_RigidBody4D a,
	float* velocitys4D,
	float* angularVelocitys4D
)
{
	velocitys4D[4 * index] = a.velocity4d.x, velocitys4D[4 * index + 1] = a.velocity4d.y, velocitys4D[4 * index + 2] = a.velocity4d.z, velocitys4D[4 * index + 3] = a.velocity4d.w;
	angularVelocitys4D[6 * index] = a.angularVelocity4D.xy, angularVelocitys4D[6 * index + 1] = a.angularVelocity4D.xz, angularVelocitys4D[6 * index + 2] = a.angularVelocity4D.xw, angularVelocitys4D[6 * index + 3] = a.angularVelocity4D.yz, angularVelocitys4D[6 * index + 4] = a.angularVelocity4D.yw, angularVelocitys4D[6 * index + 5] = a.angularVelocity4D.zw;
}

__device__ static _d_Constraint copy_data_to_constraint(
	int index,
	int* constraintsVecIntArray,
	float* constraintsVecFloatArray
)
{
	int arrayIndexF = 50 * index;
	return{
	    constraintsVecIntArray[2 * index],
		constraintsVecIntArray[2 * index + 1],
		{{vec4(constraintsVecFloatArray[arrayIndexF],
		constraintsVecFloatArray[arrayIndexF + 1],
		constraintsVecFloatArray[arrayIndexF + 2],
		constraintsVecFloatArray[arrayIndexF + 3]),
		vec4(constraintsVecFloatArray[arrayIndexF + 4],
		constraintsVecFloatArray[arrayIndexF + 5],
		constraintsVecFloatArray[arrayIndexF + 6],
		constraintsVecFloatArray[arrayIndexF + 7]),
		vec4(constraintsVecFloatArray[arrayIndexF + 8],
		constraintsVecFloatArray[arrayIndexF + 9],
		constraintsVecFloatArray[arrayIndexF + 10],
		constraintsVecFloatArray[arrayIndexF + 11]),
		vec4(constraintsVecFloatArray[arrayIndexF + 12],
		constraintsVecFloatArray[arrayIndexF + 13],
		constraintsVecFloatArray[arrayIndexF + 14],
		constraintsVecFloatArray[arrayIndexF + 15])},
		{vec4(constraintsVecFloatArray[arrayIndexF + 16],
		constraintsVecFloatArray[arrayIndexF + 17],
		constraintsVecFloatArray[arrayIndexF + 18],
		constraintsVecFloatArray[arrayIndexF + 19]),
		vec4(constraintsVecFloatArray[arrayIndexF + 20],
		constraintsVecFloatArray[arrayIndexF + 21],
		constraintsVecFloatArray[arrayIndexF + 22],
		constraintsVecFloatArray[arrayIndexF + 23]),
		constraintsVecFloatArray[arrayIndexF + 24],
		{vec3(constraintsVecFloatArray[arrayIndexF + 25],
		constraintsVecFloatArray[arrayIndexF + 26],
		constraintsVecFloatArray[arrayIndexF + 27]),
		vec3(constraintsVecFloatArray[arrayIndexF + 28],
		constraintsVecFloatArray[arrayIndexF + 29],
		constraintsVecFloatArray[arrayIndexF + 30]),
		vec3(constraintsVecFloatArray[arrayIndexF + 31],
		constraintsVecFloatArray[arrayIndexF + 32],
		constraintsVecFloatArray[arrayIndexF + 33]),
		vec3(constraintsVecFloatArray[arrayIndexF + 34],
		constraintsVecFloatArray[arrayIndexF + 35],
		constraintsVecFloatArray[arrayIndexF + 36])},
		vec4(constraintsVecFloatArray[arrayIndexF + 37],
		constraintsVecFloatArray[arrayIndexF + 38],
		constraintsVecFloatArray[arrayIndexF + 39],
		constraintsVecFloatArray[arrayIndexF + 40])},
		constraintsVecFloatArray[arrayIndexF + 41]},
		vec4(constraintsVecFloatArray[arrayIndexF + 42],
		constraintsVecFloatArray[arrayIndexF + 43],
		constraintsVecFloatArray[arrayIndexF + 44],
		constraintsVecFloatArray[arrayIndexF + 45]),
		constraintsVecFloatArray[arrayIndexF + 46],
		constraintsVecFloatArray[arrayIndexF + 47],
		constraintsVecFloatArray[arrayIndexF + 48],
		constraintsVecFloatArray[arrayIndexF + 49]
	};
}

__device__ static void move_data_from_constraint(
	int index,
	_d_Constraint constraint,
	int* constraintsVecIntArray,
	float* constraintsVecFloatArray
)
{
	constraintsVecIntArray[2 * index] = constraint.index1;
	constraintsVecIntArray[2 * index + 1] = constraint.index2;
	int arrayIndexF = 50 * index;
	constraintsVecFloatArray[arrayIndexF] = constraint.collisionConstraint.orthonormalBasis[0].x;
	constraintsVecFloatArray[arrayIndexF + 1] = constraint.collisionConstraint.orthonormalBasis[0].y;
	constraintsVecFloatArray[arrayIndexF + 2] = constraint.collisionConstraint.orthonormalBasis[0].z;
	constraintsVecFloatArray[arrayIndexF + 3] = constraint.collisionConstraint.orthonormalBasis[0].w;
	constraintsVecFloatArray[arrayIndexF + 4] = constraint.collisionConstraint.orthonormalBasis[1].x;
	constraintsVecFloatArray[arrayIndexF + 5] = constraint.collisionConstraint.orthonormalBasis[1].y;
	constraintsVecFloatArray[arrayIndexF + 6] = constraint.collisionConstraint.orthonormalBasis[1].z;
	constraintsVecFloatArray[arrayIndexF + 7] = constraint.collisionConstraint.orthonormalBasis[1].w;
	constraintsVecFloatArray[arrayIndexF + 8] = constraint.collisionConstraint.orthonormalBasis[2].x;
	constraintsVecFloatArray[arrayIndexF + 9] = constraint.collisionConstraint.orthonormalBasis[2].y;
	constraintsVecFloatArray[arrayIndexF + 10] = constraint.collisionConstraint.orthonormalBasis[2].z;
	constraintsVecFloatArray[arrayIndexF + 11] = constraint.collisionConstraint.orthonormalBasis[2].w;
	constraintsVecFloatArray[arrayIndexF + 12] = constraint.collisionConstraint.orthonormalBasis[3].x;
	constraintsVecFloatArray[arrayIndexF + 13] = constraint.collisionConstraint.orthonormalBasis[3].y;
	constraintsVecFloatArray[arrayIndexF + 14] = constraint.collisionConstraint.orthonormalBasis[3].z;
	constraintsVecFloatArray[arrayIndexF + 15] = constraint.collisionConstraint.orthonormalBasis[3].w;
	constraintsVecFloatArray[arrayIndexF + 16] = constraint.collisionConstraint.contacts.contactPosA.x;
	constraintsVecFloatArray[arrayIndexF + 17] = constraint.collisionConstraint.contacts.contactPosA.y;
	constraintsVecFloatArray[arrayIndexF + 18] = constraint.collisionConstraint.contacts.contactPosA.z;
	constraintsVecFloatArray[arrayIndexF + 19] = constraint.collisionConstraint.contacts.contactPosA.w;
	constraintsVecFloatArray[arrayIndexF + 20] = constraint.collisionConstraint.contacts.contactPosB.x;
	constraintsVecFloatArray[arrayIndexF + 21] = constraint.collisionConstraint.contacts.contactPosB.y;
	constraintsVecFloatArray[arrayIndexF + 22] = constraint.collisionConstraint.contacts.contactPosB.z;
	constraintsVecFloatArray[arrayIndexF + 23] = constraint.collisionConstraint.contacts.contactPosB.w;
	constraintsVecFloatArray[arrayIndexF + 24] = constraint.collisionConstraint.contacts.bias;
	constraintsVecFloatArray[arrayIndexF + 25] = constraint.collisionConstraint.contacts.orthonormalBasisInv[0].x;
	constraintsVecFloatArray[arrayIndexF + 26] = constraint.collisionConstraint.contacts.orthonormalBasisInv[0].y;
	constraintsVecFloatArray[arrayIndexF + 27] = constraint.collisionConstraint.contacts.orthonormalBasisInv[0].z;
	constraintsVecFloatArray[arrayIndexF + 28] = constraint.collisionConstraint.contacts.orthonormalBasisInv[1].x;
	constraintsVecFloatArray[arrayIndexF + 29] = constraint.collisionConstraint.contacts.orthonormalBasisInv[1].y;
	constraintsVecFloatArray[arrayIndexF + 30] = constraint.collisionConstraint.contacts.orthonormalBasisInv[1].z;
	constraintsVecFloatArray[arrayIndexF + 31] = constraint.collisionConstraint.contacts.orthonormalBasisInv[2].x;
	constraintsVecFloatArray[arrayIndexF + 32] = constraint.collisionConstraint.contacts.orthonormalBasisInv[2].y;
	constraintsVecFloatArray[arrayIndexF + 33] = constraint.collisionConstraint.contacts.orthonormalBasisInv[2].z;
	constraintsVecFloatArray[arrayIndexF + 34] = constraint.collisionConstraint.contacts.orthonormalBasisInv[3].x;
	constraintsVecFloatArray[arrayIndexF + 35] = constraint.collisionConstraint.contacts.orthonormalBasisInv[3].y;
	constraintsVecFloatArray[arrayIndexF + 36] = constraint.collisionConstraint.contacts.orthonormalBasisInv[3].z;
	constraintsVecFloatArray[arrayIndexF + 37] = constraint.collisionConstraint.contacts.orthonormalBasisImpulse.x;
	constraintsVecFloatArray[arrayIndexF + 38] = constraint.collisionConstraint.contacts.orthonormalBasisImpulse.y;
	constraintsVecFloatArray[arrayIndexF + 39] = constraint.collisionConstraint.contacts.orthonormalBasisImpulse.z;
	constraintsVecFloatArray[arrayIndexF + 40] = constraint.collisionConstraint.contacts.orthonormalBasisImpulse.w;
	constraintsVecFloatArray[arrayIndexF + 41] = constraint.collisionConstraint.mu;
	constraintsVecFloatArray[arrayIndexF + 42] = constraint.impulse.x;
	constraintsVecFloatArray[arrayIndexF + 43] = constraint.impulse.y;
	constraintsVecFloatArray[arrayIndexF + 44] = constraint.impulse.z;
	constraintsVecFloatArray[arrayIndexF + 45] = constraint.impulse.w;
	constraintsVecFloatArray[arrayIndexF + 46] = constraint.momentInertiaScalarA;
	constraintsVecFloatArray[arrayIndexF + 47] = constraint.momentInertiaScalarB;
	constraintsVecFloatArray[arrayIndexF + 48] = constraint.impulseMagAdd;
	constraintsVecFloatArray[arrayIndexF + 49] = constraint.maxImpulseAdd;
}

//__global__ static void apply_forces(
//	float* positions4D, 
//	float* rotations4D, 
//	float* scales4D, 
//	bool* isGravitys,
//	bool* isStatics,
//	bool* isSleeps,
//	bool* isContinueSleeps,
//	float* forceSystems4D,
//	int* sizesOfForces,
//	int* forceStartIndices,
//	float* masss, 
//	float* momentInertiaScalars,
//	float* restitutions,
//	float* mus,
//	float* massCenters,
//	float* velocitys4D,
//	float* angularVelocitys4D,
//	int* colTypes,
//	int* primitiveIds,
//	float dt,
//	int sizeOfRigidBodies
//)
//{
//	int index = blockDim.x * blockIdx.x + threadIdx.x;
//
//}

__global__ static void detect_collision(
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	bool* isGravitys,
	bool* isStatics,
	bool* isSleeps,
	bool* isContinueSleeps,
	int* sizesOfForces,
	int* forceStartIndices,
	float* masss,
	float* momentInertiaScalars,
	float* restitutions,
	float* mus,
	float* massCenters,
	float* velocitys4D,
	float* angularVelocitys4D,
	int* colTypes,
	float* vertices4DsVec,
	int* sizesOfVertices4D,
	int* verticesStartIndices,
	int* primitiveIds,
	int* pairsVec,
	int* sizesOfPairs,
	int* pairsStartIndices,
	int* collisionsVecIntArray,
	float* collisionsVecFloatArray,
	int* sizesOfCollisionsVec,
	float* constraintsVecFloatArray,
	int* pPairsVec,
	int* pSizesOfPairs,
	int* pPairsStartIndices,
	int* pSizesOfCollisionsVec,
	size_t pSizeOfPairs,
	float dt,
	int sizeOfRigidBodies
)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	int index1 = pairsVec[2 * index];
	int index2 = pairsVec[2 * index + 1];
	_d_Collision collisions[32];
	sizesOfCollisionsVec[index] = 0;
	_d_RigidBody4D a = copy_data_to_rigid_body(index1, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
	_d_RigidBody4D b = copy_data_to_rigid_body(_d_max(index2, 0), index2 < sizeOfRigidBodies, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
	if (index2 != -1)
	{
		if (!isStatics[index1])
		{
			detect_rigidbody_or_wall(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
		}
		else if (isStatics[index1] && !isStatics[index2] && index2 < sizeOfRigidBodies)
		{
			detect_rigidbody_or_wall(index2, index1, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
		}
	}
	else
	{
		if (!isStatics[index1])
		{
			detect_rigidbody_edge(index1, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
		}
	}

	//if (sizesOfCollisionsVec[index] > 0)
	//{
	//	for (int j(0); j < 20; j++)
	//	{
	//		for (int i(0); i < sizesOfCollisionsVec[index]; i++)
	//		{
	//			a.position4d = vec4(positions4D[4 * index1], positions4D[4 * index1 + 1], positions4D[4 * index1 + 2], positions4D[4 * index1 + 3]);
	//			a.rotation4D = rotor4(rotations4D[8 * index1], bivec4(rotations4D[8 * index1 + 1], rotations4D[8 * index1 + 2], rotations4D[8 * index1 + 3], rotations4D[8 * index1 + 4], rotations4D[8 * index1 + 5], rotations4D[8 * index1 + 6]), quadvec4(rotations4D[8 * index1 + 7]));
	//			if (index2 < sizeOfRigidBodies)
	//			{
	//				b.position4d = vec4(positions4D[4 * index2], positions4D[4 * index2 + 1], positions4D[4 * index2 + 2], positions4D[4 * index2 + 3]);
	//				b.rotation4D = rotor4(rotations4D[8 * index2], bivec4(rotations4D[8 * index2 + 1], rotations4D[8 * index2 + 2], rotations4D[8 * index2 + 3], rotations4D[8 * index2 + 4], rotations4D[8 * index2 + 5], rotations4D[8 * index2 + 6]), quadvec4(rotations4D[8 * index2 + 7]));
	//			}
	//			vec4 contactPosAToWorld = body_pos_to_world(a, collisions[i].collisionManifold.contactPosA);
	//			vec4 contactPosBToWorld = body_pos_to_world(b, collisions[i].collisionManifold.contactPosB);
	//			vec4 aB = contactPosAToWorld - contactPosBToWorld;
	//			if (aB != vec4(0.f))
	//			{
	//				vec4 force4D = normalize(aB);
	//				vec4 velocity4DA = (a.mass > 0.f ? -force4D / a.mass : vec4(0.f));
	//				vec4 velocity4DB;
	//				if (index2 < sizeOfRigidBodies|| !isStatics[index2])velocity4DB = (b.mass > 0.f ? force4D / b.mass : vec4(0.f));
	//				else velocity4DB = vec4(0.f);
	//				//bivec4 angularVelocity4DA(wedge_v(collisions[i].collisionManifold.contactPosA - a.massCenter, rotate(a.rotation4D.reverse(), -force4D)));
	//				//bivec4 angularVelocity4DB(wedge_v(collisions[i].collisionManifold.contactPosB - b.massCenter, rotate(b.rotation4D.reverse(), force4D)));
	//				//float momentInertiaScalarA(get_moment_inertia_scalar(a, angularVelocity4DA));
	//				//float momentInertiaScalarB(get_moment_inertia_scalar(b, angularVelocity4DB));
	//				//angularVelocity4DA = inverse_moment_of_inertia(momentInertiaScalarA, angularVelocity4DA);
	//				//angularVelocity4DB = inverse_moment_of_inertia(momentInertiaScalarB, angularVelocity4DB);
	//				vec4 vatAtA = velocity4DA;// + body_vec_to_world(a, left_contract_bv(collisions[i].collisionManifold.contactPosA - a.massCenter, angularVelocity4DA));
	//				vec4 vatAtB = velocity4DB;// + body_vec_to_world(b, left_contract_bv(collisions[i].collisionManifold.contactPosB - b.massCenter, angularVelocity4DB));
	//				if (vatAtB != vatAtA)
	//				{
	//					float factor = collisions[i].collisionManifold.depth / length(vatAtB - vatAtA);
	//					collisions[i].collisionManifold.depth = length(aB);
	//					velocity4DA = velocity4DA * factor/4.f;
	//					velocity4DB = velocity4DB * factor/4.f;
	//					//angularVelocity4DA = angularVelocity4DA * factor;
	//					//angularVelocity4DB = angularVelocity4DB * factor;
	//					atomicAdd(&positions4D[4 * index1], velocity4DA.x), atomicAdd(&positions4D[4 * index1 + 1], velocity4DA.y), atomicAdd(&positions4D[4 * index1 + 2], velocity4DA.z), atomicAdd(&positions4D[4 * index1 + 3], velocity4DA.w);
	//					if (index2 < sizeOfRigidBodies)atomicAdd(&positions4D[4 * index2], velocity4DB.x), atomicAdd(&positions4D[4 * index2 + 1], velocity4DB.y), atomicAdd(&positions4D[4 * index2 + 2], velocity4DB.z), atomicAdd(&positions4D[4 * index2 + 3], velocity4DB.w);
	//					//atomicAdd(&angularVelocitys4D[6 * index1], angularVelocity4DA.xy), atomicAdd(&angularVelocitys4D[6 * index1 + 1], angularVelocity4DA.xz), atomicAdd(&angularVelocitys4D[6 * index1 + 2], angularVelocity4DA.xw), atomicAdd(&angularVelocitys4D[6 * index1 + 3], angularVelocity4DA.yz), atomicAdd(&angularVelocitys4D[6 * index1 + 4], angularVelocity4DA.yw), atomicAdd(&angularVelocitys4D[6 * index1 + 5], angularVelocity4DA.zw);
	//					//atomicAdd(&angularVelocitys4D[6 * index2], angularVelocity4DB.xy), atomicAdd(&angularVelocitys4D[6 * index2 + 1], angularVelocity4DB.xz), atomicAdd(&angularVelocitys4D[6 * index2 + 2], angularVelocity4DB.xw), atomicAdd(&angularVelocitys4D[6 * index2 + 3], angularVelocity4DB.yz), atomicAdd(&angularVelocitys4D[6 * index2 + 4], angularVelocity4DB.yw), atomicAdd(&angularVelocitys4D[6 * index2 + 5], angularVelocity4DB.zw);
	//
	//				}
	//			}
	//		}
	//	}
	//}

	//sizesOfCollisionsVec[index] = 0;
	//a.position4d = vec4(positions4D[4 * index1], positions4D[4 * index1 + 1], positions4D[4 * index1 + 2], positions4D[4 * index1 + 3]);
	//a.rotation4D = rotor4(rotations4D[8 * index1], bivec4(rotations4D[8 * index1 + 1], rotations4D[8 * index1 + 2], rotations4D[8 * index1 + 3], rotations4D[8 * index1 + 4], rotations4D[8 * index1 + 5], rotations4D[8 * index1 + 6]), quadvec4(rotations4D[8 * index1 + 7]));
	//if (index2 < sizeOfRigidBodies)
	//{
	//	b.position4d = vec4(positions4D[4 * index2], positions4D[4 * index2 + 1], positions4D[4 * index2 + 2], positions4D[4 * index2 + 3]);
	//	b.rotation4D = rotor4(rotations4D[8 * index2], bivec4(rotations4D[8 * index2 + 1], rotations4D[8 * index2 + 2], rotations4D[8 * index2 + 3], rotations4D[8 * index2 + 4], rotations4D[8 * index2 + 5], rotations4D[8 * index2 + 6]), quadvec4(rotations4D[8 * index2 + 7]));
	//}
	//if (index2 != -1)
	//{
	//	if (!isStatics[index1])
	//	{
	//		detect_rigidbody_or_wall(index1, index2, a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
	//	}
	//	else if (isStatics[index1] && !isStatics[index2] && index2 < sizeOfRigidBodies)
	//	{
	//		detect_rigidbody_or_wall(index2, index1, b, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
	//	}
	//}
	//else
	//{
	//	if (!isStatics[index1])
	//	{
	//		detect_rigidbody_edge(index1, a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, collisions, &sizesOfCollisionsVec[index]);
	//	}
	//}

	if (sizesOfCollisionsVec[index] > 0)
	{
		for (int i(_d_max(index - 1, 0)); i < pSizeOfPairs; i++)
		{
			if (pSizesOfCollisionsVec[i] > 0)
			{
				//velocitys4D[4 * index1 + 1] = 1.f; velocitys4D[4 * index2 + 1] = 1.f;
				if (index1 == pPairsVec[2 * i] && index2 == pPairsVec[2 * i + 1])
				{
					//velocitys4D[4 * index1 + 1] = 1.f; velocitys4D[4 * index2 + 1] = 1.f;
					for (int j(0); j < pSizesOfCollisionsVec[i]; j++)
					{
						//int pIndexI = 2 * (j + 32 * i);
						int pIndexF = 50 * (j + 32 * i);
						vec4 pContactPosA = vec4(constraintsVecFloatArray[pIndexF + 16], constraintsVecFloatArray[pIndexF + 17], constraintsVecFloatArray[pIndexF + 18], constraintsVecFloatArray[pIndexF + 19]);
						vec4 pContactPosB = vec4(constraintsVecFloatArray[pIndexF + 20], constraintsVecFloatArray[pIndexF + 21], constraintsVecFloatArray[pIndexF + 22], constraintsVecFloatArray[pIndexF + 23]);
						for (int k(0); k < sizesOfCollisionsVec[index]; k++)
						{
							
							//int indexI = 3 * (k + 32 * index);
							int indexF = 15 * (k + 32 * index);
							vec4 contactPosA = collisions[k].collisionManifold.contactPosA;
							vec4 contactPosB = collisions[k].collisionManifold.contactPosB;
							if (length(contactPosA - pContactPosA) < 0.1f &&
								length(contactPosB - pContactPosB) < 0.1f)
							{
								if (collisions[k].type == 1)
									if (constraintsVecFloatArray[pIndexF + 48] < constraintsVecFloatArray[pIndexF + 49])
									{
										vec4 contactPosAToWorld;
										vec4 contactPosBToWorld;
										if (a.isStatic && !b.isStatic)
										{
											contactPosAToWorld = body_pos_to_world(b, pContactPosA);
											if (index2 == -1)contactPosBToWorld = pContactPosB;
											else contactPosBToWorld = body_pos_to_world(a, pContactPosB);
										}
										else
										{
											contactPosAToWorld = body_pos_to_world(a, pContactPosA);
											if (index2 == -1)contactPosBToWorld = pContactPosB;
											else contactPosBToWorld = body_pos_to_world(b, pContactPosB);
										}
										if (contactPosAToWorld != contactPosBToWorld)
										{
											vec4 normal2(contactPosAToWorld - contactPosBToWorld);
											vec4 normalE(normalize(normal2));
											collisions[k].collisionManifold.depth = length(normal2);
											collisions[k].collisionManifold.normal = normalE;
										}
										collisions[k].collisionManifold.contactPosA = pContactPosA;
										collisions[k].collisionManifold.contactPosB = pContactPosB;
									}
								vec4 impulse = vec4(constraintsVecFloatArray[pIndexF + 42], constraintsVecFloatArray[pIndexF + 43], constraintsVecFloatArray[pIndexF + 44], constraintsVecFloatArray[pIndexF + 45]);
								resolve_impulse(a, index1, velocitys4D, angularVelocitys4D, -impulse, pContactPosA, constraintsVecFloatArray[pIndexF + 46]);
								if (index2 < sizeOfRigidBodies && index2 != -1)
								{
									resolve_impulse(b, index2, velocitys4D, angularVelocitys4D, impulse, pContactPosB, constraintsVecFloatArray[pIndexF + 47]);
								}
							}
						}
					}
					break;
				}
			}
		}
	}
	if (sizesOfCollisionsVec[index] > 0)
	{
		if (index2 < sizeOfRigidBodies)
		{
			if (!a.isStatic && !b.isStatic)
			{
				if (!a.isContinueSleep || length(a.velocity4d) > 0.2f || length(a.angularVelocity4D) > 1.6f || !b.isContinueSleep || length(b.velocity4d) > 0.2f || length(b.angularVelocity4D) > 1.6f)
				{
					isSleeps[index1] = isSleeps[index2] = false, isContinueSleeps[index1] = isContinueSleeps[index2] = false;
				}
			}
		}
	}
	for (int i(0); i < sizesOfCollisionsVec[index]; i++)
	{
		//velocitys4D[4 * index1] = -collisions[i].collisionManifold.normal.x;// * vertices4DsVec[4*verticesStartIndices[a.primitiveId]];
		//velocitys4D[4 * index1 + 1] = -collisions[i].collisionManifold.normal.y;// * vertices4DsVec[4*verticesStartIndices[a.primitiveId]+1];
		//velocitys4D[4 * index1 + 2] = -collisions[i].collisionManifold.normal.z;// * vertices4DsVec[4*verticesStartIndices[a.primitiveId]+2];
		//velocitys4D[4 * index1 + 3] = -collisions[i].collisionManifold.normal.w;// * vertices4DsVec[4*verticesStartIndices[a.primitiveId]+3];
		//velocitys4D[4 * index2] = collisions[i].collisionManifold.normal.x;// * vertices4DsVec[4*verticesStartIndices[b.primitiveId]];
		//velocitys4D[4 * index2 + 1] = collisions[i].collisionManifold.normal.y;// * vertices4DsVec[4*verticesStartIndices[b.primitiveId]+1];
		//velocitys4D[4 * index2 + 2] = collisions[i].collisionManifold.normal.z;// * vertices4DsVec[4*verticesStartIndices[b.primitiveId]+2];
		//velocitys4D[4 * index2 + 3] = collisions[i].collisionManifold.normal.w;// * vertices4DsVec[4*verticesStartIndices[b.primitiveId]+3];
		int arrayIndexI = 3 * (i + 32 * index);
		collisionsVecIntArray[arrayIndexI] = collisions[i].index1;
		collisionsVecIntArray[arrayIndexI + 1] = collisions[i].index2;
		collisionsVecIntArray[arrayIndexI + 2] = collisions[i].type;
		int arrayIndexF = 15 * (i + 32 * index);
		collisionsVecFloatArray[arrayIndexF] = collisions[i].massAdjustmentA;
		collisionsVecFloatArray[arrayIndexF + 1] = collisions[i].massAdjustmentB;
		collisionsVecFloatArray[arrayIndexF + 2] = collisions[i].collisionManifold.normal.x;
		collisionsVecFloatArray[arrayIndexF + 3] = collisions[i].collisionManifold.normal.y;
		collisionsVecFloatArray[arrayIndexF + 4] = collisions[i].collisionManifold.normal.z;
		collisionsVecFloatArray[arrayIndexF + 5] = collisions[i].collisionManifold.normal.w;
		collisionsVecFloatArray[arrayIndexF + 6] = collisions[i].collisionManifold.depth;
		collisionsVecFloatArray[arrayIndexF + 7] = collisions[i].collisionManifold.contactPosA.x;
		collisionsVecFloatArray[arrayIndexF + 8] = collisions[i].collisionManifold.contactPosA.y;
		collisionsVecFloatArray[arrayIndexF + 9] = collisions[i].collisionManifold.contactPosA.z;
		collisionsVecFloatArray[arrayIndexF + 10] = collisions[i].collisionManifold.contactPosA.w;
		collisionsVecFloatArray[arrayIndexF + 11] = collisions[i].collisionManifold.contactPosB.x;
		collisionsVecFloatArray[arrayIndexF + 12] = collisions[i].collisionManifold.contactPosB.y;
		collisionsVecFloatArray[arrayIndexF + 13] = collisions[i].collisionManifold.contactPosB.z;
		collisionsVecFloatArray[arrayIndexF + 14] = collisions[i].collisionManifold.contactPosB.w;
	}
}

__global__ static void adjust_collisions_and_apply_forces(
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	bool* isGravitys,
	bool* isStatics,
	bool* isSleeps,
	bool* isContinueSleeps,
	float* forceSystems4D,
	int* sizesOfForces,
	int* forceStartIndices,
	float* masss,
	float* momentInertiaScalars,
	float* restitutions,
	float* mus,
	float* massCenters,
	float* velocitys4D,
	float* angularVelocitys4D,
	int* colTypes,
	int* primitiveIds,
	int* pairsVec,
	int* sizesOfPairs,
	int* pairsStartIndices,
	int* collisionsVecIntArray,
	float* collisionsVecFloatArray,
	int* sizesOfCollisionsVec,
	bool isTimeToSleep,
	float dt,
	int sizeOfRigidBodies
)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;

	int massAdjustmentA = 0;
	for (int i(0); i < sizesOfPairs[index]; i++)
	{
		massAdjustmentA += sizesOfCollisionsVec[pairsStartIndices[index] + i];
	}
	for (int i(0); i < sizesOfPairs[index]; i++)
	{
		int collisionIndex = pairsStartIndices[index] + i;
		int arrayIndexF = 32 * 15 * collisionIndex;
		for (int j(0); j < sizesOfCollisionsVec[collisionIndex]; j++)
		{
			collisionsVecFloatArray[15 * j + arrayIndexF] = massAdjustmentA;
			collisionsVecFloatArray[15 * j + arrayIndexF + 1] += sizesOfCollisionsVec[collisionIndex];
		}
	}
	_d_RigidBody4D a = copy_data_to_rigid_body(index, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
	if (a.isSleep)
	{
		if (a.isStatic)
		{
			if (isTimeToSleep)
			{
				a.isSleep = false;
			}
		}
	}
	else
	{
		if (!a.isStatic)
		{
			if (length(a.velocity4d) > 0.1f || length(a.angularVelocity4D) > 0.8f)
			{
				a.isContinueSleep = false;
			}
			if (isTimeToSleep)
			{
				if (a.isContinueSleep)
				{
					a.isSleep = true;
				}
				a.isContinueSleep = true;
			}
		}
	}
	if (!a.isStatic)
	{
		update_rigidbody_velocity4D(&a, forceSystems4D, dt);
	}
	if (a.is_dynamic())
	{
		if (a.isGravity)resolve_impulse(&a, vec4(0.f, -9.80665f * a.mass * dt, 0.f, 0.f));
		move_velocity_data_from_rigid_body(index, a, velocitys4D, angularVelocitys4D);
	}
	isSleeps[index] = a.isSleep, isContinueSleeps[index] = a.isContinueSleep;
}

__global__ static void get_and_solve_constraint(
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	bool* isGravitys,
	bool* isStatics,
	bool* isSleeps,
	bool* isContinueSleeps,
	int* sizesOfForces,
	int* forceStartIndices,
	float* masss,
	float* momentInertiaScalars,
	float* restitutions,
	float* mus,
	float* massCenters,
	float* velocitys4D,
	float* angularVelocitys4D,
	int* colTypes,
	int* primitiveIds,
	int* pairsVec,
	int* sizesOfPairs,
	int* pairsStartIndices,
	int* collisionsVecIntArray,
	float* collisionsVecFloatArray,
	int* sizesOfCollisionsVec,
	int* constraintsVecIntArray,
	float* constraintsVecFloatArray,
	int sizeOfRigidBodies
)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	if (index%32<sizesOfCollisionsVec[index/32])
	{
		int arrayIndexF(15 * index);
	_d_Collision collision = { collisionsVecIntArray[3 * index], collisionsVecIntArray[3 * index + 1], collisionsVecFloatArray[arrayIndexF], collisionsVecFloatArray[arrayIndexF + 1],
		{vec4(collisionsVecFloatArray[arrayIndexF + 2],collisionsVecFloatArray[arrayIndexF + 3], collisionsVecFloatArray[arrayIndexF + 4], collisionsVecFloatArray[arrayIndexF + 5]),collisionsVecFloatArray[arrayIndexF + 6],
		vec4(collisionsVecFloatArray[arrayIndexF + 7], collisionsVecFloatArray[arrayIndexF + 8],collisionsVecFloatArray[arrayIndexF + 9], collisionsVecFloatArray[arrayIndexF + 10]),
	vec4(collisionsVecFloatArray[arrayIndexF + 11], collisionsVecFloatArray[arrayIndexF + 12],collisionsVecFloatArray[arrayIndexF + 13], collisionsVecFloatArray[arrayIndexF + 14])}, collisionsVecIntArray[3 * index + 2] };
		_d_Constraint constraint;
		int index1 = collision.index1;
		int index2 = collision.index2;
		_d_RigidBody4D a = copy_data_to_rigid_body(index1, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
		if (index2 != -1)
		{
			_d_RigidBody4D b = copy_data_to_rigid_body(index2, index2 < sizeOfRigidBodies, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
			if (!a.isStatic && !b.isStatic)
			{
				get_constraint(a, b, collision, &constraint);
				move_data_from_constraint(index, constraint, constraintsVecIntArray, constraintsVecFloatArray);
				if (!(a.isSleep && b.isSleep))
				{
					for (int i(0); i < 140; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, b, index2, velocitys4D, angularVelocitys4D); }
				}
			}
			else if (!a.isStatic && b.isStatic)
			{
				get_constraint_of_wall(a, b, collision, &constraint);
				move_data_from_constraint(index, constraint, constraintsVecIntArray, constraintsVecFloatArray);
				if (!a.isSleep)
				{
					for (int i(0); i < 140; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, velocitys4D, angularVelocitys4D); }
				}
			}
			else if (a.isStatic && !b.isStatic)
			{
				get_constraint_of_wall(b, a, collision, &constraint);
				move_data_from_constraint(index, constraint, constraintsVecIntArray, constraintsVecFloatArray);
				if (!b.isSleep)
				{
					for (int i(0); i < 140; i++) { solve(constraintsVecFloatArray, 50 * index, b, index2, velocitys4D, angularVelocitys4D); }
				}
			}
		}
		else
		{
			if (!a.isStatic) {
				get_constraint(a, collision, &constraint);
				move_data_from_constraint(index, constraint, constraintsVecIntArray, constraintsVecFloatArray);
				if (!a.isSleep)
				{
					for (int i(0); i < 140; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, velocitys4D, angularVelocitys4D); }
				}
			}
		}
		
		//_d_RigidBody4D a = copy_data_to_rigid_body(index1, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, forceSystems4D, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
	}
}

//__global__ static void solve_constraint(
//	float* positions4D,
//	float* rotations4D,
//	float* scales4D,
//	bool* isGravitys,
//	bool* isStatics,
//	bool* isSleeps,
//	bool* isContinueSleeps,
//	float* forceSystems4D,
//	int* sizesOfForces,
//	int* forceStartIndices,
//	float* masss,
//	float* momentInertiaScalars,
//	float* restitutions,
//	float* mus,
//	float* massCenters,
//	float* velocitys4D,
//	float* angularVelocitys4D,
//	int* colTypes,
//	int* primitiveIds,
//	int* pairsVec,
//	int* sizesOfPairs,
//	int* pairsStartIndices,
//	int* collisionsVecIntArray,
//	float* collisionsVecFloatArray,
//	int* sizesOfCollisionsVec,
//	int* constraintsVecIntArray,
//	float* constraintsVecFloatArray,
//	int sizeOfRigidBodies
//)
//{
//	int index = blockDim.x * blockIdx.x + threadIdx.x;
//	if (index % 32 < sizesOfCollisionsVec[(index - index % 32) / 32])
//	{
//		int index1 = collisionsVecIntArray[3 * index];
//		int index2 = collisionsVecIntArray[3 * index + 1];
//		_d_RigidBody4D a = copy_data_to_rigid_body(index1, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, forceSystems4D, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
//		if (index2 != -1)
//		{
//			_d_RigidBody4D b = copy_data_to_rigid_body(index2, index2 < sizeOfRigidBodies, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, forceSystems4D, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
//			if (!a.isStatic && !b.isStatic)
//			{
//				for (int i(0); i < 192; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, b, index2, velocitys4D, angularVelocitys4D); }
//			}
//			else if (!a.isStatic && b.isStatic)
//			{
//				for (int i(0); i < 192; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, velocitys4D, angularVelocitys4D); }
//			}
//			else if (a.isStatic && !b.isStatic)
//			{
//				for (int i(0); i < 192; i++) { solve(constraintsVecFloatArray, 50 * index, b, index2, velocitys4D, angularVelocitys4D); }
//			}
//		}
//		else
//		{
//			if (!a.isStatic) {
//				for (int i(0); i < 192; i++) { solve(constraintsVecFloatArray, 50 * index, a, index1, velocitys4D, angularVelocitys4D); }
//			}
//		}
//	}
//}

//__global__ static void apply_velocitys(
//	float* velocitys4D,
//	float* angularVelocitys4D,
//	int* pairsVec,
//	int* sizesOfPairs,
//	int* pairsStartIndices,
//	int* collisionsVecIntArray,
//	float* collisionsVecFloatArray,
//	int* sizesOfCollisionsVec,
//	int* constraintsVecIntArray,
//	float* constraintsVecFloatArray,
//	float* velocitys4DAdd,
//	float* angularVelocitys4DAdd,
//	int sizeOfRigidBodies
//)
//{
//	int index = blockDim.x * blockIdx.x + threadIdx.x;
//	for (int j(0); j < pairsStartIndices[index]+sizesOfPairs[index]; j++)
//	{
//		for (int i(0); i < sizesOfCollisionsVec[j]; i++)
//		{
//			if (pairsVec[2 * j] == index)
//			{
//				int indexV = 2 * (32 * j + i);
//				velocitys4D[4 * index] += velocitys4DAdd[4 * indexV], velocitys4D[4 * index + 1] += velocitys4DAdd[4 * indexV + 1], velocitys4D[4 * index + 2] += velocitys4DAdd[4 * indexV + 2], velocitys4D[4 * index + 3] += velocitys4DAdd[4 * indexV + 3];
//				angularVelocitys4D[6 * index] += angularVelocitys4DAdd[6 * indexV], angularVelocitys4D[6 * index + 1] += angularVelocitys4DAdd[6 * indexV + 1], angularVelocitys4D[6 * index + 2] += angularVelocitys4DAdd[6 * indexV + 2], angularVelocitys4D[6 * index + 3] += angularVelocitys4DAdd[6 * indexV + 3], angularVelocitys4D[6 * index + 4] += angularVelocitys4DAdd[6 * indexV + 4], angularVelocitys4D[6 * index + 5] += angularVelocitys4DAdd[6 * indexV + 5];
//			}
//			if (pairsVec[2 * j + 1] == index)
//			{
//				int indexV = 2 * (32 * j + i);
//				velocitys4D[4 * index] += velocitys4DAdd[4 * indexV + 4], velocitys4D[4 * index + 1] += velocitys4DAdd[4 * indexV + 5], velocitys4D[4 * index + 2] += velocitys4DAdd[4 * indexV + 6], velocitys4D[4 * index + 3] += velocitys4DAdd[4 * indexV + 7];
//				angularVelocitys4D[6 * index] += angularVelocitys4DAdd[6 * indexV + 6], angularVelocitys4D[6 * index + 1] += angularVelocitys4DAdd[6 * indexV + 7], angularVelocitys4D[6 * index + 2] += angularVelocitys4DAdd[6 * indexV + 8], angularVelocitys4D[6 * index + 3] += angularVelocitys4DAdd[6 * indexV + 9], angularVelocitys4D[6 * index + 4] += angularVelocitys4DAdd[6 * indexV + 10], angularVelocitys4D[6 * index + 5] += angularVelocitys4DAdd[6 * indexV + 11];
//			}
//		}
//	}
//}

__global__ static void update_positions4D(
	float* positions4D,
	float* rotations4D,
	float* scales4D,
	bool* isGravitys,
	bool* isStatics,
	bool* isSleeps,
	bool* isContinueSleeps,
	int* sizesOfForces,
	int* forceStartIndices,
	float* masss,
	float* momentInertiaScalars,
	float* restitutions,
	float* mus,
	float* massCenters,
	float* velocitys4D,
	float* angularVelocitys4D,
	int* colTypes,
	int* primitiveIds,
	float* mats4,
	float dt,
	int sizeOfRigidBodies
)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	_d_RigidBody4D a = copy_data_to_rigid_body(index, true, positions4D, rotations4D, scales4D, isGravitys, isStatics, isSleeps, isContinueSleeps, sizesOfForces, forceStartIndices, masss, momentInertiaScalars, restitutions, mus, massCenters, velocitys4D, angularVelocitys4D, colTypes, primitiveIds);
	if (a.is_dynamic())
	{
		if (a.massCenter == vec4(0.f))
		{
			a.position4d = a.position4d + a.velocity4d * dt;
			a.rotation4D = update(a.rotation4D, a.angularVelocity4D * dt);

		}
		else
		{
			vec4 bodyMassCenterToWorld(body_pos_to_world(a, a.massCenter));
			a.rotation4D = update(a.rotation4D, a.angularVelocity4D * dt);
			vec4 bodyMassCenterToVec(body_vec_to_world(a, a.massCenter));
			a.position4d = bodyMassCenterToWorld - bodyMassCenterToVec + a.velocity4d * dt;
		}
		positions4D[4 * index] = a.position4d.x, positions4D[4 * index + 1] = a.position4d.y, positions4D[4 * index + 2] = a.position4d.z, positions4D[4 * index + 3] = a.position4d.w;
		rotations4D[8 * index] = a.rotation4D.s, rotations4D[8 * index + 1] = a.rotation4D.b.xy, rotations4D[8 * index + 2] = a.rotation4D.b.xz, rotations4D[8 * index + 3] = a.rotation4D.b.xw, rotations4D[8 * index + 4] = a.rotation4D.b.yz, rotations4D[8 * index + 5] = a.rotation4D.b.yw, rotations4D[8 * index + 6] = a.rotation4D.b.zw, rotations4D[8 * index + 7] = a.rotation4D.q.xyzw;
		to_matrix(a.rotation4D, a.scale4D, mats4, index);
	}
}

static float* positions4D;
static float* rotations4D;
static float* scales4D;
static bool* isGravitys;
static bool* isStatics;
static bool* isSleeps;
static bool* isContinueSleeps;
static float* forceSystems4D;
static int* sizesOfForces;
static int* forceStartIndices;
static float* masss;
static float* momentInertiaScalars;
static float* restitutions;
static float* mus;
static float* massCenters;
static float* velocitys4D;
static float* angularVelocitys4D;
static float* vertices4DsVec;
static int* sizesOfVertices4D;
static int* verticesStartIndices;
static int* colTypes;
static int* primitiveIds;
static int* pairsVec;
static int* sizesOfPairs;
static int* pairsStartIndices;
//static int* collisionsVecIntArray;
static float* collisionsVecFloatArray;
static int* sizesOfCollisionsVec;
static float* mats4;

static float* _d_positions4D;
static float* _d_rotations4D;
static float* _d_scales4D;
static bool* _d_isGravitys;
static bool* _d_isStatics;
static bool* _d_isSleeps;
static bool* _d_isContinueSleeps;
static float* _d_forceSystems4D;
static int* _d_sizesOfForces;
static int* _d_forceStartIndices;
static float* _d_masss;
static float* _d_momentInertiaScalars;
static float* _d_restitutions;
static float* _d_mus;
static float* _d_massCenters;
static float* _d_velocitys4D;
static float* _d_angularVelocitys4D;
static float* _d_vertices4DsVec;
static int* _d_sizesOfVertices4D;
static int* _d_verticesStartIndices;
static int* _d_colTypes;
static int* _d_primitiveIds;
static int* _d_pairsVec;
static int* _d_sizesOfPairs;
static int* _d_pairsStartIndices;
static int* _d_collisionsVecIntArray;
static float* _d_collisionsVecFloatArray;
static int* _d_sizesOfCollisionsVec;
static int* _d_constraintsVecIntArray;
static float* _d_constraintsVecFloatArray;
static float* _d_mats4;
static int* _d_pPairsVec;
static int* _d_pSizesOfPairs;
static int* _d_pPairsStartIndices;
static int* _d_pSizesOfCollisionsVec;

static size_t pSizeOfPairs;

static void init_physics4d_function()
{
	const int sizeOfRigidBodies = 2500;
	const int sizeOfRigidBodiesAndWalls = 5000;
	size_t sizeList[38];
	sizeList[0] = 4 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[1] = 8 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[2] = 4 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[3] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[4] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[5] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[6] = sizeof(bool) * sizeOfRigidBodies;
	int forceVecSize = 0; for (int i(0); i < sizeOfRigidBodies; i++) forceVecSize += 1;
	sizeList[7] = 8 * sizeof(float) * forceVecSize;
	sizeList[8] = sizeof(int) * sizeOfRigidBodies;
	sizeList[9] = sizeof(int) * sizeOfRigidBodies;
	sizeList[10] = sizeof(float) * sizeOfRigidBodies;
	sizeList[11] = sizeof(float) * sizeOfRigidBodies;
	sizeList[12] = sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[13] = sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[14] = 4 * sizeof(float) * sizeOfRigidBodies;
	sizeList[15] = 4 * sizeof(float) * sizeOfRigidBodies;
	sizeList[16] = 6 * sizeof(float) * sizeOfRigidBodies;
	sizeList[17] = sizeof(int) * sizeOfRigidBodiesAndWalls;
	int vertices4DVecSize = 0; for (int i(3); i < 13; i++) { vertices4DVecSize += get_vertices_size(i); }
	sizeList[18] = 4 * sizeof(float) * vertices4DVecSize;
	sizeList[19] = sizeof(int) * 13;
	sizeList[20] = sizeof(int) * 13;
	sizeList[24] = sizeof(int) * sizeOfRigidBodiesAndWalls;
	sizeList[25] = 16 * sizeof(int) * sizeOfRigidBodies;
	sizeList[26] = 8 * sizeof(int) * sizeOfRigidBodies;
	sizeList[27] = 8 * sizeof(int) * sizeOfRigidBodies;
	sizeList[28] = 32 * 8 * 3 * sizeof(int) * sizeOfRigidBodies;
	sizeList[29] = 32 * 8 * 15 * sizeof(float) * sizeOfRigidBodies;
	sizeList[30] = 8 * sizeof(int) * sizeOfRigidBodies;
	sizeList[31] = 32 * 8 * 2 * sizeof(int) * sizeOfRigidBodies;
	sizeList[32] = 32 * 8 * 50 * sizeof(float) * sizeOfRigidBodies;
	sizeList[33] = 16 * sizeof(float) * sizeOfRigidBodies;
	sizeList[34] = 16 * sizeof(int) * sizeOfRigidBodies;
	sizeList[35] = 8 * sizeof(int) * sizeOfRigidBodies;
	sizeList[36] = 8 * sizeof(int) * sizeOfRigidBodies;
	sizeList[37] = 8 * sizeof(int) * sizeOfRigidBodies;
	
	cudaMallocHost((void**)&positions4D, sizeList[0]);
	cudaMallocHost((void**)&rotations4D, sizeList[1]);
	cudaMallocHost((void**)&scales4D, sizeList[2]);
	cudaMallocHost((void**)&isGravitys, sizeList[3]);
	cudaMallocHost((void**)&isStatics, sizeList[4]);
	cudaMallocHost((void**)&isSleeps, sizeList[5]);
	cudaMallocHost((void**)&isContinueSleeps, sizeList[6]);
	cudaMallocHost((void**)&forceSystems4D, sizeList[7]);
	cudaMallocHost((void**)&sizesOfForces, sizeList[8]);
	cudaMallocHost((void**)&forceStartIndices, sizeList[9]);
	cudaMallocHost((void**)&masss, sizeList[10]);
	cudaMallocHost((void**)&momentInertiaScalars, sizeList[11]);
	cudaMallocHost((void**)&restitutions, sizeList[12]);
	cudaMallocHost((void**)&mus, sizeList[13]);
	cudaMallocHost((void**)&massCenters, sizeList[14]);
	cudaMallocHost((void**)&velocitys4D, sizeList[15]);
	cudaMallocHost((void**)&angularVelocitys4D, sizeList[16]);
	cudaMallocHost((void**)&colTypes, sizeList[17]);
	cudaMallocHost((void**)&vertices4DsVec, sizeList[18]);
	cudaMallocHost((void**)&sizesOfVertices4D, sizeList[19]);
	cudaMallocHost((void**)&verticesStartIndices, sizeList[20]);
	cudaMallocHost((void**)&primitiveIds, sizeList[24]);
	cudaMallocHost((void**)&pairsVec, sizeList[25]);
	cudaMallocHost((void**)&sizesOfPairs, sizeList[26]);
	cudaMallocHost((void**)&pairsStartIndices, sizeList[27]);
	//cudaMallocHost((void**)&collisionsVecIntArray, sizeList[28]);
	cudaMallocHost((void**)&collisionsVecFloatArray, sizeList[29]);
	cudaMallocHost((void**)&sizesOfCollisionsVec, sizeList[30]);
	cudaMallocHost((void**)&mats4, sizeList[33]);

	cudaMalloc((void**)&_d_positions4D, sizeList[0]);
	cudaMalloc((void**)&_d_rotations4D, sizeList[1]);
	cudaMalloc((void**)&_d_scales4D, sizeList[2]);
	cudaMalloc((void**)&_d_isGravitys, sizeList[3]);
	cudaMalloc((void**)&_d_isStatics, sizeList[4]);
	cudaMalloc((void**)&_d_isSleeps, sizeList[5]);
	cudaMalloc((void**)&_d_isContinueSleeps, sizeList[6]);
	cudaMalloc((void**)&_d_forceSystems4D, sizeList[7]);
	cudaMalloc((void**)&_d_sizesOfForces, sizeList[8]);
	cudaMalloc((void**)&_d_forceStartIndices, sizeList[9]);
	cudaMalloc((void**)&_d_masss, sizeList[10]);
	cudaMalloc((void**)&_d_momentInertiaScalars, sizeList[11]);
	cudaMalloc((void**)&_d_restitutions, sizeList[12]);
	cudaMalloc((void**)&_d_mus, sizeList[13]);
	cudaMalloc((void**)&_d_massCenters, sizeList[14]);
	cudaMalloc((void**)&_d_velocitys4D, sizeList[15]);
	cudaMalloc((void**)&_d_angularVelocitys4D, sizeList[16]);
	cudaMalloc((void**)&_d_colTypes, sizeList[17]);
	cudaMalloc((void**)&_d_vertices4DsVec, sizeList[18]);
	cudaMalloc((void**)&_d_sizesOfVertices4D, sizeList[19]);
	cudaMalloc((void**)&_d_verticesStartIndices, sizeList[20]);
	cudaMalloc((void**)&_d_primitiveIds, sizeList[24]);
	cudaMalloc((void**)&_d_pairsVec, sizeList[25]);
	cudaMalloc((void**)&_d_sizesOfPairs, sizeList[26]);
	cudaMalloc((void**)&_d_pairsStartIndices, sizeList[27]);
	cudaMalloc((void**)&_d_collisionsVecIntArray, sizeList[28]);
	cudaMalloc((void**)&_d_collisionsVecFloatArray, sizeList[29]);
	cudaMalloc((void**)&_d_sizesOfCollisionsVec, sizeList[30]);
	cudaMalloc((void**)&_d_constraintsVecIntArray, sizeList[31]);
	cudaMalloc((void**)&_d_constraintsVecFloatArray, sizeList[32]);
	cudaMalloc((void**)&_d_mats4, sizeList[33]);
	cudaMalloc((void**)&_d_pPairsVec, sizeList[34]);
	cudaMalloc((void**)&_d_pSizesOfPairs, sizeList[35]);
	cudaMalloc((void**)&_d_pPairsStartIndices, sizeList[36]);
	cudaMalloc((void**)&_d_pSizesOfCollisionsVec, sizeList[37]);

	int vertexStartIndex = 0;
	for (int i(3); i < 13; i++)
	{
		//if (i != 5)
		{
			sizesOfVertices4D[i] = get_vertices_size(i);
			verticesStartIndices[i] = vertexStartIndex;
			vertexStartIndex += sizesOfVertices4D[i];
			for (int j(0); j < sizesOfVertices4D[i]; j++) {
				int vIndex = 4 * (verticesStartIndices[i] + j);
				glm::vec4 vertex(get_vertex(i,j));
				vertices4DsVec[vIndex] = vertex.x, vertices4DsVec[vIndex + 1] = vertex.y, vertices4DsVec[vIndex + 2] = vertex.z, vertices4DsVec[vIndex + 3] = vertex.w;
			}
		}
	}
	sizesOfVertices4D[0] = 0;
	sizesOfVertices4D[1] = 0;
	sizesOfVertices4D[2] = 0;
	//sizesOfVertices4D[5] = 0;
	verticesStartIndices[0] = 0;
	verticesStartIndices[1] = 0;
	verticesStartIndices[2] = 0;
	//verticesStartIndices[5] = verticesStartIndices[4];
	cudaMemcpy(_d_vertices4DsVec, vertices4DsVec, sizeList[18], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_sizesOfVertices4D, sizesOfVertices4D, sizeList[19], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_verticesStartIndices, verticesStartIndices, sizeList[20], cudaMemcpyHostToDevice);
}

static void destroy_physics4d_function()
{
	cudaFreeHost(positions4D);
	cudaFreeHost(rotations4D);
	cudaFreeHost(scales4D);
	cudaFreeHost(isGravitys);
	cudaFreeHost(isStatics);
	cudaFreeHost(isSleeps);
	cudaFreeHost(isContinueSleeps);
	cudaFreeHost(forceSystems4D);
	cudaFreeHost(sizesOfForces);
	cudaFreeHost(forceStartIndices);
	cudaFreeHost(masss);
	cudaFreeHost(momentInertiaScalars);
	cudaFreeHost(restitutions);
	cudaFreeHost(mus);
	cudaFreeHost(massCenters);
	cudaFreeHost(velocitys4D);
	cudaFreeHost(angularVelocitys4D);
	cudaFreeHost(colTypes);
	cudaFreeHost(vertices4DsVec);
	cudaFreeHost(sizesOfVertices4D);
	cudaFreeHost(verticesStartIndices);
	cudaFreeHost(primitiveIds);
	cudaFreeHost(pairsVec);
	cudaFreeHost(sizesOfPairs);
	cudaFreeHost(pairsStartIndices);
	//cudaFreeHost(collisionsVecIntArray);
	cudaFreeHost(collisionsVecFloatArray);
	cudaFreeHost(sizesOfCollisionsVec);
	cudaFreeHost(mats4);

	cudaFree(_d_positions4D);
	cudaFree(_d_rotations4D);
	cudaFree(_d_scales4D);
	cudaFree(_d_isGravitys);
	cudaFree(_d_isStatics);
	cudaFree(_d_isSleeps);
	cudaFree(_d_isContinueSleeps);
	cudaFree(_d_forceSystems4D);
	cudaFree(_d_sizesOfForces);
	cudaFree(_d_forceStartIndices);
	cudaFree(_d_masss);
	cudaFree(_d_momentInertiaScalars);
	cudaFree(_d_restitutions);
	cudaFree(_d_mus);
	cudaFree(_d_massCenters);
	cudaFree(_d_velocitys4D);
	cudaFree(_d_angularVelocitys4D);
	cudaFree(_d_colTypes);
	cudaFree(_d_vertices4DsVec);
	cudaFree(_d_sizesOfVertices4D);
	cudaFree(_d_verticesStartIndices);
	cudaFree(_d_primitiveIds);
	cudaFree(_d_pairsVec);
	cudaFree(_d_sizesOfPairs);
	cudaFree(_d_pairsStartIndices);
	cudaFree(_d_collisionsVecIntArray);
	cudaFree(_d_collisionsVecFloatArray);
	cudaFree(_d_sizesOfCollisionsVec);
	cudaFree(_d_constraintsVecIntArray);
	cudaFree(_d_constraintsVecFloatArray);
	cudaFree(_d_mats4);
	cudaFree(_d_pPairsVec);
	cudaFree(_d_pSizesOfPairs);
	cudaFree(_d_pPairsStartIndices);
	cudaFree(_d_pSizesOfCollisionsVec);
}

static float timeToSleep = 0.f;

static void update_cuda(
	size_t sizeOfPairs,
	size_t* sizeList,
	size_t* sizeList2,
	bool isTimeToSleep,
	float dt,
	int sizeOfRigidBodies)
{

	cudaMemcpy(_d_positions4D, positions4D, sizeList[0], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_rotations4D, rotations4D, sizeList[1], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_scales4D, scales4D, sizeList[2], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_isGravitys, isGravitys, sizeList[3], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_isStatics, isStatics, sizeList[4], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_isSleeps, isSleeps, sizeList[5], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_isContinueSleeps, isContinueSleeps, sizeList[6], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_forceSystems4D, forceSystems4D, sizeList[7], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_sizesOfForces, sizesOfForces, sizeList[8], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_forceStartIndices, forceStartIndices, sizeList[9], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_masss, masss, sizeList[10], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_momentInertiaScalars, momentInertiaScalars, sizeList[11], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_restitutions, restitutions, sizeList[12], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_mus, mus, sizeList[13], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_massCenters, massCenters, sizeList[14], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_velocitys4D, velocitys4D, sizeList[15], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_angularVelocitys4D, angularVelocitys4D, sizeList[16], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_colTypes, colTypes, sizeList[17], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_primitiveIds, primitiveIds, sizeList[24], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_pairsVec, pairsVec, sizeList[25], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_sizesOfPairs, sizesOfPairs, sizeList[26], cudaMemcpyHostToDevice);
	cudaMemcpy(_d_pairsStartIndices, pairsStartIndices, sizeList[27], cudaMemcpyHostToDevice);

	detect_collision << <sizeOfPairs, 1 >> > (_d_positions4D, _d_rotations4D, _d_scales4D, _d_isGravitys, _d_isStatics, _d_isSleeps, _d_isContinueSleeps, _d_sizesOfForces, _d_forceStartIndices, _d_masss, _d_momentInertiaScalars, _d_restitutions, _d_mus, _d_massCenters, _d_velocitys4D, _d_angularVelocitys4D, _d_colTypes, _d_vertices4DsVec, _d_sizesOfVertices4D, _d_verticesStartIndices, _d_primitiveIds, _d_pairsVec, _d_sizesOfPairs, _d_pairsStartIndices, _d_collisionsVecIntArray, _d_collisionsVecFloatArray, _d_sizesOfCollisionsVec, _d_constraintsVecFloatArray, _d_pPairsVec, _d_pSizesOfPairs, _d_pPairsStartIndices, _d_pSizesOfCollisionsVec, pSizeOfPairs, dt, sizeOfRigidBodies);

	cudaDeviceSynchronize();

	adjust_collisions_and_apply_forces << <sizeOfRigidBodies, 1 >> > (_d_positions4D, _d_rotations4D, _d_scales4D, _d_isGravitys, _d_isStatics, _d_isSleeps, _d_isContinueSleeps, _d_forceSystems4D, _d_sizesOfForces, _d_forceStartIndices, _d_masss, _d_momentInertiaScalars, _d_restitutions, _d_mus, _d_massCenters, _d_velocitys4D, _d_angularVelocitys4D, _d_colTypes, primitiveIds, _d_pairsVec, _d_sizesOfPairs, _d_pairsStartIndices, _d_collisionsVecIntArray, _d_collisionsVecFloatArray, _d_sizesOfCollisionsVec, isTimeToSleep, dt, sizeOfRigidBodies);

	cudaDeviceSynchronize();

	get_and_solve_constraint << <sizeOfPairs, 32 >> > (_d_positions4D, _d_rotations4D, _d_scales4D, _d_isGravitys, _d_isStatics, _d_isSleeps, _d_isContinueSleeps, _d_sizesOfForces, _d_forceStartIndices, _d_masss, _d_momentInertiaScalars, _d_restitutions, _d_mus, _d_massCenters, _d_velocitys4D, _d_angularVelocitys4D, _d_colTypes, _d_primitiveIds, _d_pairsVec, _d_sizesOfPairs, _d_pairsStartIndices, _d_collisionsVecIntArray, _d_collisionsVecFloatArray, _d_sizesOfCollisionsVec, _d_constraintsVecIntArray, _d_constraintsVecFloatArray, sizeOfRigidBodies);

	cudaDeviceSynchronize();

	update_positions4D << <sizeOfRigidBodies, 1 >> > (_d_positions4D, _d_rotations4D, _d_scales4D, _d_isGravitys, _d_isStatics, _d_isSleeps, _d_isContinueSleeps, _d_sizesOfForces, _d_forceStartIndices, _d_masss, _d_momentInertiaScalars, _d_restitutions, _d_mus, _d_massCenters, _d_velocitys4D, _d_angularVelocitys4D, _d_colTypes, _d_primitiveIds, _d_mats4, dt, sizeOfRigidBodies);

	cudaDeviceSynchronize();

	cudaMemcpy(_d_pPairsVec, _d_pairsVec, sizeList[25], cudaMemcpyDeviceToDevice);
	cudaMemcpy(_d_pSizesOfPairs, _d_sizesOfPairs, sizeList[26], cudaMemcpyDeviceToDevice);
	cudaMemcpy(_d_pPairsStartIndices, _d_pairsStartIndices, sizeList[27], cudaMemcpyDeviceToDevice);
	cudaMemcpy(_d_pSizesOfCollisionsVec, _d_sizesOfCollisionsVec, sizeList[25], cudaMemcpyDeviceToDevice);
	
	pSizeOfPairs = sizeOfPairs;

	cudaMemcpy(positions4D, _d_positions4D, sizeList2[0], cudaMemcpyDeviceToHost);
	cudaMemcpy(rotations4D, _d_rotations4D, sizeList2[1], cudaMemcpyDeviceToHost);
	cudaMemcpy(isSleeps, _d_isSleeps, sizeList[5], cudaMemcpyDeviceToHost);
	cudaMemcpy(isContinueSleeps, _d_isContinueSleeps, sizeList[6], cudaMemcpyDeviceToHost);
	cudaMemcpy(velocitys4D, _d_velocitys4D, sizeList[15], cudaMemcpyDeviceToHost);
	cudaMemcpy(angularVelocitys4D, _d_angularVelocitys4D, sizeList[16], cudaMemcpyDeviceToHost);
	//cudaMemcpy(collisionsVecIntArray, _d_collisionsVecIntArray, 32 * 3 * sizesOfPairs[0], cudaMemcpyDeviceToHost);
	cudaMemcpy(collisionsVecFloatArray, _d_collisionsVecFloatArray, 32 * 15 * sizesOfPairs[0] * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(sizesOfCollisionsVec, _d_sizesOfCollisionsVec, sizesOfPairs[0] * sizeof(int), cudaMemcpyDeviceToHost);
	cudaMemcpy(mats4, _d_mats4, sizeList[28], cudaMemcpyDeviceToHost);
}

static void phy_function(std::vector<RigidBody4D*> rigidBodies4d, std::vector<Wall4D*> walls4d, std::vector < std::vector<Collision>>* collisionsVec)
{
	size_t sizeList[29];
	size_t sizeList2[2];
	int sizeOfRigidBodies = rigidBodies4d.size();
	int sizeOfRigidBodiesAndWalls = size_of_objects4d(rigidBodies4d, walls4d);
	sizeList[0] = 4 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[1] = 8 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[2] = 4 * sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[3] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[4] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[5] = sizeof(bool) * sizeOfRigidBodies;
	sizeList[6] = sizeof(bool) * sizeOfRigidBodies;
	int forceVecSize = 0; for (int i(0); i < sizeOfRigidBodies; i++) forceVecSize += rigidBodies4d[i]->forceSystems4D.size();
	sizeList[7] = 8 * sizeof(float) * forceVecSize;
	sizeList[8] = sizeof(int) * sizeOfRigidBodies;
	sizeList[9] = sizeof(int) * sizeOfRigidBodies;
	sizeList[10] = sizeof(float) * sizeOfRigidBodies;
	sizeList[11] = sizeof(float) * sizeOfRigidBodies;
	sizeList[12] = sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[13] = sizeof(float) * sizeOfRigidBodiesAndWalls;
	sizeList[14] = 4 * sizeof(float) * sizeOfRigidBodies;
	sizeList[15] = 4 * sizeof(float) * sizeOfRigidBodies;
	sizeList[16] = 6 * sizeof(float) * sizeOfRigidBodies;
	sizeList[17] = sizeof(int) * sizeOfRigidBodiesAndWalls;
	sizeList[24] = sizeof(int) * sizeOfRigidBodiesAndWalls;
	sizeList[28] = 16 * sizeof(float) * sizeOfRigidBodies;

	sizeList2[0] = 4 * sizeof(float) * sizeOfRigidBodies;
	sizeList2[1] = 8 * sizeof(float) * sizeOfRigidBodies;

	int forcesStartIndex = 0;
	int pairsStartIndex = 0;
	for (int i(0); i < sizeOfRigidBodies; i++)
	{
		RigidBody4D* a(rigidBodies4d[i]);
		isGravitys[i] = a->isGravity;
		isStatics[i] = a->is_static();
		isSleeps[i] = a->isSleep;
		isContinueSleeps[i] = a->isContinueSleep;

		sizesOfForces[i] = a->forceSystems4D.size();
		forceStartIndices[i] = forcesStartIndex;
		for (int j(0); j < a->forceSystems4D.size(); j++){
			//std::cout << forceStartIndices[i] << '\n';
			int fIndex = 8 * (forcesStartIndex + j);
			forceSystems4D[fIndex] = a->forceSystems4D[j]->force4D.x, forceSystems4D[fIndex + 1] = a->forceSystems4D[j]->force4D.y, forceSystems4D[fIndex + 2] = a->forceSystems4D[j]->force4D.z, forceSystems4D[fIndex + 3] = a->forceSystems4D[j]->force4D.w;
			forceSystems4D[fIndex + 4] = a->forceSystems4D[j]->position4d.x, forceSystems4D[fIndex + 5] = a->forceSystems4D[j]->position4d.y, forceSystems4D[fIndex + 6] = a->forceSystems4D[j]->position4d.z, forceSystems4D[fIndex + 7] = a->forceSystems4D[j]->position4d.w;
		}
		forcesStartIndex += a->forceSystems4D.size();

		masss[i] = a->mass;
		momentInertiaScalars[i] = a->momentInertiaScalar;
		massCenters[4 * i] = a->massCenter.x, massCenters[4 * i + 1] = a->massCenter.y, massCenters[4 * i + 2] = a->massCenter.z, massCenters[4 * i + 3] = a->massCenter.w;
		velocitys4D[4 * i] = a->velocity4d.x, velocitys4D[4 * i + 1] = a->velocity4d.y, velocitys4D[4 * i + 2] = a->velocity4d.z, velocitys4D[4 * i + 3] = a->velocity4d.w;
		angularVelocitys4D[6 * i] = a->angularVelocity4D.xy, angularVelocitys4D[6 * i + 1] = a->angularVelocity4D.xz, angularVelocitys4D[6 * i + 2] = a->angularVelocity4D.xw, angularVelocitys4D[6 * i + 3] = a->angularVelocity4D.yz, angularVelocitys4D[6 * i + 4] = a->angularVelocity4D.yw, angularVelocitys4D[6 * i + 5] = a->angularVelocity4D.zw;

		sizesOfPairs[i] = a->rigidBodyIndices.size() + a->wallIndices.size() + 1;
		pairsStartIndices[i] = pairsStartIndex;
		for (size_t j(0); j < a->rigidBodyIndices.size(); j++)
		{
			int pIndex = 2 * (pairsStartIndex + j);
			pairsVec[pIndex] = i, pairsVec[pIndex+1] = a->rigidBodyIndices[j];
		}
		for (size_t j(0); j < a->wallIndices.size(); j++)
		{
			int pIndex = 2 * (pairsStartIndex + a->rigidBodyIndices.size() + j);
			pairsVec[pIndex] = i, pairsVec[pIndex+1] = a->wallIndices[j] + sizeOfRigidBodies;
		}
		int pIndex = 2 * (pairsStartIndex + a->rigidBodyIndices.size() + a->wallIndices.size());
		pairsVec[pIndex] = i, pairsVec[pIndex + 1] = -1;
		pairsStartIndex += a->rigidBodyIndices.size() + a->wallIndices.size() + 1;
	}
	for (int i(0); i < sizeOfRigidBodiesAndWalls; i++)
	{
		Object4D* a(find_object4d(rigidBodies4d, walls4d, i));
		positions4D[4 * i] = a->position4d.x, positions4D[4 * i + 1] = a->position4d.y, positions4D[4 * i + 2] = a->position4d.z, positions4D[4 * i + 3] = a->position4d.w;
		rotations4D[8 * i] = a->rotation4D.s, rotations4D[8 * i + 1] = a->rotation4D.b.xy, rotations4D[8 * i + 2] = a->rotation4D.b.xz, rotations4D[8 * i + 3] = a->rotation4D.b.xw, rotations4D[8 * i + 4] = a->rotation4D.b.yz, rotations4D[8 * i + 5] = a->rotation4D.b.yw, rotations4D[8 * i + 6] = a->rotation4D.b.zw, rotations4D[8 * i + 7] = a->rotation4D.q.xyzw;
		scales4D[4 * i] = a->scale4D.x, scales4D[4 * i + 1] = a->scale4D.y, scales4D[4 * i + 2] = a->scale4D.z, scales4D[4 * i + 3] = a->scale4D.w;
		restitutions[i] = a->restitution;
		mus[i] = a->mu;
		colTypes[i] = a->colType;
		primitiveIds[i] = a->primitive4D.id;
	}

	sizeList[25] = 2 * sizeof(int) * pairsStartIndex;
	sizeList[26] = sizeof(int) * pairsStartIndex;
	sizeList[27] = sizeof(int) * pairsStartIndex;

	const float dt = 1 / 60.f;
	bool isTimeToSleep(false);
	timeToSleep += dt;
	if (timeToSleep > 2.f)
	{
		isTimeToSleep = true;
		timeToSleep = 0.f;
	}

	update_cuda(pairsStartIndex, sizeList, sizeList2, isTimeToSleep, dt, sizeOfRigidBodies);

	for (int i(0); i < sizeOfRigidBodies; i++)
	{
		RigidBody4D* a(rigidBodies4d[i]);
		if (!isSleeps[i] && !isStatics[i])
		{
			a->set_position4D(glm::vec4(positions4D[4 * i], positions4D[4 * i + 1], positions4D[4 * i + 2], positions4D[4 * i + 3]));
			a->set_rotation4D(alg::rotor4(rotations4D[8 * i], alg::bivec4(rotations4D[8 * i + 1], rotations4D[8 * i + 2], rotations4D[8 * i + 3], rotations4D[8 * i + 4], rotations4D[8 * i + 5], rotations4D[8 * i + 6]), alg::quadvec4(rotations4D[8 * i + 7]))
				, glm::mat4(mats4[16 * i], mats4[16 * i + 1], mats4[16 * i + 2], mats4[16 * i + 3], mats4[16 * i + 4], mats4[16 * i + 5], mats4[16 * i + 6], mats4[16 * i + 7], mats4[16 * i + 8], mats4[16 * i + 9], mats4[16 * i + 10], mats4[16 * i + 11], mats4[16 * i + 12], mats4[16 * i + 13], mats4[16 * i + 14], mats4[16 * i + 15]));
		}
		a->isSleep = isSleeps[i];
		a->isContinueSleep = isContinueSleeps[i];
		for (size_t j(0); j < a->forceSystems4D.size(); j++)a->forceSystems4D[j] = nullptr, free(a->forceSystems4D[j]); a->forceSystems4D.clear();
		a->velocity4d = glm::vec4(velocitys4D[4 * i], velocitys4D[4 * i + 1], velocitys4D[4 * i + 2], velocitys4D[4 * i + 3]);
		a->angularVelocity4D = alg::bivec4(angularVelocitys4D[6 * i], angularVelocitys4D[6 * i + 1], angularVelocitys4D[6 * i + 2], angularVelocitys4D[6 * i + 3], angularVelocitys4D[6 * i + 4], angularVelocitys4D[6 * i + 5]);
	}
	for (size_t i(0); i < collisionsVec->size(); i++)
	{
		collisionsVec[i].clear();
	}
	collisionsVec->clear();
	for (int j(0); j < sizesOfPairs[0]; j++)
	{
		//std::cout << "j=" << j << "collisionSize=" << sizesOfCollisionsVec[j] << '\n';
		if (sizesOfCollisionsVec[j] > 0)
		{
			std::vector<Collision> collisions;
			for (int i(0); i < sizesOfCollisionsVec[j]; i++)
			{
				size_t indexI = 3 * (32 * j + i);
				size_t indexF = 15 * (32 * j + i);
				collisions.push_back(Collision(pairsVec[2 * j], pairsVec[2 * j + 1], 0.f, 0.f, glm::vec4(collisionsVecFloatArray[indexF + 2], collisionsVecFloatArray[indexF + 3], collisionsVecFloatArray[indexF + 4], collisionsVecFloatArray[indexF + 5]), 0.f, glm::vec4(0.f), glm::vec4(0.f)));
			}
			collisionsVec->push_back(collisions);
		}
	}
}