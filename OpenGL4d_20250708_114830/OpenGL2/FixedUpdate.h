#pragma once
namespace fixedUpdate {
	static bool isFixedUpdate0;
	static float fixedTime = 0.f;
	static float fixedCurTime = 0.f;
	static bool is_fixed_update(const float dt, const float fixedDt)
	{
		isFixedUpdate0 = false;
		fixedTime += dt;
		if (fixedTime >= fixedDt)
		{
			isFixedUpdate0 = true;
			fixedTime = alg::fmod(fixedTime, fixedDt);//fixedTime - fixedDt * floor(fixedTime / fixedDt);
		}
		return isFixedUpdate0;
	}

	static bool isFixedUpdate02;
	static float fixedTime2 = 0.f;
	static bool is_fixed_update2(const float dt, const float fixedDt)
	{
		isFixedUpdate02 = false;
		fixedTime2 += dt;
		if (fixedTime2 >= fixedDt)
		{
			isFixedUpdate02 = true;
			fixedTime = alg::fmod(fixedTime, fixedDt);//fixedTime - fixedDt * floor(fixedTime / fixedDt);
		}
		return isFixedUpdate02;
	}
}