// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UStaticMeshComponent* ShellMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	float ShellScale = 1.f;
};


UCLASS(BlueprintType)
class LUDUMDARE54_API AHermitShellActor : public AActor
{
	GENERATED_BODY()

public:
	AHermitShellActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitShell)
	UHermitShell* Shell;
};
