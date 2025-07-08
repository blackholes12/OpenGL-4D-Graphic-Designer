#pragma once

//#include<GLFW/glfw3.h>
//#include"libs.h"
//#include<glm.hpp>
//#include<vec2.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat4x4.hpp>

#include"Simplex3d.h"
#define PI glm::pi<float>()

static glm::vec2 cross2d(glm::vec2 a2) {
	return glm::vec2(a2.y, - a2.x);
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
	if (alg::abs(normal4D.x) < 1e-8f && alg::abs(normal4D.y) < 1e-8f && alg::abs(normal4D.z) < 1e-8f)
	{
		*vec41 = glm::vec4(-normal4D.w, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 1.f, 0.f);
	}
	else if (alg::abs(normal4D.x) < 1e-8f && alg::abs(normal4D.y) < 1e-8f && alg::abs(normal4D.w) < 1e-8f)
	{
		*vec41 = glm::vec4(normal4D.z, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (alg::abs(normal4D.x) < 1e-8f && alg::abs(normal4D.z) < 1e-8f && alg::abs(normal4D.w) < 1e-8f)
	{
		*vec41 = glm::vec4(-normal4D.y, 0.f, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (alg::abs(normal4D.y) < 1e-8f && alg::abs(normal4D.z) < 1e-8f && alg::abs(normal4D.w) < 1e-8f)
	{
		*vec41 = glm::vec4(0.f, normal4D.x, 0.f, 0.f);
		*vec42 = glm::vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}
	else
	{
		glm::vec4 vA(glm::vec4(0.f, 1.f, 0.f, 0.f));
		if(normal4D.y<0.f)
		*vec41 = alg::normalize(vA - normal4D * alg::dot(vA, normal4D));
		else if (normal4D.y == 0.f)
		*vec41 = -vA;
		else
		*vec41 = -alg::normalize(vA - normal4D * alg::dot(vA, normal4D));
		glm::vec3 normalXZW(glm::vec3(normal4D.x, normal4D.z, normal4D.w));
		if (alg::abs(normalXZW.y)<1e-8f&&alg::abs(normalXZW.z) < 1e-8f)
		{
			*vec42 = glm::vec4(0.f, 0.f, 1.f, 0.f);
			*vec43 = glm::vec4(0.f, 0.f, 0.f, 1.f);
			//if (!(alg::length(glm::vec4(v1.x, 0.f, v1.y, v1.z))) > 0.f || !(alg::length(glm::vec4(v2.x, 0.f, v2.y, v2.z))) > 0.f)std::cout << "glm::vec4(" << normalXZW.x << "," << 0.f << "," << normalXZW.y << "," << normalXZW.z << "),glm::vec4(" << "glm::vec4(" << v1.x << "," << 0.f << "," << v1.y << "," << v1.z << "),glm::vec4(" << v2.x << "," << 0.f << "," << v2.y << "," << v2.z << ")" << '\n';
		}
		else
		{
			glm::vec3 v1(cross(glm::vec3(1.f, 0.f, 0.f), normalXZW));
			*vec42 = alg::normalize(glm::vec4(v1.x, 0.f, v1.y, v1.z));
			glm::vec3 v2(cross(v1, normalXZW));
			*vec43 = alg::normalize(glm::vec4(v2.x, 0.f, v2.y, v2.z));
		}
		//glm::vec4 divide1, divide2, axisX, axisY, axisZ;
		//divide1 = glm::vec4(1000000.f, 0.1f, 1.f, 0.0000001f), divide2 = glm::vec4(0.1f, 1000000.f, 1.f, 0.0000002f);
		//axisX = alg::normalize(cross4d(normal4D, divide1, divide2));
		//axisY = alg::normalize(cross4d(normal4D, axisX, divide2));
		//axisZ = cross4d(normal4D, axisX, axisY);
		//*vec41 = axisX;
		//*vec42 = axisY;
		//*vec43 = axisZ;
	}
}

static glm::mat4 look_at_mat4(glm::vec4 from, glm::vec4 to)
{
	glm::vec4 x, y, z, w;
	z = alg::normalize(to - from);
	orthonormal_basis(z, &y, &w, &x);
	return glm::mat4(x,y,z,w);
}

static glm::vec3 texcoord_position(glm::vec4 normal4d, glm::vec4 position4d, glm::vec3 offset)
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
			axisX = alg::normalize(cross4d(normal4d, divide1, divide2));
			axisY = alg::normalize(cross4d(normal4d, axisX, divide2));
			axisZ = alg::normalize(cross4d(normal4d, axisX, axisY));
		}
		return glm::vec3(alg::dot(axisX, position4d), alg::dot(axisY, position4d), alg::dot(axisZ, position4d)) + offset;
}
static glm::vec3 texcoord_position2(glm::vec4 position4d, glm::vec3 offset)
{
	return glm::vec3(position4d.x, position4d.z, position4d.w) / 2.f+ offset;
}

static glm::vec3 texcoord_position2(glm::vec4 normal4d, glm::vec4 position4d, glm::vec3 offset)
{
	if (alg::abs(normal4d.x) > alg::abs(normal4d.y) && alg::abs(normal4d.x) > alg::abs(normal4d.z) && alg::abs(normal4d.x) > alg::abs(normal4d.w))
	    return glm::vec3(position4d.y - 0.5f, position4d.z - 0.5f, position4d.w - 0.5f)+ offset;
	else if (alg::abs(normal4d.y) > alg::abs(normal4d.x) && alg::abs(normal4d.y) > alg::abs(normal4d.z) && alg::abs(normal4d.y) > alg::abs(normal4d.w))
		return glm::vec3(position4d.x - 0.5f, position4d.z - 0.5f, position4d.w - 0.5f)+ offset;
	else if (alg::abs(normal4d.z) > alg::abs(normal4d.x) && alg::abs(normal4d.z) > alg::abs(normal4d.y) && alg::abs(normal4d.z) > alg::abs(normal4d.w))
		return glm::vec3(position4d.x - 0.5f, position4d.y - 0.5f, position4d.w - 0.5f)+ offset;
	else if (alg::abs(normal4d.w) > alg::abs(normal4d.x) && alg::abs(normal4d.w) > alg::abs(normal4d.y) && alg::abs(normal4d.w) > alg::abs(normal4d.z))
		return glm::vec3(position4d.x - 0.5f, position4d.y - 0.5f, position4d.z - 0.5f)+ offset;
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
	m2 = m - glm::vec4(0.5f);
	pos1 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.x += 1.f;
	pos2 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.z += 1.f;
	pos3 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	m2.w += 1.f;
	pos4 = glm::vec4(m2.x, terrain_height2(m2), m2.z, m2.w);
	normal4d = alg::normalize(cross4d(pos4 - pos1, pos3 - pos1, pos2 - pos1));
	return alg::normalize(normal4d);
}

static glm::vec4 get_terrain_normal2(glm::vec4 m)
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
	normal4d = alg::normalize(cross4d(pos4 - pos1, pos3 - pos1, pos2 - pos1));
	if (alg::abs(m.x) >= 32.f)
	{
		normal4d.x /= 100.f;
	}
	if (alg::abs(m.z) >= 32.f)
	{
		normal4d.z /= 100.f;
	}
	if (alg::abs(m.w) >= 32.f)
	{
		normal4d.w /= 100.f;
	}
	return alg::normalize(normal4d);
}

//a=-1:reflectDirection4D,a=1:direction4D;
static glm::vec4 get_lens_flare_direction4D(glm::vec4 direction4D, glm::vec4 cameraForward4D,float a)
{
	float k(alg::dot(cameraForward4D, -direction4D));
	float angle(a*acos(k));
	glm::vec4 n(alg::normalize(-direction4D-k* cameraForward4D));
	return cos(angle) * cameraForward4D + sin(angle) * n;
}

static bool is_in_terrain_tetra(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec3 a2(glm::vec3(a.x, a.z, a.w));
	glm::vec3 b2(glm::vec3(b.x, b.z, b.w));
	glm::vec3 c2(glm::vec3(c.x, c.z, c.w));
	glm::vec3 d2(glm::vec3(d.x, d.z, d.w));
	glm::vec3 n1(cross(c2 - b2, b2 - a2));
	glm::vec3 n2(cross(d2 - c2, c2 - a2));
	glm::vec3 n3(cross(b2 - d2, d2 - a2));
	glm::vec3 n4(cross(d2 - b2, b2 - c2));
	glm::vec3 A(glm::vec3(E.x, E.z, E.w) - a2);
	glm::vec3 B(A);
	glm::vec3 C(A);
	glm::vec3 D(glm::vec3(E.x, E.z, E.w) - b2);
	float dis1(alg::dot(A, n1));
	float dis2(alg::dot(B, n2));
	float dis3(alg::dot(C, n3));
	float dis4(alg::dot(D, n4));
	return dis1 <= 0.f && dis2 <= 0.f && dis3 <= 0.f && dis4 <= 0.f;
}

static bool is_in_tetra(glm::vec4 E, glm::vec4 normal4D,glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec3 a2(glm::vec3(a.x, a.z, a.w));
	glm::vec3 b2(glm::vec3(b.x, b.z, b.w));
	glm::vec3 c2(glm::vec3(c.x, c.z, c.w));
	glm::vec3 d2(glm::vec3(d.x, d.z, d.w));
	glm::vec3 n1(cross(c2 - b2, b2 - a2));
	glm::vec3 n2(cross(d2 - c2, c2 - a2));
	glm::vec3 n3(cross(b2 - d2, d2 - a2));
	glm::vec3 n4(cross(d2 - b2, b2 - c2));
	glm::vec3 A(glm::vec3(E.x, E.z, E.w) - a2);
	glm::vec3 B(A);
	glm::vec3 C(A);
	glm::vec3 D(glm::vec3(E.x, E.z, E.w) - b2);
	float dis1(alg::dot(A, n1));
	float dis2(alg::dot(B, n2));
	float dis3(alg::dot(C, n3));
	float dis4(alg::dot(D, n4));
	if(normal4D.y>0.f)return dis1 <= 0.f && dis2 <= 0.f && dis3 <= 0.f && dis4 <= 0.f;
	else return dis1 >= 0.f && dis2 >= 0.f && dis3 >= 0.f && dis4 >= 0.f;
}

static glm::vec4 get_normal_from_point_and_face(glm::vec4 position4d, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3)
{
	glm::vec4 ve12(alg::normalize(vertex4D2 - vertex4D1));
	glm::vec4 v13(vertex4D3 - vertex4D1);
	glm::vec4 ne12(alg::normalize(v13 - ve12 * alg::dot(v13, ve12)));
	glm::vec4 v1s(position4d - vertex4D1);
	float kv(alg::dot(v1s, ve12));
	float kn(alg::dot(v1s, ne12));
	glm::vec4 closetPosToS(vertex4D1 + kv * ve12 + kn * ne12);
	return alg::normalize(position4d - closetPosToS);
}

static glm::vec4 get_distance_and_normal_from_point_and_face(glm::vec4 position4d, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3,float*distance)
{
	glm::vec4 ve12(alg::normalize(vertex4D2 - vertex4D1));
	glm::vec4 v13(vertex4D3 - vertex4D1);
	glm::vec4 ne12(alg::normalize(v13 - ve12 * alg::dot(v13, ve12)));
	glm::vec4 v1s(position4d - vertex4D1);
	float kv(alg::dot(v1s, ve12));
	float kn(alg::dot(v1s, ne12));
	glm::vec4 closetPosToS(vertex4D1 + kv * ve12 + kn * ne12);
	glm::vec4 normal(position4d - closetPosToS);
	*distance = alg::length(normal);
	return alg::normalize(normal);
}

static bool is_in_tetra2(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec4 n1(get_normal_from_point_and_face(d, a, b, c));
	glm::vec4 n2(get_normal_from_point_and_face(a, b, c, d));
	glm::vec4 n3(get_normal_from_point_and_face(b, c, d, a));
	glm::vec4 n4(get_normal_from_point_and_face(c, d, a, b));
	return (alg::dot(E - a, n1) >= 0.f && alg::dot(E - b, n2) >= 0.f && alg::dot(E - c, n3) >= 0.f && alg::dot(E - d, n4) >= 0.f);
}

static bool is_in_tetra3(glm::vec4 normal4D, glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	glm::vec4 contactPos0(E + alg::dot(normal4D, a - E) * normal4D);
	return is_in_tetra2(contactPos0, a, b, c, d);
}

static bool is_in_tetra4(glm::vec4 E, glm::vec4 normal4D, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
{
	//bool isInTetra(false);
	if (normal4D.y != 0.f)
	{
		if (is_in_tetra(E, normal4D, a, b, c, d))
		{
			return true;
		}
	}
	else
	{
		if (is_in_tetra2(E, a, b, c, d))
		{
			return true;
		}
	}
	return false;
}

static glm::vec4 get_point_from_edge_and_edge(glm::vec4 vertex4DA1, glm::vec4 vertex4DA2, glm::vec4 vertex4DB1, glm::vec4 vertex4DB2)
{
	glm::vec4 dirB(alg::normalize(vertex4DB2 - vertex4DB1));
	glm::vec4 dirA1ToB1(vertex4DB1 - vertex4DA1);
	glm::vec4 dirA2ToB2(vertex4DB2 - vertex4DA2);
	float distanceA1(alg::length(dirA1ToB1 - alg::dot(dirB, dirA1ToB1) * dirB));
	float distanceA2(alg::length(dirA2ToB2 - alg::dot(dirB, dirA2ToB2) * dirB));
	return (distanceA2 * vertex4DA1 + distanceA1 * vertex4DA2)/(distanceA1 + distanceA2);
}

static void get_edge_in_face_pos(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 faceVertex1, glm::vec4 faceVertex2, glm::vec4 faceVertex3, glm::vec4* contactPosA, glm::vec4* contactPosB)
{
	glm::vec4 shiftFromLineToFace(normal4D * alg::dot(normal4D, faceVertex1 - lineVertex1));
	glm::vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	glm::vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1, distance2;
	get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1);
	get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2);
	glm::vec4 intersectFacePoint;
	if (distance1 > 0.f)intersectFacePoint = glm::mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2));
	else intersectFacePoint = (lineVertexShifted1 + lineVertexShifted2) / 2.f;
	*contactPosA = intersectFacePoint - shiftFromLineToFace;
	*contactPosB = intersectFacePoint;
}

