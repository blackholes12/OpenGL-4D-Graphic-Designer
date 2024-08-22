#pragma once
#include<vec4.hpp>
#include"body.h"
#include"gjk.h"
#include"resourcefile/primitive4d/box4d.h"
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
    explicit Collision(int index1, int index2, float massAdjustmentA, float massAdjustmentB, glm::vec4 normal, float depth, glm::vec4 contactPosA,glm::vec4 contactPosB)
    {
        this->index1 = index1;
        this->index2 = index2;
        this->massAdjustmentA = massAdjustmentA;
        this->massAdjustmentB = massAdjustmentB;
        this->collisionManifold.normal = normal;
        this->collisionManifold.depth = depth;
        this->collisionManifold.contactPosA = contactPosA;
        this->collisionManifold.contactPosB = contactPosB;
    }
};

static glm::vec4 inverse(glm::vec4 normal,bool isInverse)
{
    return isInverse ? normal : -normal;
}

static std::pair < glm::vec4, glm::vec4 > inverse(glm::vec4 contactPosA, glm::vec4 contactPosB, bool isInverse)
{
    if (isInverse) return { contactPosB ,contactPosA };
    else return { contactPosA ,contactPosB };
}

static std::vector<std::vector<Collision>> sphere_to_sphere(Object4D* a, Object4D* b,int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.y - b->position4D.y) < (a->scale4D.y + b->scale4D.y) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radiusA(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
        float radiusB(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (length(a->position4D - b->position4D) < radiusA + radiusB)
        {
            std::vector<Collision> collisions;
            glm::vec4 normal(normalize(b->position4D - a->position4D));
            float depth(radiusA + radiusB - length(a->position4D - b->position4D));
            glm::vec4 contactPosA(world_vec_to_body(a, radiusA * normal));
            glm::vec4 contactPosB(world_vec_to_body(b, -radiusB * normal));
            std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal,isInverse),depth, contactPosA, contactPosB));
            collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_sphere(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radius(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float cuberadius(length(a->scale4D)/2.f);
    if (abs(a->position4D.x - b->position4D.x) < radius + cuberadius &&
        abs(a->position4D.y - b->position4D.y) < radius + cuberadius &&
        abs(a->position4D.z - b->position4D.z) < radius + cuberadius &&
        abs(a->position4D.w - b->position4D.w) < radius + cuberadius)
    {
        glm::vec4 pB(world_pos_to_body(a, b->position4D));
        if (abs(pB.x) < a->scale4D.x / 2.f + radius &&
            abs(pB.y) < a->scale4D.y / 2.f + radius &&
            abs(pB.z) < a->scale4D.z / 2.f + radius &&
            abs(pB.w) < a->scale4D.w / 2.f + radius)
        {
            glm::vec4 sA(a->scale4D / 2.f);
            if (abs(pB.x) < sA.x + radius &&
                abs(pB.y) < sA.y + radius &&
                abs(pB.z) < sA.z + radius &&
                abs(pB.w) < sA.w + radius)
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
                    if (abs(pB[dir1[0]]) <= sA[dir1[0]] &&
                        abs(pB[dir1[1]]) <= sA[dir1[1]] &&
                        abs(pB[dir1[2]]) <= sA[dir1[2]])
                    {
                        for (int j(0); j < 2; j++)
                        {
                            float sign;
                            if (j == 0)sign = 1.f;
                            else if (j == 1)sign = -1.f;
                            if (sign * pB[dir2] > sA[dir2] &&
                                abs(pB[dir2] - sign * sA[dir2]) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2] = pB[dir2] - sign * sA[dir2];
                                normal = normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2] = sign * sA[dir2];
                                depth = radius - abs(pB[dir2] - aVec4[dir2]);
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
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
                    if (abs(pB[dir1[0]]) < sA[dir1[0]] &&
                        abs(pB[dir1[1]]) < sA[dir1[1]])
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
                                length(glm::vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal = normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                depth = radius - length(glm::vec2(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b,normal);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
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
                    if (abs(pB[dir1]) < sA[dir1])
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
                                length(glm::vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal = normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                depth = radius - length(glm::vec3(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
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
                                length(glm::vec4(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]],
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]])) < radius)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal[dir2[3]] = pB[dir2[3]] - sign[3] * sA[dir2[3]];
                                normal = normalize(normal);
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                aVec4[dir2[3]] = sign[3] * sA[dir2[3]];
                                depth = radius - length(glm::vec4(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]],
                                    pB[dir2[3]] - aVec4[dir2[3]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = -radius * world_vec_to_body(b, normal);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
                            }
                        }
                    }
                }
                if(collisions.size()>0)collisionsVec.push_back(collisions);
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_sphere(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radius(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float meshradius(length(a->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radius + meshradius &&
        abs(a->position4D.y - b->position4D.y) < radius + meshradius &&
        abs(a->position4D.z - b->position4D.z) < radius + meshradius &&
        abs(a->position4D.w - b->position4D.w) < radius + meshradius)
    {
        glm::vec4 pB(world_pos_to_body(a, b->position4D));
        glm::vec4 normal;
        float depth;
        glm::vec4 contactPosA;
        glm::vec4 contactPosB;
        std::vector<Collision> collisions;
        std::vector<Tetra4D> tetras4DA;
        std::vector < glm::vec4 > tetraNormal4D;
        for (int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
        {
            glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D));
            glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D));
            glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D));
            glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D));
            glm::vec4 normal0 = normalize(body_vec_to_world(a, a->primitive4D.normalData4D[4 * i] / a->scale4D));
            float supportDistanceA(dot(tetraVertexPos4D1 - b->position4D, normal0));
            if (abs(supportDistanceA) < radius) 
            { 
                tetras4DA.push_back({ 
                    a->primitive4D.vertexData4D[4 * i] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D ,
                    a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D });
                tetraNormal4D.push_back(normalize(a->primitive4D.normalData4D[4 * i] / a->scale4D));
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
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA,contactPosB));
            }

            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D1,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_face4D(pB, radius,
                vertexPos4D2,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }

            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D2,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D1,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contactPosA, &contactPosB))
            {
                normal = body_vec_to_world(a, normal);
                contactPosB = -radius * world_vec_to_body(b, normal);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
            else if (sphere_col_line4D(pB, radius,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }

            else if (sphere_col_point4D(pB, radius,
                vertexPos4D1,
                &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D2,
                &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D3,
                &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
            else if (sphere_col_point4D(pB, radius,
                vertexPos4D4,
                &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = -radius * world_vec_to_body(b, normal);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                    }
        }
        if(collisions.size()>0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_sphere(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float massAdjustment(0.f);
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            unsigned int cubeIndex;
            glm::vec4 detectPos4D0;
            for (size_t x(0); x < terrainSize; x++)
            {
                for (size_t z(0); z < terrainSize; z++)
                {
                    for (size_t w(0); w < terrainSize; w++)
                    {
                        if (abs(a->position4D.x - b->position4D.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                            abs(a->position4D.z - b->position4D.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                            abs(a->position4D.w - b->position4D.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                        {
                            cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                            for (size_t i(0); i < 6; i++)
                            {
                                glm::vec4 normal;
                                float depth;
                                glm::vec4 contactPosA;
                                glm::vec4 contactPosB;
                                std::vector<Collision> collisions;
                                if (sphere_col_terrain_tetra4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contactPosA, contactPosB));
                                }

                                else if (sphere_col_face4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_face4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_face4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_face4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }

                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }

                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_line4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA, &contactPosB))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }

                                else if (sphere_col_point4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                else if (sphere_col_point4D(b->position4D - a->position4D, radius,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contactPosA))
                                {
                                    contactPosA += a->position4D;
                                    contactPosA = world_pos_to_body(b, contactPosA);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, contactPosB));
                                }
                                if(collisions.size()>0)collisionsVec.push_back(collisions);
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_cube(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA(length(a->scale4D) / 2.f);
    float radiusB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radiusA + radiusB &&
        abs(a->position4D.y - b->position4D.y) < radiusA + radiusB &&
        abs(a->position4D.z - b->position4D.z) < radiusA + radiusB &&
        abs(a->position4D.w - b->position4D.w) < radiusA + radiusB)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4D));
        glm::vec4 posBToA(world_pos_to_body(a, b->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + radiusA &&
            abs(posAToB.y) < b->scale4D.y / 2.f + radiusA &&
            abs(posAToB.z) < b->scale4D.z / 2.f + radiusA &&
            abs(posAToB.w) < b->scale4D.w / 2.f + radiusA &&
            abs(posBToA.x) < a->scale4D.x / 2.f + radiusB &&
            abs(posBToA.y) < a->scale4D.y / 2.f + radiusB &&
            abs(posBToA.z) < a->scale4D.z / 2.f + radiusB &&
            abs(posBToA.w) < a->scale4D.w / 2.f + radiusB)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0;
                glm::vec4 normal0(epa2(a, b, simplex, &depth0,false));
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
                        if (supportDistanceA - dot(vertexPos4D - a->position4D, normal0) < 0.01f)
                        {
                            vertices4DA.push_back(vertexPos4D);
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(a, hypercube::edges4D[i].vertices4D[0] * a->scale4D));
                        glm::vec4 edgeVertexPos4D2(body_pos_to_world(a, hypercube::edges4D[i].vertices4D[1] * a->scale4D));
                        if (supportDistanceA - dot(edgeVertexPos4D1 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(edgeVertexPos4D2 - a->position4D, normal0) < 0.01f)
                        {
                            edges4DA.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        glm::vec4 faceVertexPos4D1(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[0] * a->scale4D));
                        glm::vec4 faceVertexPos4D2(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[1] * a->scale4D));
                        glm::vec4 faceVertexPos4D3(body_pos_to_world(a, hypercube::faces4D[i].vertices4D[2] * a->scale4D));
                        if (supportDistanceA - dot(faceVertexPos4D1 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D2 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D3 - a->position4D, normal0) < 0.01f)
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
                        if (supportDistanceA - dot(tetraVertexPos4D1 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D2 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D3 - a->position4D, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D4 - a->position4D, normal0) < 0.01f)
                        {
                            cubes4DA.push_back(Cube4D({ tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < 16; i++)
                    {
                        glm::vec4 vertexPos4D(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b->position4D, -normal0) < 0.01f)
                        {
                            vertices4DB.push_back(vertexPos4D);
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 edgeVertexPos4D2(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[1] * b->scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(edgeVertexPos4D2 - b->position4D, -normal0) < 0.01f)
                        {
                            edges4DB.push_back({ edgeVertexPos4D1, edgeVertexPos4D2 });
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        glm::vec4 faceVertexPos4D1(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[0] * b->scale4D));
                        glm::vec4 faceVertexPos4D2(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[1] * b->scale4D));
                        glm::vec4 faceVertexPos4D3(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[2] * b->scale4D));
                        if (supportDistanceB - dot(faceVertexPos4D1 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D2 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D3 - b->position4D, -normal0) < 0.01f)
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
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b->position4D, -normal0) < 0.01f)
                        {
                            cubes4DB.push_back(Cube4D({ tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < vertices4DA.size(); i++)
                    {
                        for (int j(0); j < cubes4DB.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D/2.f, b->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DA[i] + depth * normal0);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    for (int i(0); i < vertices4DB.size(); i++)
                    {
                        for (int j(0); j < cubes4DA.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(a, vertices4DB[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(a, normal0), a->scale4D * cubes4DA[j].normal4D/2.f, a->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DA[j].direction4D))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DB[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DB[i] - depth * normal0);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
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
                                get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2],&contactPosA, &contactPosB);
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    if(collisions.size()>0)collisionsVec.push_back(collisions);
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_cube(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float meshradius(length(a->scale4D) / 2.f);
    float cuberadius(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < meshradius + cuberadius &&
        abs(a->position4D.y - b->position4D.y) < meshradius + cuberadius &&
        abs(a->position4D.z - b->position4D.z) < meshradius + cuberadius &&
        abs(a->position4D.w - b->position4D.w) < meshradius + cuberadius)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + meshradius &&
            abs(posAToB.y) < b->scale4D.y / 2.f + meshradius &&
            abs(posAToB.z) < b->scale4D.z / 2.f + meshradius &&
            abs(posAToB.w) < b->scale4D.w / 2.f + meshradius)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0(0.f);
                glm::vec4 normal0(epa2(a, b, simplex, &depth0, false));
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

                    for (int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
                    {
                        glm::vec4 tetraVertexPos4D1(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D));
                        glm::vec4 tetraVertexPos4D2(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D));
                        glm::vec4 tetraVertexPos4D3(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D));
                        glm::vec4 tetraVertexPos4D4(body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D));
                        glm::vec4 distances(glm::vec4(
                            supportDistanceA - dot(tetraVertexPos4D1 - a->position4D, normal0),
                            supportDistanceA - dot(tetraVertexPos4D2 - a->position4D, normal0),
                            supportDistanceA - dot(tetraVertexPos4D3 - a->position4D, normal0),
                            supportDistanceA - dot(tetraVertexPos4D4 - a->position4D, normal0)
                        ));
                        tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &tetras4DA);
                        faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4D, &faces4DA);
                        faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                        faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                        faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                        edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a->position4D, &edges4DA);
                        edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a->position4D, &edges4DA);
                        edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                        edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4D, &edges4DA);
                        edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                        edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                        vertices_used(distances[0], tetraVertexPos4D1, normal0, a->position4D, &vertices4DA);
                        vertices_used(distances[1], tetraVertexPos4D2, normal0, a->position4D, &vertices4DA);
                        vertices_used(distances[2], tetraVertexPos4D3, normal0, a->position4D, &vertices4DA);
                        vertices_used(distances[3], tetraVertexPos4D4, normal0, a->position4D, &vertices4DA);
                    }

                    for (int i(0); i < 16; i++)
                    {
                        glm::vec4 vertexPos4D(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b->position4D, -normal0) < 0.01f)
                        {
                            vertices4DB.push_back(vertexPos4D);
                        }
                    } 
                    for (int i(0); i < 32; i++)
                    {
                        glm::vec4 edgeVertexPos4D1(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[0] * b->scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b->position4D, -normal0) < 0.01f)
                        {
                            glm::vec4 edgeVertexPos4D2(body_pos_to_world(b, hypercube::edges4D[i].vertices4D[1] * b->scale4D));
                            if (supportDistanceB - dot(edgeVertexPos4D2 - b->position4D, -normal0) < 0.01f)
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
                        if (supportDistanceB - dot(faceVertexPos4D1 - b->position4D, -normal0) < 0.01f)
                        {
                            glm::vec4 faceVertexPos4D2(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[1] * b->scale4D));
                            glm::vec4 faceVertexPos4D3(body_pos_to_world(b, hypercube::faces4D[i].vertices4D[2] * b->scale4D));
                            if (supportDistanceB - dot(faceVertexPos4D2 - b->position4D, -normal0) < 0.01f &&
                                supportDistanceB - dot(faceVertexPos4D3 - b->position4D, -normal0) < 0.01f)
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
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b->position4D, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b->position4D, -normal0) < 0.01f)
                        {
                            cubes4DB.push_back(Cube4D({ tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, hypercube::cubes4D[i].normal4D, hypercube::cubes4D[i].direction4D));
                        }
                    }

                    for (int i(0); i < vertices4DA.size(); i++)
                    {
                        for (int j(0); j < cubes4DB.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D / 2.f, b->scale4D + glm::vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA =  world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB =  world_pos_to_body(b, vertices4DA[i] + depth * normal0);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                                float depth(supportDistanceA - dot(vertices4DB[i] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA =  world_pos_to_body(a, vertices4DB[i] - depth * normal0);
                                    contactPosB =  world_pos_to_body(b, vertices4DB[i]);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
                                }
                            }
                        }
                    }
                    if(collisions.size()>0)collisionsVec.push_back(collisions);
                }
            }
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_cube(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(length(b->scale4D) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            unsigned int cubeIndex;
            for (int i(0); i < 16; i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (abs(a->position4D.x - b->position4D.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                abs(a->position4D.z - b->position4D.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                abs(a->position4D.w - b->position4D.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra(vertexOfB - a->position4D,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contactPosB,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                contactPosA = world_pos_to_body(b, vertexOfB);
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contactPosA, contactPosB));
                                            }
                                        }
                                    }
                                    if(collisions.size()>0)collisionsVec.push_back(collisions);
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

static std::vector<std::vector<Collision>> mesh_to_mesh(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float meshradiusA(length(a->scale4D) / 2.f);
    float meshradiusB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < meshradiusA + meshradiusB &&
        abs(a->position4D.y - b->position4D.y) < meshradiusA + meshradiusB &&
        abs(a->position4D.z - b->position4D.z) < meshradiusA + meshradiusB &&
        abs(a->position4D.w - b->position4D.w) < meshradiusA + meshradiusB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth0(0.f);
            glm::vec4 normal0(epa2(a, b, simplex, &depth0, false));
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
                        supportDistanceA - dot(tetraVertexPos4D1 - a->position4D, normal0),
                        supportDistanceA - dot(tetraVertexPos4D2 - a->position4D, normal0),
                        supportDistanceA - dot(tetraVertexPos4D3 - a->position4D, normal0),
                        supportDistanceA - dot(tetraVertexPos4D4 - a->position4D, normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &tetras4DA);
                    faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4D, &faces4DA);
                    faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                    faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                    faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &faces4DA);
                    edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a->position4D, &edges4DA);
                    edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a->position4D, &edges4DA);
                    edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                    edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a->position4D, &edges4DA);
                    edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                    edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a->position4D, &edges4DA);
                    vertices_used(distances[0], tetraVertexPos4D1, normal0, a->position4D, &vertices4DA);
                    vertices_used(distances[1], tetraVertexPos4D2, normal0, a->position4D, &vertices4DA);
                    vertices_used(distances[2], tetraVertexPos4D3, normal0, a->position4D, &vertices4DA);
                    vertices_used(distances[3], tetraVertexPos4D4, normal0, a->position4D, &vertices4DA);
                }
                for (int i(0); i < b->primitive4D.get_size_of_vertices4D() / 4; i++)
                {
                    glm::vec4 tetraVertexPos4D1(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i] * b->scale4D));
                    glm::vec4 tetraVertexPos4D2(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 1] * b->scale4D));
                    glm::vec4 tetraVertexPos4D3(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 2] * b->scale4D));
                    glm::vec4 tetraVertexPos4D4(body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 3] * b->scale4D));
                    glm::vec4 distances(glm::vec4(
                        supportDistanceB - dot(tetraVertexPos4D1 - b->position4D, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D2 - b->position4D, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D3 - b->position4D, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D4 - b->position4D, -normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4D, &tetras4DB);
                    faces_used({ distances[0],distances[1],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b->position4D, &faces4DB);
                    faces_used({ distances[0],distances[1],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b->position4D, &faces4DB);
                    faces_used({ distances[0],distances[2],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4D, &faces4DB);
                    faces_used({ distances[1],distances[2],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4D, &faces4DB);
                    edges_used({ distances[0],distances[1] }, { tetraVertexPos4D1 ,tetraVertexPos4D2 }, -normal0, b->position4D, &edges4DB);
                    edges_used({ distances[0],distances[2] }, { tetraVertexPos4D1 ,tetraVertexPos4D3 }, -normal0, b->position4D, &edges4DB);
                    edges_used({ distances[0],distances[3] }, { tetraVertexPos4D1 ,tetraVertexPos4D4 }, -normal0, b->position4D, &edges4DB);
                    edges_used({ distances[1],distances[2] }, { tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b->position4D, &edges4DB);
                    edges_used({ distances[1],distances[3] }, { tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b->position4D, &edges4DB);
                    edges_used({ distances[2],distances[3] }, { tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b->position4D, &edges4DB);
                    vertices_used(distances[0], tetraVertexPos4D1, -normal0, b->position4D, &vertices4DB);
                    vertices_used(distances[1], tetraVertexPos4D2, -normal0, b->position4D, &vertices4DB);
                    vertices_used(distances[2], tetraVertexPos4D3, -normal0, b->position4D, &vertices4DB);
                    vertices_used(distances[3], tetraVertexPos4D4, -normal0, b->position4D, &vertices4DB);
                }

                for (int i(0); i < vertices4DA.size(); i++)
                {
                    for (int j(0); j < tetras4DB.size(); j++)
                    {
                        if (is_in_tetra2(vertices4DA[i], tetras4DB[j].vertices4D[0], tetras4DB[j].vertices4D[1], tetras4DB[j].vertices4D[2], tetras4DB[j].vertices4D[3]))
                        {
                            float depth(supportDistanceB - dot(vertices4DA[i] - b->position4D, -normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                contactPosB = world_pos_to_body(b, vertices4DA[i] + depth * normal0);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                            float depth(supportDistanceA - dot(vertices4DB[i] - a->position4D, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                contactPosB = world_pos_to_body(b, vertices4DB[i] - depth * normal0);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                            float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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
                            float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contactPosA, contactPosB));
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

static std::vector<std::vector<Collision>> terrain_to_mesh(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(length(b->scale4D) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            unsigned int cubeIndex;
            for (int i(0); i < b->primitive4D.get_size_of_vertices4D(); i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, b->primitive4D.vertexData4D[i] * b->scale4D));
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (abs(a->position4D.x - b->position4D.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                abs(a->position4D.z - b->position4D.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radius &&
                                abs(a->position4D.w - b->position4D.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radius)
                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra(vertexOfB - a->position4D,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contactPosB,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                contactPosA = world_pos_to_body(b, vertexOfB);
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contactPosA, contactPosB));
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

static std::vector<std::vector<Collision>> capsule_to_sphere(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float capsuleradius(length(a->scale4D) / 2.f);
    float sphereradius(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < capsuleradius + sphereradius &&
        abs(a->position4D.y - b->position4D.y) < capsuleradius + sphereradius &&
        abs(a->position4D.z - b->position4D.z) < capsuleradius + sphereradius &&
        abs(a->position4D.w - b->position4D.w) < capsuleradius + sphereradius)
    {
        float radiusA(min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f);
        float lengthA(a->scale4D.z);
        float radiusB(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        glm::vec4 pB(world_pos_to_body(a, b->position4D));
        glm::vec4 pA1(glm::vec4(0.f, 0.f,lengthA / 2.f - radiusA, 0.f));
        glm::vec4 contactPosA;
        glm::vec4 contactPosB;
        std::vector<Collision> collisions;
        if (length(pA1 - pB) < radiusA + radiusB && pB.z > pA1.z)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(pB - pA1)));
            float depth(radiusA + radiusB - length(pA1 - pB));
            contactPosA = pA1 + radiusA * normal;
            contactPosB = world_pos_to_body(b, body_pos_to_world(a, pB - radiusA * normal));
            std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
        }
        glm::vec4 pA2(-glm::vec4(0.f, 0.f,lengthA / 2.f - radiusA, 0.f));
        if (length(pA2 - pB) < radiusA + radiusB && pB.z < pA2.z)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(pB - pA2)));
            float depth(radiusA + radiusB - length(pA2 - pB));
            contactPosA = pA2 + radiusA * normal;
            contactPosB = world_pos_to_body(b, body_pos_to_world(a, pB - radiusA * normal));
            std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
        }

        if (pB.z < pA1.z && pB.z > pA2.z && length(glm::vec4(pB.x, pB.y, 0.f, pB.w)) < radiusA + radiusB)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(glm::vec4(pB.x, pB.y, 0.f, pB.w))));
            float depth(radiusA + radiusB - length(glm::vec4(pB.x, pB.y, 0.f, pB.w)));
            contactPosA = radiusA * normal;
            contactPosB = world_pos_to_body(b, body_pos_to_world(a, pB - radiusA * normal));
            std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_cube(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float capsuleradius(a->scale4D.z / 2.f);
    float cuberadius(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < capsuleradius + cuberadius &&
        abs(a->position4D.y - b->position4D.y) < capsuleradius + cuberadius &&
        abs(a->position4D.z - b->position4D.z) < capsuleradius + cuberadius &&
        abs(a->position4D.w - b->position4D.w) < capsuleradius + cuberadius)
    {
        glm::vec4 posAToB(world_pos_to_body(b,a->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + capsuleradius && 
            abs(posAToB.y) < b->scale4D.y / 2.f + capsuleradius &&
            abs(posAToB.z) < b->scale4D.z / 2.f + capsuleradius &&
            abs(posAToB.w) < b->scale4D.w / 2.f + capsuleradius)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth(0.f);
                glm::vec4 contact((a->position4D + b->position4D) / 2.f);
                glm::vec4 normal(epa2(a, b, simplex, &depth, true));
                glm::vec4 contactPosA;
                glm::vec4 contactPosB;
                std::vector<Collision> collisions;
                if (depth > 0.f)
                {
                    std::vector<glm::vec4> supportPoints1(support_points(a, normal));
                    std::vector<glm::vec4> supportPoints2(support_points(b, -normal));
                    if (b->colType == STEP4D && a->objectName == "Player"&& normal.y < 0.f)
                    {
                        if (supportPoints1.size()>0)
                        {
                            depth = support(b, -normal).y - support(a, normal).y;
                            float height(depth + a->position4D.y - b->position4D.y);
                            if (height > 0.f && depth < 0.1f)
                            {
                                if (depth > 0.f) {
                                    contactPosA = world_pos_to_body(a, supportPoints1[0] - depth * normal / 2.f);
                                    contactPosB = world_pos_to_body(b, supportPoints1[0] - depth * normal / 2.f);
                                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(glm::vec4(0.f, -1.f, 0.f, 0.f), isInverse), depth, contactPosA, contactPosB));
                                }
                                if (depth > 0.03f)
                                a->set_position4D(glm::vec4(a->position4D.x, b->position4D.y + height-0.02f , a->position4D.z, a->position4D.w));
                            }
                        }
                    }
                    else
                    {
                        bool isMuti(false);
                        if (supportPoints1.size() == 1)
                        {
                            contact = supportPoints1[0] - depth * normal / 2.f;
                        }
                        if (supportPoints2.size() == 1)
                        {
                            contact = supportPoints2[0] + depth * normal / 2.f;
                        }
                        if (supportPoints1.size() == 2)
                        {
                            if (supportPoints2.size() == 4)
                            {
                                get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2], &contact, &contact);
                            }
                            if (supportPoints2.size() == 8)
                            {
                                isMuti = true;
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[0] - depth * normal / 2.f), world_pos_to_body(b, supportPoints1[0] - depth * normal / 2.f)));
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[1] - depth * normal / 2.f), world_pos_to_body(b, supportPoints1[1] - depth * normal / 2.f)));
                            }
                        }
                        if (!isMuti)
                        {
                            contactPosA = world_pos_to_body(a, contact);
                            contactPosB = world_pos_to_body(b, contact);
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
                        }
                    }
                }
                if (collisions.size() > 0)collisionsVec.push_back(collisions);
            }
        } 
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_mesh(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA(a->scale4D.z / 2.f);
    float radiusB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radiusA + radiusB &&
        abs(a->position4D.y - b->position4D.y) < radiusA + radiusB &&
        abs(a->position4D.z - b->position4D.z) < radiusA + radiusB &&
        abs(a->position4D.w - b->position4D.w) < radiusA + radiusB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth(0.f);
            glm::vec4 contact((a->position4D + b->position4D) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth, true));
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
                    contact = supportPoints1[0] - depth * normal / 2.f;
                }
                if (supportPoints2.size() == 1)
                {
                    contact = supportPoints2[0] + depth * normal / 2.f;
                }
                if (supportPoints1.size() == 2)
                {
                    if (supportPoints2.size() == 3)
                    {
                        get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2], &contact, &contact);
                    }
                    if (supportPoints2.size() == 4)
                    {
                        get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2], &contact, &contact);
                    }
                    if (supportPoints2.size() > 4)
                    {
                        isMuti = true;
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[0] - depth * normal / 2.f), world_pos_to_body(b, supportPoints1[0] - depth * normal / 2.f)));
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, world_pos_to_body(a, supportPoints1[1] - depth * normal / 2.f), world_pos_to_body(b, supportPoints1[1] - depth * normal / 2.f)));
                    }
                }
                if (!isMuti) {
                    contactPosA = world_pos_to_body(a, contact);
                    contactPosB = world_pos_to_body(b, contact);
                    std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                    collisions.push_back(Collision(index1, index2, 0.f, 0.f, inverse(normal, isInverse), depth, contactPosA, contactPosB));
                }
            }
            if (collisions.size() > 0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_capsule(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radiusA(a->scale4D.z / 2.f);
    float radiusB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radiusA + radiusB &&
        abs(a->position4D.y - b->position4D.y) < radiusA + radiusB &&
        abs(a->position4D.z - b->position4D.z) < radiusA + radiusB &&
        abs(a->position4D.w - b->position4D.w) < radiusA + radiusB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            //std::cout << a0->objectName <<"Collide" << b0->objectName << "\n";
            float depth(0.f);
            glm::vec4 contact((a->position4D + b->position4D) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth, true));
            glm::vec4 contactPosA;
            glm::vec4 contactPosB;
            std::vector<Collision> collisions;
            if (depth > 0.f)
            {
                float massAdjustment(1.f);
                std::vector<glm::vec4> supportPoints1(support_points(a, normal));
                std::vector<glm::vec4> supportPoints2(support_points(b, -normal));
                if (supportPoints1.size() == 1)
                {
                    contact = supportPoints1[0] - depth * normal / 2.f;
                }
                if (supportPoints2.size() == 1)
                {
                    contact = supportPoints2[0] + depth * normal / 2.f;
                }
                if (supportPoints1.size() == 2 || supportPoints2.size() == 2)
                {
                    contact = (a->position4D + b->position4D) / 2.f;
                    massAdjustment = 2.f;
                }
                contactPosA = world_pos_to_body(a, contact);
                contactPosB = world_pos_to_body(b, contact);
                std::tie(contactPosA, contactPosB) = inverse(contactPosA, contactPosB, isInverse);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contactPosA, contactPosB));
            }
            if (collisions.size() > 0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> terrain_to_capsule(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radius(b->scale4D.z);
        if (b->position4D.y - support(a, glm::vec4(0.f, 1.f, 0.f, 0.f)).y < radius)
        {
            float radiusA(min(b->scale4D.w, min(b->scale4D.x, b->scale4D.y)) / 2.f);
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
                unsigned int cubeIndex;
                glm::vec4 detectPos4D0;
                for (size_t x(0); x < terrainSize; x++)
                {
                    for (size_t z(0); z < terrainSize; z++)
                    {
                        for (size_t w(0); w < terrainSize; w++)
                        {
                            if (abs(a->position4D.x - sphereCenter.x + terrainScale * ((float)x + 0.5f - terrainSize / 2)) < terrainScale + radiusA &&
                                abs(a->position4D.z - sphereCenter.z + terrainScale * ((float)z + 0.5f - terrainSize / 2)) < terrainScale + radiusA &&
                                abs(a->position4D.w - sphereCenter.w + terrainScale * ((float)w + 0.5f - terrainSize / 2)) < terrainScale + radiusA)

                            {
                                cubeIndex = 4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contactPosA;
                                    glm::vec4 contactPosB;
                                    std::vector<Collision> collisions;
                                    if (sphere_col_terrain_tetra4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contactPosB, contactPosA));
                                    }

                                    else if (sphere_col_face4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    { 
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    { 
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_face4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    { 
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }

                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {  
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    { 
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }

                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {   
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    { 
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_line4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA, &contactPosB))
                                    {  
                                        contactPosA += a->position4D, contactPosB += a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }

                                    else if (sphere_col_point4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        &depth, &normal, &contactPosA))
                                    { 
                                        contactPosA += a->position4D, contactPosB = a->primitive4D.vertexData4D[cubeIndex + 4 * i] + a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contactPosA))
                                    { 
                                        contactPosA += a->position4D, contactPosB = a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1] + a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contactPosA))
                                    {  
                                        contactPosA += a->position4D, contactPosB = a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2] + a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
                                    }
                                    else if (sphere_col_point4D(sphereCenter - a->position4D, radiusA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contactPosA))
                                    {
                                        contactPosA += a->position4D, contactPosB = a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3] + a->position4D;
                                        contactPosB = world_pos_to_body(a, contactPosB), contactPosA = world_pos_to_body(b, contactPosA);
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosB, contactPosA));
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

static std::vector<std::vector<Collision>> sphere_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radius(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
    if (a->position4D.y< radius + height)
    {
        std::vector<Collision> collisions;
        glm::vec4 normal(glm::vec4(0.f, 1.f, 0.f, 0.f));
        glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(a->position4D.x, a->position4D.y-radius, a->position4D.z, a->position4D.w)));
        float depth(radius - a->position4D.y+height);     
        collisions.push_back(Collision(index1, index2,0.f, 0.f,normal, depth, contactPosA, glm::vec4()));
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiusA(length(a->scale4D) / 2.f);
    if (a->position4D.y < radiusA + height)
    {
        std::vector<Collision> collisions;
        for (int i(0); i < 16; i++)
        {
            glm::vec4 vertexPos4D(body_pos_to_world(a, hypercube::vertices4D[i] * a->scale4D));
            if (vertexPos4D.y < height)
            {
                glm::vec4 normal(glm::vec4(0.f, 1.f, 0.f, 0.f));
                glm::vec4 contactPosA(world_pos_to_body(a, vertexPos4D));
                float depth(height - vertexPos4D.y); 
                collisions.push_back(Collision(index1, index2,0.f, 0.f,normal, depth, contactPosA, glm::vec4()));
            }
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiusB(length(a->scale4D) / 2.f);
    if (a->position4D.y < radiusB + height)
    {
        std::vector<glm::vec4> vertices4DA;
        std::vector<Collision> collisions;
        for (int i(0); i < a->primitive4D.get_size_of_vertices4D(); i++)
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
        glm::vec4 normal(glm::vec4(0.f, 1.f, 0.f, 0.f));
        for (int i(0); i < vertices4DA.size(); i++)
        {
            glm::vec4 contactPosA(world_pos_to_body(a, vertices4DA[i]));
            float depth(height - vertices4DA[i].y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contactPosA, glm::vec4()));
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radius(min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f);
    float length(a->scale4D.z);
    std::vector<Collision> collisions;
    {
        glm::vec4 position4D(a->position4D + body_vec_to_world(a, glm::vec4(0.f, 0.f,length / 2.f - radius, 0.f)));
        if (position4D.y < radius + height)
        {
            glm::vec4 normal(glm::vec4(0.f, 1.f, 0.f, 0.f));
            glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(position4D.x, position4D.y - radius, position4D.z, position4D.w)));
            float depth(radius + height - position4D.y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, glm::vec4()));
        }
    }
    {
        glm::vec4 position4D(a->position4D - body_vec_to_world(a, glm::vec4(0.f, 0.f,length / 2.f - radius, 0.f)));
        if (position4D.y < radius + height)
        {
            glm::vec4 normal(glm::vec4(0.f, 1.f, 0.f, 0.f));
            glm::vec4 contactPosA(world_pos_to_body(a, glm::vec4(position4D.x, position4D.y - radius, position4D.z, position4D.w)));
            float depth(radius + height - position4D.y);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f, normal, depth, contactPosA, glm::vec4()));
        }
    }
    if (collisions.size() > 0)collisionsVec.push_back(collisions);
    return collisionsVec;
}

