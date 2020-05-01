#pragma once

class APlayerController;


class UGameplayStatics
{
public:
	
	static APlayerController* PlayerController;
	
	static void SetPlayerController(APlayerController* PlayerControllerToSet) { PlayerController = PlayerControllerToSet; }

	static APlayerController* GetPlayerController() { return PlayerController; }
};

