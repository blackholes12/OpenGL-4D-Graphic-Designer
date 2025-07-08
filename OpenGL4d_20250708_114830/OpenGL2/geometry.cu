#pragma once
#include "object.cu"

__device__ static vec2 cross2d(vec2 a2) {
	return vec2(a2.y, -a2.x);
}

__device__ static vec3 cross3d(vec3 a2, vec3 a3) {
	return vec3(
		a2.y * a3.z - a3.y * a2.z,
		a2.z * a3.x - a3.z * a2.x,
		a2.x * a3.y - a3.x * a2.y
	);
}

__device__ static vec4 cross4d(vec4 a2, vec4 a3, vec4 a4) {
	return vec4(
		a2.y * a3.z * a4.w - a2.y * a3.w * a4.z - a2.z * a3.y * a4.w + a2.z * a3.w * a4.y + a2.w * a3.y * a4.z - a2.w * a3.z * a4.y,
		-a2.x * a3.z * a4.w + a2.x * a3.w * a4.z + a2.z * a3.x * a4.w - a2.z * a3.w * a4.x - a2.w * a3.x * a4.z + a2.w * a3.z * a4.x,
		a2.x * a3.y * a4.w - a2.x * a3.w * a4.y - a2.y * a3.x * a4.w + a2.y * a3.w * a4.x + a2.w * a3.x * a4.y - a2.w * a3.y * a4.x,
		-a2.x * a3.y * a4.z + a2.x * a3.z * a4.y + a2.y * a3.x * a4.z - a2.y * a3.z * a4.x - a2.z * a3.x * a4.y + a2.z * a3.y * a4.x
	);
}

