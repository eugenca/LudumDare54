// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ShellActor.h"
#include "LudumDare54.h"

#include "Components/SphereComponent.h"

#include "Characters/HermitPlayer.h"


// Sets default values
AHermitShellActor::AHermitShellActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Shell Collision"));
	CollisionSphere->SetupAttachment(RootComponent);

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shell Mesh1"));
	ShellMesh->SetupAttachment(CollisionSphere);

}

// Called when the game starts or when spawned
void AHermitShellActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHermitShellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHermitShellActor::Interact(AActor* InInstigator)
{
	AHermitPlayer* Character = Cast<AHermitPlayer>(InInstigator);
	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitShellActor::Interact: Failed to cast to Character!"));
		return;
	}

	Character->EquipShell(Shell);
}

void AHermitShellActor::InteractBP_Implementation(AActor* InInstigator)
{
	Interact(InInstigator);
}
