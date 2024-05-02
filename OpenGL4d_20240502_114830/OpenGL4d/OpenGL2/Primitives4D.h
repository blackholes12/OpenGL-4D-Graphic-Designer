#pragma once

#include<vector>
#include"Vertex.h"
#include"resourcefile/primitive4d/triPrism.h"
#include"resourcefile/primitive4d/hyperslope.h"
//#include"resourcefile/primitive4d/hypercone.h"
#include"resourcefile/primitive4d/hypercube.h"
#include"resourcefile/primitive4d/quad4d.h"
#include"resourcefile/primitive4d/doublequads4d.h"
#include"resourcefile/primitive4d/box4d.h"
#include"resourcefile/primitive4d/waterbox4d.h"
#include"resourcefile/primitive4d/pentachoron.h"
#include"resourcefile/primitive4d/pyramid4d.h"
#include"resourcefile/primitive4d/hexadecachoron.h"
#include"resourcefile/primitive4d/hexacosichoron.h"
#include"Geometry.h"
#include"resourcefile/frame4d/hypercube_frame.h"
#include"resourcefile/frame4d/hypersphere_frame.h"
#include"resourcefile/frame4d/hypercapsule_frame.h"
#include"resourcefile/frame4d/particle4d_frame.h"

class Primitive4D
{
private:
	Vertex4D* vertices4D;
	unsigned sizeOfVertices4D;
	GLuint* indices4D;
	unsigned sizeOfIndices4D;
	FrameVertex4D* frameVertices4D;
	unsigned sizeOfFrameVertices4D;
	GLuint* frameIndices4D;
	unsigned sizeOfFrameIndices4D;
	glm::vec4 normals4D;
public:
	glm::vec4* vertexData4D;
	glm::vec4* normalData4D;
	const char* primitiveName;
	glm::vec4 scale4D;
	Primitive4D() {}
	virtual ~Primitive4D() 
	{ 
		this->vertices4D = nullptr;
		this->indices4D = nullptr;
		this->frameVertices4D = nullptr;
		this->frameIndices4D = nullptr;
		this->vertexData4D = nullptr;
		this->normalData4D = nullptr;
		this->primitiveName = nullptr;
	}

	void deleteFunction()
	{
		delete[] this->vertices4D;
		delete[] this->indices4D;
		delete[] this->frameVertices4D;
		delete[] this->frameIndices4D;
		delete[] this->vertexData4D;
		delete[] this->normalData4D;
		this->vertices4D = nullptr;
		this->indices4D = nullptr;
		this->frameVertices4D = nullptr;
		this->frameIndices4D = nullptr;
		this->vertexData4D = nullptr;
		this->normalData4D = nullptr;
		this->primitiveName = nullptr;
	}
	//Functions
	void set(const Vertex4D* vertices4D,
		const unsigned int sizeOfVertices4D,
		const GLuint* indices4D,
		const unsigned int sizeOfIndices4D)
	{
		this->vertices4D = new Vertex4D[sizeOfVertices4D];
		this->sizeOfVertices4D = sizeOfVertices4D;
		this->indices4D = new GLuint[sizeOfIndices4D];
		this->sizeOfIndices4D = sizeOfIndices4D;
		for (unsigned i = 0; i < sizeOfVertices4D; i++)
		{this->vertices4D[i]=vertices4D[i];}
		for (unsigned i = 0; i < sizeOfIndices4D; i++)
		{this->indices4D[i]=indices4D[i];}
	}
	inline Vertex4D* get_vertices4D() { return this->vertices4D; }
	inline GLuint* get_indices4D() { return this->indices4D; }
	inline unsigned get_size_of_vertices4D() { return this->sizeOfVertices4D; }
	inline unsigned get_size_of_indices4D() { return this->sizeOfIndices4D; }

