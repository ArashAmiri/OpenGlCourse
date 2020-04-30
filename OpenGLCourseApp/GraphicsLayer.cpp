#include "GraphicsLayer.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

void GraphicsLayer::ClearScreen(glm::vec4 ColorAndAlpha)
{
	//Clear window
	glClearColor(ColorAndAlpha.x, ColorAndAlpha.y, ColorAndAlpha.z, ColorAndAlpha.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GraphicsLayer::PassUniforms(
	const GLuint &uniformProjection, 
	const GLuint &uniformView, 
	const GLuint &uniformEyePosition, 
	const glm::mat4 &projection, 
	const ACamera &Camera)
{
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(Camera.CalculateViewMatrix()));
	glUniform3f(uniformEyePosition, Camera.GetPosition().x, Camera.GetPosition().y, Camera.GetPosition().z);
}

void GraphicsLayer::UseShaderProgram(int ProgramId)
{
	glUseProgram(ProgramId);
}
