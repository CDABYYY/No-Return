// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo0GameMode.h"
#include "Demo0Character.h"
#include "UObject/ConstructorHelpers.h"

ADemo0GameMode::ADemo0GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
