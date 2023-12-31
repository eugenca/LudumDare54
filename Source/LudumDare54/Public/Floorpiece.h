// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/ShellActor.h"
#include "Floorpiece.generated.h"

class UBoxComponent;

UCLASS()
class LUDUMDARE54_API AFloorpiece : public AActor
{
	GENERATED_BODY()

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Setup, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(Category = Setup, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 PickupCount = 10;

	UPROPERTY(Category = Setup, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AHermitShellActor> BaseObject;

public:	
	// Sets default values for this actor's properties
	AFloorpiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	TArray<AHermitShellActor*> Pickups;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloorPiece)
	float MeshSizeX = 3500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloorPiece)
	float MeshSizeY = 3500;

	void MoveFloorpiece(FVector NewLocation);

};
