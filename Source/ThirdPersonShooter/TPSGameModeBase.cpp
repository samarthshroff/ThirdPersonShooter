// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

#include "TPSPlayerController.h"

ATPSGameModeBase::ATPSGameModeBase() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/Blueprints/BP_TPSCharacter"));
	DefaultPawnClass = PlayerPawnFinder.Class;
	
	PlayerControllerClass = ATPSPlayerController::StaticClass();
}
