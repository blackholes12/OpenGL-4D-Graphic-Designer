#pragma once
#include"bivec4.h"
namespace alg
{
	struct quadvec4 {
		float xyzw;

		explicit quadvec4(float xyzw = 0.f) 
		{
			this->xyzw = xyzw;
		}

		quadvec4 zero()
		{
			return quadvec4(0.f);
		}

		quadvec4 one()
		{
			return quadvec4( 1.f );
		}

		bivec4 mul_bv(bivec4 b)
		{
			return bivec4(- b.zw * xyzw, b.yw* xyzw, -b.yz * xyzw, -b.xw * xyzw, b.xz* xyzw, -b.xy * xyzw );
		}

		quadvec4 operator+(const quadvec4 q)
		{
			return quadvec4( xyzw + q.xyzw );
		}
		quadvec4 operator+=(const quadvec4 q)
		{
			return quadvec4( xyzw + q.xyzw );
		}

		quadvec4 operator*(const quadvec4 q)
		{
			return quadvec4( xyzw * q.xyzw );
		}

		quadvec4 operator*=(const quadvec4 q)
		{
			return quadvec4( xyzw * q.xyzw );
		}

		quadvec4 operator*(const float f)
		{
			return quadvec4(xyzw * f);
		}

		quadvec4 operator*=(const float f)
		{
			return quadvec4(xyzw * f);
		}

	};
}
