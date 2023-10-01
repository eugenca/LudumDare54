// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorpieceQueue.h"

AFloorpiece* AFloorpieceQueue::Spawn(float indexMult)
{
	UWorld* MyLevel = GetWorld();

	if (!IsValid(BaseObject) || !IsValid(MyLevel)) return nullptr;

	FTransform SpawnTransform = GetActorTransform();

	AFloorpiece* SpawnedActor = MyLevel->SpawnActor<AFloorpiece>(BaseObject, SpawnTransform);
	if (IsValid(SpawnedActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Spawned successfully! New Actor: %s"), *SpawnedActor->GetName());
		SpawnedActor->AddActorWorldOffset({ indexMult * SpawnedActor->MeshBoundsX, 0,0 });
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
		if (AFloorpiece* Floorpiece = Spawn(i)) Queue->Enqueue(Floorpiece);
	}

	GetWorldTimerManager().SetTimer(CountdownHandle, this, &AFloorpieceQueue::TimerTick, TimerDelay, true, 0.0);
}

// Called every frame
void AFloorpieceQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorpieceQueue::TimerTick()
{
	AFloorpiece* SpawnedActor;
	Queue->Dequeue(SpawnedActor);

	SpawnedActor->AddActorWorldOffset({ QueueLength * SpawnedActor->MeshBoundsX, 0,0 });
	Queue->Enqueue(SpawnedActor);
}