	void set2(glm::vec4* points4D,const unsigned int sizeOfpoints4D, unsigned int* indices4D0, const unsigned int sizeOfTetra, glm::vec4 scale4D)
	{
		FrameVertex4D* frameVertices4d;
		GLuint* frameIndices4d;
		unsigned sizeOfFrameVertices4D;
		unsigned sizeOfFrameIndices4D;
		bool isMesh = false;
		if (this->primitiveName == "Hypercube")
		{
			sizeOfFrameVertices4D = sizeof(hypercube_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypercube_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i = 0; i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercube_frame::frameVertices4D[i];
			}
			for (unsigned i = 0; i < sizeOfFrameIndices4D; i++)
			{
				frameIndices4d[i] = hypercube_frame::frameIndices4D0[i];
			}
		}
		else if (this->primitiveName == "Hypersphere"|| this->primitiveName == "Hyperspherecol")
		{
			sizeOfFrameVertices4D = sizeof(hypersphere_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypersphere_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i = 0; i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypersphere_frame::frameVertices4D[i];
			}
			for (unsigned i = 0; i < sizeOfFrameIndices4D; i++)
			{
				frameIndices4d[i] = hypersphere_frame::frameIndices4D0[i];
			}
		}
		else if (this->primitiveName == "Hypercapsule")
		{
			sizeOfFrameVertices4D = sizeof(hypercapsule_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypercapsule_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i = 0; i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercapsule_frame::frameVertice4D(scale4D, i);
			}
			for (unsigned i = 0; i < sizeOfFrameIndices4D; i++)
			{
				frameIndices4d[i] = hypercapsule_frame::frameIndices4D0[i];
			}
		}
		else if (this->primitiveName == "Particle4d")
		{
			sizeOfFrameVertices4D = sizeof(particle4d_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(particle4d_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i = 0; i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = particle4d_frame::frameVertices4D[i];
			}
			for (unsigned i = 0; i < sizeOfFrameIndices4D; i++)
			{
				frameIndices4d[i] = particle4d_frame::frameIndices4D0[i];
			}
		}
		else
		{
			sizeOfFrameVertices4D = sizeOfpoints4D;
			sizeOfFrameIndices4D = 12 * sizeOfTetra;
			frameVertices4d = new FrameVertex4D[sizeOfpoints4D];
			frameIndices4d = new GLuint[12 * sizeOfTetra];
			for (GLuint j = 0; j < sizeOfpoints4D; j++)
			{
				frameVertices4d[j].pos4D = points4D[j];
			}
			for (GLuint j = 0; j < sizeOfTetra; j++)
			{
				frameIndices4d[12 * j + 0] = indices4D0[4 * j];
				frameIndices4d[12 * j + 1] = indices4D0[4 * j + 1];
				frameIndices4d[12 * j + 2] = indices4D0[4 * j];
				frameIndices4d[12 * j + 3] = indices4D0[4 * j + 2];
				frameIndices4d[12 * j + 4] = indices4D0[4 * j];
				frameIndices4d[12 * j + 5] = indices4D0[4 * j + 3];
				frameIndices4d[12 * j + 6] = indices4D0[4 * j + 1];
				frameIndices4d[12 * j + 7] = indices4D0[4 * j + 2];
				frameIndices4d[12 * j + 8] = indices4D0[4 * j + 1];
				frameIndices4d[12 * j + 9] = indices4D0[4 * j + 3];
				frameIndices4d[12 * j + 10] = indices4D0[4 * j + 2];
				frameIndices4d[12 * j + 11] = indices4D0[4 * j + 3];
			}
			isMesh = true;
		}
		this->frameVertices4D = new FrameVertex4D[sizeOfFrameVertices4D];
		this->sizeOfFrameVertices4D = sizeOfFrameVertices4D;
		this->frameIndices4D = new GLuint[sizeOfFrameIndices4D];
		this->sizeOfFrameIndices4D = 0;
		for (unsigned i = 0; i < sizeOfFrameVertices4D; i++)
		{
			this->frameVertices4D[i]=frameVertices4d[i];
		}
		for (unsigned i = 0; i < sizeOfFrameIndices4D/2; i++)
		{
			bool isOverlap = false;
			if (isMesh)
			{
				for (unsigned j = 0; j < i; j++)
				{
					if ((this->frameVertices4D[frameIndices4d[2 * i]].pos4D == this->frameVertices4D[frameIndices4d[2 * j]].pos4D
						&& this->frameVertices4D[frameIndices4d[2 * i + 1]].pos4D == this->frameVertices4D[frameIndices4d[2 * j + 1]].pos4D) ||
						(this->frameVertices4D[frameIndices4d[2 * i]].pos4D == this->frameVertices4D[frameIndices4d[2 * j + 1]].pos4D
							&& this->frameVertices4D[frameIndices4d[2 * i + 1]].pos4D == this->frameVertices4D[frameIndices4d[2 * j]].pos4D))
					{
						isOverlap = true;
					}
				}
			}
			if (!isOverlap)
			{
				this->frameIndices4D[this->sizeOfFrameIndices4D]=frameIndices4d[2 * i];
				this->frameIndices4D[this->sizeOfFrameIndices4D+1]=frameIndices4d[2 * i + 1];
				this->sizeOfFrameIndices4D += 2;
			}
		}
	}
	inline FrameVertex4D* get_frame_vertices4D() { return this->frameVertices4D; }
	inline GLuint* get_frame_indices4D() { return this->frameIndices4D; }
	inline unsigned get_size_of_frame_vertices4D() { return this->sizeOfFrameVertices4D; }
	inline unsigned get_size_of_frame_indices4D() { return this->sizeOfFrameIndices4D; }
	
	void set_vertex_data(glm::vec4* points4D, unsigned int* indices4D0, unsigned int size)
	{
		this->vertexData4D = new glm::vec4[size];
		for (unsigned i = 0; i < size; i++) {
			this->vertexData4D[i] = points4D[indices4D0[i]];
		}
	}

	void set_normal_data(glm::vec4* points4D, unsigned int* indices4D0, unsigned int size)
	{
		this->normalData4D = new glm::vec4[size];
		for (unsigned i = 0; i < size/4; i++) {
			glm::vec4 normal4D= normalize(cross4d(points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 1]], points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 2]], points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 3]]));
			for(int j=0;j<4;j++)
			this->normalData4D[4*i+j] = normal4D;
		}
	}

	void transform_vertex4D(glm::vec4* points4D, const unsigned int sizeOfpoints4D, unsigned int* indices4D0, const unsigned int sizeOfTetra, Vertex4D* vertices4d, GLuint* indices4d,glm::vec4 scale4D) {
		this->set_vertex_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->set_normal_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->scale4D = scale4D;
		for (unsigned j = 0;j < sizeOfTetra;j++) {
			this->normals4D = normalize(cross4d(points4D[indices4D0[4 * j]] - points4D[indices4D0[4 * j + 1]], points4D[indices4D0[4 * j]] - points4D[indices4D0[4 * j + 2]], points4D[indices4D0[4 * j]] - points4D[indices4D0[4 * j + 3]]));
			glm::vec4 point_A = points4D[indices4D0[4 * j]];
			glm::vec4 point_B = points4D[indices4D0[4 * j + 1]];
			glm::vec4 point_C = points4D[indices4D0[4 * j + 2]];
			glm::vec4 point_D = points4D[indices4D0[4 * j + 3]];
			//if (this->primitiveName == "Hyperslope")
			//{
			//	if (dot(this->normals4D, point_A) > -1.f)
			//	{
			//		std::cout << j << "\n";
			//	}
			//	else
			//	{
			//		std::cout <<"need to delete" << j << "\n";
			//	}
			//}
			glm::vec3 texcoord_A = texcoord_position(this->normals4D, points4D[indices4D0[4 * j]] * scale4D);
			glm::vec3 texcoord_B = texcoord_position(this->normals4D, points4D[indices4D0[4 * j + 1]] * scale4D);
			glm::vec3 texcoord_C = texcoord_position(this->normals4D, points4D[indices4D0[4 * j + 2]] * scale4D);
			glm::vec3 texcoord_D = texcoord_position(this->normals4D, points4D[indices4D0[4 * j + 3]] * scale4D);
			glm::vec4 normal_A = this->normals4D;
			glm::vec4 normal_B = this->normals4D;
			glm::vec4 normal_C = this->normals4D;
			glm::vec4 normal_D = this->normals4D;
			for (GLuint i = 0;i < 4;i++) {

				vertices4d[i + 4 * j].positions4D[0] = point_A;
				vertices4d[i + 4 * j].positions4D[1] = point_B;
				vertices4d[i + 4 * j].positions4D[2] = point_C;
				vertices4d[i + 4 * j].positions4D[3] = point_D;

				vertices4d[i + 4 * j].texcoords3D[0] = texcoord_A;
				vertices4d[i + 4 * j].texcoords3D[1] = texcoord_B;
				vertices4d[i + 4 * j].texcoords3D[2] = texcoord_C;
				vertices4d[i + 4 * j].texcoords3D[3] = texcoord_D;

				vertices4d[i + 4 * j].normals4D[0] = normal_A;
				vertices4d[i + 4 * j].normals4D[1] = normal_B;
				vertices4d[i + 4 * j].normals4D[2] = normal_C;
				vertices4d[i + 4 * j].normals4D[3] = normal_D;

				vertices4d[i + 4 * j].id = i;
			}
			indices4d[6 * j] = 4 * j;
			indices4d[6 * j + 1] = 4 * j + 1;
			indices4d[6 * j + 2] = 4 * j + 2;
			indices4d[6 * j + 3] = 4 * j;
			indices4d[6 * j + 4] = 4 * j + 2;
			indices4d[6 * j + 5] = 4 * j + 3;
		}

		this->set(vertices4d, 4 * sizeOfTetra, indices4d, 6 * sizeOfTetra);
		this->set2(points4D, sizeOfpoints4D, indices4D0, sizeOfTetra, scale4D);
	}

	void transform_vertex4D(glm::vec4* points4D, const unsigned int sizeOfpoints4D, glm::vec4* normal4d, unsigned int* indices4D0, const unsigned int sizeOfTetra, Vertex4D* vertices4d, GLuint* indices4d, glm::vec4 scale4D) {
		this->set_vertex_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->set_normal_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->scale4D = scale4D;
		for (unsigned j = 0; j < sizeOfTetra; j++) {
			glm::vec4 point_A = points4D[indices4D0[4 * j]];
			glm::vec4 point_B = points4D[indices4D0[4 * j + 1]];
			glm::vec4 point_C = points4D[indices4D0[4 * j + 2]];
			glm::vec4 point_D = points4D[indices4D0[4 * j + 3]];
			glm::vec4 normalAverage = normal4d[indices4D0[4 * j]] + normal4d[indices4D0[4 * j + 1]] + normal4d[indices4D0[4 * j + 2]] + normal4d[indices4D0[4 * j + 3]];
			glm::vec3 texcoord_A = texcoord_position2(normalAverage, points4D[indices4D0[4 * j]] * scale4D);
			glm::vec3 texcoord_B = texcoord_position2(normalAverage, points4D[indices4D0[4 * j + 1]] * scale4D);
			glm::vec3 texcoord_C = texcoord_position2(normalAverage, points4D[indices4D0[4 * j + 2]] * scale4D);
			glm::vec3 texcoord_D = texcoord_position2(normalAverage, points4D[indices4D0[4 * j + 3]] * scale4D);
			glm::vec4 normal_A = normal4d[indices4D0[4 * j]];
			glm::vec4 normal_B = normal4d[indices4D0[4 * j + 1]];
			glm::vec4 normal_C = normal4d[indices4D0[4 * j + 2]];
			glm::vec4 normal_D = normal4d[indices4D0[4 * j + 3]];
			for (GLuint i = 0; i < 4; i++) {

				vertices4d[i + 4 * j].positions4D[0] = point_A;
				vertices4d[i + 4 * j].positions4D[1] = point_B;
				vertices4d[i + 4 * j].positions4D[2] = point_C;
				vertices4d[i + 4 * j].positions4D[3] = point_D;

				vertices4d[i + 4 * j].texcoords3D[0] = texcoord_A;
				vertices4d[i + 4 * j].texcoords3D[1] = texcoord_B;
				vertices4d[i + 4 * j].texcoords3D[2] = texcoord_C;
				vertices4d[i + 4 * j].texcoords3D[3] = texcoord_D;

				vertices4d[i + 4 * j].normals4D[0] = normal_A;
				vertices4d[i + 4 * j].normals4D[1] = normal_B;
				vertices4d[i + 4 * j].normals4D[2] = normal_C;
				vertices4d[i + 4 * j].normals4D[3] = normal_D;

				vertices4d[i + 4 * j].id = i;
			}
			indices4d[6 * j] = 4 * j;
			indices4d[6 * j + 1] = 4 * j + 1;
			indices4d[6 * j + 2] = 4 * j + 2;
			indices4d[6 * j + 3] = 4 * j;
			indices4d[6 * j + 4] = 4 * j + 2;
			indices4d[6 * j + 5] = 4 * j + 3;
		}

		this->set(vertices4d, 4 * sizeOfTetra, indices4d, 6 * sizeOfTetra);
		this->set2(points4D, sizeOfpoints4D, indices4D0, sizeOfTetra, scale4D);
	}

	void transform_terrain4D(glm::vec4* points4D, glm::vec4* normal4d, glm::ivec3* cubeIndex_XZW,unsigned int* indices4D0,glm::vec4 offset4d, const unsigned int sizeOfTetra, Vertex4D* vertices4d, GLuint* indices4d) {
		this->set_vertex_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->set_normal_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->scale4D = glm::vec4(1.f);
		for (unsigned j = 0;j < sizeOfTetra;j++) {
			glm::vec4 point_A = points4D[indices4D0[4 * j]];
			glm::vec4 point_B = points4D[indices4D0[4 * j + 1]];
			glm::vec4 point_C = points4D[indices4D0[4 * j + 2]];
			glm::vec4 point_D = points4D[indices4D0[4 * j + 3]];
			glm::vec3 texcoord_A = texcoord_position2(points4D[indices4D0[4 * j]]+ offset4d);
			glm::vec3 texcoord_B = texcoord_position2(points4D[indices4D0[4 * j + 1]] + offset4d);
			glm::vec3 texcoord_C = texcoord_position2(points4D[indices4D0[4 * j + 2]] + offset4d);
			glm::vec3 texcoord_D = texcoord_position2(points4D[indices4D0[4 * j + 3]] + offset4d);
			glm::vec4 normal_A = normal4d[indices4D0[4 * j]];
			glm::vec4 normal_B = normal4d[indices4D0[4 * j+1]];
			glm::vec4 normal_C = normal4d[indices4D0[4 * j+2]];
			glm::vec4 normal_D = normal4d[indices4D0[4 * j+3]];
			glm::ivec3 cubeIndex_Xzw = cubeIndex_XZW[4 * j];
			for (GLuint i = 0;i < 4;i++) {

				vertices4d[i + 4 * j].positions4D[0] = point_A;
				vertices4d[i + 4 * j].positions4D[1] = point_B;
				vertices4d[i + 4 * j].positions4D[2] = point_C;
				vertices4d[i + 4 * j].positions4D[3] = point_D;

				vertices4d[i + 4 * j].texcoords3D[0] = texcoord_A;
				vertices4d[i + 4 * j].texcoords3D[1] = texcoord_B;
				vertices4d[i + 4 * j].texcoords3D[2] = texcoord_C;
				vertices4d[i + 4 * j].texcoords3D[3] = texcoord_D;

				vertices4d[i + 4 * j].normals4D[0] = normal_A;
				vertices4d[i + 4 * j].normals4D[1] = normal_B;
				vertices4d[i + 4 * j].normals4D[2] = normal_C;
				vertices4d[i + 4 * j].normals4D[3] = normal_D;

				vertices4d[i + 4 * j].cubeIndex_XZW = cubeIndex_Xzw;

				vertices4d[i + 4 * j].id = i;
			}
			indices4d[6 * j] = 4 * j;
			indices4d[6 * j + 1] = 4 * j + 1;
			indices4d[6 * j + 2] = 4 * j + 2;
			indices4d[6 * j + 3] = 4 * j;
			indices4d[6 * j + 4] = 4 * j + 2;
			indices4d[6 * j + 5] = 4 * j + 3;
		}
		this->set(vertices4d, 4 * sizeOfTetra, indices4d, 6 * sizeOfTetra);
		this->set2(new glm::vec4[0], 0, new unsigned[0], 0, glm::vec4(1.f));
	}
};

