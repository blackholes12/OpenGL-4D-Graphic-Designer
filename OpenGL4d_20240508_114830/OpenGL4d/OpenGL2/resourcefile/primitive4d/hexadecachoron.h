#pragma once
//#include<GLFW/glfw3.h>
//#include<vec4.hpp>
namespace hexadecachoron {
	static glm::vec4 vertices4D[] =
	{
    glm::vec4(0.5, 0 ,0 ,0),
    glm::vec4(0, 0, 0, 0.5),
    glm::vec4(0, 0, 0.5, 0),
    glm::vec4(0, 0.5 ,0 ,0),
    glm::vec4(-0.5 ,0, 0, 0),
    glm::vec4(0, 0 ,0, -0.5),
    glm::vec4(0 ,0 ,-0.5 ,0),
    glm::vec4(0, -0.5, 0 ,0)
	};
	static glm::vec4 normals4D[] =
	{
    glm::vec4(-0.5,-0.5,-0.5,-0.5),
    glm::vec4(0.5,-0.5,-0.5,-0.5),
    glm::vec4(-0.5,-0.5,-0.5,0.5),
    glm::vec4(0.5,-0.5,-0.5,0.5),
    glm::vec4(0.5,-0.5,0.5,-0.5),
    glm::vec4(-0.5,-0.5,0.5,-0.5),
    glm::vec4(0.5,-0.5,0.5,0.5),
    glm::vec4(-0.5,-0.5,0.5,0.5),
    glm::vec4(-0.5,0.5,-0.5,-0.5),
    glm::vec4(0.5,0.5,-0.5,-0.5),
    glm::vec4(0.5,0.5,-0.5,0.5),
    glm::vec4(-0.5,0.5,-0.5,0.5),
    glm::vec4(-0.5,0.5,0.5,0.5),
    glm::vec4(0.5,0.5,0.5,0.5),
    glm::vec4(-0.5,0.5,0.5,-0.5),
    glm::vec4(0.5,0.5,0.5,-0.5)
	};
	static glm::ivec2 indices4D0[] =
	{
	glm::ivec2(7,0),glm::ivec2(6,0),glm::ivec2(5,0),glm::ivec2(4,0),
	glm::ivec2(5,1),glm::ivec2(6,1),glm::ivec2(7,1),glm::ivec2(0,1),
	glm::ivec2(7,2),glm::ivec2(6,2),glm::ivec2(4,2),glm::ivec2(1,2),
	glm::ivec2(0,3),glm::ivec2(6,3),glm::ivec2(7,3),glm::ivec2(1,3),
	glm::ivec2(7,4),glm::ivec2(5,4),glm::ivec2(0,4),glm::ivec2(2,4),
	glm::ivec2(4,5),glm::ivec2(5,5),glm::ivec2(7,5),glm::ivec2(2,5),
	glm::ivec2(0,6),glm::ivec2(1,6),glm::ivec2(7,6),glm::ivec2(2,6),
	glm::ivec2(1,7),glm::ivec2(4,7),glm::ivec2(7,7),glm::ivec2(2,7),
	glm::ivec2(6,8),glm::ivec2(5,8),glm::ivec2(4,8),glm::ivec2(3,8),
	glm::ivec2(0,9),glm::ivec2(5,9),glm::ivec2(6,9),glm::ivec2(3,9),
	glm::ivec2(6,10),glm::ivec2(1,10),glm::ivec2(0,10),glm::ivec2(3,10),
	glm::ivec2(6,11),glm::ivec2(4,11),glm::ivec2(1,11),glm::ivec2(3,11),
	glm::ivec2(4,12),glm::ivec2(2,12),glm::ivec2(1,12),glm::ivec2(3,12),
	glm::ivec2(0,13),glm::ivec2(1,13),glm::ivec2(2,13),glm::ivec2(3,13),
	glm::ivec2(4,14),glm::ivec2(5,14),glm::ivec2(2,14),glm::ivec2(3,14),
	glm::ivec2(2,15),glm::ivec2(5,15),glm::ivec2(0,15),glm::ivec2(3,15)
	};
}
