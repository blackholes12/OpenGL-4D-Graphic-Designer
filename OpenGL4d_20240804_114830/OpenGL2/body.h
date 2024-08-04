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
        if (b->mass > 0.f) return force4D * dt / b->mass;
        else return glm::vec4(0.f);
    }

    static alg::bivec4 inverse_moment_of_inertia(RigidBody4D* b, alg::bivec4 bodyBivec)
    {
        if (b->momentInertiaScalar > 0.f) return bodyBivec / b->momentInertiaScalar;
        else return alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    }

    static float get_moment_inertia_scalar(RigidBody4D* a)
    {
        switch (a->colType)
        {
        case SPHERE4D:
        {
            float radious(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
            return 1.5f * a->mass * radious * radious / 5.f+ a->mass * radious * radious;
            break;
        }
        case BOX4D:
        {
            return 0.4f * a->mass;
            break;
        }
        case STEP4D:
        {
            return 0.4f * a->mass;
            break;
        }
        case MESH4D:
        {
            return 0.4f * a->mass;
            break;
        }
        case CAPSULE4D:
        {
            return 0.4f * a->mass;
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
                a->velocity4D += j->force4D * dt / a->mass;
                a->angularVelocity4D = a->angularVelocity4D + inverse_moment_of_inertia(a, wedge_v(alg::vec4(j->position4D), rotate(a->rotation4D.reverse(), alg::vec4(dt * j->force4D))));
            }
            a->forceSystems4D.clear();
        }
    }

    static alg::bivec4 update_angular_velocity4D(RigidBody4D* b, glm::vec4 force4D,glm::vec4 forcePosition4D,const float dt)
    {
        alg::bivec4 bodyBivec(wedge_v(alg::vec4(forcePosition4D), rotate(b->rotation4D.reverse(), alg::vec4(dt * force4D))));
        float momentInertiaScalar(get_moment_inertia_scalar(b));
        if (b->momentInertiaScalar > 0.f) return  b->angularVelocity4D+bodyBivec / momentInertiaScalar;
        else return b->angularVelocity4D;
    }

    static void resolve_impulse(RigidBody4D* b, glm::vec4 impulse, glm::vec4 bodyContact)
    {
        b->velocity4D += impulse / b->mass;
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(bodyContact), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

    static void resolve_impulse0(RigidBody4D* b, glm::vec4 impulse)
    {
        b->velocity4D += impulse / b->mass;
    }

    static void resolve_impulse0(RigidBody4D* b, glm::vec4 impulse, glm::vec4 worldContact)
    {
        b->velocity4D += impulse / b->mass;
        b->angularVelocity4D = b->angularVelocity4D + inverse_moment_of_inertia(b, wedge_v(alg::vec4(world_pos_to_body(b,worldContact)), rotate(b->rotation4D.reverse(), alg::vec4(impulse))));
    }

    static glm::vec4 vel_at(RigidBody4D* b, glm::vec4 worldPos)
    {
        glm::vec4 bodyPos(world_pos_to_body(b,worldPos));
        glm::vec4 rotVel(body_vec_to_world(b,left_contract_bv(alg::vec4(bodyPos), b->angularVelocity4D).transform()));
        return b->velocity4D + rotVel;
    }

    static glm::vec4 get_cap_position4D(glm::vec4 hittingPos){
        glm::vec4 wallPos4D(glm::vec4(floor(2.f * hittingPos.x + 0.5f) / 2.f, floor(4.f * hittingPos.y + 0.25f) / 4.f, floor(2.f * hittingPos.z + 0.5f) / 2.f, floor(2.f * hittingPos.w + 0.5f) / 2.f));
        return wallPos4D;
    }

    static glm::vec4 get_cap_position4D(Object4D* obj, bool isFindPoint,glm::vec4 hittingPos){
        glm::vec4 bodypos(world_pos_to_body(obj, hittingPos));
        if (obj!=nullptr)return body_pos_to_world(obj, 
            glm::vec4(floor(2.f * bodypos.x + 0.5f) / 2.f, floor(4.f * bodypos.y + 0.25f) / 4.f, floor(2.f * bodypos.z + 0.5f) / 2.f, floor(2.f * bodypos.w + 0.5f) / 2.f)
            );
        else if(isFindPoint) return floor(2.f * hittingPos + 0.5f) / 2.f;
    }

