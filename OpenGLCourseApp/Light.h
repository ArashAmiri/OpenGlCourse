#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class ALight
{


public:
	ALight();

	ALight(
		GLfloat red, GLfloat green, GLfloat blue, 
		GLfloat ambientIntensity, 
		GLfloat dIntensity);
	~ALight();

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
		GLfloat diffuseIntensityLocation);

protected:

	glm::vec3 Color;
	GLfloat AmbientIntensity;
	GLfloat DiffuseIntensity;
	


};

