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

    static float get_moment_inertia_scalar(RigidBody4D* a, glm::vec4 velocity4D, alg::bivec4 angularVelocity4D)
    {
        float lengthOfAngularVelocity4D(length(angularVelocity4D));
        float distance(length(velocity4D) / lengthOfAngularVelocity4D);
        float momentInertiaFromDistance(lengthOfAngularVelocity4D > 0.f ? distance * distance * a->mass : 0.f);
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
            float momentInertiaScalar0(lengthOfAngularVelocity4D>0?(
                angularVelocity4D.xy * momentInertiaScalarXY +
                angularVelocity4D.xz * momentInertiaScalarXZ +
                angularVelocity4D.xw * momentInertiaScalarXW +
                angularVelocity4D.yz * momentInertiaScalarYZ +
                angularVelocity4D.yw * momentInertiaScalarYW +
                angularVelocity4D.zw * momentInertiaScalarZW
                ) / (angularVelocity4D.xy + angularVelocity4D.xz + angularVelocity4D.xw + angularVelocity4D.yz + angularVelocity4D.yw + angularVelocity4D.zw): a->mass / 6.f);
            return momentInertiaScalar0 + momentInertiaFromDistance;
            break;
        }
        case STEP4D:
        {
            return 2.f * a->mass / 12.f + momentInertiaFromDistance;
            break;
        }
        case MESH4D:
        {
            return 2.f * a->mass / 12.f + momentInertiaFromDistance;
            break;
        }
        case CAPSULE4D:
        {
            return 2.f * a->mass / 12.f + momentInertiaFromDistance;
            break;
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
                a->angularVelocity4D = a->angularVelocity4D + inverse_moment_of_inertia(a, wedge_v(alg::vec4(j->position4D), rotate(a->rotation4D.reverse(), alg::vec4(dt * j->force4D))));
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
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(bodyContact), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

    static void resolve_impulse(RigidBody4D* b, glm::vec4 impulse)
    {
        b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
    }

    static void resolve_impulse0(RigidBody4D* b, glm::vec4 impulse, glm::vec4 worldContact)
    {
        b->velocity4D += b->mass > 0.f ? impulse / b->mass : glm::vec4(0.f);
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(world_pos_to_body(b,worldContact)), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

    static glm::vec4 vel_at(RigidBody4D* b, glm::vec4 bodyPos)
    {
        glm::vec4 rotVel(body_vec_to_world(b, left_contract_bv(alg::vec4(bodyPos), b->angularVelocity4D).transform()));
        return b->velocity4D + rotVel;
    }

    static glm::vec4 vel_at_world(RigidBody4D* b, glm::vec4 worldPos)
    {
        glm::vec4 bodyPos(world_pos_to_body(b,worldPos));
        glm::vec4 rotVel(body_vec_to_world(b,left_contract_bv(alg::vec4(bodyPos), b->angularVelocity4D).transform()));
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

