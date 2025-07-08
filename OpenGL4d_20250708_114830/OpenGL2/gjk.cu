#pragma once
#include "geometry.cu"

__device__ static vec4 support(_d_RigidBody4D a, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, vec4 direction4D)
{
    if(a.colType == 3)//SPHERE
    {
        float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
        return a.position4d + normalize(direction4D)* radius;
    }
    else if (a.colType == 1)//BOX
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d(sign(direction4DToObj) * a.scale4D / 2.f);
        return body_pos_to_world(a, supportPosition4d);
    }
    else if (a.colType == 2)//STEP
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d(sign(direction4DToObj) * a.scale4D / 2.f);
        return body_pos_to_world(a, supportPosition4d);
    }
    else if (a.colType == 4)//MESH
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d;
        float dot0(-100000.f);
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId]; i++)
        {
            vec4 vertexPos4D(get_vertex(a.primitiveId, i, vertices4DsVec, verticesStartIndices) * a.scale4D);
            float dot1(dot(direction4DToObj, vertexPos4D));
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return body_pos_to_world(a, supportPosition4d);
    }
    else if (a.colType == 5)//CAPSULE
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.x, a.scale4D.y)) / 2.f);
        float length(a.scale4D.z);
        if (direction4DToObj.z > 0.f)
        {
            return body_pos_to_world(a, vec4(0.f, 0.f, length / 2.f - radius, 0.f)) + normalize(direction4D)* radius;
        }
        else
        {
            return body_pos_to_world(a, -vec4(0.f, 0.f, length / 2.f - radius, 0.f)) + normalize(direction4D)* radius;
        }
    }
    else if (a.colType == 6)//TERRAIN
    {
        vec4 direction4DToObj(direction4D);
        vec4 supportPosition4d;
        float dot0(-0.00001f);
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId]; i++)
        {
            vec4 vertexPos4D(get_vertex(a.primitiveId, i, vertices4DsVec, verticesStartIndices) * a.scale4D);
            float dot1(dot(direction4DToObj, vertexPos4D));
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return a.position4d + supportPosition4d;
    }
}

__device__ static vec4 support_of_cso(_d_RigidBody4D a, _d_RigidBody4D b, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, vec4 direction4D)
{
    return support(b, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, direction4D) - support(a, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, -direction4D);
}

__device__ static float support_distance(_d_RigidBody4D a, int index, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, vec4 direction4D)
{
    if (a.colType == 3)//SPHERE
    {
        float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.z, _d_min(a.scale4D.x, a.scale4D.y))) / 2.f);
        return radius;
    }
    else if (a.colType == 1)//BOX
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d(sign(direction4DToObj) * a.scale4D / 2.f);
        return dot(supportPosition4d, direction4DToObj);
    }
    else if (a.colType == 2)//STEP
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d(sign(direction4DToObj) * a.scale4D / 2.f);
        return dot(supportPosition4d, direction4DToObj);
    }
    else if (a.colType == 4)//MESH
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        vec4 supportPosition4d;
        float dot0(-0.00001f);
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId]; i++)
        {
            vec4 vertexPos4D(get_vertex(a.primitiveId, i, vertices4DsVec, verticesStartIndices) * a.scale4D);
            float dot1(dot(direction4DToObj, vertexPos4D));
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return dot0;
    }
    else if (a.colType == 5)//CAPSULE
    {
        vec4 direction4DToObj(world_vec_to_body(a, direction4D));
        float radius(_d_min(a.scale4D.w, _d_min(a.scale4D.x, a.scale4D.y)) / 2.f);
        float length(a.scale4D.z);
        if (direction4DToObj.z > 0.f)
        {
            return dot(direction4D, body_pos_to_world(a, vec4(0.f, 0.f, length / 2.f - radius, 0.f)) + normalize(direction4D)* radius);
        }
        else
        {
            return dot(direction4D, body_pos_to_world(a, -vec4(0.f, 0.f, length / 2.f - radius, 0.f)) + normalize(direction4D)* radius);
        }
    }
    else if (a.colType == 6)//TERRAIN
    {
        vec4 direction4DToObj(direction4D);
        vec4 supportPosition4d;
        float dot0(-0.00001f);
        for (unsigned int i(0); i < sizesOfVertices4D[a.primitiveId]; i++)
        {
            vec4 vertexPos4D(get_vertex(a.primitiveId, i, vertices4DsVec, verticesStartIndices) * a.scale4D);
            float dot1(dot(direction4DToObj, vertexPos4D));
            if (dot1 > dot0)
            {
                supportPosition4d = vertexPos4D;
                dot0 = dot1;
            }
        }
        return dot(direction4D, a.position4d + supportPosition4d);
    }
}

