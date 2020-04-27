#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{


public:
	Light();
	Light(
		GLfloat red, GLfloat green, GLfloat blue, 
		GLfloat ambientIntensity, 
		GLfloat xDir, GLfloat yDir, GLfloat zDir, 
		GLfloat dIntensity);
	~Light();

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
		GLfloat diffuseIntensityLocation,
		GLfloat directionLocation);


private:
	glm::vec3 color;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;

};
