#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace quad4d {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(-0.5f, 0.f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.f, -0.5f,0.5f)
	};
	static GLuint indices4D0[] =
	{
		7,0,2,3,
		6,7,5,2,
		4,0,5,7,
		5,0,1,2,
		5,7,0,2,
	};
}