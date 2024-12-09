#pragma once
#include"mod.h"

    static glm::vec4 body_vec_to_world(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D, alg::vec4(v)).transform();
    }

    static glm::vec4 body_vec_to_world(alg::rotor4 r, glm::vec4 v)
    {
        return rotate(r, alg::vec4(v)).transform();
    }

    static glm::vec4 world_vec_to_body(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D.reverse(), alg::vec4(v)).transform();
    }

    static glm::vec4 body_pos_to_world(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D, alg::vec4(v)).transform() + b->position4D;
    }

    static glm::vec4 world_pos_to_body(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D.reverse(), alg::vec4(v - b->position4D)).transform();
    }

    static glm::vec4 inverse_moment_of_mass(RigidBody4D* b, glm::vec4 force4D,const float dt)
    {
        return b->mass > 0.f ? force4D * dt / b->mass : glm::vec4(0.f);
    }

    static alg::bivec4 inverse_moment_of_inertia(RigidBody4D* b, alg::bivec4 bodyBivec)
    {
        return b->momentInertiaScalar > 0.f ? bodyBivec / b->momentInertiaScalar : alg::bivec4();
    }

	static alg::bivec4 inverse_moment_of_inertia(float momentInertiaScalar, alg::bivec4 bodyBivec)
	{
		return momentInertiaScalar > 0.f ? bodyBivec / momentInertiaScalar : alg::bivec4();
	}

    static float get_moment_inertia_scalar(RigidBody4D* a, glm::vec4 bodyPos, alg::bivec4 angularVelocity4D, alg::bivec4 angularVelocityAdd4D)
    {
		if (a->momentInertiaScalar > 0.f)
		{
			float lengthOfAngularVelocity4D(length(angularVelocity4D));
			if (lengthOfAngularVelocity4D < 0.05f) {
				lengthOfAngularVelocity4D = length(angularVelocityAdd4D);
				angularVelocity4D = angularVelocityAdd4D;
			}
			float rotVel(length(left_contract_bv(alg::vec4(bodyPos - a->massCenter), angularVelocity4D / lengthOfAngularVelocity4D).transform()));
			float distance;
			if (rotVel > 0.f) distance = rotVel;
			else return 1000000.f;
			float momentInertiaFromDistance(distance * distance * a->mass);
			switch (a->colType)
			{
			case SPHERE4D:
			{
				float radius(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
				return 1.5f * a->mass * radius * radius / 5.f + momentInertiaFromDistance;
				break;
			}
			case BOX4D:
			{
				float momentInertiaScalarXY((a->scale4D.x * a->scale4D.x + a->scale4D.y * a->scale4D.y) * a->mass / 12.f);
				float momentInertiaScalarXZ((a->scale4D.x * a->scale4D.x + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarXW((a->scale4D.x * a->scale4D.x + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarYZ((a->scale4D.y * a->scale4D.y + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarYW((a->scale4D.y * a->scale4D.y + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarZW((a->scale4D.z * a->scale4D.z + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
					alg::abs(angularVelocity4D.xy) * momentInertiaScalarXY +
					alg::abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
					alg::abs(angularVelocity4D.xw) * momentInertiaScalarXW +
					alg::abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
					alg::abs(angularVelocity4D.yw) * momentInertiaScalarYW +
					alg::abs(angularVelocity4D.zw) * momentInertiaScalarZW
					) / (alg::abs(angularVelocity4D.xy) + alg::abs(angularVelocity4D.xz) + alg::abs(angularVelocity4D.xw) + alg::abs(angularVelocity4D.yz) + alg::abs(angularVelocity4D.yw) + alg::abs(angularVelocity4D.zw)) : a->mass / 6.f);
				return momentInertiaScalar0 + momentInertiaFromDistance;
				break;
			}
			case STEP4D:
			{
				float momentInertiaScalarXY((a->scale4D.x * a->scale4D.x + a->scale4D.y * a->scale4D.y) * a->mass / 12.f);
				float momentInertiaScalarXZ((a->scale4D.x * a->scale4D.x + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarXW((a->scale4D.x * a->scale4D.x + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarYZ((a->scale4D.y * a->scale4D.y + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarYW((a->scale4D.y * a->scale4D.y + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarZW((a->scale4D.z * a->scale4D.z + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
					alg::abs(angularVelocity4D.xy) * momentInertiaScalarXY +
					alg::abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
					alg::abs(angularVelocity4D.xw) * momentInertiaScalarXW +
					alg::abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
					alg::abs(angularVelocity4D.yw) * momentInertiaScalarYW +
					alg::abs(angularVelocity4D.zw) * momentInertiaScalarZW
					) / (alg::abs(angularVelocity4D.xy) + alg::abs(angularVelocity4D.xz) + alg::abs(angularVelocity4D.xw) + alg::abs(angularVelocity4D.yz) + alg::abs(angularVelocity4D.yw) + alg::abs(angularVelocity4D.zw)) : a->mass / 6.f);
				return momentInertiaScalar0 + momentInertiaFromDistance;
				break;
			}
			case MESH4D:
			{
				float momentInertiaScalarXY((a->scale4D.x * a->scale4D.x + a->scale4D.y * a->scale4D.y) * a->mass / 12.f);
				float momentInertiaScalarXZ((a->scale4D.x * a->scale4D.x + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarXW((a->scale4D.x * a->scale4D.x + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarYZ((a->scale4D.y * a->scale4D.y + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarYW((a->scale4D.y * a->scale4D.y + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarZW((a->scale4D.z * a->scale4D.z + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
					alg::abs(angularVelocity4D.xy) * momentInertiaScalarXY +
					alg::abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
					alg::abs(angularVelocity4D.xw) * momentInertiaScalarXW +
					alg::abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
					alg::abs(angularVelocity4D.yw) * momentInertiaScalarYW +
					alg::abs(angularVelocity4D.zw) * momentInertiaScalarZW
					) / (alg::abs(angularVelocity4D.xy) + alg::abs(angularVelocity4D.xz) + alg::abs(angularVelocity4D.xw) + alg::abs(angularVelocity4D.yz) + alg::abs(angularVelocity4D.yw) + alg::abs(angularVelocity4D.zw)) : a->mass / 6.f);
				return (momentInertiaScalar0)/2.f + momentInertiaFromDistance;
				break;
			}
			case CAPSULE4D:
			{
				float momentInertiaScalarXY((a->scale4D.x * a->scale4D.x + a->scale4D.y * a->scale4D.y) * a->mass / 12.f);
				float momentInertiaScalarXZ((a->scale4D.x * a->scale4D.x + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarXW((a->scale4D.x * a->scale4D.x + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarYZ((a->scale4D.y * a->scale4D.y + a->scale4D.z * a->scale4D.z) * a->mass / 12.f);
				float momentInertiaScalarYW((a->scale4D.y * a->scale4D.y + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalarZW((a->scale4D.z * a->scale4D.z + a->scale4D.w * a->scale4D.w) * a->mass / 12.f);
				float momentInertiaScalar0(lengthOfAngularVelocity4D > 0 ? (
					alg::abs(angularVelocity4D.xy) * momentInertiaScalarXY +
					alg::abs(angularVelocity4D.xz) * momentInertiaScalarXZ +
					alg::abs(angularVelocity4D.xw) * momentInertiaScalarXW +
					alg::abs(angularVelocity4D.yz) * momentInertiaScalarYZ +
					alg::abs(angularVelocity4D.yw) * momentInertiaScalarYW +
					alg::abs(angularVelocity4D.zw) * momentInertiaScalarZW
					) / (alg::abs(angularVelocity4D.xy) + alg::abs(angularVelocity4D.xz) + alg::abs(angularVelocity4D.xw) + alg::abs(angularVelocity4D.yz) + alg::abs(angularVelocity4D.yw) + alg::abs(angularVelocity4D.zw)) : a->mass / 6.f);
				return momentInertiaScalar0 + momentInertiaFromDistance;
				break;
			}
			}
		}
    }

    static void update_rigidbody_velocity4D(RigidBody4D* a, const float dt)
    {
        if (!a->is_static())
        {
            for (ForceSystem4D* j : a->forceSystems4D)
            {
                a->velocity4D += a->mass > 0.f ? j->force4D * dt / a->mass : glm::vec4(0.f);
				if (j->position4D != glm::vec4(0.f))
				{
					alg::bivec4 angularVelocityAdd4D(wedge_v(alg::vec4(j->position4D - a->massCenter), rotate(a->rotation4D.reverse(), alg::vec4(dt * j->force4D))));
					float momentInertiaScalar(get_moment_inertia_scalar(a, j->position4D - a->massCenter, angularVelocityAdd4D, angularVelocityAdd4D));
					a->angularVelocity4D = a->angularVelocity4D + inverse_moment_of_inertia(momentInertiaScalar, angularVelocityAdd4D);
				}
            }
            a->forceSystems4D.clear();
        }
    }

    //static alg::bivec4 update_angular_velocity4D(RigidBody4D* b, glm::vec4 force4D,glm::vec4 forcePosition4D,const float dt)
    //{
    //    alg::bivec4 bodyBivec(wedge_v(alg::vec4(forcePosition4D), rotate(b->rotation4D.reverse(), alg::vec4(dt * force4D))));
    //    float momentInertiaScalar(get_moment_inertia_scalar(b));
    //    if (b->momentInertiaScalar > 0.f) return  b->angularVelocity4D+bodyBivec / momentInertiaScalar;
    //    else return b->angularVelocity4D;
    //}

    static void resolve_impulse(RigidBody4D* b, glm::vec4 impulse, glm::vec4 bodyContact)
    {
        b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(bodyContact - b->massCenter), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

	static void resolve_impulse(RigidBody4D* b, glm::vec4 impulse, glm::vec4 bodyContact, float momentInertiaScalar)
	{
		b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
		b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(momentInertiaScalar, wedge_v(alg::vec4(bodyContact - b->massCenter), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
	}

    static void resolve_impulse(RigidBody4D* b, glm::vec4 impulse)
    {
        b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
    }

    static void resolve_impulse0(RigidBody4D* b, glm::vec4 impulse, glm::vec4 worldContact)
    {
        b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(world_pos_to_body(b,worldContact - b->massCenter)), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

    static glm::vec4 vel_at(RigidBody4D* b, glm::vec4 bodyPos)
    {
        glm::vec4 rotVel(body_vec_to_world(b, left_contract_bv(alg::vec4(bodyPos - b->massCenter), b->angularVelocity4D).transform()));
        return b->velocity4D + rotVel;
    }

    static glm::vec4 vel_at_world(RigidBody4D* b, glm::vec4 worldPos)
    {
        glm::vec4 bodyPos(world_pos_to_body(b,worldPos));
        glm::vec4 rotVel(body_vec_to_world(b,left_contract_bv(alg::vec4(bodyPos - b->massCenter), b->angularVelocity4D).transform()));
        return b->velocity4D + rotVel;
    }

    static glm::vec4 get_cap_position4D(glm::vec4 hittingPos,glm::vec2 buildDistance,glm::vec4 buildOffset){
        glm::vec4 wallPos4D(glm::vec4(
            floor(hittingPos.x / buildDistance.x + buildDistance.x) * buildDistance.x, 
            floor(hittingPos.y / buildDistance.y + buildDistance.y) * buildDistance.y, 
            floor(hittingPos.z / buildDistance.x + buildDistance.x) * buildDistance.x, 
            floor(hittingPos.w / buildDistance.x + buildDistance.x) * buildDistance.x) + buildOffset);
        return wallPos4D;
    }

    static glm::vec4 get_cap_position4D(Object4D* obj, bool isFindPoint,glm::vec4 hittingPos, glm::vec2 buildDistance, glm::vec4 buildOffset){
        glm::vec4 bodypos(world_pos_to_body(obj, hittingPos));
        if (obj!=nullptr)return body_pos_to_world(obj, 
            glm::vec4(
                floor(bodypos.x / buildDistance.x + buildDistance.x) * buildDistance.x,
                floor(bodypos.y / buildDistance.y + buildDistance.y) * buildDistance.y,
                floor(bodypos.z / buildDistance.x + buildDistance.x) * buildDistance.x,
                floor(bodypos.w / buildDistance.x + buildDistance.x) * buildDistance.x) + buildOffset
            );
        else if(isFindPoint) return glm::vec4(
            floor(hittingPos.x / buildDistance.x + buildDistance.x) * buildDistance.x, 
            floor(hittingPos.y / buildDistance.y + buildDistance.y) * buildDistance.y, 
            floor(hittingPos.z / buildDistance.x + buildDistance.x) * buildDistance.x, 
            floor(hittingPos.w / buildDistance.x + buildDistance.x) * buildDistance.x) + buildOffset;
    }

	static const glm::vec3 black_body_color[200] = {
			glm::vec3(1, -0.00987248, -0.0166818),
			glm::vec3(1, 0.000671682, -0.0173831),
			glm::vec3(1, 0.0113477, -0.0179839),
			glm::vec3(1, 0.0221357, -0.0184684),
			glm::vec3(1, 0.0330177, -0.0188214),
			glm::vec3(1, 0.0439771, -0.0190283),
			glm::vec3(1, 0.0549989, -0.0190754),
			glm::vec3(1, 0.0660696, -0.0189496),
			glm::vec3(1, 0.0771766, -0.0186391),
			glm::vec3(1, 0.0883086, -0.0181329),
			glm::vec3(1, 0.0994553, -0.017421),
			glm::vec3(1, 0.110607, -0.0164945),
			glm::vec3(1, 0.121756, -0.0153455),
			glm::vec3(1, 0.132894, -0.0139671),
			glm::vec3(1, 0.144013, -0.0123534),
			glm::vec3(1, 0.155107, -0.0104993),
			glm::vec3(1, 0.166171, -0.0084008),
			glm::vec3(1, 0.177198, -0.00605465),
			glm::vec3(1, 0.188184, -0.00345843),
			glm::vec3(1, 0.199125, -0.000610485),
			glm::vec3(1, 0.210015, 0.00249014),
			glm::vec3(1, 0.220853, 0.00584373),
			glm::vec3(1, 0.231633, 0.00944995),
			glm::vec3(1, 0.242353, 0.0133079),
			glm::vec3(1, 0.25301, 0.0174162),
			glm::vec3(1, 0.263601, 0.021773),
			glm::vec3(1, 0.274125, 0.0263759),
			glm::vec3(1, 0.284579, 0.0312223),
			glm::vec3(1, 0.294962, 0.0363091),
			glm::vec3(1, 0.305271, 0.0416328),
			glm::vec3(1, 0.315505, 0.0471899),
			glm::vec3(1, 0.325662, 0.0529765),
			glm::vec3(1, 0.335742, 0.0589884),
			glm::vec3(1, 0.345744, 0.0652213),
			glm::vec3(1, 0.355666, 0.0716707),
			glm::vec3(1, 0.365508, 0.078332),
			glm::vec3(1, 0.375268, 0.0852003),
			glm::vec3(1, 0.384948, 0.0922709),
			glm::vec3(1, 0.394544, 0.0995389),
			glm::vec3(1, 0.404059, 0.106999),
			glm::vec3(1, 0.41349, 0.114646),
			glm::vec3(1, 0.422838, 0.122476),
			glm::vec3(1, 0.432103, 0.130482),
			glm::vec3(1, 0.441284, 0.138661),
			glm::vec3(1, 0.450381, 0.147005),
			glm::vec3(1, 0.459395, 0.155512),
			glm::vec3(1, 0.468325, 0.164175),
			glm::vec3(1, 0.477172, 0.172989),
			glm::vec3(1, 0.485935, 0.181949),
			glm::vec3(1, 0.494614, 0.19105),
			glm::vec3(1, 0.503211, 0.200288),
			glm::vec3(1, 0.511724, 0.209657),
			glm::vec3(1, 0.520155, 0.219152),
			glm::vec3(1, 0.528504, 0.228769),
			glm::vec3(1, 0.536771, 0.238502),
			glm::vec3(1, 0.544955, 0.248347),
			glm::vec3(1, 0.553059, 0.2583),
			glm::vec3(1, 0.561082, 0.268356),
			glm::vec3(1, 0.569024, 0.27851),
			glm::vec3(1, 0.576886, 0.288758),
			glm::vec3(1, 0.584668, 0.299095),
			glm::vec3(1, 0.592372, 0.309518),
			glm::vec3(1, 0.599996, 0.320022),
			glm::vec3(1, 0.607543, 0.330603),
			glm::vec3(1, 0.615012, 0.341257),
			glm::vec3(1, 0.622403, 0.35198),
			glm::vec3(1, 0.629719, 0.362768),
			glm::vec3(1, 0.636958, 0.373617),
			glm::vec3(1, 0.644122, 0.384524),
			glm::vec3(1, 0.65121, 0.395486),
			glm::vec3(1, 0.658225, 0.406497),
			glm::vec3(1, 0.665166, 0.417556),
			glm::vec3(1, 0.672034, 0.428659),
			glm::vec3(1, 0.678829, 0.439802),
			glm::vec3(1, 0.685552, 0.450982),
			glm::vec3(1, 0.692204, 0.462196),
			glm::vec3(1, 0.698786, 0.473441),
			glm::vec3(1, 0.705297, 0.484714),
			glm::vec3(1, 0.711739, 0.496013),
			glm::vec3(1, 0.718112, 0.507333),
			glm::vec3(1, 0.724417, 0.518673),
			glm::vec3(1, 0.730654, 0.53003),
			glm::vec3(1, 0.736825, 0.541402),
			glm::vec3(1, 0.742929, 0.552785),
			glm::vec3(1, 0.748968, 0.564177),
			glm::vec3(1, 0.754942, 0.575576),
			glm::vec3(1, 0.760851, 0.586979),
			glm::vec3(1, 0.766696, 0.598385),
			glm::vec3(1, 0.772479, 0.609791),
			glm::vec3(1, 0.778199, 0.621195),
			glm::vec3(1, 0.783858, 0.632595),
			glm::vec3(1, 0.789455, 0.643989),
			glm::vec3(1, 0.794991, 0.655375),
			glm::vec3(1, 0.800468, 0.666751),
			glm::vec3(1, 0.805886, 0.678116),
			glm::vec3(1, 0.811245, 0.689467),
			glm::vec3(1, 0.816546, 0.700803),
			glm::vec3(1, 0.82179, 0.712122),
			glm::vec3(1, 0.826976, 0.723423),
			glm::vec3(1, 0.832107, 0.734704),
			glm::vec3(1, 0.837183, 0.745964),
			glm::vec3(1, 0.842203, 0.757201),
			glm::vec3(1, 0.847169, 0.768414),
			glm::vec3(1, 0.852082, 0.779601),
			glm::vec3(1, 0.856941, 0.790762),
			glm::vec3(1, 0.861748, 0.801895),
			glm::vec3(1, 0.866503, 0.812999),
			glm::vec3(1, 0.871207, 0.824073),
			glm::vec3(1, 0.87586, 0.835115),
			glm::vec3(1, 0.880463, 0.846125),
			glm::vec3(1, 0.885017, 0.857102),
			glm::vec3(1, 0.889521, 0.868044),
			glm::vec3(1, 0.893977, 0.878951),
			glm::vec3(1, 0.898386, 0.889822),
			glm::vec3(1, 0.902747, 0.900657),
			glm::vec3(1, 0.907061, 0.911453),
			glm::vec3(1, 0.91133, 0.922211),
			glm::vec3(1, 0.915552, 0.932929),
			glm::vec3(1, 0.91973, 0.943608),
			glm::vec3(1, 0.923863, 0.954246),
			glm::vec3(1, 0.927952, 0.964842),
			glm::vec3(1, 0.931998, 0.975397),
			glm::vec3(1, 0.936001, 0.985909),
			glm::vec3(1, 0.939961, 0.996379),
			glm::vec3(0.993241, 0.9375, 1),
			glm::vec3(0.983104, 0.931743, 1),
			glm::vec3(0.973213, 0.926103, 1),
			glm::vec3(0.963562, 0.920576, 1),
			glm::vec3(0.954141, 0.915159, 1),
			glm::vec3(0.944943, 0.909849, 1),
			glm::vec3(0.935961, 0.904643, 1),
			glm::vec3(0.927189, 0.899538, 1),
			glm::vec3(0.918618, 0.894531, 1),
			glm::vec3(0.910244, 0.88962, 1),
			glm::vec3(0.902059, 0.884801, 1),
			glm::vec3(0.894058, 0.880074, 1),
			glm::vec3(0.886236, 0.875434, 1),
			glm::vec3(0.878586, 0.87088, 1),
			glm::vec3(0.871103, 0.86641, 1),
			glm::vec3(0.863783, 0.862021, 1),
			glm::vec3(0.856621, 0.857712, 1),
			glm::vec3(0.849611, 0.853479, 1),
			glm::vec3(0.84275, 0.849322, 1),
			glm::vec3(0.836033, 0.845239, 1),
			glm::vec3(0.829456, 0.841227, 1),
			glm::vec3(0.823014, 0.837285, 1),
			glm::vec3(0.816705, 0.83341, 1),
			glm::vec3(0.810524, 0.829602, 1),
			glm::vec3(0.804468, 0.825859, 1),
			glm::vec3(0.798532, 0.82218, 1),
			glm::vec3(0.792715, 0.818562, 1),
			glm::vec3(0.787012, 0.815004, 1),
			glm::vec3(0.781421, 0.811505, 1),
			glm::vec3(0.775939, 0.808063, 1),
			glm::vec3(0.770561, 0.804678, 1),
			glm::vec3(0.765287, 0.801348, 1),
			glm::vec3(0.760112, 0.798071, 1),
			glm::vec3(0.755035, 0.794846, 1),
			glm::vec3(0.750053, 0.791672, 1),
			glm::vec3(0.745164, 0.788549, 1),
			glm::vec3(0.740364, 0.785474, 1),
			glm::vec3(0.735652, 0.782448, 1),
			glm::vec3(0.731026, 0.779468, 1),
			glm::vec3(0.726482, 0.776534, 1),
			glm::vec3(0.722021, 0.773644, 1),
			glm::vec3(0.717638, 0.770798, 1),
			glm::vec3(0.713333, 0.767996, 1),
			glm::vec3(0.709103, 0.765235, 1),
			glm::vec3(0.704947, 0.762515, 1),
			glm::vec3(0.700862, 0.759835, 1),
			glm::vec3(0.696848, 0.757195, 1),
			glm::vec3(0.692902, 0.754593, 1),
			glm::vec3(0.689023, 0.752029, 1),
			glm::vec3(0.685208, 0.749502, 1),
			glm::vec3(0.681458, 0.747011, 1),
			glm::vec3(0.67777, 0.744555, 1),
			glm::vec3(0.674143, 0.742134, 1),
			glm::vec3(0.670574, 0.739747, 1),
			glm::vec3(0.667064, 0.737394, 1),
			glm::vec3(0.663611, 0.735073, 1),
			glm::vec3(0.660213, 0.732785, 1),
			glm::vec3(0.656869, 0.730528, 1),
			glm::vec3(0.653579, 0.728301, 1),
			glm::vec3(0.65034, 0.726105, 1),
			glm::vec3(0.647151, 0.723939, 1),
			glm::vec3(0.644013, 0.721801, 1),
			glm::vec3(0.640922, 0.719692, 1),
			glm::vec3(0.637879, 0.717611, 1),
			glm::vec3(0.634883, 0.715558, 1),
			glm::vec3(0.631932, 0.713531, 1),
			glm::vec3(0.629025, 0.711531, 1),
			glm::vec3(0.626162, 0.709557, 1),
			glm::vec3(0.623342, 0.707609, 1),
			glm::vec3(0.620563, 0.705685, 1),
			glm::vec3(0.617825, 0.703786, 1),
			glm::vec3(0.615127, 0.701911, 1),
			glm::vec3(0.612469, 0.70006, 1),
			glm::vec3(0.609848, 0.698231, 1),
			glm::vec3(0.607266, 0.696426, 1),
			glm::vec3(0.60472, 0.694643, 1)
	};

	static inline glm::vec3 color_from_temperature(float temp)
	{
		if (temp > 1000.f)
		{
			const int colNum(200);
			float idx = ((temp - 1000.f) / (10000.f - 1000.f) * (float)colNum);
			idx = alg::min(float(colNum - 1), idx);
			idx = alg::max(0.f, idx);
			return alg::max(glm::vec3(0.f), temp * mix(black_body_color[int(floor(idx))], black_body_color[int(ceil(idx))], fract(idx)) / 1000.f);
		}
		else
		{
			return alg::max(glm::vec3(0.f), temp * black_body_color[0] / 1000.f);
		}
	}
