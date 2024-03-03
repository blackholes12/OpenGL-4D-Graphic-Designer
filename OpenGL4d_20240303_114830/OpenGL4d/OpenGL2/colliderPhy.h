#pragma once
#include<vec4.hpp>
#include"body.h"
#include"gjk.h"
#include"resourcefile/primitive4d/box4d.h"
#include"Geometry.h"
static struct Collider 
{
    glm::vec4 normal;
    //std::vector <glm::vec4> mesh;
    float radius;
};

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

static struct VertexCellContact
{
    // if true indicates that the vertex is on body b but the cell is on body a
    bool side;
    int vertexIdx;
    int cellIdx;
    glm::vec4 normal;
};

static struct EdgeFaceContact {
    // if true indicates that the edge is on body b but the face is on body a
    bool side;
    glm::vec4 k;
    glm::vec4 t;
    glm::vec4 s;
    glm::vec4 u;
    glm::vec4 v;
    glm::vec4 normal;
};

static enum ContactData
{
    VertexCell,
    EdgeFace,
};


static enum ContactAxis
{
    VertexCell2, EdgeFace2,
};


static enum AxisResult {
    Intersection,
    NotValidAxis,
    LargerPenetration,
    NoIntersection,
};

static glm::vec4 inverse(glm::vec4 normal,bool isInverse)
{
    return isInverse ? normal : -normal;
}

static std::pair<Object4D*, Object4D*> inverse_object4D(Object4D* a, Object4D* b,bool isInverse)
{
    if (isInverse)
        return { b, a };
    else
        return { a, b };
}

//static void resolve_vertex_cell_contact(Object4D* a, Object4D* b,glm::vec4 contactNormal4D)
//{
//    // Need to determine incident cell - find the cell with the least dot
//// product with the reference normal
//    float min_dot_product = 1.0;
//    unsigned incident_cell_idx = 0;
//    for (int cell_idx = 0; cell_idx < b->primitive4D.get_size_of_vertices4D(); cell_idx++)
//    {
//        float dot_product = dot(body_vec_to_world(b, b->primitive4D.normalData4D[cell_idx]), contactNormal4D);
//        if (dot_product < min_dot_product){
//            min_dot_product = dot_product;
//            incident_cell_idx = cell_idx;
//        }
//    }
//    glm::vec4 v0 = glm::vec4(0.f);
//    for face_idx in reference_cell.faces.iter() {
//        let face = &a.mesh.faces[*face_idx];
//        // grab a representative vertex
//        v0 = a.mesh.vertices[a.mesh.edges[face.edges[0]].hd_vertex];
//
//        unsigned cell_idx;
//        if face.hd_cell == contact.cell_idx{
//            face.tl_cell
//        }
//        else {
//            face.hd_cell
//        };
//        glm::vec4 clip_normal = world_vec_to_body(b,body_vec_to_world(a,-contactNormal4D));
//        float clip_distance = dot(clip_normal,body.world_pos_to_body(b,body.body_pos_to_world(a,v0)));
//
//        clipper.clip_by(clip_normal, clip_distance);
//    }
//    float max_depth = 0.f;
//    glm::vec4 world_vec = body_pos_to_world(b,b_vec);
//    glm::vec4 a_vec = world_pos_to_body(a,world_vec);
//
//    float dist = dot(a_vec,reference_cell.normal);
//    if (dist < reference_dist){
//        max_depth = glm::max(max_depth,reference_dist - dist);
//        Some(world_vec)
//    }
//    else {
//        None
//    }
//}

static void resolve_edge_face_contact(Object4D* a, Object4D* b)
{

}

static vector<Collision*> sphere_to_sphere(Object4D* a0, Object4D* b0,int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    float massAdjustment = 0.f;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.y - b->position4D.y) < (a->scale4D.y + b->scale4D.y) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radiousA = min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f;
        float radiousB = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
        if (length(a->position4D - b->position4D) < radiousA + radiousB)
        {
            glm::vec4 normal;
            float depth;
            glm::vec4 contacts;
            massAdjustment += 1.f;
            normal = normalize(b->position4D - a->position4D);
            depth = radiousA + radiousB - length(a->position4D - b->position4D);
            contacts = a->position4D + (radiousA - depth / 2.f) * normal;
            collisions.push_back(new Collision(index1, index2, massAdjustment,massAdjustment, inverse(normal,isInverse),depth,contacts));
        }
    }
    return collisions;
}

