// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Containers/Deque.h"
#include "Gameplay/HermitStateChangedInterface.h"
#include "FloorpieceQueue.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloorpieceMoved, AFloorpiece*, Floorpiece);

UCLASS()
class LUDUMDARE54_API AFloorpieceQueue : public AInfo, public IHermitStateChangedInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFloorpieceQueue();

	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Begin IHermitStateChangedInterface Interface
public:
	UFUNCTION()
	virtual void StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState) override { StateChangedImplementation(NewState, OldState); }

protected:
	virtual void StateChanged_MainMenu() override;
	virtual void StateChanged_PlayingCharacter() override;
	virtual void StateChanged_EndGameSequence() override;
	virtual void StateChanged_ScoreTable() override;
	// End IHermitStateChangedInterface Interface

private:
	void InitializeQueue();

	void GetMapController();

	int32 YCoordToIndex(float YCoord);
	float IndexToYCoord(int32 Index);

	void CheckPlayerPosition(double PlayerY);
	void MoveInDirection(int32 Direction);
	void RebuildAroundPosition(double PlayerY);

private:
	int32 QueueMiddleTileIndex;

public:

	UPROPERTY(BlueprintAssignable)
	FOnFloorpieceMoved OnFloorpieceMoved;

	// - Queue

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Queue")
	TSubclassOf<class AFloorpiece> BaseObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Queue")
	int32 QueueLength = 5;

	TDeque<class AFloorpiece*> Queue;

	// - Timer

	void TimerTick();

	FTimerHandle CountdownHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimerDelay = 1;

private:
	class AHermitMapController* MapController = nullptr;
};
