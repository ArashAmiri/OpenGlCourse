#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;

	direction = glm::vec3(0.f, -1.f, 0.f);
	diffuseIntensity = 0.f;
}

Light::Light(
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat dIntensity)
{
	color = glm::vec3(red, green, blue);
	this->ambientIntensity = ambientIntensity;
	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

void Light::UseLight(
	GLfloat ambientIntensityLocation, 
	GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation,
	GLfloat directionLocation
	)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

Light::~Light()
{
}
