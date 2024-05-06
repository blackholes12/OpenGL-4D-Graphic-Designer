#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
#define PI glm::pi<float>()
namespace hyperCone {
	static void get_primitive(glm::vec4** points4D,unsigned* sizeOfPoints4D,glm::vec4** normals4D,GLuint** indices4D0, unsigned* sizeOfTetra)
	{
		const int length = 8;
		const int width = 16;
		*points4D = new glm::vec4[width * length * 3 + 1];
		*normals4D = new glm::vec4[width * length * 3 + 1];
		*indices4D0 = new GLuint[width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2];
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				glm::vec2 xz = glm::vec2(cos(2.f * PI * (float)(j) / (float)(width)), sin(2.f * PI * (float)(j) / (float)(width)));
				float rateShift = (float)length / (float)(length - 1);
				float w = sin(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				float xzRw = cos(PI * (((float)i * rateShift - (float)length / 2.f) / (float)length));
				*points4D[j + width * i] = glm::vec4(0.f, 0.f, 1.f, 0.f) * 0.5f;
				*points4D[width * length + j + width * i] = glm::vec4(xzRw * xz.x, xzRw * xz.y, -1.f, w) * 0.5f;
			}
		}
		for (int i = width * length * 2; i < width * length * 3; i++)
		{
			*points4D[i] = *points4D[i - width * length];
		}
		*points4D[width * length * 3] = glm::vec4(0, 0, -1.f, 0) * 0.5f;


		for (int i = 0; i < width * length; i++)
		{
			glm::vec4 normal4D = normalize(glm::vec4(points4D[i + width * length]->x, points4D[i + width * length]->y, 0.f,points4D[i + width * length]->w));
			*normals4D[i] = normalize(glm::vec4(normal4D.x, normal4D.y, 1.f / 2.f, normal4D.w));
		}
		for (int i = width * length; i < 2 * width * length; i++)
		{
			glm::vec4 normal4D = normalize(glm::vec4(points4D[i]->x, points4D[i]->y, 0.f, points4D[i]->w));
			*normals4D[i] = normalize(glm::vec4(normal4D.x, normal4D.y, 1.f / 2.f, normal4D.w));
		}
		for (int i = 2 * width * length; i < 3 * width * length; i++)
		{
			*normals4D[i] = glm::vec4(0, 0, -1.f, 0);
		}
		*normals4D[width * length * 3] = glm::vec4(0, 0, -1.f, 0);

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
						*indices4D0[24 * (j + width * i) + l + width * (length - 1) * 4 * 2] = coordinate[l];
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
					coordinate[0] = index[1] + width * length, coordinate[1] = index[0] + width * length, coordinate[2] = index[2] + width * length, coordinate[3] = width * length * 2 + 0,
						coordinate[4] = index[1] + width * length, coordinate[5] = index[2] + width * length, coordinate[6] = index[3] + width * length, coordinate[7] = width * length * 2 + 0;
					for (int l = 0; l < 8; l++)
					{
						*indices4D0[8 * (j + width * i) + l] = coordinate[l] + width * length;
					}
				}
			}
		}
		*sizeOfPoints4D = width * length * 3 + 1;
		*sizeOfTetra = (width * (length - 1) * 4 * 6 + width * (length - 1) * 4 * 2) / 4;
	}
}
