#pragma once

//#include<iostream>
//#include<string>

//#include<GLFW/glfw3.h>

//#include<SOIL2.h>

class Texture
{
private:
	GLuint id;
	unsigned int target;
	unsigned char* pixelData;
public:
	int width;
	int height;
	Texture(const char* fileName)
	{
		this->target = GL_TEXTURE_2D;

		this->pixelData = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->target, this->id);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (this->pixelData)
		{
			glTexImage2D(this->target, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixelData);
			glGenerateMipmap(this->target);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->target, 0);
		SOIL_free_image_data(this->pixelData);
	}
	
	~Texture()
	{
		glDeleteTextures(1, &this->id);
		delete this->pixelData;
		this->pixelData = nullptr;
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->target, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}

	void set_filter(unsigned char filterType)
	{
		glBindTexture(this->target, this->id);
		if (filterType == 0)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else
			if (filterType == 1)
			{
				glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			}
			else
				if (filterType == 2)
				{
					glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				else
					if (filterType == 3)
					{
						glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					}
	}

	void loadFromFile(const char* fileName)
	{
		if (this->id)
		{
			glDeleteTextures(1, &this->id);
		}

		this->pixelData = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->target, this->id);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		if (this->pixelData)
		{
			glTexImage2D(this->target, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixelData);
			glGenerateMipmap(this->target);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->target, 0);
		SOIL_free_image_data(this->pixelData);
	}
};

class HDRTexture
{
public:
	GLuint id;
	unsigned int target;
	unsigned int rboDepth;
	unsigned int hdrFBO;
	HDRTexture(unsigned width, unsigned height)
	{
		this->target = GL_TEXTURE_2D;
		glGenTextures(1, &this->id);
		glBindTexture(this->target, this->id);
		glTexImage2D(this->target, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glActiveTexture(0);
		glBindTexture(this->target, 0);
		//Depth Buffer
		glGenRenderbuffers(1, &this->rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, this->rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		
		//FrameBuffer
		glGenFramebuffers(1, &this->hdrFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->target, this->id, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rboDepth);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)std::cout << "Frame cache not fully initialized!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void set_texture_size(unsigned width, unsigned height)
	{
		glBindTexture(this->target, this->id);
		glTexImage2D(this->target, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glBindRenderbuffer(GL_RENDERBUFFER, this->rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	}
	void set_filter(unsigned char filterType)
	{
		glBindTexture(this->target, this->id);
		if (filterType == 0)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else if (filterType == 1)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	}
	void update_mipmap()
	{
		glBindTexture(this->target, this->id);
		glGenerateMipmap(this->target);
	}

	float pixelData[27];
	glm::vec3 get_avg_color()
	{
		glBindTexture(this->target, this->id);
		//glReadPixels(0, 0, 3, 3, GL_RGB, GL_FLOAT, &pixelData);
		glGetTexImage(this->target, 0, GL_RGB, GL_FLOAT, pixelData);
		glm::vec3 color(glm::vec3(
			(pixelData[0] + pixelData[3] + pixelData[6] + pixelData[9] + pixelData[12] + pixelData[15] + pixelData[18] + pixelData[21] + pixelData[24]) / 9.f,
			(pixelData[1] + pixelData[4] + pixelData[7] + pixelData[10] + pixelData[13] + pixelData[16] + pixelData[19] + pixelData[22] + pixelData[25]) / 9.f,
			(pixelData[2] + pixelData[5] + pixelData[8] + pixelData[11] + pixelData[14] + pixelData[17] + pixelData[20] + pixelData[23] + pixelData[26]) / 9.f
		));
		//std::cout << "brightness=" << dot(color, glm::vec3(0.333f)) << "\n";
		return color;
	}

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->target, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}
	void bind_frame_buffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	}
	void unbind_frame_buffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	~HDRTexture()
	{
		glDeleteTextures(1, &this->id);
		glDeleteRenderbuffers(1, &this->rboDepth);
		glDeleteFramebuffers(1, &this->hdrFBO);
	}
};

class Texture3D
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int target;
	unsigned char* pixelData;
	unsigned int pType = -1;
	float pScale = -1;
	GLubyte checkImage3D[128][128][128][4];
public:
	Texture3D(const char* fileName)
	{
		this->target = GL_TEXTURE_3D;

		this->pixelData = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
		//if (fileName == "resourcefile/images/sky_panorama/3dstars_field.png")
		//{
		//	this->save_image();
		//}
		glGenTextures(1, &this->id);
		glBindTexture(this->target, this->id);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (this->pixelData)
		{
			if (this->height == this->width * this->width) {
				glTexImage3D(this->target, 0, GL_RGBA, this->width, this->width, this->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixelData);
			}
			if (this->height == this->width * this->width / 4) {
				glTexImage3D(this->target, 0, GL_RGBA, this->width, this->width / 2, this->width / 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixelData);
			}
			glGenerateMipmap(this->target);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->target, 0);
		SOIL_free_image_data(this->pixelData);
	}

	~Texture3D()
	{
		glDeleteTextures(1, &this->id);
		this->pixelData = nullptr,delete this->pixelData;
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->target, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}
	void save_image()
	{
		if (this->width * this->height == 128 * 128 * 128)
		{
			std::cout << "save image start" << "\n";
			//glBindTexture(this->target, this->id);
			//glGetTexImage(this->target,0, GL_RGBA, GL_UNSIGNED_BYTE, &this->pixelData);
			SOIL_save_image("resourcefile/123.png", SOIL_SAVE_TYPE_PNG, 128 * 128, 128, 4, this->pixelData);
			std::cout << "save image end" << "\n";
		}
	}
	void set_filter(unsigned char filterType)
	{
		glBindTexture(this->target, this->id);
		if (filterType == 0)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		} else
		if (filterType == 1)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		} else 
		if (filterType == 2)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else
		if (filterType == 3)
		{
			glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}

