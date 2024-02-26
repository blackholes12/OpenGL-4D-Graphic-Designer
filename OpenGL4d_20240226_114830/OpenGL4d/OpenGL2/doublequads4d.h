#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace doublequads4d {
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
		3,4,6,7,
		2,3,1,6,
		0,4,1,3,
		1,4,5,6,
		1,3,4,6,

		7,0,2,3,
		6,7,5,2,
		4,0,5,7,
		5,0,1,2,
		5,7,0,2,
	};
}
