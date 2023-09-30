// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameplayState.generated.h"

/**
 * 
 */
UENUM()
enum EGameplayState : uint8
{
	Start,
	Play,
	End
};
