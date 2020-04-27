#pragma once

#include <glm/glm.hpp>

typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef float GLfloat;


class ACamera
{

public:

	ACamera();

	ACamera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	
	inline glm::vec3 GetPosition() { return Position; }
	inline glm::vec3 GetFront() { return Front; }
	inline glm::vec3 GetRight() { return Right; }
	inline glm::vec3 GetUp() { return Up; }
	
	void KeyControl(bool* keys, GLfloat DeltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
	
	glm::mat4 CalculateViewMatrix();

	~ACamera();



private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;
	GLfloat TurnSpeed;

	void Update();



};