static vector<Collision*> cube_to_sphere(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    float massAdjustment = 0.f;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float radious = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
    float cubeRadious = length(a->scale4D)/2.f;
    if (abs(a->position4D.x - b->position4D.x) < radious+ cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < radious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < radious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < radious + cubeRadious)
    {
        glm::vec4 posAToB = world_pos_to_body(a, b->position4D);
        if (abs(posAToB.x) < a->scale4D.x / 2.f + radious &&
            abs(posAToB.y) < a->scale4D.y / 2.f + radious &&
            abs(posAToB.z) < a->scale4D.z / 2.f + radious &&
            abs(posAToB.w) < a->scale4D.w / 2.f + radious)
        {
            glm::vec4 pB = world_pos_to_body(a, b->position4D);
            glm::vec4 sA = a->scale4D / 2.f;
            if (abs(pB.x) < sA.x + radious &&
                abs(pB.y) < sA.y + radious &&
                abs(pB.z) < sA.z + radious &&
                abs(pB.w) < sA.w + radious)
            {
                glm::vec4 normal;
                float depth;
                glm::vec4 contacts;
                for (int i = 0; i < 4; i++)
                {
                    int dir1[3];
                    int dir2;
                    if (i == 0)dir2 = 0, dir1[0] = 1, dir1[1] = 2, dir1[2] = 3;
                    if (i == 1)dir1[0] = 0, dir2 = 1, dir1[1] = 2, dir1[2] = 3;
                    if (i == 2)dir1[0] = 0, dir1[1] = 1, dir2 = 2, dir1[2] = 3;
                    if (i == 3)dir1[0] = 0, dir1[1] = 1, dir1[2] = 2, dir2 = 3;
                    if (abs(pB[dir1[0]]) < sA[dir1[0]] &&
                        abs(pB[dir1[1]]) < sA[dir1[1]] &&
                        abs(pB[dir1[2]]) < sA[dir1[2]])
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            float sign;
                            if (j == 0)sign = 1.f;
                            if (j == 1)sign = -1.f;
                            if (sign * pB[dir2] > sA[dir2] &&
                                abs(pB[dir2] - sign * sA[dir2]) < radious)
                            {
                                massAdjustment += 1.f;
                                normal = glm::vec4(0.f);
                                normal[dir2] = pB[dir2] - sign * sA[dir2];
                                normal = normalize(normal);
                                depth = radious - abs(pB[dir2] - sign * sA[dir2]);
                                glm::vec4 aVec4 = pB;
                                aVec4[dir2] = sign * sA[dir2];
                                contacts = aVec4 / 2.f + (pB - normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                            }
                        }
                    }
                }
                for (int i = 0; i < 6; i++)
                {
                    int dir1[2];
                    int dir2[2];
                    if (i == 0)dir1[0] = 2, dir1[1] = 3, dir2[0] = 0, dir2[1] = 1;
                    if (i == 1)dir1[0] = 1, dir1[1] = 3, dir2[0] = 0, dir2[1] = 2;
                    if (i == 2)dir1[0] = 2, dir1[1] = 1, dir2[0] = 0, dir2[1] = 3;           
                    if (i == 3) dir1[0] = 0, dir1[1] = 3, dir2[0] = 1, dir2[1] = 2;
                    if (i == 4)dir1[0] = 2, dir1[1] = 0, dir2[0] = 3, dir2[1] = 1;
                    if (i == 5)dir1[0] = 0, dir1[1] = 1, dir2[0] = 2, dir2[1] = 3;
                    if (abs(pB[dir1[0]]) < sA[dir1[0]] &&
                        abs(pB[dir1[1]]) < sA[dir1[1]])
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            float sign[2];
                            if (j == 0)sign[0] = 1.f, sign[1] = 1.f;
                            if (j == 1)sign[0] = -1.f, sign[1] = 1.f;
                            if (j == 2)sign[0] = 1.f, sign[1] = -1.f;
                            if (j == 3)sign[0] = -1.f, sign[1] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                length(glm::vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]])) < radious)
                            {
                                massAdjustment += 1.f;
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal = normalize(normal);
                                depth = radious - length(glm::vec2(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]]));
                                glm::vec4 aVec4 = pB;
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                contacts = aVec4 / 2.f + (pB - normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                            }
                        }
                    }
                }

                for (int i = 0; i < 4; i++)
                {
                    int dir1;
                    int dir2[3];
                    if (i == 0)dir2[0] = 0, dir2[1] = 1, dir2[2] = 2, dir1 = 3;
                    if (i == 1)dir2[0] = 0, dir2[1] = 1, dir1 = 2, dir2[2] = 3;
                    if (i == 2)dir2[0] = 0, dir1 = 1, dir2[1] = 2, dir2[2] = 3;
                    if (i == 3)dir1 = 0, dir2[0] = 1, dir2[1] = 2, dir2[2] = 3;
                    if (abs(pB[dir1]) < sA[dir1])
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            float sign[3];
                            if (j == 0)sign[0] = 1.f, sign[1] = 1.f, sign[2] = 1.f;
                            if (j == 1)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f;
                            if (j == 2)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f;
                            if (j == 3)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f;
                            if (j == 4)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f;
                            if (j == 5)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f;
                            if (j == 6)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f;
                            if (j == 7)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                sign[2] * pB[dir2[2]] > sA[dir2[2]] &&
                                length(glm::vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]])) < radious)
                            {
                                massAdjustment += 1.f;
                                normal = glm::vec4(0.f);
                                normal[dir2[0]] = pB[dir2[0]] - sign[0] * sA[dir2[0]];
                                normal[dir2[1]] = pB[dir2[1]] - sign[1] * sA[dir2[1]];
                                normal[dir2[2]] = pB[dir2[2]] - sign[2] * sA[dir2[2]];
                                normal = normalize(normal);
                                depth = radious - length(glm::vec3(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]]));
                                glm::vec4 aVec4 = pB;
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                contacts = aVec4 / 2.f + (pB - normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
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
                            if (j == 1)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = 1.f;
                            if (j == 2)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = 1.f;
                            if (j == 3)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = 1.f;
                            if (j == 4)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = 1.f;
                            if (j == 5)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = 1.f;
                            if (j == 6)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = 1.f;
                            if (j == 7)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = 1.f;
                            if (j == 8)sign[0] = 1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = -1.f;
                            if (j == 9)sign[0] = -1.f, sign[1] = 1.f, sign[2] = 1.f, sign[3] = -1.f;
                            if (j == 10)sign[0] = 1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = -1.f;
                            if (j == 11)sign[0] = -1.f, sign[1] = -1.f, sign[2] = 1.f, sign[3] = -1.f;
                            if (j == 12)sign[0] = 1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = -1.f;
                            if (j == 13)sign[0] = -1.f, sign[1] = 1.f, sign[2] = -1.f, sign[3] = -1.f;
                            if (j == 14)sign[0] = 1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = -1.f;
                            if (j == 15)sign[0] = -1.f, sign[1] = -1.f, sign[2] = -1.f, sign[3] = -1.f;
                            if (sign[0] * pB[dir2[0]] > sA[dir2[0]] &&
                                sign[1] * pB[dir2[1]] > sA[dir2[1]] &&
                                sign[2] * pB[dir2[2]] > sA[dir2[2]] &&
                                sign[3] * pB[dir2[3]] > sA[dir2[3]] &&
                                length(glm::vec4(pB[dir2[0]] - sign[0] * sA[dir2[0]],
                                    pB[dir2[1]] - sign[1] * sA[dir2[1]],
                                    pB[dir2[2]] - sign[2] * sA[dir2[2]],
                                    pB[dir2[3]] - sign[3] * sA[dir2[3]])) < radious)
                            {
                                massAdjustment += 1.f;
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
                                glm::vec4 aVec4 = pB;
                                aVec4[dir2[0]] = sign[0] * sA[dir2[0]];
                                aVec4[dir2[1]] = sign[1] * sA[dir2[1]];
                                aVec4[dir2[2]] = sign[2] * sA[dir2[2]];
                                aVec4[dir2[3]] = sign[3] * sA[dir2[3]];
                                contacts = aVec4 / 2.f + (pB - normal) / 2.f;
                                normal = body_vec_to_world(a, normal);
                                contacts = body_pos_to_world(a, contacts);
                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> mesh_to_sphere(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    float massAdjustment = 0.f;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float radious = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
    float meshRadious = length(a->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < radious + meshRadious &&
        abs(a->position4D.y - b->position4D.y) < radious + meshRadious &&
        abs(a->position4D.z - b->position4D.z) < radious + meshRadious &&
        abs(a->position4D.w - b->position4D.w) < radious + meshRadious)
    {
        glm::vec4 pB = world_pos_to_body(a, b->position4D);
        glm::vec4 normal;
        float depth;
        glm::vec4 contacts;
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
        {
            glm::vec4 vertexPos4D1 = a->primitive4D.vertexData4D[4 * i] * a->scale4D;
            glm::vec4 vertexPos4D2 = a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D;
            glm::vec4 vertexPos4D3 = a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D;
            glm::vec4 vertexPos4D4 = a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D;
            if (length(vertexPos4D1 - vertexPos4D2) > 0.001f && length(vertexPos4D1 - vertexPos4D3) > 0.001f &&
                length(vertexPos4D1 - vertexPos4D4) > 0.001f && length(vertexPos4D2 - vertexPos4D3) > 0.001f &&
                length(vertexPos4D2 - vertexPos4D4) > 0.001f && length(vertexPos4D3 - vertexPos4D4) > 0.001f)
            {
                if (sphere_col_tetra4D(pB, radious,
                    normalize(a->primitive4D.normalData4D[4 * i]/ a->scale4D),
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }

                if (sphere_col_face4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D3,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_face4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D2,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_face4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_face4D(pB, radious,
                    vertexPos4D2,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }

                if (sphere_col_line4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D2,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_line4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D3,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_line4D(pB, radious,
                    vertexPos4D1,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_line4D(pB, radious,
                    vertexPos4D2,
                    vertexPos4D3,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_line4D(pB, radious,
                    vertexPos4D2,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_line4D(pB, radious,
                    vertexPos4D3,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }

                if (sphere_col_point4D(pB, radious,
                    vertexPos4D1,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_point4D(pB, radious,
                    vertexPos4D2,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_point4D(pB, radious,
                    vertexPos4D3,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
                if (sphere_col_point4D(pB, radious,
                    vertexPos4D4,
                    &depth, &normal, &contacts))
                {
                    massAdjustment += 1.f;
                    normal = body_vec_to_world(a, normal);
                    contacts = body_pos_to_world(a, contacts);
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, inverse(normal, isInverse), depth, contacts));
                }
            }
        }
    }

    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> terrain_to_sphere(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radious = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            int size = 4;
            unsigned int cubeIndex;
            glm::vec4 detectPos4D0;
            for (size_t x = 0; x < size; x++)
            {
                for (size_t z = 0; z < size; z++)
                {
                    for (size_t w = 0; w < size; w++)
                    {
                        if (abs(b->position4D.x - a->position4D.x - x + 1.5f) < 0.5f + radious &&
                            abs(b->position4D.z - a->position4D.z - z + 1.5f) < 0.5f + radious &&
                            abs(b->position4D.w - a->position4D.w - w + 1.5f) < 0.5f + radious)

                        {
                            cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                            for (size_t i = 0; i < 6; i++)
                            {
                                glm::vec4 normal;
                                float depth;
                                glm::vec4 contacts;
                                if (sphere_col_terrain_tetra4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    //std::cout << "depth: "<< depth << "\n";
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_face4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_line4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }

                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }
                                if (sphere_col_point4D(b->position4D - a->position4D, radious,
                                    a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                    &depth, &normal, &contacts))
                                {
                                    massAdjustment += 1.f;
                                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                }

                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> cube_to_cube(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    float massAdjustment = 0.f;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float radiousA = length(a->scale4D) / 2.f;
    float radiousB = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < radiousA + radiousB &&
        abs(a->position4D.y - b->position4D.y) < radiousA + radiousB &&
        abs(a->position4D.z - b->position4D.z) < radiousA + radiousB &&
        abs(a->position4D.w - b->position4D.w) < radiousA + radiousB)
    {
        glm::vec4 posAToB = world_pos_to_body(b, a->position4D);
        glm::vec4 posBToA = world_pos_to_body(a, b->position4D);
        if (abs(posAToB.x) < b->scale4D.x / 2.f + radiousA &&
            abs(posAToB.y) < b->scale4D.y / 2.f + radiousA &&
            abs(posAToB.z) < b->scale4D.z / 2.f + radiousA &&
            abs(posAToB.w) < b->scale4D.w / 2.f + radiousA &&
            abs(posBToA.x) < a->scale4D.x / 2.f + radiousB &&
            abs(posBToA.y) < a->scale4D.y / 2.f + radiousB &&
            abs(posBToA.z) < a->scale4D.z / 2.f + radiousB &&
            abs(posBToA.w) < a->scale4D.w / 2.f + radiousB)
        {
            Simplex simplex = Simplex(glm::vec4(0.f));
            if (gjk(a, b, 12, &simplex))
            {
                float depth = 0.f;
                glm::vec4 contact = (a->position4D+b->position4D)/2.f;
                std::vector<glm::vec4> supportPoints1;
                std::vector<glm::vec4> supportPoints2;
                glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1,&supportPoints2);
                if (depth > 0.f)
                {
                    bool isMuti = false;
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
                            contact = get_line_in_face_pos(normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                        }
                        if (supportPoints2.size() == 8)
                        {
                            isMuti = true;
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                        }
                    }
                    if (supportPoints2.size() == 2)
                    {
                        if (supportPoints1.size() == 4)
                        {
                            contact = get_line_in_face_pos(-normal, supportPoints2[0], supportPoints2[1], supportPoints1[0], supportPoints1[1], supportPoints1[2]);
                        }
                        if (supportPoints1.size() == 8)
                        {
                            isMuti = true;
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints2[0] + depth * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints2[1] + depth * normal / 2.f));
                        }
                    }
                    if (supportPoints1.size() == 4)
                    {
                        if (supportPoints2.size() == 4)
                        {
                            isMuti = true;
                            float scaleRate = length(a->scale4D) / length(b->scale4D);
                            if (scaleRate > 4.f)
                            {
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[0] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[1] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[2] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[3] + depth * normal / 2.f));
                            }
                            else if (1.f / scaleRate > 4.f)
                            {
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints1[2] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints1[3] - depth * normal / 2.f));
                            }
                            else
                            {
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints1[2] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints1[3] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints2[0] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints2[1] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints2[2] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth, supportPoints2[3] + depth * normal / 2.f));
                            }
                        }
                        if (supportPoints2.size() == 8)
                        {
                            isMuti = true;
                            float depth2[4];
                            for (int i = 0; i < 4; i++)
                            {
                                depth2[i] = abs(dot(supportPoints1[i]- supportPoints2[0], normal));
                            }
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[0], supportPoints1[0] - depth2[0] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[1], supportPoints1[1] - depth2[1] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[2], supportPoints1[2] - depth2[2] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[3], supportPoints1[3] - depth2[3] * normal / 2.f));
                        }
                    }
                    if (supportPoints2.size() == 4)
                    {
                        if (supportPoints1.size() == 8)
                        {
                            isMuti = true;
                            float depth2[4];
                            for (int i = 0; i < 4; i++)
                            {
                                depth2[i] = abs(dot(supportPoints2[i] - supportPoints1[0], normal));
                            }
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[0], supportPoints2[0] + depth2[0] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[1], supportPoints2[1] + depth2[1] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[2], supportPoints2[2] + depth2[2] * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth2[3], supportPoints2[3] + depth2[3] * normal / 2.f));
                        }
                    }
                    if (supportPoints1.size() == 8)
                    {
                        if (supportPoints2.size() == 8)
                        {
                            isMuti = true;
                            float scaleRate = length(a->scale4D) / length(b->scale4D);
                            if (scaleRate > 4.f)
                            {
                                float depth2[8];
                                for (int i = 0; i < 8; i++)
                                {
                                    depth2[i] = abs(dot(supportPoints2[i] - supportPoints1[0], normal));
                                }
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[0], supportPoints2[0] + depth2[0] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[1], supportPoints2[1] + depth2[1] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[2], supportPoints2[2] + depth2[2] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[3], supportPoints2[3] + depth2[3] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[4], supportPoints2[4] + depth2[4] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[5], supportPoints2[5] + depth2[5] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[6], supportPoints2[6] + depth2[6] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[7], supportPoints2[7] + depth2[7] * normal / 2.f));
                            }
                            else if(1.f/ scaleRate > 4.f)
                            {
                                float depth2[8];
                                for (int i = 0; i < 8; i++)
                                {
                                    depth2[i] = abs(dot(supportPoints1[i] - supportPoints2[0], normal));
                                }
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[0], supportPoints1[0] - depth2[0] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[1], supportPoints1[1] - depth2[1] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[2], supportPoints1[2] - depth2[2] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[3], supportPoints1[3] - depth2[3] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[4], supportPoints1[4] - depth2[4] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[5], supportPoints1[5] - depth2[5] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[6], supportPoints1[6] - depth2[6] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 8.f, 8.f, inverse(normal, isInverse), depth2[7], supportPoints1[7] - depth2[7] * normal / 2.f));
                            }
                            else
                            {
                                float depth2[8];
                                for (int i = 0; i < 8; i++)
                                {
                                    depth2[i] = abs(dot(supportPoints1[i] - supportPoints2[0], normal));
                                }
                                float depth3[8];
                                for (int i = 0; i < 8; i++)
                                {
                                    depth3[i] = abs(dot(supportPoints2[i] - supportPoints1[0], normal));
                                }
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[0], supportPoints1[0] - depth2[0] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[1], supportPoints1[1] - depth2[1] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[2], supportPoints1[2] - depth2[2] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[3], supportPoints1[3] - depth2[3] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[4], supportPoints1[4] - depth2[4] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[5], supportPoints1[5] - depth2[5] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[6], supportPoints1[6] - depth2[6] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth2[7], supportPoints1[7] - depth2[7] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[0], supportPoints2[0] + depth3[0] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[1], supportPoints2[1] + depth3[1] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[2], supportPoints2[2] + depth3[2] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[3], supportPoints2[3] + depth3[3] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[4], supportPoints2[4] + depth3[4] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[5], supportPoints2[5] + depth3[5] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[6], supportPoints2[6] + depth3[6] * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 16.f, 16.f, inverse(normal, isInverse), depth3[7], supportPoints2[7] + depth3[7] * normal / 2.f));
                            }
                        }
                    }
                    if(!isMuti)
                    collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
                }
            }
        }
    }
    return collisions;
}

