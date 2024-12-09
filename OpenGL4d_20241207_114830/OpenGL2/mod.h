#pragma once
#include<mat4x4.hpp>
#include"vec4.h"
#include"trivec4.h"
#include"bivec4.h"
#include"quadvec4.h"
#include"rotor4.h"
//vec4

namespace alg
{
	static float max(float x, float y)
	{
		return x > y ? x : y;
	}

	static int max(int x, int y)
	{
		return x > y ? x : y;
	}

	static glm::vec3 max(glm::vec3 x, glm::vec3 y)
	{
		return glm::vec3(max(x.x, y.x), max(x.y, y.y), max(x.z, y.z));
	}

	static float min(float x, float y)
	{
		return x < y ? x : y;
	}

	static int min(int x, int y)
	{
		return x < y ? x : y;
	}

	static float abs(float x)
	{
		return x > 0.f ? x : -x;
	}

	static glm::vec4 abs(glm::vec4 x)
	{
		return glm::vec4(alg::abs(x.x), alg::abs(x.y), alg::abs(x.z), alg::abs(x.w));
	}

	static int abs(int x)
	{
		return x > 0 ? x : -x;
	}

	static float fmod(float x, float y)
	{
		return x - int(x / y) * y;
	}

	static float fract(float x)
	{
		return x - int(x);
	}

	static float sign(float x)
	{
		return x > 0.f ? 1.f : -1.f;
	}

	static int sign(int x)
	{
		return x > 0 ? 1 : -1;
	}

	static glm::vec4 sign(glm::vec4 x)
	{
		return glm::vec4(alg::sign(x.x), alg::sign(x.y), alg::sign(x.z), alg::sign(x.w));
	}

	static float clamp(float x, float y, float z)
	{
		return x < y ? y : x > z ? z : x;
	}

	static int clamp(int x, int y, int z)
	{
		return x < y ? y : x > z ? z : x;
	}

	static int inverse_clamp(int x, int y, int z)
	{
		return x < y ? z : x > z ? y : x;
	}

	static float length(glm::vec2 x)
	{
		return sqrt(x.x * x.x + x.y * x.y);
	}

	static float length(glm::vec3 x)
	{
		return sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
	}

	static float length(glm::vec4 x)
	{
		return sqrt(x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w);
	}

	static glm::vec2 normalize(glm::vec2 x)
	{
		return x / alg::length(x);
	}

	static glm::vec3 normalize(glm::vec3 x)
	{
		return x / alg::length(x);
	}

	static glm::vec4 normalize(glm::vec4 x)
	{
		return x / alg::length(x);
	}

	static float dot(glm::vec3 x, glm::vec3 y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}

	static float dot(glm::vec4 x, glm::vec4 y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
	}
}

static alg::vec4 left_contract_bv(alg::vec4 v, alg::bivec4 b){
	return
		alg::vec4(
			-v.y * b.xy - v.z * b.xz - v.w * b.xw,
			v.x * b.xy - v.z * b.yz - v.w * b.yw,
			v.x * b.xz + v.y * b.yz - v.w * b.zw,
			v.x * b.xw + v.y * b.yw + v.z * b.zw
		);
}

static alg::trivec4 wedge_bv(alg::vec4 v, alg::bivec4 b){
	return
		alg::trivec4(
			v.x * b.yz - v.y * b.xz + v.z * b.xy,
			v.x * b.yw - v.y * b.xw + v.w * b.xy,
			v.x * b.zw - v.z * b.xw + v.w * b.xz,
			v.x * b.zw - v.z * b.yw + v.w * b.yz);
}

static alg::bivec4 wedge_v(alg::vec4 u, alg::vec4 v) {
	return
		alg::bivec4(
			u.x * v.y - u.y * v.x,
			u.x * v.z - u.z * v.x,
			-u.w * v.x + u.x * v.w,
			u.y * v.z - u.z * v.y,
			-u.w * v.y + u.y * v.w,
			-u.w * v.z + u.z * v.w
		);
}

static std::pair<alg::vec4 ,alg::trivec4> mul_bv(alg::vec4 v, alg::bivec4 b)
{
	return { left_contract_bv(v, b), wedge_bv(v, b) };
}

//bivec4
static alg::vec4 dot_v(alg::bivec4 b,alg::vec4 v)
{
	return alg::vec4(
		b.xw * v.w + b.xy * v.y + b.xz * v.z,
		-b.xy * v.x + b.yw * v.w + b.yz * v.z,
		-b.xz * v.x - b.yz * v.y + b.zw * v.w,
		-b.xw * v.x - b.yw * v.y - b.zw * v.z
	);
}

