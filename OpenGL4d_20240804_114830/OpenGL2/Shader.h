#pragma once
//#define GLEW_STATIC
//#include<iostream>
//#include<fstream>
//#include<string>
//
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//#include<glm.hpp>
//#include<vec2.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat4x4.hpp>
//#include<gtc\type_ptr.hpp>

class Shader
{
private:
	//Member variables
	GLuint id;
	const int versionMajor;
	const int versionMinor;

	//Private functions
	std::string load_shader_source(const char* fileName)
	{
		std::string temp("");
		std::string src("");

		std::ifstream in_file;

		//Vertex
		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << "\n";
		}

		in_file.close();

		std::string versionNr =
			std::to_string(this->versionMajor) +
			std::to_string(this->versionMinor) +
			"0";

		src.replace(src.find("#version"), 12, ("#version " + versionNr));

		return src;
	}

	GLuint load_shader(GLenum type, const char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader(glCreateShader(type));
		std::string str_src(this->load_shader_source(fileName));
		const GLchar* src(str_src.c_str());
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << "\n";
			std::cout << infoLog << "\n";
		}

		return shader;
	}

	void link_program_v_g_f(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);

		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}

	void link_program_v_g(GLuint vertexShader, GLuint geometryShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}

	void link_program_c(GLuint computeShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		glAttachShader(this->id, computeShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}

public:

	//Constructors/Destructors
	Shader(const int versionMajor, const int versionMinor,
		const char* vertexFile, const char* fragmentFile, const char* geometryFile = "")
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vertexFile);
		GLuint geometryShader(0);
		if (geometryFile != "")
			geometryShader = load_shader(GL_GEOMETRY_SHADER, geometryFile);
		GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, fragmentFile);
		this->link_program_v_g_f(vertexShader, geometryShader, fragmentShader);
		//End
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	Shader(const int versionMajor, const int versionMinor,
		const char* vertexFile, const char* geometryFile, unsigned type)
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vertexFile);
		GLuint geometryShader(0);
		if (geometryFile != "")
			geometryShader = load_shader(GL_GEOMETRY_SHADER, geometryFile);
		this->link_program_v_g(vertexShader, geometryShader);
		//End
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
	}

	Shader(const int versionMajor, const int versionMinor,
		const char* computeFile)
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint computeShader = load_shader(GL_COMPUTE_SHADER, computeFile);
		this->link_program_c(computeShader);
		//End
		glDeleteShader(computeShader);
	}

	~Shader()
	{
		glDeleteProgram(this->id);
	}

	GLuint get_id()
	{
		return this->id;
	}

	//Set uniform functions
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar* name)
	{

		glUniform1i(glGetUniformLocation(this->id, name), value);

	}

	void set1f(GLfloat value, const GLchar* name)
	{

		glUniform1f(glGetUniformLocation(this->id, name), value);

	}

	void set_vec2f(glm::fvec2 value, const GLchar* name)
	{

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	}

	void set_vec2u(glm::uvec2 value, const GLchar* name)
	{

		glUniform2uiv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	}

	void set_vec3f(glm::fvec3 value, const GLchar* name)
	{

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	}
	

	void set_vec4f(glm::fvec4 value, const GLchar* name)
	{

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	}

	void set_mat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

	}

	void set_mat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

	}

};