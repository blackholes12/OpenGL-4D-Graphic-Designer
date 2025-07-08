#pragma once

//#include<glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

struct Vertex4D
{
	glm::vec4 positions4D[4];

	glm::vec3 texcoords3D[4];

	glm::vec4 normals4D[4];

	glm::uint id;
};

struct LineVertex4D
{
	glm::vec4 pos4D;
	glm::vec3 color;
};

struct FrameVertex4D
{
	glm::vec4 pos4D;
};

struct Vertex2D
{
	glm::vec2 position2D;
	glm::vec2 texcoord;
};

struct Edge4D
{
	glm::vec4 vertices4D[2];
	//explicit Edge4D(glm::vec4 vertex1, glm::vec4 vertex2)
	//{
	//	this->vertices4D[0] = vertex1, this->vertices4D[1] = vertex2;
	//}
};

struct Face4D
{
	glm::vec4 vertices4D[3];
};

struct Tetra4D
{
	glm::vec4 vertices4D[4];
};

struct Cube4D
{
	glm::vec4 vertices4D[4];
	glm::vec4 normal4D;
	int direction4D;
	explicit Cube4D(glm::vec4 vertex1, glm::vec4 vertex2, glm::vec4 vertex3, glm::vec4 vertex4, glm::vec4 normal, int direction4D)
	{
		this->vertices4D[0] = vertex1, this->vertices4D[1] = vertex2, this->vertices4D[2] = vertex3, this->vertices4D[3] = vertex4;
		this->normal4D = normal;
		this->direction4D = direction4D;
	}
};



