#pragma once
#include "gjk.cu"

__device__ static struct _d_CollisionManifold
{
    vec4 normal;
    float depth;
    vec4 contactPosA;
    vec4 contactPosB;
};

__device__ static struct _d_Collision
{
    int index1;
    int index2;//-1 collide with edge
    float massAdjustmentA;
    float massAdjustmentB;
    _d_CollisionManifold collisionManifold;
    int type;
    //explicit {int index1, int index2, float massAdjustmentA, float massAdjustmentB, vec4 normal, float depth, vec4 contactPosA, vec4 contactPosB, int type = 1)
    //{
    //    this->index1 = index1;
    //    this->index2 = index2;
    //    this->massAdjustmentA = massAdjustmentA;
    //    this->massAdjustmentB = massAdjustmentB;
    //    this->collisionManifold.normal = normal;
    //    this->collisionManifold.depth = depth;
    //    this->collisionManifold.contactPosA = contactPosA;
    //    this->collisionManifold.contactPosB = contactPosB;
    //    this->type = type;
    //}
};

__device__ static vec4 inverse(vec4 normal, bool isInverse)
{
    return isInverse ? normal * -1.f : normal;
}

__device__ static void inverse(int* index1, int* index2, bool isInverse)
{
    if (isInverse) { int index(*index1); *index1 = *index2; *index2 = index; }
}

__device__ static void inverse(vec4* contactPosA, vec4* contactPosB, bool isInverse)
{
    if (isInverse) { vec4 contact = *contactPosA; *contactPosA = *contactPosB; *contactPosB = contact; }
}

__device__ static void hinge_to_hinge(_d_HingeConstraint4D h, _d_RigidBody4D a, _d_RigidBody4D b, _d_Collision* collisions, int* size, bool isInverse)
{ 
    if (h.index2!=-1)
    {
        vec4 worldPosition4D2 = body_pos_to_world(a, h.bodyPosition4D1);
        vec4 normal4D0 = worldPosition4D2 - h.worldPosition4D;
        float depth = length(normal4D0);
        if (depth > 0.f)
        {
            vec4 normal4D = normalize(normal4D0);
            vec4 contactPosA = h.bodyPosition4D1;
            vec4 contactPosB = h.worldPosition4D;
            if (*size < 32) {
                collisions[*size] = { h.index1, -1, 1.f, 1.f, {normal4D, depth, contactPosA, contactPosB}, 0 }; *size = *size + 1;
            }
        }
    }
    else
    {
        vec4 contactPosA = h.bodyPosition4D1;
        vec4 contactPosB = h.bodyPosition4D2;
        vec4 normal4D0 = body_pos_to_world(a, contactPosA) - body_pos_to_world(b, contactPosB);
        float depth = length(normal4D0);
        if (depth > 0.f)
        {
            vec4 normal4D = normalize(normal4D0);
            inverse(&h.index1, &h.index2, isInverse);
            inverse(&contactPosA, &contactPosB, isInverse);
            if (*size < 32) {
                collisions[*size] = { h.index1, h.index2, 1.f, 1.f, {inverse(normal4D, isInverse), depth, contactPosA, contactPosB}, 0 }; *size = *size + 1;
            }
        }
    }
}

