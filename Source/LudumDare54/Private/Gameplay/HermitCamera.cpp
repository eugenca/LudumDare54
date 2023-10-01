// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/HermitCamera.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Ludum54GM.h"
#include "Gameplay/HermitMapController.h"
#include "Characters/HermitPlayer.h"

AHermitCamera::AHermitCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// Make the scene component the root component
	RootComponent = SceneComponent;

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(SceneComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->FieldOfView = 90.0f;
	Camera->bConstrainAspectRatio = true;
	Camera->AspectRatio = 1.777778f;
	Camera->PostProcessBlendWeight = 1.0f;

	Camera->SetupAttachment(CameraSpring, USpringArmComponent::SocketName);

	CurrentCameraHeight = DefaultCameraHeight;
}

void AHermitCamera::BeginPlay()
{
	// If we find a matching PC, bind to it immediately.
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->SetViewTarget(this);
	}

	Super::BeginPlay();

	if (!MainMenuTransformTarget)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::BeginPlay: No Transform Target provided!"));
		return;
	}

	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::BeginPlay: Failed to get gamemode!"));
		return;
	}

	// Subscribe to state change event and initialize initial state
	InitializeStateChange(this, GameMode);

	//UCameraComponent* Camera = GetCameraComponent();
	CurrentCameraHeight = DefaultCameraHeight;
	CameraHeightRatio = 1. / FMath::Tan(FMath::DegreesToRadians(Camera->FieldOfView * 0.5));
}

void AHermitCamera::Tick(float DeltaSeconds)
{
	if (!GetIsPlayingCharacter())
	{
		return;
	}

	check(ActorToFollow);
	

	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::Tick: Failed to get gamemode!"));
		return;
	}

	AHermitMapController* MapController = GameMode->MapController;

	if (!MapController)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::Tick: Failed to get MapController!"));
		return;
	}

	auto* Character = Cast<AHermitPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::Tick: Failed to get Character!"));
		return;
	}

	//UCameraComponent* Camera = GetCameraComponent();

	const double CharacterConstrainRadius = Character->BaseInteractRadius * Character->CurrentHermitScale;

	const double HalfSizeX = MapController->CameraViewBox.GetSize().X * 0.5 + CharacterConstrainRadius;
	
	CurrentCameraHeight = HalfSizeX * CameraHeightRatio;

	//TrackedPosition = MapController->CameraViewBox.GetCenter() + FVector(0., 0., CurrentCameraHeight);

	FTransform Transform = GetActorTransform();
	Transform.SetLocation(MapController->CameraViewBox.GetCenter() + FVector(0., 0., CurrentCameraHeight));
	SetActorTransform(Transform);
}

//USceneComponent* AHermitCamera::GetDefaultAttachComponent() const
//{
//	return Camera;
//}

void AHermitCamera::StateChanged_MainMenu()
{
	SetActorTransform(MainMenuTransformTarget->GetTransform());
	//CameraRotation = FQuat();
	SetActorRotation(FQuat());
}

void AHermitCamera::StateChanged_PlayingCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (!PlayerController)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::StateChanged_PlayingCharacter: Failed to get correct PlayerController!"));
		return;
	}

	ACharacter* Character = PlayerController->GetCharacter();

	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::StateChanged_PlayingCharacter: Failed to get correct Character!"));
		return;
	}

	ActorToFollow = Character;
	//CameraRotation = FQuat(FRotator(-90., 0, 90.));
	SetActorRotation(FQuat(FRotator(-90., 0, 90.)));
}

void AHermitCamera::StateChanged_EndGameSequence()
{
	//SetActorTransform(MainMenuTransformTarget->GetTransform());
	//CameraRotation = FQuat();
	//SetActorRotation(FQuat());
}

void AHermitCamera::StateChanged_ScoreTable()
{
	SetActorTransform(MainMenuTransformTarget->GetTransform());
	//CameraRotation = FQuat();
	SetActorRotation(FQuat());
}
