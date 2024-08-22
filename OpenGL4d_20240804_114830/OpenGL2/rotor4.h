#pragma once
#include"bivec4.h"
#include"quadvec4.h"
namespace alg
{
	struct rotor4 
	{
		float s;
		bivec4 b;
		quadvec4 q;

		explicit rotor4(float s = 1.f, bivec4 b = bivec4(0.f,0.f,0.f,0.f,0.f,0.f), quadvec4 q = quadvec4(0.f))
		{
			this->s = s;
			this->b = b;
			this->q = q;
		}

		rotor4 reverse()
		{
			return rotor4(s,b.reverse(),q);
		}

		rotor4 mul_bv(bivec4 c)
		{
			float s2;
			bivec4 d2;
			quadvec4 q2;
			s2 =
				-b.xy * c.xy
				- b.xz * c.xz
				- b.xw * c.xw
				- b.yz * c.yz
				- b.yw * c.yw
				- b.zw * c.zw;
			d2 = bivec4(
				-b.xw * c.yw - b.xz * c.yz + b.yw * c.xw + b.yz * c.xz,
				-b.xw * c.zw + b.xy * c.yz - b.yz * c.xy + b.zw * c.xw,
				b.xy * c.yw + b.xz * c.zw - b.yw * c.xy - b.zw * c.xz,
				-b.xy * c.xz + b.xz * c.xy - b.yw * c.zw + b.zw * c.yw,
				b.xw * c.xy - b.xy * c.xw + b.yz * c.zw - b.zw * c.yz,
				b.xw * c.xz - b.xz * c.xw + b.yw * c.yz - b.yz * c.yw
			);
			q2 = quadvec4(
				b.xw * c.yz
				+ b.xy * c.zw
				- b.xz * c.yw
				- b.yw * c.xz
				+ b.yz * c.xw
				+ b.zw * c.xy);
			return rotor4(s2, d2, q2);
		}

		rotor4 operator+(const rotor4 r)
		{
			return rotor4(s+r.s,b+r.b,q+r.q);
		}
		rotor4 operator+=(const rotor4 r)
		{
			return rotor4(s + r.s, b + r.b, q + r.q);
		}
		rotor4 operator*(const rotor4 r1)
		{
			bivec4 rb(r1.b);
			quadvec4 rq(r1.q);
			float a0(mul_bv(r1.b).s);
			bivec4 a2(mul_bv(r1.b).b);
			quadvec4 a4(mul_bv(r1.b).q);
			return rotor4(s * r1.s + a0 + q.xyzw * r1.q.xyzw,
				 rb * s
				+ b* r1.s
				+ a2
				+ q.mul_bv(rb)
				+ rq.mul_bv(b),
				rq*s + q* r1.s + a4);
		}
		rotor4 operator*=(const rotor4 r1)
		{
			bivec4 rb(r1.b);
			quadvec4 rq(r1.q);
			float a0(mul_bv(r1.b).s);
			bivec4 a2(mul_bv(r1.b).b);
			quadvec4 a4(mul_bv(r1.b).q);
			return rotor4(s * r1.s + a0 + q.xyzw * r1.q.xyzw,
				rb * s
				+ b * r1.s
				+ a2
				+ q.mul_bv(rb)
				+ rq.mul_bv(b),
				rq * s + q * r1.s + a4);
		}
	};
}