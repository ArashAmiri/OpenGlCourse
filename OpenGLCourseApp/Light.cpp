#include "Light.h"

ALight::ALight()
	: Color(glm::vec3(1.f, 1.f, 1.f))
	, AmbientIntensity(1.f)
	, DiffuseIntensity(0.f)
{}

ALight::ALight(
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat AmbientIntensityToSet,
	GLfloat DIntensity) 
	: AmbientIntensity(AmbientIntensityToSet)
	, DiffuseIntensity(DIntensity)
	, Color(glm::vec3(red, green, blue))
{}

void ALight::UseLight(
	GLfloat ambientIntensityLocation, 
	GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation
	)
{
	glUniform3f(ambientColorLocation, Color.x, Color.y, Color.z);
	glUniform1f(ambientIntensityLocation, AmbientIntensity);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);
}

ALight::~ALight()
{
}