class Noneshape : public Primitive4D
{
public:
	Noneshape(): Primitive4D()
	{
		this->primitiveName = "Noneshape";
		this->transform_vertex4D(new glm::vec4[0], 0, new unsigned int[0], 0, new Vertex4D[0], new GLuint[0], glm::vec4(1.f));
	}
	~Noneshape() {
		
	}
};

class TriPrism : public Primitive4D
{
public:
	TriPrism(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "TriPrism";
		const unsigned int sizeOfTetra = sizeof(triPrism::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(triPrism::vertices4D, sizeof(triPrism::vertices4D) / sizeof(glm::vec4), triPrism::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~TriPrism() {
		
	}
};

class Hyperslope : public Primitive4D
{
public:
	Hyperslope(glm::vec4 scale4D) : Primitive4D()
	{
		this->primitiveName = "Hyperslope";
		const unsigned int sizeOfTetra = sizeof(hyperslope::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hyperslope::vertices4D, sizeof(hyperslope::vertices4D) / sizeof(glm::vec4), hyperslope::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hyperslope() {
		
	}
};
#define PI glm::pi<float>()
class Hypersphere : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hypersphere(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypersphere";
		const int length = 8;
		const int width = 16;
		this->points4D =new glm::vec4[width*length* length];
		this->normals4D = new glm::vec4[width * length * length];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				for (int k = 0; k < width; k++)
				{
					glm::vec2 xz = glm::vec2(cos(2.f*PI*(float)(k)/ (float)(width)), sin(2.f * PI * (float)(k) / (float)(width)));
					float rateShift = (float)length / (float)(length - 1);
					float y = sin(PI  * (((float)j* rateShift - (float)length / 2.f) / (float)length));
					float xzRy = cos(PI * (((float)j* rateShift - (float)length / 2.f) / (float)length));
					float w = sin(PI * (((float)i* rateShift - (float)length / 2.f) / (float)length));
					float xyzRw = cos(PI * (((float)i* rateShift - (float)length / 2.f) / (float)length));
					this->points4D[k+width*j+width*length*i] = glm::vec4(0.5*xyzRw*xzRy*xz.x, 0.5 * xyzRw*y, 0.5 * xyzRw*xzRy*xz.y, 0.5 * w);
				}
			}
		}
		for (int i = 0; i < width * length * length; i++)
		{
			this->normals4D[i] = normalize(this->points4D[i]);
		}
		this->indices4D0 = new GLuint[width * (length-1) * (length-1) * 4 * 6];
		int index[8];
		int coordinate[24];
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < length - 1; j++)
			{
				for (int k = 0; k < width; k++)
				{
					if (k == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1+width, index[3] = 0+width,
						index[4] = width - 1+width*length, index[5] = 0 + width * length, 
						index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * j + width * length * i;
						}
					}
					if (k != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
						index[4] = 0 + width * length, index[5] = 1 + width * length,
						index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += k+width * j + width * length * i;
						}
					}
					coordinate[0] = index[5], coordinate[1] = index[3], coordinate[2] = index[1], coordinate[3] = index[0],
					coordinate[4] = index[4], coordinate[5] = index[2], coordinate[6] = index[3], coordinate[7] = index[0],
					coordinate[8] = index[5], coordinate[9] = index[3], coordinate[10] = index[0], coordinate[11] = index[4],
					coordinate[12] = index[7], coordinate[13] = index[6], coordinate[14] = index[2], coordinate[15] = index[4],
					coordinate[16] = index[3], coordinate[17] = index[7], coordinate[18] = index[2], coordinate[19] = index[4],
					coordinate[20] = index[7], coordinate[21] = index[3], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (k + width * j + width * (length-1) * i)+l] = coordinate[l];
					}
				}
			}
		}
		const unsigned int sizeOfTetra = 6 * width * (length - 1) * (length - 1);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(this->points4D, width * length * length, this->normals4D, this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hypersphere() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};

