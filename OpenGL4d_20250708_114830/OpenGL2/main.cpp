#include "phy4d.cu"
//ZOOOOOOOOOOOM IN BEFORE RECORDING!
//static void cursor_position_callback(GLFWwindow* window, double positionX, double positionY);
//void cursor_enter_callback(GLFWwindow* window, int entered);
//void mouse_button_callback(GLFWwindow* window, int button,int action, int mods);
void framebuffer_resize_call_back(GLFWwindow* window, int fbW, int fbH);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void char_callback(GLFWwindow* window, unsigned int c);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
Game* game;
int main(){
	game = new Game("YOUTUBE_TUTORIAL", 1920, 1080, 4, 4, true);
	init_physics4d_function();
	//glfwSetCursorPosCallback(game->window, cursor_position_callback);
	//glfwSetCursorEnterCallback(game->window, cursor_enter_callback);
	//glfwSetMouseButtonCallback(game->window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(game->window, framebuffer_resize_call_back);
	glfwSetScrollCallback(game->window, scroll_callback);
	glfwSetCharCallback(game->window, char_callback);
	glfwSetKeyCallback(game->window, key_callback);
	//MAIN LOOP
	for (;!game->getWindowShouldClose();)
	{
		//UPDATE INPUT ---
		game->update0();
		if (game->isFixedTime) { phy_function(game->rigidBodies4d, game->walls4d, &game->collisionsVec); }
		game->update1();
		game->render0();
		if (game->isCloseUI) glfwSetScrollCallback(game->window, scroll_callback);
	}
	destroy_physics4d_function();
	delete game;
	return 0;
}
void framebuffer_resize_call_back(GLFWwindow* window, int fbW, int fbH){
	glViewport(0, 0, fbW, fbH);
	game->updateProjectMat(fbW, fbH);
	//std::cout << "fbH=" << fbH << "\n";
};

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset){
	game->update_scroll_input(-1, yOffset);
};

void char_callback(GLFWwindow* window, unsigned int c)
{
	//std::cout << c << '\n';
	game->textinputs_add(c);
};
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << key << '\n';
	game->textinputs_delete(key, action);
};