static bool is_in_triangle(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c)
{
	glm::vec4 ca(alg::normalize(c - a)), ab(alg::normalize(a - b)), bc(alg::normalize(b - c));
	glm::vec4 n1(b - a - ca * alg::dot(ca, b - a));
	glm::vec4 n2(c - b - ab * alg::dot(ab, c - b));
	glm::vec4 n3(a - c - bc * alg::dot(bc, a - c));
	return alg::dot(E - a, n1) >= 0.f && alg::dot(E - b, n2) >= 0.f && alg::dot(E - c, n3) >= 0.f;
}

static bool is_in_square(glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c)
{
	return is_in_triangle(E, a, b, c) || is_in_triangle(E, c, c + a - b, a);
}

static bool is_edge_in_face(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 faceVertex1, glm::vec4 faceVertex2, glm::vec4 faceVertex3,glm::vec4* contactPos4D)
{
	glm::vec4 shiftFromLineToFace(normal4D * alg::dot(normal4D, faceVertex1 - lineVertex1));
	glm::vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	glm::vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1,distance2;
	glm::vec4 normal1(get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3,&distance1));
	glm::vec4 normal2(get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3,&distance2));
	glm::vec4 intersectPoint(glm::mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2)));
	*contactPos4D = intersectPoint - shiftFromLineToFace;
	return alg::dot(normal1, normal2)<0.f && is_in_triangle(intersectPoint, faceVertex1, faceVertex2, faceVertex3)&& distance1!=distance2;
}

