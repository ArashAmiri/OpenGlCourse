#include "PointLight.h"

APointLight::APointLight() 
	: ALight()
	, Position(glm::vec3(0.0f))
	, Constant(1.f)
	, Linear(0.0f)
	, Exponent(0.0f)
{}

APointLight::APointLight(
	GLfloat Red, 
	GLfloat Green, 
	GLfloat Blue, 
	GLfloat AmbientIntensity, 
	GLfloat DIntensity, 
	GLfloat XPos,
	GLfloat YPos,
	GLfloat ZPos,
	GLfloat ConstantToSet,
	GLfloat LinearToSet,
	GLfloat ExponentToSet	
	)
	: ALight(Red, Green, Blue, AmbientIntensity, DIntensity)
	, Position(glm::vec3(XPos, YPos, ZPos))
	, Constant(ConstantToSet)
	, Linear(LinearToSet)
	, Exponent(ExponentToSet)
{}

APointLight::~APointLight()
{}

void APointLight::UseLight(
	GLfloat ambientIntensityLocation, 
	GLfloat ambientColorLocation, 
	GLfloat diffuseIntensityLocation, 
	GLfloat PositionLocation, 
	GLfloat ConstantLocation, 
	GLfloat LinearLocation, 
	GLfloat ExponentLocation)
{
	ALight::UseLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(PositionLocation, Position.x, Position.y, Position.z);
	glUniform1f(ConstantLocation, Constant);
	glUniform1f(LinearLocation, Linear);
	glUniform1f(ExponentLocation, Exponent);
}
