#pragma once
#include<vec4.hpp>
#include"body.h"
#include"gjk.h"
#include"Geometry.h"
//static struct Collider 
//{
//    glm::vec4 normal;
//    float radius;
//};
//
static struct CollisionManifold
{
    glm::vec4 normal;
    float depth;
    glm::vec4 contactPosA;
    glm::vec4 contactPosB;
};

static struct Collision
{
    int index1;
    int index2;//-1 collide with edge
    float massAdjustmentA;
    float massAdjustmentB;
    CollisionManifold collisionManifold;
    int type;
    explicit Collision(int index1, int index2, float massAdjustmentA, float massAdjustmentB, glm::vec4 normal, float depth, glm::vec4 contactPosA, glm::vec4 contactPosB, int type = 1)
    {
        this->index1 = index1;
        this->index2 = index2;
        this->massAdjustmentA = massAdjustmentA;
        this->massAdjustmentB = massAdjustmentB;
        this->collisionManifold.normal = normal;
        this->collisionManifold.depth = depth;
        this->collisionManifold.contactPosA = contactPosA;
        this->collisionManifold.contactPosB = contactPosB;
        this->type = type;
    }
};

static glm::vec4 inverse(glm::vec4 normal, bool isInverse)
{
    return isInverse ? -normal : normal;
}

static void inverse(size_t* index1, size_t* index2, bool isInverse)
{
    if (isInverse) { size_t index(*index1); *index1 = *index2; *index2 = index; }
}

static void inverse(glm::vec4* contactPosA, glm::vec4* contactPosB, bool isInverse)
{
    if (isInverse) { glm::vec4 contact(*contactPosA); *contactPosA = *contactPosB; *contactPosB = contact; }
}

static std::vector<std::vector<Collision>> hinge_to_hinge(std::vector< HingeConstraint4D*> hs, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    std::vector<Collision> collisions;
    for (HingeConstraint4D* h : hs)
    {
        if (!h->index2.isValid)
        {
            glm::vec4 worldPosition4D2(body_pos_to_world(a, h->bodyPosition4D1));
            glm::vec4 normal4D0(worldPosition4D2 - h->worldPosition4D);
            float depth(alg::length(normal4D0));
            if (depth > 0.f)
            {
                glm::vec4 normal4D(alg::normalize(normal4D0));
                glm::vec4 contactPosA(h->bodyPosition4D1);
                glm::vec4 contactPosB(h->worldPosition4D);
                collisions.push_back(Collision(h->index1, -1, 1.f, 1.f, normal4D, depth, contactPosA, contactPosB, 0));
            }
        }
        else
        {
            glm::vec4 contactPosA(h->bodyPosition4D1);
            glm::vec4 contactPosB(h->bodyPosition4D2);
            glm::vec4 normal4D0(body_pos_to_world(a, contactPosA) - body_pos_to_world(b, contactPosB));
            float depth(alg::length(normal4D0));
            if (depth > 0.f)
            {
                glm::vec4 normal4D(alg::normalize(normal4D0));
                inverse(&h->index1, &h->index2.n, isInverse);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(h->index1, h->index2.n, 1.f, 1.f, inverse(normal4D, isInverse), depth, contactPosA, contactPosB, 0));
            }
        }
    }
    if (collisions.size() > 0)collisionsVec.push_back(collisions);
    return collisionsVec;
}

