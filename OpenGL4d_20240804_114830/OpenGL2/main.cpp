#include "Game.h"

//ZOOOOOOOOOOOM IN BEFORE RECORDING!
//static void cursor_position_callback(GLFWwindow* window, double positionX, double positionY);
//void cursor_enter_callback(GLFWwindow* window, int entered);
//void mouse_button_callback(GLFWwindow* window, int button,int action, int mods);
void framebuffer_resize_call_back(GLFWwindow* window, int fbW, int fbH);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
Game* game;
int main(){
	game = new Game("YOUTUBE_TUTORIAL", 1920, 1080, 4, 4, true);
	//glfwSetCursorPosCallback(game->window, cursor_position_callback);
	//glfwSetCursorEnterCallback(game->window, cursor_enter_callback);
	//glfwSetMouseButtonCallback(game->window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(game->window, framebuffer_resize_call_back);
	glfwSetScrollCallback(game->window, scroll_callback);
	//MAIN LOOP
	for (;!game->getWindowShouldClose();)
	{
		//UPDATE INPUT ---
		game->update0();
		game->render0();
		if (game->isCloseUI) glfwSetScrollCallback(game->window, scroll_callback);
	}
	game = nullptr,delete game;
	return 0;
}
void framebuffer_resize_call_back(GLFWwindow* window, int fbW, int fbH){
	glViewport(0, 0, fbW, fbH);
	game->updateProjectMat(fbW, fbH);
	//std::cout << "fbH=" << fbH << "\n";
};

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset){
	game->updateModes(-1, yOffset);
};