class Hyperspherecol : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hyperspherecol(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hyperspherecol";
		const int length = 8;
		const int width = 16;
		this->points4D = new glm::vec4[width * length * length];
		this->normals4D = new glm::vec4[width * length * length];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				for (int k = 0; k < width; k++)
				{
					glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(k) / (float)(width)), sin(2.f * PI * (float)(k) / (float)(width)));
					float rateShift = (float)length / (float)(length - 1);
					float y = sin(PI * (((float)j * rateShift - (float)length / 2.f) / (float)length));
					float xzRy = cos(PI * (((float)j * rateShift - (float)length / 2.f) / (float)length));
					float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
					float xyzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
					this->points4D[k + width * j + width * length * i] = glm::vec4(0.5 * xyzRw * xzRy * xz.x, -0.5 * xyzRw * y, 0.5 * xyzRw * xzRy * xz.y, 0.5 * w);
				}
			}
		}
		for (int i = 0; i < width * length * length; i++)
		{
			this->normals4D[i] = normalize(this->points4D[i]);
		}
		this->indices4D0 = new GLuint[width * (length - 1) * (length - 1) * 4 * 6];
		int index[8];
		int coordinate[24];
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < length - 1; j++)
			{
				for (int k = 0; k < width; k++)
				{
					if (k == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width,
							index[4] = width - 1 + width * length, index[5] = 0 + width * length,
							index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * j + width * length * i;
						}
					}
					if (k != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
							index[4] = 0 + width * length, index[5] = 1 + width * length,
							index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += k + width * j + width * length * i;
						}
					}
					coordinate[0] = index[5], coordinate[1] = index[3], coordinate[2] = index[1], coordinate[3] = index[0],
						coordinate[4] = index[4], coordinate[5] = index[2], coordinate[6] = index[3], coordinate[7] = index[0],
						coordinate[8] = index[5], coordinate[9] = index[3], coordinate[10] = index[0], coordinate[11] = index[4],
						coordinate[12] = index[7], coordinate[13] = index[6], coordinate[14] = index[2], coordinate[15] = index[4],
						coordinate[16] = index[3], coordinate[17] = index[7], coordinate[18] = index[2], coordinate[19] = index[4],
						coordinate[20] = index[7], coordinate[21] = index[3], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (k + width * j + width * (length - 1) * i) + l] = coordinate[l];
					}
				}
			}
		}
		const unsigned int sizeOfTetra = 6 * width * (length - 1) * (length - 1);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(this->points4D, width * length * length, this->normals4D, this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hyperspherecol() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};

class Hypercapsule : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hypercapsule(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercapsule";
		const int length = 8;
		const int width = 16;
		float radious = glm::min(scale4D.w, glm::min(scale4D.x, scale4D.y)) / 2.f;
		float capsuleLength = scale4D.z;
		this->points4D = new glm::vec4[width * length * length];
		this->normals4D = new glm::vec4[width * length * length];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				for (int k = 0; k < width; k++)
				{
					glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(k) / (float)(width)), sin(2.f * PI * (float)(k) / (float)(width)));
					float rateShift = (float)length / (float)(length - 1);
					float y = sin(PI * (((float)j * rateShift - (float)length / 2.f) / (float)length));
					float xzRy = cos(PI * (((float)j * rateShift - (float)length / 2.f) / (float)length));
					float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
					float xyzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
					glm::vec4 hyperSphereCoordinate = glm::vec4(xyzRw * xzRy * xz.x, xyzRw * xzRy * xz.y, w, xyzRw * y);
					float height = hyperSphereCoordinate.z;
					if (height > 0.f)
					{
						height = glm::mix(1.f - 2.f*radious/ capsuleLength, 1.f,height);
					}
					if (height < 0.f)
					{
						height = -glm::mix(1.f - 2.f * radious/ capsuleLength, 1.f, -height);
					}
					this->points4D[k + width * j + width * length * i] = 0.5f*glm::vec4(hyperSphereCoordinate.x, hyperSphereCoordinate.y, height, hyperSphereCoordinate.w);
					//glm::vec4(0.5 * xyzRw * xzRy * xz.x, 0.5 * xyzRw * y, 0.5 * xyzRw * xzRy * xz.y, 0.5 * w);
					this->normals4D[k + width * j + width * length * i] = normalize(glm::vec4(hyperSphereCoordinate.x, hyperSphereCoordinate.y, hyperSphereCoordinate.z/(2.f* radious/capsuleLength), hyperSphereCoordinate.w));
				}
			}
		}

		this->indices4D0 = new GLuint[width * (length - 1) * (length - 1) * 4 * 6];
		int index[8];
		int coordinate[24];
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < length - 1; j++)
			{
				for (int k = 0; k < width; k++)
				{
					if (k == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width,
							index[4] = width - 1 + width * length, index[5] = 0 + width * length,
							index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * j + width * length * i;
						}
					}
					if (k != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
							index[4] = 0 + width * length, index[5] = 1 + width * length,
							index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += k + width * j + width * length * i;
						}
					}
					coordinate[0] = index[5], coordinate[1] = index[3], coordinate[2] = index[1], coordinate[3] = index[0],
						coordinate[4] = index[4], coordinate[5] = index[2], coordinate[6] = index[3], coordinate[7] = index[0],
						coordinate[8] = index[5], coordinate[9] = index[3], coordinate[10] = index[0], coordinate[11] = index[4],
						coordinate[12] = index[7], coordinate[13] = index[6], coordinate[14] = index[2], coordinate[15] = index[4],
						coordinate[16] = index[3], coordinate[17] = index[7], coordinate[18] = index[2], coordinate[19] = index[4],
						coordinate[20] = index[7], coordinate[21] = index[3], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (k + width * j + width * (length - 1) * i) + l] = coordinate[l];
					}
				}
			}
		}
		const unsigned int sizeOfTetra = 6 * width * (length - 1) * (length - 1);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(this->points4D, width * length * length, this->normals4D, this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hypercapsule() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};

