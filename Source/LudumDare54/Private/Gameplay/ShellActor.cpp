// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ShellActor.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

#include "Characters/HermitPlayer.h"


// Sets default values
AHermitShellActor::AHermitShellActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Shell Collision"));
	CollisionCapsule->SetupAttachment(RootComponent);

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shell Mesh1"));
	ShellMesh->SetupAttachment(CollisionCapsule);


	Shell = CreateDefaultSubobject<UHermitShell>(TEXT("Shell Object"));

}

// Called when the game starts or when spawned
void AHermitShellActor::BeginPlay()
{
	Super::BeginPlay();

	Shell->ShellMesh = ShellMesh;

	auto* Character = Cast<AHermitPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Character)
	{
		SetActorScale3D(FVector(0.2));
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::Tick: Failed to get Character!"));
		return;
	}

	Shell->ShellScale = FMath::RandRange(1., FMath::Max(9., Character->CurrentHermitScale * 1.15));
	SetActorScale3D(FVector(Shell->ShellScale));
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

	Character->PickShell(this);
}

void AHermitShellActor::InteractBP_Implementation(AActor* InInstigator)
{
	Interact(InInstigator);
}

bool AHermitShellActor::IsPickableByPlayer(AActor* InInstigator)
{

	AHermitPlayer* Character = Cast<AHermitPlayer>(InInstigator);
	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitShellActor::IsPickableByPlayer: Failed to cast to Character!"));
		return false;
	}

	FVector2D MinMax = Shell->GetMinMaxCrabScale();

	double Min = MinMax.X;
	double Max = MinMax.Y;

	const double CrabScale = Character->CurrentHermitScale;
	if (CrabScale > Min && CrabScale < Max)
	{
		return true;
	}
	return false;
}

FVector2D UHermitShell::GetMinMaxCrabScale()
{
	double Min1 = 0.78;
	double Max1 = 1.15;

	double Min2 = 0.86;
	double Max2 = 1.17;

	FVector2D Result;
	if (ShellSocketName == FName("TailSocket1"))
	{
		Result.X = Min1; Result.Y = Max1;
	}
	else if (ShellSocketName == FName("TailSocket2"))
	{
		Result.X = Min2; Result.Y = Max2;
	}
	else
	{
		UE_LOG(LogHermit, Error, TEXT("UHermitShell::GetMinMaxCrabScale: Incorrect Shell Socket Name!"));
		return FVector2D(1., 1.);
	}


	return Result * ShellScale;
}
