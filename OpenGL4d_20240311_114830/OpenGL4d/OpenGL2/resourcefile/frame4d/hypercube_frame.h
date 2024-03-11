#pragma once
#include<GLFW/glfw3.h>
#include<vec4.hpp>
namespace hypercube_frame {
	static glm::vec4 frameVertices4D[] =
	{
	glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),//8
	glm::vec4(0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),//12
	glm::vec4(0.5f, 0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.5f, -0.5f,0.5f)
	};
	static GLuint frameIndices4D0[] =
	{
		0,1,
		0,3,
		0,4,
		0,8,
		1,2,
		1,5,
		1,9,
		2,3,
		2,6,
		2,10,
		3,7,
		3,11,

		4,5,
		4,7,
		4,12,
		5,6,
		5,13,
		6,7,
		6,14,
		7,15,

		8,9,
		8,11,
		8,12,
		9,10,
		9,13,
		10,11,
		10,14,
		11,15,
		12,13,
		12,15,
		13,14,
		14,15
	};
}
