#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace pentachoron {
	static glm::vec4 vertices4D[] =
	{
	glm::vec4(0.158113883008419f, 0.204124145231932f, -0.577350269189626f ,0),
	glm::vec4(0.158113883008419f, 0.204124145231932f, 0.288675134594813f, -0.5),
	glm::vec4(0.158113883008419f ,0.204124145231932f, 0.288675134594813f, 0.5),
	glm::vec4(0.158113883008419f, -0.612372435695794f, 0, 0),
	glm::vec4(-0.632455532033676f ,0 ,0 ,0)
	};
	static glm::vec4 normals4D[] =
	{
	glm::vec4(-0.25,-0.322749,0.912871,5.26836e-09),
	glm::vec4(-0.25,-0.322749,-0.456435,0.790569),
	glm::vec4(-0.25,-0.322749,-0.456435,-0.790569),
	glm::vec4(-0.25,0.968246,0,5.26836e-09),
	glm::vec4(1,0,0,0),
	};
	static glm::ivec2 indices4D0[] =
	{
	glm::ivec2(1,0),glm::ivec2(4,0),glm::ivec2(2,0),glm::ivec2(3,0),
	glm::ivec2(2,1),glm::ivec2(4,1),glm::ivec2(0,1),glm::ivec2(3,1),
	glm::ivec2(0,2),glm::ivec2(4,2),glm::ivec2(1,2),glm::ivec2(3,2),
	glm::ivec2(1,3),glm::ivec2(4,3),glm::ivec2(0,3),glm::ivec2(2,3),
	glm::ivec2(1,4),glm::ivec2(3,4),glm::ivec2(2,4),glm::ivec2(0,4) 
	};
}
