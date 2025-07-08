#pragma once

#include<iostream>
#include<vector>

#include"Vertex.h"
#include"Primitives.h"
#include"Primitives4D.h"
#include"Shader.h"
#include"Texture.h"
#include"bivec4.h"

class Mesh
{
private:
	Vertex* vertexArray;
	size_t sizeOfVertices;
	GLuint* indexArray;
	size_t sizeOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 Rotate_Angle;
	glm::vec3 Rotate_Angle_rad;
	glm::vec3 scale;

	glm::mat4 ObjectMat;

	void initVAO()
	{
		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* this->sizeOfVertices, this->vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		if (this->sizeOfIndices > 0)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* this->sizeOfIndices, this->indexArray, GL_STATIC_DRAW);
		}

		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
	}

	void updateObjectMat()
	{
		this->Rotate_Angle_rad = this->Rotate_Angle * glm::pi<float>() / 180.f;
	this->ObjectMat =
			glm::mat4(1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f);
		this->ObjectMat = this->ObjectMat*
			glm::mat4(cos(this->Rotate_Angle_rad.z), -sin(this->Rotate_Angle_rad.z), 0.f, 0.f,
				sin(this->Rotate_Angle_rad.z), cos(this->Rotate_Angle_rad.z), 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f)*
			glm::mat4(1.f, 0, 0, 0,
				0.f, cos(this->Rotate_Angle_rad.x), -sin(this->Rotate_Angle_rad.x), 0.f,
				0.f, sin(this->Rotate_Angle_rad.x), cos(this->Rotate_Angle_rad.x), 0.f,
				0.f, 0.f, 0.f, 1.f)*
			glm::mat4(cos(this->Rotate_Angle_rad.y), 0.f, sin(this->Rotate_Angle_rad.y), 0.f,
				0.f, 1.f, 0.f, 0.f,
				-sin(this->Rotate_Angle_rad.y), 0.f, cos(this->Rotate_Angle_rad.y), 0.f,
				0.f, 0.f, 0.f, 1.f)
			;
		this->ObjectMat = this->ObjectMat
			* glm::mat4(this->scale.x, 0.f, 0.f, 0.f,
				0.f, this->scale.y, 0.f, 0.f,
				0.f, 0.f, this->scale.z, 0.f,
				0.f, 0.f, 0.f, 1.f)
			;
	}

