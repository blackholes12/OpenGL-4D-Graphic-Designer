#pragma once
namespace alg
{
	struct trivec4
	{
		float xyz;
		float xyw;
		float xzw;
		float yzw;
		explicit trivec4(float xyz = 0.f, float xyw = 0.f, float xzw = 0.f, float yzw = 0.f)
		{
			this->xyz = xyz;
			this->xyw = xyw;
			this->xzw = xzw;
			this->yzw = yzw;
		}
		trivec4 operator+(const trivec4 q)
		{
			return trivec4(xyz + q.xyz, xyw + q.xyw, xzw + q.xzw, yzw + q.yzw);
		}
		trivec4 operator+=(const trivec4 q)
		{
			return trivec4(xyz + q.xyz, xyw + q.xyw, xzw + q.xzw, yzw + q.yzw);
		}
	};
}
