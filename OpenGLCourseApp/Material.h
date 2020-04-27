#pragma once

#include <GL\glew.h>


class AMaterial
{
public:
	AMaterial();
	AMaterial(GLfloat SpecularIntensity, GLfloat Shininess);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shiniessLocation);

	~AMaterial();

private:
	GLfloat SpecularIntensity;
	GLfloat Shininess;

};

