// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLFPSGameMode.h"
#include "RLFPSHUD.h"
#include "RLFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARLFPSGameMode::ARLFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/DefaultContent/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARLFPSHUD::StaticClass();
}
