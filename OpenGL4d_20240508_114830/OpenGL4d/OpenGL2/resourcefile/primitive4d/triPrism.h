#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace triPrism{
	static glm::vec4 vertices4D[8] =
	{
	glm::vec4(-sqrt(3) / 6,-0.5f,-0.5f,-sqrt(6) / 12),
	glm::vec4(-sqrt(3) / 6,-0.5f,0.5f,-sqrt(6) / 12),
	glm::vec4(sqrt(3) / 3,-0.5f,0,-sqrt(6) / 12),
	glm::vec4(0,-0.5f,0,sqrt(6) / 4),
	glm::vec4(-sqrt(3) / 6,0.5f,-0.5f,-sqrt(6) / 12),
	glm::vec4(-sqrt(3) / 6,0.5f,0.5f,-sqrt(6) / 12),
	glm::vec4(sqrt(3) / 3,0.5f,0,-sqrt(6) / 12),
	glm::vec4(0,0.5f,0,sqrt(6) / 4)
	};
	static glm::vec4 normals4D[] =
	{
    glm::vec4(0,0,0,-1),
    glm::vec4(-0.942809,0,0,0.333333),
    glm::vec4(0.471405,0,-0.816497,0.333333),
    glm::vec4(0.471405,0,0.816497,0.333333),
    glm::vec4(0,-1,0,4),
    glm::vec4(0,1,0,4)
	};
	static glm::ivec2 indices4D0[] =
	{
	glm::ivec2(6,4),glm::ivec2(5,4),glm::ivec2(2,4),glm::ivec2(4,4),
	glm::ivec2(5,4),glm::ivec2(2,4),glm::ivec2(4,4),glm::ivec2(1,4),
	glm::ivec2(4,4),glm::ivec2(1,4),glm::ivec2(2,4),glm::ivec2(0,4),
	glm::ivec2(7,1),glm::ivec2(4,1),glm::ivec2(3,1),glm::ivec2(5,1),
	glm::ivec2(5,1),glm::ivec2(1,1),glm::ivec2(4,1),glm::ivec2(3,1),
	glm::ivec2(4,1),glm::ivec2(0,1),glm::ivec2(3,1),glm::ivec2(1,1),
	glm::ivec2(6,2),glm::ivec2(4,2),glm::ivec2(2,2),glm::ivec2(7,2),
	glm::ivec2(7,2),glm::ivec2(3,2),glm::ivec2(4,2),glm::ivec2(2,2),
	glm::ivec2(4,2),glm::ivec2(0,2),glm::ivec2(2,2),glm::ivec2(3,2),
	glm::ivec2(6,3),glm::ivec2(7,3),glm::ivec2(2,3),glm::ivec2(5,3),
	glm::ivec2(5,3),glm::ivec2(1,3),glm::ivec2(7,3),glm::ivec2(2,3),
	glm::ivec2(7,3),glm::ivec2(3,3),glm::ivec2(2,3),glm::ivec2(1,3),
	glm::ivec2(3,4),glm::ivec2(2,4),glm::ivec2(1,4),glm::ivec2(0,4),
	glm::ivec2(7,5),glm::ivec2(4,5),glm::ivec2(5,5),glm::ivec2(6,5)
	};
}