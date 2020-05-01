#include "Camera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "PlayerController.h"
#include "OpenGLCourseApp.h"
#include "Actor.h"

ACamera::ACamera()
{
}

ACamera::ACamera(
	glm::vec3 startPosition,
	glm::vec3 startUp,
	GLfloat startYaw,
	GLfloat startPitch,
	GLfloat startMoveSpeed,
	GLfloat startTurnSpeed)
	: Position(startPosition)
	, WorldUp(startUp)
	, Yaw(startYaw)
	, Pitch(startPitch)
	, MovementSpeed(startMoveSpeed)
	, TurnSpeed(startTurnSpeed)
{
	Front = glm::vec3(0.f, 0.f, -1.f);
	Update();

}

void ACamera::KeyControl(bool* keys, GLfloat DeltaTime)
{
	/*
	if (keys[GLFW_KEY_W]) Position += Front * MovementSpeed * DeltaTime;
	if (keys[GLFW_KEY_S]) Position -= Front * MovementSpeed * DeltaTime;

	if (keys[GLFW_KEY_D]) Position += Right * MovementSpeed * DeltaTime;
	if (keys[GLFW_KEY_A]) Position -= Right * MovementSpeed * DeltaTime;

	if (keys[GLFW_KEY_Q]) Position += Up * MovementSpeed * DeltaTime;
	if (keys[GLFW_KEY_E]) Position -= Up * MovementSpeed * DeltaTime;
	*/	
}

void ACamera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= TurnSpeed;
	yChange *= TurnSpeed;

	Yaw += xChange;
	Pitch += yChange;

	if (Pitch > 89.f) Pitch = 89.f;
	if (Pitch < -89.f) Pitch = -89.f;

	Update();
}

glm::mat4 ACamera::CalculateViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}



ACamera::~ACamera()
{
}

void ACamera::Update()
{
	Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front.y = sin(glm::radians(Pitch));
	Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(Front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));


	APlayerController* GlobalPlayerController = GetGlobalPlayerController();
	if (GlobalPlayerController)
	{
		auto Player = GlobalPlayerController->GetControlledActor();
		if (Player)
		{
			Position = Player->GetPosition() - (Front * 6.f);
		}
	}
}