static alg::trivec4 wedge_v(alg::bivec4 b, alg::vec4 v)
{
	return alg::trivec4(
		b.xy * v.z - b.xz * v.y + b.yz * v.x,
		-b.xw * v.y + b.xy * v.w + b.yw * v.x,
		-b.xw * v.z + b.xz * v.w + b.zw * v.x,
		-b.yw * v.z + b.yz * v.w + b.zw * v.y
	);
}

static std::pair<alg::vec4,alg::trivec4> mul_v(alg::bivec4 b, alg::vec4 v)
{
	return { dot_v(b, v) ,wedge_v(b,v) };
}

static float mul_bv_s(alg::bivec4 b, alg::bivec4 c)
{
	return 
		-b.xy * c.xy
		- b.xz * c.xz
		- b.xw * c.xw
		- b.yz * c.yz
		- b.yw * c.yw
		- b.zw * c.zw;
}

static alg::bivec4 mul_bv_b(alg::bivec4 b, alg::bivec4 c)
{
	return
		alg::bivec4(
			-b.xw * c.yw - b.xz * c.yz + b.yw * c.xw + b.yz * c.xz,
			-b.xw * c.zw + b.xy * c.yz - b.yz * c.xy + b.zw * c.xw,
			b.xy * c.yw + b.xz * c.zw - b.yw * c.xy - b.zw * c.xz,
			-b.xy * c.xz + b.xz * c.xy - b.yw * c.zw + b.zw * c.yw,
			b.xw * c.xy - b.xy * c.xw + b.yz * c.zw - b.zw * c.yz,
			b.xw * c.xz - b.xz * c.xw + b.yw * c.yz - b.yz * c.yw
		);
}

static alg::quadvec4 mul_bv_q(alg::bivec4 b, alg::bivec4 c)
{
	return
		alg::quadvec4(
			b.xw * c.yz
			+ b.xy * c.zw
			- b.xz * c.yw
			- b.yw * c.xz
			+ b.yz * c.xw
			+ b.zw * c.xy);
}

static alg::rotor4 mul_bv(alg::bivec4 b,alg::bivec4 c)
{
	return alg::rotor4(mul_bv_s(b,c), mul_bv_b(b,c), mul_bv_q(b,c));
}

static std::pair<alg::bivec4,alg::bivec4> decompose(alg::bivec4 b) {
	alg::quadvec4 posHalfXYZW(alg::quadvec4(0.5));
	alg::quadvec4 negHalfXYZW(alg::quadvec4(-0.5));
	return { b * 0.5f + posHalfXYZW.mul_bv(b) ,b * 0.5f + negHalfXYZW.mul_bv(b) };
}


static alg::rotor4 exp(alg::bivec4 b){
	alg::bivec4 bPlus;
	alg::bivec4 bMinus;
	std::tie(bPlus, bMinus) = decompose(b);
	float thetaPlus(2.f * sqrt(bPlus.xy* bPlus.xy + bPlus.xz* bPlus.xz + bPlus.xw* bPlus.xw));
	float thetaMinus(2.f * sqrt(bMinus.xy* bMinus.xy + bMinus.xz* bMinus.xz + bMinus.xw* bMinus.xw));

	float invThetaPlus(thetaPlus > 0.f?1.f / thetaPlus:0.f);
	float invThetaMinus(thetaMinus > 0.f?1.f / thetaMinus:0.f);

	alg::bivec4 unitBPlus(bPlus * invThetaPlus);
	alg::bivec4 unitBMinus(bMinus * invThetaMinus);
	float cosThetaPlus(cos(thetaPlus));
	float cosThetaMinus(cos(thetaMinus));
	return alg::rotor4(
		0.5f * (cosThetaPlus + cosThetaMinus),
		unitBPlus * sin(thetaPlus) + unitBMinus * sin(thetaMinus),
		alg::quadvec4(0.5f * (cosThetaPlus - cosThetaMinus))
	);
}
//trivec4
static alg::vec4 right_contract_bv(alg::trivec4 t, alg::bivec4 b){
	return alg::vec4(
			-b.yw * t.xyw - b.yz * t.xyz - b.zw * t.xzw,
			b.xw * t.xyw + b.xz * t.xyz - b.zw * t.yzw,
			b.xw * t.xzw - b.xy * t.xyz + b.yw * t.yzw,
			-b.xy * t.xyw - b.xz * t.xzw - b.yz * t.yzw
			);
}

