// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Gameplay/HermitStateChangedInterface.h"

#include "HermitPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShellDropTight);


UCLASS()
class LUDUMDARE54_API AHermitPlayer : public ACharacter, public IHermitStateChangedInterface
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SpawnShellAction;

public:
	// Sets default values for this character's properties
	AHermitPlayer();

	void PickShell(class AHermitShellActor* Shell);
	void DropShell();

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
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

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Interact(const FInputActionValue& Value);
	void SpawnShell(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ResetCharacter();

private:
	FVector DesiredDirection;
	FVector CurrentDirection;

public:
	UPROPERTY(BlueprintAssignable, Category = "HermitInput")
	FOnInteractPressed OnInteractPressed;

	UPROPERTY(BlueprintAssignable, Category = "Hermit")
	FOnShellDropTight OnShellDropTight;

	// Crab growth
	// Scale from 1 to x
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HermitProperties)
	double DefaultHermitScale = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HermitProperties)
	double CurrentHermitScale;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	double HermitGrowthRate = 0.1f;


	//Constraints on shell size
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	//float BaseCollisionRadius = 20.f;

	// Crab size
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	float BaseCollisionRadius = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	float BaseInteractRadius = 25.f;

	// Crab Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	float HermitSpeedScale = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HermitProperties)
	float HermitRotationSpeedDegrees = 10.f;

	// Crab time to live
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HermitProperties)
	float TimeLeftToDieWithoutShell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	float DefaultTimeToDieWithoutShell = 8.f;


	// Crab meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	class USkeletalMeshComponent* CrabMesh = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	UClass* ShellActorClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	class UStaticMeshComponent* ShellMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	class UHermitShell* Shell = nullptr;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	float TEMPDistToSpawn = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HermitProperties)
	TSubclassOf<class AHermitShellActor> TEMPShell;
};
