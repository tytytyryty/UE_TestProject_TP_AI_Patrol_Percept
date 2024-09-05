// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_AI_patrol_perceptGameMode.h"
#include "TP_AI_patrol_perceptCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATP_AI_patrol_perceptGameMode::ATP_AI_patrol_perceptGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
