#pragma once
#include<vec4.hpp>
#include<vector>
#include<mat2x2.hpp>
static void sort(unsigned int i1, unsigned int i2, unsigned int i3, unsigned int* a1, unsigned int* a2, unsigned int* a3)
{
    if (i1 < i2)
    {
        if (i2 < i3)
        {
            *a1 = i1, * a2 = i2, * a3 = i3;
        }
        else
        {
            if (i1 > i3)
            {
                *a1 = i3, * a2 = i1, * a3 = i2;
            }
            else
            {
                *a1 = i1, * a2 = i3, * a3 = i2;
            }
        }
    }
    else
    {
        if (i2 > i3)
        {
            *a1 = i3, * a2 = i2, * a3 = i1;
        }
        else
        {
            if (i1 < i3)
            {
                *a1 = i2, * a2 = i1, * a3 = i3;
            }
            else
            {
                *a1 = i2, * a2 = i3, * a3 = i1;
            }
        }
    }
}

static void sort(int i1, int i2, int i3, int i4, int* a1, int* a2, int* a3, int* a4)
{
    int ia1, ia2, ia3, ia4;
    ia4 = i4;
    if (i1 < i2)
    {
        if (i2 < i3)
        {
            ia1 = i1, ia2 = i2, ia3 = i3;
        }
        else
        {
            if (i1 > i3)
            {
                ia1 = i3, ia2 = i1, ia3 = i2;
            }
            else
            {
                ia1 = i1, ia2 = i3, ia3 = i2;
            }
        }
    }
    else
    {
        if (i2 > i3)
        {
            ia1 = i3, ia2 = i2, ia3 = i1;
        }
        else
        {
            if (i1 < i3)
            {
                ia1 = i2, ia2 = i1, ia3 = i3;
            }
            else
            {
                ia1 = i2, ia2 = i3, ia3 = i1;
            }
        }
    }
    if (i4 < ia1)
    {
        *a1 = ia4, * a2 = ia1, * a3 = ia2, * a4 = ia3;
    }
    else
    {
        if (i4 < ia2)
        {
            *a1 = ia1, * a2 = ia4, * a3 = ia2, * a4 = ia3;
        }
        else
        {
            if (i4 < ia3)
            {
                *a1 = ia1, * a2 = ia2, * a3 = ia4, * a4 = ia3;
            }
            else
            {
                *a1 = ia1, * a2 = ia2, * a3 = ia3, * a4 = ia4;
            }
        }
    }
}

static glm::vec4 support(Object4D* a,glm::vec4 direction4D)
{
    switch (a->colType)
    {
    case SPHERE4D:
    {
        float radious = min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f;
        return a->position4D + radious * normalize(direction4D);
        break;
    }
    case BOX4D:
    {
        glm::vec4 direction4DToObj = world_vec_to_body(a, direction4D);
        glm::vec4 supportPosition4d;
        float dot0=-0.00001f;
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return body_pos_to_world(a, supportPosition4d);
        break;
    }
    case STEP4D:
    {
        glm::vec4 direction4DToObj = world_vec_to_body(a, direction4D);
        glm::vec4 supportPosition4d;
        float dot0 = -0.00001f;
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return body_pos_to_world(a, supportPosition4d);
        break;
    }
    case MESH4D:
    {
        glm::vec4 direction4DToObj = world_vec_to_body(a, direction4D);
        glm::vec4 supportPosition4d;
        float dot0 = -0.00001f;
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D = a->primitive4D.vertexData4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return body_pos_to_world(a, supportPosition4d);
        break;
    }
    case CAPSULE4D:
    {
        glm::vec4 direction4DToObj = world_vec_to_body(a, direction4D);
        float radious = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float length = a->scale4D.z;
        if (direction4DToObj.z > 0.f)
        {
            return body_pos_to_world(a,glm::vec4(0.f,0.f, length/2.f-radious,0.f)) + radious * normalize(direction4D);
        }
        else if (direction4DToObj.z < 0.f)
        {
            return body_pos_to_world(a, -glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f)) + radious * normalize(direction4D);
        }
        else
        {
            return body_pos_to_world(a, radious*normalize(glm::vec4(direction4DToObj.x, direction4DToObj.y,0.f, direction4DToObj.w)));
        }
        break;
    }
    case TERRAIN4D:
    {
        glm::vec4 direction4DToObj = direction4D;
        glm::vec4 supportPosition4d;
        float dot0 = -0.00001f;
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D = a->primitive4D.vertexData4D[i];
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return a->position4D + supportPosition4d;
        break;
    }
    default:
        break;
    }
}

