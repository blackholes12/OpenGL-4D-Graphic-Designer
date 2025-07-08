#pragma once
#include<GLFW/glfw3.h>
#include<vec4.hpp>
#include"Simplex3d.h"
namespace terrain {
	const int size = 7;
	float half_size = (float)(size) / 2;
	static const unsigned nofPoint =(size + 1) * (size + 1) * (size + 1);
	static const unsigned nofIndices = 4 * 6 * size * size * size;
	static glm::vec4* point4D(glm::vec4 pos, glm::vec4* point4D0) {
		glm::vec4* point4D00 = point4D0;
		for (int w = 0;w < size + 1;w++) {
			for (int z = 0;z < size + 1;z++) {
				for (int x = 0;x < size + 1;x++) {

					point4D00[(size + 1) * (size + 1) * w + (size + 1) * z + x] =
						glm::vec4(x - half_size, 7.5f * simplex3d_fractal(glm::vec3(0.005f) * glm::vec3(x + size * pos.x - half_size,
							z + size * pos.z - half_size, w + size * pos.w - half_size)),
							z - half_size, w - half_size);

				}
			}
		}
		return point4D00;
	}
	static GLuint* indices4D0(GLuint* indices4D00)
	{
		GLuint* indices4D000= indices4D00;
		for (GLuint w = 0;w < size;w++) {
			for (GLuint z = 0;z < size;z++) {
				for (GLuint x = 0;x < size;x++) {
					unsigned int cubeIndex = 4 * 6 * (size * size * w + size * z + x);

					indices4D000[cubeIndex] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x + 1);
					indices4D000[cubeIndex + 3] = (size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D000[cubeIndex + 2] = (size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x + 1);
					indices4D000[cubeIndex + 1] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x + 1);

					indices4D000[cubeIndex + 4] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x);
					indices4D000[cubeIndex + 7] = (size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D000[cubeIndex + 6] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x + 1);
					indices4D000[cubeIndex + 5] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);

					indices4D000[cubeIndex + 8] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x + 1);
					indices4D000[cubeIndex + 11] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);
					indices4D000[cubeIndex + 10] = (size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D000[cubeIndex + 9] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x + 1);

					indices4D000[cubeIndex + 12] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z + 1) + (x);
					indices4D000[cubeIndex + 15] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);
					indices4D000[cubeIndex + 14] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x);
					indices4D000[cubeIndex + 13] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z + 1) + (x + 1);

					indices4D000[cubeIndex + 16] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z + 1) + (x + 1);
					indices4D000[cubeIndex + 19] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);
					indices4D000[cubeIndex + 18] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x);
					indices4D000[cubeIndex + 17] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x + 1);

					indices4D000[cubeIndex + 20] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z)+(x + 1);
					indices4D000[cubeIndex + 23] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);
					indices4D000[cubeIndex + 22] = (size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x + 1);
					indices4D000[cubeIndex + 21] = (size + 1) * (size + 1) * (w + 1) + (size + 1) * (z + 1) + (x + 1);
				}
			}
		}
		return indices4D000;
	}
}
/*
class Plane4D : public Primitive4D
{
public:
	Plane4D(glm::vec4 pos)
		: Primitive4D()
	{
		glm::vec4 point4D[terrain::nofPoint];
		terrain::point4D(pos,point4D);
		GLuint indices4D0[terrain::nofIndices];
		terrain::indices4D0(indices4D0);
		const unsigned int telax_size = sizeof(indices4D0) / sizeof(GLuint) / 4;
		Vertex4D vertices4D[4 * telax_size];GLuint indices4D[6 * telax_size];
		this->transform_vertex4D(telax_size, vertices4D, indices4D, point4D, indices4D0);

		this->vertexData4D = new glm::vec4[4 * telax_size];
		for (size_t i = 0;i < 4 * telax_size;i++) {
			this->vertexData4D[i]=point4D[indices4D0[i]];
		}
	}
};
*/
/*
class Plane4D : public Primitive4D
{
public:
	Plane4D(glm::vec4 pos)
		: Primitive4D()
	{
		const int size = 7;
		float half_size = (float)(size) / 2;
		glm::vec4 point4D[(size+1)* (size + 1)* (size + 1)];
		for (int w = 0;w < size + 1;w++) {
			for (int z = 0;z < size + 1;z++) {
				for (int x = 0;x < size + 1;x++) {

					point4D[(size + 1) * (size + 1) * w + (size + 1) * z + x] =
						glm::vec4(x - half_size, 7.5f*simplex3d_fractal(glm::vec3(0.005f)*glm::vec3(x + size * pos.x - half_size,
							z + size * pos.z - half_size, w + size * pos.w - half_size)),
							z - half_size,w - half_size);

				}
			}
		}
		GLuint indices4D0[4*6* size* size* size];
		for (GLuint w = 0;w < size;w++) {
			for (GLuint z = 0;z < size;z++) {
				for (GLuint x = 0;x < size;x++) {
					unsigned int cubeIndex = 4 * 6 * (size * size * w + size * z + x);

					indices4D0[cubeIndex]=(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x + 1);
					indices4D0[cubeIndex +3] =(size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +2] =(size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x+1);
					indices4D0[cubeIndex +1] =(size + 1) * (size + 1) * (w)+(size + 1) * (z+1)+(x + 1);

					indices4D0[cubeIndex +4] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +7] =(size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +6] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x + 1);
					indices4D0[cubeIndex +5] =(size + 1) * (size + 1) * (w)+(size + 1) * (z+1)+(x);

					indices4D0[cubeIndex +8] =(size + 1) * (size + 1) * (w + 1) + (size + 1) * (z) + (x+1);
					indices4D0[cubeIndex +11] =(size + 1) * (size + 1) * (w)+(size + 1) * (z+1)+(x);
					indices4D0[cubeIndex +10] =(size + 1) * (size + 1) * (w)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +9] =(size + 1) * (size + 1) * (w)+(size + 1) * (z+1)+(x+1);

					indices4D0[cubeIndex +12] =(size + 1) * (size + 1) * (w+1) + (size + 1) * (z + 1) + (x);
					indices4D0[cubeIndex +15] =(size + 1) * (size + 1) * (w)+(size + 1) * (z+1)+(x);
					indices4D0[cubeIndex +14] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +13] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z+1)+(x+1);

					indices4D0[cubeIndex +16] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z+1)+(x + 1);
					indices4D0[cubeIndex +19] =(size + 1) * (size + 1) * (w) + (size + 1) * (z + 1) + (x);
					indices4D0[cubeIndex +18] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x);
					indices4D0[cubeIndex +17] =(size + 1) * (size + 1) * (w+1)+(size + 1) * (z)+(x + 1);

					indices4D0[cubeIndex + 20] =(size + 1) * (size + 1) * (w + 1) + (size + 1) * (z) + (x + 1);
					indices4D0[cubeIndex + 23] =(size + 1) * (size + 1) * (w)+(size + 1) * (z + 1) + (x);
					indices4D0[cubeIndex + 22] =(size + 1) * (size + 1) * (w) + (size + 1) * (z+1)+(x+1);
					indices4D0[cubeIndex + 21] =(size + 1) * (size + 1) * (w + 1) + (size + 1) * (z+1)+(x + 1);
				}
			}
		}
		const unsigned int telax_size = sizeof(indices4D0) / sizeof(GLuint) / 4;
		Vertex4D vertices4D[4 * telax_size];GLuint indices4D[6 * telax_size];
		this->transform_vertex4D(telax_size, vertices4D, indices4D, point4D, indices4D0);

		this->vertexData4D = new glm::vec4[4 * telax_size];
		for (size_t i = 0;i < 4 * telax_size;i++) {
			this->vertexData4D[i]=point4D[indices4D0[i]];
		}
	}
};
*/