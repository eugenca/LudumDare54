// Fill out your copyright notice in the Description page of Project Settings.


#include "Ludum54GM.h"
#include "LudumDare54.h"

#include "Gameplay/HermitMapController.h"

void ALudum54GM::StartPlay()
{
	UE_LOG(LogHermit, Warning, TEXT("ALudum54GM::StartPlay"));
	// Spawn before StartPlay to call BeginPlay of a spawned actor
	MapController = Cast<AHermitMapController>(GetWorld()->SpawnActor(MapControllerClass));
	check(MapController);

	Super::StartPlay();
	
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.Owner = this;
	
}

void ALudum54GM::SetGameplayState(EHermitGameplayState NewState)
{
	EHermitGameplayState OldState = State;
	State = NewState;

	OnGameplayStateChanged.Broadcast(State, OldState);
}