__device__ static void orthonormal_basis(vec4 normal4D, vec4* vec41, vec4* vec42, vec4* vec43)
{
	if (_d_abs(normal4D.x) < 1e-8f && _d_abs(normal4D.y) < 1e-8f && _d_abs(normal4D.z) < 1e-8f)
	{
		*vec41 = vec4(-normal4D.w, 0.f, 0.f, 0.f);
		*vec42 = vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = vec4(0.f, 0.f, 1.f, 0.f);
	}
	else if (_d_abs(normal4D.x) < 1e-8f && _d_abs(normal4D.y) < 1e-8f && _d_abs(normal4D.w) < 1e-8f)
	{
		*vec41 = vec4(normal4D.z, 0.f, 0.f, 0.f);
		*vec42 = vec4(0.f, 1.f, 0.f, 0.f);
		*vec43 = vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (_d_abs(normal4D.x) < 1e-8f && _d_abs(normal4D.z) < 1e-8f && _d_abs(normal4D.w) < 1e-8f)
	{
		*vec41 = vec4(-normal4D.y, 0.f, 0.f, 0.f);
		*vec42 = vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = vec4(0.f, 0.f, 0.f, 1.f);
	}
	else if (_d_abs(normal4D.y) < 1e-8f && _d_abs(normal4D.z) < 1e-8f && _d_abs(normal4D.w) < 1e-8f)
	{
		*vec41 = vec4(0.f, normal4D.x, 0.f, 0.f);
		*vec42 = vec4(0.f, 0.f, 1.f, 0.f);
		*vec43 = vec4(0.f, 0.f, 0.f, 1.f);
	}
	else
	{
		vec4 vA(vec4(0.f, 1.f, 0.f, 0.f));
		if (normal4D.y < 0.f)
			*vec41 = normalize(vA - normal4D * dot(vA, normal4D));
		else if (normal4D.y == 0.f)
			*vec41 = vA*-1.f;
		else
			*vec41 = normalize(vA - normal4D * dot(vA, normal4D))*-1.f;
		vec3 normalXZW(vec3(normal4D.x, normal4D.z, normal4D.w));
		if (_d_abs(normalXZW.y) < 1e-8f && _d_abs(normalXZW.z) < 1e-8f)
		{
			*vec42 = vec4(0.f, 0.f, 1.f, 0.f);
			*vec43 = vec4(0.f, 0.f, 0.f, 1.f);
		}
		else
		{
			vec3 v1(cross3d(vec3(1.f, 0.f, 0.f), normalXZW));
			*vec42 = normalize(vec4(v1.x, 0.f, v1.y, v1.z));
			vec3 v2(cross3d(v1, normalXZW));
			*vec43 = normalize(vec4(v2.x, 0.f, v2.y, v2.z));
		}
	}
}

__device__ static bool is_in_terrain_tetra(vec4 E, vec4 a, vec4 b, vec4 c, vec4 d)
{
	vec3 a2(vec3(a.x, a.z, a.w));
	vec3 b2(vec3(b.x, b.z, b.w));
	vec3 c2(vec3(c.x, c.z, c.w));
	vec3 d2(vec3(d.x, d.z, d.w));
	vec3 n1(cross3d(c2 - b2, b2 - a2));
	vec3 n2(cross3d(d2 - c2, c2 - a2));
	vec3 n3(cross3d(b2 - d2, d2 - a2));
	vec3 n4(cross3d(d2 - b2, b2 - c2));
	vec3 A(vec3(E.x, E.z, E.w) - a2);
	vec3 B(A);
	vec3 C(A);
	vec3 D(vec3(E.x, E.z, E.w) - b2);
	float dis1(dot(A, n1));
	float dis2(dot(B, n2));
	float dis3(dot(C, n3));
	float dis4(dot(D, n4));
	return dis1 < 0.f && dis2 < 0.f && dis3 < 0.f && dis4 < 0.f;
}

__device__ static bool is_in_tetra(vec4 E, vec4 normal4D, vec4 a, vec4 b, vec4 c, vec4 d)
{
	vec3 a2(vec3(a.x, a.z, a.w));
	vec3 b2(vec3(b.x, b.z, b.w));
	vec3 c2(vec3(c.x, c.z, c.w));
	vec3 d2(vec3(d.x, d.z, d.w));
	vec3 n1(cross3d(c2 - b2, b2 - a2));
	vec3 n2(cross3d(d2 - c2, c2 - a2));
	vec3 n3(cross3d(b2 - d2, d2 - a2));
	vec3 n4(cross3d(d2 - b2, b2 - c2));
	vec3 A(vec3(E.x, E.z, E.w) - a2);
	vec3 B(A);
	vec3 C(A);
	vec3 D(vec3(E.x, E.z, E.w) - b2);
	float dis1(dot(A, n1));
	float dis2(dot(B, n2));
	float dis3(dot(C, n3));
	float dis4(dot(D, n4));
	if (normal4D.y > 0.f)return dis1 <= 0.f && dis2 <= 0.f && dis3 <= 0.f && dis4 <= 0.f;
	else return dis1 >= 0.f && dis2 >= 0.f && dis3 >= 0.f && dis4 >= 0.f;
}

__device__ static vec4 get_normal_from_point_and_face(vec4 position4d, vec4 vertex4D1, vec4 vertex4D2, vec4 vertex4D3)
{
	vec4 ve12(normalize(vertex4D2 - vertex4D1));
	vec4 v13(vertex4D3 - vertex4D1);
	vec4 ne12(normalize(v13 - ve12 * dot(v13, ve12)));
	vec4 v1s(position4d - vertex4D1);
	float kv(dot(v1s, ve12));
	float kn(dot(v1s, ne12));
	vec4 closetPosToS(vertex4D1 + ve12 * kv + ne12 * kn);
	return normalize(position4d - closetPosToS);
}

__device__ static vec4 get_distance_and_normal_from_point_and_face(vec4 position4d, vec4 vertex4D1, vec4 vertex4D2, vec4 vertex4D3, float* distance)
{
	vec4 ve12(normalize(vertex4D2 - vertex4D1));
	vec4 v13(vertex4D3 - vertex4D1);
	vec4 ne12(normalize(v13 - ve12 * dot(v13, ve12)));
	vec4 v1s(position4d - vertex4D1);
	float kv(dot(v1s, ve12));
	float kn(dot(v1s, ne12));
	vec4 closetPosToS(vertex4D1 + ve12 * kv + ne12 * kn);
	vec4 normal(position4d - closetPosToS);
	*distance = length(normal);
	return normalize(normal);
}

__device__ static bool is_in_tetra2(vec4 E, vec4 a, vec4 b, vec4 c, vec4 d)
{
	vec4 n1(get_normal_from_point_and_face(d, a, b, c));
	vec4 n2(get_normal_from_point_and_face(a, b, c, d));
	vec4 n3(get_normal_from_point_and_face(b, c, d, a));
	vec4 n4(get_normal_from_point_and_face(c, d, a, b));
	return (dot(E - a, n1) >= 0.f && dot(E - b, n2) >= 0.f && dot(E - c, n3) >= 0.f && dot(E - d, n4) >= 0.f);
}

__device__ static bool is_in_tetra3(vec4 normal4D, vec4 E, vec4 a, vec4 b, vec4 c, vec4 d)
{
	vec4 contactPos0(E + normal4D * dot(normal4D, a - E));
	return is_in_tetra2(contactPos0, a, b, c, d);
}

__device__ static bool is_in_tetra4(vec4 E, vec4 normal4D, vec4 a, vec4 b, vec4 c, vec4 d)
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

__device__ static vec4 get_point_from_edge_and_edge(vec4 vertex4DA1, vec4 vertex4DA2, vec4 vertex4DB1, vec4 vertex4DB2)
{
	vec4 dirB(normalize(vertex4DB2 - vertex4DB1));
	vec4 dirA1ToB1(vertex4DB1 - vertex4DA1);
	vec4 dirA2ToB2(vertex4DB2 - vertex4DA2);
	float distanceA1(length(dirA1ToB1 - dirB * dot(dirB, dirA1ToB1)));
	float distanceA2(length(dirA2ToB2 - dirB * dot(dirB, dirA2ToB2)));
	return (vertex4DA1 * distanceA2 + vertex4DA2 * distanceA1) / (distanceA1 + distanceA2);
}

__device__ static void get_edge_in_face_pos(vec4 normal4D, vec4 lineVertex1, vec4 lineVertex2, vec4 faceVertex1, vec4 faceVertex2, vec4 faceVertex3, vec4* contactPosA, vec4* contactPosB)
{
	vec4 shiftFromLineToFace(normal4D * dot(normal4D, faceVertex1 - lineVertex1));
	vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1, distance2;
	get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1);
	get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2);
	vec4 intersectFacePoint;
	if (distance1 > 0.f)intersectFacePoint = mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2));
	else intersectFacePoint = (lineVertexShifted1 + lineVertexShifted2) / 2.f;
	*contactPosA = intersectFacePoint - shiftFromLineToFace;
	*contactPosB = intersectFacePoint;
}

