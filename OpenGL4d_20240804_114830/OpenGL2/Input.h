//#pragma once
#pragma once

#include<iostream>
#include<vector>

#include<GLFW/glfw3.h>

class Input
{
	bool isRelease;
	bool isPress;
    bool isOnPress;
	bool isOnRelease;
    bool isRecord;
    float recordTime;
    bool isDoublePress;
public:
    Input() { 
		isRelease = false;
		isOnPress = false;
		isRecord = false;
		recordTime = 0.f;
		isDoublePress=false;
    }
    ~Input() {
    }
	bool getKeyOnPress(GLFWwindow* window, int key)
	{
		isOnPress = false;
		if (glfwGetKey(window, key) == GLFW_RELEASE)
		{
			isRelease = true;
		}
		else if (glfwGetKey(window, key) == GLFW_PRESS && isRelease)
		{
			isRelease = false;
			isOnPress = true;
		}
		return isOnPress;
	}

	bool getKeyOnRelease(GLFWwindow* window, int key)
	{
		isOnRelease = false;
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			isPress = true;
		}
		else if (glfwGetKey(window, key) == GLFW_RELEASE && isPress)
		{
			isPress = false;
			isOnRelease = true;
		}
		return isOnRelease;
	}

	bool getKeyDoublePress(GLFWwindow* window, int key, float clampTime, float dt)
	{
		isDoublePress = false;
		if (getKeyOnPress(window, key)) {
			if (isRecord) {
				isDoublePress = true;
				recordTime = 0.f;
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
		isOnPress = false;
		if (glfwGetMouseButton(window, mouseButton) == GLFW_RELEASE)
		{
			isRelease = true;
		}
		else if (glfwGetMouseButton(window, mouseButton) == GLFW_PRESS && isRelease)
		{
			isRelease = false;
			isOnPress = true;
		}
		return isOnPress;
	}

	bool getMouseOnRelease(GLFWwindow* window, int mouseButton)
	{
		isOnRelease = false;
		if (glfwGetMouseButton(window, mouseButton) == GLFW_PRESS)
		{
			isPress = true;
		}
		else if (glfwGetMouseButton(window, mouseButton) == GLFW_RELEASE && isPress)
		{
			isPress = false;
			isOnRelease = true;
		}
		return isOnRelease;
	}

	bool getMouseDoublePress(GLFWwindow* window, int mouseButton, float clampTime, float dt)
	{
		isDoublePress = false;
		if (glfwGetMouseButton(window, mouseButton)) {
			if (isRecord) {
				isDoublePress = true;
				recordTime = 0.f;
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