static bool is_edge_in_face(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 faceVertex1, glm::vec4 faceVertex2, glm::vec4 faceVertex3)
{
	glm::vec4 shiftFromLineToFace(normal4D * alg::dot(normal4D, faceVertex1 - lineVertex1));
	glm::vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	glm::vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1, distance2;
	glm::vec4 normal1(get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1));
	glm::vec4 normal2(get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2));
	glm::vec4 intersectPoint(distance1 + distance2==0.f? (lineVertexShifted1 + lineVertexShifted2)/2.f:glm::mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2)));
	return alg::dot(normal1, normal2) < 0.f && is_in_triangle(intersectPoint, faceVertex1, faceVertex2, faceVertex3);
}

static bool is_edge_in_square(glm::vec4 normal4D, glm::vec4 lineVertex1, glm::vec4 lineVertex2, glm::vec4 a, glm::vec4 b, glm::vec4 c)
{
	return is_edge_in_face(normal4D, lineVertex1, lineVertex2, a, b, c) || is_edge_in_face(normal4D, lineVertex1, lineVertex2, c, c + a - b, a);
}

//static bool is_vertex_in_cube(glm::vec4 normal4D, glm::vec4 E, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d)
//{
//	glm::vec4 center((b + c + d - a) / 2.f);
//	glm::vec4 bc();
//}

