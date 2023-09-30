// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/HermitCamera.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"

#include "Ludum54GM.h"

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



	EHermitGameplayState StateAtBegin = GameMode->GetGameplayState();

	StateChanged(StateAtBegin, EHermitGameplayState::End);
}

void AHermitCamera::StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState)
{
	// todo: treat OldState to toggle animations

	if (NewState == EHermitGameplayState::MainMenu)
	{
		SetActorTransform(MainMenuTransformTarget->GetTransform());
	}
}
