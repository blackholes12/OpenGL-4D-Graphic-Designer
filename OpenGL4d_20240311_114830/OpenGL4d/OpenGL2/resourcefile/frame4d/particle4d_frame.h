#pragma once
#include<GLFW/glfw3.h>
#include<vec4.hpp>
namespace particle4d_frame {
	static glm::vec4 frameVertices4D[] =
	{
	glm::vec4(1.f, 0.f, 0.f,0.f) / 6.f,//0
	glm::vec4(-1.f, 0.f, 0.f,0.f) / 6.f,//1
	glm::vec4(0.f, 1.f, 0.f,0.f) / 6.f,//2
	glm::vec4(0.f, -1.f, 0.f,0.f) / 6.f,//3
	glm::vec4(0.f, 0.f, 1.f,0.f) / 6.f,//4
	glm::vec4(0.f, 0.f, -1.f,0.f) / 6.f,//5
	glm::vec4(0.f, 0.f, 0.f,1.f) / 6.f,//6
	glm::vec4(0.f, 0.f, 0.f,-1.f) / 6.f,//7
	normalize(glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f)) / 6.f,//8
	normalize(glm::vec4(0.5f, -0.5f, 0.5f,-0.5f)) / 6.f,//9
	normalize(glm::vec4(0.5f, -0.5f, -0.5f,-0.5f)) / 6.f,//10
	normalize(glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f)) / 6.f,//11
	normalize(glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f)) / 6.f,//12
	normalize(glm::vec4(0.5f, 0.5f, 0.5f,-0.5f)) / 6.f,//13
	normalize(glm::vec4(0.5f, 0.5f, -0.5f,-0.5f)) / 6.f,//14
	normalize(glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f)) / 6.f,//15
	normalize(glm::vec4(-0.5f, -0.5f, 0.5f,0.5f)) / 6.f,//16
	normalize(glm::vec4(0.5f, -0.5f, 0.5f,0.5f)) / 6.f,//17
	normalize(glm::vec4(0.5f, -0.5f, -0.5f,0.5f)) / 6.f,//18
	normalize(glm::vec4(-0.5f, -0.5f, -0.5f,0.5f)) / 6.f,//19
	normalize(glm::vec4(-0.5f, 0.5f, 0.5f,0.5f)) / 6.f,//20
	normalize(glm::vec4(0.5f, 0.5f, 0.5f,0.5f)) / 6.f,//21
	normalize(glm::vec4(0.5f, 0.5f, -0.5f,0.5f)) / 6.f,//22
	normalize(glm::vec4(-0.5f, 0.5f, -0.5f,0.5f)) / 6.f//23
	};
	static GLuint frameIndices4D0[] =
	{
		0,1,
		2,3,
		4,5,
		6,7,
		8,22,
		9,23,
		10,20,
		11,21,
		12,18,
		13,19,
		14,16,
		15,17
	};
}