	void paint_colors(const unsigned int type,glm::vec3 positionXZW, const int scale,bool isSphericalPainting)
	{	
		glBindTexture(this->target, this->id);
		if (isSphericalPainting) {
			glm::vec3 positionXZW2 (positionXZW + glm::vec3(63.5f));
			if (scale > 16)
			{
				glGetTexImage(this->target, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
				for (int i (static_cast<int>(positionXZW2.x - scale / 2.f - 1));i < static_cast<int>(positionXZW2.x + scale / 2.f + 1);i++)
				{
					for (int j (static_cast<int>(positionXZW2.y - scale / 2.f - 1));j < static_cast<int>(positionXZW2.y + scale / 2.f + 1);j++)
					{
						for (int k (static_cast<int>(positionXZW2.z - scale / 2.f - 1));k < static_cast<int>(positionXZW2.z + scale / 2.f + 1);k++)
						{
							if (length(glm::vec3(i, j, k) - positionXZW2) < scale / 2.f && i >= 0 && i < 128 && j >= 0 && j < 128 && k >= 0 && k < 128)
							{
								this->checkImage3D[k][j][i][0] = (GLubyte)type;
							}
						}
					}
				}
				glTexSubImage3D(this->target, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
			}
			if (scale <= 16) {

				this->checkImage3D[0][0][0][0] = (GLubyte)type;

				for (int i (static_cast<int>(positionXZW2.x - scale / 2.f - 1));i < static_cast<int>(positionXZW2.x + scale / 2.f + 1);i++)
				{
					for (int j (static_cast<int>(positionXZW2.y - scale / 2.f - 1));j < static_cast<int>(positionXZW2.y + scale / 2.f + 1);j++)
					{
						for (int k (static_cast<int>(positionXZW2.z - scale / 2.f - 1));k < static_cast<int>(positionXZW2.z + scale / 2.f + 1);k++)
						{
							if (length(glm::vec3(i, j, k) - positionXZW2) < scale / 2.f)
							{
								glTexSubImage3D(this->target, 0, i, j, k, 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
							}
						}
					}
				}
			}
		}
		if (!isSphericalPainting) {
			glm::vec3 positionXZW2(positionXZW + glm::vec3(63.5f- scale / 2.f));
			if (this->pType != type)
			{
				for (int i(0);i < 128;i++)
				{
					for (int j(0);j < 128;j++)
					{
						for (int k(0);k < 128;k++)
						{
							this->checkImage3D[k][j][i][0] = (GLubyte)type;
						}
					}
				}
				this->pType = type;
			}
			
			glTexSubImage3D(this->target, 0, static_cast<GLint>(ceil(positionXZW2.x)), static_cast<GLint>(ceil(positionXZW2.y)), static_cast<GLint>(ceil(positionXZW2.z)), scale, scale, scale, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
		}
		
	}

};

class CustomTexture3D
{
private:
	GLuint id;
	GLenum target;
	GLubyte checkImage3D[128][128][128][4];
	GLubyte checkImage3D0[128][128][128][4];
	GLubyte checkImageData3D[128][128][128][4];
public:

	CustomTexture3D(glm::ivec3 size = glm::ivec3(128), int channel = GL_RGBA)
	{
		this->target = GL_TEXTURE_3D;

		for (int i(0);i < 128;i++)
		{
			for (int j(0);j < 128;j++)
			{
				for (int k(0);k < 128;k++)
				{
					this->checkImage3D0[k][j][i][0] = (GLubyte)0;
					this->checkImage3D0[k][j][i][1] = (GLubyte)0;
					this->checkImage3D0[k][j][i][2] = (GLubyte)0;
					this->checkImage3D0[k][j][i][3] = (GLubyte)255;

					this->checkImage3D[k][j][i][0] = (GLubyte)1;
					this->checkImage3D[k][j][i][1] = (GLubyte)0;
					this->checkImage3D[k][j][i][2] = (GLubyte)0;
					this->checkImage3D[k][j][i][3] = (GLubyte)255;
				}
			}
		}

		glGenTextures(1, &this->id);
		glBindTexture(this->target, this->id);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (this->checkImage3D)
		{
			glTexImage3D(this->target, 0, channel, size.x, size.y, size.z, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glGenerateMipmap(this->target);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: "<< "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}

	~CustomTexture3D()
	{
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(this->target, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}

	void bind_image(const GLint textureUnit)
	{
		glBindImageTexture(textureUnit, this->id, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA16F);
	}

	void selectArea(glm::vec3 beginPosXZW, glm::vec3 endPosXZW)
	{
		glm::ivec3 beginPosXZW2(glm::ivec3(floor(beginPosXZW + glm::vec3(64.0f))));
		glm::ivec3 endPosXZW2(glm::ivec3(floor(endPosXZW + glm::vec3(64.0f))));
		glm::ivec3 ancherPosXZW(glm::ivec3(alg::min(beginPosXZW2.x, endPosXZW2.x), alg::min(beginPosXZW2.y, endPosXZW2.y), alg::min(beginPosXZW2.z, endPosXZW2.z)));
		glm::ivec3 scaleXZW(glm::ivec3(alg::abs(beginPosXZW2.x-endPosXZW2.x), alg::abs(beginPosXZW2.y-endPosXZW2.y), alg::abs(beginPosXZW2.z-endPosXZW2.z)));
		glBindTexture(this->target, this->id);
		glTexSubImage3D(this->target, 0, ancherPosXZW.x, ancherPosXZW.y, ancherPosXZW.z, scaleXZW.x+1, scaleXZW.y+1, scaleXZW.z+1, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
	}

	void unselectArea()
	{
		glBindTexture(this->target, this->id);
		glTexSubImage3D(this->target, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D0);
		glGetTexImage(this->target, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
	}

	void washArea()
	{
		glBindTexture(this->target, this->id);
		glTexSubImage3D(this->target, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
	}

	void getImageData()
	{
		glBindTexture(this->target, this->id);
		glGetTexImage(this->target, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
	}
	bool isDelete(glm::ivec3 indexXZW) 
	{
		if (indexXZW.x >= 0 && indexXZW.x <= 127 &&
			indexXZW.y >= 0 && indexXZW.y <= 127 &&
			indexXZW.z >= 0 && indexXZW.z <= 127) {
			return int(this->checkImageData3D[indexXZW.x][indexXZW.y][indexXZW.z][0]) == 1;
		}
			
		else
			return false;
	}

};

//class PixelBufferObject
//{
//	GLuint* PBO;
//public:
//	void* pixelData;
//	PixelBufferObject()
//	{
//		this->PBO = new GLuint[2];
//		glGenBuffers(2, this->PBO);
//		//glBindBuffer(GL_PIXEL_PACK_BUFFER,);
//	}
//
//	void get_pixels(unsigned width, unsigned height)
//	{
//		glBindBuffer(GL_PIXEL_PACK_BUFFER, this->PBO[0]);
//		glReadPixels(0, 0, width, height, GL_RGB, GL_FLOAT, nullptr);
//		this->pixelData = nullptr;
//		glBindBuffer(GL_PIXEL_PACK_BUFFER, this->PBO[1]);
//		glReadPixels(0, 0, width, height, GL_RGB, GL_FLOAT, nullptr);
//		this->pixelData = glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, width * height, GL_MAP_READ_BIT);
//		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
//		glBindBuffer(GL_PIXEL_PACK_BUFFER, GL_NONE);
//		GLuint PBO2(this->PBO[1]);
//		this->PBO[1] = this->PBO[0], this->PBO[0] = PBO2;
//	}
//
//	~PixelBufferObject()
//	{
//		glDeleteBuffers(2, this->PBO);
//		this->PBO = nullptr, delete[] this->PBO;
//		this->pixelData = nullptr, delete[] this->pixelData;
//	}
//};