// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enumerations/GameplayState.h"
#include "Ludum54GM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayStateChangedSignature, EGameplayState, NewState, EGameplayState, OldState);

/**
 * 
 */
UCLASS()
class LUDUMDARE54_API ALudum54GM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EGameplayState> State;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayStateChangedSignature OnGameplayStateChangedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
	void SetGameplayState(EGameplayState NewState);
};
