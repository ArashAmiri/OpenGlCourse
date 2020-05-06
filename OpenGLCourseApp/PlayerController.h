#pragma once

class ACamera;

class APlayerController
{
private:

	const class AActor *ControlledActor;

	float MovementSpeed = 1000.f;

public:

	inline void SetControlledActor(const AActor &Actor) { ControlledActor = &Actor; }
	inline const AActor* GetControlledActor() const { return ControlledActor; }

	void HandleUserInput(bool* keys, float DeltaTime, const ACamera &Camera);

};