//E camPos

static float get_tetra_height(glm::vec4 E, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	glm::vec4 normal4D(alg::normalize(cross4d(A - B, A - C, A - D)));
	float l(alg::dot(normal4D, E - A));
	float t(l / alg::dot(-normal4D, glm::vec4(0.f,-1.f,0.f,0.f)));
	return E.y - t;
}

static float get_tetra_height(glm::vec4 E, glm::vec4 normal4D,glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	float l(alg::dot(normal4D, E - A));
	float t(l / alg::dot(-normal4D, glm::vec4(0.f, -1.f, 0.f, 0.f)));
	return E.y - t;
}

static float get_tetra_height(glm::vec4 E, glm::vec4* normal4D, float* t, glm::vec4 normal4D2, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	*normal4D = normal4D2;
	float dis(alg::dot(normal4D2, E - A));
	*t = dis / alg::dot(-normal4D2, glm::vec4(0.f, -1.f, 0.f, 0.f));//distance/cos
	return E.y - *t;
}

static glm::vec4 get_ray_detect_tetra_pos(glm::vec4 cameraPos, glm::vec4 forward,glm::vec4 normal4D, glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D)
{
	float l(alg::dot(normal4D, cameraPos - A));
	float t(l / alg::dot(-normal4D, forward));
	return cameraPos + forward * t;
}

