// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI_LessonGameMode.h"
#include "UI_LessonHUD.h"
#include "UI_LessonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUI_LessonGameMode::AUI_LessonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUI_LessonHUD::StaticClass();
}