static glm::vec4 support_of_cso(Object4D* a, Object4D* b, glm::vec4 direction4D)
{
    return support(a, direction4D) - support(b, -direction4D);
}

static std::vector<glm::vec4> support_points(Object4D* a, glm::vec4 direction4D)
{
    std::vector<glm::vec4> supportPoints4D;
    glm::vec4 direction4DToObj = world_vec_to_body(a, direction4D);
    switch (a->colType)
    {
    case BOX4D:
    {
        float dot0 = -0.00001f;
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                dot0 = dot1;
            }
        }
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float supportDistance2 = dot(direction4DToObj, vertexPos4D);
            if (dot0 - supportDistance2 < 0.0001f)
            {
                supportPoints4D.push_back(body_pos_to_world(a, vertexPos4D));
            }
        }
        break;
    }
    case STEP4D:
    {
        float dot0 = -0.00001f;
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                dot0 = dot1;
            }
        }
        for (int i = 0; i < 16; i++)
        {
            glm::vec4 vertexPos4D = hypercube::vertices4D[i] * a->scale4D;
            float supportDistance2 = dot(direction4DToObj, vertexPos4D);
            if (dot0 - supportDistance2 < 0.0001f)
            {
                supportPoints4D.push_back(body_pos_to_world(a, vertexPos4D));
            }
        }
        break;
    }
    case MESH4D:
    {
        float dot0 = -0.00001f;
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D = a->primitive4D.vertexData4D[i] * a->scale4D;
            float dot1 = dot(direction4DToObj, vertexPos4D);
            if (dot1 > dot0)
            {
                dot0 = dot1;
            }
        }
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D(); i++)
        {
            glm::vec4 vertexPos4D = a->primitive4D.vertexData4D[i] * a->scale4D;
            float supportDistance2 = dot(direction4DToObj, vertexPos4D);
            if (dot0 - supportDistance2 < 0.0001f)
            {
                supportPoints4D.push_back(body_pos_to_world(a, vertexPos4D));
            }
        }
        for (int i = 0; i < supportPoints4D.size(); i++)
        {
            for (int j = i+1; j < supportPoints4D.size(); j++)
            {
                if (length(supportPoints4D[i] - supportPoints4D[j]) < 0.0001f)
                {
                    supportPoints4D.erase(supportPoints4D.begin()+j);
                    j--;
                }
            }
        }
        break;
    }
    case CAPSULE4D:
    {
        float radious = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float length = a->scale4D.z;
        if (direction4DToObj.z > 0.0001f)
        {
            supportPoints4D.push_back(body_pos_to_world(a, glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f)) + radious * normalize(direction4D));
        }
        else if (direction4DToObj.z < -0.0001f)
        {
            supportPoints4D.push_back(body_pos_to_world(a, -glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f)) + radious * normalize(direction4D));
        }
        else
        {
            supportPoints4D.push_back(body_pos_to_world(a, radious * normalize(glm::vec4(direction4DToObj.x, direction4DToObj.y, 0.f, direction4DToObj.w))+glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f)));
            supportPoints4D.push_back(body_pos_to_world(a, radious * normalize(glm::vec4(direction4DToObj.x, direction4DToObj.y, 0.f, direction4DToObj.w))-glm::vec4(0.f, 0.f, length / 2.f - radious, 0.f)));
        }
        break;
    }
    default:
        break;
    }
    return supportPoints4D;
}

