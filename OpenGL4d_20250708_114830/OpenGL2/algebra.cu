#pragma once
#include"cudaLibs.h"
__device__ struct bivec4 {
	float xy;
	float xz;
	float xw;
	float yz;
	float yw;
	float zw;

	__device__ explicit bivec4(float xy = 0.f, float xz = 0.f, float xw = 0.f, float yz = 0.f, float yw = 0.f, float zw = 0.f)
	{
		this->xy = xy, this->xz = xz, this->xw = xw, this->yz = yz, this->yw = yw, this->zw = zw;
	}

	__device__ bivec4 zero()
	{
		return bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
	}

	__device__ bivec4 reverse()
	{
		return bivec4(-xy, -xz, -xw, -yz, -yw, -zw);
	}

	//bivec4 radians()
	//{
	//	return bivec4(glm::radians(this->xy), glm::radians(this->xz), glm::radians(this->xw), glm::radians(this->yz), glm::radians(this->yw), glm::radians(this->zw));
	//}

	__device__ 	bivec4 operator+(const bivec4 q)
	{
		return bivec4(xy + q.xy, xz + q.xz, xw + q.xw, yz + q.yz, yw + q.yw, zw + q.zw);
	}

	__device__ bivec4 operator+=(const bivec4 q)
	{
		return bivec4(xy + q.xy, xz + q.xz, xw + q.xw, yz + q.yz, yw + q.yw, zw + q.zw);
	}

	__device__ bivec4 operator-(const bivec4 q)
	{
		return bivec4(xy - q.xy, xz - q.xz, xw - q.xw, yz - q.yz, yw - q.yw, zw - q.zw);
	}

	__device__ 	bivec4 operator-=(const bivec4 q)
	{
		return bivec4(xy - q.xy, xz - q.xz, xw - q.xw, yz - q.yz, yw - q.yw, zw - q.zw);
	}

	__device__ bivec4 operator*(const bivec4 q)
	{
		return bivec4(xy * q.xy, xz * q.xz, xw * q.xw, yz * q.yz, yw * q.yw, zw * q.zw);
	}

	__device__ bivec4 operator*(const float f)
	{
		return bivec4(xy * f, xz * f, xw * f, yz * f, yw * f, zw * f);
	}

	__device__ bivec4 operator*=(const bivec4 q)
	{
		return bivec4(xy * q.xy, xz * q.xz, xw * q.xw, yz * q.yz, yw * q.yw, zw * q.zw);
	}

	__device__ bivec4 operator*=(const float f)
	{
		return bivec4(xy * f, xz * f, xw * f, yz * f, yw * f, zw * f);
	}

	__device__ bivec4 operator/(const bivec4 q)
	{
		return bivec4(xy / q.xy, xz / q.xz, xw / q.xw, yz / q.yz, yw / q.yw, zw / q.zw);
	}

	__device__ bivec4 operator/(const float f)
	{
		return bivec4(xy / f, xz / f, xw / f, yz / f, yw / f, zw / f);
	}

	__device__ bivec4 operator/=(const bivec4 q)
	{
		return bivec4(xy / q.xy, xz / q.xz, xw / q.xw, yz / q.yz, yw / q.yw, zw / q.zw);
	}

	__device__ bivec4 operator/=(const float f)
	{
		return bivec4(xy / f, xz / f, xw / f, yz / f, yw / f, zw / f);
	}
};

__device__ struct quadvec4 {
	float xyzw;

	__device__ explicit quadvec4(float xyzw = 0.f)
	{
		this->xyzw = xyzw;
	}

	__device__ quadvec4 zero()
	{
		return quadvec4(0.f);
	}

	__device__ quadvec4 one()
	{
		return quadvec4(1.f);
	}

	__device__ bivec4 mul_bv(bivec4 b)
	{
		return bivec4(-b.zw * xyzw, b.yw * xyzw, -b.yz * xyzw, -b.xw * xyzw, b.xz * xyzw, -b.xy * xyzw);
	}

	__device__ quadvec4 operator+(const quadvec4 q)
	{
		return quadvec4(xyzw + q.xyzw);
	}
	__device__ quadvec4 operator+=(const quadvec4 q)
	{
		return quadvec4(xyzw + q.xyzw);
	}

	__device__ quadvec4 operator*(const quadvec4 q)
	{
		return quadvec4(xyzw * q.xyzw);
	}

	__device__ quadvec4 operator*=(const quadvec4 q)
	{
		return quadvec4(xyzw * q.xyzw);
	}

	__device__ quadvec4 operator*(const float f)
	{
		return quadvec4(xyzw * f);
	}

	__device__ quadvec4 operator*=(const float f)
	{
		return quadvec4(xyzw * f);
	}

};