__device__ static bool is_in_triangle(vec4 E, vec4 a, vec4 b, vec4 c)
{
	vec4 ca(normalize(c - a)), ab(normalize(a - b)), bc(normalize(b - c));
	vec4 n1(b - a - ca * dot(ca, b - a));
	vec4 n2(c - b - ab * dot(ab, c - b));
	vec4 n3(a - c - bc * dot(bc, a - c));
	return dot(E - a, n1) >= 0.f && dot(E - b, n2) >= 0.f && dot(E - c, n3) >= 0.f;
}

__device__ static bool is_in_square(vec4 E, vec4 a, vec4 b, vec4 c)
{
	return is_in_triangle(E, a, b, c) || is_in_triangle(E, c, c + a - b, a);
}

__device__ static bool is_edge_in_face(vec4 normal4D, vec4 lineVertex1, vec4 lineVertex2, vec4 faceVertex1, vec4 faceVertex2, vec4 faceVertex3, vec4* contactPos4D)
{
	vec4 shiftFromLineToFace(normal4D * dot(normal4D, faceVertex1 - lineVertex1));
	vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1, distance2;
	vec4 normal1(get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1));
	vec4 normal2(get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2));
	vec4 intersectPoint(mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2)));
	*contactPos4D = intersectPoint - shiftFromLineToFace;
	return dot(normal1, normal2) < 0.f && is_in_triangle(intersectPoint, faceVertex1, faceVertex2, faceVertex3) && distance1 != distance2;
}

__device__ static bool is_edge_in_face(vec4 normal4D, vec4 lineVertex1, vec4 lineVertex2, vec4 faceVertex1, vec4 faceVertex2, vec4 faceVertex3)
{
	vec4 shiftFromLineToFace(normal4D * dot(normal4D, faceVertex1 - lineVertex1));
	vec4 lineVertexShifted1(lineVertex1 + shiftFromLineToFace);
	vec4 lineVertexShifted2(lineVertex2 + shiftFromLineToFace);
	float distance1, distance2;
	vec4 normal1(get_distance_and_normal_from_point_and_face(lineVertexShifted1, faceVertex1, faceVertex2, faceVertex3, &distance1));
	vec4 normal2(get_distance_and_normal_from_point_and_face(lineVertexShifted2, faceVertex1, faceVertex2, faceVertex3, &distance2));
	vec4 intersectPoint(distance1 + distance2 == 0.f ? (lineVertexShifted1 + lineVertexShifted2) / 2.f : mix(lineVertexShifted1, lineVertexShifted2, distance1 / (distance1 + distance2)));
	return dot(normal1, normal2) < 0.f && is_in_triangle(intersectPoint, faceVertex1, faceVertex2, faceVertex3);
}