static bool is_point_in_collider(Object4D* a, glm::vec4 position4D)
{
    switch (a->colType)
    {
    case SPHERE4D:
    {
        float radious = min(a->scale4D.w, min(a->scale4D.z, min(a->scale4D.x, a->scale4D.y))) / 2.f;
        return length(a->position4D - position4D) < radious;
        break;
    }
    case BOX4D:
    {
        glm::vec4 position4DToBody = world_pos_to_body(a, position4D);
        return abs(position4DToBody.x) < a->scale4D.x / 2.f&& abs(position4DToBody.y) < a->scale4D.y / 2.f&& abs(position4DToBody.z) < a->scale4D.z / 2.f&& abs(position4DToBody.w) < a->scale4D.w / 2.f;
        break;
    }
    case STEP4D:
    {
        glm::vec4 position4DToBody = world_pos_to_body(a, position4D);
        return abs(position4DToBody.x) < a->scale4D.x / 2.f && abs(position4DToBody.y) < a->scale4D.y / 2.f && abs(position4DToBody.z) < a->scale4D.z / 2.f && abs(position4DToBody.w) < a->scale4D.w / 2.f;
        break;
    }
    case MESH4D:
    {
        bool isInside = true;
        glm::vec4 position4DToBody = world_pos_to_body(a, position4D) / a->scale4D;
        for (int i = 0; i < a->primitive4D.get_size_of_vertices4D() / 4; i++)
        {
            glm::vec4 tetraNormal4DOfA = a->primitive4D.normalData4D[4 * i];
            glm::vec4 vertex4D1OfA = a->primitive4D.vertexData4D[4 * i];
            glm::vec4 vertex4D2OfA = a->primitive4D.vertexData4D[4 * i];
            glm::vec4 vertex4D3OfA = a->primitive4D.vertexData4D[4 * i];
            glm::vec4 vertex4D4OfA = a->primitive4D.vertexData4D[4 * i];
            if (length(vertex4D1OfA - vertex4D2OfA) > 0.001f && length(vertex4D1OfA - vertex4D3OfA) > 0.001f &&
                length(vertex4D1OfA - vertex4D4OfA) > 0.001f && length(vertex4D2OfA - vertex4D3OfA) > 0.001f &&
                length(vertex4D2OfA - vertex4D4OfA) > 0.001f && length(vertex4D3OfA - vertex4D4OfA) > 0.001f)
            {
                if (dot(tetraNormal4DOfA, position4DToBody - vertex4D1OfA) > 0.f)
                {
                    isInside = false;
                }
            }
        }
        return isInside;
        break;
    }
    case CAPSULE4D:
    {
        bool isInside = false;
        glm::vec4 position4DToBody = world_pos_to_body(a, position4D);
        float radiousOfCapsule4D = min(a->scale4D.w, min(a->scale4D.x, a->scale4D.y)) / 2.f;
        float lengthOfCapsule4D = a->scale4D.z;
        if (length(glm::vec3(position4DToBody.x, position4DToBody.y, position4DToBody.w)) < radiousOfCapsule4D)
        {
            if (abs(position4DToBody.z) < lengthOfCapsule4D / 2.f - radiousOfCapsule4D)
            {
                isInside = true;
            }
            else
            {
                if (length(a->position4D + glm::vec4(0.f, 0.f, lengthOfCapsule4D / 2.f - radiousOfCapsule4D, 0.f) - position4DToBody) < radiousOfCapsule4D)
                {
                    isInside = true;
                }
                if (length(a->position4D - glm::vec4(0.f, 0.f, lengthOfCapsule4D / 2.f - radiousOfCapsule4D, 0.f) - position4DToBody) < radiousOfCapsule4D)
                {
                    isInside = true;
                }
            }
        }
        return isInside;
        break;
    }
    default:
    {
        return false;
        break;
    }
    }
}

static struct Simplex
{
    glm::vec4 vertices4D[5];
    size_t length0;
    explicit Simplex(glm::vec4 initialPoint4D)
    {
        for (int i = 0; i < 5; i++)
        {
            this->vertices4D[i] = initialPoint4D;
        }
        this->length0 = 1;
    }
    void push(glm::vec4 vertice4D)
    {
        if (this->length0 >= 5)
        {
            std::cout << "Simplex is already full!" << "\n";
        }
        else {
            this->vertices4D[this->length0] = vertice4D;
            this->length0 += 1;
        }
    }
    void remove(size_t index)
    {
        if (index >= this->length0){
            std::cout << "Invalid simplex index provided to remove_at" << "\n";
        }
        else if (this->length0 == 1) {
            std::cout << "Simplex cannot have no points!" << "\n";
        }
        else
        {
            for (int i = index + 1; i < this->length0; i++) {
                this->vertices4D[i - 1] = this->vertices4D[i];
            }
            this->length0 -= 1;
        }
    }

