// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorpieceQueue.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"

#include "Floorpiece.h"
#include "Gameplay/HermitMapController.h"

UE_DISABLE_OPTIMIZATION

void AFloorpieceQueue::InitializeQueue()
{
	// Make it odd
	QueueLength += (QueueLength + 1) % 2;

	UWorld* MyLevel = GetWorld();

	if (!IsValid(BaseObject) || !IsValid(MyLevel))
	{
		UE_LOG(LogHermit, Error, TEXT("AFloorpieceQueue::InitializeQueue: BaseObject or World is not valid!"));
		return;
	}

	for (int32 i = 0; i < QueueLength; ++i)
	{
		AFloorpiece* SpawnedActor = MyLevel->SpawnActor<AFloorpiece>(BaseObject, FTransform());
		Queue.EmplaceLast(SpawnedActor);
	}

	RebuildAroundPosition(0.f);

	//
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

	
	GetMapController();
	InitializeQueue();

	CheckPlayerPosition(MapController->CurrentPosition);

	//for (int i = 0; i < QueueLength; ++i)
	//{
	//	if (AFloorpiece* Floorpiece = Spawn(i))
	//	{
	//		Queue.Enqueue(Floorpiece);
	//	}
	//}

	//GetWorldTimerManager().SetTimer(CountdownHandle, this, &AFloorpieceQueue::TimerTick, TimerDelay, true, 0.0);
}

void AFloorpieceQueue::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//UWorld* MyLevel = GetWorld();

	//if (!IsValid(MyLevel))
	//	return;

	//AFloorpiece* Piece;
	//while (Queue.Dequeue(Piece))
	//{
	//	MyLevel->DestroyActor(Piece);
	//}
}

void AFloorpieceQueue::StateChanged_MainMenu()
{
}

void AFloorpieceQueue::StateChanged_PlayingCharacter()
{
}

void AFloorpieceQueue::StateChanged_EndGameSequence()
{
}

void AFloorpieceQueue::StateChanged_ScoreTable()
{
}

void AFloorpieceQueue::GetMapController()
{
	if (!MapController)
	{
		if (ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this)))
		{
			MapController = GameMode->MapController;
		}
		if (!MapController)
		{
			UE_LOG(LogHermit, Error, TEXT("AFloorpieceQueue::Tick: Failed to get MapController!"));
		}
	}
	check(MapController);
}

int32 AFloorpieceQueue::YCoordToIndex(float YCoord)
{
	if (AFloorpiece* CDO = BaseObject.GetDefaultObject())
	{
		return FMath::RoundToInt32(YCoord / CDO->MeshSizeY);
	}
	UE_LOG(LogHermit, Error, TEXT("AFloorpieceQueue::YCoordToIndex: BaseObject not set!"));
	return -1;
}

float AFloorpieceQueue::IndexToYCoord(int32 Index)
{
	if (AFloorpiece* CDO = BaseObject.GetDefaultObject())
	{
		return CDO->MeshSizeY * Index;
	}
	UE_LOG(LogHermit, Error, TEXT("AFloorpieceQueue::IndexToYCoord: BaseObject not set!"));
	return -1.f;
}

void AFloorpieceQueue::CheckPlayerPosition(double PlayerY)
{

	const int32 PlayerTileIndex = YCoordToIndex(PlayerY);
	const int32 TileDiff = PlayerTileIndex - QueueMiddleTileIndex;

	
	if (FMath::Abs(TileDiff) == 0)
	{
		// We are at the same place, don't do anything
		return;
	}
	else if (FMath::Abs(TileDiff) > 1)
	{
		// We are too far away, rebuild tiles around
		RebuildAroundPosition(PlayerY);
		return;
	}
	else
	{
		// We are on next tile, move one tile in TileDiff direction
		MoveInDirection(TileDiff);
	}
}

void AFloorpieceQueue::MoveInDirection(int32 Direction)
{
	check(FMath::Abs(Direction) == 1);

	const int32 FirstIndex = QueueMiddleTileIndex - QueueLength / 2;
	const int32 LastIndex = QueueMiddleTileIndex + QueueLength / 2;

	if (Direction > 0)
	{
		// Take low (first), put high (last)
		AFloorpiece* ActorToMove = Queue.First();
		Queue.PopFirst();
		ActorToMove->SetActorLocation(FVector(MapController->HorizontalSize / 2., IndexToYCoord(LastIndex + 1), 0.));
		Queue.EmplaceLast(ActorToMove);
	}
	else
	{
		// Take high (last), put low (first)
		AFloorpiece* ActorToMove = Queue.Last();
		Queue.PopLast();
		ActorToMove->SetActorLocation(FVector(MapController->HorizontalSize / 2., IndexToYCoord(FirstIndex - 1), 0.));
		Queue.EmplaceFirst(ActorToMove);
	}

	QueueMiddleTileIndex += Direction;
}

void AFloorpieceQueue::RebuildAroundPosition(double PlayerY)
{
	QueueMiddleTileIndex = YCoordToIndex(PlayerY);

	TArray<AFloorpiece*> TempArray;
	
	while (!Queue.IsEmpty())
	{
		AFloorpiece* TempElement = Queue.Last();
		Queue.PopLast();
		TempArray.Add(TempElement);
	}

	for (int32 i = QueueMiddleTileIndex - QueueLength / 2; i <= QueueMiddleTileIndex + QueueLength / 2; ++i)
	{
		AFloorpiece* Floorpiece = TempArray.Pop(false);
		Floorpiece->SetActorLocation(FVector(MapController->HorizontalSize / 2., IndexToYCoord(i), 0.));
		Queue.EmplaceLast(Floorpiece);
	}

}

// Called every frame
void AFloorpieceQueue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPlayerPosition(MapController->CurrentPosition);
}

void AFloorpieceQueue::TimerTick()
{
	//AFloorpiece* ActorToMove;
	//Queue.Dequeue(ActorToMove);

	//OnFloorpieceMoved.Broadcast(ActorToMove);
	//ActorToMove->MoveFloorpiece({ 0,  QueueLength * ActorToMove->MeshSizeY,0 });
	//Queue.Enqueue(ActorToMove);
}

UE_ENABLE_OPTIMIZATION