public:
	
	Mesh(
		Primitive primitive,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 Rotate_Angle = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->Rotate_Angle = Rotate_Angle;
		this->scale = scale;

		this->sizeOfVertices = primitive.getsizeOfVertices();
		this->sizeOfIndices = primitive.getsizeOfIndices();

		this->vertexArray = new Vertex[this->sizeOfVertices];
		for (size_t i = 0; i < this->sizeOfVertices; i++)
		{
			this->vertexArray[i] = primitive.getVertices()[i];
		}

		this->indexArray = new GLuint[this->sizeOfIndices];
		for (size_t i = 0; i < this->sizeOfIndices; i++)
		{
			this->indexArray[i] = primitive.getIndices()[i];
		}

		this->initVAO();
		this->updateObjectMat();
	}

	Mesh(const Mesh& obj)
	{
		this->position = obj.position;
		this->Rotate_Angle = obj.Rotate_Angle;
		this->scale = obj.scale;

		this->sizeOfVertices = obj.sizeOfVertices;
		this->sizeOfIndices = obj.sizeOfIndices;

		this->vertexArray = new Vertex[this->sizeOfVertices];
		for (size_t i = 0; i < this->sizeOfVertices; i++)
		{
			this->vertexArray[i] = obj.vertexArray[i];
		}

		this->indexArray = new GLuint[this->sizeOfIndices];
		for (size_t i = 0; i < this->sizeOfIndices; i++)
		{
			this->indexArray[i] = obj.indexArray[i];
		}

		this->initVAO();
		this->updateObjectMat();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);

		if (this->sizeOfIndices > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}

		delete[] this->vertexArray;
		delete[] this->indexArray;
	}

	//Accessors
	void setObjMat() 
	{
		this->updateObjectMat();
	}
	//set get
	void set_mesh_position(glm::vec3 position)
	{
		this->position = position;
		this->updateObjectMat();
	}
	void get_mesh_position(glm::vec3* position) {
		*position= this->position;
	}

	void set_mesh_rotate_angle(glm::vec3 Rotate_Angle)
	{
		this->Rotate_Angle = Rotate_Angle;
		this->updateObjectMat();
	}
	void get_mesh_rotate_angle(glm::vec3* Rotate_Angle) {
		*Rotate_Angle = this->Rotate_Angle;
	}

	void set_mesh_scale(glm::vec3 scale)
	{
		this->scale = scale;
		this->updateObjectMat();
	}
	void get_mesh_scale(glm::vec3* scale) {
		*scale = this->scale;
	}

	void render(Shader* shader)
	{	
		//Update shader
		shader->use();
		shader->set_mat4fv(this->ObjectMat, "ObjectMat");
		shader->set_vec3f(this->position, "translate");
		//Bind VAO
		glBindVertexArray(this->VAO);
		//RENDER
		if (this->sizeOfIndices > 0)
			glDrawElements(GL_TRIANGLES, (GLsizei)this->sizeOfIndices, GL_UNSIGNED_INT, 0);
		else if (this->sizeOfIndices == 0)
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)this->sizeOfVertices);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mesh4D
{
private:
	Vertex4D* vertexArray4D;
	unsigned sizeOfVertices4D;
	GLuint* indexArray4D;
	unsigned sizeOfIndices4D;

	FrameVertex4D* vertexFrameArray4D;
	unsigned sizeOfFrameVertices4D;
	GLuint* indexFrameArray4D;
	unsigned sizeOfFrameIndices4D;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint VAO2;
	GLuint VBO2;
	GLuint EBO2;

	glm::vec4 position4d;
	//alg::bivec4 rotateAngle4D;
	alg::rotor4 rotation4D;
	glm::vec4 scale4D;

	glm::mat4 mesh4DMat;

	void initVAO()
	{
		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex4D)* this->sizeOfVertices4D, this->vertexArray4D, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		if (this->sizeOfIndices4D != 0)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* this->sizeOfIndices4D, this->indexArray4D, GL_STATIC_DRAW);
		}

		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//PositionA
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, positions4D[0]));
		glEnableVertexAttribArray(0);
		//PositionB
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, positions4D[1]));
		glEnableVertexAttribArray(1);
		//PositionC
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, positions4D[2]));
		glEnableVertexAttribArray(2);
		//PositionD
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, positions4D[3]));
		glEnableVertexAttribArray(3);

		//TexcoordD
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, texcoords3D[0]));
		glEnableVertexAttribArray(4);
		//TexcoordD
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, texcoords3D[1]));
		glEnableVertexAttribArray(5);
		//TexcoordD
		glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, texcoords3D[2]));
		glEnableVertexAttribArray(6);
		//TexcoordD
		glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, texcoords3D[3]));
		glEnableVertexAttribArray(7);

		//NormalA
		glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, normals4D[0]));
		glEnableVertexAttribArray(8);
		//NormalB
		glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, normals4D[1]));
		glEnableVertexAttribArray(9);
		//NormalC
		glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, normals4D[2]));
		glEnableVertexAttribArray(10);
		//NormalD
		glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, normals4D[3]));
		glEnableVertexAttribArray(11);
		//ID
		glVertexAttribPointer(12, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex4D), (GLvoid*)offsetof(Vertex4D, id));
		glEnableVertexAttribArray(12);
		//BIND VAO 0
		glBindVertexArray(0);
	}

	void initVAO2()
	{
		glCreateVertexArrays(1, &this->VAO2);
		glBindVertexArray(this->VAO2);

		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO2);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FrameVertex4D) * this->sizeOfFrameVertices4D, this->vertexFrameArray4D, GL_STATIC_DRAW);
		//GEN EBO AND BIND AND SEND DATA
		if (this->sizeOfFrameIndices4D != 0)
		{
			glGenBuffers(1, &this->EBO2);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO2);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->sizeOfFrameIndices4D, this->indexFrameArray4D, GL_STATIC_DRAW);
		}
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FrameVertex4D), (GLvoid*)offsetof(FrameVertex4D, pos4D));
		glEnableVertexAttribArray(0);
		//BIND VAO 0
		glBindVertexArray(0);
	}
	
	void update_mesh4D_mat()
	{
		this->mesh4DMat = to_matrix(this->rotation4D) *

		    glm::mat4(this->scale4D.x, 0.f, 0.f, 0.f,
				0.f, this->scale4D.y, 0.f, 0.f,
				0.f, 0.f, this->scale4D.z, 0.f,
				0.f, 0.f, 0.f, this->scale4D.w)
			;
	}
	void update_mesh4D_mat(glm::mat4 mesh4DMat)
	{
		this->mesh4DMat = mesh4DMat;
	}

