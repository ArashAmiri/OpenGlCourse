#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	inline GLfloat getBufferWidth() { return bufferWidth; }
	inline GLfloat getBufferHeight() { return bufferHeight; }

	inline bool getShouldClose() { return mainWindow && glfwWindowShouldClose(mainWindow);  }

	inline bool* GetKeys() { return keys; }

	GLfloat GetXChange();

	GLfloat GetYChange();

	inline void swapBuffers() { 
		if (mainWindow)
			glfwSwapBuffers(mainWindow); 
	}

	~Window();

private:

	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	static void handleKeys(GLFWwindow* window, int key, int code, int action , int mode);
	void createCallbacks();
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};