static vector<Collision*> mesh_to_cube(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float meshRadious = length(a->scale4D) / 2.f;
    float cubeRadious = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < meshRadious + cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < meshRadious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < meshRadious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < meshRadious + cubeRadious)
    {
        glm::vec4 posAToB = world_pos_to_body(b, a->position4D);
        if (abs(posAToB.x) < b->scale4D.x / 2.f + meshRadious &&
            abs(posAToB.y) < b->scale4D.y / 2.f + meshRadious &&
            abs(posAToB.z) < b->scale4D.z / 2.f + meshRadious &&
            abs(posAToB.w) < b->scale4D.w / 2.f + meshRadious)
        {
            Simplex simplex = Simplex(glm::vec4(0.f));
            if (gjk(a, b, 12, &simplex))
            {
                float depth = 0.f;
                glm::vec4 contact = (a->position4D + b->position4D) / 2.f;
                std::vector<glm::vec4> supportPoints1;
                std::vector<glm::vec4> supportPoints2;
                glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1, &supportPoints2);
                if (depth > 0.f)
                {
                    bool isMuti = false;
                    if (supportPoints1.size() == 1)
                    {
                        contact = supportPoints1[0] - depth * normal / 2.f;
                    }
                    if (supportPoints2.size() == 1)
                    {
                        contact = supportPoints2[0] + depth * normal / 2.f;
                    }
                    if (supportPoints2.size() == 2)
                    {
                        if (supportPoints1.size() == 3)
                        {
                            contact = get_line_in_face_pos(normal, supportPoints2[0], supportPoints2[1], supportPoints1[0], supportPoints1[1], supportPoints1[2]);
                        }
                        if (supportPoints1.size() == 4)
                        {
                            contact = get_line_in_face_pos(normal, supportPoints2[0], supportPoints2[1], supportPoints1[0], supportPoints1[1], supportPoints1[2]);
                        }
                    }
                    if (supportPoints2.size() == 4)
                    {
                        if (supportPoints1.size() == 2)
                        {
                            contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                        }
                        if (supportPoints1.size() > 3)
                        {
                            if (supportPoints1.size() > 12)
                            {
                                contact = (supportPoints2[0] + supportPoints2[1] + supportPoints2[2] + supportPoints2[3]) / 4.f + depth * normal / 2.f;
                            }
                            else
                            {
                                isMuti = true;
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[0] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[1] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[2] + depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 4.f, 4.f, inverse(normal, isInverse), depth, supportPoints2[3] + depth * normal / 2.f));
                            }
                        }
                    }
                    if (supportPoints2.size() == 8)
                    {
                        if (supportPoints1.size() == 2)
                        {
                            isMuti = true;
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                        }
                        if (supportPoints1.size() == 3)
                        {
                            isMuti = true;
                            collisions.push_back(new Collision(index1, index2, 3.f, 3.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 3.f, 3.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                            collisions.push_back(new Collision(index1, index2, 3.f, 3.f, inverse(normal, isInverse), depth, supportPoints1[2] - depth * normal / 2.f));
                        }
                        if (supportPoints1.size() > 3)
                        {
                            if (supportPoints1.size() > 12)
                            {
                                contact = a->position4D;
                            }
                            else
                            {
                                isMuti = true;
                                float scaleRate = length(a->scale4D) / length(b->scale4D);
                                if (scaleRate > 4.f)
                                {
                                    for (int i = 0; i < supportPoints2.size(); i++)
                                    {
                                        collisions.push_back(new Collision(index1, index2, supportPoints2.size(), supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints2[i] + depth * normal / 2.f));
                                    }
                                }
                                else if (1.f/scaleRate > 4.f)
                                {
                                    for (int i = 0; i < supportPoints1.size(); i++)
                                    {
                                        collisions.push_back(new Collision(index1, index2, supportPoints1.size(), supportPoints1.size(), inverse(normal, isInverse), depth, supportPoints1[i] - depth * normal / 2.f));
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < supportPoints1.size(); i++)
                                    {
                                        collisions.push_back(new Collision(index1, index2, supportPoints1.size() + supportPoints2.size(), supportPoints1.size() + supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints1[i] - depth * normal / 2.f));
                                    }
                                    for (int i = 0; i < supportPoints2.size(); i++)
                                    {
                                        collisions.push_back(new Collision(index1, index2, supportPoints1.size() + supportPoints2.size(), supportPoints1.size() + supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints2[i] + depth * normal / 2.f));
                                    }
                                }
                            }
                        }
                    }
                    if(!isMuti)
                    collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
                }
            }
        }
    }
    return collisions;
}

