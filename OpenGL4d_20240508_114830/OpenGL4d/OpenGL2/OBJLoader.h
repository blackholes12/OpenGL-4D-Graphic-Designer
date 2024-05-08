#pragma once

////STD Libs
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<vector>
//#include<sstream>
//#include<algorithm>
//
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
////OpenGL Math libs
//#include<glm.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat4x4.hpp>
//#include<gtc/matrix_transform.hpp>
//#include<gtc/type_ptr.hpp>
//
////Own libs
//#include"Vertex.h"
//Vertex portions
static std::vector<glm::fvec3> vertex_positions;
static std::vector<glm::fvec2> vertex_texcoords;
static std::vector<glm::fvec3> vertex_normals;

//Face vectors
static std::vector<GLint> vertex_position_indicies;
static std::vector<GLint> vertex_texcoord_indicies;
static std::vector<GLint> vertex_normal_indicies;

//Vertex array
static std::vector<Vertex> vertices;
static Primitive primitive;
static std::stringstream ss;

static std::string line = "";
static std::string prefix = "";
static glm::vec3 temp_vec3;
static glm::vec2 temp_vec2;
static GLint temp_glint = 0;
static int counter;
static int loadCounter=0;
static Primitive loadOBJ(const char* file_name)
{
	ss.clear();
	line = "";
	prefix = "";
	vertex_positions.clear();
	vertex_texcoords.clear();
	vertex_normals.clear();
	vertex_position_indicies.clear();
	vertex_texcoord_indicies.clear();
	vertex_normal_indicies.clear();
	vertices.clear();
	std::ifstream in_file(file_name);
	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;


		if (prefix == "v") //Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		if (prefix == "f")
		{
			counter = 0;
			while (ss >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint - 1);
				if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint - 1);
				if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint - 1);

				//Handling characters
				if (ss.peek() == '/')
				{
					counter++;
					ss.ignore(1, '/');
				}
				if (ss.peek() == ' ')
				{
					counter = 0;
					ss.ignore(1, ' ');
				}

			}
		}

	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size(), Vertex());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = vertex_positions[vertex_position_indicies[i]];
		vertices[i].color = vertices[i].position;
		vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i]];
		vertices[i].normal = vertex_normals[vertex_normal_indicies[i]];
	}

	//DEBUG
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//Loaded success
	loadCounter++;
	std::cout << "OBJ file loaded!" << loadCounter << "\n";
	
	primitive.set(vertices.data(), (const unsigned int)vertices.size(), NULL, 0);
	
	return primitive;
}