__device__ struct rotor4
{
	float s;
	bivec4 b;
	quadvec4 q;

	__device__ explicit rotor4(float s = 1.f, bivec4 b = bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f), quadvec4 q = quadvec4(0.f))
	{
		this->s = s;
		this->b = b;
		this->q = q;
	}

	__device__ void set(float s = 1.f, bivec4 b = bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f), quadvec4 q = quadvec4(0.f))
	{
		this->s = s;
		this->b = b;
		this->q = q;
	}

	__device__ rotor4 reverse()
	{
		return rotor4(s, b.reverse(), q);
	}

	__device__ float mul_bv_s(bivec4 c)
	{
		return
			-b.xy * c.xy
			- b.xz * c.xz
			- b.xw * c.xw
			- b.yz * c.yz
			- b.yw * c.yw
			- b.zw * c.zw;
	}

	__device__ bivec4 mul_bv_b(bivec4 c)
	{
		return bivec4(
			-b.xw * c.yw - b.xz * c.yz + b.yw * c.xw + b.yz * c.xz,
			-b.xw * c.zw + b.xy * c.yz - b.yz * c.xy + b.zw * c.xw,
			b.xy * c.yw + b.xz * c.zw - b.yw * c.xy - b.zw * c.xz,
			-b.xy * c.xz + b.xz * c.xy - b.yw * c.zw + b.zw * c.yw,
			b.xw * c.xy - b.xy * c.xw + b.yz * c.zw - b.zw * c.yz,
			b.xw * c.xz - b.xz * c.xw + b.yw * c.yz - b.yz * c.yw
		);
	}

	__device__ quadvec4 mul_bv_q(bivec4 c)
	{
		return quadvec4(
			b.xw * c.yz
			+ b.xy * c.zw
			- b.xz * c.yw
			- b.yw * c.xz
			+ b.yz * c.xw
			+ b.zw * c.xy);
	}

	__device__ rotor4 mul_bv(bivec4 c)
	{
		return rotor4(mul_bv_s(c), mul_bv_b(c), mul_bv_q(c));
	}

	__device__ rotor4 operator+(const rotor4 r)
	{
		return rotor4(s + r.s, b + r.b, q + r.q);
	}
	__device__ rotor4 operator+=(const rotor4 r)
	{
		return rotor4(s + r.s, b + r.b, q + r.q);
	}
	__device__ rotor4 operator*(const rotor4 r1)
	{
		bivec4 rb(r1.b);
		quadvec4 rq(r1.q);
		float a0(mul_bv_s(r1.b));
		bivec4 a2(mul_bv_b(r1.b));
		quadvec4 a4(mul_bv_q(r1.b));
		return rotor4(s * r1.s + a0 + q.xyzw * r1.q.xyzw,
			rb * s
			+ b * r1.s
			+ a2
			+ q.mul_bv(rb)
			+ rq.mul_bv(b),
			rq * s + q * r1.s + a4);
	}
	__device__ rotor4 operator*=(const rotor4 r1)
	{
		bivec4 rb(r1.b);
		quadvec4 rq(r1.q);
		float a0(mul_bv_s(r1.b));
		bivec4 a2(mul_bv_b(r1.b));
		quadvec4 a4(mul_bv_q(r1.b));
		return rotor4(s * r1.s + a0 + q.xyzw * r1.q.xyzw,
			rb * s
			+ b * r1.s
			+ a2
			+ q.mul_bv(rb)
			+ rq.mul_bv(b),
			rq * s + q * r1.s + a4);
	}
};

