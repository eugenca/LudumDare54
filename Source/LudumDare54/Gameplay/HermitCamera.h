// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"

#include "HermitCamera.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitCamera : public ACameraActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