class Hypercylinder : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hypercylinder(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercylinder";
		const int length = 8;
		const int width = 16;
		this->points4D = new glm::vec4[width*length * 4+2];
		this->normals4D = new glm::vec4[width * length * 4 + 2];
		this->indices4D0 = new GLuint[width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2 * 2];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(j) / (float)(width)), sin(2.f * PI * (float)(j) / (float)(width)));
				float rateShift = (float)length / (float)(length - 1);
				float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				float xzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				this->points4D[j + width * i] = glm::vec4(xzRw * xz.x, xzRw * xz.y, 1.f, w)*0.5f;
				this->points4D[width * length+j + width * i] = glm::vec4(xzRw * xz.x, xzRw * xz.y, -1.f,  w)*0.5f;
			}
		}
		for (int i = width * length * 2; i < width * length * 4; i++)
		{
			this->points4D[i] = this->points4D[i- width * length * 2];
		}
		this->points4D[width * length * 4 + 0]= glm::vec4(0, 0, 1.f, 0) *0.5f;
		this->points4D[width * length * 4 + 1]= glm::vec4(0, 0, -1.f, 0) *0.5f;
		for (int i = 0; i < width * length * 2; i++)
		{
			this->normals4D[i] = normalize(glm::vec4(this->points4D[i].x, this->points4D[i].y,0.f, this->points4D[i].w));
		}
		for (int i = width * length * 2; i < width * length * 3; i++)
		{
			this->normals4D[i] = glm::vec4(0, 0, 1.f, 0);
		}
		this->normals4D[width * length * 4]= glm::vec4(0, 0, 1.f, 0);
		for (int i = width * length * 3; i < width * length * 4; i++)
		{
			this->normals4D[i] = glm::vec4(0, 0, -1.f, 0);
		}
		this->normals4D[width * length * 4+1]= glm::vec4(0, 0, -1.f, 0);
		
		{
			int index[8];
			int coordinate[24];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width,
							index[4] = width - 1 + width * length, index[5] = 0 + width * length,
							index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
							index[4] = 0 + width * length, index[5] = 1 + width * length,
							index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[3], coordinate[1] = index[5], coordinate[2] = index[1], coordinate[3] = index[0],
						coordinate[4] = index[2], coordinate[5] = index[4], coordinate[6] = index[3], coordinate[7] = index[0],
						coordinate[8] = index[3], coordinate[9] = index[5], coordinate[10] = index[0], coordinate[11] = index[4],
						coordinate[12] = index[6], coordinate[13] = index[7], coordinate[14] = index[2], coordinate[15] = index[4],
						coordinate[16] = index[7], coordinate[17] = index[3], coordinate[18] = index[2], coordinate[19] = index[4],
						coordinate[20] = index[3], coordinate[21] = index[7], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (j + width * i) + l+ width * (length - 1) * 4 * 2 * 2] = coordinate[l];
					}
				}
			}
		}
		
		{
			int index[4];
			int coordinate[8];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[0], coordinate[1] = index[1], coordinate[2] = index[2], coordinate[3] = width * length * 2 + 0,
					coordinate[4] = index[2], coordinate[5] = index[1], coordinate[6] = index[3], coordinate[7] = width * length * 2 + 0;
					for (int l = 0; l < 8; l++)
					{
						this->indices4D0[8*(j + width * i) + l]= coordinate[l]+width * length * 2;
					}
					coordinate[0] = index[1]+ width * length, coordinate[1] = index[0] + width * length, coordinate[2] = index[2] + width * length, coordinate[3] = width * length * 2 + 1,
					coordinate[4] = index[1] + width * length, coordinate[5] = index[2] + width * length, coordinate[6] = index[3] + width * length, coordinate[7] = width * length * 2 + 1;
					for (int l = 0; l < 8; l++)
					{
						this->indices4D0[8*width * (length - 1) + 8*(j + width * i) + l] = coordinate[l]+ width * length * 2;
					}
				}
			}
		}
		

		const unsigned int sizeOfTetra = (width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2 * 2 )/4;
		this->transform_vertex4D(this->points4D, width* length * 4 + 2,this->normals4D,this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hypercylinder() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};