static bool point_col_terrain_tetra4D(glm::vec4 position4d,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPos,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4)
{
	bool isCol(false);
	float depth0(-alg::dot(position4d - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		glm::vec4 contactPos0(position4d + depth0 * normal4D0);
		if (is_in_tetra(contactPos0,*normal4D, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_terrain_tetra4D(glm::vec4 spherePos4D, float radius,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPosA, glm::vec4* contactPosB)
{
	bool isCol(false);
	float depth0(radius - alg::dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		glm::vec4 contactPosB0(spherePos4D - (radius - depth0) * normal4D0);
		glm::vec4 contactPosA0(spherePos4D - radius * normal4D0);
		if (is_in_tetra(contactPosB0, normal4D0, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPosA = contactPosA0;
			*contactPosB = contactPosB0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_tetra4D(glm::vec4 spherePos4D, float radius,
	glm::vec4 normal4D0,
	glm::vec4 vertex4D1,
	glm::vec4 vertex4D2,
	glm::vec4 vertex4D3,
	glm::vec4 vertex4D4,
	float* depth, glm::vec4* normal4D, glm::vec4* contactPosA, glm::vec4* contactPosB)
{
	bool isCol(false);
	float depth0(radius - alg::dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f && depth0 < radius)
	{
		glm::vec4 contactPosB0(spherePos4D - (radius - depth0) * normal4D0);
		glm::vec4 contactPosA0(spherePos4D - radius * normal4D0);
		if (is_in_tetra4(contactPosB0, normal4D0,vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPosA = contactPosA0;
			*contactPosB = contactPosB0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_face4D(glm::vec4 spherePos4D, float radius, glm::vec4 vertex4D1, glm::vec4 vertex4D2, glm::vec4 vertex4D3,float* depth,glm::vec4* normal4D,glm::vec4* contactPosA, glm::vec4* contactPosB)
{
	bool isCol(false);
	glm::vec4 normal4D0(get_normal_from_point_and_face(spherePos4D, vertex4D1, vertex4D2, vertex4D3));
	float depth0(radius - alg::dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		glm::vec4 contactPosB0(spherePos4D - (radius - depth0) * normal4D0);
		glm::vec4 contactPosA0(spherePos4D - radius * normal4D0);
		if (is_in_triangle(contactPosB0, vertex4D1, vertex4D2, vertex4D3))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPosA = contactPosA0;
			*contactPosB = contactPosB0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_line4D(glm::vec4 spherePos4D, float radius, glm::vec4 vertex4D1, glm::vec4 vertex4D2, float* depth, glm::vec4* normal4D, glm::vec4* contactPosA, glm::vec4* contactPosB)
{
	bool isCol(false);
	glm::vec4 normal4D0(alg::normalize(spherePos4D - vertex4D1 - alg::normalize(vertex4D2 - vertex4D1) * alg::dot(alg::normalize(vertex4D2 - vertex4D1), spherePos4D - vertex4D1)));
	float depth0(radius - alg::dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		glm::vec4 contactPosB0(spherePos4D - (radius - depth0) * normal4D0);
		glm::vec4 contactPosA0(spherePos4D - radius * normal4D0);
		if (alg::dot(vertex4D1 - contactPosB0, vertex4D2 - contactPosB0)<0.f)
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPosA = contactPosA0;
			*contactPosB = contactPosB0;
			isCol = true;
		}
	}
	return isCol;
}

static bool sphere_col_point4D(glm::vec4 spherePos4D, float radius, glm::vec4 vertex4D, float* depth, glm::vec4* normal4D, glm::vec4* contacts)
{
	bool isCol(false);
	glm::vec4 normal4D0(alg::normalize(spherePos4D - vertex4D));
	float depth0(radius - alg::dot(spherePos4D - vertex4D, normal4D0));
	if (depth0 > 0.f)
	{
		glm::vec4 contacts0(spherePos4D - radius * normal4D0);
		*depth = depth0;
		*normal4D = normal4D0;
		*contacts = contacts0;
		isCol = true;
	}
	return isCol;
}

static bool get_ray_detect_tetra_distance(glm::vec4 cameraPos, glm::vec4 forward, glm::vec4 normal4D , glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 D, float* t)
{
	bool isCol(false);
	if (alg::dot(forward, normal4D) < 0.f)
	{
		float l(alg::dot(normal4D, cameraPos - A));
		float t2(-l / alg::dot(normal4D, forward));
		if (t2 < *t&& t2 > 0.f)
		{
			glm::vec4 hitPos0(cameraPos + forward * t2);
			if (is_in_tetra4(hitPos0, normal4D, A, B, C, D))
			{
				//std::cout<<"is in tetra"<<"\n";
				*t = t2;
				isCol = true;
			}
		}
	}
	return isCol;
}

//x=0,y=1,z=2,w=3,-x=4,-y=5,-z=6,-w=7
//a direction
static bool col_plane4D(glm::vec4 startPos4D, glm::vec4 endPos4D, glm::vec4 planePos4D, glm::vec4 planeScale4D, float* t, glm::vec4* hitNormal, const unsigned int a)
{
	bool isCol(false);
	unsigned int a2;
	float sign;
	if (a > 3)a2 = a - 4,sign = -1.f;
	else a2 = a,sign = 1.f;
	glm::vec4 normal4D(glm::vec4(0.f));
	normal4D[a2] = a > 3 ? -1.f : 1.f;
	if ((startPos4D[a2] - endPos4D[a2]) * normal4D[a2] > 0.f)
	{
		if ((startPos4D[a2] - planePos4D[a2]) * (endPos4D[a2] - planePos4D[a2]) < 0.f)
		{
			unsigned int b2, c2, d2;
			if (a2 == 0)b2 = 1, c2 = 2, d2 = 3;
			else if (a2 == 1)b2 = 0, c2 = 2, d2 = 3;
			else if (a2 == 2)b2 = 0, c2 = 1, d2 = 3;
			else if (a2 == 3)b2 = 0, c2 = 1, d2 = 2;
			glm::vec4 rcolPos4D (startPos4D + (endPos4D - startPos4D) * (planePos4D[a2] - startPos4D[a2]) / (endPos4D[a2] - startPos4D[a2]) - planePos4D);
			isCol =
				alg::abs(rcolPos4D[b2]) <= planeScale4D[b2] / 2.f &&
				alg::abs(rcolPos4D[c2]) <= planeScale4D[c2] / 2.f &&
				alg::abs(rcolPos4D[d2]) <= planeScale4D[d2] / 2.f;
			if (isCol)
			{
				//std::cout << "hit" << "\n";
				glm::vec4 hitPos(rcolPos4D + planePos4D);
				float t2(alg::length(startPos4D - hitPos));
				if (t2 < *t)
				{
					//std::cout << "alg::length of ray=" << alg::length(startPos4D - hitPos) << "\n";
					*t = t2;
					*hitNormal = normal4D;
				}
			}
		}
	}
	return isCol;
}

static bool line_sigment_detect_box4D(glm::vec4 startPos4D, glm::vec4 endPos4D, glm::vec4 scale4D, float* t, glm::vec4* hitNormal)
{
	unsigned int a2;
	float sign;
	for (int i(0); i < 8; i++)
	{
		if (i > 3)a2 = i - 4,sign = -1.f;
		else a2 = i,sign = 1.f;
		glm::vec4 planePos4D(glm::vec4(0.f));
		planePos4D[a2] = sign * scale4D[a2] / 2.f;
		if (col_plane4D(startPos4D, endPos4D, planePos4D, scale4D, t, hitNormal, i))
		{
			return true;
		}
	}
	return false;
}

static void vertices_used(float distance,glm::vec4 vertexPos4D,glm::vec4 normal0,glm::vec4 objectPosition4D, std::vector<glm::vec4>* vertices4D)
{
	if(distance<0.01f)
	{
		bool isAdd(true);
		for (int j(0); j < vertices4D->size(); j++)
		{
			if ((*vertices4D)[j] == vertexPos4D)
			{
				isAdd = false;
			}
		}
		if (isAdd)
			vertices4D->push_back(vertexPos4D);
	}
}

static void edges_used(glm::vec2 distances, Edge4D edge4D, glm::vec4 normal0, glm::vec4 objectPosition4D, std::vector<Edge4D>* edges4D)
{
	if (distances[0] < 0.01f &&
		distances[1] < 0.01f)
	{
		bool isAdd(true);
		for (int j(0); j < edges4D->size(); j++)
		{
			if (((*edges4D)[j].vertices4D[0] == edge4D.vertices4D[0] && (*edges4D)[j].vertices4D[1] == edge4D.vertices4D[1]) ||
				((*edges4D)[j].vertices4D[0] == edge4D.vertices4D[1] && (*edges4D)[j].vertices4D[1] == edge4D.vertices4D[0]))
			{
				isAdd = false;
			}
		}
		if (isAdd)
			edges4D->push_back(edge4D);
	}
}

static void faces_used(glm::vec3 distances, Face4D face4D, glm::vec4 normal0, glm::vec4 objectPosition4D, std::vector<Face4D>* faces4D)
{
	if (distances[0] < 0.01f &&
		distances[1] < 0.01f &&
		distances[2] < 0.01f)
	{
		bool isAdd(true);
		for (int j(0); j < faces4D->size(); j++)
		{
			if (((*faces4D)[j].vertices4D[0] == face4D.vertices4D[0] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[1] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[2]) ||
				((*faces4D)[j].vertices4D[0] == face4D.vertices4D[0] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[2] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[1]) ||
				((*faces4D)[j].vertices4D[0] == face4D.vertices4D[1] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[0] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[2]) ||
				((*faces4D)[j].vertices4D[0] == face4D.vertices4D[1] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[2] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[0]) ||
				((*faces4D)[j].vertices4D[0] == face4D.vertices4D[2] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[0] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[1]) ||
				((*faces4D)[j].vertices4D[0] == face4D.vertices4D[2] && (*faces4D)[j].vertices4D[1] == face4D.vertices4D[1] && (*faces4D)[j].vertices4D[2] == face4D.vertices4D[0]))
			{
				isAdd = false;
			}
		}
		if (isAdd)
			faces4D->push_back(face4D);
	}
}

static void tetras_used(glm::vec4 distances, Tetra4D tetra4D, glm::vec4 normal0, glm::vec4 objectPosition4D, std::vector<Tetra4D>* tetras4D)
{
	if (distances[0] < 0.01f &&
		distances[1] < 0.01f &&
		distances[2] < 0.01f &&
		distances[3] < 0.01f)
	{
		tetras4D->push_back(tetra4D);
	}
}

static bool isConstLength;
static glm::vec4 buildingPos4D;
static float hitLengthHorizontal;

static glm::vec4 get_build_position4D(glm::vec4 cameraPos, glm::vec4 forward, glm::vec4 hittingPos,bool isShift)
{
	if (isShift) 
	{
		if (!isConstLength) {
			glm::vec4 RelativeHitPos(hittingPos - cameraPos);
			hitLengthHorizontal = alg::length(glm::vec3(RelativeHitPos.x, RelativeHitPos.z, RelativeHitPos.w));
			isConstLength = true;
		}
		
		float buildLengthHorizontal0 = alg::length(glm::vec3(forward.x, forward.z, forward.w));
		buildingPos4D = cameraPos + forward * hitLengthHorizontal / buildLengthHorizontal0;
	}
	if (!isShift)
	{
		buildingPos4D = hittingPos;
		isConstLength = false;
	}
	return buildingPos4D;
}

//static glm::vec4 get_wall_build_position4D(glm::vec4 hittingPos) 
//{
//	glm::vec3 gridPosXZW = glm::vec3(floor(hittingPos.x), floor(hittingPos.z), floor(hittingPos.w));
//	glm::vec3 relativeInGridPosXZW = glm::vec3(hittingPos.x-0.5f, hittingPos.z-0.5f , hittingPos.w-0.5f) - gridPosXZW;
//	if (relativeInGridPosXZW.x > 0 && alg::abs(relativeInGridPosXZW.y) < relativeInGridPosXZW.x && alg::abs(relativeInGridPosXZW.z) < relativeInGridPosXZW.x)
//	{
//		wallPos4D= glm::vec4(floor(hittingPos.x) + 0.9f,floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f,floor(hittingPos.z) + 0.5f,floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(0.2f, 0.75f, 1.f, 1.f);
//	}
//	if (relativeInGridPosXZW.x < 0 && alg::abs(relativeInGridPosXZW.y) > relativeInGridPosXZW.x && alg::abs(relativeInGridPosXZW.z) > relativeInGridPosXZW.x)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.1f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(0.2f, 0.75f, 1.f, 1.f);
//	}
//	if (relativeInGridPosXZW.y > 0 && alg::abs(relativeInGridPosXZW.x) < relativeInGridPosXZW.y && alg::abs(relativeInGridPosXZW.z) < relativeInGridPosXZW.y)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.9f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 0.2f, 1.f);
//	}
//	if (relativeInGridPosXZW.y < 0 && alg::abs(relativeInGridPosXZW.x) > relativeInGridPosXZW.y && alg::abs(relativeInGridPosXZW.z) > relativeInGridPosXZW.y)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.1f, floor(hittingPos.w) + 0.5f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 0.2f, 1.f);
//	}
//	if (relativeInGridPosXZW.z > 0 && alg::abs(relativeInGridPosXZW.x) < relativeInGridPosXZW.z && alg::abs(relativeInGridPosXZW.y) < relativeInGridPosXZW.z)
//	{
//		wallPos4D = glm::vec4(floor(hittingPos.x) + 0.5f, floor(hittingPos.y * 4.f) / 4.f + 0.75f / 2.f, floor(hittingPos.z) + 0.5f, floor(hittingPos.w) + 0.9f);
//		wallScale4D = glm::vec4(1.f, 0.75f, 1.f, 0.2f);
//	}
//	if (relativeInGridPosXZW.z < 0 && alg::abs(relativeInGridPosXZW.x) > relativeInGridPosXZW.z && alg::abs(relativeInGridPosXZW.y) > relativeInGridPosXZW.z)
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

//static glm::vec4 get_build_position4D(glm::vec4 hittingPos)
//{
//}

//static glm::vec4 get_cap_scale4D()
//{
//	return wallScale4D;
//}

static float luma(glm::vec3 color) {
	return alg::dot(color, glm::vec3(0.333333f));
}

static float get_exposure(glm::vec3 avgColor, float* currentExposure, float exposureSpeed, float exposureMultiplier, const float dt)
{
	float avgExp(luma(avgColor));

	float nightVision(0.f);
	float avgBrightness(glm::clamp(avgExp, 0.00003051757f, 65000.0f));
	float targetExposure(glm::clamp(0.022f / (1.f - 2.f / (log(avgBrightness * 2.f + 1.f) / log(10.f) + 2.f)), 0.f, 6.f));

	float rad(sqrt(*currentExposure));
	float rtarget(sqrt(targetExposure));
	float dir(glm::sign(rtarget - rad));
	float dist(alg::abs(rtarget - rad));
	if (alg::abs(*currentExposure - targetExposure) < 0.015f)exposureSpeed /= 8.f;
	else if (alg::abs(*currentExposure - targetExposure) < 0.04f)exposureSpeed /= 2.5f;
	float maxApertureChange(0.0032f * dt / 0.016666f * exposureSpeed * exp2(alg::max(rad, rtarget) * 0.5f));

	maxApertureChange *= 1.f + nightVision * 4.f;
	rad = rad + dir * alg::min(dist, maxApertureChange);

	float exposureF(rad * rad);
	float exposure(exposureF * exposureMultiplier);
	*currentExposure = exposure;
	return exposure;
}