    // If self contains the origin, returns None. Otherwise, updates self to be
   // the closest simplex on self to the origin, and returns the closest point
   // on the updated simplex to the origin.
    glm::vec4 nearest_simplex()
    {
        switch (this->length0)
        {
        case 1:
        {
            // single point case, just return it
            glm::vec4 a = this->vertices4D[0];
            return a;
            break;
        }
        case 2:
        {
            // line case, return a direction perpendicular
            glm::vec4 a = this->vertices4D[0];
            glm::vec4 b = this->vertices4D[1];
            glm::vec4 ab = normalize(b - a);
            float lambda = dot(-a, ab);
            // lambda is now such that a + lambda * (b - a) is the point on
            // the defined by a and b closest to the origin.
            return a + lambda * ab;
            break;
        }
        case 3:
        {
            // triangle case, return the closest point on the triangle
            glm::vec4 a = this->vertices4D[0];
            glm::vec4 b = this->vertices4D[1];
            glm::vec4 c = this->vertices4D[2];
            // Equation of two variables, we're just going to use cgmath to
            // solve it
            glm::vec4 veAB = normalize(b - a);
            glm::vec4 vAC = c - a;
            glm::vec4 neAB = normalize(vAC - veAB * dot(vAC, veAB));
            glm::vec4 v1s = - a;
            float kv = dot(v1s, veAB);
            float kn = dot(v1s, neAB);
            glm::vec4 closetPosToO = a + kv * veAB + kn * neAB;

            return closetPosToO;
            break;
        }
        case 4:
        {
            // tetrahedron case, return a direction perpendicular
            glm::vec4 a = this->vertices4D[0];
            glm::vec4 b = this->vertices4D[1];
            glm::vec4 c = this->vertices4D[2];
            glm::vec4 d = this->vertices4D[3];
            glm::vec4 ab = b - a;
            glm::vec4 ac = c - a;
            glm::vec4 ad = d - a;

            // We can use the triple cross product to just grab a normal to
            // the tetrahedron
            glm::vec4 n = cross4d(ab, ac, ad);
            float k = dot(a, n);

            return k * n;
            break;
        }
        case 5:
        {
            // Now we have a full 5-cell as our simplex. To check if the
            // origin is inside our simplex now, we simply need to perform
            // 5 halfspace tests.

            // We can actually skip one of the halfspace tests - because we
            // know that on the last iteration the direction was set to the
            // normal of the tetrahedron abcd, the origin must be in the
            // halfspace defined by the tetrahedron abcd.
            unsigned int i2 = -1;
            glm::vec4 direction4D2 = glm::vec4(100000.f);
            float aoDist2 = 0.f;
            for (int i = 0; i < 4; i++) {
                // tetrahedron is the 5 vertices without the ith vertex
                int j = 0;
                glm::vec4 tetrahedron[4] = { glm::vec4(0.f),glm::vec4(0.f), glm::vec4(0.f), glm::vec4(0.f) };
                for (int k = 0; k < 5; k++) {
                    if (k != i) {
                        tetrahedron[j] = this->vertices4D[k];
                        j += 1;
                    }
                }

                glm::vec4 a = tetrahedron[0];
                glm::vec4 b = tetrahedron[1];
                glm::vec4 c = tetrahedron[2];
                glm::vec4 d = tetrahedron[3];
                // e is the last vertex not in the tetrahedron
                glm::vec4 e = this->vertices4D[i];

                glm::vec4 ab = b - a;
                glm::vec4 ac = c - a;
                glm::vec4 ad = d - a;
                glm::vec4 normal = normalize(cross4d(ab, ac, ad));
                //std::cout << "length of simplex normal!"<< length(normal) << "\n";
                // the origin has to be on the same side as e to pass the
                // halfspace test!
                float aoDist = dot(-a, normal);
                if (aoDist * dot(e - a, normal) < 0.00000008f) {
                    // failed the halfspace test, so we know e is on the
                    // opposite side of the tetrahedron to the origin.
                    // We can then remove e from the simplex and set
                    // direction to the normal pointing towards the origin.
                    float k = -aoDist;
                    glm::vec4 dir = k * normal;
                    if (i2 == -1||aoDist2 > abs(aoDist))
                    { 
                        direction4D2 = dir;
                        aoDist2 = abs(aoDist);
                        i2 = i;
                    } 
                }
            }
            if (i2 != -1)
            {
                this->remove(i2);
                return direction4D2;
            }
            else
            {
                return glm::vec4(100000.f);
            }
            // If we reach here we've passed all the halfspace tests, so
            // the tetrahedron does indeed contain the origin!
            break;
        }
        default:
        {
            std::cout << "invalid simplex!" << "\n";
            break;
        }
        }
    }
};

