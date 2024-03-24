#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace hypercube {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, 0.5f, -0.5f,0.5f)
	};
	static GLuint indices4D0[] =
	{
		7,0,2,3, 
		6,7,5,2, 
		4,0,5,7, 
		5,0,1,2, 
		5,7,0,2, 
		6,1,10,2, 
		14,6,13,10, 
		5,1,13,6, 
		13,1,9,10, 
		13,6,1,10,
		15,3,10,11, 
		14,15,6,10, 
		7,3,6,15, 
		6,3,2,10, 
		6,15,3,10, 
		15,8,3,11, 
		7,15,4,3, 
		12,8,4,15, 
		4,8,0,3, 
		4,15,8,3,
		4,8,1,0, 
		5,4,13,1, 
		12,8,13,4, 
		13,8,9,1, 
		13,4,8,1, 
		3,8,10,11, 
		2,3,1,10, 
		0,8,1,3, 
		1,8,9,10, 
		1,3,8,10,
		15,4,6,7, 
		14,15,13,6, 
		12,4,13,15, 
		13,4,5,6, 
		13,15,4,6, 
		15,11,10,8, 
		14,10,13,15, 
		12,15,13,8, 
		13,10,9,8, 
		13,10,8,15
	};

	struct line4D
	{
		glm::vec4 vertices4D[2];
	};

	struct tetraFaceTetra4D
	{
		glm::vec4 vertices4D[3];
		glm::vec4 tetraNormals4D[2];
	};
	
	static line4D lines4D[32] =
	{
		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),//0
		glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),
		glm::vec4(0.5f, 0.5f, -0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),
		glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(0.5f, -0.5f, -0.5f,0.5f),glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),

		glm::vec4(0.5f, 0.5f,0.5f,0.5f),   glm::vec4(0.5f, -0.5f, 0.5f,0.5f),//8
		glm::vec4(-0.5f,0.5f, 0.5f,0.5f),  glm::vec4(-0.5f,-0.5f,  0.5f,0.5f),
		glm::vec4(0.5f, 0.5f,-0.5f,0.5f),  glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(0.5f, 0.5f,0.5f,-0.5f),  glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(-0.5f,0.5f, -0.5f,0.5f), glm::vec4(-0.5f,-0.5f,  -0.5f,0.5f),
		glm::vec4(-0.5f,0.5f, 0.5f,-0.5f), glm::vec4(-0.5f,-0.5f,  0.5f,-0.5f),
		glm::vec4(0.5f, 0.5f,-0.5f,-0.5f), glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
		glm::vec4(-0.5f,0.5f, -0.5f,-0.5f),glm::vec4(-0.5f,-0.5f,  -0.5f,-0.5f),

		glm::vec4(0.5f, 0.5f,  0.5f,0.5f), glm::vec4(0.5f, 0.5f,  -0.5f,0.5f), //16
		glm::vec4(-0.5f, 0.5f, 0.5f,0.5f), glm::vec4(-0.5f, 0.5f, -0.5f,0.5f), 
		glm::vec4(0.5f, -0.5f, 0.5f,0.5f), glm::vec4(0.5f, -0.5f, -0.5f,0.5f), 
		glm::vec4(0.5f, 0.5f,  0.5f,-0.5f),glm::vec4(0.5f, 0.5f,  -0.5f,-0.5f),
		glm::vec4(-0.5f, -0.5f,0.5f,0.5f), glm::vec4(-0.5f, -0.5f,-0.5f,0.5f), 
		glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
		glm::vec4(-0.5f, -0.5f,0.5f,-0.5f),glm::vec4(-0.5f, -0.5f,-0.5f,-0.5f),

		glm::vec4(0.5f, 0.5f,  0.5f ,0.5f),glm::vec4(0.5f, 0.5f,  0.5f ,-0.5f), //24
		glm::vec4(-0.5f, 0.5f, 0.5f ,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f ,-0.5f),
		glm::vec4(0.5f, -0.5f, 0.5f ,0.5f),glm::vec4(0.5f, -0.5f, 0.5f ,-0.5f),
		glm::vec4(0.5f, 0.5f,  -0.5f,0.5f),glm::vec4(0.5f, 0.5f,  -0.5f,-0.5f),
		glm::vec4(-0.5f, -0.5f,0.5f ,0.5f),glm::vec4(-0.5f, -0.5f,0.5f ,-0.5f),
		glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0.5f, -0.5f, -0.5f,0.5f),glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
		glm::vec4(-0.5f, -0.5f,-0.5f,0.5f),glm::vec4(-0.5f, -0.5f,-0.5f,-0.5f)
	};
	static tetraFaceTetra4D tetraFaceTetras4D[24] =
	{
		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, 0.5f,0.5f),
		glm::vec4(0,0,1,0),glm::vec4(0,0,0,1),

		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, 0.5f, -0.5f,0.5f),
		glm::vec4(0,1,0,0),glm::vec4(0,0,0,1),

		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),

		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(0.5f, 0.5f, -0.5f,0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,0,0,1),

		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,0,1,0),

		glm::vec4(0.5f, 0.5f, 0.5f,0.5f),glm::vec4(0.5f, 0.5f, -0.5f,0.5f),glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),


		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0,0,-1,0),glm::vec4(0,0,0,-1),

		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(0,-1,0,0),glm::vec4(0,0,0,-1),

		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(0,-1,0,0),glm::vec4(0,0,-1,0),

		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,0,0,-1),

		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,0,-1,0),

		glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,-1,0,0),


		glm::vec4(0.5f, 0.5f, -0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(0,0,-1,0),glm::vec4(0,0,0,1),

		glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
		glm::vec4(0,-1,0,0),glm::vec4(0,0,0,1),

		glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(0,-1,0,0),glm::vec4(0,0,1,0),

		glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,0,0,1),

		glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,0,1,0),

		glm::vec4(-0.5f, 0.5f, 0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),
		glm::vec4(-1,0,0,0),glm::vec4(0,1,0,0),


		glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(0,0,1,0),glm::vec4(0,0,0,-1),

		glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(-0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0,1,0,0),glm::vec4(0,0,0,-1),

		glm::vec4(0.5f, 0.5f, -0.5f,0.5f),glm::vec4(-0.5f, 0.5f, -0.5f,0.5f),glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(0,1,0,0),glm::vec4(0,0,-1,0),

		glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,0,0,-1),

		glm::vec4(0.5f, 0.5f, -0.5f,0.5f),glm::vec4(0.5f, -0.5f, -0.5f,0.5f),glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,0,-1,0),

		glm::vec4(0.5f, -0.5f, 0.5f,0.5f),glm::vec4(0.5f, -0.5f, -0.5f,0.5f),glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
		glm::vec4(1,0,0,0),glm::vec4(0,-1,0,0),
	};
}
