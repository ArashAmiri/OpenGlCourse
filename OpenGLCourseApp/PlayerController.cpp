#include "PlayerController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Actor.h"

void APlayerController::HandleUserInput(bool* keys, float DeltaTime)
{
	FVector ActorLocation = ControlledActor->GetTransform().GetLocation();

	if (keys[GLFW_KEY_W])
	{
		FTransform Transform = ControlledActor->GetTransform();
		Transform.Location = ActorLocation + FVector(3.0, 0.f, 0.f);
		ControlledActor->SetTransform(Transform);
	}
	/*
	if (keys[GLFW_KEY_S]) ActorLocation = &(*(ActorLocation) + FVector(0, 1.f * DeltaTime, 0.f));
	if (keys[GLFW_KEY_W]) ActorLocation = &(*(ActorLocation) + FVector(-1.0 * DeltaTime, 0.f, 0.f));
	if (keys[GLFW_KEY_S]) ActorLocation = &(*(ActorLocation) + FVector(0, -1.f * DeltaTime, 0.f));
	*/
}
