// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"

#include "Enumerations/GameplayState.h"
#include "Gameplay/HermitStateChangedInterface.h"

#include "HermitCamera.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitCamera : public ACameraActor, public IHermitStateChangedInterface
{
	GENERATED_BODY()

public:
	AHermitCamera();

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// End AActor Interface

	// Begin IHermitStateChangedInterface Interface
public:
	UFUNCTION() virtual void StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState) override { StateChangedImplementation(NewState, OldState); }
protected:
	virtual void StateChanged_MainMenu() override;
    virtual void StateChanged_PlayingCharacter() override;
    virtual void StateChanged_EndGameSequence() override;
    virtual void StateChanged_ScoreTable() override;
	// End IHermitStateChangedInterface Interface

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HermitCameraParams)
	AActor* MainMenuTransformTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HermitCameraParams)
	double DefaultCameraHeight = 300.;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HermitCameraParams)
	//double CameraViewBoxXAdditionToIncreaseHeight = 50.;

private:
	double CameraHeightRatio;
	double CurrentCameraHeight;

private:
	AActor* ActorToFollow = nullptr;

};