public:

	Mesh4D(
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D
	)
	{
		this->position4d = position4d;
		//this->rotateAngle4D = rotateAngle4D;
		this->scale4D = scale4D;

		this->sizeOfVertices4D = primitive4D.get_size_of_vertices4D();
		this->sizeOfIndices4D = primitive4D.get_size_of_indices4D();

		this->vertexArray4D = new Vertex4D[this->sizeOfVertices4D];
		for (unsigned i = 0; i < this->sizeOfVertices4D; i++)
		{
			this->vertexArray4D[i] = primitive4D.get_vertices4D()[i];
		}

		this->indexArray4D = new GLuint[this->sizeOfIndices4D];
		for (unsigned i = 0; i < this->sizeOfIndices4D; i++)
		{
			this->indexArray4D[i] = primitive4D.get_indices4D()[i];
		}
///////////////////////
		this->sizeOfFrameVertices4D = primitive4D.get_size_of_frame_vertices4D();
		this->sizeOfFrameIndices4D = primitive4D.get_size_of_frame_indices4D();

		this->vertexFrameArray4D = new FrameVertex4D[this->sizeOfFrameVertices4D];
		for (unsigned i = 0; i < this->sizeOfFrameVertices4D; i++)
		{
			this->vertexFrameArray4D[i] = primitive4D.get_frame_vertices4D()[i];
		}

		this->indexFrameArray4D = new GLuint[this->sizeOfFrameIndices4D];
		for (unsigned i = 0; i < this->sizeOfFrameIndices4D; i++)
		{
			this->indexFrameArray4D[i] = primitive4D.get_frame_indices4D()[i];
		}

		this->initVAO();
		this->initVAO2();
		this->set_mesh_rotation_mat4(to_matrix(rotation4D));
	}

	Mesh4D(const Mesh4D& obj)
	{
		this->position4d = obj.position4d;
		this->rotation4D = obj.rotation4D;
		this->scale4D = obj.scale4D;

		this->sizeOfVertices4D = obj.sizeOfVertices4D;
		this->sizeOfIndices4D = obj.sizeOfIndices4D;

		this->vertexArray4D = new Vertex4D[this->sizeOfVertices4D];
		for (unsigned i = 0; i < this->sizeOfVertices4D; i++)
		{
			this->vertexArray4D[i] = obj.vertexArray4D[i];
		}

		this->indexArray4D = new GLuint[this->sizeOfIndices4D];
		for (unsigned i = 0; i < this->sizeOfIndices4D; i++)
		{
			this->indexArray4D[i] = obj.indexArray4D[i];
		}
		///////////////////
		this->sizeOfFrameVertices4D = obj.sizeOfFrameVertices4D;
		this->sizeOfFrameIndices4D = obj.sizeOfFrameIndices4D;

		this->vertexFrameArray4D = new FrameVertex4D[this->sizeOfFrameVertices4D];
		for (unsigned i = 0; i < this->sizeOfFrameVertices4D; i++)
		{
			this->vertexFrameArray4D[i] = obj.vertexFrameArray4D[i];
		}

		this->indexFrameArray4D = new GLuint[this->sizeOfFrameIndices4D];
		for (unsigned i = 0; i < this->sizeOfFrameIndices4D; i++)
		{
			this->indexFrameArray4D[i] = obj.indexFrameArray4D[i];
		}

		this->initVAO();
		this->initVAO2();
		this->set_mesh_rotation_mat4(to_matrix(this->rotation4D));
	}

	~Mesh4D()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteVertexArrays(1, &this->VAO2);
		glDeleteBuffers(1, &this->VBO2);

		if (this->sizeOfIndices4D > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}
		if (this->sizeOfFrameIndices4D > 0)
		{
			glDeleteBuffers(1, &this->EBO2);
		}

		delete[] this->vertexArray4D;
		delete[] this->indexArray4D;
		delete[] this->vertexFrameArray4D;
		delete[] this->indexFrameArray4D;
	}

	//Accessors
	//set get
	void set_mesh_position4D(glm::vec4 position4d)
	{
		this->position4d = position4d;
	}
	glm::vec4 get_mesh_position4D() {
		return this->position4d;
	}

	void set_mesh_rotation4D(alg::rotor4 rotation4D)
	{
		this->rotation4D = rotation4D;
		this->update_mesh4D_mat();
	}

	void set_mesh_rotation4D(alg::rotor4 rotation4D, glm::mat4 mesh4DMat)
	{
		this->rotation4D = rotation4D;
		this->update_mesh4D_mat(mesh4DMat);
	}

	void get_mesh_rotation4D(alg::rotor4* rotation4D)
	{
		*rotation4D = this->rotation4D;
	}

	void set_mesh_scale4D(glm::vec4 scale4D)
	{
		this->scale4D = scale4D;
		this->update_mesh4D_mat();
	}
	void get_mesh_scale4D(glm::vec4* scale4D) {
		*scale4D = this->scale4D;
	}
	void set_mesh_rotation_mat4(glm::mat4 mesh4DMat)
	{
		this->mesh4DMat = mesh4DMat*
			glm::mat4(this->scale4D.x, 0.f, 0.f, 0.f,
				0.f, this->scale4D.y, 0.f, 0.f,
				0.f, 0.f, this->scale4D.z, 0.f,
				0.f, 0.f, 0.f, this->scale4D.w);
	}
	const glm::mat4 get_mesh_mat4()
	{
		return this->mesh4DMat;
	}

	void render(Shader* shader)
	{
		//Update shader
		//shader->use();
		shader->set_mat4fv(this->mesh4DMat, "mesh4DMat");
		shader->set_vec4f(this->position4d, "translate4D");
		//Bind VAO
		glBindVertexArray(this->VAO);
		//RENDER
		if (this->sizeOfIndices4D > 0)glDrawElements(GL_TRIANGLES, (GLsizei)this->sizeOfIndices4D, GL_UNSIGNED_INT, 0);
		else glDrawArrays(GL_TRIANGLES, 0, (GLsizei)this->sizeOfVertices4D);
	}
	void render2(Shader* shader2)
	{
		shader2->set_mat4fv(this->mesh4DMat, "mesh4DMat");
		shader2->set_vec4f(this->position4d, "translate4D");
		glBindVertexArray(this->VAO2);
		if (this->sizeOfIndices4D > 0)glDrawElements(GL_LINES, (GLsizei)this->sizeOfFrameIndices4D, GL_UNSIGNED_INT, 0);
		else glDrawArrays(GL_LINES, 0,(GLsizei)this->sizeOfFrameIndices4D);
	}
};

