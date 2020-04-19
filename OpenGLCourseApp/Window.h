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

	inline void swapBuffers() { 
		if (mainWindow)
			glfwSwapBuffers(mainWindow); 
	}

	~Window();

private:

	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;



};

