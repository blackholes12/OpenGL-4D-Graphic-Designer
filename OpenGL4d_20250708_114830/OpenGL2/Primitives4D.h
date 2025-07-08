#pragma once

#include<vector>
#include"Vertex.h"
#include"resourcefile/primitive4d/triPrism.h"
#include"resourcefile/primitive4d/hyperslope.h"
#include"resourcefile/primitive4d/hypercone.h"
#include"resourcefile/primitive4d/hypercube.h"
#include"resourcefile/primitive4d/hypercubecol.h"
#include"resourcefile/primitive4d/hypersphere.h"
#include"resourcefile/primitive4d/hyperspherecol.h"
#include"resourcefile/primitive4d/hypercylinder.h"
#include"resourcefile/primitive4d/hyperpot.h"
#include"resourcefile/primitive4d/quad4d.h"
#include"resourcefile/primitive4d/doublequads4d.h"
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
	std::string primitiveName;
	size_t id;
	glm::vec4 scale4D;
	Primitive4D() {}
	virtual ~Primitive4D() 
	{ 
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
		for (unsigned i(0); i < sizeOfVertices4D; i++)
		{this->vertices4D[i]=vertices4D[i];}
		for (unsigned i(0); i < sizeOfIndices4D; i++)
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
		bool isMesh(false);
		if (this->primitiveName == "Hypercube"|| this->primitiveName == "Hypercubecol")
		{
			sizeOfFrameVertices4D = sizeof(hypercube_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypercube_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercube_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypersphere_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercapsule_frame::frameVertice4D(scale4D, i);
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = particle4d_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (GLuint j(0); j < sizeOfpoints4D; j++)
			{
				frameVertices4d[j].pos4D = points4D[j];
			}
			for (GLuint j(0); j < sizeOfTetra; j++)
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
		for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
		{
			this->frameVertices4D[i]=frameVertices4d[i];
		}
		for (unsigned i(0); i < sizeOfFrameIndices4D/2; i++)
		{
			bool isOverlap(false);
			if (isMesh)
			{
				for (unsigned j(0); j < i; j++)
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
	void set2(glm::vec4* points4D, const unsigned int sizeOfpoints4D, glm::ivec2* indices4D0, const unsigned int sizeOfTetra, glm::vec4 scale4D)
	{
		FrameVertex4D* frameVertices4d;
		GLuint* frameIndices4d;
		unsigned sizeOfFrameVertices4D;
		unsigned sizeOfFrameIndices4D;
		bool isMesh(false);
		if (this->primitiveName == "Hypercube")
		{
			sizeOfFrameVertices4D = sizeof(hypercube_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypercube_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercube_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
			{
				frameIndices4d[i] = hypercube_frame::frameIndices4D0[i];
			}
		}
		else if (this->primitiveName == "Hypersphere" || this->primitiveName == "Hyperspherecol")
		{
			sizeOfFrameVertices4D = sizeof(hypersphere_frame::frameVertices4D) / sizeof(glm::vec4);
			sizeOfFrameIndices4D = sizeof(hypersphere_frame::frameIndices4D0) / sizeof(GLuint);
			frameVertices4d = new FrameVertex4D[sizeOfFrameVertices4D];
			frameIndices4d = new GLuint[sizeOfFrameIndices4D];
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypersphere_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = hypercapsule_frame::frameVertice4D(scale4D, i);
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
			{
				frameVertices4d[i].pos4D = particle4d_frame::frameVertices4D[i];
			}
			for (unsigned i(0); i < sizeOfFrameIndices4D; i++)
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
			for (GLuint j(0); j < sizeOfpoints4D; j++)
			{
				frameVertices4d[j].pos4D = points4D[j];
			}
			for (GLuint j(0); j < sizeOfTetra; j++)
			{
				frameIndices4d[12 * j + 0] = indices4D0[4 * j][0];
				frameIndices4d[12 * j + 1] = indices4D0[4 * j + 1][0];
				frameIndices4d[12 * j + 2] = indices4D0[4 * j][0];
				frameIndices4d[12 * j + 3] = indices4D0[4 * j + 2][0];
				frameIndices4d[12 * j + 4] = indices4D0[4 * j][0];
				frameIndices4d[12 * j + 5] = indices4D0[4 * j + 3][0];
				frameIndices4d[12 * j + 6] = indices4D0[4 * j + 1][0];
				frameIndices4d[12 * j + 7] = indices4D0[4 * j + 2][0];
				frameIndices4d[12 * j + 8] = indices4D0[4 * j + 1][0];
				frameIndices4d[12 * j + 9] = indices4D0[4 * j + 3][0];
				frameIndices4d[12 * j + 10] = indices4D0[4 * j + 2][0];
				frameIndices4d[12 * j + 11] = indices4D0[4 * j + 3][0];
			}
			isMesh = true;
		}
		this->frameVertices4D = new FrameVertex4D[sizeOfFrameVertices4D];
		this->sizeOfFrameVertices4D = sizeOfFrameVertices4D;
		this->frameIndices4D = new GLuint[sizeOfFrameIndices4D];
		this->sizeOfFrameIndices4D = 0;
		for (unsigned i(0); i < sizeOfFrameVertices4D; i++)
		{
			this->frameVertices4D[i] = frameVertices4d[i];
		}
		for (unsigned i(0); i < sizeOfFrameIndices4D / 2; i++)
		{
			bool isOverlap(false);
			if (isMesh)
			{
				for (unsigned j(0); j < i; j++)
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
				this->frameIndices4D[this->sizeOfFrameIndices4D] = frameIndices4d[2 * i];
				this->frameIndices4D[this->sizeOfFrameIndices4D + 1] = frameIndices4d[2 * i + 1];
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
		for (unsigned i(0); i < size; i++) {
			this->vertexData4D[i] = points4D[indices4D0[i]];
		}
	}

	void set_vertex_data(glm::vec4* points4D, glm::ivec2* indices4D0, unsigned int size)
	{
		this->vertexData4D = new glm::vec4[size];
		for (unsigned i(0); i < size; i++) {
			this->vertexData4D[i] = points4D[indices4D0[i][0]];
		}
	}

	void set_normal_data(glm::vec4* points4D, unsigned int* indices4D0, unsigned int size)
	{
		this->normalData4D = new glm::vec4[size];
		for (unsigned i(0); i < size/4; i++) {
			glm::vec4 normal4D= alg::normalize(cross4d(points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 1]], points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 2]], points4D[indices4D0[4 * i]] - points4D[indices4D0[4 * i + 3]]));
			for(int j(0);j<4;j++)
			this->normalData4D[4*i+j] = normal4D;
		}
	}

	void set_normal_data(glm::vec4* points4D, glm::ivec2* indices4D0, unsigned int size)
	{
		this->normalData4D = new glm::vec4[size];
		for (unsigned i(0); i < size / 4; i++) {
			glm::vec4 normal4D(alg::normalize(cross4d(points4D[indices4D0[4 * i][0]] - points4D[indices4D0[4 * i + 1][0]], points4D[indices4D0[4 * i][0]] - points4D[indices4D0[4 * i + 2][0]], points4D[indices4D0[4 * i][0]] - points4D[indices4D0[4 * i + 3][0]])));
			for (int j(0); j < 4; j++)
				this->normalData4D[4 * i + j] = normal4D;
		}
	}

	void transform_vertex4D(glm::vec4* points4D, const unsigned int sizeOfpoints4D, glm::vec4* normal4d, glm::ivec2* indices4D0, const unsigned int sizeOfTetra, Vertex4D* vertices4d, GLuint* indices4d, glm::vec4 scale4D,glm::vec3 offset,unsigned int texType) {
		this->set_vertex_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->set_normal_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->scale4D = scale4D;
		for (unsigned j(0); j < sizeOfTetra; j++) {
			glm::vec4 point_A(points4D[indices4D0[4 * j][0]]);
			glm::vec4 point_B(points4D[indices4D0[4 * j + 1][0]]);
			glm::vec4 point_C(points4D[indices4D0[4 * j + 2][0]]);
			glm::vec4 point_D(points4D[indices4D0[4 * j + 3][0]]);
			glm::vec3 texcoord_A,texcoord_B,texcoord_C,texcoord_D;
			glm::vec4 normal_A(normal4d[indices4D0[4 * j][1]]);
			glm::vec4 normal_B(normal4d[indices4D0[4 * j + 1][1]]);
			glm::vec4 normal_C(normal4d[indices4D0[4 * j + 2][1]]);
			glm::vec4 normal_D(normal4d[indices4D0[4 * j + 3][1]]);
			glm::vec4 normalAverage((normal_A + normal_B + normal_C + normal_D)/4.f);
			if (texType == 0)
			{
				texcoord_A = texcoord_position(normalAverage, point_A * scale4D,offset);
				texcoord_B = texcoord_position(normalAverage, point_B * scale4D,offset);
				texcoord_C = texcoord_position(normalAverage, point_C * scale4D,offset);
				texcoord_D = texcoord_position(normalAverage, point_D * scale4D,offset);
			}
			else if (texType == 1)
			{
				texcoord_A = texcoord_position2(normalAverage, point_A * scale4D,offset);
				texcoord_B = texcoord_position2(normalAverage, point_B * scale4D,offset);
				texcoord_C = texcoord_position2(normalAverage, point_C * scale4D,offset);
				texcoord_D = texcoord_position2(normalAverage, point_D * scale4D,offset);
			}
			for (GLuint i(0); i < 4; i++) {

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

	void transform_terrain4D(glm::vec4* points4D, glm::vec4* normal4d, unsigned int* indices4D0, glm::vec4 offset4d, const unsigned int sizeOfTetra, Vertex4D* vertices4d, GLuint* indices4d, glm::vec3 offset) {
		this->set_vertex_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->set_normal_data(points4D, indices4D0, 4 * sizeOfTetra);
		this->scale4D = glm::vec4(1.f);
		for (unsigned j(0);j < sizeOfTetra;j++) {
			glm::vec4 point_A(points4D[indices4D0[4 * j]]);
			glm::vec4 point_B(points4D[indices4D0[4 * j + 1]]);
			glm::vec4 point_C(points4D[indices4D0[4 * j + 2]]);
			glm::vec4 point_D(points4D[indices4D0[4 * j + 3]]);
			glm::vec3 texcoord_A(texcoord_position2(point_A + offset4d,offset));
			glm::vec3 texcoord_B(texcoord_position2(point_B + offset4d,offset));
			glm::vec3 texcoord_C(texcoord_position2(point_C + offset4d,offset));
			glm::vec3 texcoord_D(texcoord_position2(point_D + offset4d,offset));
			glm::vec4 normal_A(normal4d[indices4D0[4 * j]]);
			glm::vec4 normal_B(normal4d[indices4D0[4 * j+1]]);
			glm::vec4 normal_C(normal4d[indices4D0[4 * j+2]]);
			glm::vec4 normal_D(normal4d[indices4D0[4 * j+3]]);
			for (GLuint i(0);i < 4;i++) {

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
		this->set2(new glm::vec4[0], 0, new unsigned[0], 0, glm::vec4(1.f));
	}
};

class Noneshape : public Primitive4D
{
public:
	Noneshape(): Primitive4D()
	{
		this->primitiveName = "Noneshape";
		this->transform_vertex4D(nullptr, 0, nullptr, nullptr, 0, nullptr, nullptr, glm::vec4(1.f),glm::vec3(), 0);
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
		this->id = 6;
		const unsigned int sizeOfTetra = sizeof(triPrism::indices4D0) / sizeof(glm::ivec2) / 4;
		this->transform_vertex4D(triPrism::vertices4D, sizeof(triPrism::vertices4D) / sizeof(glm::vec4), triPrism::normals4D, triPrism::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f),0);
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
		this->id = 7;
		const unsigned int sizeOfTetra = sizeof(hyperslope::indices4D0) / sizeof(glm::ivec2) / 4;
		this->transform_vertex4D(hyperslope::vertices4D, sizeof(hyperslope::vertices4D) / sizeof(glm::vec4), hyperslope::normals4D,hyperslope::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
	}
	~Hyperslope() {
		
	}
};

class Hypersphere : public Primitive4D
{
public:
	Hypersphere(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypersphere";
		this->id = 1;
		const unsigned int sizeOfTetra = sizeof(hypersphere::indices4D0) / sizeof(glm::ivec2) / 4;//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hypersphere::vertices4D, sizeof(hypersphere::vertices4D) / sizeof(glm::vec4), hypersphere::normals4D, hypersphere::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hypersphere() {	
	}
};

class Hyperspherecol : public Primitive4D
{
public:
	Hyperspherecol(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hyperspherecol";
		const unsigned int sizeOfTetra = sizeof(hyperspherecol::indices4D0) / sizeof(glm::ivec2) / 4;//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hyperspherecol::vertices4D, sizeof(hyperspherecol::vertices4D) / sizeof(glm::vec4), hyperspherecol::normals4D, hyperspherecol::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hyperspherecol() {
	}
};

class Hypercapsule : public Primitive4D
{
	glm::vec4* points4D;
	glm::vec4* normals4D;
public:
	Hypercapsule(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercapsule";
		this->id = 2;
		const unsigned int sizeOfTetra(sizeof(hypersphere::indices4D0) / sizeof(glm::ivec2) / 4);
		const unsigned int sizeOfPoints(sizeof(hypersphere::vertices4D) / sizeof(glm::vec4));
		float radius(glm::min(scale4D.w, glm::min(scale4D.x, scale4D.y)) / 2.f);
		float capsuleLength(scale4D.z);
		this->points4D = new glm::vec4[sizeOfPoints];
		this->normals4D = new glm::vec4[sizeOfPoints];
		for (int i(0); i < sizeOfPoints; i++){
			glm::vec4 point4D(hypersphere::vertices4D[i]);
			float height(2.f*point4D.w);
			if (height > 0.f){height = glm::mix(1.f - 2.f * radius / capsuleLength, 1.f, height);}
			if (height < 0.f){height = -glm::mix(1.f - 2.f * radius / capsuleLength, 1.f, -height);}
			this->points4D[i] = glm::vec4(point4D.x, point4D.y, height/2.f, -point4D.z);
			this->normals4D[i] = alg::normalize(glm::vec4(point4D.x, point4D.y, point4D.w / (2.f * radius / capsuleLength), -point4D.z));
		}
		this->transform_vertex4D(this->points4D, sizeOfPoints, this->normals4D, hypersphere::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hypercapsule() {
		this->points4D=nullptr,delete[] this->points4D;
		this->normals4D=nullptr,delete[] this->normals4D;
	}
};

class Hypercylinder : public Primitive4D
{
public:
	Hypercylinder(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercylinder";
		this->id = 3;
		const unsigned int sizeOfTetra(sizeof(hypercylinder::indices4D0) / sizeof(glm::ivec2) / 4);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hypercylinder::vertices4D, sizeof(hypercylinder::vertices4D) / sizeof(glm::vec4), hypercylinder::normals4D, hypercylinder::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hypercylinder() {
	}
};

class Hypercone : public Primitive4D
{
public:
	Hypercone(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercone";
		this->id = 4;
		const unsigned int sizeOfTetra(sizeof(hypercone::indices4D0) / sizeof(glm::ivec2) / 4);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hypercone::vertices4D, sizeof(hypercone::vertices4D) / sizeof(glm::vec4), hypercone::normals4D, hypercone::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hypercone() {
	}
};

class Hyperpot : public Primitive4D
{

public:
	Hyperpot(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hyperpot";
		this->id = 5;
		const unsigned int sizeOfTetra(sizeof(hyperpot::indices4D0) / sizeof(glm::ivec2) / 4);//sizeof(this->indices4D0) / sizeof(GLuint) / 4;
		this->transform_vertex4D(hyperpot::vertices4D, sizeof(hyperpot::vertices4D) / sizeof(glm::vec4), hyperpot::normals4D, hyperpot::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hyperpot() {
	}
};


class Hypercube : public Primitive4D
{
public:
	Hypercube(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercube";
		this->id = 1;
		const unsigned int sizeOfTetra(sizeof(hypercube::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(hypercube::vertices4D, sizeof(hypercube::vertices4D) / sizeof(glm::vec4), hypercube::normals4D,hypercube::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
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
		const unsigned int sizeOfTetra(sizeof(quad4d::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(quad4d::vertices4D, sizeof(quad4d::vertices4D) / sizeof(glm::vec4), quad4d::normals4D, quad4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
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
		const unsigned int sizeOfTetra(sizeof(quad4d::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(quad4d::vertices4D, sizeof(quad4d::vertices4D) / sizeof(glm::vec4), quad4d::normals4D, quad4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], glm::vec4(1.f), glm::vec3(0.5f), 0);
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
		this->id = 8;
		const unsigned int sizeOfTetra(sizeof(doublequads4d::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(doublequads4d::vertices4D,sizeof(doublequads4d::vertices4D) / sizeof(glm::vec4), doublequads4d::normals4D,doublequads4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
	}
	~DoubleQuads4d() {
		
	}
};

class Hypercubecol : public Primitive4D
{
public:
	Hypercubecol(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Hypercubecol";
		const unsigned int sizeOfTetra(sizeof(hypercubecol::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(hypercubecol::vertices4D,sizeof(hypercubecol::vertices4D) / sizeof(glm::vec4), hypercubecol::normals4D, hypercubecol::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
	}
	~Hypercubecol() {
		
	}
};

class Waterbox4d : public Primitive4D
{
public:
	Waterbox4d(glm::vec4 scale4D): Primitive4D()
	{
		this->primitiveName = "Waterbox4d";
		const unsigned int sizeOfTetra(sizeof(waterbox4d::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(waterbox4d::vertices4D,sizeof(waterbox4d::vertices4D) / sizeof(glm::vec4), waterbox4d::normals4D ,waterbox4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
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
		this->id = 9;
		const unsigned int sizeOfTetra(sizeof(pentachoron::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(pentachoron::vertices4D,sizeof(pentachoron::vertices4D) / sizeof(glm::vec4), pentachoron::normals4D,pentachoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra],scale4D, glm::vec3(0.25f), 0);
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
		this->id = 10;
		const unsigned int sizeOfTetra(sizeof(pyramid4d::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(pyramid4d::vertices4D, sizeof(pyramid4d::vertices4D) / sizeof(glm::vec4), pyramid4d::normals4D, pyramid4d::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
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
		this->id = 11;
		const unsigned int sizeOfTetra(sizeof(hexadecachoron::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(hexadecachoron::vertices4D, sizeof(hexadecachoron::vertices4D) / sizeof(glm::vec4), hexadecachoron::normals4D,hexadecachoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 0);
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
		this->id = 12;
		const unsigned int sizeOfTetra(sizeof(hexacosichoron::indices4D0) / sizeof(glm::ivec2) / 4);
		this->transform_vertex4D(hexacosichoron::vertices4D, sizeof(hexacosichoron::vertices4D) / sizeof(glm::vec4), hexacosichoron::normals4D,hexacosichoron::indices4D0, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], scale4D, glm::vec3(0.25f), 1);
	}
	~Hexacosichoron() {
		
	}
};

static const int terrainSize = 4;
static const int terrainScale = 4;

class Terrain4d : public Primitive4D
{
	float* terrainHeight2;
	glm::vec4* terrainNormal2;
	glm::ivec3* coordinate_XZW;
	glm::vec4* points4D;
	glm::vec4* normals4D2;
	GLuint* indices4D0;
public:
	Terrain4d(glm::ivec4 pos): Primitive4D()
	{
		this->primitiveName = "Terrain4d";
		int halfTerrainSize(terrainSize / 2);
		this->terrainHeight2 = new float[(terrainSize+1)* (terrainSize + 1)* (terrainSize + 1)];
		this->terrainNormal2 = new glm::vec4[(terrainSize + 1) * (terrainSize + 1) * (terrainSize + 1)];
		for (int w(0);w < terrainSize+1;w++) {
			for (int z(0);z < terrainSize+1;z++) {
				for (int x(0);x < terrainSize+1;x++) {
					this->terrainHeight2[x + (terrainSize + 1) * z + (terrainSize + 1) * (terrainSize + 1) * w] =
						terrain_height(glm::vec4(terrainScale * (x - halfTerrainSize) + pos.x, pos.y, terrainScale * (z - halfTerrainSize) + pos.z, terrainScale * (w - halfTerrainSize) + pos.w));
					
					this->terrainNormal2[x + (terrainSize + 1) * z + (terrainSize + 1) * (terrainSize + 1) * w] =
						get_terrain_normal(glm::vec4(terrainScale * (x - halfTerrainSize) + pos.x, pos.y, terrainScale * (z - halfTerrainSize) + pos.z, terrainScale * (w - halfTerrainSize) + pos.w));
				}
			}
		}

		this->coordinate_XZW = new glm::ivec3[24];
		this->points4D = new glm::vec4[4 * 6 * terrainSize * terrainSize * terrainSize];
		this->normals4D2 = new glm::vec4[4 * 6 * terrainSize * terrainSize * terrainSize];
		for (size_t w(0);w < terrainSize;w++) {
			for (size_t z(0);z < terrainSize;z++) {
				for (size_t x(0);x < terrainSize;x++) {					
					size_t cubeIndex(4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x));
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
					for (size_t i(0);i < 24;i++) {
						int x0(x + this->coordinate_XZW[i].x);
						int z0(z + this->coordinate_XZW[i].y);
						int w0(w + this->coordinate_XZW[i].z);
						this->points4D[cubeIndex + i] = glm::vec4(terrainScale * float(x0 - halfTerrainSize), this->terrainHeight2[x0 + (terrainSize + 1) * z0 + (terrainSize + 1) * (terrainSize + 1) * w0], terrainScale * float(z0 - halfTerrainSize), terrainScale * float(w0 - halfTerrainSize));
						this->normals4D2[cubeIndex + i] = this->terrainNormal2[x0 + (terrainSize + 1) * z0 + (terrainSize + 1) * (terrainSize + 1) * w0];
					}
				}
			}
		}

		this->indices4D0 = new GLuint[4 * 6 * terrainSize * terrainSize * terrainSize];

		for (int i(0);i < 4 * 6 * terrainSize * terrainSize * terrainSize;i++)
		{
			this->indices4D0[i] = i;
		}
		const unsigned int sizeOfTetra(6 * terrainSize * terrainSize * terrainSize);
		this->transform_terrain4D(this->points4D, this->normals4D2, this->indices4D0, pos, sizeOfTetra, new Vertex4D[4 * sizeOfTetra], new GLuint[6 * sizeOfTetra], glm::vec3(0.25f));
	}
	~Terrain4d() {
		delete[] this->terrainHeight2;
		delete[] this->terrainNormal2;
		delete[] this->coordinate_XZW;
		delete[] this->points4D;
		delete[] this->normals4D2;
		delete[] this->indices4D0;
		
	}
};

static unsigned primitive_index(std::string primitiveName)
{
	if (primitiveName == "Noneshape"){return 0;}
	else if (primitiveName == "TriPrism"){return 1;}
	else if (primitiveName == "Hyperslope"){return 2;}
	else if (primitiveName == "Hypersphere"){return 3;}
	else if (primitiveName == "Hyperspherecol"){return 4;}
	else if (primitiveName == "Hypercapsule"){return 5;}
	else if (primitiveName == "Hypercylinder"){return 6;}
	else if (primitiveName == "Hypercone"){return 7;}
	else if (primitiveName == "Hyperpot"){return 8;}
	else if (primitiveName == "Hypercube"){return 9;}
	else if (primitiveName == "Quad4d"){return 10;}
	else if (primitiveName == "Particle4d"){return 11;}
	else if (primitiveName == "DoubleQuads4d"){return 12;}
	else if (primitiveName == "Box4d"){return 13;}
	else if (primitiveName == "Waterbox4d"){return 14;}
	else if (primitiveName == "Pentachoron"){return 15;}
	else if (primitiveName == "Pyramid4D"){return 16;}
	else if (primitiveName == "Hexadecachoron"){return 17;}
	else if (primitiveName == "Hexacosichoron"){return 18;}
	else{return 0;}
}

static Primitive4D primitive_list(unsigned index, glm::vec4 scale4D)
{
	switch (index)
	{
	case 0: { return Noneshape(); }
	case 1: { return TriPrism(scale4D); }
	case 2: { return Hyperslope(scale4D); }
	case 3: { return Hypersphere(scale4D); }
	case 4: { return Hyperspherecol(scale4D); }
	case 5: { return Hypercapsule(scale4D); }
	case 6: { return Hypercylinder(scale4D); }
	case 7: { return Hypercone(scale4D); }
	case 8: { return Hyperpot(scale4D); }
	case 9: { return Hypercube(scale4D); }
	case 10: { return Quad4d(scale4D); }
	case 11: { return Particle4d(); }
	case 12: { return DoubleQuads4d(scale4D); }
	case 13: { return Hypercubecol(scale4D); }
	case 14: { return Waterbox4d(scale4D); }
	case 15: { return Pentachoron(scale4D); }
	case 16: { return Pyramid4D(scale4D); }
	case 17: { return Hexadecachoron(scale4D); }
	case 18: { return Hexacosichoron(scale4D); }
	default: { return Noneshape(); }
	}
}

static glm::vec4 get_vertex(int primitiveId, int index)
{
	switch (primitiveId)
	{
	case 3: { return hypercylinder::vertices4D[hypercylinder::indices4D0[index].x]; }
	case 4: { return hypercone::vertices4D[hypercone::indices4D0[index].x]; }
	case 5: { return hyperpot::vertices4D[hyperpot::indices4D0[index].x]; }
	case 6: { return triPrism::vertices4D[triPrism::indices4D0[index].x]; }
	case 7: { return hyperslope::vertices4D[hyperslope::indices4D0[index].x]; }
	case 8: { return doublequads4d::vertices4D[doublequads4d::indices4D0[index].x]; }
	case 9: { return pentachoron::vertices4D[pentachoron::indices4D0[index].x]; }
	case 10: { return pyramid4d::vertices4D[pyramid4d::indices4D0[index].x]; }
	case 11: { return hexadecachoron::vertices4D[hexadecachoron::indices4D0[index].x]; }
	case 12: { return hexacosichoron::vertices4D[hexacosichoron::indices4D0[index].x]; }
	}
}

static int get_vertices_size(int primitiveId)
{
	switch (primitiveId)
	{
		case 3: {return 3840; }
		case 4: {return 1536; }
		case 5: { return 8448; }
		case 6: {return 56;	}
		case 7: {return 108; }
		case 8: {return 40;	}
		case 9: {return 20; }
		case 10: {return 68; }
		case 11: {return 64; }
		case 12: {return 2400; }
	}
}