static glm::vec4 get_initial_direction4D(glm::vec4 dirction4D)
{
    if (abs(dirction4D.x * dirction4D.y * dirction4D.z * dirction4D.w) < 0.00001f)
    {
        return dirction4D + glm::vec4(0.00001f, 0.00002f, 0.00003f, 0.00004f);
    }
    else
    {
        return dirction4D;
    }
}

static bool gjk(Object4D* s1, Object4D* s2,unsigned steps, Simplex* simplex)
{
    glm::vec4 a = support_of_cso(s1, s2, get_initial_direction4D(s1->position4D-s2->position4D));
    *simplex = Simplex(a);
    glm::vec4 d = -a;
    unsigned int count = 0;
    while(true)
    {
        a = support_of_cso(s1, s2, d);

        if (dot(a, d) < 0.00000008f)
        {
            return false;
            break;
        }

        simplex->push(a);
        glm::vec4 dir = simplex->nearest_simplex();
        if (dir != glm::vec4(100000.f))
        {
            d = -dir;
        }
        else
        {
            return true;
            break;
        }

        count++;
        if (count > steps)
        {
            return false;
            break;
        }
    }
}

struct EPTetra
{
    glm::ivec4 tetra4DIndexs;
    glm::vec4 normal4D;
    float distance;
};

