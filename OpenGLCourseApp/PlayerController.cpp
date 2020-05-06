#include "PlayerController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Actor.h"
#include "Camera.h"

void APlayerController::HandleUserInput(bool* keys, float DeltaTime, const ACamera& Camera)
{

	glm::vec3 UpdateFactor = glm::vec3(0.f);

	if (keys[GLFW_KEY_W]) UpdateFactor = Camera.GetFront();
	if (keys[GLFW_KEY_S]) UpdateFactor = -Camera.GetFront();
	if (keys[GLFW_KEY_D]) UpdateFactor = Camera.GetRight();
	if (keys[GLFW_KEY_A]) UpdateFactor = -Camera.GetRight();
	if (keys[GLFW_KEY_Q]) UpdateFactor = Camera.GetUp();
	if (keys[GLFW_KEY_E]) UpdateFactor = -Camera.GetUp();

	ControlledActor->Position = ControlledActor->GetPosition() + (UpdateFactor * MovementSpeed * DeltaTime);
	ControlledActor->RotationVector = -Camera.GetRight();
}
