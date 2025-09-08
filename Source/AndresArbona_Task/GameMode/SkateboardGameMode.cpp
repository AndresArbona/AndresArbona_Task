// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GameMode/SkateboardGameMode.h"

#include "AndresArbona_Task/PlayerCharacter/PlayerCharacter.h"
#include "AndresArbona_Task/Controller/MainPlayerController.h"

ASkateboardGameMode::ASkateboardGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}
