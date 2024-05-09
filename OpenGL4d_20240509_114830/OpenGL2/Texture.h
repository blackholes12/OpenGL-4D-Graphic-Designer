#pragma once

//#include<iostream>
//#include<string>

//#include<GLFW/glfw3.h>

//#include<SOIL2.h>

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;
	unsigned char* image;
public:

	Texture(const char* fileName)
	{
		this->type = GL_TEXTURE_2D;

		this->image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (this->image)
		{
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(this->image);
	}
	
	~Texture()
	{
		glDeleteTextures(1, &this->id);
		delete this->image;
		this->image = nullptr;
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	void loadFromFile(const char* fileName)
	{
		if (this->id)
		{
			glDeleteTextures(1, &this->id);
		}

		this->image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		if (this->image)
		{
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(this->image);
	}
};



class Texture3D
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;
	unsigned char* image3D;
	unsigned int pType = -1;
	float pScale = -1;
	GLubyte checkImage3D[128][128][128][4];
public:
	bool isTransparent;
	Texture3D(const char* fileName, bool isTransparent)
	{
		start_texture3D(fileName);
		this->isTransparent = isTransparent;
	}
	Texture3D(const char* fileName)
	{
		start_texture3D(fileName);
		this->isTransparent = false;
	}
	void start_texture3D(const char* fileName)
	{
		this->type = GL_TEXTURE_3D;

		this->image3D = SOIL_load_image(fileName ,&this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (this->image3D)
		{
			if (this->height == this->width * this->width) {
				glTexImage3D(this->type, 0, GL_RGBA, this->width, this->width, this->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image3D);
			}
			if (this->height == this->width * this->width / 4) {
				glTexImage3D(this->type, 0, GL_RGBA, this->width, this->width/2, this->width/2, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image3D);
			}
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(this->image3D);
	}

	~Texture3D()
	{
		glDeleteTextures(1, &this->id);
		this->image3D = nullptr,delete this->image3D;
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	void set_filter(unsigned filterType)
	{
		glBindTexture(this->type, this->id);
		if (filterType == 0)
		{
			glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		if (filterType == 1)
		{
			glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}
		if (filterType == 2)
		{
			glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		if (filterType == 3)
		{
			glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
	}

	void paintColors(const unsigned int type,glm::vec3 positionXZW, const int scale,bool isSphericalPainting)
	{	
		glBindTexture(this->type, this->id);
		if (isSphericalPainting) {
			glm::vec3 positionXZW2 (positionXZW + glm::vec3(63.5f));
			if (scale > 16)
			{
				glGetTexImage(this->type, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
				for (int i (positionXZW2.x - scale / 2.f - 1);i < positionXZW2.x + scale / 2.f + 1;i++)
				{
					for (int j (positionXZW2.y - scale / 2.f - 1);j < positionXZW2.y + scale / 2.f + 1;j++)
					{
						for (int k (positionXZW2.z - scale / 2.f - 1);k < positionXZW2.z + scale / 2.f + 1;k++)
						{
							if (length(glm::vec3(i, j, k) - positionXZW2) < scale / 2.f && i >= 0 && i < 128 && j >= 0 && j < 128 && k >= 0 && k < 128)
							{
								this->checkImage3D[k][j][i][0] = (GLubyte)type;
							}
						}
					}
				}
				glTexSubImage3D(this->type, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
			}
			if (scale <= 16) {

				this->checkImage3D[0][0][0][0] = (GLubyte)type;

				for (int i (positionXZW2.x - scale / 2.f - 1);i < positionXZW2.x + scale / 2.f + 1;i++)
				{
					for (int j (positionXZW2.y - scale / 2.f - 1);j < positionXZW2.y + scale / 2.f + 1;j++)
					{
						for (int k (positionXZW2.z - scale / 2.f - 1);k < positionXZW2.z + scale / 2.f + 1;k++)
						{
							if (length(glm::vec3(i, j, k) - positionXZW2) < scale / 2.f)
							{
								glTexSubImage3D(this->type, 0, i, j, k, 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
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
			
			glTexSubImage3D(this->type, 0, ceil(positionXZW2.x), ceil(positionXZW2.y), ceil(positionXZW2.z), scale, scale, scale, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
		}
		
	}

};

class DeleteMap3D
{
private:
	GLuint id;
	unsigned int type;
	GLubyte checkImage3D[128][128][128][4];
	GLubyte checkImage3D0[128][128][128][4];
	GLubyte checkImageData3D[128][128][128][4];
public:

	DeleteMap3D()
	{
		this->type = GL_TEXTURE_3D;

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
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (this->checkImage3D)
		{
			glTexImage3D(this->type, 0, GL_RGBA, 128, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D0);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: "<< "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	~DeleteMap3D()
	{
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	int min(int a, int b) {
		return a < b ?a:b;
	}

	void selectArea(glm::vec3 beginPosXZW, glm::vec3 endPosXZW)
	{
		glm::ivec3 beginPosXZW2(glm::ivec3(floor(beginPosXZW + glm::vec3(64.0f))));
		glm::ivec3 endPosXZW2(glm::ivec3(floor(endPosXZW + glm::vec3(64.0f))));
		glm::ivec3 ancherPosXZW(glm::ivec3(min(beginPosXZW2.x, endPosXZW2.x), min(beginPosXZW2.y, endPosXZW2.y), min(beginPosXZW2.z, endPosXZW2.z)));
		glm::ivec3 scaleXZW(glm::ivec3(abs(beginPosXZW2.x-endPosXZW2.x), abs(beginPosXZW2.y-endPosXZW2.y), abs(beginPosXZW2.z-endPosXZW2.z)));
		glBindTexture(this->type, this->id);
		glTexSubImage3D(this->type, 0, ancherPosXZW.x, ancherPosXZW.y, ancherPosXZW.z, scaleXZW.x+1, scaleXZW.y+1, scaleXZW.z+1, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D);
	}

	void unselectArea()
	{
		glBindTexture(this->type, this->id);
		glTexSubImage3D(this->type, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImage3D0);
		glGetTexImage(this->type, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
	}

	void washArea()
	{
		glBindTexture(this->type, this->id);
		glTexSubImage3D(this->type, 0, 0, 0, 0, 128, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
	}

	void getImageData()
	{
		glBindTexture(this->type, this->id);
		glGetTexImage(this->type, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->checkImageData3D);
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