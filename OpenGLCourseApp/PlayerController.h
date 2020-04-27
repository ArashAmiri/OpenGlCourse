#pragma once
class APlayerController
{
private:

	class AActor* ControlledActor;

public:

	inline void SetControlledActor(AActor* Actor) { ControlledActor = Actor; }

	void HandleUserInput(bool* keys, float DeltaTime);

};