__device__ static void sphere_to_sphere(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, _d_Collision* collisions, int* size, bool isInverse)
{
    if (_d_abs(a.position4d.x - b.position4d.x) < (a.scale4D.x + b.scale4D.x) / 2.f &&
        _d_abs(a.position4d.y - b.position4d.y) < (a.scale4D.y + b.scale4D.y) / 2.f &&
        _d_abs(a.position4d.z - b.position4d.z) < (a.scale4D.z + b.scale4D.z) / 2.f &&
        _d_abs(a.position4d.w - b.position4d.w) < (a.scale4D.w + b.scale4D.w) / 2.f)
    {
        float radiusA(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
        float radiusB(_d_min(b.scale4D.w, _d_min(b.scale4D.z, _d_min(b.scale4D.x, b.scale4D.y))) / 2.f);
        if (length(a.position4d - b.position4d) < radiusA + radiusB)
        {
            vec4 normal(normalize(b.position4d - a.position4d));
            float depth(radiusA + radiusB - length(b.position4d - a.position4d));
            vec4 contactPosA(world_vec_to_body(a, normal * radiusA));
            vec4 contactPosB(world_vec_to_body(b, normal * -radiusB));
            inverse(&contactPosA, &contactPosB, isInverse);
            if (*size < 32) {
                collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
            }
        }
    }
}

__device__ static void cube_to_sphere(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, _d_Collision* collisions, int* size, bool isInverse)
{
    float radius(_d_min(b.scale4D.w, _d_min(b.scale4D.z, _d_min(b.scale4D.x, b.scale4D.y))) / 2.f);
    float cubeRadius(length(a.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < radius + cubeRadius &&
        _d_abs(a.position4d.y - b.position4d.y) < radius + cubeRadius &&
        _d_abs(a.position4d.z - b.position4d.z) < radius + cubeRadius &&
        _d_abs(a.position4d.w - b.position4d.w) < radius + cubeRadius)
    {
        vec4 pB(world_pos_to_body(a, b.position4d));
        if (_d_abs(pB.x) < a.scale4D.x / 2.f + radius &&
            _d_abs(pB.y) < a.scale4D.y / 2.f + radius &&
            _d_abs(pB.z) < a.scale4D.z / 2.f + radius &&
            _d_abs(pB.w) < a.scale4D.w / 2.f + radius)
        {
            vec4 sA(a.scale4D / 2.f);
            if (_d_abs(pB.x) < sA.x + radius &&
                _d_abs(pB.y) < sA.y + radius &&
                _d_abs(pB.z) < sA.z + radius &&
                _d_abs(pB.w) < sA.w + radius)
            {
                vec4 normal;
                float depth;
                vec4 contacts;
                vec4 contactPosA;
                vec4 contactPosB;
                for (int i(0); i < 4; i++)
                {
                    int dir1[3];
                    int dir2;
                    if (i == 0)dir2 = 0, dir1[0] = 1, dir1[1] = 2, dir1[2] = 3;
                    else if (i == 1)dir1[0] = 0, dir2 = 1, dir1[1] = 2, dir1[2] = 3;
                    else if (i == 2)dir1[0] = 0, dir1[1] = 1, dir2 = 2, dir1[2] = 3;
                    else if (i == 3)dir1[0] = 0, dir1[1] = 1, dir1[2] = 2, dir2 = 3;
                    if (_d_abs(pB[dir1[0]]) <= sA[dir1[0]] &&
                        _d_abs(pB[dir1[1]]) <= sA[dir1[1]] &&
                        _d_abs(pB[dir1[2]]) <= sA[dir1[2]])
                    {
                        for (int j(0); j < 2; j++)
                        {
                            float sign;
                            if (j == 0)sign = 1.f;
                            else if (j == 1)sign = -1.f;
                            if (sign * pB[dir2] > sA[dir2] &&
                                _d_abs(pB[dir2] - sign * sA[dir2]) < radius)
                            {
                                normal = vec4(0.f);
                                normal.value(dir2,pB[dir2] - sign * sA[dir2]);
                                normal = normalize(normal);
                                vec4 aVec4(pB);
                                aVec4.value(dir2,sign * sA[dir2]);
                                depth = radius - _d_abs(pB[dir2] - aVec4[dir2]);
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = world_vec_to_body(b, normal) * -radius;
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) {
                                    collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }, * size = *size + 1;
                                }
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
                    if (_d_abs(pB[dir1[0]]) <= sA[dir1[0]] &&
                        _d_abs(pB[dir1[1]]) <= sA[dir1[1]])
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
                                length(vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]])) < radius)
                            {
                                normal = vec4(0.f);
                                normal.value(dir2[0],pB[dir2[0]] - sign[0] * sA[dir2[0]]);
                                normal.value(dir2[1],pB[dir2[1]] - sign[1] * sA[dir2[1]]);
                                normal = normalize(normal);
                                vec4 aVec4(pB);
                                aVec4.value(dir2[0], sign[0] * sA[dir2[0]]);
                                aVec4.value(dir2[1], sign[1] * sA[dir2[1]]);
                                depth = radius - length(vec2(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = world_vec_to_body(b, normal)* -radius;
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) {
                                    collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                                }
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
                    if (_d_abs(pB[dir1]) <= sA[dir1])
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
                                length(vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]])) < radius)
                            {
                                normal = vec4(0.f);
                                normal.value(dir2[0], pB[dir2[0]] - sign[0] * sA[dir2[0]]);
                                normal.value(dir2[1], pB[dir2[1]] - sign[1] * sA[dir2[1]]);
                                normal.value(dir2[2], pB[dir2[2]] - sign[2] * sA[dir2[2]]);
                                normal = normalize(normal);
                                vec4 aVec4(pB);
                                aVec4.value(dir2[0], sign[0] * sA[dir2[0]]);
                                aVec4.value(dir2[1], sign[1] * sA[dir2[1]]);
                                aVec4.value(dir2[2], sign[2] * sA[dir2[2]]);
                                depth = radius - length(vec3(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = world_vec_to_body(b, normal)* -radius;
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) {
                                    collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                                }
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
                                length(vec4(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]],
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]])) < radius)
                            {
                                normal = vec4(0.f);
                                normal.value(dir2[0], pB[dir2[0]] - sign[0] * sA[dir2[0]]);
                                normal.value(dir2[1], pB[dir2[1]] - sign[1] * sA[dir2[1]]);
                                normal.value(dir2[2], pB[dir2[2]] - sign[2] * sA[dir2[2]]);
                                normal.value(dir2[3], pB[dir2[3]] - sign[3] * sA[dir2[3]]);
                                normal = normalize(normal);
                                vec4 aVec4(pB);
                                aVec4.value(dir2[0], sign[0] * sA[dir2[0]]);
                                aVec4.value(dir2[1], sign[1] * sA[dir2[1]]);
                                aVec4.value(dir2[2], sign[2] * sA[dir2[2]]);
                                aVec4.value(dir2[3], sign[3] * sA[dir2[3]]);
                                depth = radius - length(vec4(pB[dir2[0]] - aVec4[dir2[0]],
                                    pB[dir2[1]] - aVec4[dir2[1]],
                                    pB[dir2[2]] - aVec4[dir2[2]],
                                    pB[dir2[3]] - aVec4[dir2[3]]));
                                contactPosA = aVec4;
                                normal = body_vec_to_world(a, normal);
                                contactPosB = world_vec_to_body(b, normal)* -radius;
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) {
                                    collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB }, 1}; *size = *size + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

__device__ static void mesh_to_sphere(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float radius(_d_min(b.scale4D.w, _d_min(b.scale4D.z, _d_min(b.scale4D.x, b.scale4D.y))) / 2.f);
    float meshRadius(length(a.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < radius + meshRadius &&
        _d_abs(a.position4d.y - b.position4d.y) < radius + meshRadius &&
        _d_abs(a.position4d.z - b.position4d.z) < radius + meshRadius &&
        _d_abs(a.position4d.w - b.position4d.w) < radius + meshRadius)
    {
        vec4 pB(world_pos_to_body(a, b.position4d));
        vec4 normal;
        float depth;
        vec4 contactPosA;
        vec4 contactPosB;
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId] / 4; i++)
        {
            vec4 vertexPos4D1(get_vertex(a.primitiveId, 4 * i, vertices4DsVec, verticesStartIndices) * a.scale4D);
            vec4 vertexPos4D2(get_vertex(a.primitiveId, 4 * i + 1, vertices4DsVec, verticesStartIndices) * a.scale4D);
            vec4 vertexPos4D3(get_vertex(a.primitiveId, 4 * i + 2, vertices4DsVec, verticesStartIndices) * a.scale4D);
            vec4 vertexPos4D4(get_vertex(a.primitiveId, 4 * i + 3, vertices4DsVec, verticesStartIndices) * a.scale4D);
            vec4 tetraVertexPos4D1(body_pos_to_world(a, vertexPos4D1));
            vec4 tetraVertexPos4D2(body_pos_to_world(a, vertexPos4D2));
            vec4 tetraVertexPos4D3(body_pos_to_world(a, vertexPos4D3));
            vec4 tetraVertexPos4D4(body_pos_to_world(a, vertexPos4D4));
            vec4 tetraNormal4D = normalize(cross4d(vertexPos4D1 - vertexPos4D2, vertexPos4D1 - vertexPos4D3, vertexPos4D1 - vertexPos4D4) / a.scale4D);
            vec4 normalAToB = normalize(body_vec_to_world(a, tetraNormal4D / a.scale4D));
            float supportDistanceA(dot(tetraVertexPos4D1 - b.position4d, -normalAToB));
            if (_d_abs(supportDistanceA) < radius)
            {
                if (sphere_col_tetra4D(pB, radius,
                    tetraNormal4D,
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }

                else if (sphere_col_face4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D3,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }
                else if (sphere_col_face4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }
                else if (sphere_col_face4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }
                else if (sphere_col_face4D(pB, radius,
                    vertexPos4D2,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }

                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D2,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) {
                        collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1;
                    }
                }
                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D3,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }
                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D1,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }
                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D2,
                    vertexPos4D3,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }
                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D2,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }
                else if (sphere_col_line4D(pB, radius,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA, &contactPosB))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }

                else if (sphere_col_point4D(pB, radius,
                    vertexPos4D1,
                    &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB},1  }; *size = *size + 1; }
                }
                else if (sphere_col_point4D(pB, radius,
                    vertexPos4D2,
                    &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB},1 }; *size = *size + 1; }
                }
                else if (sphere_col_point4D(pB, radius,
                    vertexPos4D3,
                    &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB},1 }; *size = *size + 1; }
                }
                else if (sphere_col_point4D(pB, radius,
                    vertexPos4D4,
                    &depth, &normal, &contactPosA))
                {
                    normal = body_vec_to_world(a, normal);
                    contactPosB = world_vec_to_body(b, normal) * -radius;
                    inverse(&contactPosA, &contactPosB, isInverse);
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB},1 }; *size = *size + 1; }
                }
            }
        }
    }
}

