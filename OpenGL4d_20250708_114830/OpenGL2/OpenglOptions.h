#pragma once
//#include<GLFW/glfw3.h>
void set_gl_options(GLFWwindow* window) {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPointSize(5.f);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	//glDepthFunc(GL_LESS);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