__device__ struct trivec4
{
	float xyz;
	float xyw;
	float xzw;
	float yzw;
	__device__ explicit trivec4(float xyz = 0.f, float xyw = 0.f, float xzw = 0.f, float yzw = 0.f)
	{
		this->xyz = xyz;
		this->xyw = xyw;
		this->xzw = xzw;
		this->yzw = yzw;
	}
	__device__ trivec4 operator+(const trivec4 q)
	{
		return trivec4(xyz + q.xyz, xyw + q.xyw, xzw + q.xzw, yzw + q.yzw);
	}
	__device__ trivec4 operator+=(const trivec4 q)
	{
		return trivec4(xyz + q.xyz, xyw + q.xyw, xzw + q.xzw, yzw + q.yzw);
	}
};

__device__ struct vec2
{
	float x;
	float y;
	__device__ explicit vec2(float x = 0.f, float y = 0.f)
	{
		this->x = x;
		this->y = y;
	}

	__device__ vec2 operator+(const vec2 q)
	{
		return vec2(x + q.x, y + q.y);
	}
	__device__ vec2 operator+=(const vec2 q)
	{
		return vec2(x + q.x, y + q.y);
	}
	__device__ vec2 operator-(const vec2 q)
	{
		return vec2(x - q.x, y - q.y);
	}
	__device__ vec2 operator-=(const vec2 q)
	{
		return vec2(x - q.x, y - q.y);
	}
	__device__ vec2 operator*(const vec2 q)
	{
		return vec2(x * q.x, y * q.y);
	}
	__device__ vec2 operator*=(const vec2 q)
	{
		return vec2(x * q.x, y * q.y);
	}
	__device__ vec2 operator*(const float f)
	{
		return vec2(x * f, y * f);
	}
	__device__ vec2 operator*=(const float f)
	{
		return vec2(x * f, y * f);
	}
	__device__ vec2 operator/(const float f)
	{
		return vec2(x / f, y / f);
	}	
	__device__ float operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
	}
};

__device__ struct vec3
{
	float x;
	float y;
	float z;
	__device__ explicit vec3(float x = 0.f, float y = 0.f, float z = 0.f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	__device__ vec3 operator+(const vec3 q)
	{
		return vec3(x + q.x, y + q.y, z + q.z);
	}
	__device__ vec3 operator+=(const vec3 q)
	{
		return vec3(x + q.x, y + q.y, z + q.z);
	}
	__device__ vec3 operator-(const vec3 q)
	{
		return vec3(x - q.x, y - q.y, z - q.z);
	}
	__device__ vec3 operator-=(const vec3 q)
	{
		return vec3(x - q.x, y - q.y, z - q.z);
	}
	__device__ vec3 operator*(const vec3 q)
	{
		return vec3(x * q.x, y * q.y, z * q.z);
	}
	__device__ vec3 operator*=(const vec3 q)
	{
		return vec3(x * q.x, y * q.y, z * q.z);
	}
	__device__ vec3 operator*(const float f)
	{
		return vec3(x * f, y * f, z * f);
	}
	__device__ vec3 operator*=(const float f)
	{
		return vec3(x * f, y * f, z * f);
	}
	__device__ vec3 operator/(const float f)
	{
		return vec3(x / f, y / f, z / f);
	}
	__device__ float operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
		else if (n == 2) return this->z;
	}
};