__device__ static bool is_edge_in_square(vec4 normal4D, vec4 lineVertex1, vec4 lineVertex2, vec4 a, vec4 b, vec4 c)
{
	return is_edge_in_face(normal4D, lineVertex1, lineVertex2, a, b, c) || is_edge_in_face(normal4D, lineVertex1, lineVertex2, c, c + a - b, a);
}

__device__ static float get_tetra_height(vec4 E, vec4 A, vec4 B, vec4 C, vec4 D)
{
	vec4 normal4D(normalize(cross4d(A - B, A - C, A - D)));
	float l(dot(normal4D, E - A));
	float t(l / dot(normal4D*-1.f, vec4(0.f, -1.f, 0.f, 0.f)));
	return E.y - t;
}

__device__ static float get_tetra_height(vec4 E, vec4 normal4D, vec4 A, vec4 B, vec4 C, vec4 D)
{
	float l(dot(normal4D, E - A));
	float t(l / dot(normal4D*-1.f, vec4(0.f, -1.f, 0.f, 0.f)));
	return E.y - t;
}

__device__ static float get_tetra_height(vec4 E, vec4* normal4D, float* t, vec4 normal4D2, vec4 A, vec4 B, vec4 C, vec4 D)
{
	*normal4D = normal4D2;
	float dis(dot(normal4D2, E - A));
	*t = dis / dot(normal4D2*-1.f, vec4(0.f, -1.f, 0.f, 0.f));//distance/cos
	return E.y - *t;
}

__device__ static vec4 get_ray_detect_tetra_pos(vec4 cameraPos, vec4 forward, vec4 normal4D, vec4 A, vec4 B, vec4 C, vec4 D)
{
	float l(dot(normal4D, cameraPos - A));
	float t(l / dot(normal4D*1.f, forward));
	return cameraPos + forward * t;
}

