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
	static glm::vec4 normals4D[] =
	{
	glm::vec4(0,-1,0,0),
	glm::vec4(0,1,0,0)
	};
	static glm::ivec2 indices4D0[] =
	{
		glm::ivec2(3,0),glm::ivec2(4,0),glm::ivec2(6,0),glm::ivec2(7,0),
		glm::ivec2(2,0),glm::ivec2(3,0),glm::ivec2(1,0),glm::ivec2(6,0),
		glm::ivec2(0,0),glm::ivec2(4,0),glm::ivec2(1,0),glm::ivec2(3,0),
		glm::ivec2(1,0),glm::ivec2(4,0),glm::ivec2(5,0),glm::ivec2(6,0),
		glm::ivec2(1,0),glm::ivec2(3,0),glm::ivec2(4,0),glm::ivec2(6,0),
		glm::ivec2(7,1),glm::ivec2(0,1),glm::ivec2(2,1),glm::ivec2(3,1),
		glm::ivec2(6,1),glm::ivec2(7,1),glm::ivec2(5,1),glm::ivec2(2,1),
		glm::ivec2(4,1),glm::ivec2(0,1),glm::ivec2(5,1),glm::ivec2(7,1),
		glm::ivec2(5,1),glm::ivec2(0,1),glm::ivec2(1,1),glm::ivec2(2,1),
		glm::ivec2(5,1),glm::ivec2(7,1),glm::ivec2(0,1),glm::ivec2(2,1)
	};
}