struct ExpandingPolytope2
{
    std::vector<EPTetra> ePTetras;
    std::vector<glm::vec4> vertices4D;
    void from_simplex(Simplex simplex)
    {
        if (simplex.length0 == 5)
        {
            for (int i = 0; i < 5; i++)
            {
                this->vertices4D.push_back(simplex.vertices4D[i]);
            }
        }
        else
        {
            throw("simplex is not full!");
        }
        this->ePTetras.resize(5);
        for (int i = 0; i < 5; i++)
        {
            unsigned count = 0;
            for (int k = 0; k < 5; k++)
            {
                if (i != k)
                {
                    this->ePTetras[i].tetra4DIndexs[count] = k;
                    count++;
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            glm::vec4 normal4D = normalize(cross4d(this->vertices4D[this->ePTetras[i].tetra4DIndexs[3]] - this->vertices4D[this->ePTetras[i].tetra4DIndexs[0]],this->vertices4D[this->ePTetras[i].tetra4DIndexs[2]] - this->vertices4D[this->ePTetras[i].tetra4DIndexs[0]],this->vertices4D[this->ePTetras[i].tetra4DIndexs[1]] - this->vertices4D[this->ePTetras[i].tetra4DIndexs[0]]));
            float distance = dot(normal4D, this->vertices4D[this->ePTetras[i].tetra4DIndexs[0]]);
            if (distance > 0.f)
            {
                this->ePTetras[i].normal4D = normal4D;
                this->ePTetras[i].distance = distance;
            }
            else
            {
                this->ePTetras[i].normal4D = -normal4D;
                this->ePTetras[i].distance = -distance;
            }
        }
    }
    //for (int i = 0; i < this->vertices4D.size(); i++)
    //{
    //    if (this->vertices4D[i] == newPoint4D)
    //    {
    //        //isRemove = true;
    //        //if(count==0)
    //        std::cout << "error" << "\n";
    //        newVertexIndex = i;
    //    }
    //}
    
        //for (int i = 0; i < this->ePTetras.size(); i++)
    //{
    //    for (int j = 0; j < newTetrasIndexs.size(); j++)
    //    {
    //        if (this->ePTetras[i].tetra4DIndexs == newTetrasIndexs[j])
    //        {
    //            this->ePTetras.erase(this->ePTetras.begin() + i);
    //            i--;
    //            newTetrasIndexs.erase(newTetrasIndexs.begin() + j);
    //            j--;
    //        }
    //    }
    //}
    void expand(glm::vec4 newPoint4D)
    {
        //bool isRemove = false;
        //for (int i = 0; i < this->vertices4D.size(); i++)
        //{
        //    if (this->vertices4D[i] == newPoint4D)
        //    {
        //        //std::cout << "error" << "\n";
        //        isRemove = true;
        //    }
        //}
        //if (!isRemove)
        //{
        std::vector<glm::ivec4> newTetrasIndexs;
        glm::vec4 normal4D;
        float distance;
        this->vertices4D.push_back(newPoint4D);
        unsigned newVertexIndex = this->vertices4D.size() - 1;

        for (int i = 0; i < this->ePTetras.size(); i++)
        {
            if (dot(this->ePTetras[i].normal4D, this->vertices4D[newVertexIndex] - this->vertices4D[this->ePTetras[i].tetra4DIndexs[0]]) > 0.f)
            {
                newTetrasIndexs.push_back(glm::ivec4(ePTetras[i].tetra4DIndexs[0], ePTetras[i].tetra4DIndexs[1], ePTetras[i].tetra4DIndexs[2], newVertexIndex));
                newTetrasIndexs.push_back(glm::ivec4(ePTetras[i].tetra4DIndexs[0], ePTetras[i].tetra4DIndexs[1], ePTetras[i].tetra4DIndexs[3], newVertexIndex));
                newTetrasIndexs.push_back(glm::ivec4(ePTetras[i].tetra4DIndexs[0], ePTetras[i].tetra4DIndexs[2], ePTetras[i].tetra4DIndexs[3], newVertexIndex));
                newTetrasIndexs.push_back(glm::ivec4(ePTetras[i].tetra4DIndexs[1], ePTetras[i].tetra4DIndexs[2], ePTetras[i].tetra4DIndexs[3], newVertexIndex));
                this->ePTetras.erase(this->ePTetras.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < newTetrasIndexs.size(); i++)
        {
            sort(newTetrasIndexs[i][0], newTetrasIndexs[i][1], newTetrasIndexs[i][2], newTetrasIndexs[i][3], &newTetrasIndexs[i][0], &newTetrasIndexs[i][1], &newTetrasIndexs[i][2], &newTetrasIndexs[i][3]);
        }

        for (int i = 0; i < newTetrasIndexs.size(); i++)
        {
            for (int j = i + 1; j < newTetrasIndexs.size(); j++)
            {
                if (newTetrasIndexs[i] == newTetrasIndexs[j])
                {
                    newTetrasIndexs.erase(newTetrasIndexs.begin() + j);
                    j--;
                    newTetrasIndexs.erase(newTetrasIndexs.begin() + i);
                    i--;
                    j--;
                }
            }
        }

        for (int i = 0; i < newTetrasIndexs.size(); i++)
        {
            normal4D = normalize(cross4d(this->vertices4D[newTetrasIndexs[i][3]] - this->vertices4D[newTetrasIndexs[i][0]], this->vertices4D[newTetrasIndexs[i][2]] - this->vertices4D[newTetrasIndexs[i][0]], this->vertices4D[newTetrasIndexs[i][1]] - this->vertices4D[newTetrasIndexs[i][0]]));
            distance = dot(normal4D, this->vertices4D[newTetrasIndexs[i][0]]);
            if (distance > 0.f)
            {
                this->ePTetras.push_back(EPTetra(newTetrasIndexs[i], normal4D, distance));
            }
            else
            {
                this->ePTetras.push_back(EPTetra(newTetrasIndexs[i], -normal4D, -distance));
            }
        }
        //}
    }
};

static glm::vec4 epa2(Object4D* s1, Object4D* s2, unsigned steps, Simplex simplex, float* depth, std::vector<glm::vec4>* supportPoints1, std::vector<glm::vec4>* supportPoints2)
{
    unsigned int count = 0;
    ExpandingPolytope2 polytope;
    polytope.from_simplex(simplex);
    float distance = 0.f;
    float depth0 = 0.000001f;
    glm::vec4 normal;
    unsigned i;
    unsigned i2;
    glm::vec4 expandPoint;
    while (true)
    {
        for (i = 0; i < polytope.ePTetras.size(); i++)
        {
            if (i == 0 || distance > polytope.ePTetras[i].distance)
            {
                distance = polytope.ePTetras[i].distance;
                i2 = i;
            }
        }
        normal = polytope.ePTetras[i2].normal4D;
        expandPoint = support_of_cso(s1, s2, normal);
        if (dot(expandPoint, normal) - distance < 0.00001f)
        {
            break;
        }
        //std::cout << 100000.f*(dot(expandPoint, normal) - distance) << "\n";
        if (count > steps)
        {
            depth0 = -1.f;
            break;
        }
        polytope.expand(expandPoint);
        count++;
    }
    if (depth0 > 0.f)
    {
        *depth = distance;
        *supportPoints1 = support_points(s1, normal);
        *supportPoints2 = support_points(s2, -normal);
        return normal;
    }
    else
    {
        //std::cout << s1->objectName << "collide" << s2->objectName << "\n";
        *depth = -0.005f;
        return glm::vec4(0,-1,0,0);
    }
}

struct EPCell
{
    unsigned int faces[4][3];
    glm::vec4 normal;
    float distance;
    void from_faces(std::vector<glm::vec4> vertices4D, unsigned int faces[4][3])
    {
        unsigned int uniqueVertices[4] = { 0,0,0,0 };
        unsigned int uniqueVerticesCount = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                bool isContains=false;
                for (int k = 0; k < uniqueVerticesCount+1; k++)
                {
                    if (uniqueVertices[k] == faces[i][j])
                    {
                        isContains = true;
                    }
                }
                if (!isContains)
                {
                    uniqueVertices[uniqueVerticesCount] = faces[i][j];
                    uniqueVerticesCount += 1;
                    if (uniqueVerticesCount >= 4) {
                        break;
                        i = 4;
                    }
                }
            }
        }
        glm::vec4 a = vertices4D[uniqueVertices[0]];
        glm::vec4 b = vertices4D[uniqueVertices[1]];
        glm::vec4 c = vertices4D[uniqueVertices[2]];
        glm::vec4 d = vertices4D[uniqueVertices[3]];
        
        glm::vec4 normal = normalize(cross4d(b - a, c - a, d - a));
        float distance = dot(normal, a);
        if (distance < 0.f) {
            normal = -normal;
            distance = -distance;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->faces[i][j] = faces[i][j];
            }
        }
        this->normal = normal;
        this->distance = distance;
    }
};
struct ExpandingPolytope
{
    std::vector<glm::vec4> vertices4D;
    std::vector <EPCell> cells;
    void from_simplex(Simplex simplex)
    {
        if (simplex.length0 == 5)
        {
            std::vector<glm::vec4> vertices;
            for (int i = 0; i < 5; i++)
            {
                vertices.push_back(simplex.vertices4D[i]);
            }
            unsigned int faces[10][3];
            unsigned int count = 0;
            for (int i = 0; i < 5; i++)
            {
                for (int j = i + 1; j < 5; j++)
                {
                    for (int k = j + 1; k < 5; k++)
                    {
                        faces[count][0] = i;
                        faces[count][1] = j;
                        faces[count][2] = k;
                        count++;
                    }
                }
            }
            std::vector <EPCell> cells;
            for (int i = 0; i < 5; i++)
            {
                unsigned int cellFaces[4][3] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
                unsigned int cellFaceCount = 0;
                for (int j = 0; j < 10; j++)
                {
                    if (faces[j][0] != i && faces[j][1] != i && faces[j][2] != i) {
                        cellFaces[cellFaceCount][0] = faces[j][0];
                        cellFaces[cellFaceCount][1] = faces[j][1];
                        cellFaces[cellFaceCount][2] = faces[j][2];
                        cellFaceCount += 1;
            
                        if (cellFaceCount >= 4) {
                            break;
                        }
                    }
                }
                EPCell cell;
                cell.from_faces(vertices, cellFaces);
                cells.push_back(cell);
            }
            this->vertices4D = vertices;
            this->cells = cells;
        }
        else
        {
            std::cout << "simplex is not full" << "\n";
        }
    }

