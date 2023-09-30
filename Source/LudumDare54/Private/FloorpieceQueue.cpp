// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorpieceQueue.h"

AFloorpiece* AFloorpieceQueue::Spawn()
{
	UWorld* MyLevel = GetWorld();

	if (!IsValid(BaseObject) || !IsValid(MyLevel))
	{
		return nullptr;
	}

	// You can determine the spawned Actor's initial location, rotation and scale.
		// Here we're just setting it to the spawner's transform.
		// NOTE: depending on your Actor settings, this could prevent spawning if the location is obstructed!
	FTransform SpawnTransform = GetActorTransform();

	AFloorpiece* SpawnedActor = MyLevel->SpawnActor<AFloorpiece>(BaseObject, SpawnTransform);
	if (IsValid(SpawnedActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Spawned successfully! New Actor: %s"), *SpawnedActor->GetName());
	}

	return SpawnedActor;
}

// Sets default values
AFloorpieceQueue::AFloorpieceQueue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFloorpieceQueue::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < QueueLength; ++i)
	{
		Spawn();
	}
}

// Called every frame
void AFloorpieceQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

