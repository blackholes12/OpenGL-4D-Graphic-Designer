#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace pyramid4d {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(-0.5f,-0.5f,-0.5f,-0.5f),
	glm::vec4(-0.5f,-0.5f,0.5f,-0.5f),
	glm::vec4(0.5f,-0.5f,0.5f,-0.5f),
	glm::vec4(0.5f,-0.5f,-0.5f,-0.5f),
	glm::vec4(-0.5f,-0.5f,-0.5f,0.5f),
	glm::vec4(-0.5f,-0.5f,0.5f,0.5f),
	glm::vec4(0.5f,-0.5f,0.5f,0.5f),
	glm::vec4(0.5f,-0.5f,-0.5f,0.5f),
	glm::vec4(0,0.5f,0,0)
	};
	static glm::vec4 normals4D[] =
	{
    glm::vec4(0,0.447214,-0.894427,0),
    glm::vec4(-0.894427,0.447214,0,0),
    glm::vec4(0,0.447214,0.894427,0),
    glm::vec4(0.894427,0.447214,0,0),
    glm::vec4(0,0.447214,0,-0.894427),
    glm::vec4(0,0.447214,0,0.894427),
    glm::vec4(0,-1,0,0)
	};
	static glm::ivec2 indices4D0[] =
	{
	glm::ivec2(8,0),glm::ivec2(0,0),glm::ivec2(7,0),glm::ivec2(4,0),
	glm::ivec2(8,0),glm::ivec2(0,0),glm::ivec2(3,0),glm::ivec2(7,0),
	glm::ivec2(8,1),glm::ivec2(5,1),glm::ivec2(1,1),glm::ivec2(0,1),
	glm::ivec2(8,1),glm::ivec2(5,1),glm::ivec2(0,1),glm::ivec2(4,1),
	glm::ivec2(8,2),glm::ivec2(5,2),glm::ivec2(2,2),glm::ivec2(1,2),
	glm::ivec2(8,2),glm::ivec2(5,2),glm::ivec2(6,2),glm::ivec2(2,2),
	glm::ivec2(8,3),glm::ivec2(7,3),glm::ivec2(3,3),glm::ivec2(6,3),
	glm::ivec2(8,3),glm::ivec2(3,3),glm::ivec2(2,3),glm::ivec2(6,3),
	glm::ivec2(8,4),glm::ivec2(3,4),glm::ivec2(0,4),glm::ivec2(1,4),
	glm::ivec2(8,4),glm::ivec2(3,4),glm::ivec2(1,4),glm::ivec2(2,4),
	glm::ivec2(8,5),glm::ivec2(5,5),glm::ivec2(4,5),glm::ivec2(7,5),
	glm::ivec2(8,5),glm::ivec2(6,5),glm::ivec2(5,5),glm::ivec2(7,5),
	glm::ivec2(7,6),glm::ivec2(3,6),glm::ivec2(2,6),glm::ivec2(0,6),
	glm::ivec2(6,6),glm::ivec2(2,6),glm::ivec2(5,6),glm::ivec2(7,6),
	glm::ivec2(4,6),glm::ivec2(7,6),glm::ivec2(5,6),glm::ivec2(0,6),
	glm::ivec2(5,6),glm::ivec2(2,6),glm::ivec2(1,6),glm::ivec2(0,6),
	glm::ivec2(5,6),glm::ivec2(2,6),glm::ivec2(0,6),glm::ivec2(7,6)
	};
}