static vector<Collision*> terrain_to_cube(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radious = length(b->scale4D) / 2.f;
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            unsigned int size = 4;
            unsigned int cubeIndex;
            for (int i = 0; i < 16; i++)
            {
                glm::vec4 vertexOfB = body_pos_to_world(b, hypercube::vertices4D[i] * b->scale4D);
                for (size_t x = 0; x < size; x++)
                {
                    for (size_t z = 0; z < size; z++)
                    {
                        for (size_t w = 0; w < size; w++)
                        {
                            if (abs(b->position4D.x - a->position4D.x - x + 1.5f) < 0.5f + radious &&
                                abs(b->position4D.z - a->position4D.z - z + 1.5f) < 0.5f + radious &&
                                abs(b->position4D.w - a->position4D.w - w + 1.5f) < 0.5f + radious)
                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i = 0; i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
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
                                                massAdjustment += 1.f;
                                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> mesh_to_mesh(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    float meshRadiousA = length(a->scale4D) / 2.f;
    float meshRadiousB = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.y - b->position4D.y) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.z - b->position4D.z) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.w - b->position4D.w) < meshRadiousA + meshRadiousB)
    {
        Simplex simplex = Simplex(glm::vec4(0.f));
        if (gjk(a, b, 12, &simplex))
        {
            float depth = 0.f;
            glm::vec4 contact = (a->position4D + b->position4D) / 2.f;
             std::vector<glm::vec4> supportPoints1;
                std::vector<glm::vec4> supportPoints2;
                glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1,&supportPoints2);
            if (depth > 0.f)
            {
                bool isMuti = false;
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
                        contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                    if (supportPoints2.size() == 4)
                    {
                        contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                }
                if (supportPoints1.size() == 3)
                {
                    if (supportPoints2.size() == 2)
                    {
                        contact = get_line_in_face_pos(normal, supportPoints2[0], supportPoints2[1], supportPoints1[0], supportPoints1[1], supportPoints1[2]);
                    }
                }
                if (supportPoints1.size() == 4)
                {
                    if (supportPoints2.size() == 2)
                    {
                        contact = get_line_in_face_pos(normal, supportPoints2[0], supportPoints2[1], supportPoints1[0], supportPoints1[1], supportPoints1[2]);
                    }
                    if (supportPoints2.size() > 4)
                    {
                        if (supportPoints2.size() > 12)
                        {
                            contact = b->position4D;
                        }
                        else
                        {
                            for (int i = 0; i < supportPoints2.size(); i++)
                            {
                                collisions.push_back(new Collision(index1, index2, supportPoints2.size(), supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints2[i] + depth * normal / 2.f));
                            }
                        }
                    }
                }
                if (supportPoints1.size() > 4)
                {
                    if (supportPoints1.size() > 12)
                    {
                        if (supportPoints2.size() == 3)
                        {
                            contact = b->position4D;
                        }
                        if (supportPoints2.size() == 4)
                        {
                            contact = a->position4D;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < supportPoints1.size(); i++)
                        {
                            collisions.push_back(new Collision(index1, index2, supportPoints1.size(), supportPoints1.size(), inverse(normal, isInverse), depth, supportPoints1[i] - depth * normal / 2.f));
                        }
                    }
                }
                if (supportPoints2.size() > 4)
                {
                    if (supportPoints2.size() > 12)
                    {
                        if (supportPoints1.size() == 3)
                        {
                            contact = a->position4D;
                        }
                    }
                    else
                    {
                        isMuti = true;
                        float scaleRate = length(a->scale4D) / length(b->scale4D);
                        if (scaleRate > 4.f)
                        {
                            for (int i = 0; i < supportPoints2.size(); i++)
                            {
                                collisions.push_back(new Collision(index1, index2, supportPoints2.size(), supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints2[i] + depth * normal / 2.f));
                            }
                        }
                        else if (1.f / scaleRate > 4.f)
                        {
                            for (int i = 0; i < supportPoints1.size(); i++)
                            {
                                collisions.push_back(new Collision(index1, index2, supportPoints1.size(), supportPoints1.size(), inverse(normal, isInverse), depth, supportPoints1[i] - depth * normal / 2.f));
                            }
                        }
                        else
                        {
                            for (int i = 0; i < supportPoints2.size(); i++)
                            {
                                collisions.push_back(new Collision(index1, index2, supportPoints1.size() + supportPoints2.size(), supportPoints1.size() + supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints2[i] + depth * normal / 2.f));
                            }
                            for (int i = 0; i < supportPoints1.size(); i++)
                            {
                                collisions.push_back(new Collision(index1, index2, supportPoints1.size() + supportPoints2.size(), supportPoints1.size() + supportPoints2.size(), inverse(normal, isInverse), depth, supportPoints1[i] - depth * normal / 2.f));
                            }
                        }
                    }
                }
                if(!isMuti)
                collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
            }
        }
    }
    return collisions;
}