__device__ struct vec4
{
	float x;
	float y;
	float z;
	float w;
	__device__ explicit vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	__device__ explicit vec4(float n = 0.f)
	{
		this->x = n;
		this->y = n;
		this->z = n;
		this->w = n;
	}
	
	__device__ vec4 operator+(const vec4 q)
	{
		return vec4(x + q.x, y + q.y, z + q.z, w + q.w);
	}
	__device__ vec4 operator+=(const vec4 q)
	{
		return vec4(x + q.x, y + q.y, z + q.z, w + q.w);
	}
	__device__ vec4 operator-(const vec4 q)
	{
		return vec4(x - q.x, y - q.y, z - q.z, w - q.w);
	}
	__device__ vec4 operator-=(const vec4 q)
	{
		return vec4(x - q.x, y - q.y, z - q.z, w - q.w);
	}
	__device__ vec4 operator-()
	{
		return vec4(-x, -y, -z, -w);
	}
	__device__ vec4 operator*(const vec4 q)
	{
		return vec4(x * q.x, y * q.y, z * q.z, w * q.w);
	}
	__device__ vec4 operator*=(const vec4 q)
	{
		return vec4(x * q.x, y * q.y, z * q.z, w * q.w);
	}
	__device__ vec4 operator*(const float f)
	{
		return vec4(x * f, y * f, z * f, w * f);
	}
	__device__ vec4 operator*=(const float f)
	{
		return vec4(x * f, y * f, z * f, w * f);
	}
	__device__ vec4 operator/(const float f)
	{
		return vec4(x / f, y / f, z / f, w / f);
	}

	__device__ vec4 operator/(const vec4 v)
	{
		return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	__device__ bool operator==(const vec4 q)
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	__device__ bool operator!=(const vec4 q)
	{
		return x != q.x || y != q.y || z != q.z || w != q.w;
	}

	__device__ float operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
		else if (n == 2) return this->z;
		else if (n == 3) return this->w;
	}

	__device__ void value(int n, float n2)
	{
		if (n == 0) this->x = n2;
		else if (n == 1) this->y = n2;
		else if (n == 2) this->z = n2;
		else if (n == 3) this->w = n2;
	}
};

__device__ static struct mat4x3
{
	vec3 x;
	vec3 y;
	vec3 z;
	vec3 w;
	//explicit mat4x3(vec4 x, vec4 y, vec4 z)
	//{
	//	this->x = x;
	//	this->y = y;
	//	this->z = z;
	//}
	__device__ vec3 operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
		else if (n == 2) return this->z;
		else if (n == 3) return this->w;
	}
	__device__ void value(int n, vec3 v)
	{
		if (n == 0) this->x = v;
		else if (n == 1) this->y = v;
		else if (n == 2) this->z = v;
		else if (n == 3) this->w = v;
	}
};

__device__ static struct mat4
{
	vec4 x;
	vec4 y;
	vec4 z;
	vec4 w;
	//explicit mat4(vec4 x, vec4 y, vec4 z, vec4 w)
	//{
	//	this->x = x;
	//	this->y = y;
	//	this->z = z;
	//	this->w = w;
	//}
	__device__ vec4 operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
		else if (n == 2) return this->z;
		else if (n == 3) return this->w;
	}
};

__device__ static struct ivec2
{
	int x;
	int y;
	explicit ivec2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	__device__ bool operator==(const ivec2 q)
	{
		return x == q.x && y == q.y;
	}
	__device__ int operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
	}
	__device__ void value(int n, int n2)
	{
		if (n == 0) this->x = n2;
		else if (n == 1) this->y = n2;
	}
};

__device__ static struct ivec4
{
	int x;
	int y;
	int z;
	int w;
	//__device__ explicit ivec4(int x, int y, int z, int w)
	//{
	//	this->x = x;
	//	this->y = y;
	//	this->z = z;
	//	this->w = w;
	//}
	__device__ bool operator==(const ivec4 q)
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}
	__device__ int operator[ ](int n)
	{
		if (n == 0) return this->x;
		else if (n == 1) return this->y;
		else if (n == 2) return this->z;
		else if (n == 3) return this->w;
	}
	__device__ void value(int n, int n2)
	{
		if (n == 0) this->x = n2;
		else if (n == 1) this->y = n2;
		else if (n == 2) this->z = n2;
		else if (n == 3) this->w = n2;
	}
};

__device__ static float _d_max(float x, float y)
{
	return x > y ? x : y;
}

__device__ static int _d_max(int x, int y)
{
	return x > y ? x : y;
}

__device__ static vec3 _d_max(vec3 x, vec3 y)
{
	return vec3(_d_max(x.x, y.x), _d_max(x.y, y.y), _d_max(x.z, y.z));
}

__device__ static float _d_min(float x, float y)
{
	return x < y ? x : y;
}

__device__ static int _d_min(int x, int y)
{
	return x < y ? x : y;
}

