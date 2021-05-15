// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerProjectGameMode.h"
#include "PlatformerProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformerProjectGameMode::APlatformerProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