/*
static vector<Collision*> mesh_to_mesh(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    float massAdjustment = 0.f;
    float meshRadiousA = length(a->scale4D) / 2.f;
    float meshRadiousB = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.y - b->position4D.y) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.z - b->position4D.z) < meshRadiousA + meshRadiousB &&
        abs(a->position4D.w - b->position4D.w) < meshRadiousA + meshRadiousB)
    {
        Simplex simplex = Simplex(glm::vec4(0.f));
        if (gjk(a, b, false, 12, &simplex))
        {
            //std::cout << a->objectName << "collide" << b->objectName<< "\n";
            glm::vec4 normal = glm::vec4(0.f);
            float depth = 0.f;
            glm::vec4 contact = glm::vec4(0.f);
            normal = inverse(get_collision_information2(a, b, 24, simplex), isInverse);
            for (int i = 0; i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
            {
                glm::vec4 tetraNormal4DOf1 = normalize(body_vec_to_world(a, a->primitive4D.normalData4D[4 * i] / a->scale4D));
                if (dot(tetraNormal4DOf1, normal) > 0.985f)
                {
                    glm::vec4 vertex4D1Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i] * a->scale4D);
                    glm::vec4 vertex4D2Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 1] * a->scale4D);
                    glm::vec4 vertex4D3Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 2] * a->scale4D);
                    glm::vec4 vertex4D4Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + 3] * a->scale4D);
                    for (int j = 0; j < b->primitive4D.get_size_of_vertices4D(); j++)
                    {
                        glm::vec4 vertex4DOfB = body_pos_to_world(b, b->primitive4D.vertexData4D[j] * b->scale4D);
                        depth = dot(vertex4D1Of1 - vertex4DOfB, tetraNormal4DOf1);
                        if (depth > 0.f)
                        {
                            if (is_in_tetra2(vertex4DOfB + depth * normal, vertex4D1Of1, vertex4D2Of1, vertex4D3Of1, vertex4D4Of1))
                            {
                                contact = vertex4DOfB + 0.5f * depth * normal;
                                massAdjustment += 1.f;
                                collisions.push_back(new Collision(index1, index2, 1.f, 1.f, tetraNormal4DOf1, depth, contact));
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
            {
                glm::vec4 tetraNormal4DOfB = normalize(body_vec_to_world(b, b->primitive4D.normalData4D[4 * i] / b->scale4D));
                if (dot(tetraNormal4DOfB, normal) > 0.985f)
                {
                    glm::vec4 vertex4D1OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i] * b->scale4D);
                    glm::vec4 vertex4D2OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 1] * b->scale4D);
                    glm::vec4 vertex4D3OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 2] * b->scale4D);
                    glm::vec4 vertex4D4OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + 3] * b->scale4D);
                    for (int j = 0; j < a->primitive4D.get_size_of_vertices4D(); j++)
                    {
                        glm::vec4 vertex4DOf1 = body_pos_to_world(a, a->primitive4D.vertexData4D[j] * a->scale4D);
                        depth = dot(vertex4D1OfB - vertex4DOf1, tetraNormal4DOfB);
                        if (depth > 0.f)
                        {
                            if (is_in_tetra2(vertex4DOf1 + depth * normal, vertex4D1OfB, vertex4D2OfB, vertex4D3OfB, vertex4D4OfB))
                            {
                                contact = vertex4DOf1 + 0.5f * depth * normal;
                                massAdjustment += 1.f;
                                collisions.push_back(new Collision(index1, index2, 1.f, 1.f, tetraNormal4DOfB, depth, contact));
                            }
                        }
                    }
                }
            }
            ////////
            for (int i = 0; i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    unsigned faceIndex1, faceIndex2, faceIndex3;
                    if (j == 0)faceIndex1 = 0, faceIndex2 = 1, faceIndex3 = 2; if (j == 1)faceIndex1 = 0, faceIndex2 = 1, faceIndex3 = 3; if (j == 2)faceIndex1 = 0, faceIndex2 = 2, faceIndex3 = 3; if (j == 3)faceIndex1 = 1, faceIndex2 = 2, faceIndex3 = 3;
                    glm::vec4 faceVertex4D1Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + faceIndex1] * a->scale4D);
                    glm::vec4 faceVertex4D2Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + faceIndex2] * a->scale4D);
                    glm::vec4 faceVertex4D3Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * i + faceIndex3] * a->scale4D);
                    if (abs(dot(normal, normalize(faceVertex4D1Of1 - faceVertex4D2Of1))) < 0.001f && abs(dot(normal, normalize(faceVertex4D1Of1 - faceVertex4D3Of1))) < 0.001f)
                    {
                        if (length(faceVertex4D1Of1 - faceVertex4D2Of1) > 0.001f && length(faceVertex4D1Of1 - faceVertex4D3Of1) > 0.001f && length(faceVertex4D2Of1 - faceVertex4D3Of1) > 0.001f)
                        {
                            for (int l = 0; l < a->primitive4D.get_size_of_vertices4D() / 4; l++)
                            {
                                for (int m = 0; m < 6; m++)
                                {
                                    unsigned lineIndex1, lineIndex2;
                                    if (m == 0)lineIndex1 = 0, lineIndex2 = 1; if (m == 1)lineIndex1 = 0, lineIndex2 = 2; if (m == 2)lineIndex1 = 0, lineIndex2 = 3; if (m == 3)lineIndex1 = 1, lineIndex2 = 2; if (m == 4)lineIndex1 = 1, lineIndex2 = 3; if (m == 5)lineIndex1 = 2, lineIndex2 = 3;
                                    glm::vec4 lineVertex4D1OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * l + lineIndex1] * b->scale4D);
                                    glm::vec4 lineVertex4D2OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * l + lineIndex2] * b->scale4D);
                                    depth = dot(faceVertex4D1Of1 - lineVertex4D1OfB, normal);
                                    if (depth > 0.f)
                                    {
                                        if (abs(dot(normal, normalize(lineVertex4D1OfB - lineVertex4D2OfB))) < 0.001f)
                                        {
                                            if (length(lineVertex4D1OfB - lineVertex4D2OfB) > 0.001f)
                                            {
                                                glm::vec4 normal2 = normalize(cross4d(lineVertex4D1OfB - lineVertex4D2OfB, faceVertex4D1Of1 - faceVertex4D2Of1, faceVertex4D1Of1 - faceVertex4D3Of1));
                                                if (dot(normal2, normal) < 0.f)
                                                {
                                                    normal2 = -normal2;
                                                }
                                                if (is_line_in_face(normal2, lineVertex4D1OfB, lineVertex4D2OfB, faceVertex4D1Of1, faceVertex4D2Of1, faceVertex4D3Of1, &contact))
                                                {
                                                    depth = dot(faceVertex4D1Of1 - lineVertex4D1OfB, normal2);
                                                    //if (depth < 0.1f)
                                                    {
                                                        contact = contact + 0.5f * depth * normal2;
                                                        massAdjustment += 1.f;
                                                        collisions.push_back(new Collision(index1, index2, 1.f, 1.f, normal2, depth, contact));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < b->primitive4D.get_size_of_vertices4D() / 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    unsigned faceIndex1, faceIndex2, faceIndex3;
                    if (j == 0)faceIndex1 = 0, faceIndex2 = 1, faceIndex3 = 2; if (j == 1)faceIndex1 = 0, faceIndex2 = 1, faceIndex3 = 3; if (j == 2)faceIndex1 = 0, faceIndex2 = 2, faceIndex3 = 3; if (j == 3)faceIndex1 = 1, faceIndex2 = 2, faceIndex3 = 3;
                    glm::vec4 faceVertex4D1OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + faceIndex1] * b->scale4D);
                    glm::vec4 faceVertex4D2OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + faceIndex2] * b->scale4D);
                    glm::vec4 faceVertex4D3OfB = body_pos_to_world(b, b->primitive4D.vertexData4D[4 * i + faceIndex3] * b->scale4D);
                    if (abs(dot(normal, normalize(faceVertex4D1OfB - faceVertex4D2OfB))) < 0.001f && abs(dot(normal, normalize(faceVertex4D1OfB - faceVertex4D3OfB))) < 0.001f)
                    {
                        if (length(faceVertex4D1OfB - faceVertex4D2OfB) > 0.001f && length(faceVertex4D1OfB - faceVertex4D3OfB) > 0.001f && length(faceVertex4D2OfB - faceVertex4D3OfB) > 0.001f)
                        {
                            for (int l = 0; l < a->primitive4D.get_size_of_vertices4D() / 4; l++)
                            {
                                for (int m = 0; m < 6; m++)
                                {
                                    unsigned lineIndex1, lineIndex2;
                                    if (m == 0)lineIndex1 = 0, lineIndex2 = 1; if (m == 1)lineIndex1 = 0, lineIndex2 = 2; if (m == 2)lineIndex1 = 0, lineIndex2 = 3; if (m == 3)lineIndex1 = 1, lineIndex2 = 2; if (m == 4)lineIndex1 = 1, lineIndex2 = 3; if (m == 5)lineIndex1 = 2, lineIndex2 = 3;
                                    glm::vec4 lineVertex4D1Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * l + lineIndex1] * a->scale4D);
                                    glm::vec4 lineVertex4D2Of1 = body_pos_to_world(a, a->primitive4D.vertexData4D[4 * l + lineIndex2] * a->scale4D);
                                    depth = dot(faceVertex4D1OfB - lineVertex4D1Of1, normal);
                                    if (depth > 0.f)
                                    {
                                        if (abs(dot(normal, normalize(lineVertex4D1Of1 - lineVertex4D2Of1))) < 0.001f)
                                        {
                                            if (length(lineVertex4D1Of1 - lineVertex4D2Of1) > 0.001f)
                                            {
                                                glm::vec4 normal2 = normalize(cross4d(lineVertex4D1Of1 - lineVertex4D2Of1, faceVertex4D1OfB - faceVertex4D2OfB, faceVertex4D1OfB - faceVertex4D3OfB));
                                                if (dot(normal2, normal) < 0.f)
                                                {
                                                    normal2 = -normal2;
                                                }
                                                if (is_line_in_face(normal2, lineVertex4D1Of1, lineVertex4D2Of1, faceVertex4D1OfB, faceVertex4D2OfB, faceVertex4D3OfB, &contact))
                                                {
                                                    depth = dot(faceVertex4D1OfB - lineVertex4D1Of1, normal2);
                                                    //if (depth < 0.1f)
                                                    {
                                                        contact = contact + 0.5f * depth * normal2;
                                                        massAdjustment += 1.f;
                                                        collisions.push_back(new Collision(index1, index2, 1.f, 1.f, normal2, depth, contact));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}
*/

