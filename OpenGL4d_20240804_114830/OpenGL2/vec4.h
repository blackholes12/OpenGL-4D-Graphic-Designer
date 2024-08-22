#pragma once
#include<vec4.hpp>
namespace alg 
{
	struct vec4 
	{
		float x;
		float y;
		float z;
		float w;
		explicit vec4(float x=0.f,float y=0.f,float z=0.f,float w=0.f)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		explicit vec4(glm::vec4 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
		}

		vec4 operator+(const vec4 q)
		{
			return vec4( x + q.x,y + q.y,z + q.z,w + q.w );
		}
		vec4 operator+=(const vec4 q)
		{
			return vec4( x + q.x,y + q.y,z + q.z,w + q.w );
		}
		vec4 operator*(const vec4 q)
		{
			return vec4( x * q.x,y * q.y,z * q.z,w * q.w );
		}
		vec4 operator*=(const vec4 q)
		{
			return vec4( x * q.x,y * q.y,z * q.z,w * q.w );
		}
		vec4 operator*(const float f)
		{
			return vec4(x * f, y * f, z * f, w * f);
		}
		vec4 operator*=(const float f)
		{
			return vec4(x * f, y * f, z * f, w * f);
		}
		glm::vec4 transform()
		{
			return glm::vec4(x,y,z,w);
		}
		vec4 operator=(const glm::vec4 q)
		{
			return vec4(q.x, q.y, q.z, q.w);
		}
	};
}
