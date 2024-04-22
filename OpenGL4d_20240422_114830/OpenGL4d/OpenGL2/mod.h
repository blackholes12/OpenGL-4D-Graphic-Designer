#pragma once
#include<mat4x4.hpp>
#include"vec4.h"
#include"trivec4.h"
#include"bivec4.h"
#include"quadvec4.h"
#include"rotor4.h"
//vec4
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

static alg::rotor4 mul_bv(alg::bivec4 b,alg::bivec4 c)
{
	float s2;
	alg::bivec4 d2;
	alg::quadvec4 q2;
	s2 =
		-b.xy * c.xy
		- b.xz * c.xz
		- b.xw * c.xw
		- b.yz * c.yz
		- b.yw * c.yw
		- b.zw * c.zw;
	d2 = alg::bivec4(
			-b.xw * c.yw - b.xz * c.yz + b.yw * c.xw + b.yz * c.xz,
			-b.xw * c.zw + b.xy * c.yz - b.yz * c.xy + b.zw * c.xw,
			b.xy * c.yw + b.xz * c.zw - b.yw * c.xy - b.zw * c.xz,
			-b.xy * c.xz + b.xz * c.xy - b.yw * c.zw + b.zw * c.yw,
			b.xw * c.xy - b.xy * c.xw + b.yz * c.zw - b.zw * c.yz,
			b.xw * c.xz - b.xz * c.xw + b.yw * c.yz - b.yz * c.yw
	);
	q2 = alg::quadvec4(
		b.xw * c.yz
		+ b.xy * c.zw
		- b.xz * c.yw
		- b.yw * c.xz
		+ b.yz * c.xw
		+ b.zw * c.xy);
	return alg::rotor4(s2,d2,q2);
}

static std::pair<alg::bivec4,alg::bivec4> decompose(alg::bivec4 b) {
	alg::quadvec4 posHalfXYZW = alg::quadvec4(0.5);
	alg::quadvec4 negHalfXYZW = alg::quadvec4(-0.5);
	return { b * 0.5 + posHalfXYZW.mul_bv(b) ,b * 0.5 + negHalfXYZW.mul_bv(b) };
}


static alg::rotor4 exp(alg::bivec4 b){
	alg::bivec4 bPlus;
	alg::bivec4 bMinus;
	std::tie(bPlus, bMinus) = decompose(b);
	float thetaPlus = 2.0 * sqrt(pow(bPlus.xy,2) + pow(bPlus.xz,2) + pow(bPlus.xw,2));
	float thetaMinus = 2.0* sqrt(pow(bMinus.xy, 2) + pow(bMinus.xz, 2) + pow(bMinus.xw, 2));

	float invThetaPlus = thetaPlus > 0.0?1.0 / thetaPlus:0.0;
	float invThetaMinus = thetaMinus > 0.0?1.0 / thetaMinus:0.0;

	alg::bivec4 unitBPlus = bPlus*invThetaPlus ;
	alg::bivec4 unitBMinus = bMinus*invThetaMinus ;

	return alg::rotor4(
		0.5 * cos(thetaPlus) + 0.5 * cos(thetaMinus),
		unitBPlus*sin(thetaPlus)  + unitBMinus*sin(thetaMinus),
		alg::quadvec4(0.5 * cos(thetaPlus) - 0.5 * cos(thetaMinus))
	);
}
//trivec4
static alg::vec4 right_contract_bv(alg::trivec4 t, alg::bivec4 b){
	return
		alg::vec4(
			-b.yw * t.xyw - b.yz * t.xyz - b.zw * t.xzw,
			b.xw * t.xyw + b.xz * t.xyz - b.zw * t.yzw,
			b.xw * t.xzw - b.xy * t.xyz + b.yw * t.yzw,
			-b.xy * t.xyw - b.xz * t.xzw - b.yz * t.yzw
			);
}

static alg::vec4 mul_qv(alg::trivec4 t, alg::quadvec4 q)
{
	float xyzw = q.xyzw;
	return
		alg::vec4(
			xyzw * t.yzw,
			-xyzw * t.xzw,
			xyzw * t.xyw,
			-xyzw * t.xyz
		);

}
//quadvec4
static alg::trivec4 mul_v(alg::quadvec4 q, alg::vec4 v)
{
	return alg::trivec4(q.xyzw * v.w, -q.xyzw * v.z,q.xyzw * v.y,-q.xyzw * v.x);
}

static alg::bivec4 mul_bv(alg::quadvec4 q, alg::bivec4 b)
{
	float xyzw = q.xyzw;
	return
		alg::bivec4(
			-b.zw * xyzw,
			b.yw * xyzw,
			-b.yz * xyzw,
			-b.xw * xyzw,
			b.xz * xyzw,
			-b.xy * xyzw
			);
}
//rotor4
static alg::vec4 rotate(alg::rotor4 r, alg::vec4 v)
{
	// p = R v ~R. We do this in two steps:
	// Q = R v
	alg::vec4 a1;
	alg::trivec4 a3;
	std::tie(a1, a3) = mul_v(r.b, v);

	alg::trivec4 b3 = mul_v(r.q,v);
	alg::vec4 q1 = v*r.s + a1;
	alg::trivec4 q3 = a3 + b3;

	// p = Q ~R
	alg::bivec4 bRev = r.b.reverse();
	alg::vec4 p = q1* r.s
		+ left_contract_bv(q1,bRev)
		+ right_contract_bv(q3,bRev)
		+ mul_qv(q3,r.q);
	return p;
}