static alg::vec4 mul_qv(alg::trivec4 t, alg::quadvec4 q)
{
	float xyzw(q.xyzw);
	return alg::vec4(xyzw * t.yzw,-xyzw * t.xzw,xyzw * t.xyw,-xyzw * t.xyz);
}
//quadvec4
static alg::trivec4 mul_v(alg::quadvec4 q, alg::vec4 v)
{
	return alg::trivec4(q.xyzw * v.w, -q.xyzw * v.z,q.xyzw * v.y,-q.xyzw * v.x);
}

static alg::bivec4 mul_bv(alg::quadvec4 q, alg::bivec4 b)
{
	float xyzw(q.xyzw);
	return alg::bivec4(-b.zw * xyzw,b.yw * xyzw,-b.yz * xyzw,-b.xw * xyzw,b.xz * xyzw,-b.xy * xyzw);
}
//rotor4
static alg::vec4 rotate(alg::rotor4 r, alg::vec4 v)
{
	// p = R v ~R. We do this in two steps:
	// Q = R v
	alg::vec4 a1;
	alg::trivec4 a3;
	std::tie(a1, a3) = mul_v(r.b, v);

	alg::trivec4 b3(mul_v(r.q,v));
	alg::vec4 q1(v * r.s + a1);
	alg::trivec4 q3(a3 + b3);

	// p = Q ~R
	alg::bivec4 bRev(r.b.reverse());
	alg::vec4 p(q1* r.s + left_contract_bv(q1,bRev) + right_contract_bv(q3,bRev) + mul_qv(q3,r.q));
	return p;
}

static glm::mat4 to_matrix(alg::rotor4 r)
{
	alg::vec4 x = rotate(r, alg::vec4(1.f, 0.f, 0.f, 0.f));
	alg::vec4 y = rotate(r, alg::vec4(0.f, 1.f, 0.f, 0.f));
	alg::vec4 z = rotate(r, alg::vec4(0.f, 0.f, 1.f, 0.f));
	alg::vec4 w = rotate(r, alg::vec4(0.f, 0.f, 0.f, 1.f));

	return glm::mat4(
		x.x, x.y, x.z, x.w,
		y.x, y.y, y.z, y.w,
		z.x, z.y, z.z, z.w,
		w.x, w.y, w.z, w.w
		);
}

static alg::rotor4 mul_bv(alg::rotor4 r, alg::bivec4 c)
{
	return alg::rotor4(mul_bv_s(r.b, c), c * r.s + mul_bv_b(r.b, c) + mul_bv(r.q, c), mul_bv_q(r.b, c));
}

static std::pair<alg::rotor4,alg::rotor4> decompose(alg::rotor4 r)
{
	alg::quadvec4 posHalfXYZW(alg::quadvec4(0.5f));
	alg::quadvec4 negHalfXYZW(alg::quadvec4(-0.5f));

	alg::rotor4 rPlus(alg::rotor4(
		0.5f * (1.f + r.s + r.q.xyzw),
		r.b * 0.5f + posHalfXYZW.mul_bv(r.b),
		r.q * 0.5f + posHalfXYZW * r.s + negHalfXYZW
	));

	alg::rotor4 rMinus(alg::rotor4(
		0.5f*(1.f + r.s - r.q.xyzw),
		r.b * 0.5f + negHalfXYZW.mul_bv(r.b),
		r.q * 0.5f + negHalfXYZW * r.s + posHalfXYZW
	));
	return { rPlus, rMinus };
}

