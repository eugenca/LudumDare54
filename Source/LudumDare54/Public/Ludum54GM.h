// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enumerations/GameplayState.h"
#include "Ludum54GM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayStateChangedSignature, EHermitGameplayState, NewState, EHermitGameplayState, OldState);

/**
 * 
 */
UCLASS()
class LUDUMDARE54_API ALudum54GM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EHermitGameplayState> State = EHermitGameplayState::MainMenu;

public:

	virtual void StartPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
	void SetGameplayState(EHermitGameplayState NewState);

	UFUNCTION(BlueprintPure, Category = "Input Mode")
	EHermitGameplayState GetGameplayState() { return State.GetValue(); };

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayStateChangedSignature OnGameplayStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hermit)
	TSubclassOf<class AHermitMapController> MapControllerClass;

	UPROPERTY(BlueprintReadOnly, Category = Hermit)
	class AHermitMapController* MapController;
};