__device__ static struct _d_Simplex
{
    vec4 vertices4D[5];
    int size;
    vec4 normal4D[5];
    __device__ explicit _d_Simplex(vec4 initialPoint4D)
    {
        for (int i(0); i < 5; i++)
        {
            this->vertices4D[i] = initialPoint4D;
        }
        this->size = 1;
    }
    __device__ void push(vec4 vertice4D)
    {
        if (this->size >= 5)
        {
            //std::cout << "Simplex is already full!" << "\n";
        }
        else {
            this->vertices4D[this->size] = vertice4D;
            this->size += 1;
        }
    }
    __device__ void remove(int index)
    {
        if (index >= this->size) {
            //std::cout << "Invalid simplex index provided to remove_at" << "\n";
        }
        else if (this->size == 1) {
            //std::cout << "Simplex cannot have no points!" << "\n";
        }
        else
        {
            for (int i(index + 1); i < this->size; i++) {
                this->vertices4D[i - 1] = this->vertices4D[i];
            }
            this->size -= 1;
        }
    }

    // If self contains the origin, returns None. Otherwise, updates self to be
   // the closest simplex on self to the origin, and returns the closest point
   // on the updated simplex to the origin.
    __device__ vec4 nearest_simplex()
    {
        if (this->size == 1)
        {
            // single point case, just return it
            vec4 a(this->vertices4D[0]);
            return a - vec4(1e-4f, 2e-4f, 3e-4f, 4e-4f);
        }
        else if (this->size == 2)
        {
            // line case, return a direction perpendicular
            vec4 a(this->vertices4D[0]);
            vec4 b(this->vertices4D[1]);
            vec4 ab(normalize(b - a));
            float lambda(dot(-a, ab));
            // lambda is now such that a + lambda * (b - a) is the point on
            // the defined by a and b closest to the origin.
            return a + ab* lambda - vec4(1e-4f, 2e-4f, 3e-4f, 4e-4f);
        }
        else if (this->size == 3)
        {
            // triangle case, return the closest point on the triangle
            vec4 a(this->vertices4D[0]);
            vec4 b(this->vertices4D[1]);
            vec4 c(this->vertices4D[2]);
            // Equation of two variables, we're just going to use cgmath to
            // solve it
            vec4 veAB(normalize(b - a));
            vec4 vAC(c - a);
            vec4 neAB(normalize(vAC - veAB * dot(vAC, veAB)));
            float kv(dot(vec4(1e-4f,2e-4f,3e-4f,4e-4f)-a, veAB));
            float kn(dot(vec4(1e-4f,2e-4f,3e-4f,4e-4f)-a, neAB));
            return a + veAB* kv + neAB* kn - vec4(1e-4f, 2e-4f, 3e-4f, 4e-4f);
        }
        else if (this->size == 4)
        {
            // tetrahedron case, return a direction perpendicular
            vec4 a(this->vertices4D[0]);
            vec4 b(this->vertices4D[1]);
            vec4 c(this->vertices4D[2]);
            vec4 d(this->vertices4D[3]);
            vec4 ab(b - a);
            vec4 ac(c - a);
            vec4 ad(d - a);

            // We can use the triple cross product to just grab a normal to
            // the tetrahedron
            vec4 n(cross4d(ab, ac, ad));
            float k(dot(a - vec4(1e-4f, 2e-4f, 3e-4f, 4e-4f), n));
            return n*k;
        }
        else if (this->size == 5)
        {
            // Now we have a full 5-cell as our simplex. To check if the
            // origin is inside our simplex now, we simply need to perform
            // 5 halfspace tests.

            // We can actually skip one of the halfspace tests - because we
            // know that on the last iteration the direction was set to the
            // normal of the tetrahedron abcd, the origin must be in the
            // halfspace defined by the tetrahedron abcd.
            int i2(-1);
            vec4 direction4D2(vec4(0.f));
            float aoDist2(0.f);
            for (int i(0); i < 5; i++) {
                // tetrahedron is the 5 vertices without the ith vertex
                int j(0);
                vec4 tetrahedron[4];
                for (int k(0); k < 5; k++) {
                    if (k != i) {
                        tetrahedron[j] = this->vertices4D[k];
                        j++;
                    }
                }

                vec4 a(tetrahedron[0]);
                vec4 b(tetrahedron[1]);
                vec4 c(tetrahedron[2]);
                vec4 d(tetrahedron[3]);
                // e is the last vertex not in the tetrahedron
                vec4 e(this->vertices4D[i]);

                vec4 ab(b - a);
                vec4 ac(c - a);
                vec4 ad(d - a);
                this->normal4D[i] = normalize(cross4d(ab, ac, ad));
                //std::cout << "length of simplex normal!"<< length(normal) << "\n";
                // the origin has to be on the same side as e to pass the
                // halfspace test!
                float aoDist(dot(-a, this->normal4D[i]));
                if (aoDist * dot(e - a, this->normal4D[i]) < 0.f) {
                    // failed the halfspace test, so we know e is on the
                    // opposite side of the tetrahedron to the origin.
                    // We can then remove e from the simplex and set
                    // direction to the normal pointing towards the origin.
                    float k(-aoDist);
                    // k = k == 0.f ? 1.f : k;
                    vec4 dir(this->normal4D[i] * k);
                    if (i2 == -1 || aoDist2 > _d_abs(aoDist))
                    {
                        direction4D2 = dir;
                        aoDist2 = _d_abs(aoDist);
                        i2 = i;
                    }
                }
            }
            if (i2 == -1)
            {
                return vec4(0.f);
            }
            else
            {
                this->remove(i2);
                //if (direction4D2 == vec4(0.f))direction4D2=vec4(1.f,2.f,3.f,4.f);
                return direction4D2;
            }
            // If we reach here we've passed all the halfspace tests, so
            // the tetrahedron does indeed contain the origin!
        }
    }
};

