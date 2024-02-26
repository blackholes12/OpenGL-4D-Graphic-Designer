#pragma once

//#include<GLFW/glfw3.h>
//#include"libs.h"
//#include<glm.hpp>
//#include<vec2.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat4x4.hpp>

#include"Simplex3d.h"
static glm::vec2 a02, b02, c02, d02, A0, B0, C0, D0, n01, n02, n03, n04;
static float dis1, dis2, dis3, dis4;

static glm::vec2 cross2d(glm::vec2 a2) {
	return glm::vec2(a2.y, 
		           - a2.x);
}

static glm::vec4 cross4d(glm::vec4 a2, glm::vec4 a3, glm::vec4 a4) {
	return glm::vec4(
		a2.y * a3.z * a4.w - a2.y * a3.w * a4.z - a2.z * a3.y * a4.w + a2.z * a3.w * a4.y + a2.w * a3.y * a4.z - a2.w * a3.z * a4.y,
		-a2.x * a3.z * a4.w + a2.x * a3.w * a4.z + a2.z * a3.x * a4.w - a2.z * a3.w * a4.x - a2.w * a3.x * a4.z + a2.w * a3.z * a4.x,
		a2.x * a3.y * a4.w - a2.x * a3.w * a4.y - a2.y * a3.x * a4.w + a2.y * a3.w * a4.x + a2.w * a3.x * a4.y - a2.w * a3.y * a4.x,
		-a2.x * a3.y * a4.z + a2.x * a3.z * a4.y + a2.y * a3.x * a4.z - a2.y * a3.z * a4.x - a2.z * a3.x * a4.y + a2.z * a3.y * a4.x
	);
}

