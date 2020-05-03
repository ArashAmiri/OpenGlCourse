#pragma once

#include <glm\glm.hpp>

#include "Light.h"

class APointLight : ALight
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

	~APointLight();

	void UseLight(
		GLfloat ambientIntensityLocation,
		GLfloat ambientColorLocation,
		GLfloat diffuseIntensityLocation,
		GLfloat PositionLocation,
		GLfloat ConstantLocation,
		GLfloat LinearLocation,
		GLfloat ExponentLocation
	);

private:

	glm::vec3 Position;
	GLfloat Constant, Linear, Exponent;

};