__device__ static bool gjk(_d_RigidBody4D o1, _d_RigidBody4D o2, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Simplex* simplex)
{
    vec4 a(support_of_cso(o2, o1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, o2.position4d - o1.position4d));
    *simplex = _d_Simplex(a);
    vec4 d(-a);
    for (int i(0); i < 24; i++)
    {
        a = support_of_cso(o2, o1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, d);

        if (dot(a, d) < 0.f)
        {
            return false;
        }

        simplex->push(a);
        vec4 dir(simplex->nearest_simplex());
        if (dir == vec4(0.f))
        {
            return simplex->size==5;
        }
        else
        {
            d = -dir;
        }
    }
    return false;
}

__device__ static struct _d_EPTetra
{
    ivec4 tetra4DIndices;
    vec4 normal4D;
    float distance;
};

__device__ static struct _d_ExpandingPolytope
{
    vec4 vertices4D[64];
    int sizeOfVertices4D;
    _d_EPTetra ePTetras[192];
    int sizeOfEPTetras;
    __device__ void from_simplex(_d_Simplex simplex)
    {   
        this->sizeOfVertices4D = 0;
        this->sizeOfEPTetras = 0;
        if (simplex.size == 5)
        {
            for (int i(0); i < 5; i++)
            {
                this->vertices4D[i] = simplex.vertices4D[i];
            }
            this->sizeOfVertices4D = 5;
            for (int i(0); i < 5; i++)
            {
                unsigned count(0);
                for (int k(0); k < 5; k++)
                {
                    if (i != k)
                    {
                        this->ePTetras[i].tetra4DIndices.value(count, k); 
                        count += 1;
                    }
                }
            }
            this->sizeOfEPTetras = 5;
            for (int i(0); i < 5; i++)
            {
                vec4 normal4D(simplex.normal4D[i]);
                float distance(dot(normal4D, this->vertices4D[this->ePTetras[i].tetra4DIndices[0]]));
                if (distance == 0.f)
                {
                    this->ePTetras[i].normal4D = normal4D * _d_sign(-dot(normal4D, this->vertices4D[this->ePTetras[(i + 1)%5].tetra4DIndices[0]] + this->vertices4D[this->ePTetras[(i + 1) % 5].tetra4DIndices[1]] + this->vertices4D[this->ePTetras[(i + 1) % 5].tetra4DIndices[2]] + this->vertices4D[this->ePTetras[(i + 1) % 5].tetra4DIndices[3]]));
                    this->ePTetras[i].distance = 0.f;
                }
                else
                {
                    this->ePTetras[i].normal4D = normal4D * _d_sign(distance);
                    this->ePTetras[i].distance = _d_abs(distance);
                }
            }
        }
        //else
        //{
        //    this->vertices4D[0] = vec4(0.158113883008419f, 0.204124145231932f, -0.577350269189626f, 0) / 100.f;
        //    this->vertices4D[1] = vec4(0.158113883008419f, 0.204124145231932f, 0.288675134594813f, -0.5) / 100.f;
        //    this->vertices4D[2] = vec4(0.158113883008419f, 0.204124145231932f, 0.288675134594813f, 0.5) / 100.f;
        //    this->vertices4D[3] = vec4(0.158113883008419f, -0.612372435695794f, 0, 0) / 100.f;
        //    this->vertices4D[4] = vec4(-0.632455532033676f, 0, 0, 0) / 100.f;
        //    this->sizeOfVertices4D = 5;
        //    for (int i(0); i < 5; i++)
        //    {
        //        unsigned count(0);
        //        for (int k(0); k < 5; k++)
        //        {
        //            if (i != k)
        //            {
        //                this->ePTetras[i].tetra4DIndices.value(count, k);
        //                count += 1;
        //            }
        //        }
        //    }
        //    this->sizeOfEPTetras = 5;
        //    simplex.normal4D[0] = vec4(-0.25f, -0.322749f, 0.912871f, 5.26836e-09f);
        //    simplex.normal4D[1] = vec4(-0.25f, -0.322749f, -0.456435f, 0.790569f);
        //    simplex.normal4D[2] = vec4(-0.25f, -0.322749f, -0.456435f, -0.790569f);
        //    simplex.normal4D[3] = vec4(-0.25f, 0.968246f, 0, 5.26836e-09f);
        //    simplex.normal4D[4] = vec4(1.f, 0, 0, 0);
        //    for (int i(0); i < 5; i++)
        //    {
        //        vec4 normal4D(simplex.normal4D[i]);
        //        float distance(dot(normal4D, this->vertices4D[this->ePTetras[i].tetra4DIndices[0]]));
        //        this->ePTetras[i].normal4D = normal4D * _d_sign(distance), this->ePTetras[i].distance = _d_abs(distance);
        //    }
        //}
    }

    ivec4 expandTetras4DIndices[196];

    __device__ void expand(vec4 expandPoint4D)
    {
        int sizeOfIndices = 0;
        vec4 normal4D;
        float distance;
        int expandVertexIndex(this->sizeOfVertices4D);
        this->vertices4D[expandVertexIndex] = expandPoint4D; this->sizeOfVertices4D = this->sizeOfVertices4D + 1;

        for (size_t i(0); i < this->sizeOfEPTetras; i++)
        {
            if (dot(this->ePTetras[i].normal4D, expandPoint4D - this->vertices4D[this->ePTetras[i].tetra4DIndices[0]]) > -0.00003f)
            {
                expandTetras4DIndices[sizeOfIndices] = {this->ePTetras[i].tetra4DIndices[0], this->ePTetras[i].tetra4DIndices[1], this->ePTetras[i].tetra4DIndices[2], expandVertexIndex};sizeOfIndices = sizeOfIndices + 1;
                expandTetras4DIndices[sizeOfIndices] = {this->ePTetras[i].tetra4DIndices[0], this->ePTetras[i].tetra4DIndices[1], this->ePTetras[i].tetra4DIndices[3], expandVertexIndex};sizeOfIndices = sizeOfIndices + 1;
                expandTetras4DIndices[sizeOfIndices] = {this->ePTetras[i].tetra4DIndices[0], this->ePTetras[i].tetra4DIndices[2], this->ePTetras[i].tetra4DIndices[3], expandVertexIndex};sizeOfIndices = sizeOfIndices + 1;
                expandTetras4DIndices[sizeOfIndices] = {this->ePTetras[i].tetra4DIndices[1], this->ePTetras[i].tetra4DIndices[2], this->ePTetras[i].tetra4DIndices[3], expandVertexIndex};sizeOfIndices = sizeOfIndices + 1;
                for (int j(i + 1); j < this->sizeOfEPTetras; j++)
                {
                    this->ePTetras[j-1] = this->ePTetras[j];
                }
                this->sizeOfEPTetras -= 1;
                i--;
            }
        }

        for (size_t i(0); i < sizeOfIndices; i++)
        {
            bool isOverlap(false);
            for (size_t j(0); j < sizeOfIndices; j++)
            {
                if (i != j && expandTetras4DIndices[i] == expandTetras4DIndices[j])
                {
                    isOverlap = true;
                    break;
                }
            }
            if (!isOverlap)
            {
                normal4D = normalize(cross4d(this->vertices4D[expandTetras4DIndices[i][3]] - this->vertices4D[expandTetras4DIndices[i][0]], this->vertices4D[expandTetras4DIndices[i][2]] - this->vertices4D[expandTetras4DIndices[i][0]], this->vertices4D[expandTetras4DIndices[i][1]] - this->vertices4D[expandTetras4DIndices[i][0]]));
                distance = dot(normal4D, this->vertices4D[expandTetras4DIndices[i][0]]);
                if (distance == 0.f)
                {
                    this->ePTetras[this->sizeOfEPTetras].normal4D = normal4D * _d_sign(-dot(normal4D, this->vertices4D[0] + this->vertices4D[1] + this->vertices4D[2] + this->vertices4D[3] + this->vertices4D[4]));
                    this->ePTetras[this->sizeOfEPTetras].distance = 0.f;
                }
                else
                {
                    this->ePTetras[this->sizeOfEPTetras].normal4D = normal4D * _d_sign(distance);
                    this->ePTetras[this->sizeOfEPTetras].distance = _d_abs(distance);
                }
                this->ePTetras[this->sizeOfEPTetras].tetra4DIndices = expandTetras4DIndices[i];
                this->sizeOfEPTetras = this->sizeOfEPTetras + 1;
            }
        }
    }
};

