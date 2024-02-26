#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace hexadecachoron {
	static glm::vec4 vertices4D[] =
	{
glm::vec4(0.5, 0 ,0 ,0),
glm::vec4(0, 0, 0, 0.5),
glm::vec4(0, 0, 0.5, 0),
glm::vec4(0, 0.5 ,0 ,0),
glm::vec4(-0.5 ,0, 0, 0),
glm::vec4(0, 0 ,0, -0.5),
glm::vec4(0 ,0 ,-0.5 ,0),
glm::vec4(0, -0.5, 0 ,0)
	};
	static GLuint indices4D0[] =
	{
	7,6,5,4, 
	5,6,7,0, 
	7,6,4,1, 
	0,6,7,1, 
	7,5,0,2, 
	4,5,7,2, 
	0,1,7,2, 
	1,4,7,2, 
	6,5,4,3, 
	0,5,6,3, 
	6,1,0,3, 
	6,4,1,3, 
	4,2,1,3, 
	0,1,2,3, 
	4,5,2,3, 
	2,5,0,3
	};
}
