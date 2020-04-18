// OpenGLCourseApp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;

const float toRadians = 3.14159265f / 180.f;

GLuint VAO, VBO, IBO, shader, uniformModel, uniformProjection;

bool direction = true;

float triOffset = 0.f;
float triMaxOffset = 2.f;
float triIncrement = 0.005f;

float curAngle = 0.0f;

float sizeDirectionRight = true;
float curSize = .4f;
const float maxSize = .8f;
const float minSize = .1f;

// Vertex Shader
static const char* vShader = "								\n\
#version 330												\n\
															\n\
layout (location = 0) in vec3 pos;							\n\
															\n\
out vec4 vCol; 												\n\
															\n\
uniform mat4 model;											\n\
uniform mat4 projection;									\n\
															\n\
void main()													\n\
{															\n\
	gl_Position = projection * model * vec4(pos, 1.0);		\n\
	vCol = vec4(clamp(pos, 0.f, 1.f), 1.f);					\n\
}															\n\
";

// Fragment Shader
static const char* fShader = "								\n\
#version 330												\n\
															\n\
in vec4 vCol;												\n\
															\n\
															\n\
out vec4 color;												\n\
															\n\
void main()													\n\
{															\n\
	color = vCol;											\n\
}";

void CreateTriangle()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};



	GLfloat vertices[] = {
		-1.f, -1.f, 0.f, 
		0.f, -1.f, 1.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	{
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}
	

	glAttachShader(theProgram, theShader);
}

void CompileShaders() 
{
	shader = glCreateProgram();

	if (!shader) {
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
	uniformProjection = glGetUniformLocation(shader, "projection");

}

int main()
{
	if (!glfwInit())
	{
		printf("GLFW initialization failed!");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information
	GLint bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed.");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);


	//setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	glm::mat4 projection = glm::perspective(45.f, GLfloat(bufferWidth) / GLfloat(bufferHeight), .1f, 100.f);


	//Loop until window is closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get and handle user input event
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (sizeDirectionRight)
		{
			curSize += .01f;
		}
		else
		{
			curSize -= .01f;
		}

		if (curSize >= maxSize || curSize <= minSize) sizeDirectionRight = !sizeDirectionRight;

		if (abs(triOffset) >= triMaxOffset) direction = !direction;

		curAngle += 0.5;
		if (curAngle > 360) {
			curAngle -= 360;
		}

		//Clear window
		glClearColor(0.f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);
		{
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::scale(model, glm::vec3(.4f, .4f, 1.0f));
			model = glm::translate(model, glm::vec3(0.f, triOffset, -2.5f));
			//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 1.f, 0.f));

			glUniform1f(uniformModel, triOffset);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(VAO);
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
				{
					glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				}

			}
			glBindVertexArray(0);
		}
		glUseProgram(0);



		glfwSwapBuffers(mainWindow);
	}

	return 0;

}