__device__ static vec4 epa2(_d_RigidBody4D o1, _d_RigidBody4D o2, float* vertices4DsVec, int* sizesOfVertices4D, int* verticesStartIndices, _d_Simplex simplex, float* depth)
{
    _d_ExpandingPolytope polytope;
    polytope.from_simplex(simplex);
    vec4 normal4D;
    vec4 expandPoint;
    //bool isContactOrderly;
    int i2;
    for (unsigned int count(0); count < 24; count++) {
        for (int i(0); i < polytope.sizeOfEPTetras; i++) {
            if (i == 0 || *depth > polytope.ePTetras[i].distance) {
                *depth = polytope.ePTetras[i].distance;
                i2 = i;
                //isContactOrderly = false;
            }
            //else if (*depth == polytope.ePTetras[i].distance)
            //{
            //    //if (!isContactOrderly)normal4D = vec4(0.f);
            //    normal4D += polytope.ePTetras[i].normal4D;
            //    isContactOrderly = true;
            //}
        }
        //if (isContactOrderly)
        //{
        //    *depth = dot(support_of_cso(o2, o1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, normal4D), normalize(normal4D));
        //    break;
        //}
        normal4D = polytope.ePTetras[i2].normal4D;
        expandPoint = support_of_cso(o2, o1, vertices4DsVec, sizesOfVertices4D, verticesStartIndices, normal4D);
        if (dot(expandPoint, normal4D) - *depth > 0.0001f) polytope.expand(expandPoint);
        else break;
    }
    return normalize(normal4D);
}