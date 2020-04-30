#pragma once

class ACamera;

class APlayerController
{
private:

	class AActor *ControlledActor;

	float MovementSpeed = 2.f;

public:

	inline void SetControlledActor(AActor &Actor) { ControlledActor = &Actor; }
	inline AActor* GetControlledActor() const { return ControlledActor; }

	void HandleUserInput(bool* keys, float DeltaTime, const ACamera &Camera);

};

