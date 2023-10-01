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
	void TimerTick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	TSubclassOf<AFloorpiece> BaseObject;

	TQueue<AFloorpiece*, EQueueMode::Mpsc>* Queue = new TQueue<AFloorpiece*, EQueueMode::Mpsc>;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	int32 QueueLength = 5;

	FTimerHandle CountdownHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float PresentXLocation = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
