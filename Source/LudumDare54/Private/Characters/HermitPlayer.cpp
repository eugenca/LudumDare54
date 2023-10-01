// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HermitPlayer.h"
#include "LudumDare54.h"

#include "Logging/StructuredLog.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Ludum54GM.h"
#include "Gameplay/HermitMapController.h"
#include "Gameplay/ShellActor.h"

using KML = UKismetMathLibrary;
using EIC = UEnhancedInputComponent;


// Sets default values
AHermitPlayer::AHermitPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	TimeLeftToDieWithoutShell = DefaultTimeToDieWithoutShell;
}

void AHermitPlayer::EquipShell(UHermitShell* InShell)
{
	// TODO: Animations?

	Shell = nullptr;

	Shell = InShell;
	ShellMesh->SetStaticMesh(Shell->ShellMesh);
}

// Called when the game starts or when spawned
void AHermitPlayer::BeginPlay()
{
	using EILPS = UEnhancedInputLocalPlayerSubsystem;

	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (MappingContext)
			{
				Subsystem->AddMappingContext(MappingContext, 0);
			}
			else
			{
				UE_LOGFMT(LogTemp, Warning, "No default input mapping context set in player blueprint.");
			}
		}
	}

	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera::BeginPlay: Failed to get gamemode!"));
		return;
	}

	// Subscribe to state change event and initialize initial state
	InitializeStateChange(this, GameMode);
	ResetCharacter();
}

void AHermitPlayer::StateChanged_MainMenu()
{
}

void AHermitPlayer::StateChanged_PlayingCharacter()
{
	ResetCharacter();
}

void AHermitPlayer::StateChanged_EndGameSequence()
{
}

void AHermitPlayer::StateChanged_ScoreTable()
{
}

// Called every frame
void AHermitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetIsPlayingCharacter())
	{
		return;
	}

	

	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitPlayer::Tick: Failed to get gamemode!"));
		return;
	}

	AHermitMapController* MapController = GameMode->MapController;

	if (!MapController)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitPlayer::Tick: Failed to get MapController!"));
		return;
	}

	CurrentHermitScale += HermitGrowthRate * DeltaTime;
	SetActorScale3D(FVector(CurrentHermitScale));

	FVector MyLocation = GetActorLocation();

	const double CurrentRadius = BaseInteractRadius * CurrentHermitScale;

	MyLocation.X = FMath::Clamp(MyLocation.X, CurrentRadius, MapController->HorizontalSize - CurrentRadius);
	MyLocation.Y = FMath::Clamp(MyLocation.Y,
		MapController->CurrentPosition + CurrentRadius,
		MapController->CurrentPosition + MapController->CurrentVerticalSize - CurrentRadius);
	SetActorLocation(MyLocation);

	if (!Shell)
	{
		TimeLeftToDieWithoutShell -= DeltaTime;
	}

	if (TimeLeftToDieWithoutShell < 0.f)
	{
		GameMode->SetGameplayState(EHermitGameplayState::EndGameSequence);
	}

}

// Called to bind functionality to input
void AHermitPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (EIC* EnhancedInputComponent = CastChecked<EIC>(PlayerInputComponent)) 
	{

		if ( MoveAction && InteractAction) 
		{
			//Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHermitPlayer::Move);

			//Interacting
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AHermitPlayer::Interact);
		}
		else 
		{
			UE_LOGFMT(LogTemp, Warning, "One or more of the input actions has not be set in player blueprint.");
		}
	}
}

void AHermitPlayer::ResetCharacter()
{
	CurrentHermitScale = DefaultHermitScale;
	TimeLeftToDieWithoutShell = DefaultTimeToDieWithoutShell;
	Shell = nullptr;
}

void AHermitPlayer::Move(const FInputActionValue& Value)
{
	if (!GetIsPlayingCharacter())
	{
		return;
	}
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>() * HermitSpeedScale;
	FRotator r = GetControlRotation();

	const FVector v = KML::GetRightVector({ 0, r.Roll, r.Yaw });
	AddMovementInput(v, MovementVector.Y);

	const FVector va = KML::GetForwardVector({ 0, 0, r.Yaw });
	AddMovementInput(va, -MovementVector.X);
}

void AHermitPlayer::Interact(const FInputActionValue& Value)
{
	// input is a Vector2D
	bool MovementVector = Value.Get<bool>();
}