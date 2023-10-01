// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Gameplay/HermitInteractInterface.h"

#include "ShellActor.generated.h"

UCLASS()
class LUDUMDARE54_API UHermitShell: public UObject
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	UStaticMesh* ShellMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	float ShellScale = 1.f;
};


UCLASS(BlueprintType)
class LUDUMDARE54_API AHermitShellActor: public AActor, public IHermitInteractInterface
{
	GENERATED_BODY()

public:
	AHermitShellActor();

	// Begin AActor Interface
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// End AActor Interface

	// Begin IHermitInteractInterface Interface
public:
	virtual void Interact(AActor* Instigator) override;
	virtual void InteractBP_Implementation(AActor* Instigator) override;
	// End IHermitInteractInterface Interface


public:

	// Shell size
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitShell)
	float BaseCollisionRadius = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitShell)
	float BaseInteractRadius = 25.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	class USphereComponent* CollisionSphere;

	// Shell mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	class UStaticMeshComponent* ShellMesh = nullptr;

	// Shell object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	UHermitShell* Shell;
};
