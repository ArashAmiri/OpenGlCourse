#pragma once

#include "Light.h"

class ADirectionalLight : ALight
{

public:

	ADirectionalLight();

	ADirectionalLight(
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity,
		GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir
		);

	void UseLight(
		GLuint ambientIntensityLocation, 
		GLuint ambientColorLocation,
		GLuint diffuseIntensityLocation,
		GLuint directionLocation);

	~ADirectionalLight();

protected:

	glm::vec3 Direction;

};

