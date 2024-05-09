#pragma once
#include"mod.h"

    static glm::vec4 body_vec_to_world(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D, alg::vec4(v)).transform();
    }

    static glm::vec4 world_vec_to_body(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D.reverse(), alg::vec4(v)).transform();
    }

    static glm::vec4 body_pos_to_world(Object4D* b, glm::vec4 v)
    {
        glm::vec4 rotated(rotate(b->rotation4D, alg::vec4(v)).transform());
        return rotated + b->position4D;
    }

    static glm::vec4 world_pos_to_body(Object4D* b, glm::vec4 v)
    {
        return rotate(b->rotation4D.reverse(), alg::vec4(v - b->position4D)).transform();
    }

    static glm::vec4 inverse_moment_of_mass(RigidBody4D* b, glm::vec4 force4D,const float dt)
    {
        if (b->mass <= 0.0)
        {
            return glm::vec4(0.f);
        }
        else
            return force4D * dt / b->mass;
    }

    static alg::bivec4 inverse_moment_of_inertia(RigidBody4D* b, alg::bivec4 bodyBivec)
    {
        if (b->momentInertiaScalar <= 0.0)
        {
            return alg::bivec4(0, 0, 0, 0, 0, 0);
        }
        else
            return bodyBivec * (1.f / b->momentInertiaScalar);
    }

    static void resolve_impulse(
        RigidBody4D* b,
        glm::vec4 impulse,
        glm::vec4 worldContact,float dt
    )
    {
            b->forceSystems4D.push_back(new ForceSystem4D(impulse / dt, world_pos_to_body(b,worldContact)));
    }

    static glm::vec4 vel_at(RigidBody4D* b, glm::vec4 worldPos)
    {
        glm::vec4 bodyPos(world_pos_to_body(b,worldPos));
        glm::vec4 rotVel(body_vec_to_world(b,left_contract_bv(alg::vec4(bodyPos), b->angularVelocity4D).transform()));
        return b->velocity4D + rotVel;
    }

