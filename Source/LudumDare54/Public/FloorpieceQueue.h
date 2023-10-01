// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "Floorpiece.h"
#include "FloorpieceQueue.generated.h"

UCLASS()
class LUDUMDARE54_API AFloorpieceQueue : public AActor
{
	GENERATED_BODY()

	AFloorpiece* Spawn(float indexMult);
	
public:	
	// Sets default values for this actor's properties
	AFloorpieceQueue();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// - Queue

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Queue")
		TSubclassOf<AFloorpiece> BaseObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Queue")
		int32 QueueLength = 5;

	TQueue<AFloorpiece*, EQueueMode::Mpsc>* Queue = new TQueue<AFloorpiece*, EQueueMode::Mpsc>;

	// - Timer

	void TimerTick();

	FTimerHandle CountdownHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimerDelay = 1;
};
