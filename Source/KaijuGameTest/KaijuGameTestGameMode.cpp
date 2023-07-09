// Copyright Epic Games, Inc. All Rights Reserved.

#include "KaijuGameTestGameMode.h"
#include "KaijuGameTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKaijuGameTestGameMode::AKaijuGameTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