class Hypercone : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hypercone(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercone";
		const int length = 8;
		const int width = 16;
		this->points4D = new glm::vec4[width * length * 3 + 1];
		this->normals4D = new glm::vec4[width * length * 3 + 1];
		this->indices4D0 = new GLuint[width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(j) / (float)(width)), sin(2.f * PI * (float)(j) / (float)(width)));
				float rateShift = (float)length / (float)(length - 1);
				float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				float xzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				this->points4D[j + width * i] = glm::vec4(0.f, 0.f, 1.f, 0.f) * 0.5f;
				this->points4D[width * length + j + width * i] = glm::vec4(xzRw * xz.x, xzRw * xz.y, -1.f, w) * 0.5f;
			}
		}
		for (int i = width * length * 2; i < width * length * 3; i++)
		{
			this->points4D[i] = this->points4D[i - width * length];
		}
		this->points4D[width * length * 3] = glm::vec4(0, 0, -1.f, 0) * 0.5f;


		for (int i = 0; i < width * length; i++)
		{
			glm::vec4 normal4D = normalize(glm::vec4(this->points4D[i + width * length].x, this->points4D[i + width * length].y, 0.f, this->points4D[i + width * length].w));
			this->normals4D[i] = normalize(glm::vec4(normal4D.x, normal4D.y,0.5f, normal4D.w)/sqrt(1.5f));
		}
		for (int i = width * length; i < 2 * width * length; i++)
		{
			glm::vec4 normal4D = normalize(glm::vec4(this->points4D[i].x, this->points4D[i].y, 0.f, this->points4D[i].w));
			this->normals4D[i] = normalize(glm::vec4(normal4D.x, normal4D.y, 0.5f, normal4D.w) / sqrt(1.5f));
		}
		for (int i = 2*width * length; i < 3*width * length; i++)
		{
			this->normals4D[i] = glm::vec4(0, 0, -1.f, 0);
		}
		this->normals4D[width * length * 3] = glm::vec4(0, 0, -1.f, 0);

		{
			int index[8];
			int coordinate[24];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width,
							index[4] = width - 1 + width * length, index[5] = 0 + width * length,
							index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
							index[4] = 0 + width * length, index[5] = 1 + width * length,
							index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[3], coordinate[1] = index[5], coordinate[2] = index[1], coordinate[3] = index[0],
						coordinate[4] = index[2], coordinate[5] = index[4], coordinate[6] = index[3], coordinate[7] = index[0],
						coordinate[8] = index[3], coordinate[9] = index[5], coordinate[10] = index[0], coordinate[11] = index[4],
						coordinate[12] = index[6], coordinate[13] = index[7], coordinate[14] = index[2], coordinate[15] = index[4],
						coordinate[16] = index[7], coordinate[17] = index[3], coordinate[18] = index[2], coordinate[19] = index[4],
						coordinate[20] = index[3], coordinate[21] = index[7], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (j + width * i) + l + width * (length - 1) * 4 * 2] = coordinate[l];
					}
				}
			}
		}

		{
			int index[4];
			int coordinate[8];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[1] + width * length, coordinate[1] = index[0] + width * length, coordinate[2] = index[2] + width * length, coordinate[3] = width * length*2 + 0,
						coordinate[4] = index[1] + width * length, coordinate[5] = index[2] + width * length, coordinate[6] = index[3] + width * length, coordinate[7] = width * length*2 + 0;
					for (int l = 0; l < 8; l++)
					{
						this->indices4D0[8 * (j + width * i) + l] = coordinate[l]+ width * length;
					}
				}
			}
		}
		unsigned sizeOfpoints4D = width * length * 3 + 1;
		unsigned sizeOfTetra = (width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2) / 4;
		this->transform_vertex4D(this->points4D, sizeOfpoints4D, this->normals4D, this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hypercone() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};

class Hyperpot : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
	GLuint* indices4D0;
public:
	Hyperpot(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hyperpot";
		const int length = 8;
		const int width = 16;
		this->points4D = new glm::vec4[width * length * 8 + 2];
		this->normals4D = new glm::vec4[width * length * 8 + 2];
		this->indices4D0 = new GLuint[width * (length - 1) * 4 * 6 * 3 + width * (length - 1) * 4 * 2 * 2];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(j) / (float)(width)), sin(2.f * PI * (float)(j) / (float)(width)));
				float rateShift = (float)length / (float)(length - 1);
				float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				float xzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));

				this->points4D[j + width * i] = glm::vec4(0.8*xzRw * xz.x, -1.f, 0.8 * xzRw * xz.y, 0.8 * w) * 0.5f;
				this->points4D[width * length + j + width * i] = glm::vec4(xzRw * xz.x, 1.f, xzRw * xz.y, w) * 0.5f;

				this->points4D[width * length * 2 + j + width * i] = glm::vec4(xzRw * xz.x, 1.f, xzRw * xz.y, w) * 0.5f;
				this->points4D[width * length * 3 + j + width * i] = glm::vec4(0.95 * xzRw * xz.x, 1.f, 0.95 * xzRw * xz.y, 0.95 * w) * 0.5f;

				this->points4D[width * length * 4 + j + width * i] = glm::vec4(0.95 * xzRw * xz.x, 1.f, 0.95 * xzRw * xz.y, 0.95 * w) * 0.5f;
				this->points4D[width * length * 5 + j + width * i] = glm::vec4(0.75 * xzRw * xz.x, -0.95f, 0.75 * xzRw * xz.y, 0.75 * w) * 0.5f;
			}
		}
		for (int i = width * length * 6; i < width * length * 7; i++)
		{
			this->points4D[i] = this->points4D[i - width * length * 6];
		}
		for (int i = width * length * 7; i < width * length * 8; i++)
		{
			this->points4D[i] = this->points4D[i - width * length * 2];
		}
		this->points4D[width * length * 8 + 0] = glm::vec4(0, -1.f,0, 0) * 0.5f;
		this->points4D[width * length * 8 + 1] = glm::vec4(0, -0.95f,0, 0) * 0.5f;
		for (int i = 0; i < width * length * 2; i++)
		{
			glm::vec4 normalXZW4D = normalize(glm::vec4(this->points4D[i].x, 0.f, this->points4D[i].y, this->points4D[i].w));
			this->normals4D[i] = normalize(glm::vec4(normalXZW4D.x, -0.2f, normalXZW4D.y, normalXZW4D.w) / sqrt(1.2f));
		}
		for (int i = width * length * 2; i < width * length * 4; i++)
		{
			this->normals4D[i] = glm::vec4(0, 1.f, 0, 0);
		}
		for (int i = width * length * 4; i < width * length * 6; i++)
		{
			glm::vec4 normalXZW4D = normalize(glm::vec4(this->points4D[i].x, 0.f, this->points4D[i].y, this->points4D[i].w));
			this->normals4D[i] = -normalize(glm::vec4(normalXZW4D.x, -0.2f, normalXZW4D.y, normalXZW4D.w) / sqrt(1.2f));
		}
		for (int i = width * length * 6; i < width * length * 7; i++)
		{
			this->normals4D[i] = -normalize(glm::vec4(0.f, 1.f, 0.f,0.f));
		}
		for (int i = width * length * 7; i < width * length * 8; i++)
		{
			this->normals4D[i] = -normalize(glm::vec4(0.f, -1.f, 0.f, 0.f));
		}
		this->normals4D[width * length * 8] = glm::vec4(0, -1.f, 0, 0);
		this->normals4D[width * length * 8 + 1] = glm::vec4(0, 1.f, 0, 0);

		{
			int index[8];
			int coordinate[24];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width,
							index[4] = width - 1 + width * length, index[5] = 0 + width * length,
							index[6] = width - 1 + width + width * length, index[7] = 0 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width,
							index[4] = 0 + width * length, index[5] = 1 + width * length,
							index[6] = 0 + width + width * length, index[7] = 1 + width + width * length;
						for (int l = 0; l < 8; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[3], coordinate[1] = index[5], coordinate[2] = index[1], coordinate[3] = index[0],
						coordinate[4] = index[2], coordinate[5] = index[4], coordinate[6] = index[3], coordinate[7] = index[0],
						coordinate[8] = index[3], coordinate[9] = index[5], coordinate[10] = index[0], coordinate[11] = index[4],
						coordinate[12] = index[6], coordinate[13] = index[7], coordinate[14] = index[2], coordinate[15] = index[4],
						coordinate[16] = index[7], coordinate[17] = index[3], coordinate[18] = index[2], coordinate[19] = index[4],
						coordinate[20] = index[3], coordinate[21] = index[7], coordinate[22] = index[5], coordinate[23] = index[4];
					for (int l = 0; l < 24; l++)
					{
						this->indices4D0[24 * (j + width * i) + l + width * (length - 1) * 4 * 2 * 2] = coordinate[l];
						this->indices4D0[width * (length - 1) * 4 * 6 +
							24 * (j + width * i) + l + width * (length - 1) * 4 * 2 * 2] = coordinate[l] + width * length * 2;
						this->indices4D0[width * (length - 1) * 4 * 6 * 2 +
							24 * (j + width * i) + l + width * (length - 1) * 4 * 2 * 2] = coordinate[l] + width * length * 4;
					}
				}
			}
		}

		{
			int index[4];
			int coordinate[8];
			for (int i = 0; i < length - 1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (j == width - 1)
					{
						index[0] = width - 1, index[1] = 0, index[2] = width - 1 + width, index[3] = 0 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += width * i;
						}
					}
					if (j != width - 1)
					{
						index[0] = 0, index[1] = 1, index[2] = 0 + width, index[3] = 1 + width;
						for (int l = 0; l < 4; l++)
						{
							index[l] += j + width * i;
						}
					}
					coordinate[0] = index[0], coordinate[1] = index[1], coordinate[2] = index[2], coordinate[3] = width * length * 2 + 0,
						coordinate[4] = index[2], coordinate[5] = index[1], coordinate[6] = index[3], coordinate[7] = width * length * 2 + 0;
					for (int l = 0; l < 8; l++)
					{
						this->indices4D0[8 * (j + width * i) + l] = coordinate[l] + width * length * 6;
					}
					coordinate[0] = index[1] + width * length, coordinate[1] = index[0] + width * length, coordinate[2] = index[2] + width * length, coordinate[3] = width * length * 2 + 1,
						coordinate[4] = index[1] + width * length, coordinate[5] = index[2] + width * length, coordinate[6] = index[3] + width * length, coordinate[7] = width * length * 2 + 1;
					for (int l = 0; l < 8; l++)
					{
						this->indices4D0[8 * width * (length - 1) + 8 * (j + width * i) + l] = coordinate[l] + width * length * 6;
					}
				}
			}
		}


		const unsigned int sizeOfTetra = (width * (length - 1) * 4 * 6 * 3 + width * (length - 1) * 4 * 2 * 2) / 4;
		this->transform_vertex4D(this->points4D, width * length * 8 + 2, this->normals4D, this->indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hyperpot() {
		delete[] this->points4D;
		delete[] this->normals4D;
		delete[] this->indices4D0;
		
	}
};


