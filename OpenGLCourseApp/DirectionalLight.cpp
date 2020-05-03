#include "DirectionalLight.h"

ADirectionalLight::ADirectionalLight()
	: ALight()
	, Direction(glm::vec3(0.0f, -1.0f, 0.0f)) {}

ADirectionalLight::ADirectionalLight(
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat AmbientIntensityToSet,
	GLfloat DIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir
	)
	: ALight(red, green, blue, AmbientIntensityToSet, DIntensity)
	, Direction(glm::vec3(xDir, yDir, zDir))
{}

void ADirectionalLight::UseLight(
	GLuint ambientIntensityLocation,
	GLuint ambientColorLocation,
	GLuint diffuseIntensityLocation,
	GLuint directionLocation
)
{
	ALight::UseLight(ambientIntensityLocation, ambientColorLocation, diffuseIntensityLocation);
	glUniform3f(directionLocation, Direction.x, Direction.y, Direction.z);
}

ADirectionalLight::~ADirectionalLight()
{
}
