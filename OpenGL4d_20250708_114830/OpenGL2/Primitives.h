#pragma once
#define Pi 3.1415926535f
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include"Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices,
		const unsigned int sizeOfVertices,
		const GLuint* indices,
		const unsigned int sizeOfIndices)
	{
		this->vertices.clear();
		this->indices.clear();
		for (size_t i = 0; i < sizeOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < sizeOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}
	
	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline size_t getsizeOfVertices() { return this->vertices.size(); }
	inline size_t getsizeOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
	Triangle()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2	//Triangle 1
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};

class Quad : public Primitive
{
public:
	Quad()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,	//Triangle 1
			0, 2, 3		//Triangle 2
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};

class Pyramid : public Primitive
{
public:
	Pyramid()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			//Triangle front
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 1.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 1.f),

			//Triangle left
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 1.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 1.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 1.f, 0.f),

			//Triangle back
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 1.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, -1.f),

			//Triangles right
			glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 1.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 1.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 1.f, 0.f),
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);
		GLuint indices[] =
		{
			0, 1, 2,
			3, 4, 5,

			6, 7, 8,
			9, 10, 11

			
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};

class Cube : public Primitive
{
public:
	Cube()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),

			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),

			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(-0.5f,- 0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),

			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
	
};
class Room : public Primitive
{
public:
	Room()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(10.f, 3.5f, 10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(10.f, -0.5f, 10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-10.f, -0.5f, 10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-10.f, 3.5f, 10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

			glm::vec3(-10.f, 3.5f, -10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-10.f, -0.5f, -10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(10.f, -0.5f, -10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(10.f, 3.5f, -10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(10.f, 3.5f, -10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, -0.5f, -10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, -0.5f, 10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, 3.5f, 10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),

			glm::vec3(-10.f, 3.5f, 10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, -0.5f, 10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, -0.5f, -10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, 3.5f, -10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),

			glm::vec3(-10.f, 3.5f, 10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(-10.f, 3.5f, -10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(10.f, 3.5f, -10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(10.f, 3.5f, 10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),

			glm::vec3(-10.f, -0.5f, -10.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(-10.f, -0.5f, 10.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(10.f, -0.5f, 10.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(10.f, -0.5f, -10.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};
class SkyBox : public Primitive
{
public:
	SkyBox()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(10.f, 10.f, 10.f),			glm::vec3(1.f, 1.f, 1.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(10.f, -10.f, 10.f),			glm::vec3(1.f, -1.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-10.f, -10.f, 10.f),			glm::vec3(-1.f, -1.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-10.f, 10.f, 10.f),			glm::vec3(-1.f, 1.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

			glm::vec3(-10.f, 10.f, -10.f),			glm::vec3(-1.f, 1.f, -1.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-10.f, -10.f, -10.f),			glm::vec3(-1.f, -1.f, -1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(10.f, -10.f, -10.f),			glm::vec3(1.f, -1.f, -1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(10.f, 10.f, -10.f),			glm::vec3(1.f, 1.f, -1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(10.f, 10.f, -10.f),			glm::vec3(1.f, 1.f, -1.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, -10.f, -10.f),			glm::vec3(1.f, -1.f, -1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, -10.f, 10.f),			glm::vec3(1.f, -1.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(10.f, 10.f, 10.f),			glm::vec3(1.f, 1.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),

			glm::vec3(-10.f, 10.f, 10.f),			glm::vec3(-1.f, 1.f, 1.f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, -10.f, 10.f),			glm::vec3(-1.f, -1.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, -10.f, -10.f),			glm::vec3(-1.f, -1.f, -1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(-10.f, 10.f, -10.f),			glm::vec3(-1.f, 1.f, -1.f),		glm::vec2(1.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),

			glm::vec3(-10.f, 10.f, 10.f),			glm::vec3(-1.f, 1.f, 1.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(-10.f, 10.f, -10.f),			glm::vec3(-1.f, 1.f, -1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(10.f, 10.f, -10.f),			glm::vec3(1.f, 1.f, -1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(10.f, 10.f, 10.f),			glm::vec3(1.f, 1.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),

			glm::vec3(-10.f, -10.f, -10.f),			glm::vec3(-1.f, -1.f, -1.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(-10.f, -10.f, 10.f),			glm::vec3(-1.f, -1.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(10.f, -10.f, 10.f),			glm::vec3(1.f, -1.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(10.f, -10.f, -10.f),			glm::vec3(1.f, -1.f, -1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
		};
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8, 9, 10,
			8, 10, 11,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};
class Sphere : public Primitive
{
public:
	Sphere()
		: Primitive()
	{
		const int grid_x = 120;
		const int grid_y = 110;
		const int point_x= grid_x+1;
		const int point_y = grid_y + 1;
		int i, j,point_index,grid_index;
		float angle_x, angle_y;
		Vertex vertices[point_x * point_y];
		for (j = 0; j < point_y; j++) 
		{
			angle_y = (j / (float)grid_y-0.5f)* Pi;
			for (i = 0; i < point_x; i++)
			{
				angle_x = 2*Pi*i / (float)grid_x;
				point_index = point_x * j + i;
				vertices[point_index].position =
				vertices[point_index].color =
				vertices[point_index].normal = glm::vec3(sin(angle_x)*cos(angle_y),
				sin(angle_y),
					cos(angle_x) *cos(angle_y)
				);
				vertices[point_index].texcoord = glm::vec2(i/ (float)grid_x,j/ (float)grid_y);
			}
		}
		unsigned sizeOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[grid_x* grid_y*6];
		for (j = 0; j < grid_y; j++)
		{
			for (i = 0; i < grid_x; i++)
			{
				grid_index = (grid_x * j + i)*6;
				point_index = point_x * j + i;
				indices[grid_index] = point_index+1;
				indices[grid_index+1] = point_index+ point_x;
				indices[grid_index + 2] = point_index;
				indices[grid_index+3] = point_index+1;
				indices[grid_index + 4] = point_index + point_x+1;
				indices[grid_index + 5] = point_index + point_x;
			}
		}
		unsigned sizeOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, sizeOfVertices, indices, sizeOfIndices);
	}
};