__device__ static float _d_abs(float x)
{
	return x > 0.f ? x : -x;
}

__device__ static vec4 abs(vec4 x)
{
	return vec4(_d_abs(x.x), _d_abs(x.y), _d_abs(x.z), _d_abs(x.w));
}

__device__ static int _d_abs(int x)
{
	return x > 0 ? x : -x;
}

__device__ static float _d_fmod(float x, float y)
{
	return x - int(x / y) * y;
}

__device__ static float _d_fract(float x)
{
	return x - int(x);
}

__device__ static float _d_sign(float x)
{
	return x > 0.f ? 1.f : -1.f;
}

__device__ static int _d_sign(int x)
{
	return x > 0 ? 1 : -1;
}

__device__ static vec4 sign(vec4 x)
{
	return vec4(_d_sign(x.x), _d_sign(x.y), _d_sign(x.z), _d_sign(x.w));
}

__device__ static float _d_clamp(float x, float y, float z)
{
	return x < y ? y : x > z ? z : x;
}

__device__ static int _d_clamp(int x, int y, int z)
{
	return x < y ? y : x > z ? z : x;
}

__device__ static int _d_inverse_clamp(int x, int y, int z)
{
	return x < y ? z : x > z ? y : x;
}

__device__ static float length(vec2 x)
{
	return sqrt(x.x * x.x + x.y * x.y);
}

__device__ static float length(vec3 x)
{
	return sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
}

__device__ static float length(vec4 x)
{
	return sqrt(x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w);
}

__device__ static vec2 normalize(vec2 x)
{
	return x / length(x);
}

__device__ static vec3 normalize(vec3 x)
{
	return x / length(x);
}

__device__ static vec4 normalize(vec4 x)
{
	return x / length(x);
}

