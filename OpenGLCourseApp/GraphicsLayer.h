#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class ACamera;

class GraphicsLayer
{
public:

	static void ClearScreen(glm::vec4 ColorAndAlpha);

	static void PassUniforms(
		const GLuint &uniformProjection, 
		const GLuint &uniformView, 
		const GLuint &uniformEyePosition, 
		const glm::mat4 &projection, 
		const ACamera &Camera);

	static void UseShaderProgram(int ProgramId);

};

