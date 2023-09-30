// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameplayState.generated.h"

/**
 * Possible Game States
 */
UENUM()
enum EHermitGameplayState : uint8
{
	MainMenu,
	PlayingCharacter,
	EndGameSequence,
	ScoreTable,

	End
};