static vector<Collision*> terrain_to_mesh(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radious = length(b->scale4D) / 2.f;
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            unsigned int size = 4;
            unsigned int cubeIndex;
            for (int i = 0; i < b->primitive4D.get_size_of_vertices4D(); i++)
            {
                glm::vec4 vertexOfB = body_pos_to_world(b, b->primitive4D.vertexData4D[i] * b->scale4D);
                for (size_t x = 0; x < size; x++)
                {
                    for (size_t z = 0; z < size; z++)
                    {
                        for (size_t w = 0; w < size; w++)
                        {
                            if (abs(b->position4D.x - a->position4D.x - x + 1.5f) < 0.5f + radious &&
                                abs(b->position4D.z - a->position4D.z - z + 1.5f) < 0.5f + radious &&
                                abs(b->position4D.w - a->position4D.w - w + 1.5f) < 0.5f + radious)
                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i = 0; i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
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
                                                massAdjustment += 1.f;
                                                collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> capsule_to_sphere(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float capsuleRadious = length(a->scale4D) / 2.f;
    float sphereRadious = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < capsuleRadious + sphereRadious &&
        abs(a->position4D.y - b->position4D.y) < capsuleRadious + sphereRadious &&
        abs(a->position4D.z - b->position4D.z) < capsuleRadious + sphereRadious &&
        abs(a->position4D.w - b->position4D.w) < capsuleRadious + sphereRadious)
    {
        float radiousA = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float lengthA = a->scale4D.z;
        float radiousB = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
        glm::vec4 pB = world_pos_to_body(a, b->position4D);
        glm::vec4 pA1 = glm::vec4(0.f, 0.f, lengthA / 2.f - radiousA, 0.f);
        if (length(pA1 - pB) < radiousA + radiousB && pB.z > pA1.z)
        {
            glm::vec4 normal;
            float depth;
            glm::vec4 contacts;
            normal = body_vec_to_world(a, normalize(pB - pA1));
            depth = radiousA + radiousB - length(pA1 - pB);
            contacts = body_pos_to_world(a, pA1+(radiousA - depth / 2.f) * normal);
            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contacts));
        }
        glm::vec4 pA2 = -glm::vec4(0.f, 0.f, lengthA / 2.f - radiousA, 0.f);
        if (length(pA2 - pB) < radiousA + radiousB && pB.z < pA2.z)
        {
            glm::vec4 normal;
            float depth;
            glm::vec4 contacts;
            normal = body_vec_to_world(a, normalize(pB - pA2));
            depth = radiousA + radiousB - length(pA2 - pB);
            contacts = body_pos_to_world(a, pA2+(radiousA - depth / 2.f) * normal);
            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contacts));
        }

        if (pB.z < pA1.z && pB.z > pA2.z && length(glm::vec4(pB.x, pB.y, 0.f, pB.w)) < radiousA + radiousB)
        {
            glm::vec4 normal;
            float depth;
            glm::vec4 contacts;
            normal = body_vec_to_world(a, normalize(glm::vec4(pB.x, pB.y, 0.f, pB.w)));
            depth = radiousA + radiousB - length(glm::vec4(pB.x, pB.y, 0.f, pB.w));
            contacts = body_pos_to_world(a, (radiousA - depth / 2.f) * normal);
            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contacts));
        }
    }
    return collisions;
}