//class Particle4DMesh
//{
//private:
//	Vertex* vertexArray;
//	unsigned sizeOfVertices;
//	GLuint* indexArray;
//	unsigned sizeOfIndices;
//	float intensity;
//
//	GLuint VAO;
//	GLuint VBO;
//	GLuint EBO;
//
//	glm::vec4 position4d;
//	Texture3D* diffuse3D;
//	glm::mat4 Particle4DMat;
//
//	void initVAO()
//	{
//		//Create VAO
//		glCreateVertexArrays(1, &this->VAO);
//		glBindVertexArray(this->VAO);
//
//		//GEN VBO AND BIND AND SEND DATA
//		glGenBuffers(1, &this->VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* this->sizeOfVertices, this->vertexArray, GL_STATIC_DRAW);
//
//		//GEN EBO AND BIND AND SEND DATA
//		if (this->sizeOfIndices > 0)
//		{
//			glGenBuffers(1, &this->EBO);
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
//			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* this->sizeOfIndices, this->indexArray, GL_STATIC_DRAW);
//		}
//
//		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
//		//Position
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
//		glEnableVertexAttribArray(0);
//		//Color
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
//		glEnableVertexAttribArray(1);
//		//Texcoord
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
//		glEnableVertexAttribArray(2);
//		//Normal
//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
//		glEnableVertexAttribArray(3);
//
//		//BIND VAO 0
//		glBindVertexArray(0);
//	}
//
//public:
//
//	Particle4DMesh(
//		Primitive primitive,
//		glm::vec4 position4d ,
//		float intensity, 
//		Texture3D* diffuse3D)
//	{
//		this->position4d = position4d;
//		this->intensity = intensity;
//		this->diffuse3D = diffuse3D;
//		this->sizeOfVertices = primitive.getsizeOfVertices();
//		this->sizeOfIndices = primitive.getsizeOfIndices();
//
//		this->vertexArray = new Vertex[this->sizeOfVertices];
//		for (unsigned i = 0; i < this->sizeOfVertices; i++)
//		{
//			this->vertexArray[i] = primitive.getVertices()[i];
//		}
//
//		this->indexArray = new GLuint[this->sizeOfIndices];
//		for (unsigned i = 0; i < this->sizeOfIndices; i++)
//		{
//			this->indexArray[i] = primitive.getIndices()[i];
//		}
//
//		this->initVAO();
//	}
//
//	~Particle4DMesh()
//	{
//		glDeleteVertexArrays(1, &this->VAO);
//		glDeleteBuffers(1, &this->VBO);
//
//		if (this->sizeOfIndices > 0)
//		{
//			glDeleteBuffers(1, &this->EBO);
//		}
//
//		delete[] this->vertexArray;
//		this->vertexArray = nullptr;
//		delete[] this->indexArray;
//		this->indexArray = nullptr;
//	}
//
//	
//	void render(Shader* shader)
//	{
//		//Update shader
//		this->diffuse3D->bind(0);
//		shader->use();
//
//		shader->set1f(0.67f * pow(intensity, 1.f / 3.f), "radius");
//		shader->set_vec4f(this->position4d, "translate4D");
//		//std::cout << "Light Height:" << this->position4d.y << "\n";
//		//Bind VAO
//		glBindVertexArray(this->VAO);
//		//RENDER
//		if (this->sizeOfIndices == 0)
//			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)this->sizeOfVertices);
//		if (this->sizeOfIndices != 0)
//			glDrawElements(GL_TRIANGLES, (GLsizei)this->sizeOfIndices, GL_UNSIGNED_INT, 0);
//	}
//};