static std::vector<std::vector<Collision>> sphere_to_sphere(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    if (alg::abs(a->position4d.x - b->position4d.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        alg::abs(a->position4d.y - b->position4d.y) < (a->scale4D.y + b->scale4D.y) / 2.f &&
        alg::abs(a->position4d.z - b->position4d.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        alg::abs(a->position4d.w - b->position4d.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radiusA(alg::min(a->scale4D.w, alg::min(a->scale4D.z, alg::min(a->scale4D.x, a->scale4D.y))) / 2.f);
        float radiusB(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (alg::length(a->position4d - b->position4d) < radiusA + radiusB)
        {
            std::vector<Collision> collisions;
            glm::vec4 normal(alg::normalize(b->position4d - a->position4d));
            float depth(radiusA + radiusB - alg::length(b->position4d - a->position4d));
            glm::vec4 contactPosA(world_vec_to_body(a, radiusA * normal));
            glm::vec4 contactPosB(world_vec_to_body(b, -radiusB * normal));
            inverse(&contactPosA, &contactPosB, isInverse);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_sphere(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radius(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float cubeRadius(alg::length(a->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < radius + cubeRadius &&
        alg::abs(a->position4d.y - b->position4d.y) < radius + cubeRadius &&
        alg::abs(a->position4d.z - b->position4d.z) < radius + cubeRadius &&
        alg::abs(a->position4d.w - b->position4d.w) < radius + cubeRadius)
    {
        glm::vec4 pB(world_pos_to_body(a, b->position4d));
        if (alg::abs(pB.x) < a->scale4D.x / 2.f + radius &&
            alg::abs(pB.y) < a->scale4D.y / 2.f + radius &&
            alg::abs(pB.z) < a->scale4D.z / 2.f + radius &&
            alg::abs(pB.w) < a->scale4D.w / 2.f + radius)
        {
            glm::vec4 sA(a->scale4D / 2.f);
            if (alg::abs(pB.x) < sA.x + radius &&
                alg::abs(pB.y) < sA.y + radius &&
                alg::abs(pB.z) < sA.z + radius &&
                alg::abs(pB.w) < sA.w + radius)
            {
                glm::vec4 normal;
                float depth;
                glm::vec4 contacts;
                glm::vec4 contactPosA;
                glm::vec4 contactPosB;
                std::vector<Collision> collisions;
                for (int i(0); i < 4; i++)
                {
                    int dir1[3];
                    int dir2;
                    if (i == 0)dir2 = 0, dir1[0] = 1, dir1[1] = 2, dir1[2] = 3;
                    else if (i == 1)dir1[0] = 0, dir2 = 1, dir1[1] = 2, dir1[2] = 3;
                    else if (i == 2)dir1[0] = 0, dir1[1] = 1, dir2 = 2, dir1[2] = 3;
                    else if (i == 3)dir1[0] = 0, dir1[1] = 1, dir1[2] = 2, dir2 = 3;
                    if (alg::abs(pB[dir1[0]]) <= sA[dir1[0]] &&
                        alg::abs(pB[dir1[1]]) <= sA[dir1[1]] &&
                        alg::abs(pB[dir1[2]]) <= sA[dir1[2]])
                    {
                        for (int j(0); j < 2; j++)
                        {
                            float sign;
                            if (j == 0)sign = 1.f;
                            else if (j == 1)sign = -1.f;
                            if (sign * pB[dir2] > sA[dir2] &&
                                alg::abs(pB[dir2] - sign * sA[dir2]) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2] = pB[dir2] - sign * sA[dir2];
                                normal = alg::normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2] = sign * sA[dir2];
                                depth = radius - alg::abs(pB[dir2] - aVec4[dir2]);
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
                            }
                        }
                    }
                }
                for (int i(0); i < 6; i++)
                {
                    int dir1[2];
                    int dir2[2];
                    if (i == 0)dir1[0] = 2, dir1[1] = 3, dir2[0] = 0, dir2[1] = 1;
                    else if (i == 1)dir1[0] = 1, dir1[1] = 3, dir2[0] = 0, dir2[1] = 2;
                    else if (i == 2)dir1[0] = 2, dir1[1] = 1, dir2[0] = 0, dir2[1] = 3;
                    else if (i == 3) dir1[0] = 0, dir1[1] = 3, dir2[0] = 1, dir2[1] = 2;
                    else if (i == 4)dir1[0] = 2, dir1[1] = 0, dir2[0] = 3, dir2[1] = 1;
                    else if (i == 5)dir1[0] = 0, dir1[1] = 1, dir2[0] = 2, dir2[1] = 3;
                    if (alg::abs(pB[dir1[0]]) <= sA[dir1[0]] &&
                        alg::abs(pB[dir1[1]]) <= sA[dir1[1]])
                    {
                        for (int j(0); j < 4; j++)
                        {
                            float sign[2];
                            if (j == 0)sign[0] = 1.f, sign[1] = 1.f;
                            else if (j == 1)sign[0] = -1.f, sign[1] = 1.f;
                            else if (j == 2)sign[0] = 1.f, sign[1] = -1.f;
                            else if (j == 3)sign[0] = -1.f, sign[1] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                alg::length(glm::vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal = alg::normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                depth = radius - alg::length(glm::vec2(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
                            }
                        }
                    }
                }

                for (int i(0); i < 4; i++)
                {
                    int dir1;
                    int dir2[3];
                    if (i == 0)dir2[0] = 0, dir2[1] = 1, dir2[2] = 2, dir1 = 3;
                    else if (i == 1)dir2[0] = 0, dir2[1] = 1, dir1 = 2, dir2[2] = 3;
                    else if (i == 2)dir2[0] = 0, dir1 = 1, dir2[1] = 2, dir2[2] = 3;
                    else if (i == 3)dir1 = 0, dir2[0] = 1, dir2[1] = 2, dir2[2] = 3;
                    if (alg::abs(pB[dir1]) <= sA[dir1])
                    {
                        for (int j(0); j < 8; j++)
                        {
                            float sign[3];
                            if (j == 0)sign[0] = 1.f, sign[1] = 1.f, sign[2] = 1.f;
                            else if (j == 1)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f;
                            else if (j == 2)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f;
                            else if (j == 3)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f;
                            else if (j == 4)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f;
                            else if (j == 5)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f;
                            else if (j == 6)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f;
                            else if (j == 7)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                sign[2] * pB[dir2[2]] > sA[dir2[2]] &&
                                alg::length(glm::vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal = alg::normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                depth = radius - alg::length(glm::vec3(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
                            }
                        }
                    }
                }

                {
                    int dir2[4];
                    dir2[0] = 0, dir2[1] = 1, dir2[2] = 2, dir2[3] = 3;
                    {
                        for (int j = 0; j < 16; j++)
                        {
                            float sign[4];
                            if (j == 0)sign[0] = 1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = 1.f;
                            else if (j == 1)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = 1.f;
                            else if (j == 2)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = 1.f;
                            else if (j == 3)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = 1.f;
                            else if (j == 4)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = 1.f;
                            else if (j == 5)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = 1.f;
                            else if (j == 6)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = 1.f;
                            else if (j == 7)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = 1.f;
                            else if (j == 8)sign[0] = 1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = -1.f;
                            else if (j == 9)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = -1.f;
                            else if (j == 10)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = -1.f;
                            else if (j == 11)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = -1.f;
                            else if (j == 12)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = -1.f;
                            else if (j == 13)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = -1.f;
                            else if (j == 14)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = -1.f;
                            else if (j == 15)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                sign[2] * pB[dir2[2]] > sA[dir2[2]] &&
                                sign[3] * pB[dir2[3]] > sA[dir2[3]] &&
                                alg::length(glm::vec4(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]],
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal[dir2[3]] = pB[dir2[3]] - sign[3] * sA[dir2[3]];
                                normal = alg::normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                aVec4[dir2[3]] = sign[3] * sA[dir2[3]];
                                depth = radius - alg::length(glm::vec4(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]],
                                    pB[dir2[3]] - aVec4[dir2[3]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                if (collisions.size() > 0)collisionsVec.push_back(collisions);
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_sphere(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radius(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float meshRadius(alg::length(a->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < radius + meshRadius &&
        alg::abs(a->position4d.y - b->position4d.y) < radius + meshRadius &&
        alg::abs(a->position4d.z - b->position4d.z) < radius + meshRadius &&
        alg::abs(a->position4d.w - b->position4d.w) < radius + meshRadius)
    {
        glm::vec4 pB(world_pos_to_body(a, b->position4d));
        glm::vec4 normal;
        float depth;
        glm::vec4 contactPosA;
        glm::vec4 contactPosB;
        std::vector<Collision> collisions;
        std::vector<Tetra4D> tetras4DA;
        std::vector < glm::vec4 > tetraNormal4D;
        for (unsigned int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
        {
            glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D));
            glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D));
            glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D));
            glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D));
            glm::vec4 normalAToB = alg::normalize(body_vec_to_world(a, a->primitive4D.normalData4D[4 * i] / a->scale4D));
            float supportDistanceA(dot(tetraVertexPos4D1 - b->position4d, -normalAToB));
            if (alg::abs(supportDistanceA) < radius)
            {
                tetras4DA.push_back({
                    a->primitive4D.vertexData4D[4 * i] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D });
                tetraNormal4D.push_back(alg::normalize(a->primitive4D.normalData4D[4 * i] / a->scale4D));
            }
        }
        //std::cout << tetras4DA.size() << '\n';
        for (int i(0); i < tetras4DA.size(); i++)
        {
            glm::vec4 vertexPos4D1(tetras4DA[i].vertices4D[0]);
            glm::vec4 vertexPos4D2(tetras4DA[i].vertices4D[1]);
            glm::vec4 vertexPos4D3(tetras4DA[i].vertices4D[2]);
            glm::vec4 vertexPos4D4(tetras4DA[i].vertices4D[3]);
            if (sphere_col_tetra4D(pB, radius,
                tetraNormal4D[i],
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }

            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D2,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }

            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
            }

            else if (sphere_col_point4D(pB, radius,
                vertexPos4D1,
                &depth, &normal, &contactPosA))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D2,
                &depth, &normal, &contactPosA))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D3,
                &depth, &normal, &contactPosA))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D4,
                &depth, &normal, &contactPosA))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                inverse(&contactPosA, &contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_sphere(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
    if (alg::abs(a->position4d.x - b->position4d.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        alg::abs(a->position4d.z - b->position4d.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        alg::abs(a->position4d.w - b->position4d.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (b->position4d.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            unsigned int cubeIndex;
            glm::vec4 detectPos4D0;
            for (size_t x(0); x < terrainSize; x++)
            {
                for (size_t z(0); z < terrainSize; z++)
                {
                    for (size_t w(0); w < terrainSize; w++)
                    {
                        if (alg::abs(a->position4d.x - b->position4d.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                            alg::abs(a->position4d.z - b->position4d.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                            alg::abs(a->position4d.w - b->position4d.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                        {
                            cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                            for (size_t i(0); i < 6; i++)
                            {
                                glm::vec4 normal;
                                float depth;
                                glm::vec4 contactPosA;
                                glm::vec4 contactPosB;
                                std::vector<Collision> collisions;
                                if (sphere_col_terrain_tetra4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }

                                else if (sphere_col_face4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_face4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_face4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_face4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }

                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }

                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }
                                else if (sphere_col_line4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                }

                                else if (sphere_col_point4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4d - a->position4d, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4d;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                }
                                if (collisions.size() > 0)collisionsVec.push_back(collisions);
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_cube(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA(alg::length(a->scale4D) / 2.f);
    float radiusB(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < radiusA + radiusB &&
        alg::abs(a->position4d.y - b->position4d.y) < radiusA + radiusB &&
        alg::abs(a->position4d.z - b->position4d.z) < radiusA + radiusB &&
        alg::abs(a->position4d.w - b->position4d.w) < radiusA + radiusB)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4d));
        glm::vec4 posBToA(world_pos_to_body(a, b->position4d));
        if (alg::abs(posAToB.x) < b->scale4D.x / 2.f + radiusA &&
            alg::abs(posAToB.y) < b->scale4D.y / 2.f + radiusA &&
            alg::abs(posAToB.z) < b->scale4D.z / 2.f + radiusA &&
            alg::abs(posAToB.w) < b->scale4D.w / 2.f + radiusA &&
            alg::abs(posBToA.x) < a->scale4D.x / 2.f + radiusB &&
            alg::abs(posBToA.y) < a->scale4D.y / 2.f + radiusB &&
            alg::abs(posBToA.z) < a->scale4D.z / 2.f + radiusB &&
            alg::abs(posBToA.w) < a->scale4D.w / 2.f + radiusB)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0;
                glm::vec4 normal0(epa2(a, b, simplex, &depth0));
                if (depth0 > 0.f)
                {
                    glm::vec4 contactPosA;
                    glm::vec4 contactPosB;
                    float supportDistanceA(support_distance(a, normal0));
                    float supportDistanceB(support_distance(b, -normal0));
                    glm::vec4 none;
                    float noneFloat;
                    std::vector<Collision> collisions;
                    std::vector<glm::vec4> vertices4DA;
                    std::vector<glm::vec4> vertices4DB;
                    std::vector<Edge4D> edges4DA;
                    std::vector<Edge4D> edges4DB;
                    std::vector<Face4D> faces4DA;
                    std::vector<Face4D> faces4DB;
                    std::vector<Cube4D> cubes4DA;
                    std::vector<Cube4D> cubes4DB;
                    for (int i(0); i < 16; i++)
                    {
                        glm::vec4 vertexPos4D(body_pos_to_world(a, hypercube::vertices4D[i] * a->scale4D));
                        if (supportDistanceA - dot(vertexPos4D - a->position4d, normal0) < 0.01f)
                        {
                            vertices4DA.push_back(vertexPos4D);
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(a, hypercube::edges4D[i].vertices4D[0] * a->scale4D));
                        glm::vec4 edgeVertexPos4D2(body_pos_to_world(a, hypercube::edges4D[i].vertices4D[1] * a->scale4D));
                        if (supportDistanceA - dot(edgeVertexPos4D1 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(edgeVertexPos4D2 - a->position4d, normal0) < 0.01f)
                        {
                            edges4DA.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        glm::vec4 faceVertexPos4D1(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[0] * a->scale4D));
                        glm::vec4 faceVertexPos4D2(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[1] * a->scale4D));
                        glm::vec4 faceVertexPos4D3(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[2] * a->scale4D));
                        if (supportDistanceA - dot(faceVertexPos4D1 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D2 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D3 - a->position4d, normal0) < 0.01f)
                        {
                            faces4DA.push_back({ faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 });
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, hypercube::cubes4D[i].vertices4D[0] * a->scale4D));
                        glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, hypercube::cubes4D[i].vertices4D[1] * a->scale4D));
                        glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, hypercube::cubes4D[i].vertices4D[2] * a->scale4D));
                        glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, hypercube::cubes4D[i].vertices4D[3] * a->scale4D));
                        if (supportDistanceA - dot(tetraVertexPos4D1 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D2 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D3 - a->position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D4 - a->position4d, normal0) < 0.01f)
                        {
                            cubes4DA.push_back(Cube4D(tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < 16; i++)
                    {
                        glm::vec4 vertexPos4D(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b->position4d, -normal0) < 0.01f)
                        {
                            vertices4DB.push_back(vertexPos4D);
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 edgeVertexPos4D2(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[1] * b->scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(edgeVertexPos4D2 - b->position4d, -normal0) < 0.01f)
                        {
                            edges4DB.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        glm::vec4 faceVertexPos4D1(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 faceVertexPos4D2(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[1] * b->scale4D));
                        glm::vec4 faceVertexPos4D3(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[2] * b->scale4D));
                        if (supportDistanceB - dot(faceVertexPos4D1 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D2 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D3 - b->position4d, -normal0) < 0.01f)
                        {
                            faces4DB.push_back({ faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 });
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        glm::vec4 tetraVertexPos4D1(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 tetraVertexPos4D2(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[1] * b->scale4D));
                        glm::vec4 tetraVertexPos4D3(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[2] * b->scale4D));
                        glm::vec4 tetraVertexPos4D4(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[3] * b->scale4D));
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b->position4d, -normal0) < 0.01f)
                        {
                            cubes4DB.push_back(Cube4D(tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < vertices4DA.size(); i++)
                    {
                        for (int j(0); j < cubes4DB.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D / 2.f, b->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB + dot(vertices4DA[i] - b->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DA[i] - depth * normal0);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < vertices4DB.size(); i++)
                    {
                        for (int j(0); j < cubes4DA.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(a, vertices4DB[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(a, normal0), a->scale4D * cubes4DA[j].normal4D / 2.f, a->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DA[j].direction4D))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DB[i] + depth * normal0);
                                    contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < edges4DA.size(); i++)
                    {
                        for (int j(0); j < faces4DB.size(); j++)
                        {
                            if (is_edge_in_square(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                            {
                                get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                float depth(supportDistanceB + dot(edges4DA[i].vertices4D[0] - b->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < edges4DB.size(); i++)
                    {
                        for (int j(0); j < faces4DA.size(); j++)
                        {
                            if (is_edge_in_square(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                            {
                                get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    if (collisions.size() > 0)collisionsVec.push_back(collisions);
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_cube(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float meshRadius(alg::length(a->scale4D) / 2.f);
    float cubeRadius(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < meshRadius + cubeRadius &&
        alg::abs(a->position4d.y - b->position4d.y) < meshRadius + cubeRadius &&
        alg::abs(a->position4d.z - b->position4d.z) < meshRadius + cubeRadius &&
        alg::abs(a->position4d.w - b->position4d.w) < meshRadius + cubeRadius)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4d));
        if (alg::abs(posAToB.x) < b->scale4D.x / 2.f + meshRadius &&
            alg::abs(posAToB.y) < b->scale4D.y / 2.f + meshRadius &&
            alg::abs(posAToB.z) < b->scale4D.z / 2.f + meshRadius &&
            alg::abs(posAToB.w) < b->scale4D.w / 2.f + meshRadius)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0(0.f);
                glm::vec4 normal0(epa2(a, b, simplex, &depth0));
                if (depth0 > 0.f)
                {
                    glm::vec4 contactPosA;
                    glm::vec4 contactPosB;
                    float supportDistanceA(support_distance(a, normal0));
                    float supportDistanceB(support_distance(b, -normal0));
                    glm::vec4 none;
                    float noneFloat;
                    std::vector<Collision> collisions;
                    std::vector<glm::vec4> vertices4DA;
                    std::vector<glm::vec4> vertices4DB;
                    std::vector<Edge4D> edges4DA;
                    std::vector<Edge4D> edges4DB;
                    std::vector<Face4D> faces4DA;
                    std::vector<Face4D> faces4DB;
                    std::vector<Tetra4D> tetras4DA;
                    std::vector<Cube4D> cubes4DB;

                    for (unsigned int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
                    {
                        glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D));
                        glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D));
                        glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D));
                        glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D));
                        glm::vec4 distances(glm::vec4(
                            supportDistanceA - dot(tetraVertexPos4D1 - a->position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D2 - a->position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D3 - a->position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D4 - a->position4d, normal0)
                        ));
                        tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &tetras4DA);
                        faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4d, &faces4DA);
                        faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                        faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                        faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                        edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a->position4d, &edges4DA);
                        edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a->position4d, &edges4DA);
                        edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                        edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4d, &edges4DA);
                        edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                        edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                        vertices_used(distances[0], tetraVertexPos4D1, normal0, a->position4d, &vertices4DA);
                        vertices_used(distances[1], tetraVertexPos4D2, normal0, a->position4d, &vertices4DA);
                        vertices_used(distances[2], tetraVertexPos4D3, normal0, a->position4d, &vertices4DA);
                        vertices_used(distances[3], tetraVertexPos4D4, normal0, a->position4d, &vertices4DA);
                    }

                    for (int i(0); i < 16; i++)
                    {
                        glm::vec4 vertexPos4D(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b->position4d, -normal0) < 0.01f)
                        {
                            vertices4DB.push_back(vertexPos4D);
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[0] * b->scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b->position4d, -normal0) < 0.01f)
                        {
                            glm::vec4 edgeVertexPos4D2(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[1] * b->scale4D));
                            if (supportDistanceB - dot(edgeVertexPos4D2 - b->position4d, -normal0) < 0.01f)
                            {
                                bool isAdd(true);
                                for (int j(0); j < edges4DB.size(); j++)
                                {
                                    if ((edges4DB[j].vertices4D[0] == edgeVertexPos4D1 && edges4DB[j].vertices4D[1] == edgeVertexPos4D2) ||
                                        (edges4DB[j].vertices4D[0] == edgeVertexPos4D2 && edges4DB[j].vertices4D[1] == edgeVertexPos4D1))
                                    {
                                        isAdd = false;
                                    }
                                }
                                if (isAdd)
                                    edges4DB.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                            }
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        glm::vec4 faceVertexPos4D1(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[0] * b->scale4D));
                        if (supportDistanceB - dot(faceVertexPos4D1 - b->position4d, -normal0) < 0.01f)
                        {
                            glm::vec4 faceVertexPos4D2(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[1] * b->scale4D));
                            glm::vec4 faceVertexPos4D3(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[2] * b->scale4D));
                            if (supportDistanceB - dot(faceVertexPos4D2 - b->position4d, -normal0) < 0.01f &&
                                supportDistanceB - dot(faceVertexPos4D3 - b->position4d, -normal0) < 0.01f)
                            {
                                faces4DB.push_back({ faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 });
                            }
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        glm::vec4 tetraVertexPos4D1(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 tetraVertexPos4D2(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[1] * b->scale4D));
                        glm::vec4 tetraVertexPos4D3(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[2] * b->scale4D));
                        glm::vec4 tetraVertexPos4D4(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[3] * b->scale4D));
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b->position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b->position4d, -normal0) < 0.01f)
                        {
                            cubes4DB.push_back(Cube4D(tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < vertices4DA.size(); i++)
                    {
                        for (int j(0); j < cubes4DB.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D / 2.f, b->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b->position4d, -normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DA[i] - depth * normal0);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < vertices4DB.size(); i++)
                    {
                        for (int j(0); j < tetras4DA.size(); j++)
                        {
                            if (is_in_tetra2(vertices4DB[i], tetras4DA[j].vertices4D[0], tetras4DA[j].vertices4D[1], tetras4DA[j].vertices4D[2], tetras4DA[j].vertices4D[3]))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DB[i] + depth * normal0);
                                    contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < edges4DA.size(); i++)
                    {
                        for (int j(0); j < faces4DB.size(); j++)
                        {
                            if (is_edge_in_square(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                            {
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4d, -normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < edges4DB.size(); i++)
                    {
                        for (int j(0); j < faces4DA.size(); j++)
                        {
                            if (is_edge_in_face(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                            {
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4d, normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    if (collisions.size() > 0)collisionsVec.push_back(collisions);
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_cube(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
    if (alg::abs(a->position4d.x - b->position4d.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        alg::abs(a->position4d.z - b->position4d.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        alg::abs(a->position4d.w - b->position4d.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(alg::length(b->scale4D) / 2.f);
        if (b->position4d.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            size_t cubeIndex;
            for (int i(0); i < 16; i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (alg::abs(a->position4d.x - b->position4d.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                alg::abs(a->position4d.z - b->position4d.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                alg::abs(a->position4d.w - b->position4d.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra(vertexOfB - a->position4d,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contactPosB,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                contactPosA = world_pos_to_body(b, vertexOfB);
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                            }
                                        }
                                    }
                                    if (collisions.size() > 0)collisionsVec.push_back(collisions);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_mesh(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float meshRadiusA(alg::length(a->scale4D) / 2.f);
    float meshRadiusB(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < meshRadiusA + meshRadiusB &&
        alg::abs(a->position4d.y - b->position4d.y) < meshRadiusA + meshRadiusB &&
        alg::abs(a->position4d.z - b->position4d.z) < meshRadiusA + meshRadiusB &&
        alg::abs(a->position4d.w - b->position4d.w) < meshRadiusA + meshRadiusB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth0(0.f);
            glm::vec4 normal0(epa2(a, b, simplex, &depth0));
            if (depth0 > 0.f)
            {
                glm::vec4 contactPosA;
                glm::vec4 contactPosB;
                float supportDistanceA(support_distance(a, normal0));
                float supportDistanceB(support_distance(b, -normal0));
                std::vector<Collision> collisions;
                std::vector<glm::vec4> vertices4DA;
                std::vector<glm::vec4> vertices4DB;
                std::vector<Edge4D> edges4DA;
                std::vector<Edge4D> edges4DB;
                std::vector<Face4D> faces4DA;
                std::vector<Face4D> faces4DB;
                std::vector<Tetra4D> tetras4DA;
                std::vector<Tetra4D> tetras4DB;
                for (int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
                {
                    glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D));
                    glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D));
                    glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D));
                    glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D));
                    glm::vec4 distances(glm::vec4(
                        supportDistanceA - dot(tetraVertexPos4D1 - a->position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D2 - a->position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D3 - a->position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D4 - a->position4d, normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &tetras4DA);
                    faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4d, &faces4DA);
                    faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                    faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                    faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &faces4DA);
                    edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a->position4d, &edges4DA);
                    edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a->position4d, &edges4DA);
                    edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                    edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4d, &edges4DA);
                    edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                    edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4d, &edges4DA);
                    vertices_used(distances[0], tetraVertexPos4D1, normal0, a->position4d, &vertices4DA);
                    vertices_used(distances[1], tetraVertexPos4D2, normal0, a->position4d, &vertices4DA);
                    vertices_used(distances[2], tetraVertexPos4D3, normal0, a->position4d, &vertices4DA);
                    vertices_used(distances[3], tetraVertexPos4D4, normal0, a->position4d, &vertices4DA);
                }
                for (unsigned int i(0); i < b->primitive4D.get_size_of_vertices4D() / 4; i++)
                {
                    glm::vec4 tetraVertexPos4D1(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i] * b->scale4D));
                    glm::vec4 tetraVertexPos4D2(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 1] * b->scale4D));
                    glm::vec4 tetraVertexPos4D3(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 2] * b->scale4D));
                    glm::vec4 tetraVertexPos4D4(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 3] * b->scale4D));
                    glm::vec4 distances(glm::vec4(
                        supportDistanceB - dot(tetraVertexPos4D1 - b->position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D2 - b->position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D3 - b->position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D4 - b->position4d, -normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4d, &tetras4DB);
                    faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b->position4d, &faces4DB);
                    faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b->position4d, &faces4DB);
                    faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4d, &faces4DB);
                    faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4d, &faces4DB);
                    edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, -normal0, b->position4d, &edges4DB);
                    edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, -normal0, b->position4d, &edges4DB);
                    edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, -normal0, b->position4d, &edges4DB);
                    edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b->position4d, &edges4DB);
                    edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b->position4d, &edges4DB);
                    edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4d, &edges4DB);
                    vertices_used(distances[0], tetraVertexPos4D1, -normal0, b->position4d, &vertices4DB);
                    vertices_used(distances[1], tetraVertexPos4D2, -normal0, b->position4d, &vertices4DB);
                    vertices_used(distances[2], tetraVertexPos4D3, -normal0, b->position4d, &vertices4DB);
                    vertices_used(distances[3], tetraVertexPos4D4, -normal0, b->position4d, &vertices4DB);
                }

                for (int i(0); i < vertices4DA.size(); i++)
                {
                    for (int j(0); j < tetras4DB.size(); j++)
                    {
                        if (is_in_tetra2(vertices4DA[i], tetras4DB[j].vertices4D[0], tetras4DB[j].vertices4D[1], tetras4DB[j].vertices4D[2], tetras4DB[j].vertices4D[3]))
                        {
                            float depth(supportDistanceB + dot(vertices4DA[i] - b->position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                contactPosB = world_pos_to_body(b, vertices4DA[i] - depth * normal0);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                for (int i(0); i < vertices4DB.size(); i++)
                {
                    for (int j(0); j < tetras4DA.size(); j++)
                    {
                        if (is_in_tetra2(vertices4DB[i], tetras4DA[j].vertices4D[0], tetras4DA[j].vertices4D[1], tetras4DA[j].vertices4D[2], tetras4DA[j].vertices4D[3]))
                        {
                            float depth(supportDistanceA - dot(vertices4DB[i] - a->position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DB[i] + depth * normal0);
                                contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                for (int i(0); i < edges4DA.size(); i++)
                {
                    for (int j(0); j < faces4DB.size(); j++)
                    {
                        if (is_edge_in_face(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                        {
                            get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                            float depth(supportDistanceB + dot(edges4DA[i].vertices4D[0] - b->position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                for (int i(0); i < edges4DB.size(); i++)
                {
                    for (int j(0); j < faces4DA.size(); j++)
                    {
                        if (is_edge_in_face(normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                        {
                            get_edge_in_face_pos(normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                            float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                if (collisions.size() > 0)collisionsVec.push_back(collisions);
            }
        }
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> terrain_to_mesh(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
    if (alg::abs(a->position4d.x - b->position4d.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        alg::abs(a->position4d.z - b->position4d.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        alg::abs(a->position4d.w - b->position4d.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(alg::length(b->scale4D) / 2.f);
        if (b->position4d.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            size_t cubeIndex;
            for (unsigned int i(0); i < b->primitive4D.get_size_of_vertices4D(); i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, b->primitive4D.vertexData4D[i] * b->scale4D));
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (alg::abs(a->position4d.x - b->position4d.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                alg::abs(a->position4d.z - b->position4d.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                alg::abs(a->position4d.w - b->position4d.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra4(vertexOfB - a->position4d,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contactPosB,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4d + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                contactPosA = world_pos_to_body(b, vertexOfB);
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                            }
                                        }
                                    }
                                    if (collisions.size() > 0)collisionsVec.push_back(collisions);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> capsule_to_sphere(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float capsuleRadius(alg::length(a->scale4D) / 2.f);
    float sphereRadius(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < capsuleRadius + sphereRadius &&
        alg::abs(a->position4d.y - b->position4d.y) < capsuleRadius + sphereRadius &&
        alg::abs(a->position4d.z - b->position4d.z) < capsuleRadius + sphereRadius &&
        alg::abs(a->position4d.w - b->position4d.w) < capsuleRadius + sphereRadius)
    {
        float radiusA(alg::min(a->scale4D.w, alg::min(a->scale4D.x, a->scale4D.y)) / 2.f);
        float lengthA(a->scale4D.z);
        float radiusB(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
        glm::vec4 pA1(glm::vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
        glm::vec4 pA2(glm::vec4(0.f, 0.f, radiusA - lengthA / 2.f, 0.f));
        glm::vec4 pBToA(world_pos_to_body(a, b->position4d));
        glm::vec4 contactPosA;
        glm::vec4 contactPosB;
        std::vector<Collision> collisions;
        if (alg::length(pBToA - pA1) < radiusA + radiusB && pBToA.z >= pA1.z)
        {
            glm::vec4 normal(alg::normalize(pBToA - pA1));
            float depth(radiusA + radiusB - alg::length(pBToA - pA1));
            contactPosA = pA1 + radiusA * normal;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -radiusB * normal));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
        }
        else if (alg::length(pBToA - pA2) < radiusA + radiusB && pBToA.z <= pA2.z)
        {
            glm::vec4 normal(alg::normalize(pBToA - pA2));
            float depth(radiusA + radiusB - alg::length(pBToA - pA2));
            contactPosA = pA2 - radiusA * normal;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -radiusB * normal));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
        }
        else if (alg::length(glm::vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)) < radiusA + radiusB && pBToA.z < pA1.z && pBToA.z > pA2.z)
        {
            glm::vec4 normal(alg::normalize(glm::vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)));
            float depth(radiusA + radiusB - alg::length(glm::vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)));
            contactPosA = glm::vec4(0.f, 0.f, pBToA.z, 0.f) - radiusA * normal;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -radiusB * normal));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB, 2));
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> capsule_to_cube(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float capsuleRadius(a->scale4D.z / 2.f);
    float cubeRadius(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < capsuleRadius + cubeRadius &&
        alg::abs(a->position4d.y - b->position4d.y) < capsuleRadius + cubeRadius &&
        alg::abs(a->position4d.z - b->position4d.z) < capsuleRadius + cubeRadius &&
        alg::abs(a->position4d.w - b->position4d.w) < capsuleRadius + cubeRadius)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4d));
        if (alg::abs(posAToB.x) < b->scale4D.x / 2.f + capsuleRadius &&
            alg::abs(posAToB.y) < b->scale4D.y / 2.f + capsuleRadius &&
            alg::abs(posAToB.z) < b->scale4D.z / 2.f + capsuleRadius &&
            alg::abs(posAToB.w) < b->scale4D.w / 2.f + capsuleRadius)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float radiusA(alg::min(a->scale4D.w, alg::min(a->scale4D.x, a->scale4D.y)) / 2.f);
                float lengthA(a->scale4D.z);
                float radiusB(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
                glm::vec4 pA1(glm::vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
                glm::vec4 pA2(glm::vec4(0.f, 0.f, radiusA - lengthA / 2.f, 0.f));
                float depth(0.f);
                glm::vec4 contact((a->position4d + b->position4d) / 2.f);
                glm::vec4 normal(epa2(a, b, simplex, &depth));
                glm::vec4 contactPosA;
                glm::vec4 contactPosB;
                std::vector<Collision> collisions;
                if (depth > 0.f)
                {
                    if (b->colType == STEP4D && a->objectName == "Player" && normal.y < 0.f)
                    {
                        std::vector<glm::vec4> supportPoints1(support_points(a, normal));
                        std::vector<glm::vec4> supportPoints2(support_points(b, -normal));
                        if (supportPoints1.size() > 0)
                        {
                            depth = support(b, -normal).y - support(a, normal).y;
                            float height(depth + a->position4d.y - b->position4d.y);
                            if (height > 0.f && depth < 0.1f)
                            {
                                if (depth > 0.f) {
                                    contactPosA = world_pos_to_body(a, supportPoints1[0] - depth * normal / 2.f);
                                    contactPosB = world_pos_to_body(b, supportPoints1[0] - depth * normal / 2.f);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(glm::vec4(0.f, -1.f, 0.f, 0.f), isInverse), depth, contactPosA, contactPosB));
                                }
                                if (depth > 0.03f)
                                    a->set_position4D(glm::vec4(a->position4d.x, b->position4d.y + height - 0.01f, a->position4d.z, a->position4d.w));
                            }
                        }
                    }
                    else
                    {
                        glm::vec4 normalToA = world_vec_to_body(a, normal);
                        if (normalToA.z > 0.0001f)
                        {
                            contactPosA = pA1 + radiusA * normalToA;
                            contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA - depth * normalToA));
                            inverse(&contactPosA, &contactPosB, isInverse);
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                        }
                        else if (normalToA.z < -0.0001f)
                        {
                            contactPosA = pA2 + radiusA * normalToA;
                            contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA - depth * normalToA));
                            inverse(&contactPosA, &contactPosB, isInverse);
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                        }
                        else
                        {
                            float supportDistanceA(support_distance(a, normal));
                            float supportDistanceB(support_distance(b, -normal));
                            std::vector<glm::vec4> vertices4DB;
                            std::vector<Edge4D> edges4DA;
                            std::vector<Edge4D> edges4DB;
                            std::vector<Face4D> faces4DA;
                            std::vector<Face4D> faces4DB;
                            std::vector<Cube4D> cubes4DB;
                            {
                                glm::vec4 edgeVertexPos4D1(body_pos_to_world(a, pA1 + radiusA * normalToA));
                                glm::vec4 edgeVertexPos4D2(body_pos_to_world(a, pA2 + radiusA * normalToA));
                                edges4DA.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                            }

                            for (int i(0); i < 32; i++)
                            {
                                glm::vec4 edgeVertexPos4D1(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[0] * b->scale4D));
                                glm::vec4 edgeVertexPos4D2(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[1] * b->scale4D));
                                if (supportDistanceB + dot(edgeVertexPos4D1 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(edgeVertexPos4D2 - b->position4d, normal) < 0.01f)
                                {
                                    edges4DB.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                                }
                            }
                            for (int i(0); i < 24; i++)
                            {
                                glm::vec4 faceVertexPos4D1(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[0] * b->scale4D));
                                glm::vec4 faceVertexPos4D2(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[1] * b->scale4D));
                                glm::vec4 faceVertexPos4D3(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[2] * b->scale4D));
                                if (supportDistanceB + dot(faceVertexPos4D1 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(faceVertexPos4D2 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(faceVertexPos4D3 - b->position4d, normal) < 0.01f)
                                {
                                    faces4DB.push_back({ faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 });
                                }
                            }
                            for (int i(0); i < 8; i++)
                            {
                                glm::vec4 tetraVertexPos4D1(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[0] * b->scale4D));
                                glm::vec4 tetraVertexPos4D2(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[1] * b->scale4D));
                                glm::vec4 tetraVertexPos4D3(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[2] * b->scale4D));
                                glm::vec4 tetraVertexPos4D4(body_pos_to_world(b, hypercube::cubes4D[i].vertices4D[3] * b->scale4D));
                                if (supportDistanceB + dot(tetraVertexPos4D1 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(tetraVertexPos4D2 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(tetraVertexPos4D3 - b->position4d, normal) < 0.01f &&
                                    supportDistanceB + dot(tetraVertexPos4D4 - b->position4d, normal) < 0.01f)
                                {
                                    cubes4DB.push_back(Cube4D(tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                                }
                            }
                            for (int i(0); i < edges4DA.size(); i++)
                            {
                                for (int j(0); j < faces4DB.size(); j++)
                                {
                                    if (is_edge_in_square(normal, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                                    {
                                        float depth(supportDistanceB + dot(edges4DA[i].vertices4D[0] - b->position4d, normal));
                                        if (depth > 0.f)
                                        {
                                            get_edge_in_face_pos(normal, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                            contactPosA = world_pos_to_body(a, contactPosA);
                                            contactPosB = world_pos_to_body(b, contactPosB);
                                            inverse(&contactPosA, &contactPosB, isInverse);
                                            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                                        }
                                    }
                                }
                            }
                            for (int j(0); j < cubes4DB.size(); j++)
                            {
                                glm::vec4 none;
                                float noneFloat;
                                glm::vec4 startPos4D(world_pos_to_body(b, a->position4d + radiusA * normal));
                                if (col_plane4D(startPos4D, startPos4D - 120000.f * world_vec_to_body(b, normal), b->scale4D * cubes4DB[j].normal4D / 2.f, b->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                                {
                                    contactPosA = pA1 + radiusA * normalToA;
                                    contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA) - depth * normal);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                                    contactPosA = pA2 + radiusA * normalToA;
                                    contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA) - depth * normal);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                            if (vertices4DB.size() == 1)
                            {
                                contactPosA = vertices4DB[0] - depth * normal;
                                contactPosB = world_pos_to_body(b, vertices4DB[0]);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                if (collisions.size() > 0)collisionsVec.push_back(collisions);
            }
        }
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_mesh(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA(a->scale4D.z / 2.f);
    float radiusB(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < radiusA + radiusB &&
        alg::abs(a->position4d.y - b->position4d.y) < radiusA + radiusB &&
        alg::abs(a->position4d.z - b->position4d.z) < radiusA + radiusB &&
        alg::abs(a->position4d.w - b->position4d.w) < radiusA + radiusB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth(0.f);
            glm::vec4 contact((a->position4d + b->position4d) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth));
            glm::vec4 contactPosA;
            glm::vec4 contactPosB;
            std::vector<Collision> collisions;
            if (depth > 0.f)
            {
                std::vector<glm::vec4> supportPoints1(support_points(a, normal));
                std::vector<glm::vec4> supportPoints2(support_points(b, -normal));
                bool isMuti(false);
                if (supportPoints1.size() == 1)
                {
                    contact = supportPoints1[0] + depth * normal / 2.f;
                }
                if (supportPoints2.size() == 1)
                {
                    contact = supportPoints2[0] - depth * normal / 2.f;
                }
                if (supportPoints1.size() == 2)
                {
                    if (supportPoints2.size() == 3)
                    {
                        get_edge_in_face_pos(normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2], &contact, &contact);
                    }
                    if (supportPoints2.size() == 4)
                    {
                        get_edge_in_face_pos(normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2], &contact, &contact);
                    }
                    if (supportPoints2.size() > 4)
                    {
                        isMuti = true;
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[0] + depth * normal / 2.f), world_pos_to_body(b, supportPoints1[0] + depth * normal / 2.f)));
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[1] + depth * normal / 2.f), world_pos_to_body(b, supportPoints1[1] + depth * normal / 2.f)));
                    }
                }
                if (!isMuti) {
                    contactPosA = world_pos_to_body(a, contact);
                    contactPosB = world_pos_to_body(b, contact);
                    inverse(&contactPosA, &contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                }
            }
            if (collisions.size() > 0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_capsule(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA0(a->scale4D.z / 2.f);
    float radiusB0(alg::length(b->scale4D) / 2.f);
    if (alg::abs(a->position4d.x - b->position4d.x) < radiusA0 + radiusB0 &&
        alg::abs(a->position4d.y - b->position4d.y) < radiusA0 + radiusB0 &&
        alg::abs(a->position4d.z - b->position4d.z) < radiusA0 + radiusB0 &&
        alg::abs(a->position4d.w - b->position4d.w) < radiusA0 + radiusB0)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            //std::cout << a0->objectName <<"Collide" << b0->objectName << "\n";
            float depth(0.f);
            glm::vec4 contact((a->position4d + b->position4d) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth));
            std::vector<Collision> collisions;
            if (depth > 0.f)
            {
                float radiusA(alg::min(a->scale4D.w, alg::min(a->scale4D.x, a->scale4D.y)) / 2.f);
                float lengthA(a->scale4D.z);
                float radiusB(alg::min(b->scale4D.w, alg::min(b->scale4D.x, b->scale4D.y)) / 2.f);
                float lengthB(b->scale4D.z);
                glm::vec4 normalToA(world_vec_to_body(a, normal));
                glm::vec4 normalToB(world_vec_to_body(b, normal));
                glm::vec4 pA1(glm::vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
                glm::vec4 pA2(glm::vec4(0.f, 0.f, radiusA - lengthA / 2.f, 0.f));
                glm::vec4 pB1(glm::vec4(0.f, 0.f, lengthB / 2.f - radiusB, 0.f));
                glm::vec4 pB2(glm::vec4(0.f, 0.f, radiusB - lengthB / 2.f, 0.f));
                glm::vec4 contactPosA;
                glm::vec4 contactPosB;
                if (alg::abs(normalToA.z) > 0.0001f)
                {
                    if (normalToA.z < -0.0001f)
                    {
                        contactPosA = pA1 + radiusA * normalToA;
                        contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA - depth * normalToA));
                        inverse(&contactPosA, &contactPosB, isInverse);
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
                    else if (normalToA.z > 0.0001f)
                    {
                        contactPosA = pA2 + radiusA * normalToA;
                        contactPosB = world_pos_to_body(b, body_pos_to_world(a, contactPosA - depth * normalToA));
                        inverse(&contactPosA, &contactPosB, isInverse);
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
                }
                else
                {
                    if (alg::abs(normalToB.z) > 0.0001f)
                    {
                        if (normalToB.z > 0.0001f)
                        {
                            contactPosB = pB2 - radiusB * normalToB;
                            contactPosA = world_pos_to_body(a, body_pos_to_world(b, contactPosB + depth * normalToB));
                            inverse(&contactPosA, &contactPosB, isInverse);
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                        }
                        else if (normalToB.z < -0.0001f)
                        {
                            contactPosB = pB1 - radiusB * normalToB;
                            contactPosA = world_pos_to_body(a, body_pos_to_world(b, contactPosB + depth * normalToB));
                            inverse(&contactPosA, &contactPosB, isInverse);
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                        }
                    }
                    else
                    {
                        contactPosA = get_point_from_edge_and_edge(body_pos_to_world(a, pA1), body_pos_to_world(a, pA2), body_pos_to_world(b, pB1) - depth * normal, body_pos_to_world(b, pB2) - depth * normal);
                        contactPosB = contactPosA + depth * normal;
                        contactPosA = world_pos_to_body(a, contactPosA);
                        contactPosB = world_pos_to_body(b, contactPosB);
                        inverse(&contactPosA, &contactPosB, isInverse);
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
                }
            }
            if (collisions.size() > 0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_capsule(int index1, int index2, Object4D* a, Object4D* b, std::vector<std::vector<Collision>> collisionsVec)
{
    if (alg::abs(a->position4d.x - b->position4d.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        alg::abs(a->position4d.z - b->position4d.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        alg::abs(a->position4d.w - b->position4d.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(b->scale4D.z);
        if (b->position4d.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            float radiusA(alg::min(b->scale4D.w, alg::min(b->scale4D.x, b->scale4D.y)) / 2.f);
            float lengthA(b->scale4D.z);
            glm::vec4 sphereCenter;
            for (int i(0); i < 2; i++)
            {
                if (i == 0)
                {
                    sphereCenter = body_pos_to_world(b, glm::vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
                }
                else if (i == 1)
                {
                    sphereCenter = body_pos_to_world(b, -glm::vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
                }
                size_t cubeIndex;
                glm::vec4 detectPos4D0;
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (alg::abs(a->position4d.x - sphereCenter.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radiusA &&
                                alg::abs(a->position4d.z - sphereCenter.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radiusA &&
                                alg::abs(a->position4d.w - sphereCenter.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radiusA)

                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (sphere_col_terrain_tetra4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }

                                    else if (sphere_col_face4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }

                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }

                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB, 2));
                                    }

                                    else if (sphere_col_point4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        &depth, &normal, &contactPosA))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contactPosA))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4d, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA))
                                    {
                                        contactPosA += a->position4d;
                                        contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, -normal, depth, contactPosA, contactPosB));
                                    }
                                    if (collisions.size() > 0)collisionsVec.push_back(collisions);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> sphere_to_half_space(int index1, int index2, Object4D* a, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radius(alg::min(a->scale4D.w, alg::min(a->scale4D.z, alg::min(a->scale4D.x, a->scale4D.y))) / 2.f);
    if (a->position4d.y < radius + height)
    {
        std::vector<Collision> collisions;
        glm::vec4 normal(glm::vec4(0.f, -1.f, 0.f, 0.f));
        glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(a->position4d.x, a->position4d.y - radius, a->position4d.z, a->position4d.w)));
        glm::vec4 contactPosB(glm::vec4(a->position4d.x, height, a->position4d.z, a->position4d.w));
        float depth(radius - a->position4d.y + height);
        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_half_space(int index1, int index2, Object4D* a, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiusA(alg::length(a->scale4D) / 2.f);
    if (a->position4d.y < radiusA + height)
    {
        std::vector<Collision> collisions;
        for (int i(0); i < 16; i++)
        {
            glm::vec4 vertexPos4D(body_pos_to_world(a, hypercube::vertices4D[i] * a->scale4D));
            if (vertexPos4D.y < height)
            {
                glm::vec4 normal(glm::vec4(0.f, -1.f, 0.f, 0.f));
                glm::vec4 contactPosA(world_pos_to_body(a, vertexPos4D));
                glm::vec4 contactPosB(glm::vec4(vertexPos4D.x, height, vertexPos4D.z, vertexPos4D.w));
                float depth(height - vertexPos4D.y);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
            }
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_half_space(int index1, int index2, Object4D* a, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiusB(alg::length(a->scale4D) / 2.f);
    if (a->position4d.y < radiusB + height)
    {
        std::vector<glm::vec4> vertices4DA;
        std::vector<Collision> collisions;
        for (unsigned int i(0); i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D(body_pos_to_world(a, a->primitive4D.vertexData4D[i] * a->scale4D));
            if (vertexPos4D.y < height)
            {
                bool isAdd(true);
                for (int j(0); j < vertices4DA.size(); j++)
                {
                    if (vertices4DA[j] == vertexPos4D)
                    {
                        isAdd = false;
                    }
                }
                if (isAdd)
                    vertices4DA.push_back(vertexPos4D);
            }
        }
        glm::vec4 normal(glm::vec4(0.f, -1.f, 0.f, 0.f));
        for (int i(0); i < vertices4DA.size(); i++)
        {
            glm::vec4 contactPosA(world_pos_to_body(a, vertices4DA[i]));
            glm::vec4 contactPosB(glm::vec4(vertices4DA[i].x, height, vertices4DA[i].z, vertices4DA[i].w));
            float depth(height - vertices4DA[i].y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_half_space(int index1, int index2, Object4D* a, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radius(alg::min(a->scale4D.w, alg::min(a->scale4D.x, a->scale4D.y)) / 2.f);
    float length(a->scale4D.z);
    std::vector<Collision> collisions;
    {
        glm::vec4 position4d(a->position4d + body_vec_to_world(a, glm::vec4(0.f, 0.f, length / 2.f - radius, 0.f)));
        if (position4d.y < radius + height)
        {
            glm::vec4 normal(glm::vec4(0.f, -1.f, 0.f, 0.f));
            glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(position4d.x, position4d.y - radius, position4d.z, position4d.w)));
            glm::vec4 contactPosB(glm::vec4(position4d.x, height, position4d.z, position4d.w));
            float depth(radius + height - position4d.y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
        }
    }
    {
        glm::vec4 position4d(a->position4d - body_vec_to_world(a, glm::vec4(0.f, 0.f, length / 2.f - radius, 0.f)));
        if (position4d.y < radius + height)
        {
            glm::vec4 normal(glm::vec4(0.f, -1.f, 0.f, 0.f));
            glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(position4d.x, position4d.y - radius, position4d.z, position4d.w)));
            glm::vec4 contactPosB(glm::vec4(position4d.x, height, position4d.z, position4d.w));
            float depth(radius + height - position4d.y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
        }
    }
    if (collisions.size() > 0)collisionsVec.push_back(collisions);
    return collisionsVec;
}

static void sphere_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float radius(alg::min(b->scale4D.w, alg::min(b->scale4D.z, alg::min(b->scale4D.x, b->scale4D.y))) / 2.f);
    if (alg::abs(b->position4d.x - a->position4d.x) < a->scale4D.x / 2.f + radius &&
        alg::abs(b->position4d.y - a->position4d.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f + radius &&
        alg::abs(b->position4d.z - a->position4d.z) < a->scale4D.z / 2.f + radius &&
        alg::abs(b->position4d.w - a->position4d.w) < a->scale4D.w / 2.f + radius)
    {
        float depth(a->position4d.y - b->position4d.y);
        if (depth > -radius)
        {
            glm::vec4 force;
            if (depth < radius) {
                force = 10000.f * glm::vec4(0, radius * radius * radius * radius * (depth + radius), 0, 0);
            }
            if (depth >= radius) {
                force = 10000.f * glm::vec4(0, radius * radius * radius * radius * (2.f * radius), 0, 0);
            }
            // std::cout << "float!" << force.y << "\n";
            b->forceSystems4D.push_back(new ForceSystem4D(force, glm::vec4(0.f)));
            b->velocity4d -= b->velocity4d * dt / 20.f;
        }
    }
}

static void cube_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float cubeRadius(sqrt(b->scale4D.x * b->scale4D.x + b->scale4D.y * b->scale4D.y + b->scale4D.z * b->scale4D.z + b->scale4D.w * b->scale4D.w) / 2.f);
    if (alg::abs(b->position4d.x - a->position4d.x) < a->scale4D.x / 2.f + cubeRadius &&
        alg::abs(b->position4d.y - a->position4d.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f + cubeRadius &&
        alg::abs(b->position4d.z - a->position4d.z) < a->scale4D.z / 2.f + cubeRadius &&
        alg::abs(b->position4d.w - a->position4d.w) < a->scale4D.w / 2.f + cubeRadius)
    {
        float depth(a->position4d.y - b->position4d.y);
        if (depth > -cubeRadius)
        {
            glm::vec4 force;
            for (int i(0); i < 16; i++)
            {
                glm::vec4 pos(body_pos_to_world(a, hypercube::vertices4D[i] * b->scale4D));
                if (alg::abs(pos.x - a->position4d.x) < a->scale4D.x / 2.f &&
                    alg::abs(pos.y - a->position4d.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f &&
                    alg::abs(pos.z - a->position4d.z) < a->scale4D.z / 2.f &&
                    alg::abs(pos.w - a->position4d.w) < a->scale4D.w / 2.f)
                {
                    glm::vec4 rel_vel = vel_at(b, hypercube::vertices4D[i] * b->scale4D);
                    force = 0.3f * glm::vec4(0.f, 1.f, 0.f, 0.f) - 0.025f * rel_vel;
                    b->forceSystems4D.push_back(new ForceSystem4D(force, hypercube::vertices4D[i] * b->scale4D));
                    b->velocity4d -= b->velocity4d * dt / 20.f;
                }
            }
        }
    }
}
