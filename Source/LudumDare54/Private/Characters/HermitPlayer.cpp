// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HermitPlayer.h"

#include "Logging/StructuredLog.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

using KML = UKismetMathLibrary;

// Sets default values
AHermitPlayer::AHermitPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHermitPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			if (MappingContext) {
				Subsystem->AddMappingContext(MappingContext, 0);
			}
			else {
				UE_LOGFMT(LogTemp, Warning, "No default input mapping context set in player blueprint.");
			}
		}
	}
}

void AHermitPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();
	FRotator r = GetControlRotation();

	const FVector v = KML::GetRightVector({ 0, r.Roll, r.Yaw });
	AddMovementInput(v, MovementVector.X);

	const FVector va = KML::GetForwardVector({ 0, 0, r.Yaw });
	AddMovementInput(va, MovementVector.Y);
}

void AHermitPlayer::Interact(const FInputActionValue& Value)
{
	// input is a Vector2D
	bool MovementVector = Value.Get<bool>();
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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		if ( MoveAction && InteractAction) {

			//Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHermitPlayer::Move);

			//Interacting
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AHermitPlayer::Interact);
		}
		else {
			UE_LOGFMT(LogTemp, Warning, "One or more of the input actions has not be set in player blueprint.");
		}
	}
}

