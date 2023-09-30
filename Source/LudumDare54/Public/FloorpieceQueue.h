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

	AFloorpiece* Spawn();
	
public:	
	// Sets default values for this actor's properties
	AFloorpieceQueue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	TSubclassOf<AFloorpiece> BaseObject;

	TQueue<AFloorpiece*, EQueueMode::Spsc>* Queue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	int32 QueueLength = 5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
