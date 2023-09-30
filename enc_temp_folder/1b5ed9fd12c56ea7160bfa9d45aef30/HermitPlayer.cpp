// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HermitPlayer.h"

// Sets default values
AHermitPlayer::AHermitPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHermitPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHermitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHermitPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

