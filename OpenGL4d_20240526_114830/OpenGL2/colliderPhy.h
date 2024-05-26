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
    glm::vec4 contacts;
};

static struct Collision
{
    int index1;
    int index2;//-1 collide with edge
    float massAdjustmentA;
    float massAdjustmentB;
    CollisionManifold collisionManifold;
    explicit Collision(int index1, int index2, float massAdjustmentA, float massAdjustmentB, glm::vec4 normal, float depth, glm::vec4 contacts)
    {
        this->index1 = index1;
        this->index2 = index2;
        this->massAdjustmentA = massAdjustmentA;
        this->massAdjustmentB = massAdjustmentB;
        this->collisionManifold.normal = normal;
        this->collisionManifold.depth = depth;
        this->collisionManifold.contacts = contacts;
    }
};

static glm::vec4 inverse(glm::vec4 normal,bool isInverse)
{
    return isInverse ? normal : -normal;
}

static std::vector<std::vector<Collision>> sphere_to_sphere(Object4D* a, Object4D* b,int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.y - b->position4D.y) < (a->scale4D.y + b->scale4D.y) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radiousA(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
        float radiousB(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (length(a->position4D - b->position4D) < radiousA + radiousB)
        {
            std::vector<Collision> collisions;
            glm::vec4 normal(normalize(b->position4D - a->position4D));
            float depth(radiousA + radiousB - length(a->position4D - b->position4D));
            glm::vec4 contacts(a->position4D + (radiousA - depth / 2.f) * normal);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal,isInverse),depth,contacts));
            if(collisions.size()>0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_sphere(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float radious(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float cubeRadious(length(a->scale4D)/2.f);
    if (abs(a->position4D.x - b->position4D.x) < radious+ cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < radious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < radious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < radious + cubeRadious)
    {
        glm::vec4 posAToB(world_pos_to_body(a, b->position4D));
        if (abs(posAToB.x) < a->scale4D.x / 2.f + radious &&
            abs(posAToB.y) < a->scale4D.y / 2.f + radious &&
            abs(posAToB.z) < a->scale4D.z / 2.f + radious &&
            abs(posAToB.w) < a->scale4D.w / 2.f + radious)
        {
            glm::vec4 pB(world_pos_to_body(a, b->position4D));
            glm::vec4 sA(a->scale4D / 2.f);
            if (abs(pB.x) < sA.x + radious &&
                abs(pB.y) < sA.y + radious &&
                abs(pB.z) < sA.z + radious &&
                abs(pB.w) < sA.w + radious)
            {
                glm::vec4 normal;
                float depth;
                glm::vec4 contacts;
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
                                abs(pB[dir2] - sign * sA[dir2]) < radious)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2] = pB[dir2] - sign * sA[dir2];
                                normal = normalize(normal);
                                depth = radious - abs(pB[dir2] - sign * sA[dir2]);
                                glm::vec4 aVec4 = pB;
                                aVec4[dir2] = sign * sA[dir2];
                                contacts = aVec4 / 2.f + (pB - radious*normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
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
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]])) < radious)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal = normalize(normal);
                                depth = radious - length(glm::vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]]));
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                contacts = aVec4 / 2.f + (pB - radious*normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
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
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]])) < radious)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal = normalize(normal);
                                depth = radious - length(glm::vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]]));
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                contacts = aVec4 / 2.f + (pB - radious*normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
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
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]])) < radious)
                            {
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal[dir2[3]] = pB[dir2[3]] - sign[3] * sA[dir2[3]];
                                normal = normalize(normal);
                                depth = radious - length(glm::vec4(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]],
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]]));
                                glm::vec4 aVec4(pB);
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                aVec4[dir2[3]] = sign[3] * sA[dir2[3]];
                                contacts = aVec4 / 2.f + (pB - radious*normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
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
    float radious(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    float meshRadious(length(a->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radious + meshRadious &&
        abs(a->position4D.y - b->position4D.y) < radious + meshRadious &&
        abs(a->position4D.z - b->position4D.z) < radious + meshRadious &&
        abs(a->position4D.w - b->position4D.w) < radious + meshRadious)
    {
        glm::vec4 pB(world_pos_to_body(a, b->position4D));
        glm::vec4 normal;
        float depth;
        glm::vec4 contacts;
        std::vector<Collision> collisions;
        for (int i(0); i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
        {
            glm::vec4 vertexPos4D1(a->primitive4D.vertexData4D[4 * i] * a->scale4D);
            glm::vec4 vertexPos4D2(a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D);
            glm::vec4 vertexPos4D3(a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D);
            glm::vec4 vertexPos4D4(a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D);
            if (sphere_col_tetra4D(pB, radious,
                normalize(a->primitive4D.normalData4D[4 * i]/ a->scale4D),
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }

            else if (sphere_col_face4D(pB, radious,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_face4D(pB, radious,
                vertexPos4D1,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contacts))
            { 
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_face4D(pB, radious,
                vertexPos4D1,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_face4D(pB, radious,
                vertexPos4D2,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }

            else if (sphere_col_line4D(pB, radious,
                vertexPos4D1,
                vertexPos4D2,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_line4D(pB, radious,
                vertexPos4D1,
                vertexPos4D3,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_line4D(pB, radious,
                vertexPos4D1,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_line4D(pB, radious,
                vertexPos4D2,
                vertexPos4D3,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_line4D(pB, radious,
                vertexPos4D2,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_line4D(pB, radious,
                vertexPos4D3,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }

            else if (sphere_col_point4D(pB, radious,
                vertexPos4D1,
                &depth, &normal, &contacts))
            { 
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_point4D(pB, radious,
                vertexPos4D2,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_point4D(pB, radious,
                vertexPos4D3,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
            }
            else if (sphere_col_point4D(pB, radious,
                vertexPos4D4,
                &depth, &normal, &contacts))
            {
                normal = body_vec_to_world(a, normal);
                contacts = body_pos_to_world(a, contacts);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
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
        float radious(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            int size(8);
            unsigned int cubeIndex;
            glm::vec4 detectPos4D0;
            for (size_t x(0); x < size; x++)
            {
                for (size_t z(0); z < size; z++)
                {
                    for (size_t w(0); w < size; w++)
                    {
                        if (abs(b->position4D.x - a->position4D.x - x + 3.5f) < 0.5f + radious &&
                            abs(b->position4D.z - a->position4D.z - z + 3.5f) < 0.5f + radious &&
                            abs(b->position4D.w - a->position4D.w - w + 3.5f) < 0.5f + radious)

                        {
                            cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                            for (size_t i(0); i < 6; i++)
                            {
                                glm::vec4 normal;
                                float depth;
                                glm::vec4 contacts;
                                std::vector<Collision> collisions;
                                if (sphere_col_terrain_tetra4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    //std::cout << "depth: "<< depth << "\n";
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
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
    float radiousA(length(a->scale4D) / 2.f);
    float radiousB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < radiousA + radiousB &&
        abs(a->position4D.y - b->position4D.y) < radiousA + radiousB &&
        abs(a->position4D.z - b->position4D.z) < radiousA + radiousB &&
        abs(a->position4D.w - b->position4D.w) < radiousA + radiousB)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4D));
        glm::vec4 posBToA(world_pos_to_body(a, b->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + radiousA &&
            abs(posAToB.y) < b->scale4D.y / 2.f + radiousA &&
            abs(posAToB.z) < b->scale4D.z / 2.f + radiousA &&
            abs(posAToB.w) < b->scale4D.w / 2.f + radiousA &&
            abs(posBToA.x) < a->scale4D.x / 2.f + radiousB &&
            abs(posBToA.y) < a->scale4D.y / 2.f + radiousB &&
            abs(posBToA.z) < a->scale4D.z / 2.f + radiousB &&
            abs(posBToA.w) < a->scale4D.w / 2.f + radiousB)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0;
                glm::vec4 normal0(epa2(a, b, simplex, &depth0,false));
                if (depth0 > 0.f)
                {
                    float supportDistanceA(support_distance(a, normal0));
                    float supportDistanceB(support_distance(b, -normal0));
                    glm::vec4 none;
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
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D/2.f, b->scale4D + glm::vec4(0.00001f), &none, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, vertices4DA[i] - depth * normal0 / 2.f));
                                }
                            }
                        }
                    }
                    for (int i(0); i < vertices4DB.size(); i++)
                    {
                        for (int j(0); j < cubes4DA.size(); j++)
                        {
                            glm::vec4 startPos4D(world_pos_to_body(a, vertices4DB[i]));
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(a, normal0), a->scale4D * cubes4DA[j].normal4D/2.f, a->scale4D + glm::vec4(0.00001f), &none, &none, cubes4DA[j].direction4D))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, vertices4DB[i] + depth * normal0 / 2.f));
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
                                glm::vec4 contact(get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]));
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                                glm::vec4 contact(get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]));
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
    float meshRadious(length(a->scale4D) / 2.f);
    float cubeRadious(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < meshRadious + cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < meshRadious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < meshRadious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < meshRadious + cubeRadious)
    {
        glm::vec4 posAToB(world_pos_to_body(b, a->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + meshRadious &&
            abs(posAToB.y) < b->scale4D.y / 2.f + meshRadious &&
            abs(posAToB.z) < b->scale4D.z / 2.f + meshRadious &&
            abs(posAToB.w) < b->scale4D.w / 2.f + meshRadious)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth0(0.f);
                glm::vec4 normal0(epa2(a, b, simplex, &depth0, false));
                if (depth0 > 0.f)
                {
                    float supportDistanceA(support_distance(a, normal0));
                    float supportDistanceB(support_distance(b, -normal0));
                    glm::vec4 none;
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
                            if (col_plane4D(startPos4D, startPos4D + 120000.f * world_vec_to_body(b, -normal0), b->scale4D * cubes4DB[j].normal4D / 2.f, b->scale4D + glm::vec4(0.00001f), &none, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b->position4D, -normal0));
                                glm::vec4 contact(vertices4DA[i] - depth * normal0 / 2.f);
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                                glm::vec4 contact(vertices4DB[i] + depth * normal0 / 2.f);
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                                glm::vec4 contact(get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]));
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                                glm::vec4 contact(get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]));
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                                if (depth > 0.f)
                                {
                                    collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
        float radious(length(b->scale4D) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            unsigned int size(8);
            unsigned int cubeIndex;
            for (int i(0); i < 16; i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D));
                for (size_t x(0); x < size; x++)
                {
                    for (size_t z(0); z < size; z++)
                    {
                        for (size_t w(0); w < size; w++)
                        {
                            if (abs(b->position4D.x - a->position4D.x - x + 3.5f) < 0.5f + radious &&
                                abs(b->position4D.z - a->position4D.z - z + 3.5f) < 0.5f + radious &&
                                abs(b->position4D.w - a->position4D.w - w + 3.5f) < 0.5f + radious)
                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra(vertexOfB - a->position4D,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contacts,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts));
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
    float meshRadiousA(length(a->scale4D) / 2.f);
    float meshRadiousB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.y - b->position4D.y) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.z - b->position4D.z) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.w - b->position4D.w) < meshRadiousA + meshRadiousB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth0(0.f);
            glm::vec4 normal0(epa2(a, b, simplex, &depth0, false));
            if (depth0 > 0.f)
            {
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
                            glm::vec4 contact(vertices4DA[i] - depth * normal0 / 2.f);
                            if (depth > 0.f)
                            {
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                            glm::vec4 contact(vertices4DB[i] + depth * normal0 / 2.f);
                            if (depth > 0.f)
                            {
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                            glm::vec4 contact(get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]));
                            float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b->position4D, -normal0));
                            if (depth > 0.f)
                            {
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
                            glm::vec4 contact(get_edge_in_face_pos(normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]));
                            float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a->position4D, normal0));
                            if (depth > 0.f)
                            {
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal0, isInverse), depth, contact));
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
        float radious(length(b->scale4D) / 2.f);
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            unsigned int size(8);
            unsigned int cubeIndex;
            for (int i(0); i < b->primitive4D.get_size_of_vertices4D(); i++)
            {
                glm::vec4 vertexOfB(body_pos_to_world(b, b->primitive4D.vertexData4D[i] * b->scale4D));
                for (size_t x(0); x < size; x++)
                {
                    for (size_t z(0); z < size; z++)
                    {
                        for (size_t w(0); w < size; w++)
                        {
                            if (abs(b->position4D.x - a->position4D.x - x + 3.5f) < 0.5f + radious &&
                                abs(b->position4D.z - a->position4D.z - z + 3.5f) < 0.5f + radious &&
                                abs(b->position4D.w - a->position4D.w - w + 3.5f) < 0.5f + radious)
                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
                                    std::vector<Collision> collisions;
                                    if (is_in_tetra(vertexOfB - a->position4D,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                    {
                                        if (point_col_terrain_tetra4D(vertexOfB, &depth, &normal, &contacts,
                                            a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                            a->position4D + a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
                                        {
                                            if (depth > 0.f)
                                            {
                                                
                                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts));
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
    float capsuleRadious(length(a->scale4D) / 2.f);
    float sphereRadious(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < capsuleRadious + sphereRadious &&
        abs(a->position4D.y - b->position4D.y) < capsuleRadious + sphereRadious &&
        abs(a->position4D.z - b->position4D.z) < capsuleRadious + sphereRadious &&
        abs(a->position4D.w - b->position4D.w) < capsuleRadious + sphereRadious)
    {
        float radiousA(min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f);
        float lengthA(a->scale4D.z);
        float radiousB(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
        glm::vec4 pB(world_pos_to_body(a, b->position4D));
        glm::vec4 pA1(glm::vec4(0.f, 0.f,lengthA / 2.f - radiousA, 0.f));
        std::vector<Collision> collisions;
        if (length(pA1 - pB) < radiousA + radiousB && pB.z > pA1.z)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(pB - pA1)));
            float depth(radiousA + radiousB - length(pA1 - pB));
            glm::vec4 contacts(body_pos_to_world(a, pA1+(radiousA - depth / 2.f) * normal));
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
        }
        glm::vec4 pA2(-glm::vec4(0.f, 0.f,lengthA / 2.f - radiousA, 0.f));
        if (length(pA2 - pB) < radiousA + radiousB && pB.z < pA2.z)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(pB - pA2)));
            float depth(radiousA + radiousB - length(pA2 - pB));
            glm::vec4 contacts(body_pos_to_world(a, pA2 + (radiousA - depth / 2.f) * normal));
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
        }

        if (pB.z < pA1.z && pB.z > pA2.z && length(glm::vec4(pB.x, pB.y, 0.f, pB.w)) < radiousA + radiousB)
        {
            glm::vec4 normal(body_vec_to_world(a, normalize(glm::vec4(pB.x, pB.y, 0.f, pB.w))));
            float depth(radiousA + radiousB - length(glm::vec4(pB.x, pB.y, 0.f, pB.w)));
            glm::vec4 contacts(body_pos_to_world(a, (radiousA - depth / 2.f) * normal));
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contacts));
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_cube(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float capsuleRadious(a->scale4D.z / 2.f);
    float cubeRadious(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < capsuleRadious + cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < capsuleRadious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < capsuleRadious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < capsuleRadious + cubeRadious)
    {
        glm::vec4 posAToB(world_pos_to_body(b,a->position4D));
        if (abs(posAToB.x) < b->scale4D.x / 2.f + capsuleRadious && 
            abs(posAToB.y) < b->scale4D.y / 2.f + capsuleRadious &&
            abs(posAToB.z) < b->scale4D.z / 2.f + capsuleRadious &&
            abs(posAToB.w) < b->scale4D.w / 2.f + capsuleRadious)
        {
            Simplex simplex(Simplex(glm::vec4(0.f)));
            if (gjk(a, b, &simplex))
            {
                float depth(0.f);
                glm::vec4 contact((a->position4D + b->position4D) / 2.f);
                glm::vec4 normal(epa2(a, b, simplex, &depth, true));
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
                            if (height > 0.f)
                            {
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(glm::vec4(0, -1, 0, 0), isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                               if(depth>0.03f)
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
                                contact = get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                            }
                            if (supportPoints2.size() == 8)
                            {
                                isMuti = true;
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                            }
                        }
                        if (!isMuti)
                        {
                            collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contact));
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
    float RadiousA(a->scale4D.z / 2.f);
    float RadiousB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < RadiousA + RadiousB &&
        abs(a->position4D.y - b->position4D.y) < RadiousA + RadiousB &&
        abs(a->position4D.z - b->position4D.z) < RadiousA + RadiousB &&
        abs(a->position4D.w - b->position4D.w) < RadiousA + RadiousB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            float depth(0.f);
            glm::vec4 contact((a->position4D + b->position4D) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth, true));
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
                        contact = get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                    if (supportPoints2.size() == 4)
                    {
                        contact = get_edge_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                    if (supportPoints2.size() > 4)
                    {
                        isMuti = true;
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                    }
                }
                if(!isMuti)
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contact));
            }
            if (collisions.size() > 0)collisionsVec.push_back(collisions);
        }
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_capsule(Object4D* a, Object4D* b, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec, bool isInverse)
{
    float RadiousA(a->scale4D.z / 2.f);
    float RadiousB(length(b->scale4D) / 2.f);
    if (abs(a->position4D.x - b->position4D.x) < RadiousA + RadiousB &&
        abs(a->position4D.y - b->position4D.y) < RadiousA + RadiousB &&
        abs(a->position4D.z - b->position4D.z) < RadiousA + RadiousB &&
        abs(a->position4D.w - b->position4D.w) < RadiousA + RadiousB)
    {
        Simplex simplex(Simplex(glm::vec4(0.f)));
        if (gjk(a, b, &simplex))
        {
            //std::cout << a0->objectName <<"Collide" << b0->objectName << "\n";
            float depth(0.f);
            glm::vec4 contact((a->position4D + b->position4D) / 2.f);
            glm::vec4 normal(epa2(a, b, simplex, &depth, true));
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
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,inverse(normal, isInverse), depth, contact));
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
        float radious(b->scale4D.z);
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            float radiousA(min(b->scale4D.w, min(b->scale4D.x, b->scale4D.y)) / 2.f);
            float lengthA(b->scale4D.z);
            glm::vec4 sphereCenter(body_pos_to_world(b,glm::vec4(0,0, lengthA/2.f - radiousA,0)));
            for (int i(0); i < 2; i++)
            {
                if (i == 1)
                {
                    sphereCenter = -sphereCenter;
                }
                int size(8);
                unsigned int cubeIndex;
                glm::vec4 detectPos4D0;
                for (size_t x(0); x < size; x++)
                {
                    for (size_t z(0); z < size; z++)
                    {
                        for (size_t w(0); w < size; w++)
                        {
                            if (abs(sphereCenter.x - a->position4D.x - x + 3.5f) < 0.5f + radiousA &&
                                abs(sphereCenter.z - a->position4D.z - z + 3.5f) < 0.5f + radiousA &&
                                abs(sphereCenter.w - a->position4D.w - w + 3.5f) < 0.5f + radiousA)

                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i(0); i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
                                    std::vector<Collision> collisions;
                                    if (sphere_col_terrain_tetra4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contacts))
                                    {
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {  
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {   
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {  
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contacts))
                                    { 
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {  
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts + a->position4D));
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
    float radiousB(min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f);
    if (a->position4D.y< radiousB + height)
    {
        std::vector<Collision> collisions;
        glm::vec4 normal(glm::vec4(0, 1, 0, 0));
        glm::vec4 contacts(glm::vec4(a->position4D.x, (height+ a->position4D.y-radiousB)/2.f, a->position4D.z, a->position4D.w));
        float depth(radiousB - a->position4D.y+height);     
        collisions.push_back(Collision(index1, index2,0.f, 0.f,normal, depth, contacts));
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> cube_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiousB(length(a->scale4D) / 2.f);
    if (a->position4D.y < radiousB + height)
    {
        std::vector<Collision> collisions;
        for (int i(0); i < 16; i++)
        {
            glm::vec4 vertexPos4D(body_pos_to_world(a, hypercube::vertices4D[i] * a->scale4D));
            if (vertexPos4D.y < height)
            {
                glm::vec4 normal(glm::vec4(0, 1, 0, 0));
                glm::vec4 contacts(glm::vec4(vertexPos4D.x,(height+ vertexPos4D.y)/2.f, vertexPos4D.z, vertexPos4D.w));
                float depth(height- vertexPos4D.y); 
                collisions.push_back(Collision(index1, index2,0.f, 0.f,normal, depth, contacts));
            }
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;
}

static std::vector<std::vector<Collision>> mesh_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radiousB(length(a->scale4D) / 2.f);
    if (a->position4D.y < radiousB + height)
    {
        std::vector<Collision> collisions;
        for (int i(0); i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D(body_pos_to_world(a, a->primitive4D.vertexData4D[i] * a->scale4D));
            if (vertexPos4D.y < height)
            {
                glm::vec4 normal(glm::vec4(0, 1, 0, 0));
                glm::vec4 contacts(glm::vec4(vertexPos4D.x, (height + vertexPos4D.y) / 2.f, vertexPos4D.z, vertexPos4D.w));
                float depth(height - vertexPos4D.y);
                collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts));
            }
        }
        if (collisions.size() > 0)collisionsVec.push_back(collisions);
    }
    return collisionsVec;

}

static std::vector<std::vector<Collision>> capsule_to_half_space(Object4D* a, int index1, int index2, std::vector<std::vector<Collision>> collisionsVec)
{
    float height(0.f);
    float radious(min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f);
    float length(a->scale4D.z);
    std::vector<Collision> collisions;
    {
        glm::vec4 position4D(a->position4D + body_vec_to_world(a, glm::vec4(0.f, 0.f,length / 2.f - radious, 0.f)));
        if (position4D.y < radious + height)
        {
            glm::vec4 normal(glm::vec4(0, 1, 0, 0));
            glm::vec4 contacts(glm::vec4(position4D.x, (height+position4D.y-radious)/2.f, position4D.z, position4D.w));
            float depth(radious - position4D.y + height);   
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts));
        }
    }
    {
        glm::vec4 position4D(a->position4D - body_vec_to_world(a, glm::vec4(0.f, 0.f,length / 2.f - radious, 0.f)));
        if (position4D.y < radious + height)
        {
            glm::vec4 normal(glm::vec4(0, 1, 0, 0));
            glm::vec4 contacts(glm::vec4(position4D.x, (height + position4D.y - radious) / 2.f, position4D.z, position4D.w));
            float depth(radious - position4D.y + height);
            collisions.push_back(Collision(index1, index2, 0.f, 0.f,normal, depth, contacts));
        }
    }
    if (collisions.size() > 0)collisionsVec.push_back(collisions);
    return collisionsVec;
}

static void sphere_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float radious(min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f);
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x / 2.f + radious &&
        abs(b->position4D.y - a->position4D.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f + radious &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + radious &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + radious)
    {
        float depth(a->position4D.y - b->position4D.y);
        if (depth > -radious)
        {
            glm::vec4 force;
            if (depth < radious) {
                force = 10000.f * glm::vec4(0, radious * radious * radious * radious * (depth + radious), 0, 0);
            }
            if (depth >= radious) {
                force = 10000.f * glm::vec4(0, radious * radious * radious * radious * (2.f * radious), 0, 0);
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
    float cubeRadious(sqrt(b->scale4D.x * b->scale4D.x + b->scale4D.y * b->scale4D.y + b->scale4D.z * b->scale4D.z + b->scale4D.w * b->scale4D.w) / 2.f);
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x/2.f + cubeRadious &&
        abs(b->position4D.y - a->position4D.y+ a->scale4D.y / 4.f) < a->scale4D.y / 4.f + cubeRadious &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + cubeRadious &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + cubeRadious)
    {
        float depth(a->position4D.y - b->position4D.y);
        if (depth > -cubeRadious)
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
                    glm::vec4 rel_vel = vel_at(b, body_pos_to_world(a, hypercube::vertices4D[i] * b->scale4D));
                    force = 0.3f * glm::vec4(0, 1.f, 0, 0) - 0.025f * rel_vel;
                    b->forceSystems4D.push_back(new ForceSystem4D(force, hypercube::vertices4D[i] * b->scale4D));
                    b->velocity4D -= b->velocity4D * dt / 20.f;
                }
            }
        }
    }
}
