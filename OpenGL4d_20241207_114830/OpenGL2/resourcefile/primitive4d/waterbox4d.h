#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace waterbox4d {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.0f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.0f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.0f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.0f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.0f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.0f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.0f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.0f, -0.5f,0.5f)
	};
	static glm::vec4 normals4D[] =
	{
    glm::vec4(0,0,0,1),
    glm::vec4(-1,0,0,0),
    glm::vec4(0,0,1,0),
    glm::vec4(1,0,0,0),
    glm::vec4(0,0,-1,0),
    glm::vec4(0,1,0,0),
    glm::vec4(0,0,0,-1)
	};
	static glm::ivec2 indices4D0[] =
	{
		glm::ivec2(0,0),glm::ivec2(2,0),glm::ivec2(3,0),glm::ivec2(7,0),
		glm::ivec2(7,0),glm::ivec2(5,0),glm::ivec2(2,0),glm::ivec2(6,0),
		glm::ivec2(0,0),glm::ivec2(5,0),glm::ivec2(7,0),glm::ivec2(4,0),
		glm::ivec2(0,0),glm::ivec2(1,0),glm::ivec2(2,0),glm::ivec2(5,0),
		glm::ivec2(7,0),glm::ivec2(0,0),glm::ivec2(2,0),glm::ivec2(5,0),
		glm::ivec2(1,1),glm::ivec2(10,1),glm::ivec2(2,1),glm::ivec2(6,1),
		glm::ivec2(6,1),glm::ivec2(13,1),glm::ivec2(10,1),glm::ivec2(14,1),
		glm::ivec2(1,1),glm::ivec2(13,1),glm::ivec2(6,1),glm::ivec2(5,1),
		glm::ivec2(1,1),glm::ivec2(9,1),glm::ivec2(10,1),glm::ivec2(13,1),
		glm::ivec2(6,1),glm::ivec2(1,1),glm::ivec2(10,1),glm::ivec2(13,1),
		glm::ivec2(3,2),glm::ivec2(10,2),glm::ivec2(11,2),glm::ivec2(15,2),
		glm::ivec2(15,2),glm::ivec2(6,2),glm::ivec2(10,2),glm::ivec2(14,2),
		glm::ivec2(3,2),glm::ivec2(6,2),glm::ivec2(15,2),glm::ivec2(7,2),
		glm::ivec2(3,2),glm::ivec2(2,2),glm::ivec2(10,2),glm::ivec2(6,2),
		glm::ivec2(15,2),glm::ivec2(3,2),glm::ivec2(10,2),glm::ivec2(6,2),
		glm::ivec2(8,3),glm::ivec2(3,3),glm::ivec2(11,3),glm::ivec2(15,3),
		glm::ivec2(15,3),glm::ivec2(4,3),glm::ivec2(3,3),glm::ivec2(7,3),
		glm::ivec2(8,3),glm::ivec2(4,3),glm::ivec2(15,3),glm::ivec2(12,3),
		glm::ivec2(8,3),glm::ivec2(0,3),glm::ivec2(3,3),glm::ivec2(4,3),
		glm::ivec2(15,3),glm::ivec2(8,3),glm::ivec2(3,3),glm::ivec2(4,3),
		glm::ivec2(8,4),glm::ivec2(1,4),glm::ivec2(0,4),glm::ivec2(4,4),
		glm::ivec2(4,4),glm::ivec2(13,4),glm::ivec2(1,4),glm::ivec2(5,4),
		glm::ivec2(8,4),glm::ivec2(13,4),glm::ivec2(4,4),glm::ivec2(12,4),
		glm::ivec2(8,4),glm::ivec2(9,4),glm::ivec2(1,4),glm::ivec2(13,4),
		glm::ivec2(4,4),glm::ivec2(8,4),glm::ivec2(1,4),glm::ivec2(13,4),
		glm::ivec2(8,5),glm::ivec2(10,5),glm::ivec2(11,5),glm::ivec2(3,5),
		glm::ivec2(3,5),glm::ivec2(1,5),glm::ivec2(10,5),glm::ivec2(2,5),
		glm::ivec2(8,5),glm::ivec2(1,5),glm::ivec2(3,5),glm::ivec2(0,5),
		glm::ivec2(8,5),glm::ivec2(9,5),glm::ivec2(10,5),glm::ivec2(1,5),
		glm::ivec2(3,5),glm::ivec2(8,5),glm::ivec2(10,5),glm::ivec2(1,5),
		glm::ivec2(11,6),glm::ivec2(10,6),glm::ivec2(8,6),glm::ivec2(15,6),
		glm::ivec2(10,6),glm::ivec2(13,6),glm::ivec2(15,6),glm::ivec2(14,6),
		glm::ivec2(15,6),glm::ivec2(13,6),glm::ivec2(8,6),glm::ivec2(12,6),
		glm::ivec2(10,6),glm::ivec2(9,6),glm::ivec2(8,6),glm::ivec2(13,6),
		glm::ivec2(10,6),glm::ivec2(8,6),glm::ivec2(15,6),glm::ivec2(13,6)
	};
}