__device__ static bool point_col_terrain_tetra4D(vec4 position4d,
	float* depth, vec4* normal4D, vec4* contactPos,
	vec4 normal4D0,
	vec4 vertex4D1,
	vec4 vertex4D2,
	vec4 vertex4D3,
	vec4 vertex4D4)
{
	bool isCol(false);
	float depth0(-dot(position4d - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		vec4 contactPos0(position4d + normal4D0 * depth0);
		if (is_in_tetra(contactPos0, *normal4D, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
		{
			*depth = depth0;
			*normal4D = normal4D0;
			*contactPos = contactPos0;
			isCol = true;
		}
	}
	return isCol;
}

__device__ static bool sphere_col_terrain_tetra4D(vec4 spherePos4D, float radius,
	vec4 normal4D0,
	vec4 vertex4D1,
	vec4 vertex4D2,
	vec4 vertex4D3,
	vec4 vertex4D4,
	float* depth, vec4* normal4D, vec4* contactPosA, vec4* contactPosB)
{
	bool isCol(false);
	float depth0(radius - dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		vec4 contactPosB0(spherePos4D - normal4D0 * (radius - depth0));
		vec4 contactPosA0(spherePos4D - normal4D0 * radius);
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

__device__ static bool sphere_col_tetra4D(vec4 spherePos4D, float radius,
	vec4 normal4D0,
	vec4 vertex4D1,
	vec4 vertex4D2,
	vec4 vertex4D3,
	vec4 vertex4D4,
	float* depth, vec4* normal4D, vec4* contactPosA, vec4* contactPosB)
{
	bool isCol(false);
	float depth0(radius - dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f && depth0 < radius)
	{
		vec4 contactPosB0(spherePos4D - normal4D0* (radius - depth0));
		vec4 contactPosA0(spherePos4D - normal4D0* radius);
		if (is_in_tetra4(contactPosB0, normal4D0, vertex4D1, vertex4D2, vertex4D3, vertex4D4))
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

__device__ static bool sphere_col_face4D(vec4 spherePos4D, float radius, vec4 vertex4D1, vec4 vertex4D2, vec4 vertex4D3, float* depth, vec4* normal4D, vec4* contactPosA, vec4* contactPosB)
{
	bool isCol(false);
	vec4 normal4D0(get_normal_from_point_and_face(spherePos4D, vertex4D1, vertex4D2, vertex4D3));
	float depth0(radius - dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		vec4 contactPosB0(spherePos4D - normal4D0* (radius - depth0));
		vec4 contactPosA0(spherePos4D - normal4D0* radius);
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

__device__ static bool sphere_col_line4D(vec4 spherePos4D, float radius, vec4 vertex4D1, vec4 vertex4D2, float* depth, vec4* normal4D, vec4* contactPosA, vec4* contactPosB)
{
	bool isCol(false);
	vec4 normal4D0(normalize(spherePos4D - vertex4D1 - normalize(vertex4D2 - vertex4D1) * dot(normalize(vertex4D2 - vertex4D1), spherePos4D - vertex4D1)));
	float depth0(radius - dot(spherePos4D - vertex4D1, normal4D0));
	if (depth0 > 0.f)
	{
		vec4 contactPosB0(spherePos4D - normal4D0* (radius - depth0));
		vec4 contactPosA0(spherePos4D - normal4D0* radius);
		if (dot(vertex4D1 - contactPosB0, vertex4D2 - contactPosB0) < 0.f)
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

__device__ static bool sphere_col_point4D(vec4 spherePos4D, float radius, vec4 vertex4D, float* depth, vec4* normal4D, vec4* contacts)
{
	bool isCol(false);
	vec4 normal4D0(normalize(spherePos4D - vertex4D));
	float depth0(radius - dot(spherePos4D - vertex4D, normal4D0));
	if (depth0 > 0.f)
	{
		vec4 contacts0(spherePos4D - normal4D0* radius);
		*depth = depth0;
		*normal4D = normal4D0;
		*contacts = contacts0;
		isCol = true;
	}
	return isCol;
}

__device__ static bool get_ray_detect_tetra_distance(vec4 cameraPos, vec4 forward, vec4 normal4D, vec4 A, vec4 B, vec4 C, vec4 D, float* t)
{
	bool isCol(false);
	if (dot(forward, normal4D) < 0.f)
	{
		float l(dot(normal4D, cameraPos - A));
		float t2(-l / dot(normal4D, forward));
		if (t2 < *t && t2 > 0.f)
		{
			vec4 hitPos0(cameraPos + forward * t2);
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
__device__ static bool col_plane4D(vec4 startPos4D, vec4 endPos4D, vec4 planePos4D, vec4 planeScale4D, float* t, vec4* hitNormal, const unsigned int a)
{
	bool isCol(false);
	unsigned int a2;
	float sign;
	if (a > 3)a2 = a - 4, sign = -1.f;
	else a2 = a, sign = 1.f;
	vec4 normal4D(vec4(0.f));
	normal4D.value(a2, a > 3 ? -1.f : 1.f);
	if ((startPos4D[a2] - endPos4D[a2]) * normal4D[a2] > 0.f)
	{
		if ((startPos4D[a2] - planePos4D[a2]) * (endPos4D[a2] - planePos4D[a2]) < 0.f)
		{
			unsigned int b2, c2, d2;
			if (a2 == 0)b2 = 1, c2 = 2, d2 = 3;
			else if (a2 == 1)b2 = 0, c2 = 2, d2 = 3;
			else if (a2 == 2)b2 = 0, c2 = 1, d2 = 3;
			else if (a2 == 3)b2 = 0, c2 = 1, d2 = 2;
			vec4 rcolPos4D(startPos4D + (endPos4D - startPos4D) * (planePos4D[a2] - startPos4D[a2]) / (endPos4D[a2] - startPos4D[a2]) - planePos4D);
			isCol =
				_d_abs(rcolPos4D[b2]) <= planeScale4D[b2] / 2.f &&
				_d_abs(rcolPos4D[c2]) <= planeScale4D[c2] / 2.f &&
				_d_abs(rcolPos4D[d2]) <= planeScale4D[d2] / 2.f;
			if (isCol)
			{
				//std::cout << "hit" << "\n";
				vec4 hitPos(rcolPos4D + planePos4D);
				float t2(length(startPos4D - hitPos));
				if (t2 < *t)
				{
					//std::cout << "length of ray=" << length(startPos4D - hitPos) << "\n";
					*t = t2;
					*hitNormal = normal4D;
				}
			}
		}
	}
	return isCol;
}

__device__ static bool line_sigment_detect_box4D(vec4 startPos4D, vec4 endPos4D, vec4 scale4D, float* t, vec4* hitNormal)
{
	unsigned int a2;
	float sign;
	for (int i(0); i < 8; i++)
	{
		if (i > 3)a2 = i - 4, sign = -1.f;
		else a2 = i, sign = 1.f;
		vec4 planePos4D(vec4(0.f));
		planePos4D.value(a2, sign * scale4D[a2] / 2.f);
		if (col_plane4D(startPos4D, endPos4D, planePos4D, scale4D, t, hitNormal, i))
		{
			return true;
		}
	}
	return false;
}

__device__ static void vertices_used(float distance, vec4 vertexPos4D, vec4 normal0, vec4 objectPosition4D, vec4* vertices4D, int* sizeOfVertices)
{
	if (*sizeOfVertices < 16) {
		if (distance < 0.01f)
		{
			bool isAdd(true);
			for (int j(0); j < *sizeOfVertices; j++)
			{
				if (vertices4D[j] == vertexPos4D)
				{
					isAdd = false;
				}
			}
			if (isAdd)
				vertices4D[*sizeOfVertices] = vertexPos4D, * sizeOfVertices = *sizeOfVertices + 1;
		}
	}
}

__device__ static void edges_used(vec2 distances, _d_Edge4D edge4D, vec4 normal0, vec4 objectPosition4D, _d_Edge4D* edges4D, int* sizeOfEdges)
{
	if (*sizeOfEdges < 32) {
		if (distances[0] < 0.01f &&
			distances[1] < 0.01f)
		{
			bool isAdd(true);
			for (int j(0); j < *sizeOfEdges; j++)
			{
				if ((edges4D[j].vertices4D[0] == edge4D.vertices4D[0] && edges4D[j].vertices4D[1] == edge4D.vertices4D[1]) ||
					(edges4D[j].vertices4D[0] == edge4D.vertices4D[1] && edges4D[j].vertices4D[1] == edge4D.vertices4D[0]))
				{
					isAdd = false;
				}
			}
			if (isAdd)
				edges4D[*sizeOfEdges] = edge4D; *sizeOfEdges = *sizeOfEdges + 1;
		}
	}
}

__device__ static void faces_used(vec3 distances, _d_Face4D face4D, vec4 normal0, vec4 objectPosition4D, _d_Face4D* faces4D, int* sizeOfFaces)
{
	if (*sizeOfFaces < 24) {
		if (distances[0] < 0.01f &&
			distances[1] < 0.01f &&
			distances[2] < 0.01f)
		{
			bool isAdd(true);
			for (int j(0); j < *sizeOfFaces; j++)
			{
				if ((faces4D[j].vertices4D[0] == face4D.vertices4D[0] && faces4D[j].vertices4D[1] == face4D.vertices4D[1] && faces4D[j].vertices4D[2] == face4D.vertices4D[2]) ||
					(faces4D[j].vertices4D[0] == face4D.vertices4D[0] && faces4D[j].vertices4D[1] == face4D.vertices4D[2] && faces4D[j].vertices4D[2] == face4D.vertices4D[1]) ||
					(faces4D[j].vertices4D[0] == face4D.vertices4D[1] && faces4D[j].vertices4D[1] == face4D.vertices4D[0] && faces4D[j].vertices4D[2] == face4D.vertices4D[2]) ||
					(faces4D[j].vertices4D[0] == face4D.vertices4D[1] && faces4D[j].vertices4D[1] == face4D.vertices4D[2] && faces4D[j].vertices4D[2] == face4D.vertices4D[0]) ||
					(faces4D[j].vertices4D[0] == face4D.vertices4D[2] && faces4D[j].vertices4D[1] == face4D.vertices4D[0] && faces4D[j].vertices4D[2] == face4D.vertices4D[1]) ||
					(faces4D[j].vertices4D[0] == face4D.vertices4D[2] && faces4D[j].vertices4D[1] == face4D.vertices4D[1] && faces4D[j].vertices4D[2] == face4D.vertices4D[0]))
				{
					isAdd = false;
				}
			}
			if (isAdd)
				faces4D[*sizeOfFaces] = face4D; *sizeOfFaces = *sizeOfFaces + 1;
		}
	}
}

__device__ static void tetras_used(vec4 distances, _d_Tetra4D tetra4D, vec4 normal0, vec4 objectPosition4D, _d_Tetra4D* tetras4D, int* sizeOfTetras)
{
	if (*sizeOfTetras < 16) {
		if (distances[0] < 0.01f &&
			distances[1] < 0.01f &&
			distances[2] < 0.01f &&
			distances[3] < 0.01f)
		{
			tetras4D[*sizeOfTetras] = tetra4D; *sizeOfTetras = *sizeOfTetras + 1;
		}
	}
}