static void orthonormal_basis(glm::vec4 normal4D, glm::vec4* vec41, glm::vec4* vec42, glm::vec4* vec43)
{
	if (glm::vec3(normal4D.x, normal4D.y, normal4D.z) == glm::vec3(0.f))
	{
		*vec41 = glm::vec4(-normal4D.w, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 1.f, 0.f);
	}
	else if (glm::vec3(normal4D.x, normal4D.y, normal4D.w) == glm::vec3(0.f))
	{
		*vec41 = glm::vec4(normal4D.z, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (glm::vec3(normal4D.x, normal4D.z, normal4D.w) == glm::vec3(0.f))
	{
		*vec41 = glm::vec4(-normal4D.y, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (glm::vec3(normal4D.y, normal4D.z, normal4D.w) == glm::vec3(0.f))
	{
		*vec41 = glm::vec4(0.f, normal4D.x, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else
	{
		glm::vec4 vA = glm::vec4(0.f, 1.f, 0.f, 0.f);
		glm::vec4 nA = normalize(vA / glm::dot(vA, normal4D) - normal4D);
		if(normal4D.y<0.f)
		*vec41 = nA;
		else if (normal4D.y == 0.f)
		*vec41 = vA;
		else
		*vec41 = -nA;
		glm::vec3 v1 = cross(glm::vec3(0.1f, 1.f, 0.f), glm::vec3(normal4D.x, normal4D.z, normal4D.w));
		*vec42 = normalize(glm::vec4(v1.x, 0.f, v1.y, v1.z));
		glm::vec3 v2 = cross(glm::vec3(vec42->x, vec42->z, vec42->w), glm::vec3(normal4D.x, normal4D.z, normal4D.w));
		*vec43 = normalize(glm::vec4(v2.x, 0.f, v2.y, v2.z));
	}
	//std::cout << "length of v0" << length(normal4D) << "\n";
	//std::cout << "length of v1" << length(*vec41) << "\n";
	//std::cout << "length of v2" << length(*vec42) << "\n";
	//std::cout << "length of v3" << length(*vec43) << "\n";
}

static glm::mat4 look_at_mat4(glm::vec4 from, glm::vec4 to)
{
	glm::vec4 x, y, z, w;
	z = normalize(to - from);
	orthonormal_basis(z, &y, &w, &x);
	return glm::mat4(x,y,z,w);
}

static glm::vec3 texcoord_position(glm::vec4 normal4d, glm::vec4 position4d)
{
		glm::vec4 divide1, divide2, axisX, axisY, axisZ;
		if (normal4d == glm::vec4(1.f, 0.f, 0.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, 1.f, 0.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 0.f, 1.f, 0.f), axisZ = glm::vec4(1.f, 0.f, 0.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, 0.f, 1.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(1.f, 0.f, 0.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, 0.f, 0.f, 1.f)) {
			axisX = glm::vec4(1.f, 0.f, 0.f, 0.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}

		else if (normal4d == glm::vec4(-1.f, 0.f, 0.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, -1.f, 0.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 0.f, 1.f, 0.f), axisZ = glm::vec4(1.f, 0.f, 0.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, 0.f, -1.f, 0.f)) {
			axisX = glm::vec4(0.f, 0.f, 0.f, 1.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(1.f, 0.f, 0.f, 0.f);
		}
		else if (normal4d == glm::vec4(0.f, 0.f, 0.f, -1.f)) {
			axisX = glm::vec4(1.f, 0.f, 0.f, 0.f), axisY = glm::vec4(0.f, 1.f, 0.f, 0.f), axisZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
		}
		else {
			divide1 = glm::vec4(1000000.f, 0.f, 1.f, 0.0000001f), divide2 = glm::vec4(0.f, 1000000.f, 1.f, 0.0000002f);
			axisX = normalize(cross4d(normal4d, divide1, divide2));
			axisY = normalize(cross4d(normal4d, axisX, divide2));
			axisZ = normalize(cross4d(normal4d, axisX, axisY));
		}
		return glm::vec3(dot(axisX, position4d)-0.5f, dot(axisY, position4d)-0.5f, dot(axisZ, position4d)-0.5f);
}
static glm::vec3 texcoord_position2(glm::vec4 position4d)
{
	return glm::vec3(position4d.x, position4d.z, position4d.w) / 2.f;
}

static glm::vec3 texcoord_position2(glm::vec4 normal4d, glm::vec4 position4d)
{
	if (abs(normal4d.x) > abs(normal4d.y) && abs(normal4d.x) > abs(normal4d.z) && abs(normal4d.x) > abs(normal4d.w))
	    return glm::vec3(position4d.y - 0.5f, position4d.z - 0.5f, position4d.w - 0.5f);
	if (abs(normal4d.y) > abs(normal4d.x) && abs(normal4d.y) > abs(normal4d.z) && abs(normal4d.y) > abs(normal4d.w))
		return glm::vec3(position4d.x - 0.5f, position4d.z - 0.5f, position4d.w - 0.5f);
	if (abs(normal4d.z) > abs(normal4d.x) && abs(normal4d.z) > abs(normal4d.y) && abs(normal4d.z) > abs(normal4d.w))
		return glm::vec3(position4d.x - 0.5f, position4d.y - 0.5f, position4d.w - 0.5f);
	if (abs(normal4d.w) > abs(normal4d.x) && abs(normal4d.w) > abs(normal4d.y) && abs(normal4d.w) > abs(normal4d.z))
		return glm::vec3(position4d.x - 0.5f, position4d.y - 0.5f, position4d.z - 0.5f);
}

static float terrain_height2(glm::vec4 m)
{
	return terrain_height(m+glm::vec4(0.02f));
}

static glm::vec4 get_terrain_normal(glm::vec4 m)
{
	glm::vec4 m2;
	glm::vec4 normal4d;
	glm::vec4 pos1, pos2, pos3, pos4;
	m2 = m;
	pos1 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.x += 0.01f;
	pos2 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.z += 0.01f;
	pos3 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.w += 0.01f;
	pos4 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	normal4d = -normalize(cross4d(pos4 - pos1, pos3 - pos1, pos2 - pos1));
	if (normal4d.y < 0)
	{
		normal4d = -normal4d;
	}
	if (abs(m.x) >= 32.f)
	{
		normal4d.x /= 100.f;
	}
	if (abs(m.z) >= 32.f)
	{
		normal4d.z /= 100.f;
	}	
	if (abs(m.w) >= 32.f)
	{
		normal4d.w /= 100.f;
	}
	return normalize(normal4d);
}

static bool is_in_tetra(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec3 a2, b2, c2, d2, A, B, C, D, n1, n2, n3, n4;
	a2 = glm::vec3(a.x, a.z, a.w);
	b2 = glm::vec3(b.x, b.z, b.w);
	c2 = glm::vec3(c.x, c.z, c.w);
	d2 = glm::vec3(d.x, d.z, d.w);
	n1 = cross(c2 - b2, b2 - a2);
	n2 = cross(d2 - c2, c2 - a2);
	n3 = cross(b2 - d2, d2 - a2);
	n4 = cross(d2 - b2, b2 - c2);
	A = B = C = glm::vec3(E.x, E.z, E.w) - a2;
	D = glm::vec3(E.x, E.z, E.w) - b2;
	dis1 = dot(A, n1);
	dis2 = dot(B, n2);
	dis3 = dot(C, n3);
	dis4 = dot(D, n4);
	return dis1 < 0 && dis2 < 0 && dis3 < 0 && dis4 < 0;
}

static glm::vec4 get_normal_from_point_and_face(glm::vec4 position4D, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3)
{
	glm::vec4 ve12 = normalize(vertex4D2 - vertex4D1);
	glm::vec4 v13 = vertex4D3 - vertex4D1;
	glm::vec4 ne12 = normalize(v13 - ve12 * dot(v13, ve12));
	glm::vec4 v1s = position4D - vertex4D1;
	float kv = dot(v1s, ve12);
	float kn = dot(v1s, ne12);
	glm::vec4 closetPosToS = vertex4D1 + kv * ve12 + kn * ne12;
	return normalize(position4D - closetPosToS);
}

static glm::vec4 get_distance_and_normal_from_point_and_face(glm::vec4 position4D, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3,float*distance)
{
	glm::vec4 ve12 = normalize(vertex4D2 - vertex4D1);
	glm::vec4 v13 = vertex4D3 - vertex4D1;
	glm::vec4 ne12 = normalize(v13 - ve12 * dot(v13, ve12));
	glm::vec4 v1s = position4D - vertex4D1;
	float kv = dot(v1s, ve12);
	float kn = dot(v1s, ne12);
	glm::vec4 closetPosToS = vertex4D1 + kv * ve12 + kn * ne12;
	glm::vec4 normal = position4D - closetPosToS;
	*distance = length(normal);
	return normalize(normal);
}

static bool is_in_tetra2(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec4 n1 = get_normal_from_point_and_face(d, a, b, c);
	glm::vec4 n2 = get_normal_from_point_and_face(a, b, c, d);
	glm::vec4 n3 = get_normal_from_point_and_face(b, c, d, a);
	glm::vec4 n4 = get_normal_from_point_and_face(c, d, a, b);
	return (dot(E - a, n1) > 0.f && dot(E - b, n2) > 0.f && dot(E - c, n3) > 0.f && dot(E - d, n4) > 0.f);
}

static glm::vec4 get_line_in_face_pos(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 faceVertex1, glm::vec4 faceVertex2, glm::vec4 faceVertex3)
{
	glm::vec4 ShiftFromLineToFace = normal4D * dot(normal4D, faceVertex1 - lineVertex1);
	glm::vec4 lineVertexShifted1 = lineVertex1 + ShiftFromLineToFace;
	glm::vec4 lineVertexShifted2 = lineVertex2 + ShiftFromLineToFace;
	float distance1, distance2;
	glm::vec4 normal1 = get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1);
	glm::vec4 normal2 = get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2);
	glm::vec4 intersectPoint = glm::mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2));
	return intersectPoint - ShiftFromLineToFace/2.f;
}

static bool is_in_triangle(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c)
{
	glm::vec4 n1 = normalize(b - a - normalize(c - a) * dot(normalize(c - a), b - a));
	glm::vec4 n2 = normalize(c - b - normalize(a - b) * dot(normalize(a - b), c - b));
	glm::vec4 n3 = normalize(a - c - normalize(b - c) * dot(normalize(b - c), a - c));
	return dot(E - a, n1) > 0.f && dot(E - b, n2) > 0.f && dot(E - c, n3) > 0.f;
}

static bool is_line_in_face(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 faceVertex1, glm::vec4 faceVertex2, glm::vec4 faceVertex3,glm::vec4* contactPos4D)
{
	glm::vec4 ShiftFromLineToFace = normal4D * dot(normal4D, faceVertex1 - lineVertex1);
	glm::vec4 lineVertexShifted1 = lineVertex1 + ShiftFromLineToFace;
	glm::vec4 lineVertexShifted2 = lineVertex2 + ShiftFromLineToFace;
	float distance1,distance2;
	glm::vec4 normal1 = get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3,&distance1);
	glm::vec4 normal2 = get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3,&distance2);
	glm::vec4 intersectPoint = glm::mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2));
	*contactPos4D = intersectPoint - ShiftFromLineToFace;
	return dot(normal1, normal2)<0.f && is_in_triangle(intersectPoint, faceVertex1, faceVertex2, faceVertex3)&& distance1!=distance2;
}
//E camPos

static float get_tetra_height(glm::vec4 E, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	glm::vec4 normal4D = normalize(cross4d(A - B, A - C, A - D));
	float l = dot(normal4D, E - A);
	float t = l / dot(-normal4D, glm::vec4(0,-1,0,0));
	return E.y - t;
}

static float get_tetra_height(glm::vec4 E, glm::vec4 normal4D,glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	float l = dot(normal4D, E - A);
	float t = l / dot(-normal4D, glm::vec4(0, -1, 0, 0));
	return E.y - t;
}

static float get_tetra_height(glm::vec4 E, glm::vec4* normal4D, float* t, glm::vec4 normal4D2, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	*normal4D = normal4D2;
	float dis = dot(normal4D2, E - A);
	*t = dis / dot(-normal4D2, glm::vec4(0, -1, 0, 0));//distance/cos
	return E.y - *t;
}

static glm::vec4 get_ray_detect_tetra_pos(glm::vec4 cameraPos, glm::vec4 forward,glm::vec4 normal4D, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	float l = dot(normal4D, cameraPos - A);
	float t = l / dot(-normal4D, forward);
	return cameraPos + forward * t;
}

static bool point_col_terrain_tetra4D(glm::vec4 position4D,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPos,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4)
{
	bool isCol = false;
	float depth0;
	glm::vec4 contactPos0;

	depth0 = -dot(position4D - vertex4D1, normal4D0);
	if (depth0 > 0.f)
	{
		contactPos0 = position4D + depth0 * normal4D0;
		if (is_in_tetra(contactPos0, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_terrain_tetra4D(glm::vec4 spherePos4D, float radious,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPos)
{
	bool isCol = false;
	float depth0;
	glm::vec4 contactPos0;

	depth0 = radious - dot(spherePos4D - vertex4D1, normal4D0);
	if (depth0 > 0.f)
	{
		contactPos0 = spherePos4D - (radious - depth0) * normal4D0;
		if (is_in_tetra(contactPos0, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_tetra4D(glm::vec4 spherePos4D, float radious,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPos)
{
	bool isCol = false;
	float depth0;
	glm::vec4 contactPos0;
	depth0 = radious - dot(spherePos4D - vertex4D1, normal4D0);
	if (depth0 > 0.f && depth0 < radious)
	{
		contactPos0 = spherePos4D - (radious - depth0) * normal4D0;
		if (is_in_tetra2(contactPos0, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_face4D(glm::vec4 spherePos4D, float radious, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3,float* depth,glm::vec4* normal4D,glm::vec4* contactPos)
{
	bool isCol = false;
	glm::vec4 normal4D0;
	float depth0;
	glm::vec4 contactPos0;
	normal4D0 = get_normal_from_point_and_face(spherePos4D, vertex4D1, vertex4D2, vertex4D3);
	depth0 = radious - dot(spherePos4D - vertex4D1, normal4D0);
	if (depth0 > 0.f)
	{
		contactPos0 = spherePos4D - (radious - depth0) * normal4D0;
		if (is_in_triangle(contactPos0, vertex4D1, vertex4D2, vertex4D3))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_line4D(glm::vec4 spherePos4D, float radious, glm::vec4 vertex4D1, glm::vec4 vertex4D2, float* depth, glm::vec4* normal4D, glm::vec4* contactPos)
{
	bool isCol = false;
	glm::vec4 normal4D0;
	float depth0;
	glm::vec4 contactPos0;
	normal4D0 = normalize(spherePos4D - vertex4D1 - normalize(vertex4D2 - vertex4D1) * dot(normalize(vertex4D2 - vertex4D1), spherePos4D - vertex4D1));
	depth0 = radious - dot(spherePos4D - vertex4D1, normal4D0);
	if (depth0 > 0.f)
	{
		contactPos0 = spherePos4D - (radious - depth0) * normal4D0;
		if (dot(vertex4D1 - contactPos0, vertex4D2 - contactPos0)<0.f)
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_point4D(glm::vec4 spherePos4D, float radious, glm::vec4 vertex4D, float* depth, glm::vec4* normal4D, glm::vec4* contactPos)
{
	bool isCol = false;
	glm::vec4 normal4D0;
	float depth0;
	glm::vec4 contactPos0;
	normal4D0 = normalize(spherePos4D - vertex4D);
	depth0 = radious - dot(spherePos4D - vertex4D, normal4D0);
	if (depth0 > 0.f)
	{
		contactPos0 = spherePos4D - (radious - depth0) * normal4D0;
		*depth = depth0;
		*normal4D = normal4D0;
		*contactPos = contactPos0;
		isCol = true;
	}
	return isCol;
}

static bool get_ray_detect_tetra_pos(glm::vec4 cameraPos, glm::vec4 forward, glm::vec4 normal4D , glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D, glm::vec4* hitPosNear, glm::vec4* hitPosFar)
{
	bool isCol = false;
	float l = dot(normal4D, cameraPos - A);
	float t0 = l / dot(-normal4D, forward);
	if (t0 > 0.f)
	{
		glm::vec4 hitPos0 = cameraPos + forward * t0;
		if (is_in_tetra2(hitPos0, A, B, C, D))
		{
			if (t0 < length(*hitPosNear - cameraPos))
			{
				*hitPosNear = hitPos0;
			}
			if (t0 > length(*hitPosFar - cameraPos))
			{
				*hitPosFar = hitPos0;
			}
			isCol = true;
		}
	}
	return isCol;
}

static glm::vec4 rcolPos4D;

static bool isIn;

//1=x,2=y,3=z,4=w,5=-x,6=-y7=-z,8=-w
//a direction

static bool col_plane4D(glm::vec4 startPos4D, glm::vec4 endPos4D, glm::vec4 planePos4D, glm::vec4 planeScale4D, glm::vec4* hitPosNear, glm::vec4* hitPosFar, const unsigned int a)
{
	isIn = false;
	unsigned int a2,b2,c2,d2;
	if (a > 3)
	{
		a2 = a - 4;
	}
	else
	{
		a2 = a;
	}

	if (a2 == 0)
	{
		b2 = 1,c2 = 2,d2 = 3;
	}
	if (a2 == 1)
	{
		b2 = 0,c2 = 2,d2 = 3;
	}
	if (a2 == 2)
	{
		b2 = 0,c2 = 1,d2 = 3;
	}
	if (a2 == 3)
	{
		b2 = 0,c2 = 1,d2 = 2;
	}
	if ((startPos4D[a2]-planePos4D[a2])*(endPos4D[a2] - planePos4D[a2])<0)
	{
		rcolPos4D = startPos4D + (endPos4D - startPos4D) * (planePos4D[a2]- startPos4D[a2]) / (endPos4D[a2]- startPos4D[a2]) - planePos4D;
		isIn = abs(rcolPos4D[b2]) < planeScale4D[b2] / 2.f &&
			abs(rcolPos4D[c2] ) < planeScale4D[c2] / 2.f &&
			abs(rcolPos4D[d2]) < planeScale4D[d2] / 2.f;
		if (isIn)
		{
			//std::cout << "hit" << "\n";
			glm::vec4 hitPos = rcolPos4D + planePos4D;
			if (length(startPos4D - hitPos) < length(startPos4D - *hitPosNear))
			{
			    //std::cout << "length of ray=" << length(startPos4D - hitPos) << "\n";
				*hitPosNear = hitPos;
			}
			if (length(startPos4D - hitPos) > length(startPos4D - *hitPosFar))
			{
				*hitPosFar = hitPos;
			}
		}
	}
	return isIn;
}

static bool line_sigment_detect_box4D(glm::vec4 startPos4D, glm::vec4 endPos4D, glm::vec4 scale4D, glm::vec4* hitPosNear, glm::vec4* hitPosFar)
{
	bool isDetected = false;
	for (int i = 0; i < 8; i++)
	{
		unsigned int a2, b2, c2, d2;
		float sign;
		if (i > 3)
		{
			a2 = i - 4;
			sign = -1.f;
		}
		else
		{
			a2 = i;
			sign = 1.f;
		}

		if (a2 == 0)
		{
			b2 = 1, c2 = 2, d2 = 3;
		}
		if (a2 == 1)
		{
			b2 = 0, c2 = 2, d2 = 3;
		}
		if (a2 == 2)
		{
			b2 = 0, c2 = 1, d2 = 3;
		}
		if (a2 == 3)
		{
			b2 = 0, c2 = 1, d2 = 2;
		}
		glm::vec4 planePos4D = glm::vec4(0.f);
		planePos4D[a2] = sign * scale4D[a2] / 2.f;
		glm::vec4 planeScale4D = glm::vec4(0.f);
		planeScale4D[b2] = scale4D[b2];
		planeScale4D[c2] = scale4D[c2];
		planeScale4D[d2] = scale4D[d2];
		if (col_plane4D(startPos4D, endPos4D, planePos4D,planeScale4D, hitPosNear, hitPosFar, i))
		{
			isDetected = true;
		}
	}
	return isDetected;
}

static glm::vec4 buildingPos4D;
static bool isConstLength;
static float hitLengthHorizontal;
static glm::vec4 get_build_position4D(glm::vec4 cameraPos, glm::vec4 forward, glm::vec4 hittingPos,bool isShift)
{
	if (isShift) 
	{

		if (!isConstLength) {
			glm::vec4 RelativeHitPos = hittingPos - cameraPos;
			hitLengthHorizontal = length(glm::vec3(RelativeHitPos.x, RelativeHitPos.z, RelativeHitPos.w));
			isConstLength = true;
		}
		
		float buildLengthHorizontal0 = length(glm::vec3(forward.x, forward.z, forward.w));
		buildingPos4D = cameraPos + forward * hitLengthHorizontal / buildLengthHorizontal0;
	}
	if (!isShift)
	{
		buildingPos4D = hittingPos;
		isConstLength = false;
	}
	return buildingPos4D;
}

static glm::vec4 wallPos4D;
static glm::vec4 wallScale4D;

//static glm::vec4 get_wall_build_position4D(glm::vec4 hittingPos) 
//{
//	glm::vec3 gridPosXZW = glm::vec3(floor(hittingPos.x), floor(hittingPos.z), floor(hittingPos.w));
//	glm::vec3 relativeInGridPosXZW = glm::vec3(hittingPos.x-0.5f, hittingPos.z-0.5f , hittingPos.w-0.5f) - gridPosXZW;
//	if (relativeInGridPosXZW.x > 0 && abs(relativeInGridPosXZW.y) < relativeInGridPosXZW.x && abs(relativeInGridPosXZW.z) < relativeInGridPosXZW.x)
//	{
//		wallPos4D= glm::vec4(floor(hittingPos.x) + 0.9f,floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f,floor(hittingPos.z) + 0.5f,floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(0.2f, 0.75f, 1.f, 1.f);
//	}
//	if (relativeInGridPosXZW.x < 0 && abs(relativeInGridPosXZW.y) > relativeInGridPosXZW.x && abs(relativeInGridPosXZW.z) > relativeInGridPosXZW.x)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.1f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(0.2f, 0.75f, 1.f, 1.f);
//	}
//	if (relativeInGridPosXZW.y > 0 && abs(relativeInGridPosXZW.x) < relativeInGridPosXZW.y && abs(relativeInGridPosXZW.z) < relativeInGridPosXZW.y)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.9f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 0.2f, 1.f);
//	}
//	if (relativeInGridPosXZW.y < 0 && abs(relativeInGridPosXZW.x) > relativeInGridPosXZW.y && abs(relativeInGridPosXZW.z) > relativeInGridPosXZW.y)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.1f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 0.2f, 1.f);
//	}
//	if (relativeInGridPosXZW.z > 0 && abs(relativeInGridPosXZW.x) < relativeInGridPosXZW.z && abs(relativeInGridPosXZW.y) < relativeInGridPosXZW.z)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.9f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 1.f, 0.2f);
//	}
//	if (relativeInGridPosXZW.z < 0 && abs(relativeInGridPosXZW.x) > relativeInGridPosXZW.z && abs(relativeInGridPosXZW.y) > relativeInGridPosXZW.z)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.1f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 1.f, 0.2f);
//	}
//	return wallPos4D;
//}
//static glm::vec4 get_wall_build_scale4D()
//{
//	return wallScale4D;
//}

static glm::vec4 get_cap_position4D(glm::vec4 hittingPos)
{
	wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.25f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.5f);
	wallScale4D = glm::vec4(1.f, 0.25f, 1.f, 1.f);
	return wallPos4D;
}

//static glm::vec4 get_cap_scale4D()
//{
//	return wallScale4D;
//}
