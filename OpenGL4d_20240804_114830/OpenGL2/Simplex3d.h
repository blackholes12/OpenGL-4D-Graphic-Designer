#pragma once
//#include<GLFW/glfw3.h>
//#include<glm.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat3x3.hpp>
//#include<mat4x4.hpp>
static float fract(float a) {
	return a - floor(a);
}
static glm::vec3 random3(glm::vec3 c) {
	float j(4096.f*sin(dot(c,glm::vec3(17.0f, 59.4f, 15.0f))));
	glm::vec3 r;
	r.z = fract(512.f*j);
	j *= 0.125f;
	r.x = fract(512.f*j);
	j *= 0.125f;
	r.y = fract(512.f*j);
	return r-glm::vec3(0.5f);
}

/* 3d simplex noise */
static float simplex3d(glm::vec3 p) {
	/* skew constants for 3d simplex functions */
	 const float F3(0.3333333f);
	 const float G3(0.1666667f);
	 /* 1. find current tetrahedron T and it's four vertices */
	 /* s, s+i1, s+i2, s+1.0 - absolute skewed (integer) coordinates of T vertices */
	 /* x, x1, x2, x3 - unskewed coordinates of p relative to each of T vertices*/
	 
	 /* calculate s and x */
	 glm::vec3 s(floor(p + dot(p, glm::vec3(F3))));
	 glm::vec3 x(p - s + dot(s, glm::vec3(G3)));
	 
	 /* calculate i1 and i2 */
	 glm::vec3 e(step(glm::vec3(0.f), x - glm::vec3(x.y,x.z,x.x)));
	 glm::vec3 i1(e - glm::vec3(e.x*e.z,e.y*e.x,e.z*e.y));
	 glm::vec3 i2( glm::vec3(1.f) - glm::vec3(e.z,e.x,e.y)*(glm::vec3(1.f) - e));
	 	
	 /* x1, x2, x3 */
	 glm::vec3 x1(x - i1 + G3);
	 glm::vec3 x2(x - i2 + glm::vec3(2.0f)*G3);
	 glm::vec3 x3(x - glm::vec3(1.0f) + glm::vec3(3.0f)*G3);
	 
	 /* 2. find four surflets and store them in d */
	 glm::vec4 w, d;
	 
	 /* calculate surflet weights */
	 w.x = dot(x, x);
	 w.y = dot(x1, x1);
	 w.z = dot(x2, x2);
	 w.w = dot(x3, x3);
	 
	 /* w fades from 0.6 at the center of the surflet to 0.0 at the margin */
	 w = max(glm::vec4(0.6f) - w, glm::vec4(0.f));
	 
	 /* calculate surflet components */
	 d.x = dot(random3(s), x);
	 d.y = dot(random3(s + i1), x1);
	 d.z = dot(random3(s + i2), x2);
	 d.w = dot(random3(s + glm::vec3(1.f)), x3);
	 
	 /* multiply d by w^4 */
	 w *= w;
	 w *= w;
	 d *= w;
	 
	 /* 3. return the sum of the four surflets */
	 return dot(d, glm::vec4(52.f));
}


/* directional artifacts can be reduced by rotating each octave */
static float simplex3d_fractal(glm::vec3 m) {
	/* const matrices for 3d rotation */
	const glm::mat3 rot1(glm::mat3(-0.37f, 0.36f, 0.85f, -0.14f, -0.93f, 0.34f, 0.92f, 0.01f, 0.4f));
	const glm::mat3 rot2(glm::mat3(-0.55f, -0.39f, 0.74f, 0.33f, -0.91f, -0.24f, 0.77f, 0.12f, 0.63f));
	const glm::mat3 rot3(glm::mat3(-0.71f, 0.52f, -0.47f, -0.08f, -0.72f, -0.68f, -0.7f, -0.45f, 0.56f));
    return   2.f*0.1333333f*simplex3d(m*rot1)
			+2.f*0.2666667f*simplex3d(glm::vec3(exp(1.0f))*m*rot2)
			+2.f*0.1333333f*simplex3d(glm::vec3(exp(2.0f))*m*rot3)
			+2.f*0.0666667f*simplex3d(glm::vec3(exp(3.0f))*m);
}
static float terrain_height(glm::vec4 m)
{
	float height = 
		simplex3d((glm::vec3(10000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f) / 10.f +
		simplex3d(glm::vec3(m.x, m.z, m.w) / 2.f / exp(1.f)) / 10.f * exp(1.f) +
		simplex3d((glm::vec3(-10000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(2.f)) / 10.f * exp(2.f) + 
		simplex3d((glm::vec3(-20000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(3.f)) / 10.f * exp(3.f) + 
		simplex3d((glm::vec3(-30000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(4.f)) / 10.f * exp(4.f) + 
		simplex3d((glm::vec3(-40000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(5.f)) / 10.f * exp(5.f) + 
		simplex3d((glm::vec3(-50000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(6.f)) / 10.f * exp(6.f) + 
		simplex3d((glm::vec3(-60000.f) + glm::vec3(m.x, m.z, m.w)) / 2.f / exp(7.f)) / 10.f * exp(7.f) + 40.f;
	if(height<54.f)height = (height - 54.f) * 0.5f + 54.f;
	//height = height + 54.f - 87.f;
	return height;
}