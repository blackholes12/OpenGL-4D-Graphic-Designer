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

	glm::ivec3 cubeIndex_XZW;

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


