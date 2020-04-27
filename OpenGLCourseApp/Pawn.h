#pragma once
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

#include "Actor.h"
#include "Camera.h"

class APawn : AActor
{

	ACamera* Camera;
	APawn(ACamera* CameraToSet, AMesh* MeshToSet);
	~APawn();

public:

	virtual void HandleUserInput(bool* keys, float DeltaTime) override;
	
};