static vector<Collision*> capsule_to_cube(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float capsuleRadious = a->scale4D.z / 2.f;
    float cubeRadious = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < capsuleRadious + cubeRadious &&
        abs(a->position4D.y - b->position4D.y) < capsuleRadious + cubeRadious &&
        abs(a->position4D.z - b->position4D.z) < capsuleRadious + cubeRadious &&
        abs(a->position4D.w - b->position4D.w) < capsuleRadious + cubeRadious)
    {
        glm::vec4 posAToB = world_pos_to_body(b,a->position4D);
        if (abs(posAToB.x) < b->scale4D.x / 2.f + capsuleRadious && 
            abs(posAToB.y) < b->scale4D.y / 2.f + capsuleRadious &&
            abs(posAToB.z) < b->scale4D.z / 2.f + capsuleRadious &&
            abs(posAToB.w) < b->scale4D.w / 2.f + capsuleRadious)
        {
            Simplex simplex = Simplex(glm::vec4(0.f));
            if (gjk(a, b, 12, &simplex))
            {
                float depth = 0.f;
                glm::vec4 contact = (a->position4D + b->position4D) / 2.f;
                std::vector<glm::vec4> supportPoints1;
                std::vector<glm::vec4> supportPoints2;
                glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1, &supportPoints2);
                if (depth > 0.f)
                {
                    if (b->colType == STEP4D && a->objectName == "Player")
                    {
                        if (normal.y < 0.f)
                        {
                            float height = support(b, -normal).y - support(a, normal).y + a->position4D.y - b->position4D.y;
                            if (height > 0.f)
                            {
                                a->set_position4D(glm::vec4(a->position4D.x, b->position4D.y + height, a->position4D.z, a->position4D.w));
                            }
                            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(glm::vec4(0, -1, 0, 0), isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                        }
                        else
                            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                    }
                    else
                    {
                        bool isMuti = false;
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
                                contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                            }
                            if (supportPoints2.size() == 8)
                            {
                                isMuti = true;
                                collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                                collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                            }
                        }
                        if (!isMuti)
                        {
                            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
                        }
                    }
                }
            }
        } 
    }
    return collisions;
}

static vector<Collision*> capsule_to_mesh(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float RadiousA = a->scale4D.z / 2.f;
    float RadiousB = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < RadiousA + RadiousB &&
        abs(a->position4D.y - b->position4D.y) < RadiousA + RadiousB &&
        abs(a->position4D.z - b->position4D.z) < RadiousA + RadiousB &&
        abs(a->position4D.w - b->position4D.w) < RadiousA + RadiousB)
    {
        Simplex simplex = Simplex(glm::vec4(0.f));
        if (gjk(a, b, 12, &simplex))
        {
            float depth = 0.f;
            glm::vec4 contact = (a->position4D + b->position4D) / 2.f;
            std::vector<glm::vec4> supportPoints1;
            std::vector<glm::vec4> supportPoints2;
            glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1, &supportPoints2);
            if (depth > 0.f)
            {
                bool isMuti = false;
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
                        contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                    if (supportPoints2.size() == 4)
                    {
                        contact = get_line_in_face_pos(-normal, supportPoints1[0], supportPoints1[1], supportPoints2[0], supportPoints2[1], supportPoints2[2]);
                    }
                    if (supportPoints2.size() > 4)
                    {
                        isMuti = true;
                        collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[0] - depth * normal / 2.f));
                        collisions.push_back(new Collision(index1, index2, 2.f, 2.f, inverse(normal, isInverse), depth, supportPoints1[1] - depth * normal / 2.f));
                    }
                }
                if(!isMuti)
                collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
            }
        }
    }
    return collisions;
}

static vector<Collision*> capsule_to_capsule(Object4D* a0, Object4D* b0, int index1, int index2, vector<Collision*> collisions, bool isInverse)
{
    Object4D* a;
    Object4D* b;
    std::tie(a, b) = inverse_object4D(a0, b0, isInverse);
    float RadiousA = a->scale4D.z / 2.f;
    float RadiousB = length(b->scale4D) / 2.f;
    if (abs(a->position4D.x - b->position4D.x) < RadiousA + RadiousB &&
        abs(a->position4D.y - b->position4D.y) < RadiousA + RadiousB &&
        abs(a->position4D.z - b->position4D.z) < RadiousA + RadiousB &&
        abs(a->position4D.w - b->position4D.w) < RadiousA + RadiousB)
    {
        Simplex simplex = Simplex(glm::vec4(0.f));
        if (gjk(a, b, 12, &simplex))
        {
            float depth = 0.f;
            glm::vec4 contact = (a->position4D + b->position4D) / 2.f;
            std::vector<glm::vec4> supportPoints1;
            std::vector<glm::vec4> supportPoints2;
            glm::vec4 normal = get_collision_information(a, b, 24, simplex, &depth, &supportPoints1, &supportPoints2);
            if (depth > 0.f)
            {
                if (supportPoints1.size() == 1)
                {
                    contact = supportPoints1[0] - depth * normal / 2.f;
                }
                if (supportPoints2.size() == 1)
                {
                    contact = supportPoints2[0] + depth * normal / 2.f;
                }
                if (supportPoints1.size() == 2 && supportPoints2.size() == 2)
                {
                    contact = (a->position4D + b->position4D) / 2.f;
                }
                collisions.push_back(new Collision(index1, index2, 1.f, 1.f, inverse(normal, isInverse), depth, contact));
            }
        }
    }
    return collisions;
}

