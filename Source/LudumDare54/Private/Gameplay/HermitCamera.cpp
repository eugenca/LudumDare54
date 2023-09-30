// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/HermitCamera.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "Ludum54GM.h"
#include "HermitPlayerController.h"

AHermitCamera::AHermitCamera()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHermitCamera::BeginPlay()
{
	Super::BeginPlay();

	if (!MainMenuTransformTarget)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera: No Transform Target provided!"));
		return;
	}

	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera: Failed to get gamemode!"));
		return;
	}

	// Subscribe to state change event and initialize initial state
	InitializeStateChange(this, GameMode);
}

void AHermitCamera::Tick(float DeltaSeconds)
{
	if (!GetIsPlayingCharacter())
	{
		return;
	}


}

/*
void AHermitCamera::StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState)
{
	switch (NewState)
	{
	case MainMenu:
		SetActorTransform(MainMenuTransformTarget->GetTransform());
		break;
	case PlayingCharacter:
		SetupPlaying();
		break;
	case EndGameSequence:
		// todo: change this
		SetActorTransform(MainMenuTransformTarget->GetTransform());
		break;
	case ScoreTable:
		// todo: change this
		SetActorTransform(MainMenuTransformTarget->GetTransform());
		break;
	case End:
	default:
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::StateChanged Invalid NewState!"));
		break;
	}

}
*/

void AHermitCamera::StateChanged_MainMenu()
{
	SetActorTransform(MainMenuTransformTarget->GetTransform());
}

void AHermitCamera::StateChanged_PlayingCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (!PlayerController)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::StateChanged_PlayingCharacter: Failed to get correct PlayerController!"));
		return;
	}

	ACharacter* Character = PlayerController->GetCharacter();

	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::StateChanged_PlayingCharacter: Failed to get correct Character!"));
		return;
	}

	ActorToFollow = Character;
}

void AHermitCamera::StateChanged_EndGameSequence()
{
	SetActorTransform(MainMenuTransformTarget->GetTransform());
}

void AHermitCamera::StateChanged_ScoreTable()
{
	SetActorTransform(MainMenuTransformTarget->GetTransform());
}