static glm::mat4 to_matrix(alg::rotor4 r)
{
	alg::vec4 x = rotate(r, alg::vec4(1, 0, 0, 0));
	alg::vec4 y = rotate(r, alg::vec4(0, 1, 0, 0));
	alg::vec4 z = rotate(r, alg::vec4(0, 0, 1, 0));
	alg::vec4 w = rotate(r, alg::vec4(0, 0, 0, 1));

	return glm::mat4(
		x.x, x.y, x.z, x.w,
		y.x, y.y, y.z, y.w,
		z.x, z.y, z.z, z.w,
		w.x, w.y, w.z, w.w
		);
}

static alg::rotor4 mul_bv(alg::rotor4 r, alg::bivec4 c)
{
	//let(a_0, a_2, a_4) = self.b.mul_bv(c);
	alg::rotor4 mulRbC = mul_bv(r.b, c);
	float a0 = mulRbC.s;
	alg::bivec4 a2 = mulRbC.b;
	alg::quadvec4 a4 = mulRbC.q;
	return alg::rotor4(a0, c* r.s + a2 + mul_bv(r.q,c), a4);
}

static std::pair<alg::rotor4,alg::rotor4> decompose(alg::rotor4 r)
{
	alg::quadvec4 posHalfXYZW = alg::quadvec4(0.5);
	alg::quadvec4 negHalfXYZW = alg::quadvec4(-0.5);

	alg::rotor4 rPlus = alg::rotor4(
		0.5 + 0.5 * r.s + 0.5 * r.q.xyzw,
		r.b * 0.5 + posHalfXYZW.mul_bv(r.b),
		r.q * 0.5 + posHalfXYZW * r.s + negHalfXYZW
	);

	alg::rotor4 rMinus = alg::rotor4(
		0.5 + 0.5 * r.s - 0.5 * r.q.xyzw,
		r.b * 0.5 + negHalfXYZW.mul_bv(r.b),
		r.q * 0.5 + negHalfXYZW * r.s + posHalfXYZW
	);
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
	rPlus.s -= 0.5;
	rMinus.s -= 0.5;
	// we're going to overwrite the quadvector components since they should
	// be just +- the scalar components.

	float plusMag = 2.0
		* sqrt(pow(rPlus.s,2)
			+ pow(rPlus.b.xy,2)
			+ pow(rPlus.b.xz,2)
			+ pow(rPlus.b.xw,2));
	float minusMag = 2.0
		* sqrt(pow(rMinus.s, 2)
			+ pow(rMinus.b.xy, 2)
			+ pow(rMinus.b.xz, 2)
			+ pow(rMinus.b.xw, 2));

	if (plusMag > 0.0 ){
		float invPlusMag = 1.0 / plusMag;
		rPlus.s *= invPlusMag;
		rPlus.b = rPlus.b* invPlusMag;
		rPlus.q.xyzw = rPlus.s;

		// readd 1/2 (1 - xyzw)
		rPlus.s += 0.5;
		rPlus.q.xyzw -= 0.5;
	}
	else {
		// TODO:
		// unimplemented!("{:?} has zero magnitude!", rPlus);
		rPlus = alg::rotor4();
	}

	if (minusMag > 0.0 ){
		float invMinusMag = 1.0 / minusMag;
		rMinus.s *= invMinusMag;
		rMinus.b = rMinus.b* invMinusMag;
		rMinus.q.xyzw = -rMinus.s;

		// readd 1/2 (1 + xyzw)
		rMinus.s += 0.5;
		rMinus.q.xyzw += 0.5;
	}
	else {
		// TODO
		// unimplemented!("{:?} has zero magnitude!", rMinus);
		rMinus = alg::rotor4();
	}

	return rPlus * rMinus;
}

static alg::rotor4 update(alg::rotor4 r, alg::bivec4 delta) {
	return normalize(r * exp(delta * -0.5f));
}

static alg::rotor4 angle_to_rotor4(alg::bivec4 RotateAngle4D)
{
	alg::rotor4 rotation4D;
	rotation4D = update(alg::rotor4(), alg::bivec4(glm::radians(RotateAngle4D.xy), 0, 0, 0, 0, 0));
	rotation4D = update(rotation4D, alg::bivec4(0, glm::radians(RotateAngle4D.xz), 0, 0, 0, 0));
	rotation4D = update(rotation4D, alg::bivec4(0, 0, glm::radians(RotateAngle4D.xw), 0, 0, 0));
	rotation4D = update(rotation4D, alg::bivec4(0, 0, 0, glm::radians(RotateAngle4D.yz), 0, 0));
	rotation4D = update(rotation4D, alg::bivec4(0, 0, 0, 0, glm::radians(RotateAngle4D.yw), 0));
	rotation4D = update(rotation4D, alg::bivec4(0, 0, 0, 0, 0, glm::radians(RotateAngle4D.zw)));
	return rotation4D;
}

static glm::vec4 rotate(alg::bivec4 rotateAngle4D, glm::vec4 v)
{
	alg::rotor4 rotation4D = angle_to_rotor4(rotateAngle4D);
	return rotate(rotation4D, alg::vec4(v)).transform();
}

static float mag(alg::rotor4& r)
{
	float magSq = r.s * r.s
		+ r.b.xy * r.b.xy
		+ r.b.xz * r.b.xz
		+ r.b.xw * r.b.xw
		+ r.b.yz * r.b.yz
		+ r.b.yw * r.b.yw
		+ r.b.zw * r.b.zw
		+ r.q.xyzw * r.q.xyzw;
	return sqrt(magSq);
}

static float weird_term(alg::rotor4& r) 
{
	return -2.0 * r.b.xw * r.b.yz - 2.0 * r.b.xy * r.b.zw
		+ 2.0 * r.b.xz * r.b.yw
		+ 2.0 * r.q.xyzw * r.s;
}
