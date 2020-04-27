#include "Pawn.h"
#include "Mesh.h"

APawn::APawn(ACamera* CameraToSet, AMesh* MeshToSet) : Camera(CameraToSet), AActor(MeshToSet) {};

void APawn::HandleUserInput(bool* keys, GLfloat DeltaTime)
{
	/*
	if (keys[GLFW_KEY_W]) Transform.Location += Camera->GetFront() * Speed * DeltaTime;
	if (keys[GLFW_KEY_S]) Transform.Location -= Camera->GetFront() * Speed * DeltaTime;

	if (keys[GLFW_KEY_D]) Transform.Location += Camera->GetRight() * Speed * DeltaTime;
	if (keys[GLFW_KEY_A]) Transform.Location -= Camera->GetRight() * Speed * DeltaTime;

	if (keys[GLFW_KEY_Q]) Transform.Location += Camera->GetUp() * Speed * DeltaTime;
	if (keys[GLFW_KEY_E]) Transform.Location -= Camera->GetUp() * Speed * DeltaTime;
	*/
}

APawn::~APawn()
{
}
