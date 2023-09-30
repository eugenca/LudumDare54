// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Enumerations/GameplayState.h"

#include "HermitCamera.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitCamera : public ACameraActor
{
	GENERATED_BODY()

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	void StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatePlacement)
	AActor* MainMenuTransformTarget;


};