static alg::rotor4 normalize(alg::rotor4 r) {
	// we decompose into two isoclinic rotations, which are each equivalent
	// to a quaternion. Each quaternion component is normalised, and then we
	// recover the original rotor

	alg::rotor4 rPlus;
	alg::rotor4 rMinus;
	std::tie(rPlus, rMinus) = decompose(r);
	// get rid of the 1/2 (1 +- xyzw) components
	rPlus.s -= 0.5f;
	rMinus.s -= 0.5f;
	// we're going to overwrite the quadvector components since they should
	// be just +- the scalar components.

	float plusMag(2.f * sqrt(rPlus.s * rPlus.s + rPlus.b.xy * rPlus.b.xy + rPlus.b.xz * rPlus.b.xz + rPlus.b.xw* rPlus.b.xw));
	float minusMag(2.f * sqrt(rMinus.s * rMinus.s + rMinus.b.xy * rMinus.b.xy + rMinus.b.xz * rMinus.b.xz + rMinus.b.xw * rMinus.b.xw));

	if (plusMag > 0.f ){
		float invPlusMag(1.f / plusMag);
		float rPlusS(rPlus.s * invPlusMag + 0.5f);
		rPlus.set(rPlusS, rPlus.b * invPlusMag, alg::quadvec4(rPlusS - 1.f));
		// readd 1/2 (1 - xyzw)
	}
	else {
		// TODO:
		// unimplemented!("{:?} has zero magnitude!", rPlus);
		rPlus.set();
	}

	if (minusMag > 0.f ){
		float invMinusMag(1.f / minusMag);
		float rMinusS(rMinus.s * invMinusMag + 0.5f);
		rMinus.set(rMinusS, rMinus.b * invMinusMag, alg::quadvec4(1.f - rMinusS));
		// readd 1/2 (1 + xyzw)
	}
	else {
		// TODO
		// unimplemented!("{:?} has zero magnitude!", rMinus);
		rMinus.set();
	}

	return rPlus * rMinus;
}

static alg::rotor4 update(alg::rotor4 r, alg::bivec4 delta) {
	return normalize(r * exp(delta * -0.5f));
}

static float length(alg::bivec4 b)
{
	return sqrt(b.xy * b.xy + b.xz * b.xz + b.xw * b.xw + b.yz * b.yz + b.yw * b.yw + b.zw * b.zw);
}

static alg::rotor4 angle_to_rotor4(alg::bivec4 RotateAngle4D)
{
	alg::rotor4 rotation4D;
	rotation4D = update(alg::rotor4(), alg::bivec4(glm::radians(RotateAngle4D.xy), 0.f, 0.f, 0.f, 0.f, 0.f));
	rotation4D = update(rotation4D, alg::bivec4(0.f, glm::radians(RotateAngle4D.xz), 0.f, 0.f, 0.f, 0.f));
	rotation4D = update(rotation4D, alg::bivec4(0.f, 0.f, glm::radians(RotateAngle4D.xw), 0.f, 0.f, 0.f));
	rotation4D = update(rotation4D, alg::bivec4(0.f, 0.f, 0.f, glm::radians(RotateAngle4D.yz), 0.f, 0.f));
	rotation4D = update(rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, glm::radians(RotateAngle4D.yw), 0.f));
	rotation4D = update(rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, glm::radians(RotateAngle4D.zw)));
	return rotation4D;
}

static alg::rotor4 look_at(glm::vec4 from,glm::vec4 to,glm::vec4 axis)
{
	glm::vec4 direction4D(normalize(to - from));
	if (alg::abs(dot(direction4D, axis))==1.f)
	{
		return alg::rotor4();
	}
	else
	{
		float cosAngle(dot(axis, direction4D));
		float angle(acos(cosAngle));
		glm::vec4 n(normalize(direction4D - cosAngle * axis));
		alg::bivec4 delta(wedge_v(alg::vec4(axis), alg::vec4(angle * n)));
		return update(alg::rotor4(), delta);
	}
}

static glm::vec4 rotate(alg::bivec4 rotateAngle4D, glm::vec4 v)
{
	alg::rotor4 rotation4D(angle_to_rotor4(rotateAngle4D));
	return rotate(rotation4D, alg::vec4(v)).transform();
}

static float mag(alg::rotor4 r)
{
	return sqrt(r.s * r.s
		+ r.b.xy * r.b.xy
		+ r.b.xz * r.b.xz
		+ r.b.xw * r.b.xw
		+ r.b.yz * r.b.yz
		+ r.b.yw * r.b.yw
		+ r.b.zw * r.b.zw
		+ r.q.xyzw * r.q.xyzw);
}

static float weird_term(alg::rotor4 r) 
{
	return 2.f*( - r.b.xw * r.b.yz - r.b.xy * r.b.zw + r.b.xz * r.b.yw + r.q.xyzw * r.s);
}

static glm::vec4 triple_cross_product(glm::vec4 u, glm::vec4 v, glm::vec4 w)
{
	return mul_qv(wedge_v(wedge_v(alg::vec4(u), alg::vec4(v)), alg::vec4(w)),alg::quadvec4(1.f)).transform();
}
