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

		OnFloorpieceMoved.Broadcast(SpawnedActor);
		SpawnedActor->MoveFloorpiece({ 0, indexMult * SpawnedActor->MeshBoundsY,0 });
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
}

void AFloorpieceQueue::StateChanged_MainMenu()
{
	IHermitStateChangedInterface::StateChanged_MainMenu();
}

void AFloorpieceQueue::StateChanged_PlayingCharacter()
{
	IHermitStateChangedInterface::StateChanged_PlayingCharacter();
	GetWorldTimerManager().SetTimer(CountdownHandle, this, &AFloorpieceQueue::TimerTick, TimerDelay, true, 0.0);
}

void AFloorpieceQueue::StateChanged_EndGameSequence()
{
	IHermitStateChangedInterface::StateChanged_EndGameSequence();
}

void AFloorpieceQueue::StateChanged_ScoreTable()
{
	IHermitStateChangedInterface::StateChanged_ScoreTable();
}

// Called every frame
void AFloorpieceQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorpieceQueue::TimerTick()
{
	AFloorpiece* ActorToMove;
	Queue->Dequeue(ActorToMove);

	OnFloorpieceMoved.Broadcast(ActorToMove);
	ActorToMove->MoveFloorpiece({ 0,  QueueLength * ActorToMove->MeshBoundsY,0 });
	Queue->Enqueue(ActorToMove);
}