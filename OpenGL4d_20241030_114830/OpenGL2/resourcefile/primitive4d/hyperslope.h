#pragma once
namespace hyperslope {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(-0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, 0.5f,-0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,-0.5f),
	glm::vec4(-0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(-0.5f, -0.5f, -0.5f,0.5f),
	glm::vec4(0.5f, 0.5f, 0.5f,0.5f),
	glm::vec4(0.5f, 0.5f, -0.5f,0.5f)
	};
	static glm::vec4 normals4D[] =
	{
		glm::vec4(0,0,0,-1),
		glm::vec4(1,0,0,0),
		glm::vec4(0,0,-1,0),
		glm::vec4(-0.707107,0.707107,0,0),
		glm::vec4(0,0,1,0),
		glm::vec4(0,-1,0,0),
		glm::vec4(0,0,0,1)
	};
	static glm::ivec2 indices4D0[] =
	{
		glm::ivec2(5,0),glm::ivec2(0,0),glm::ivec2(2,0),glm::ivec2(3,0),
		glm::ivec2(4,0),glm::ivec2(0,0),glm::ivec2(1,0),glm::ivec2(2,0),
		glm::ivec2(4,0),glm::ivec2(5,0),glm::ivec2(0,0),glm::ivec2(2,0),
		glm::ivec2(5,1),glm::ivec2(1,1),glm::ivec2(8,1),glm::ivec2(2,1),
		glm::ivec2(11,1),glm::ivec2(5,1),glm::ivec2(10,1),glm::ivec2(8,1),
		glm::ivec2(4,1),glm::ivec2(1,1),glm::ivec2(10,1),glm::ivec2(5,1),
		glm::ivec2(10,1),glm::ivec2(1,1),glm::ivec2(7,1),glm::ivec2(8,1),
		glm::ivec2(10,1),glm::ivec2(5,1),glm::ivec2(1,1),glm::ivec2(8,1),
		glm::ivec2(11,2),glm::ivec2(3,2),glm::ivec2(8,2),glm::ivec2(9,2),
		glm::ivec2(5,2),glm::ivec2(3,2),glm::ivec2(2,2),glm::ivec2(8,2),
		glm::ivec2(5,2),glm::ivec2(11,2),glm::ivec2(3,2),glm::ivec2(8,2),
		glm::ivec2(11,3),glm::ivec2(6,3),glm::ivec2(3,3),glm::ivec2(9,3),
		glm::ivec2(5,3),glm::ivec2(11,3),glm::ivec2(4,3),glm::ivec2(3,3),
		glm::ivec2(10,3),glm::ivec2(6,3),glm::ivec2(4,3),glm::ivec2(11,3),
		glm::ivec2(4,3),glm::ivec2(6,3),glm::ivec2(0,3),glm::ivec2(3,3),
		glm::ivec2(4,3),glm::ivec2(11,3),glm::ivec2(6,3),glm::ivec2(3,3),
		glm::ivec2(4,4),glm::ivec2(6,4),glm::ivec2(1,4),glm::ivec2(0,4),
		glm::ivec2(10,4),glm::ivec2(6,4),glm::ivec2(7,4),glm::ivec2(1,4),
		glm::ivec2(10,4),glm::ivec2(4,4),glm::ivec2(6,4),glm::ivec2(1,4),
		glm::ivec2(3,5),glm::ivec2(6,5),glm::ivec2(8,5),glm::ivec2(9,5),
		glm::ivec2(2,5),glm::ivec2(3,5),glm::ivec2(1,5),glm::ivec2(8,5),
		glm::ivec2(0,5),glm::ivec2(6,5),glm::ivec2(1,5),glm::ivec2(3,5),
		glm::ivec2(1,5),glm::ivec2(6,5),glm::ivec2(7,5),glm::ivec2(8,5),
		glm::ivec2(1,5),glm::ivec2(3,5),glm::ivec2(6,5),glm::ivec2(8,5),
		glm::ivec2(11,6),glm::ivec2(9,6),glm::ivec2(8,6),glm::ivec2(6,6),
		glm::ivec2(10,6),glm::ivec2(8,6),glm::ivec2(7,6),glm::ivec2(6,6),
		glm::ivec2(10,6),glm::ivec2(8,6),glm::ivec2(6,6),glm::ivec2(11,6)
	};
}
