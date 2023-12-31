// Copyright Epic Games, Inc. All Rights Reserved.

#include "GravityComponentGameMode.h"
#include "GravityComponentHUD.h"
#include "GravityComponentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGravityComponentGameMode::AGravityComponentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGravityComponentHUD::StaticClass();
}