__device__ static void cube_to_cube(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float radiusA(length(a.scale4D) / 2.f);
    float radiusB(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < radiusA + radiusB &&
        _d_abs(a.position4d.y - b.position4d.y) < radiusA + radiusB &&
        _d_abs(a.position4d.z - b.position4d.z) < radiusA + radiusB &&
        _d_abs(a.position4d.w - b.position4d.w) < radiusA + radiusB)
    {
        vec4 posAToB(world_pos_to_body(b, a.position4d));
        vec4 posBToA(world_pos_to_body(a, b.position4d));
        if (_d_abs(posAToB.x) < b.scale4D.x / 2.f + radiusA &&
            _d_abs(posAToB.y) < b.scale4D.y / 2.f + radiusA &&
            _d_abs(posAToB.z) < b.scale4D.z / 2.f + radiusA &&
            _d_abs(posAToB.w) < b.scale4D.w / 2.f + radiusA &&
            _d_abs(posBToA.x) < a.scale4D.x / 2.f + radiusB &&
            _d_abs(posBToA.y) < a.scale4D.y / 2.f + radiusB &&
            _d_abs(posBToA.z) < a.scale4D.z / 2.f + radiusB &&
            _d_abs(posBToA.w) < a.scale4D.w / 2.f + radiusB)
        {
            _d_Simplex simplex(_d_Simplex(vec4(0.f)));
            if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
            {
                float depth0;
                vec4 normal0(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth0));
                if (depth0 > 0.f)
                {
                    vec4 contactPosA;
                    vec4 contactPosB;
                    float supportDistanceA(support_distance(a, index1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, normal0));
                    float supportDistanceB(support_distance(b, index2, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, -normal0));
                    vec4 none;
                    float noneFloat;
                    vec4 vertices4DA[16];
                    int sizeOfVerticesA = 0;
                    vec4 vertices4DB[16];
                    int sizeOfVerticesB = 0;
                    _d_Edge4D edges4DA[32];
                    int sizeOfEdgesA = 0;
                    _d_Edge4D edges4DB[32];
                    int sizeOfEdgesB = 0;
                    _d_Face4D faces4DA[24];
                    int sizeOfFacesA = 0;
                    _d_Face4D faces4DB[24];
                    int sizeOfFacesB = 0;
                    _d_Cube4D cubes4DA[8];
                    int sizeOfCubesA = 0;
                    _d_Cube4D cubes4DB[8];
                    int sizeOfCubesB = 0;
                    for (int i(0); i < 16; i++)
                    {
                        vec4 vertexPos4D(body_pos_to_world(a, hypercube_vertices4D(i) * a.scale4D));
                        if (supportDistanceA - dot(vertexPos4D - a.position4d, normal0) < 0.01f)
                        {
                            vertices4DA[sizeOfVerticesA] = vertexPos4D; sizeOfVerticesA = sizeOfVerticesA + 1;
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        vec4 edgeVertexPos4D1(body_pos_to_world(a, edges4D(i).vertices4D[0] * a.scale4D));
                        vec4 edgeVertexPos4D2(body_pos_to_world(a, edges4D(i).vertices4D[1] * a.scale4D));
                        if (supportDistanceA - dot(edgeVertexPos4D1 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(edgeVertexPos4D2 - a.position4d, normal0) < 0.01f)
                        {
                            edges4DA[sizeOfEdgesA] = { edgeVertexPos4D1, edgeVertexPos4D2 }; sizeOfEdgesA = sizeOfEdgesA + 1;
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        vec4 faceVertexPos4D1(body_pos_to_world(a, faces4D(i).vertices4D[0] * a.scale4D));
                        vec4 faceVertexPos4D2(body_pos_to_world(a, faces4D(i).vertices4D[1] * a.scale4D));
                        vec4 faceVertexPos4D3(body_pos_to_world(a, faces4D(i).vertices4D[2] * a.scale4D));
                        if (supportDistanceA - dot(faceVertexPos4D1 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D2 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(faceVertexPos4D3 - a.position4d, normal0) < 0.01f)
                        {
                            faces4DA[sizeOfFacesA] = { faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 }; sizeOfFacesA = sizeOfFacesA + 1;
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        vec4 tetraVertexPos4D1(body_pos_to_world(a, cubes4D(i).vertices4D[0] * a.scale4D));
                        vec4 tetraVertexPos4D2(body_pos_to_world(a, cubes4D(i).vertices4D[1] * a.scale4D));
                        vec4 tetraVertexPos4D3(body_pos_to_world(a, cubes4D(i).vertices4D[2] * a.scale4D));
                        vec4 tetraVertexPos4D4(body_pos_to_world(a, cubes4D(i).vertices4D[3] * a.scale4D));
                        if (supportDistanceA - dot(tetraVertexPos4D1 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D2 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D3 - a.position4d, normal0) < 0.01f &&
                            supportDistanceA - dot(tetraVertexPos4D4 - a.position4d, normal0) < 0.01f)
                        {
                            cubes4DA[sizeOfCubesA] = { tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, cubes4D(i).normal4D,cubes4D(i).direction4D }; sizeOfCubesA = sizeOfCubesA + 1;
                        }
                    }

                    for (int i(0); i < 16; i++)
                    {
                        vec4 vertexPos4D(body_pos_to_world(b, hypercube_vertices4D(i) * b.scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b.position4d, -normal0) < 0.01f)
                        {
                            vertices4DB[sizeOfVerticesB] = vertexPos4D; sizeOfVerticesB = sizeOfVerticesB + 1;
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        vec4 edgeVertexPos4D1(body_pos_to_world(b, edges4D(i).vertices4D[0] * b.scale4D));
                        vec4 edgeVertexPos4D2(body_pos_to_world(b, edges4D(i).vertices4D[1] * b.scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(edgeVertexPos4D2 - b.position4d, -normal0) < 0.01f)
                        {
                            edges4DB[sizeOfEdgesB] = { edgeVertexPos4D1, edgeVertexPos4D2 }; sizeOfEdgesB = sizeOfEdgesB + 1;
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        vec4 faceVertexPos4D1(body_pos_to_world(b, faces4D(i).vertices4D[0] * b.scale4D));
                        vec4 faceVertexPos4D2(body_pos_to_world(b, faces4D(i).vertices4D[1] * b.scale4D));
                        vec4 faceVertexPos4D3(body_pos_to_world(b, faces4D(i).vertices4D[2] * b.scale4D));
                        if (supportDistanceB - dot(faceVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D2 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D3 - b.position4d, -normal0) < 0.01f)
                        {
                            faces4DB[sizeOfFacesB] = { faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 }; sizeOfFacesB = sizeOfFacesB + 1;
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        vec4 tetraVertexPos4D1(body_pos_to_world(b, cubes4D(i).vertices4D[0] * b.scale4D));
                        vec4 tetraVertexPos4D2(body_pos_to_world(b, cubes4D(i).vertices4D[1] * b.scale4D));
                        vec4 tetraVertexPos4D3(body_pos_to_world(b, cubes4D(i).vertices4D[2] * b.scale4D));
                        vec4 tetraVertexPos4D4(body_pos_to_world(b, cubes4D(i).vertices4D[3] * b.scale4D));
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b.position4d, -normal0) < 0.01f)
                        {
                            cubes4DB[sizeOfCubesB] = { tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, cubes4D(i).normal4D, cubes4D(i).direction4D }; sizeOfCubesB = sizeOfCubesB + 1;
                        }
                    }

                    for (int i(0); i < sizeOfVerticesA; i++)
                    {
                        for (int j(0); j < sizeOfCubesB; j++)
                        {
                            vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + world_vec_to_body(b, -normal0) * 120000.f, b.scale4D * cubes4DB[j].normal4D / 2.f, b.scale4D + vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB + dot(vertices4DA[i] - b.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DA[i] - normal0 * depth);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfVerticesB; i++)
                    {
                        for (int j(0); j < sizeOfCubesA; j++)
                        {
                            vec4 startPos4D(world_pos_to_body(a, vertices4DB[i]));
                            if (col_plane4D(startPos4D, startPos4D + world_vec_to_body(a, normal0) * 120000.f, a.scale4D * cubes4DA[j].normal4D / 2.f, a.scale4D + vec4(0.00001f), &noneFloat, &none, cubes4DA[j].direction4D))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DB[i] + normal0 * depth);
                                    contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfEdgesA; i++)
                    {
                        for (int j(0); j < sizeOfFacesB; j++)
                        {
                            if (is_edge_in_square(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                            {
                                get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                float depth(supportDistanceB + dot(edges4DA[i].vertices4D[0] - b.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfEdgesB; i++)
                    {
                        for (int j(0); j < sizeOfFacesA; j++)
                        {
                            if (is_edge_in_square(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                            {
                                get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

__device__ static void mesh_to_cube(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float meshRadius(length(a.scale4D) / 2.f);
    float cubeRadius(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < meshRadius + cubeRadius &&
        _d_abs(a.position4d.y - b.position4d.y) < meshRadius + cubeRadius &&
        _d_abs(a.position4d.z - b.position4d.z) < meshRadius + cubeRadius &&
        _d_abs(a.position4d.w - b.position4d.w) < meshRadius + cubeRadius)
    {
        vec4 posAToB(world_pos_to_body(b, a.position4d));
        if (_d_abs(posAToB.x) < b.scale4D.x / 2.f + meshRadius &&
            _d_abs(posAToB.y) < b.scale4D.y / 2.f + meshRadius &&
            _d_abs(posAToB.z) < b.scale4D.z / 2.f + meshRadius &&
            _d_abs(posAToB.w) < b.scale4D.w / 2.f + meshRadius)
        {
            _d_Simplex simplex(_d_Simplex(vec4(0.f)));
            if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
            {
                float depth0(0.f);
                vec4 normal0(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth0));
                if (depth0 > 0.f)
                {
                    vec4 contactPosA;
                    vec4 contactPosB;
                    float supportDistanceA(support_distance(a, index1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, normal0));
                    float supportDistanceB(support_distance(b, index2, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, -normal0));
                    vec4 none;
                    float noneFloat;
                    vec4 vertices4DA[16];
                    int sizeOfVerticesA = 0;
                    vec4 vertices4DB[16];
                    int sizeOfVerticesB = 0;
                    _d_Edge4D edges4DA[32];
                    int sizeOfEdgesA = 0;
                    _d_Edge4D edges4DB[32];
                    int sizeOfEdgesB = 0;
                    _d_Face4D faces4DA[24];
                    int sizeOfFacesA = 0;
                    _d_Face4D faces4DB[24];
                    int sizeOfFacesB = 0;
                    _d_Tetra4D tetras4DA[16];
                    int sizeOfTetrasA = 0;
                    _d_Cube4D cubes4DB[8];
                    int sizeOfCubesB = 0;

                    for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId] /4; i++)
                    {
                        vec4 tetraVertexPos4D1(body_pos_to_world(a,get_vertex(a.primitiveId, 4 * i, vertices4DsVec, verticesStartIndices) * a.scale4D));
                        vec4 tetraVertexPos4D2(body_pos_to_world(a,get_vertex(a.primitiveId, 4 * i + 1, vertices4DsVec, verticesStartIndices) * a.scale4D));
                        vec4 tetraVertexPos4D3(body_pos_to_world(a,get_vertex(a.primitiveId, 4 * i + 2, vertices4DsVec, verticesStartIndices) * a.scale4D));
                        vec4 tetraVertexPos4D4(body_pos_to_world(a,get_vertex(a.primitiveId, 4 * i + 3, vertices4DsVec, verticesStartIndices) * a.scale4D));
                        vec4 distances(vec4(
                            supportDistanceA - dot(tetraVertexPos4D1 - a.position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D2 - a.position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D3 - a.position4d, normal0),
                            supportDistanceA - dot(tetraVertexPos4D4 - a.position4d, normal0)
                        ));
                        tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, tetras4DA,&sizeOfTetrasA);
                        faces_used(vec3(distances[0],distances[1],distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                        faces_used(vec3(distances[0],distances[1],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                        faces_used(vec3(distances[0],distances[2],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                        faces_used(vec3(distances[1],distances[2],distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                        edges_used(vec2(distances[0],distances[1]), { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        edges_used(vec2(distances[0],distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        edges_used(vec2(distances[0],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        edges_used(vec2(distances[1],distances[2]), { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        edges_used(vec2(distances[1],distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        edges_used(vec2(distances[2],distances[3]), { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                        vertices_used(distances[0], tetraVertexPos4D1, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                        vertices_used(distances[1], tetraVertexPos4D2, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                        vertices_used(distances[2], tetraVertexPos4D3, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                        vertices_used(distances[3], tetraVertexPos4D4, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                    }

                    for (int i(0); i < 16; i++)
                    {
                        vec4 vertexPos4D(body_pos_to_world(b, hypercube_vertices4D(i) * b.scale4D));
                        if (supportDistanceB - dot(vertexPos4D - b.position4d, -normal0) < 0.01f)
                        {
                            vertices4DB[sizeOfVerticesB] = vertexPos4D; sizeOfVerticesB = sizeOfVerticesB + 1;
                        }
                    }
                    for (int i(0); i < 32; i++)
                    {
                        vec4 edgeVertexPos4D1(body_pos_to_world(b, edges4D(i).vertices4D[0] * b.scale4D));
                        vec4 edgeVertexPos4D2(body_pos_to_world(b, edges4D(i).vertices4D[1] * b.scale4D));
                        if (supportDistanceB - dot(edgeVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(edgeVertexPos4D2 - b.position4d, -normal0) < 0.01f)
                        {
                            edges4DB[sizeOfEdgesB] = { edgeVertexPos4D1, edgeVertexPos4D2 }; sizeOfEdgesB = sizeOfEdgesB + 1;
                        }
                    }
                    for (int i(0); i < 24; i++)
                    {
                        vec4 faceVertexPos4D1(body_pos_to_world(b, faces4D(i).vertices4D[0] * b.scale4D));
                        vec4 faceVertexPos4D2(body_pos_to_world(b, faces4D(i).vertices4D[1] * b.scale4D));
                        vec4 faceVertexPos4D3(body_pos_to_world(b, faces4D(i).vertices4D[2] * b.scale4D));
                        if (supportDistanceB - dot(faceVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D2 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(faceVertexPos4D3 - b.position4d, -normal0) < 0.01f)
                        {
                            faces4DB[sizeOfFacesB] = { faceVertexPos4D1, faceVertexPos4D2, faceVertexPos4D3 }; sizeOfFacesB = sizeOfFacesB + 1;
                        }
                    }
                    for (int i(0); i < 8; i++)
                    {
                        vec4 tetraVertexPos4D1(body_pos_to_world(b, cubes4D(i).vertices4D[0] * b.scale4D));
                        vec4 tetraVertexPos4D2(body_pos_to_world(b, cubes4D(i).vertices4D[1] * b.scale4D));
                        vec4 tetraVertexPos4D3(body_pos_to_world(b, cubes4D(i).vertices4D[2] * b.scale4D));
                        vec4 tetraVertexPos4D4(body_pos_to_world(b, cubes4D(i).vertices4D[3] * b.scale4D));
                        if (supportDistanceB - dot(tetraVertexPos4D1 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D2 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D3 - b.position4d, -normal0) < 0.01f &&
                            supportDistanceB - dot(tetraVertexPos4D4 - b.position4d, -normal0) < 0.01f)
                        {
                            cubes4DB[sizeOfCubesB] = { tetraVertexPos4D1, tetraVertexPos4D2, tetraVertexPos4D3, tetraVertexPos4D4, cubes4D(i).normal4D, cubes4D(i).direction4D}; sizeOfCubesB = sizeOfCubesB + 1;
                        }
                    }

                    for (int i(0); i < sizeOfVerticesA; i++)
                    {
                        for (int j(0); j < sizeOfCubesB; j++)
                        {
                            vec4 startPos4D(world_pos_to_body(b, vertices4DA[i]));
                            if (col_plane4D(startPos4D, startPos4D + world_vec_to_body(b, -normal0)* 120000.f, b.scale4D * cubes4DB[j].normal4D / 2.f, b.scale4D + vec4(0.00001f), &noneFloat, &none, cubes4DB[j].direction4D))
                            {
                                float depth(supportDistanceB - dot(vertices4DA[i] - b.position4d, -normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                    contactPosB = world_pos_to_body(b, vertices4DA[i] - normal0 * depth);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                    else { i = 10000; break; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfVerticesB; i++)
                    {
                        for (int j(0); j < sizeOfTetrasA; j++)
                        {
                            if (is_in_tetra2(vertices4DB[i], tetras4DA[j].vertices4D[0], tetras4DA[j].vertices4D[1], tetras4DA[j].vertices4D[2], tetras4DA[j].vertices4D[3]))
                            {
                                float depth(supportDistanceA - dot(vertices4DB[i] - a.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    contactPosA = world_pos_to_body(a, vertices4DB[i] + normal0 * depth);
                                    contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                    else { i = 10000; break; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfEdgesA; i++)
                    {
                        for (int j(0); j < sizeOfFacesB; j++)
                        {
                            if (is_edge_in_square(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                            {
                                float depth(supportDistanceB - dot(edges4DA[i].vertices4D[0] - b.position4d, -normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                    else { i = 10000; break; }
                                }
                            }
                        }
                    }
                    for (int i(0); i < sizeOfEdgesB; i++)
                    {
                        for (int j(0); j < sizeOfFacesA; j++)
                        {
                            if (is_edge_in_face(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                            {
                                float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a.position4d, normal0));
                                if (depth > 0.f)
                                {
                                    get_edge_in_face_pos(-normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                                    contactPosA = world_pos_to_body(a, contactPosA);
                                    contactPosB = world_pos_to_body(b, contactPosB);
                                    inverse(&contactPosA, &contactPosB, isInverse);
                                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB},1  }; *size = *size + 1; }
                                    else { i = 10000; break; }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

__device__ static void mesh_to_mesh(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float meshRadiusA(length(a.scale4D) / 2.f);
    float meshRadiusB(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < meshRadiusA + meshRadiusB &&
        _d_abs(a.position4d.y - b.position4d.y) < meshRadiusA + meshRadiusB &&
        _d_abs(a.position4d.z - b.position4d.z) < meshRadiusA + meshRadiusB &&
        _d_abs(a.position4d.w - b.position4d.w) < meshRadiusA + meshRadiusB)
    {
        _d_Simplex simplex(_d_Simplex(vec4(0.f)));
        if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
        {
            float depth0(0.f);
            vec4 normal0(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth0));
            if (depth0 > 0.f)
            {
                vec4 contactPosA;
                vec4 contactPosB;
                float supportDistanceA(support_distance(a, index1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, normal0));
                float supportDistanceB(support_distance(b, index2, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, -normal0));
                vec4 vertices4DA[16];
                int sizeOfVerticesA = 0;
                vec4 vertices4DB[16];
                int sizeOfVerticesB = 0;
                _d_Edge4D edges4DA[32];
                int sizeOfEdgesA = 0;
                _d_Edge4D edges4DB[32];
                int sizeOfEdgesB = 0;
                _d_Face4D faces4DA[24];
                int sizeOfFacesA = 0;
                _d_Face4D faces4DB[24];
                int sizeOfFacesB = 0;
                _d_Tetra4D tetras4DA[16];
                int sizeOfTetrasA = 0;
                _d_Tetra4D tetras4DB[16];
                int sizeOfTetrasB = 0;
                for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId] / 4; i++)
                {
                    vec4 tetraVertexPos4D1(body_pos_to_world(a, get_vertex(a.primitiveId, 4 * i, vertices4DsVec, verticesStartIndices) * a.scale4D));
                    vec4 tetraVertexPos4D2(body_pos_to_world(a, get_vertex(a.primitiveId, 4 * i + 1, vertices4DsVec, verticesStartIndices) * a.scale4D));
                    vec4 tetraVertexPos4D3(body_pos_to_world(a, get_vertex(a.primitiveId, 4 * i + 2, vertices4DsVec, verticesStartIndices) * a.scale4D));
                    vec4 tetraVertexPos4D4(body_pos_to_world(a, get_vertex(a.primitiveId, 4 * i + 3, vertices4DsVec, verticesStartIndices) * a.scale4D));
                    vec4 distances(vec4(
                        supportDistanceA - dot(tetraVertexPos4D1 - a.position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D2 - a.position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D3 - a.position4d, normal0),
                        supportDistanceA - dot(tetraVertexPos4D4 - a.position4d, normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, tetras4DA, &sizeOfTetrasA);
                    faces_used(vec3(distances[0], distances[1], distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                    faces_used(vec3(distances[0], distances[1], distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                    faces_used(vec3(distances[0], distances[2], distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                    faces_used(vec3(distances[1], distances[2], distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, faces4DA, &sizeOfFacesA);
                    edges_used(vec2(distances[0], distances[1]), { tetraVertexPos4D1 ,tetraVertexPos4D2 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    edges_used(vec2(distances[0], distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D3 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    edges_used(vec2(distances[0], distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    edges_used(vec2(distances[1], distances[2]), { tetraVertexPos4D2 ,tetraVertexPos4D3 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    edges_used(vec2(distances[1], distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    edges_used(vec2(distances[2], distances[3]), { tetraVertexPos4D3 ,tetraVertexPos4D4 }, normal0, a.position4d, edges4DA, &sizeOfEdgesA);
                    vertices_used(distances[0], tetraVertexPos4D1, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                    vertices_used(distances[1], tetraVertexPos4D2, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                    vertices_used(distances[2], tetraVertexPos4D3, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                    vertices_used(distances[3], tetraVertexPos4D4, normal0, a.position4d, vertices4DA, &sizeOfVerticesA);
                }
                for (unsigned int i(0); i < sizesOfVertices4D[b.primitiveId] / 4; i++)
                {
                    vec4 tetraVertexPos4D1(body_pos_to_world(b, get_vertex(b.primitiveId, 4 * i, vertices4DsVec, verticesStartIndices) * b.scale4D));
                    vec4 tetraVertexPos4D2(body_pos_to_world(b, get_vertex(b.primitiveId, 4 * i + 1, vertices4DsVec, verticesStartIndices) * b.scale4D));
                    vec4 tetraVertexPos4D3(body_pos_to_world(b, get_vertex(b.primitiveId, 4 * i + 2, vertices4DsVec, verticesStartIndices) * b.scale4D));
                    vec4 tetraVertexPos4D4(body_pos_to_world(b, get_vertex(b.primitiveId, 4 * i + 3, vertices4DsVec, verticesStartIndices) * b.scale4D));
                    vec4 distances(vec4(
                        supportDistanceB - dot(tetraVertexPos4D1 - b.position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D2 - b.position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D3 - b.position4d, -normal0),
                        supportDistanceB - dot(tetraVertexPos4D4 - b.position4d, -normal0)
                    ));
                    tetras_used(distances, { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b.position4d, tetras4DB, &sizeOfTetrasB);
                    faces_used(vec3(distances[0],distances[1],distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b.position4d, faces4DB, &sizeOfFacesB);
                    faces_used(vec3(distances[0],distances[1],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b.position4d, faces4DB, &sizeOfFacesB);
                    faces_used(vec3(distances[0],distances[2],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b.position4d, faces4DB, &sizeOfFacesB);
                    faces_used(vec3(distances[1],distances[2],distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b.position4d, faces4DB, &sizeOfFacesB);
                    edges_used(vec2(distances[0],distances[1]), { tetraVertexPos4D1 ,tetraVertexPos4D2 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    edges_used(vec2(distances[0],distances[2]), { tetraVertexPos4D1 ,tetraVertexPos4D3 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    edges_used(vec2(distances[0],distances[3]), { tetraVertexPos4D1 ,tetraVertexPos4D4 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    edges_used(vec2(distances[1],distances[2]), { tetraVertexPos4D2 ,tetraVertexPos4D3 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    edges_used(vec2(distances[1],distances[3]), { tetraVertexPos4D2 ,tetraVertexPos4D4 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    edges_used(vec2(distances[2],distances[3]), { tetraVertexPos4D3 ,tetraVertexPos4D4 }, -normal0, b.position4d, edges4DB, &sizeOfEdgesB);
                    vertices_used(distances[0], tetraVertexPos4D1, -normal0, b.position4d, vertices4DB, &sizeOfVerticesB);
                    vertices_used(distances[1], tetraVertexPos4D2, -normal0, b.position4d, vertices4DB, &sizeOfVerticesB);
                    vertices_used(distances[2], tetraVertexPos4D3, -normal0, b.position4d, vertices4DB, &sizeOfVerticesB);
                    vertices_used(distances[3], tetraVertexPos4D4, -normal0, b.position4d, vertices4DB, &sizeOfVerticesB);
                }

                for (int i(0); i < sizeOfVerticesA; i++)
                {
                    for (int j(0); j < sizeOfTetrasB; j++)
                    {
                        if (is_in_tetra2(vertices4DA[i], tetras4DB[j].vertices4D[0], tetras4DB[j].vertices4D[1], tetras4DB[j].vertices4D[2], tetras4DB[j].vertices4D[3]))
                        {
                            float depth(supportDistanceB + dot(vertices4DA[i] - b.position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DA[i]);
                                contactPosB = world_pos_to_body(b, vertices4DA[i] - normal0 * depth);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                else { i = 10000; break; }
                            }
                        }
                    }
                }
                for (int i(0); i < sizeOfVerticesB; i++)
                {
                    for (int j(0); j < sizeOfTetrasA; j++)
                    {
                        if (is_in_tetra2(vertices4DB[i], tetras4DA[j].vertices4D[0], tetras4DA[j].vertices4D[1], tetras4DA[j].vertices4D[2], tetras4DA[j].vertices4D[3]))
                        {
                            float depth(supportDistanceA - dot(vertices4DB[i] - a.position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, vertices4DB[i] + normal0 * depth);
                                contactPosB = world_pos_to_body(b, vertices4DB[i]);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                else { i = 10000; break; }
                            }
                        }
                    }
                }
                for (int i(0); i < sizeOfEdgesA; i++)
                {
                    for (int j(0); j < sizeOfFacesB; j++)
                    {
                        if (is_edge_in_face(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2]))
                        {
                            get_edge_in_face_pos(normal0, edges4DA[i].vertices4D[0], edges4DA[i].vertices4D[1], faces4DB[j].vertices4D[0], faces4DB[j].vertices4D[1], faces4DB[j].vertices4D[2], &contactPosA, &contactPosB);
                            float depth(supportDistanceB + dot(edges4DA[i].vertices4D[0] - b.position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                else { i = 10000; break; }
                            }
                        }
                    }
                }
                for (int i(0); i < sizeOfEdgesB; i++)
                {
                    for (int j(0); j < sizeOfFacesA; j++)
                    {
                        if (is_edge_in_face(normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2]))
                        {
                            get_edge_in_face_pos(normal0, edges4DB[i].vertices4D[0], edges4DB[i].vertices4D[1], faces4DA[j].vertices4D[0], faces4DA[j].vertices4D[1], faces4DA[j].vertices4D[2], &contactPosB, &contactPosA);
                            float depth(supportDistanceA - dot(edges4DB[i].vertices4D[0] - a.position4d, normal0));
                            if (depth > 0.f)
                            {
                                contactPosA = world_pos_to_body(a, contactPosA);
                                contactPosB = world_pos_to_body(b, contactPosB);
                                inverse(&contactPosA, &contactPosB, isInverse);
                                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                                else { i = 10000; break; }
                            }
                        }
                    }
                }
                //if (sizeOfVerticesA == 1)
                //{
                //    if (sizeOfVerticesB == 1)
                //    {
                //        contactPosA = world_pos_to_body(a, vertices4DA[0]);
                //        contactPosB = world_pos_to_body(b, vertices4DB[0]);
                //        float depth(dot(normal0, contactPosB - contactPosA));
                //        inverse(&contactPosA, &contactPosB, isInverse);
                //        if (depth > 0.f)
                //        {
                //            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal0, isInverse), depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                //        }
                //    }
                //}
            }
        }
    }
}

__device__ static void capsule_to_sphere(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, _d_Collision* collisions, int* size, bool isInverse)
{ 
    float capsuleRadius(length(a.scale4D) / 2.f);
    float sphereRadius(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < capsuleRadius + sphereRadius &&
        _d_abs(a.position4d.y - b.position4d.y) < capsuleRadius + sphereRadius &&
        _d_abs(a.position4d.z - b.position4d.z) < capsuleRadius + sphereRadius &&
        _d_abs(a.position4d.w - b.position4d.w) < capsuleRadius + sphereRadius)
    {
        float radiusA(_d_min(a.scale4D.w, _d_min(a.scale4D.x, a.scale4D.y)) / 2.f);
        float lengthA(a.scale4D.z);
        float radiusB(_d_min(b.scale4D.w, _d_min(b.scale4D.z, _d_min(b.scale4D.x, b.scale4D.y))) / 2.f);
        vec4 pA1(vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
        vec4 pA2(vec4(0.f, 0.f, radiusA - lengthA / 2.f, 0.f));
        vec4 pBToA(world_pos_to_body(a, b.position4d));
        vec4 contactPosA;
        vec4 contactPosB;
        if (length(pBToA - pA1) < radiusA + radiusB && pBToA.z >= pA1.z)
        {
            vec4 normal(normalize(pBToA - pA1));
            float depth(radiusA + radiusB - length(pBToA - pA1));
            contactPosA = pA1 + normal * radiusA;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -normal * radiusB));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
        }
        else if (length(pBToA - pA2) < radiusA + radiusB && pBToA.z <= pA2.z)
        {
            vec4 normal(normalize(pBToA - pA2));
            float depth(radiusA + radiusB - length(pBToA - pA2));
            contactPosA = pA2 - normal * radiusA;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -normal * radiusB));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
        }
        else if (length(vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)) < radiusA + radiusB && pBToA.z < pA1.z && pBToA.z > pA2.z)
        {
            vec4 normal(normalize(vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)));
            float depth(radiusA + radiusB - length(vec4(pBToA.x, pBToA.y, 0.f, pBToA.w)));
            contactPosA = vec4(0.f, 0.f, pBToA.z, 0.f) - normal * radiusA;
            contactPosB = world_vec_to_body(b, body_vec_to_world(a, -normal * radiusB));
            inverse(&contactPosA, &contactPosB, isInverse);
            normal = body_vec_to_world(a, normal);
            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
        }
    }
}

__device__ static void capsule_to_cube(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float capsuleRadius(a.scale4D.z / 2.f);
    float cubeRadius(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < capsuleRadius + cubeRadius &&
        _d_abs(a.position4d.y - b.position4d.y) < capsuleRadius + cubeRadius &&
        _d_abs(a.position4d.z - b.position4d.z) < capsuleRadius + cubeRadius &&
        _d_abs(a.position4d.w - b.position4d.w) < capsuleRadius + cubeRadius)
    {
        vec4 posAToB(world_pos_to_body(b, a.position4d));
        if (_d_abs(posAToB.x) < b.scale4D.x / 2.f + capsuleRadius &&
            _d_abs(posAToB.y) < b.scale4D.y / 2.f + capsuleRadius &&
            _d_abs(posAToB.z) < b.scale4D.z / 2.f + capsuleRadius &&
            _d_abs(posAToB.w) < b.scale4D.w / 2.f + capsuleRadius)
        {
            _d_Simplex simplex(_d_Simplex(vec4(0.f)));
            if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
            {
                float radiusA(_d_min(a.scale4D.w, _d_min(a.scale4D.x, a.scale4D.y)) / 2.f);
                float lengthA(a.scale4D.z);
                float radiusB(_d_min(b.scale4D.w, _d_min(b.scale4D.z, _d_min(b.scale4D.x, b.scale4D.y))) / 2.f);
                vec4 pA1(vec4(0.f, 0.f, lengthA / 2.f - radiusA, 0.f));
                vec4 pA2(vec4(0.f, 0.f, radiusA - lengthA / 2.f, 0.f));
                float depth(0.f);
                vec4 contact((a.position4d + b.position4d) / 2.f);
                vec4 normal(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth));
                if (b.colType == 2) { 
                    normal = vec4(0.f, -1.f, 0.f, 0.f); 
                }
                vec4 contactPosA;
                vec4 contactPosB;
                if (depth > 0.f)
                {
                    if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
                }
            }
        }
    }
}

__device__ static void capsule_to_mesh(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float radiusA(a.scale4D.z / 2.f);
    float radiusB(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < radiusA + radiusB &&
        _d_abs(a.position4d.y - b.position4d.y) < radiusA + radiusB &&
        _d_abs(a.position4d.z - b.position4d.z) < radiusA + radiusB &&
        _d_abs(a.position4d.w - b.position4d.w) < radiusA + radiusB)
    {
        _d_Simplex simplex(_d_Simplex(vec4(0.f)));
        if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
        {
            float depth(0.f);
            vec4 contact((a.position4d + b.position4d) / 2.f);
            vec4 normal(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth));
            vec4 contactPosA;
            vec4 contactPosB;
            if (depth > 0.f)
            {
                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
            }
        }
    }
}

__device__ static void capsule_to_capsule(int index1, int index2, _d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size, bool isInverse)
{
    float radiusA(a.scale4D.z / 2.f);
    float radiusB(length(b.scale4D) / 2.f);
    if (_d_abs(a.position4d.x - b.position4d.x) < radiusA + radiusB &&
        _d_abs(a.position4d.y - b.position4d.y) < radiusA + radiusB &&
        _d_abs(a.position4d.z - b.position4d.z) < radiusA + radiusB &&
        _d_abs(a.position4d.w - b.position4d.w) < radiusA + radiusB)
    {
        _d_Simplex simplex(_d_Simplex(vec4(0.f)));
        if (gjk(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, &simplex))
        {
            float depth(0.f);
            vec4 contact((a.position4d + b.position4d) / 2.f);
            vec4 normal(epa2(a, b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, simplex, &depth));
            vec4 contactPosA;
            vec4 contactPosB;
            if (depth > 0.f)
            {
                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {inverse(normal, isInverse), depth, contactPosA, contactPosB}, 2 }; *size = *size + 1; }
            }
        }
    }
}

__device__ static void sphere_to_half_space(int index1, int index2, _d_RigidBody4D a, _d_Collision* collisions, int* size)
{ 
    float height(0.f);
    float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
    if (a.position4d.y < radius + height)
    {
        vec4 normal(vec4(0.f, -1.f, 0.f, 0.f));
        vec4 contactPosA(world_pos_to_body(a, vec4(a.position4d.x, a.position4d.y - radius, a.position4d.z, a.position4d.w)));
        vec4 contactPosB(vec4(a.position4d.x, height, a.position4d.z, a.position4d.w));
        float depth(radius - a.position4d.y + height);
        if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {normal, depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
    }
}

__device__ static void cube_to_half_space(int index1, int index2, _d_RigidBody4D a, _d_Collision* collisions, int* size)
{  
    float height(0.f);
    float radiusA(length(a.scale4D) / 2.f);
    if (a.position4d.y < radiusA + height)
    {
        for (int i(0); i < 16; i++)
        {
            vec4 vertexPos4D(body_pos_to_world(a, hypercube_vertices4D(i) * a.scale4D));
            if (vertexPos4D.y < height)
            {
                vec4 normal(vec4(0.f, -1.f, 0.f, 0.f));
                vec4 contactPosA(world_pos_to_body(a, vertexPos4D));
                vec4 contactPosB(vec4(vertexPos4D.x, height, vertexPos4D.z, vertexPos4D.w));
                float depth(height - vertexPos4D.y);
                if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {normal, depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
            }
        }
    }
}

__device__ static void mesh_to_half_space(int index1, int index2, _d_RigidBody4D a, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Collision* collisions, int* size)
{  
    float height(0.f);
    float radiusB(length(a.scale4D) / 2.f);
    if (a.position4d.y < radiusB + height)
    {
        vec4 normal(vec4(0.f, -1.f, 0.f, 0.f));
        vec4 vertices4DA[32];
        int sizeOfVertices = 0;
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId]; i++)
        {
            vec4 vertexPos4D(body_pos_to_world(a, get_vertex(a.primitiveId, i, vertices4DsVec, verticesStartIndices) * a.scale4D));
            if (vertexPos4D.y < height)
            {
                bool isAdd(true);
                for (int j(0); j < sizeOfVertices; j++)
                {
                    if (vertices4DA[j] == vertexPos4D)
                    {
                        isAdd = false;
                    }
                }
                if (sizeOfVertices < 32)
                {
                    if (isAdd)
                    {
                        vertices4DA[sizeOfVertices] = vertexPos4D; sizeOfVertices = sizeOfVertices + 1;
                        vec4 contactPosA(world_pos_to_body(a, vertexPos4D));
                        vec4 contactPosB(vec4(vertexPos4D.x, height, vertexPos4D.z, vertexPos4D.w));
                        float depth(height - vertexPos4D.y);
                        if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {normal, depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
}

__device__ static void capsule_to_half_space(int index1, int index2, _d_RigidBody4D a, _d_Collision* collisions, int* size)
{
    float height(0.f);
    float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.x, a.scale4D.y)) / 2.f);
    float length(a.scale4D.z);
    {
        vec4 position4d(a.position4d + body_vec_to_world(a, vec4(0.f, 0.f, length / 2.f - radius, 0.f)));
        if (position4d.y < radius + height)
        {
            vec4 normal(vec4(0.f, -1.f, 0.f, 0.f));
            vec4 contactPosA(world_pos_to_body(a, vec4(position4d.x, position4d.y - radius, position4d.z, position4d.w)));
            vec4 contactPosB(vec4(position4d.x, height, position4d.z, position4d.w));
            float depth(radius + height - position4d.y);
            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {normal, depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
        }
    }
    {
        vec4 position4d(a.position4d - body_vec_to_world(a, vec4(0.f, 0.f, length / 2.f - radius, 0.f)));
        if (position4d.y < radius + height)
        {
            vec4 normal(vec4(0.f, -1.f, 0.f, 0.f));
            vec4 contactPosA(world_pos_to_body(a, vec4(position4d.x, position4d.y - radius, position4d.z, position4d.w)));
            vec4 contactPosB(vec4(position4d.x, height, position4d.z, position4d.w));
            float depth(radius + height - position4d.y);
            if (*size < 32) { collisions[*size] = { index1, index2, 0.f, 0.f, {normal, depth, contactPosA, contactPosB}, 1 }; *size = *size + 1; }
        }
    }
}

