#pragma once
#include "algebra.cu"

//__device__ static struct _d_ForceSystem4D
//{
//	vec4 force4D;
//	vec4 position4d;
//	//explicit _d_ForceSystem4D(vec4 force4D, vec4 position4d)
//	//{
//	//	this->force4D = force4D;
//	//	this->position4d = position4d;
//	//};
//};

__device__ static struct _d_RigidBody4D
{
	vec4 position4d;
	rotor4 rotation4D;
	vec4 scale4D;
	bool isGravity;
	bool isStatic;
	bool isSleep;
	bool isContinueSleep;
	int sizeOfForces;
	int forcesStartIndex;
	float mass;
	float momentInertiaScalar;
	float restitution;
	float mu;
	vec4 massCenter;
	vec4 velocity4d;
	bivec4 angularVelocity4D;
	int colType;
	int primitiveId;
	__device__ explicit _d_RigidBody4D(
		vec4 position4d,
		rotor4 rotation4D,
		vec4 scale4D,
		bool isGravity,
		bool isStatic,
		bool isSleep,
		bool isContinueSleep,
		int sizeOfForces,
		int forcesStartIndex,
		float mass,
		float momentInertiaScalar,
		float restitution,
		float mu,
		vec4 massCenter,
		vec4 velocity4d,
		bivec4 angularVelocity4D,
		int colType,
	    int primitiveId
		)
	{
		this->position4d = position4d;
		this->rotation4D = rotation4D;
		this->scale4D = scale4D;
		this->isGravity = isGravity;
		this->isStatic = isStatic;
		this->isSleep = isSleep;
		this->isContinueSleep = isContinueSleep;
		this->sizeOfForces = sizeOfForces;
		this->forcesStartIndex = forcesStartIndex;
		this->mass = mass;
		this->momentInertiaScalar = momentInertiaScalar;
		this->restitution = restitution;
		this->mu = mu;
		this->massCenter = massCenter;
		this->velocity4d = velocity4d;
		this->angularVelocity4D = angularVelocity4D;
		this->colType = colType;
		this->primitiveId = primitiveId;
	}
	__device__ explicit _d_RigidBody4D(
		vec4 position4d,
		rotor4 rotation4D,
		vec4 scale4D,
		float restitution,
		float mu,
		int colType,
		int primitiveId
	)
	{
		this->position4d = position4d;
		this->rotation4D = rotation4D;
		this->scale4D = scale4D;
		this->isStatic = true;
		this->restitution = restitution;
		this->mu = mu;
		this->colType = colType;
		this->primitiveId = primitiveId;
	}
	__device__ bool is_dynamic()
	{
		return !(this->isStatic || this->isSleep);
	}
};

__device__ static struct _d_HingeConstraint4D
{
	vec4 worldPosition4D;
	vec4 bodyPosition4D1;
	vec4 bodyPosition4D2;
	int index1;
	int index2;
	vec4 normal;
	float depth;
	__device__ explicit _d_HingeConstraint4D(
		vec4 worldPosition4D,
		vec4 bodyPosition4D1,
		vec4 bodyPosition4D2,
		int index1,
		int index2,
		vec4 normal,
		float depth
	)
	{
		this->worldPosition4D = worldPosition4D;
		this->bodyPosition4D1 = bodyPosition4D1;
		this->bodyPosition4D2 = bodyPosition4D2;
		this->index1 = index1;
		this->index2 = index2;
		this->normal = normal;
		this->depth = depth;
	}
};


__device__ static vec4 body_vec_to_world(rotor4 r, vec4 v)
{
	return rotate(r, v);
}

__device__ static vec4 world_vec_to_body(rotor4 r, vec4 v)
{
	return rotate(r.reverse(), v);
}

__device__ static vec4 body_pos_to_world(rotor4 r, vec4 position4d, vec4 v)
{
	return rotate(r, v) + position4d;
}

__device__ static vec4 world_pos_to_body(rotor4 r, vec4 position4d, vec4 v)
{
	return rotate(r.reverse(), v - position4d);
}

__device__ static vec4 body_vec_to_world(_d_RigidBody4D a, vec4 v)
{
	return rotate(a.rotation4D, v);
}

