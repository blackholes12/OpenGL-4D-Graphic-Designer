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
	static GLuint indices4D0[] =
	{
	6,5,2,4, 
	5,2,4,1, 
	4,1,2,0, 
	7,4,3,5, 
	5,1,4,3, 
	4,0,3,1, 
	6,4,2,7, 
	7,3,4,2, 
	4,0,2,3 ,
	6,7,2,5, 
	5,1,7,2, 
	7,3,2,1,
	3,2,1,0, 
	7,4,5,6//bottom
	};
}