__device__ static float dot(vec3 x, vec3 y)
{
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

__device__ static float dot(vec4 x, vec4 y)
{
	return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
}

__device__ static float _d_mix(float x, float y, float n)
{
	return x * (1.f - n) + y * n;
}

__device__ static vec4 mix(vec4 x, vec4 y,float n)
{
	return vec4(_d_mix(x.x, y.x, n), _d_mix(x.y, y.y, n), _d_mix(x.z, y.z, n), _d_mix(x.w, y.w, n));
}

__device__ static vec4 left_contract_bv(vec4 v, bivec4 b) {
	return
		vec4(
			-v.y * b.xy - v.z * b.xz - v.w * b.xw,
			v.x * b.xy - v.z * b.yz - v.w * b.yw,
			v.x * b.xz + v.y * b.yz - v.w * b.zw,
			v.x * b.xw + v.y * b.yw + v.z * b.zw
		);
}

//__device__ static vec4 left_contract_bv(vec4 v, float* bs, int index) {
//	return
//		vec4(
//			-v.y * bs[6 * index] - v.z * bs[6 * index + 1] - v.w * bs[6 * index + 2],
//			v.x * bs[6 * index] - v.z * bs[6 * index + 3] - v.w * bs[6 * index + 4],
//			v.x * bs[6 * index + 1] + v.y * bs[6 * index + 3] - v.w * bs[6 * index + 5],
//			v.x * bs[6 * index + 2] + v.y * bs[6 * index + 4] + v.z * bs[6 * index + 5]
//		);
//}

__device__ static trivec4 wedge_bv(vec4 v, bivec4 b) {
	return
		trivec4(
			v.x * b.yz - v.y * b.xz + v.z * b.xy,
			v.x * b.yw - v.y * b.xw + v.w * b.xy,
			v.x * b.zw - v.z * b.xw + v.w * b.xz,
			v.x * b.zw - v.z * b.yw + v.w * b.yz);
}

__device__ static bivec4 wedge_v(vec4 u, vec4 v) {
	return
		bivec4(
			u.x * v.y - u.y * v.x,
			u.x * v.z - u.z * v.x,
			-u.w * v.x + u.x * v.w,
			u.y * v.z - u.z * v.y,
			-u.w * v.y + u.y * v.w,
			-u.w * v.z + u.z * v.w
		);
}

__device__ static void mul_bv(vec4 v, bivec4 b, vec4* a1, trivec4* a3)
{
	*a1 = left_contract_bv(v, b);
	*a3 = wedge_bv(v, b);
}

//bivec4
__device__ static vec4 dot_v(bivec4 b, vec4 v)
{
	return vec4(
		b.xw * v.w + b.xy * v.y + b.xz * v.z,
		-b.xy * v.x + b.yw * v.w + b.yz * v.z,
		-b.xz * v.x - b.yz * v.y + b.zw * v.w,
		-b.xw * v.x - b.yw * v.y - b.zw * v.z
	);
}

__device__ static trivec4 wedge_v(bivec4 b, vec4 v)
{
	return trivec4(
		b.xy * v.z - b.xz * v.y + b.yz * v.x,
		-b.xw * v.y + b.xy * v.w + b.yw * v.x,
		-b.xw * v.z + b.xz * v.w + b.zw * v.x,
		-b.yw * v.z + b.yz * v.w + b.zw * v.y
	);
}

__device__ static void mul_v(bivec4 b, vec4 v, vec4* a1, trivec4* a3)
{
	*a1 = dot_v(b, v);
	*a3 = wedge_v(b, v);
}

__device__ static float mul_bv_s(bivec4 b, bivec4 c)
{
	return
		-b.xy * c.xy
		- b.xz * c.xz
		- b.xw * c.xw
		- b.yz * c.yz
		- b.yw * c.yw
		- b.zw * c.zw;
}

__device__ static bivec4 mul_bv_b(bivec4 b, bivec4 c)
{
	return
		bivec4(
			-b.xw * c.yw - b.xz * c.yz + b.yw * c.xw + b.yz * c.xz,
			-b.xw * c.zw + b.xy * c.yz - b.yz * c.xy + b.zw * c.xw,
			b.xy * c.yw + b.xz * c.zw - b.yw * c.xy - b.zw * c.xz,
			-b.xy * c.xz + b.xz * c.xy - b.yw * c.zw + b.zw * c.yw,
			b.xw * c.xy - b.xy * c.xw + b.yz * c.zw - b.zw * c.yz,
			b.xw * c.xz - b.xz * c.xw + b.yw * c.yz - b.yz * c.yw
		);
}

__device__ static quadvec4 mul_bv_q(bivec4 b, bivec4 c)
{
	return
		quadvec4(
			b.xw * c.yz
			+ b.xy * c.zw
			- b.xz * c.yw
			- b.yw * c.xz
			+ b.yz * c.xw
			+ b.zw * c.xy);
}

__device__ static rotor4 mul_bv(bivec4 b, bivec4 c)
{
	return rotor4(mul_bv_s(b, c), mul_bv_b(b, c), mul_bv_q(b, c));
}

__device__ static void decompose(bivec4 b, bivec4* bPlus, bivec4* bMinus) {
	quadvec4 posHalfXYZW(quadvec4(0.5));
	quadvec4 negHalfXYZW(quadvec4(-0.5));
	*bPlus = b * 0.5f + posHalfXYZW.mul_bv(b);
	*bMinus = b * 0.5f + negHalfXYZW.mul_bv(b);
}


__device__ static rotor4 exp(bivec4 b) {
	bivec4 bPlus;
	bivec4 bMinus;
	decompose(b, &bPlus, &bMinus);
	float thetaPlus(2.f * sqrt(bPlus.xy * bPlus.xy + bPlus.xz * bPlus.xz + bPlus.xw * bPlus.xw));
	float thetaMinus(2.f * sqrt(bMinus.xy * bMinus.xy + bMinus.xz * bMinus.xz + bMinus.xw * bMinus.xw));

	float invThetaPlus(thetaPlus > 0.f ? 1.f / thetaPlus : 0.f);
	float invThetaMinus(thetaMinus > 0.f ? 1.f / thetaMinus : 0.f);

	bivec4 unitBPlus(bPlus * invThetaPlus);
	bivec4 unitBMinus(bMinus * invThetaMinus);
	float cosThetaPlus(cos(thetaPlus));
	float cosThetaMinus(cos(thetaMinus));
	return rotor4(
		0.5f * (cosThetaPlus + cosThetaMinus),
		unitBPlus * sin(thetaPlus) + unitBMinus * sin(thetaMinus),
		quadvec4(0.5f * (cosThetaPlus - cosThetaMinus))
	);
}
//trivec4
__device__ static vec4 right_contract_bv(trivec4 t, bivec4 b) {
	return vec4(
		-b.yw * t.xyw - b.yz * t.xyz - b.zw * t.xzw,
		b.xw * t.xyw + b.xz * t.xyz - b.zw * t.yzw,
		b.xw * t.xzw - b.xy * t.xyz + b.yw * t.yzw,
		-b.xy * t.xyw - b.xz * t.xzw - b.yz * t.yzw
	);
}

__device__ static vec4 mul_qv(trivec4 t, quadvec4 q)
{
	float xyzw(q.xyzw);
	return vec4(xyzw * t.yzw, -xyzw * t.xzw, xyzw * t.xyw, -xyzw * t.xyz);
}
//quadvec4
__device__ static trivec4 mul_v(quadvec4 q, vec4 v)
{
	return trivec4(q.xyzw * v.w, -q.xyzw * v.z, q.xyzw * v.y, -q.xyzw * v.x);
}

__device__ static bivec4 mul_bv(quadvec4 q, bivec4 b)
{
	float xyzw(q.xyzw);
	return bivec4(-b.zw * xyzw, b.yw * xyzw, -b.yz * xyzw, -b.xw * xyzw, b.xz * xyzw, -b.xy * xyzw);
}
//rotor4
__device__ static vec4 rotate(rotor4 r, vec4 v)
{
	// p = R v ~R. We do this in two steps:
	// Q = R v
	vec4 a1;
	trivec4 a3;
	mul_v(r.b, v, &a1, &a3);

	trivec4 b3(mul_v(r.q, v));
	vec4 q1(v * r.s + a1);
	trivec4 q3(a3 + b3);

	// p = Q ~R
	bivec4 bRev(r.b.reverse());
	vec4 p(q1 * r.s + left_contract_bv(q1, bRev) + right_contract_bv(q3, bRev) + mul_qv(q3, r.q));
	return p;
}

__device__ static mat4 to_matrix(rotor4 r)
{
	vec4 x = rotate(r, vec4(1.f, 0.f, 0.f, 0.f));
	vec4 y = rotate(r, vec4(0.f, 1.f, 0.f, 0.f));
	vec4 z = rotate(r, vec4(0.f, 0.f, 1.f, 0.f));
	vec4 w = rotate(r, vec4(0.f, 0.f, 0.f, 1.f));

	return {
		vec4(x.x, x.y, x.z, x.w),
		vec4(y.x, y.y, y.z, y.w),
		vec4(z.x, z.y, z.z, z.w),
		vec4(w.x, w.y, w.z, w.w)
	};
}

__device__ static void to_matrix(rotor4 r, vec4 scale4D, float* mats4, int index)
{
	vec4 x = rotate(r, vec4(1.f, 0.f, 0.f, 0.f));
	vec4 y = rotate(r, vec4(0.f, 1.f, 0.f, 0.f));
	vec4 z = rotate(r, vec4(0.f, 0.f, 1.f, 0.f));
	vec4 w = rotate(r, vec4(0.f, 0.f, 0.f, 1.f));
	mats4[16 * index] = x.x * scale4D.x, mats4[16 * index + 1] = x.y * scale4D.x, mats4[16 * index + 2] = x.z * scale4D.x, mats4[16 * index + 3] = x.w * scale4D.x,
	mats4[16 * index + 4] = y.x * scale4D.y, mats4[16 * index + 5] = y.y * scale4D.y, mats4[16 * index + 6] = y.z * scale4D.y, mats4[16 * index + 7] = y.w * scale4D.y,
	mats4[16 * index + 8] = z.x * scale4D.z, mats4[16 * index + 9] = z.y * scale4D.z, mats4[16 * index + 10] = z.z * scale4D.z, mats4[16 * index + 11] = z.w * scale4D.z,
	mats4[16 * index + 12] = w.x * scale4D.w, mats4[16 * index + 13] = w.y * scale4D.w, mats4[16 * index + 14] = w.z * scale4D.w, mats4[16 * index + 15] = w.w * scale4D.w;
}

__device__ static rotor4 mul_bv(rotor4 r, bivec4 c)
{
	return rotor4(mul_bv_s(r.b, c), c * r.s + mul_bv_b(r.b, c) + mul_bv(r.q, c), mul_bv_q(r.b, c));
}

__device__ static void decompose(rotor4 r, rotor4* rPlus, rotor4* rMinus)
{
	quadvec4 posHalfXYZW(quadvec4(0.5f));
	quadvec4 negHalfXYZW(quadvec4(-0.5f));

	*rPlus = rotor4(
		0.5f * (1.f + r.s + r.q.xyzw),
		r.b * 0.5f + posHalfXYZW.mul_bv(r.b),
		r.q * 0.5f + posHalfXYZW * r.s + negHalfXYZW
	);

	*rMinus = rotor4(
		0.5f * (1.f + r.s - r.q.xyzw),
		r.b * 0.5f + negHalfXYZW.mul_bv(r.b),
		r.q * 0.5f + negHalfXYZW * r.s + posHalfXYZW
	);
}

__device__ static rotor4 normalize(rotor4 r) {
	// we decompose into two isoclinic rotations, which are each equivalent
	// to a quaternion. Each quaternion component is normalised, and then we
	// recover the original rotor

	rotor4 rPlus;
	rotor4 rMinus;
	decompose(r, &rPlus, &rMinus);
	// get rid of the 1/2 (1 +- xyzw) components
	rPlus.s = rPlus.s - 0.5f;
	rMinus.s = rMinus.s - 0.5f;
	// we're going to overwrite the quadvector components since they should
	// be just +- the scalar components.

	float plusMag(2.f * sqrt(rPlus.s * rPlus.s + rPlus.b.xy * rPlus.b.xy + rPlus.b.xz * rPlus.b.xz + rPlus.b.xw * rPlus.b.xw));
	float minusMag(2.f * sqrt(rMinus.s * rMinus.s + rMinus.b.xy * rMinus.b.xy + rMinus.b.xz * rMinus.b.xz + rMinus.b.xw * rMinus.b.xw));

	if (plusMag > 0.f) {
		float invPlusMag(1.f / plusMag);
		float rPlusS(rPlus.s * invPlusMag + 0.5f);
		rPlus.set(rPlusS, rPlus.b * invPlusMag, quadvec4(rPlusS - 1.f));
		// readd 1/2 (1 - xyzw)
	}
	else {
		// TODO:
		// unimplemented!("{:?} has zero magnitude!", rPlus);
		rPlus.set();
	}

	if (minusMag > 0.f) {
		float invMinusMag(1.f / minusMag);
		float rMinusS(rMinus.s * invMinusMag + 0.5f);
		rMinus.set(rMinusS, rMinus.b * invMinusMag, quadvec4(1.f - rMinusS));
		// readd 1/2 (1 + xyzw)
	}
	else {
		// TODO
		// unimplemented!("{:?} has zero magnitude!", rMinus);
		rMinus.set();
	}

	return rPlus * rMinus;
}

__device__ static rotor4 update(rotor4 r, bivec4 delta) {
	return normalize(r * exp(delta * -0.5f));
}

__device__ static float length(bivec4 b)
{
	return sqrt(b.xy * b.xy + b.xz * b.xz + b.xw * b.xw + b.yz * b.yz + b.yw * b.yw + b.zw * b.zw);
}

__device__ static float mag(rotor4 r)
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

__device__ static float weird_term(rotor4 r)
{
	return 2.f * (-r.b.xw * r.b.yz - r.b.xy * r.b.zw + r.b.xz * r.b.yw + r.q.xyzw * r.s);
}

__device__ static vec4 triple_cross_product(vec4 u, vec4 v, vec4 w)
{
	return mul_qv(wedge_v(wedge_v(vec4(u), vec4(v)), vec4(w)), quadvec4(1.f));
}
