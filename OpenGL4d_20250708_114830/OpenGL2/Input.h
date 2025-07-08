//#pragma once
#pragma once

//#include<iostream>
//#include<vector>

//#include<GLFW/glfw3.h>

class Input
{
public:
	bool isRelease;
	bool isPress;
	bool isRecord;
	float recordTime;
	bool isDoublePress;
    Input() { 
		this->isRelease = false;
		this->isPress = false;
		this->isRecord = false;
		this->recordTime = 0.f;
		this->isDoublePress = false;
    }
    ~Input() {
    }
	bool getKeyOnPress(GLFWwindow* window, int key)
	{
		if (glfwGetKey(window, key) == GLFW_RELEASE)
		{
			this->isRelease = true;
		}
		else if (this->isRelease)
		{
			this->isRelease = false;
			return true;
		}
		return false;
	}

	bool getKeyOnRelease(GLFWwindow* window, int key)
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			this->isPress = true;
		}
		else if (this->isPress)
		{
			this->isPress = false;
			return true;
		}
		return false;
	}

	bool getKeyDoublePress(GLFWwindow* window, int key, float clampTime, float dt)
	{
		this->isDoublePress = false;
		if (getKeyOnPress(window, key)) {
			if (this->isRecord) {
				this->recordTime = 0.f;
				this->isDoublePress = true;
			}
			this->isRecord = !this->isRecord;
		}
		if (this->isRecord) {
			this->recordTime += dt;
		}
		if (this->recordTime > clampTime) {
			this->isRecord = false;
			this->recordTime = 0.f;
		}
		return this->isDoublePress;
	}

	bool getMouseOnPress(GLFWwindow* window, int mouseButton)
	{
		if (glfwGetMouseButton(window, mouseButton) == GLFW_RELEASE)
		{
			this->isRelease = true;
		}
		else if (this->isRelease)
		{
			this->isRelease = false;
			return true;
		}
		return false;
	}

	bool getMouseOnRelease(GLFWwindow* window, int mouseButton)
	{
		if (glfwGetMouseButton(window, mouseButton) == GLFW_PRESS)
		{
			this->isPress = true;
		}
		else if (this->isPress)
		{
			this->isPress = false;
			return true;
		}
		return false;
	}

	bool getMouseDoublePress(GLFWwindow* window, int mouseButton, float clampTime, float dt)
	{
		this->isDoublePress = false;
		if (glfwGetMouseButton(window, mouseButton)) {
			if (this->isRecord) {
				this->recordTime = 0.f;
				this->isDoublePress = true;
			}
			this->isRecord = !this->isRecord;
		}
		if (this->isRecord) {
			this->recordTime += dt;
		}
		if (this->recordTime > clampTime) {
			this->isRecord = false;
			this->recordTime = 0.f;
		}
		return this->isDoublePress;
	}
};