static void sphere_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float radius(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x / 2.f + radius &&
        abs(b->position4D.y - a->position4D.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f + radius &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + radius &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + radius)
    {
        float depth(a->position4D.y - b->position4D.y);
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
            b->velocity4D -= b->velocity4D * dt / 20.f;
        }
    }
}

static void cube_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float cuberadius(sqrt(b->scale4D.x * b->scale4D.x + b->scale4D.y * b->scale4D.y + b->scale4D.z * b->scale4D.z + b->scale4D.w * b->scale4D.w) / 2.f);
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x/2.f + cuberadius &&
        abs(b->position4D.y - a->position4D.y+ a->scale4D.y / 4.f) < a->scale4D.y / 4.f + cuberadius &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + cuberadius &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + cuberadius)
    {
        float depth(a->position4D.y - b->position4D.y);
        if (depth > -cuberadius)
        {
            glm::vec4 force;
            for (int i(0); i < 16; i++)
            {
                glm::vec4 pos(body_pos_to_world(a, hypercube::vertices4D[i] * b->scale4D));
                if (abs(pos.x- a->position4D.x) < a->scale4D.x / 2.f&&
                    abs(pos.y - a->position4D.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f&&
                    abs(pos.z - a->position4D.z) < a->scale4D.z / 2.f&&
                    abs(pos.w - a->position4D.w) < a->scale4D.w / 2.f)
                {
                    glm::vec4 rel_vel = vel_at(b, hypercube::vertices4D[i] * b->scale4D);
                    force = 0.3f * glm::vec4(0.f, 1.f, 0.f, 0.f) - 0.025f * rel_vel;
                    b->forceSystems4D.push_back(new ForceSystem4D(force, hypercube::vertices4D[i] * b->scale4D));
                    b->velocity4D -= b->velocity4D * dt / 20.f;
                }
            }
        }
    }
}