__device__ static vec4 world_vec_to_body(_d_RigidBody4D a, vec4 v)
{
	return rotate(a.rotation4D.reverse(), v);
}

__device__ static vec4 body_pos_to_world(_d_RigidBody4D a, vec4 v)
{
	return rotate(a.rotation4D, v) + a.position4d;
}

__device__ static vec4 world_pos_to_body(_d_RigidBody4D a, vec4 v)
{
	return rotate(a.rotation4D.reverse(), v - a.position4d);
}

__device__ static vec4 inverse_moment_of_mass(float mass, vec4 force4D, const float dt)
{
	return mass > 0.f ? force4D * dt / mass : vec4(0.f);
}

__device__ static bivec4 inverse_moment_of_inertia(_d_RigidBody4D a, bivec4 bodyBivec)
{
	return a.momentInertiaScalar > 0.f ? bodyBivec / a.momentInertiaScalar : bivec4();
}

__device__ static bivec4 inverse_moment_of_inertia(float momentInertiaScalar, bivec4 bodyBivec)
{
	return momentInertiaScalar > 0.f ? bodyBivec / momentInertiaScalar : bivec4();
}

__device__ static float get_moment_inertia_scalar(_d_RigidBody4D a, bivec4 angularVelocity4D)
{
	if (a.momentInertiaScalar > 0.f)
	{
		float lengthOfAngularVelocity4D(length(angularVelocity4D));
		if (lengthOfAngularVelocity4D == 0.f) {
			float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
			return a.mass * radius * radius / 5.f;
		}
		if(a.colType==3)//SPHERE4D:
		{
			float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
			return 1.5f * a.mass * radius * radius / 5.f;
		}
		else if (a.colType == 1)//BOX4D:
		{
			//std::cout << "alg::bivec4(" << angularVelocity4D.xy << "," << angularVelocity4D.xz << "," << angularVelocity4D.xw << "," << angularVelocity4D.yz << "," << angularVelocity4D.yw << "," << angularVelocity4D.zw << ")" << '\n';
			float momentInertiaScalarXY((a.scale4D.x * a.scale4D.x + a.scale4D.y * a.scale4D.y) * a.mass / 12.f);
			float momentInertiaScalarXZ((a.scale4D.x * a.scale4D.x + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarXW((a.scale4D.x * a.scale4D.x + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarYZ((a.scale4D.y * a.scale4D.y + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarYW((a.scale4D.y * a.scale4D.y + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarZW((a.scale4D.z * a.scale4D.z + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
				_d_abs(angularVelocity4D.xy) * momentInertiaScalarXY +
				_d_abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
				_d_abs(angularVelocity4D.xw) * momentInertiaScalarXW +
				_d_abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
				_d_abs(angularVelocity4D.yw) * momentInertiaScalarYW +
				_d_abs(angularVelocity4D.zw) * momentInertiaScalarZW
				) / (_d_abs(angularVelocity4D.xy) + _d_abs(angularVelocity4D.xz) + _d_abs(angularVelocity4D.xw) + _d_abs(angularVelocity4D.yz) + _d_abs(angularVelocity4D.yw) + _d_abs(angularVelocity4D.zw)) : a.mass / 6.f);
			return momentInertiaScalar0;
		}
		else if (a.colType == 2)// STEP4D:
		{
			float momentInertiaScalarXY((a.scale4D.x * a.scale4D.x + a.scale4D.y * a.scale4D.y) * a.mass / 12.f);
			float momentInertiaScalarXZ((a.scale4D.x * a.scale4D.x + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarXW((a.scale4D.x * a.scale4D.x + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarYZ((a.scale4D.y * a.scale4D.y + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarYW((a.scale4D.y * a.scale4D.y + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarZW((a.scale4D.z * a.scale4D.z + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
				_d_abs(angularVelocity4D.xy) * momentInertiaScalarXY +
				_d_abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
				_d_abs(angularVelocity4D.xw) * momentInertiaScalarXW +
				_d_abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
				_d_abs(angularVelocity4D.yw) * momentInertiaScalarYW +
				_d_abs(angularVelocity4D.zw) * momentInertiaScalarZW
				) / (_d_abs(angularVelocity4D.xy) + _d_abs(angularVelocity4D.xz) + _d_abs(angularVelocity4D.xw) + _d_abs(angularVelocity4D.yz) + _d_abs(angularVelocity4D.yw) + _d_abs(angularVelocity4D.zw)) : a.mass / 6.f);
			return momentInertiaScalar0;
		}
		else if (a.colType == 4)//MESH4D:
		{
			float momentInertiaScalarXY((a.scale4D.x * a.scale4D.x + a.scale4D.y * a.scale4D.y) * a.mass / 12.f);
			float momentInertiaScalarXZ((a.scale4D.x * a.scale4D.x + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarXW((a.scale4D.x * a.scale4D.x + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarYZ((a.scale4D.y * a.scale4D.y + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarYW((a.scale4D.y * a.scale4D.y + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarZW((a.scale4D.z * a.scale4D.z + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
				_d_abs(angularVelocity4D.xy) * momentInertiaScalarXY +
				_d_abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
				_d_abs(angularVelocity4D.xw) * momentInertiaScalarXW +
				_d_abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
				_d_abs(angularVelocity4D.yw) * momentInertiaScalarYW +
				_d_abs(angularVelocity4D.zw) * momentInertiaScalarZW
				) / (_d_abs(angularVelocity4D.xy) + _d_abs(angularVelocity4D.xz) + _d_abs(angularVelocity4D.xw) + _d_abs(angularVelocity4D.yz) + _d_abs(angularVelocity4D.yw) + _d_abs(angularVelocity4D.zw)) : a.mass / 6.f);
			return (momentInertiaScalar0) / 1.5f;
		}
		else if (a.colType == 5)//CAPSULE4D:
		{
			float momentInertiaScalarXY((a.scale4D.x * a.scale4D.x + a.scale4D.y * a.scale4D.y) * a.mass / 12.f);
			float momentInertiaScalarXZ((a.scale4D.x * a.scale4D.x + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarXW((a.scale4D.x * a.scale4D.x + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarYZ((a.scale4D.y * a.scale4D.y + a.scale4D.z * a.scale4D.z) * a.mass / 12.f);
			float momentInertiaScalarYW((a.scale4D.y * a.scale4D.y + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalarZW((a.scale4D.z * a.scale4D.z + a.scale4D.w * a.scale4D.w) * a.mass / 12.f);
			float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
				_d_abs(angularVelocity4D.xy) * momentInertiaScalarXY +
				_d_abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
				_d_abs(angularVelocity4D.xw) * momentInertiaScalarXW +
				_d_abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
				_d_abs(angularVelocity4D.yw) * momentInertiaScalarYW +
				_d_abs(angularVelocity4D.zw) * momentInertiaScalarZW
				) / (_d_abs(angularVelocity4D.xy) + _d_abs(angularVelocity4D.xz) + _d_abs(angularVelocity4D.xw) + _d_abs(angularVelocity4D.yz) + _d_abs(angularVelocity4D.yw) + _d_abs(angularVelocity4D.zw)) : a.mass / 6.f);
			return momentInertiaScalar0;
		}
	}
	else
	{
		return a.momentInertiaScalar;
	}
}

__device__ static void update_rigidbody_velocity4D(_d_RigidBody4D* a, float* forceSystems4D, const float dt)
{
	if (a->sizeOfForces > 0)
	{
		a->isSleep = a->isContinueSleep = false;
		for (int i(0); i < a->sizeOfForces; i++)
		{
			int forceIndex(8 * (a->forcesStartIndex + i));
			vec4 force4D = vec4(forceSystems4D[forceIndex], forceSystems4D[forceIndex + 1], forceSystems4D[forceIndex + 2], forceSystems4D[forceIndex + 3]);
			vec4 position4d = vec4(forceSystems4D[forceIndex + 4], forceSystems4D[forceIndex + 5], forceSystems4D[forceIndex + 6], forceSystems4D[forceIndex + 7]);
			a->velocity4d = a->velocity4d + (a->mass > 0.f ? force4D * dt / a->mass : vec4(0.f));
			if (position4d != vec4(0.f))
			{
				bivec4 angularVelocityAdd4D(wedge_v(position4d - a->massCenter, rotate(a->rotation4D.reverse(), force4D * dt)));
				float momentInertiaScalar(get_moment_inertia_scalar(*a, angularVelocityAdd4D));
				a->angularVelocity4D = a->angularVelocity4D + inverse_moment_of_inertia(momentInertiaScalar, angularVelocityAdd4D);
			}
		}
	}
}

//static alg::bivec4 update_angular_velocity4D(RigidBody4D* b, vec4 force4D,vec4 forcePosition4D,const float dt)
//{
//    alg::bivec4 bodyBivec(wedge_v(alg::vec4(forcePosition4D), rotate(b->rotation4D.reverse(), alg::vec4(dt * force4D))));
//    float momentInertiaScalar(get_moment_inertia_scalar(b));
//    if (b->momentInertiaScalar > 0.f) return  b->angularVelocity4D+bodyBivec / momentInertiaScalar;
//    else return b->angularVelocity4D;
//}

__device__ static void resolve_impulse(_d_RigidBody4D* b, vec4 impulse, vec4 bodyContact)
{
	b->velocity4d = b->velocity4d + (b->mass > 0.f ? impulse / b->mass : vec4(0.f));
	b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(*b, wedge_v(bodyContact - b->massCenter, rotate(b->rotation4D.reverse(), impulse)));
}

__device__ static void resolve_impulse(_d_RigidBody4D* b, vec4 impulse, vec4 bodyContact, float momentInertiaScalar)
{
	b->velocity4d = b->velocity4d + (b->mass > 0.f ? impulse / b->mass : vec4(0.f));
	b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(momentInertiaScalar, wedge_v(bodyContact - b->massCenter, rotate(b->rotation4D.reverse(), impulse)));
}

__device__ static void resolve_impulse(_d_RigidBody4D b, int index, float* velocitys4D, float* angularVelocitys4D, vec4 impulse, vec4 bodyContact, float momentInertiaScalar)
{
	vec4 velocity4DOfPlus(b.mass > 0.f ? impulse / b.mass : vec4(0.f));
	bivec4 angularVelocity4OfPlus(inverse_moment_of_inertia(momentInertiaScalar, wedge_v(bodyContact - b.massCenter, rotate(b.rotation4D.reverse(), impulse))));
	//velocitys4D[4 * index] += velocity4DOfPlus.x, velocitys4D[4 * index + 1] += velocity4DOfPlus.y, velocitys4D[4 * index + 2] += velocity4DOfPlus.z, velocitys4D[4 * index + 3] += velocity4DOfPlus.w;
	atomicAdd(&velocitys4D[4 * index], velocity4DOfPlus.x), atomicAdd(&velocitys4D[4 * index + 1], velocity4DOfPlus.y), atomicAdd(&velocitys4D[4 * index + 2], velocity4DOfPlus.z), atomicAdd(&velocitys4D[4 * index + 3], velocity4DOfPlus.w);
	//b->velocity4d = b->velocity4d + velocity4DOfPlus;
	atomicAdd(&angularVelocitys4D[6 * index], angularVelocity4OfPlus.xy), atomicAdd(&angularVelocitys4D[6 * index + 1], angularVelocity4OfPlus.xz), atomicAdd(&angularVelocitys4D[6 * index + 2], angularVelocity4OfPlus.xw), atomicAdd(&angularVelocitys4D[6 * index + 3], angularVelocity4OfPlus.yz), atomicAdd(&angularVelocitys4D[6 * index + 4], angularVelocity4OfPlus.yw), atomicAdd(&angularVelocitys4D[6 * index + 5], angularVelocity4OfPlus.zw);
	//b->angularVelocity4D = b->angularVelocity4D + angularVelocity4OfPlus;
}

__device__ static void resolve_impulse(_d_RigidBody4D* b, vec4 impulse)
{
	b->velocity4d = b->velocity4d + (b->mass > 0.f ? impulse / b->mass : vec4(0.f));
}

__device__ static void resolve_impulse0(_d_RigidBody4D* b, vec4 impulse, vec4 worldContact)
{
	b->velocity4d = b->velocity4d + (b->mass > 0.f ? impulse / b->mass : vec4(0.f));
	b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(*b, wedge_v(world_pos_to_body(*b, worldContact - b->massCenter), rotate(b->rotation4D.reverse(), impulse)));
}

__device__ static vec4 vel_at(_d_RigidBody4D b, vec4 bodyPos)
{
	vec4 rotVel(body_vec_to_world(b, left_contract_bv(bodyPos - b.massCenter, b.angularVelocity4D)));
	return b.velocity4d + rotVel;
}

__device__ static vec4 vel_at(_d_RigidBody4D b, int index, float* velocitys4D, float* angularVelocitys4D, vec4 bodyPos)
{
	vec4 velocity4d = vec4(velocitys4D[4 * index], velocitys4D[4 * index + 1], velocitys4D[4 * index + 2], velocitys4D[4 * index + 3]);
	bivec4 angularVelocity4D = bivec4(angularVelocitys4D[6 * index], angularVelocitys4D[6 * index + 1], angularVelocitys4D[6 * index + 2], angularVelocitys4D[6 * index + 3], angularVelocitys4D[6 * index + 4], angularVelocitys4D[6 * index + 5]);
	vec4 rotVel(body_vec_to_world(b, left_contract_bv(bodyPos - b.massCenter, angularVelocity4D)));
	return velocity4d + rotVel;
}

__device__ static vec4 vel_at_world(_d_RigidBody4D b, vec4 worldPos)
{
	vec4 bodyPos(world_pos_to_body(b, worldPos));
	vec4 rotVel(body_vec_to_world(b, left_contract_bv(bodyPos - b.massCenter, b.angularVelocity4D)));
	return b.velocity4d + rotVel;
}

__device__ static struct _d_Edge4D
{
	vec4 vertices4D[2];
};

__device__ static struct _d_Face4D
{
	vec4 vertices4D[3];
};

__device__ static struct _d_Tetra4D
{
	vec4 vertices4D[4];
};

__device__ static struct _d_Cube4D
{
	vec4 vertices4D[4];
	vec4 normal4D;
	int direction4D;
};

__device__ static vec4 hypercube_vertices4D(int n)
{
	if (n == 0)return vec4(-0.5f, -0.5f, 0.5f, -0.5f);
	else if (n == 1)return vec4(0.5f, -0.5f, 0.5f, -0.5f);
	else if (n == 2)return vec4(0.5f, -0.5f, -0.5f, -0.5f);
	else if (n == 3)return vec4(-0.5f, -0.5f, -0.5f, -0.5f);
	else if (n == 4)return vec4(-0.5f, 0.5f, 0.5f, -0.5f);
	else if (n == 5)return vec4(0.5f, 0.5f, 0.5f, -0.5f);
	else if (n == 6)return vec4(0.5f, 0.5f, -0.5f, -0.5f);
	else if (n == 7)return vec4(-0.5f, 0.5f, -0.5f, -0.5f);
	else if (n == 8)return vec4(-0.5f, -0.5f, 0.5f, 0.5f);
	else if (n == 9)return vec4(0.5f, -0.5f, 0.5f, 0.5f);
	else if (n == 10)return vec4(0.5f, -0.5f, -0.5f, 0.5f);
	else if (n == 11)return vec4(-0.5f, -0.5f, -0.5f, 0.5f);
	else if (n == 12)return vec4(-0.5f, 0.5f, 0.5f, 0.5f);
	else if (n == 13)return vec4(0.5f, 0.5f, 0.5f, 0.5f);
	else if (n == 14)return vec4(0.5f, 0.5f, -0.5f, 0.5f);
	else if (n == 15)return vec4(-0.5f, 0.5f, -0.5f, 0.5f);
}

__device__ static _d_Edge4D edges4D(int n)
{
	if (n == 0)return { vec4(0.5f, 0.5f, 0.5f, 0.5f), vec4(-0.5f, 0.5f, 0.5f, 0.5f) };//0
	else if (n == 1)return { vec4(0.5f, -0.5f, 0.5f, 0.5f), vec4(-0.5f, -0.5f, 0.5f, 0.5f) };
	else if (n == 2)return { vec4(0.5f, 0.5f, -0.5f, 0.5f), vec4(-0.5f, 0.5f, -0.5f, 0.5f) };
	else if (n == 3)return { vec4(0.5f, 0.5f, 0.5f, -0.5f), vec4(-0.5f, 0.5f, 0.5f, -0.5f) };
	else if (n == 4)return { vec4(0.5f, -0.5f, -0.5f, 0.5f), vec4(-0.5f, -0.5f, -0.5f, 0.5f) };
	else if (n == 5)return { vec4(0.5f, -0.5f, 0.5f, -0.5f), vec4(-0.5f, -0.5f, 0.5f, -0.5f) };
	else if (n == 6)return { vec4(0.5f, 0.5f, -0.5f, -0.5f), vec4(-0.5f, 0.5f, -0.5f, -0.5f) };
	else if (n == 7)return { vec4(0.5f, -0.5f, -0.5f, -0.5f), vec4(-0.5f, -0.5f, -0.5f, -0.5f) };

	else if (n == 8)return { vec4(0.5f, 0.5f, 0.5f, 0.5f), vec4(0.5f, -0.5f, 0.5f, 0.5f) };//8
	else if (n == 9)return { vec4(-0.5f, 0.5f, 0.5f, 0.5f), vec4(-0.5f, -0.5f, 0.5f, 0.5f) };
	else if (n == 10)return { vec4(0.5f, 0.5f, -0.5f, 0.5f), vec4(0.5f, -0.5f, -0.5f, 0.5f) };
	else if (n == 11)return { vec4(0.5f, 0.5f, 0.5f, -0.5f), vec4(0.5f, -0.5f, 0.5f, -0.5f) };
	else if (n == 12)return { vec4(-0.5f, 0.5f, -0.5f, 0.5f), vec4(-0.5f, -0.5f, -0.5f, 0.5f) };
	else if (n == 13)return { vec4(-0.5f, 0.5f, 0.5f, -0.5f), vec4(-0.5f, -0.5f, 0.5f, -0.5f) };
	else if (n == 14)return { vec4(0.5f, 0.5f, -0.5f, -0.5f), vec4(0.5f, -0.5f, -0.5f, -0.5f) };
	else if (n == 15)return { vec4(-0.5f, 0.5f, -0.5f, -0.5f), vec4(-0.5f, -0.5f, -0.5f, -0.5f) };

	else if (n == 16)return { vec4(0.5f, 0.5f,  0.5f,0.5f), vec4(0.5f, 0.5f,  -0.5f,0.5f) }; //16
	else if (n == 17)return { vec4(-0.5f, 0.5f, 0.5f,0.5f), vec4(-0.5f, 0.5f, -0.5f,0.5f) };
	else if (n == 18)return { vec4(0.5f, -0.5f, 0.5f,0.5f), vec4(0.5f, -0.5f, -0.5f,0.5f) };
	else if (n == 19)return { vec4(0.5f, 0.5f, 0.5f, -0.5f), vec4(0.5f, 0.5f, -0.5f, -0.5f) };
	else if (n == 20)return { vec4(-0.5f, -0.5f, 0.5f, 0.5f), vec4(-0.5f, -0.5f, -0.5f, 0.5f) };
	else if (n == 21)return { vec4(-0.5f, 0.5f, 0.5f,-0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f) };
	else if (n == 22)return { vec4(0.5f, -0.5f, 0.5f,-0.5f),vec4(0.5f, -0.5f, -0.5f,-0.5f) };
	else if (n == 23)return { vec4(-0.5f, -0.5f,0.5f,-0.5f),vec4(-0.5f, -0.5f,-0.5f,-0.5f) };

	else if (n == 24)return { vec4(0.5f, 0.5f,  0.5f ,0.5f),vec4(0.5f, 0.5f,  0.5f ,-0.5f) }; //24
	else if (n == 25)return { vec4(-0.5f, 0.5f, 0.5f ,0.5f),vec4(-0.5f, 0.5f, 0.5f ,-0.5f) };
	else if (n == 26)return { vec4(0.5f, -0.5f, 0.5f ,0.5f),vec4(0.5f, -0.5f, 0.5f ,-0.5f) };
	else if (n == 27)return { vec4(0.5f, 0.5f,  -0.5f,0.5f),vec4(0.5f, 0.5f,  -0.5f,-0.5f) };
	else if (n == 28)return { vec4(-0.5f, -0.5f,0.5f ,0.5f),vec4(-0.5f, -0.5f,0.5f ,-0.5f) };
	else if (n == 29)return { vec4(-0.5f, 0.5f, -0.5f,0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f) };
	else if (n == 30)return { vec4(0.5f, -0.5f, -0.5f,0.5f),vec4(0.5f, -0.5f, -0.5f,-0.5f) };
	else if (n == 31)return { vec4(-0.5f, -0.5f,-0.5f,0.5f),vec4(-0.5f, -0.5f,-0.5f,-0.5f) };
}
__device__ static _d_Face4D faces4D(int n)
{
	if(n==0) return {vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f)};
	else if(n==1) return {vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f)};
	else if(n==2) return {vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f)};
	else if(n==3) return {vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f)};
	else if(n==4) return {vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f)};
	else if(n==5) return {vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f)};
	else if(n==6) return {vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f)};
	else if(n==7) return {vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, 0.5f,-0.5f)};
	else if(n==8) return {vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f)};
	else if(n==9) return {vec4(-0.5f, 0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, 0.5f,-0.5f)};
	else if(n==10) return {vec4(-0.5f, 0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f)};
	else if(n==11) return {vec4(-0.5f, -0.5f, 0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f)};
	else if(n==12) return {vec4(-0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, -0.5f, -0.5f,0.5f)};
	else if(n==13) return {vec4(-0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, -0.5f,0.5f)};
	else if(n==14) return {vec4(-0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,-0.5f)};
	else if(n==15) return {vec4(-0.5f, -0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, -0.5f,0.5f)};
	else if(n==16) return {vec4(-0.5f, -0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,-0.5f)};
	else if(n==17) return {vec4(-0.5f, 0.5f, -0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,-0.5f)};
	else if(n==18) return {vec4(-0.5f, 0.5f, 0.5f,-0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(0.5f, -0.5f, 0.5f,-0.5f)};
	else if(n==19) return {vec4(-0.5f, 0.5f, 0.5f,-0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(0.5f, 0.5f, -0.5f,-0.5f)};
	else if(n==20) return {vec4(-0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,-0.5f)};
	else if(n==21) return {vec4(0.5f, -0.5f, 0.5f,-0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(0.5f, 0.5f, -0.5f,-0.5f)};
	else if(n==22) return {vec4(0.5f, -0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,-0.5f)};
	else if(n==23) return {vec4(0.5f, -0.5f, -0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,-0.5f)};
}
__device__ static _d_Cube4D cubes4D(int n)
{
	if(n==0) return { vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, 0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f),vec4(-1.f, 0.f, 0.f,0.f),0};
	else if(n==1) return { vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, 0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f),vec4(0.f, -1.f, 0.f,0.f),1};
	else if(n==2) return { vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, -0.5f,0.5f),vec4(0.f, 0.f, -1.f,0.f),2};
	else if(n==3) return { vec4(-0.5f, -0.5f, -0.5f,-0.5f),vec4(0.5f, -0.5f, -0.5f,-0.5f),vec4(-0.5f, 0.5f, -0.5f,-0.5f),vec4(-0.5f, -0.5f, 0.5f,-0.5f),vec4(0.f, 0.f, 0.f,-1.f),3};
	else if(n==4) return { vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(1.f, 0.f, 0.f,0.f),4};
	else if(n==5) return { vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(0.f, 1.f, 0.f,0.f),5};
	else if(n==6) return { vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, 0.5f,-0.5f),vec4(0.f, 0.f, 1.f,0.f),6};
	else if(n==7) return { vec4(0.5f, 0.5f, 0.5f,0.5f),vec4(-0.5f, 0.5f, 0.5f,0.5f),vec4(0.5f, -0.5f, 0.5f,0.5f),vec4(0.5f, 0.5f, -0.5f,0.5f),vec4(0.f, 0.f, 0.f,1.f),7};
}

__device__ static vec4 get_vertex(int primitiveId, int index, float* vertices4DsVec, int* verticesStartIndices)
{
	index = 4 * (verticesStartIndices[primitiveId] + index);
	return vec4(vertices4DsVec[index], vertices4DsVec[index + 1], vertices4DsVec[index + 2], vertices4DsVec[index + 3]);
}