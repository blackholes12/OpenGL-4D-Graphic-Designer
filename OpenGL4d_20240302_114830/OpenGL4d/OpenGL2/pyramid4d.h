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
	static GLuint indices4D0[] =
	{
	8,0,7,4, 
	8,0,3,7, 
	8,5,1,0, 
	8,5,0,4, 
	8,5,2,1, 
	8,5,6,2, 
	8,7,3,6, 
	8,3,2,6, 
	8,3,0,1, 
	8,3,1,2, 
	8,5,4,7, 
	8,6,5,7,
	7,3,2,0, 
	6,2,5,7, 
	4,7,5,0, 
	5,2,1,0, 
	5,2,0,7//bottom
	};
}
