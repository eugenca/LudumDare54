// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShellActor.generated.h"

UCLASS()
class LUDUMDARE54_API AShellActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShellActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
