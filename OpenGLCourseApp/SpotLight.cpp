#include "SpotLight.h"

ASpotLight::ASpotLight() 
	: APointLight()
	, Direction(glm::vec3(0.f))
	, Edge(0.f)
{
	ProcessedEdge = cosf(glm::radians(Edge));
}

ASpotLight::ASpotLight(
	GLfloat Red,
	GLfloat Green,
	GLfloat Blue,
	GLfloat AmbientIntensity,
	GLfloat DIntensity,
	GLfloat XPos, GLfloat YPos, GLfloat ZPos,
	GLfloat XDir, GLfloat YDir, GLfloat ZDir,
	GLfloat ConstantToSet, GLfloat Linear, GLfloat Exponent,
	GLfloat Edge) 
	: APointLight(
		Red, Green, Blue,
		AmbientIntensity, DIntensity,
		XPos, YPos, ZPos,
		ConstantToSet, Linear, Exponent)
	, Direction(glm::vec3(XDir, YDir, ZDir)) 
	, Edge(Edge)
{
	ProcessedEdge = cosf(glm::radians(Edge));
}

void ASpotLight::UseLight(
	GLuint AmbientIntensityLocation, 
	GLuint AmbientColorLocation, 
	GLuint DiffuseIntensityLocation, 
	GLuint PositionLocation, 
	GLuint DirectionLocation, 
	GLuint ConstantLocation, GLuint LinearLocation, GLuint ExponentLocation,
	GLuint EdgeLocation)
{
	APointLight::UseLight(
		AmbientIntensityLocation, AmbientColorLocation,
		DiffuseIntensityLocation,
		PositionLocation,
		ConstantLocation, LinearLocation, ExponentLocation);
	glUniform3f(DirectionLocation, Direction.x, Direction.y, Direction.z);
	glUniform1f(EdgeLocation, ProcessedEdge);
}

ASpotLight::~ASpotLight()
{
}