static vector<Collision*> terrain_to_capsule(Object4D* a, Object4D* b, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    if (abs(a->position4D.x - b->position4D.x) < (a->scale4D.x + b->scale4D.x) / 2.f &&
        abs(a->position4D.z - b->position4D.z) < (a->scale4D.z + b->scale4D.z) / 2.f &&
        abs(a->position4D.w - b->position4D.w) < (a->scale4D.w + b->scale4D.w) / 2.f)
    {
        float radious = b->scale4D.z;
        if (b->position4D.y - support(a, glm::vec4(0, 1, 0, 0)).y < radious)
        {
            float radiousA = min(b->scale4D.w, min(b->scale4D.x, b->scale4D.y)) / 2.f;
            float lengthA = b->scale4D.z;
            glm::vec4 sphereCenter = body_pos_to_world(b,glm::vec4(0,0, lengthA/2.f - radiousA,0));
            for (int i = 0; i < 2; i++)
            {
                if (i == 1)
                {
                    sphereCenter = -sphereCenter;
                }
                int size = 4;
                unsigned int cubeIndex;
                glm::vec4 detectPos4D0;
                for (size_t x = 0; x < size; x++)
                {
                    for (size_t z = 0; z < size; z++)
                    {
                        for (size_t w = 0; w < size; w++)
                        {
                            if (abs(sphereCenter.x - a->position4D.x - x + 1.5f) < 0.5f + radiousA &&
                                abs(sphereCenter.z - a->position4D.z - z + 1.5f) < 0.5f + radiousA &&
                                abs(sphereCenter.w - a->position4D.w - w + 1.5f) < 0.5f + radiousA)

                            {
                                cubeIndex = 4 * 6 * (size * size * w + size * z + x);
                                for (size_t i = 0; i < 6; i++)
                                {
                                    glm::vec4 normal;
                                    float depth;
                                    glm::vec4 contacts;
                                    if (sphere_col_terrain_tetra4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.normalData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        //std::cout << "depth: "<< depth << "\n";
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_face4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_line4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }

                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }
                                    if (sphere_col_point4D(sphereCenter - a->position4D, radiousA,
                                        a->primitive4D.vertexData4D[cubeIndex + 4 * i + 3],
                                        &depth, &normal, &contacts))
                                    {
                                        massAdjustment += 1.f;
                                        collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts + a->position4D));
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < (int)massAdjustment; i++)
    {
        for (int j = i + 1; j < (int)massAdjustment; j++)
        {
            if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
            {
                collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                massAdjustment--;
                j--;
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> sphere_to_edge(Object4D* a, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    float height = 0.f;
    float radiousB = min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f;
    if (a->position4D.y< radiousB + height)
    {
        glm::vec4 normal = glm::vec4(0, 1, 0, 0);
        glm::vec4 contacts = glm::vec4(a->position4D.x, height, a->position4D.z, a->position4D.w);
        float depth = radiousB - a->position4D.y+height;
        massAdjustment += 1.f;
        collisions.push_back(new Collision(index1, index2,massAdjustment, massAdjustment, normal, depth, contacts));
    }
    return collisions;
}

static vector<Collision*> cube_to_edge(Object4D* a, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    float height = 0.f;
    float radiousB = length(a->scale4D) / 2.f;
    if (a->position4D.y< radiousB + height)
    {
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = body_pos_to_world(a, hypercube::vertices4D[i] * a->scale4D);
            if (vertexPos4D.y < height)
            {
                glm::vec4 normal = glm::vec4(0, 1, 0, 0);
                glm::vec4 contacts = glm::vec4(vertexPos4D.x,height, vertexPos4D.z, vertexPos4D.w);
                float depth = height- vertexPos4D.y;
                massAdjustment += 1.f;
                collisions.push_back(new Collision(index1, index2,massAdjustment, massAdjustment, normal, depth, contacts));
            }
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static vector<Collision*> mesh_to_edge(Object4D* a, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    float height = 0.f;
    float radiousB = length(a->scale4D) / 2.f;
    if (a->position4D.y < radiousB + height)
    {
        unsigned int count = 0;
        float depth0 = 0.f;
        float maxDepth = 0.f;
        glm::vec4 finalVertexPos4D;
        glm::vec4* vertexPos4D = new glm::vec4[a->primitive4D.get_size_of_vertices4D()];
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            vertexPos4D[i] = body_pos_to_world(a, a->primitive4D.vertexData4D[i] * a->scale4D);
            depth0 = height - vertexPos4D[i].y;
            if (depth0 > 0.f)
            {
                if (maxDepth < depth0)
                {
                    maxDepth = depth0;
                    finalVertexPos4D = vertexPos4D[i];
                    count++;
                }
            }
        }
        if (count > 12)
        {
            glm::vec4 normal = glm::vec4(0, 1, 0, 0);
            glm::vec4 contacts = glm::vec4(finalVertexPos4D.x, height, finalVertexPos4D.z, finalVertexPos4D.w);
            float depth = maxDepth;
            collisions.push_back(new Collision(index1, index2, 1.f, 1.f, normal, depth, contacts));
        }
        else
        {
            glm::vec4 normal;
            glm::vec4 contacts;
            float depth;
            for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
            {
                if (vertexPos4D[i].y < height)
                {
                    normal = glm::vec4(0, 1, 0, 0);
                    contacts = glm::vec4(vertexPos4D[i].x, height, vertexPos4D[i].z, vertexPos4D[i].w);
                    depth = height - vertexPos4D[i].y;
                    massAdjustment += 1.f;
                    collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts));
                }
            }
        }

        for (int i = 0; i < (int)massAdjustment; i++)
        {
            for (int j = i + 1; j < (int)massAdjustment; j++)
            {
                if (collisions[collisions.size() - (int)massAdjustment + i]->collisionManifold.contacts ==
                    collisions[collisions.size() - (int)massAdjustment + j]->collisionManifold.contacts)
                {
                    collisions.erase(collisions.begin() + collisions.size() - (int)massAdjustment + j);
                    massAdjustment--;
                    j--;
                }
            }
        }
        for (int i = 0; i < (int)massAdjustment; i++)
        {
            collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
            collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
        }
    }
    return collisions;
}

static vector<Collision*> capsule_to_edge(Object4D* a, int index1, int index2, vector<Collision*> collisions)
{
    float massAdjustment = 0.f;
    {
        float height = 0.f;
        float radious = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float length = a->scale4D.z;
        glm::vec4 position4D = a->position4D + body_vec_to_world(a, glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f));
        if (position4D.y < radious + height)
        {
            glm::vec4 normal = glm::vec4(0, 1, 0, 0);
            glm::vec4 contacts = glm::vec4(position4D.x, height, position4D.z, position4D.w);
            float depth = radious - position4D.y + height;
            massAdjustment += 1.f;
            collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts));
        }
    }
    {
        float height = 0.f;
        float radious = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float length = a->scale4D.z;
        glm::vec4 position4D = a->position4D - body_vec_to_world(a, glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f));
        if (position4D.y < radious + height)
        {
            glm::vec4 normal = glm::vec4(0, 1, 0, 0);
            glm::vec4 contacts = glm::vec4(position4D.x, height, position4D.z, position4D.w);
            float depth = radious - position4D.y + height;
            massAdjustment += 1.f;
            collisions.push_back(new Collision(index1, index2, massAdjustment, massAdjustment, normal, depth, contacts));
        }
    }
    for (int i = 0; i < (int)massAdjustment; i++)
    {
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentA = massAdjustment;
        collisions[collisions.size() - (int)massAdjustment + i]->massAdjustmentB = massAdjustment;
    }
    return collisions;
}

static void sphere_to_water(Object4D* a,
    RigidBody4D* b, const float dt)
{
    float radious = min(b->scale4D.w, min(b->scale4D.z, min(b->scale4D.x, b->scale4D.y))) / 2.f;
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x / 2.f + radious &&
        abs(b->position4D.y - a->position4D.y + a->scale4D.y / 4.f) < a->scale4D.y / 4.f + radious &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + radious &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + radious)
    {
        float depth = a->position4D.y - b->position4D.y;
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
    float cubeRadious = sqrt(b->scale4D.x * b->scale4D.x + b->scale4D.y * b->scale4D.y + b->scale4D.z * b->scale4D.z + b->scale4D.w * b->scale4D.w) / 2.f;
    if (abs(b->position4D.x - a->position4D.x) < a->scale4D.x/2.f + cubeRadious &&
        abs(b->position4D.y - a->position4D.y+ a->scale4D.y / 4.f) < a->scale4D.y / 4.f + cubeRadious &&
        abs(b->position4D.z - a->position4D.z) < a->scale4D.z / 2.f + cubeRadious &&
        abs(b->position4D.w - a->position4D.w) < a->scale4D.w / 2.f + cubeRadious)
    {
        float depth = a->position4D.y - b->position4D.y;
        if (depth > -cubeRadious)
        {
            glm::vec4 force;
            for (int i = 0; i < 16; i++)
            {
                glm::vec4 pos = body_pos_to_world(a, hypercube::vertices4D[i] * b->scale4D);
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
            // std::cout << "float!" << force.y << "\n";

        }
    }
}
