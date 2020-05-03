#pragma once

#include "PointLight.h"

class ASpotLight : public APointLight
{
public:
	ASpotLight();

	ASpotLight(
		GLfloat Red, GLfloat Green, GLfloat Blue,
		GLfloat AmbientIntensity, GLfloat DIntensity,
		GLfloat XPos, GLfloat YPos, GLfloat ZPos,
		GLfloat XDir, GLfloat YDir, GLfloat ZDir,		
		GLfloat ConstantToSet, GLfloat Linear, GLfloat Exponent,
		GLfloat Edge
	);

	void UseLight(
		GLuint ambientIntensityLocation,
		GLuint ambientColorLocation,
		GLuint diffuseIntensityLocation,
		GLuint PositionLocation,
		GLuint DirectionLocation,
		GLuint ConstantLocation,
		GLuint LinearLocation,
		GLuint ExponentLocation,
		GLuint EdgeLocation
	);

	~ASpotLight();

private:
	glm::vec3 Direction;
	GLfloat Edge, ProcessedEdge;



};

