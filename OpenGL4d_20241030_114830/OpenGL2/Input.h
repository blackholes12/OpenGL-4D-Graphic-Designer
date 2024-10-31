//#pragma once
#pragma once

//#include<iostream>
//#include<vector>

//#include<GLFW/glfw3.h>

class Input
{
	bool isRelease;
	bool isPress;
    bool isRecord;
    float recordTime;
	bool isDoublePress;
public:
    Input() { 
		isRelease = false;
		isRecord = false;
		recordTime = 0.f;
		isDoublePress = false;
    }
    ~Input() {
    }
	bool getKeyOnPress(GLFWwindow* window, int key)
	{
		if (glfwGetKey(window, key) == GLFW_RELEASE)
		{
			isRelease = true;
		}
		else if (isRelease)
		{
			isRelease = false;
			return true;
		}
		return false;
	}

	bool getKeyOnRelease(GLFWwindow* window, int key)
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			isPress = true;
		}
		else if (isPress)
		{
			isPress = false;
			return true;
		}
		return false;
	}

	bool getKeyDoublePress(GLFWwindow* window, int key, float clampTime, float dt)
	{
		isDoublePress = false;
		if (getKeyOnPress(window, key)) {
			if (isRecord) {
				recordTime = 0.f;
				isDoublePress = true;
			}
			isRecord = !isRecord;
		}
		if (isRecord) {
			recordTime += dt;
		}
		if (recordTime > clampTime) {
			isRecord = false;
			recordTime = 0.f;
		}
		return isDoublePress;
	}

	bool getMouseOnPress(GLFWwindow* window, int mouseButton)
	{
		if (glfwGetMouseButton(window, mouseButton) == GLFW_RELEASE)
		{
			isRelease = true;
		}
		else if (isRelease)
		{
			isRelease = false;
			return true;
		}
		return false;
	}

	bool getMouseOnRelease(GLFWwindow* window, int mouseButton)
	{
		if (glfwGetMouseButton(window, mouseButton) == GLFW_PRESS)
		{
			isPress = true;
		}
		else if (isPress)
		{
			isPress = false;
			return true;
		}
		return false;
	}

	bool getMouseDoublePress(GLFWwindow* window, int mouseButton, float clampTime, float dt)
	{
		isDoublePress = false;
		if (glfwGetMouseButton(window, mouseButton)) {
			if (isRecord) {
				recordTime = 0.f;
				isDoublePress = true;
			}
			isRecord = !isRecord;
		}
		if (isRecord) {
			recordTime += dt;
		}
		if (recordTime > clampTime) {
			isRecord = false;
			recordTime = 0.f;
		}
		return isDoublePress;
	}
};
