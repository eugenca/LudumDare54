// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"

#include "Enumerations/GameplayState.h"
#include "Gameplay/HermitStateChangedInterface.h"

#include "HermitCamera.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitCamera : public AActor, public IHermitStateChangedInterface
{
	GENERATED_BODY()

public:
	AHermitCamera();

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//virtual USceneComponent* GetDefaultAttachComponent() const;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HermitCameraParams)
	double DefaultHeightStep = 80.;

protected:

	UPROPERTY(BlueprintReadOnly, Category = HermitCamera)
	FVector TrackedPosition;

	UPROPERTY(BlueprintReadOnly, Category = HermitCamera)
	FQuat CameraRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HermitCamera)
	class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HermitCamera)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HermitCamera)
	class USpringArmComponent* CameraSpring;

private:
	AActor* ActorToFollow = nullptr;
	double CameraHeightRatio;
	double CurrentCameraHeight;

};
