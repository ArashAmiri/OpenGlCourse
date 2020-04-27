#include "Material.h"

AMaterial::AMaterial()
{
	SpecularIntensity = Shininess = 0;
}

AMaterial::AMaterial(GLfloat SpecularIntensity, GLfloat Shininess)
{
	this->SpecularIntensity = SpecularIntensity;
	this->Shininess = Shininess;
}

void AMaterial::UseMaterial(GLuint specularIntensityLocation, GLuint shiniessLocation)
{
	glUniform1f(specularIntensityLocation, SpecularIntensity);
	glUniform1f(shiniessLocation, Shininess);
	
}

AMaterial::~AMaterial()
{
}