    void expand(glm::vec4 extendPoint)
    {
        std::vector<glm::ivec3> removedFaces;
        for (int i=0;i< this->cells.size();i++)
        {
            glm::vec4 v0 = this->vertices4D[this->cells[i].faces[0][0]];
            if (dot(this->cells[i].normal, extendPoint - v0) > 0.001f)
            {
                // Before returning, we need to add all the faces to the removed
                // faces
                for (int j = 0; j < 4; j++) 
                { 
                    bool isMatch = false;
                    for (int k = 0; k < removedFaces.size(); k++)
                    {
                        if (removedFaces[k][0] == this->cells[i].faces[j][0] &&
                            removedFaces[k][1] == this->cells[i].faces[j][1] &&
                            removedFaces[k][2] == this->cells[i].faces[j][2])
                        {
                            removedFaces.erase(removedFaces.begin() + k);
                            k--;
                            isMatch = true;
                        }
                    }
                    if(!isMatch)
                    {
                        removedFaces.push_back(glm::ivec3(this->cells[i].faces[j][0], this->cells[i].faces[j][1], this->cells[i].faces[j][2]));
                    }
                }
                this->cells.erase(this->cells.begin()+i);
                i--;
            }
        }


        // push the new vertex
        unsigned vertexIdx = this->vertices4D.size();
        this->vertices4D.push_back(extendPoint);
        // now add a new cell for each face
        for (int i=0;i< removedFaces.size();i++)
        {
            unsigned int cellFaces[4][3];
            cellFaces[0][0] = removedFaces[i][0], cellFaces[0][1] = removedFaces[i][1], cellFaces[0][2]= vertexIdx,
            cellFaces[1][0] = removedFaces[i][0], cellFaces[1][1] = removedFaces[i][2], cellFaces[1][2] = vertexIdx,
            cellFaces[2][0] = removedFaces[i][1], cellFaces[2][1] = removedFaces[i][2], cellFaces[2][2] = vertexIdx,
            cellFaces[3][0] = removedFaces[i][0], cellFaces[3][1] = removedFaces[i][1], cellFaces[3][2] = removedFaces[i][2];
            for (int j = 0; j < 4; j++)
            {
                sort(cellFaces[j][0], cellFaces[j][1], cellFaces[j][2], &cellFaces[j][0], &cellFaces[j][1], &cellFaces[j][2]);
            }
            EPCell ePCell;
            ePCell.from_faces(this->vertices4D, cellFaces);
            this->cells.push_back(ePCell);
        }
    }
};

static glm::vec4 epa(Object4D* s1, Object4D* s2, unsigned steps, Simplex simplex, float* depth, std::vector<glm::vec4>* supportPoints1, std::vector<glm::vec4>* supportPoints2)
{
    glm::vec4 normal4D=glm::vec4(0.f,1.f,0.f,0.f);
    float distance0 = 0.f;
    glm::vec4 contact0=glm::vec4(0.f);
    ExpandingPolytope polytope;
    polytope.from_simplex(simplex);
    unsigned count = 0;
    unsigned index;
    int i;
    EPCell minCell;
    glm::vec4 extendPoint;
    while (true)
    {
        index = 0;
        for (i = 0; i < polytope.cells.size(); i++)
        {
            if (i == 0 || distance0 > polytope.cells[i].distance)
            {
                distance0 = polytope.cells[i].distance;
                index = i;
            }
        }
        minCell = polytope.cells[index];
        normal4D = minCell.normal;
        extendPoint = support_of_cso(s1, s2, normal4D);
        if (dot(extendPoint, normal4D) - distance0 > 0.001f)
        {
            polytope.expand(extendPoint);
        }
        else
        {
            break;
        }
        count++;
        if (count > steps)
        {
            distance0 = -1.f;
            break;
        }
    }

    if (distance0 > 0.f)
    {
        *depth = distance0;
        *supportPoints1 = support_points(s1, normal4D);
        *supportPoints2 = support_points(s2, -normal4D);
    }
    else
    {
        *depth = distance0;
        std::cout << "depth0:" << distance0 << "\n";
    }
    return normal4D;
}

