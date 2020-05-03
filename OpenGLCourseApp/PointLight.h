#pragma once

#include <glm\glm.hpp>

#include "Light.h"

class APointLight : public ALight
{
public:

	APointLight();

	APointLight(
		GLfloat Red, GLfloat Green, GLfloat Blue,
		GLfloat AmbientIntensity,
		GLfloat DIntensity,
		GLfloat XPos,
		GLfloat YPos,
		GLfloat ZPos,
		GLfloat ConstantToSet,
		GLfloat Linear,
		GLfloat Exponent
		);

	void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColorLocation,
		GLuint diffuseIntensityLocation,
		GLuint PositionLocation,
		GLuint ConstantLocation,
		GLuint LinearLocation,
		GLuint ExponentLocation
	);

	~APointLight();


protected:

	glm::vec3 Position;
	GLfloat Constant, Linear, Exponent;

};