class Hypercube : public Primitive4D
{
public:
	Hypercube(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercube";
		const unsigned int sizeOfTetra = sizeof(hypercube::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hypercube::vertices4D, sizeof(hypercube::vertices4D) / sizeof(glm::vec4), hypercube::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hypercube() {
		
	}
};

class Quad4d : public Primitive4D
{
public:
	Quad4d(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Quad4d";
		const unsigned int sizeOfTetra = sizeof(quad4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(quad4d::vertices4D, sizeof(quad4d::vertices4D) / sizeof(glm::vec4), quad4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Quad4d() {
		
	}
};

class Particle4d : public Primitive4D
{
public:
	Particle4d(): Primitive4D()
	{
		this->primitiveName = "Particle4d";
		const unsigned int sizeOfTetra = sizeof(quad4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(quad4d::vertices4D, sizeof(quad4d::vertices4D) / sizeof(glm::vec4), quad4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], glm::vec4(1.f));
	}
	~Particle4d() {
		
	}
};

class DoubleQuads4d : public Primitive4D
{
public:
	DoubleQuads4d(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "DoubleQuads4d";
		const unsigned int sizeOfTetra = sizeof(doublequads4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(doublequads4d::vertices4D,sizeof(doublequads4d::vertices4D) / sizeof(glm::vec4), doublequads4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~DoubleQuads4d() {
		
	}
};

class Box4d : public Primitive4D
{
public:
	Box4d(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Box4d";
		const unsigned int sizeOfTetra = sizeof(box4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(box4d::vertices4D,sizeof(box4d::vertices4D) / sizeof(glm::vec4), box4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Box4d() {
		
	}
};

class Waterbox4d : public Primitive4D
{
public:
	Waterbox4d(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Waterbox4d";
		const unsigned int sizeOfTetra = sizeof(waterbox4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(waterbox4d::vertices4D,sizeof(waterbox4d::vertices4D) / sizeof(glm::vec4), waterbox4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Waterbox4d() {
		
	}
};

class Pentachoron : public Primitive4D
{

public:
	Pentachoron(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Pentachoron";
		const unsigned int sizeOfTetra = sizeof(pentachoron::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(pentachoron::vertices4D,sizeof(pentachoron::vertices4D) / sizeof(glm::vec4), pentachoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra],scale4D);
	}
	~Pentachoron() {
		
	}
};

class Pyramid4D : public Primitive4D
{
public:
	Pyramid4D(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Pyramid4D";
		const unsigned int sizeOfTetra = sizeof(pyramid4d::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(pyramid4d::vertices4D, sizeof(pyramid4d::vertices4D) / sizeof(glm::vec4), pyramid4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Pyramid4D() {
		
	}
};

class Hexadecachoron : public Primitive4D
{
public:
	Hexadecachoron(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hexadecachoron";
		const unsigned int sizeOfTetra = sizeof(hexadecachoron::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hexadecachoron::vertices4D, sizeof(hexadecachoron::vertices4D) / sizeof(glm::vec4),hexadecachoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hexadecachoron() {
		
	}
};

class Hexacosichoron : public Primitive4D
{
public:
	Hexacosichoron(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hexacosichoron";
		const unsigned int sizeOfTetra = sizeof(hexacosichoron::indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hexacosichoron::vertices4D, sizeof(hexacosichoron::vertices4D) / sizeof(glm::vec4), hexacosichoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D);
	}
	~Hexacosichoron() {
		
	}
};

class Terrain4d : public Primitive4D
{
	float* terrainHeight2;
	glm::vec4* terrainNormal2;
	glm::ivec3* coordinate_XZW;
	glm::ivec3* cubeIndex_XZW;
	glm::vec4* points4D;
	glm::vec4* normals4D2;
	GLuint* indices4D0;
public:
	Terrain4d(glm::ivec4 pos, const int size): Primitive4D()
	{
		this->primitiveName = "Terrain4d";
		int half_size = int((float)size/ 2.f);
		this->terrainHeight2 = new float[(size+1)* (size + 1)* (size + 1)];
		this->terrainNormal2 = new glm::vec4[(size + 1) * (size + 1) * (size + 1)];
		for (int w = 0;w < size+1;w++) {
			for (int z = 0;z < size+1;z++) {
				for (int x = 0;x < size+1;x++) {
					this->terrainHeight2[x + (size + 1) * z + (size + 1) * (size + 1) * w] =
						terrain_height2(glm::vec4(x + pos.x - half_size, pos.y, z + pos.z - half_size, w + pos.w - half_size)) + 54.f;
					
					this->terrainNormal2[x + (size + 1) * z + (size + 1) * (size + 1) * w] =
						get_terrain_normal(glm::vec4(x + pos.x - half_size, pos.y, z + pos.z - half_size, w + pos.w - half_size));
				}
			}
		}

		this->coordinate_XZW = new glm::ivec3[24];
		this->points4D = new glm::vec4[4 * 6 * size * size * size];
		this->normals4D2 = new glm::vec4[4 * 6 * size * size * size];
		this->cubeIndex_XZW = new glm::ivec3[4 * 6 * size * size * size];
		for (size_t w = 0;w < size;w++) {
			for (size_t z = 0;z < size;z++) {
				for (size_t x = 0;x < size;x++) {					
					unsigned int cubeIndex = 4 * 6 * (size * size * w + size * z + x);
					    this->coordinate_XZW[0] = glm::ivec3(1, 0, 1), this->coordinate_XZW[3] = glm::ivec3(0, 0, 0),
						this->coordinate_XZW[2] = glm::ivec3(1, 0, 0), this->coordinate_XZW[1] = glm::ivec3(1, 1, 0),

						this->coordinate_XZW[4] = glm::ivec3(0, 0, 1), this->coordinate_XZW[7] = glm::ivec3(0, 0, 0),
						this->coordinate_XZW[6] = glm::ivec3(1, 0, 1), this->coordinate_XZW[5] = glm::ivec3(0, 1, 0),

						this->coordinate_XZW[8] = glm::ivec3(1, 0, 1), this->coordinate_XZW[11] = glm::ivec3(0, 1, 0),
						this->coordinate_XZW[10] = glm::ivec3(0, 0, 0), this->coordinate_XZW[9] = glm::ivec3(1, 1, 0),

						this->coordinate_XZW[12] = glm::ivec3(0, 1, 1), this->coordinate_XZW[15] = glm::ivec3(0, 1, 0),
						this->coordinate_XZW[14] = glm::ivec3(0, 0, 1), this->coordinate_XZW[13] = glm::ivec3(1, 1, 1),

						this->coordinate_XZW[16] = glm::ivec3(1, 1, 1), this->coordinate_XZW[19] = glm::ivec3(0, 1, 0),
						this->coordinate_XZW[18] = glm::ivec3(0, 0, 1), this->coordinate_XZW[17] = glm::ivec3(1, 0, 1),

						this->coordinate_XZW[20] = glm::ivec3(1, 0, 1), this->coordinate_XZW[23] = glm::ivec3(0, 1, 0),
						this->coordinate_XZW[22] = glm::ivec3(1, 1, 0), this->coordinate_XZW[21] = glm::ivec3(1, 1, 1);
					for (size_t i = 0;i < 24;i++) {
						int x0 = x + this->coordinate_XZW[i].x;
						int z0 = z + this->coordinate_XZW[i].y;
						int w0 = w + this->coordinate_XZW[i].z;
						this->cubeIndex_XZW[cubeIndex + i] = glm::ivec3(x - half_size + pos.x, z - half_size + pos.z, w - half_size + pos.w);
						this->points4D[cubeIndex + i] = glm::vec4(float(x0 - half_size), this->terrainHeight2[x0 + (size + 1) * z0 + (size + 1) * (size + 1) * w0], float(z0 - half_size), float(w0 - half_size));
						this->normals4D2[cubeIndex + i] = this->terrainNormal2[x0 + (size + 1) * z0 + (size + 1) * (size + 1) * w0];
					}
				}
			}
		}

		this->indices4D0 = new GLuint[4 * 6 * size * size * size];

		for (int i = 0;i < 4 * 6 * size * size * size;i++)
		{
			this->indices4D0[i] = i;
		}
		const unsigned int sizeOfTetra = 6 * size * size * size;
		this->transform_terrain4D(this->points4D, this->normals4D2, this->cubeIndex_XZW, this->indices4D0, pos, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra]);
	}
	~Terrain4d() {
		delete[] this->terrainHeight2; 
		this->terrainHeight2 = nullptr;
		delete[] this->terrainNormal2;
		this->terrainNormal2 = nullptr;

		delete[] this->coordinate_XZW;
		this->coordinate_XZW = nullptr;
		delete[] this->cubeIndex_XZW;
		this->cubeIndex_XZW = nullptr;
		delete[] this->points4D;
		this->points4D = nullptr;
		delete[] this->normals4D2;
		this->normals4D2 = nullptr;
		delete[] this->indices4D0;
		this->indices4D0 = nullptr;
		
	}
};

static unsigned primitive_index(const char* primitiveName)
{
	if (primitiveName == "Noneshape")
	{
		return 0;
	}
	else if (primitiveName == "TriPrism")
	{
		return 1;
	}
	else if (primitiveName == "Hyperslope")
	{
		return 2;
	}
	else if (primitiveName == "Hypersphere")
	{
		return 3;
	}
	else if (primitiveName == "Hyperspherecol")
	{
		return 4;
	}
	else if (primitiveName == "Hypercapsule")
	{
		return 5;
	}
	else if (primitiveName == "Hypercylinder")
	{
		return 6;
	}
	else if (primitiveName == "Hypercone")
	{
		return 7;
	}
	else if (primitiveName == "Hyperpot")
	{
		return 8;
	}
	else if (primitiveName == "Hypercube")
	{
		return 9;
	}
	else if (primitiveName == "Quad4d")
	{
		return 10;
	}
	else if (primitiveName == "Particle4d")
	{
		return 11;
	}
	else if (primitiveName == "DoubleQuads4d")
	{
		return 12;
	}
	else if (primitiveName == "Box4d")
	{
		return 13;
	}
	else if (primitiveName == "Waterbox4d")
	{
		return 14;
	}
	else if (primitiveName == "Pentachoron")
	{
		return 15;
	}
	else if (primitiveName == "Pyramid4D")
	{
		return 16;
	}
	else if (primitiveName == "Hexadecachoron")
	{
		return 17;
	}
	else if (primitiveName == "Hexacosichoron")
	{
		return 18;
	}
	else
	{
		return 0;
	}
}

static Primitive4D primitive_list(unsigned index, glm::vec4 scale4D)
{
	if (index == 0)
	{
		return Noneshape();
	}
	else if (index == 1)
	{
		return TriPrism(scale4D);
	}
	else if (index == 2)
	{
		return Hyperslope(scale4D);
	}
	else if (index == 3)
	{
		return Hypersphere(scale4D);
	}
	else if (index == 4)
	{
		return Hyperspherecol(scale4D);
	}
	else if (index == 5)
	{
		return Hypercapsule(scale4D);
	}
	else if (index == 6)
	{
		return Hypercylinder(scale4D);
	}
	else if (index == 7)
	{
		return Hypercone(scale4D);
	}
	else if (index == 8)
	{
		return Hyperpot(scale4D);
	}
	else if (index == 9)
	{
		return Hypercube(scale4D);
	}
	else if (index == 10)
	{
		return Quad4d(scale4D);
	}
	else if (index == 11)
	{
		return Particle4d();
	}
	else if (index == 12)
	{
		return DoubleQuads4d(scale4D);
	}
	else if (index == 13)
	{
		return Box4d(scale4D);
	}
	else if (index == 14)
	{
		return Waterbox4d(scale4D);
	}
	else if (index == 15)
	{
		return Pentachoron(scale4D);
	}
	else if (index == 16)
	{
		return Pyramid4D(scale4D);
	}
	else if (index == 17)
	{
		return Hexadecachoron(scale4D);
	}
	else if (index == 18)
	{
		return Hexacosichoron(scale4D);
	}
	else
	{
		return Noneshape();
	}
}