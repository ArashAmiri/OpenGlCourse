#include "Transform.h"

FTransform::FTransform()
{
	this->Location = FVector(1.0f);
	//Rotation = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);
	this->Scale = FVector(1.0f);
}
