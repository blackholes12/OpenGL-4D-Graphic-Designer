#pragma once
//#include"rotor4.h"
namespace alg 
{
	struct bivec4 {
		float xy;
		float xz;
		float xw;
		float yz;
		float yw;
		float zw;

		explicit bivec4(float xy = 0.f, float xz = 0.f, float xw = 0.f, float yz = 0.f, float yw = 0.f, float zw = 0.f)
		{
			this->xy = xy,this->xz = xz,this->xw = xw,this->yz = yz,this->yw = yw,this->zw = zw;
		}

		bivec4 zero()
		{
			return bivec4(0.f,0.f,0.f,0.f,0.f,0.f);
		}

		bivec4 reverse()
		{
			return bivec4( - xy, -xz, -xw, -yz, -yw, -zw );
		}

		bivec4 radians()
		{
			return bivec4(glm::radians(this->xy), glm::radians(this->xz), glm::radians(this->xw), glm::radians(this->yz), glm::radians(this->yw), glm::radians(this->zw));
		}
		
		bivec4 operator+(const bivec4 q)
		{
			return bivec4( xy + q.xy,xz + q.xz,xw + q.xw,yz + q.yz,yw + q.yw,zw + q.zw );
		}
		bivec4 operator+=(const bivec4 q)
		{
			return bivec4( xy + q.xy,xz + q.xz,xw + q.xw,yz + q.yz,yw + q.yw,zw + q.zw );
		}

		bivec4 operator*(const bivec4 q)
		{
			return bivec4( xy*q.xy,xz*q.xz,xw*q.xw,yz*q.yz,yw*q.yw,zw*q.zw );
		}

		bivec4 operator*(const float f)
		{
			return bivec4(xy * f, xz * f, xw * f, yz * f, yw * f, zw * f);
		}

		bivec4 operator*=(const bivec4 q)
		{
			return bivec4(xy * q.xy,xz * q.xz,xw * q.xw,yz * q.yz,yw * q.yw,zw * q.zw );
		}

		bivec4 operator*=(const float f)
		{
			return bivec4(xy * f, xz * f, xw * f, yz * f, yw * f, zw * f);
		}

		bivec4 operator/(const bivec4 q)
		{
			return bivec4(xy / q.xy, xz / q.xz, xw / q.xw, yz / q.yz, yw / q.yw, zw / q.zw);
		}

		bivec4 operator/(const float f)
		{
			return bivec4(xy / f, xz / f, xw / f, yz / f, yw / f, zw / f);
		}

		bivec4 operator/=(const bivec4 q)
		{
			return bivec4(xy / q.xy, xz / q.xz, xw / q.xw, yz / q.yz, yw / q.yw, zw / q.zw);
		}

		bivec4 operator/=(const float f)
		{
			return bivec4(xy / f, xz / f, xw / f, yz / f, yw / f, zw / f);
		}
	};
}