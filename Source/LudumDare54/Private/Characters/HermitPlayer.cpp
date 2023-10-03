// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HermitPlayer.h"
#include "LudumDare54.h"

#include "Logging/StructuredLog.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

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

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shell Mesh"));
	ShellMesh->SetupAttachment(RootComponent);
	ShellMesh->SetUsingAbsoluteScale(true);
}

void AHermitPlayer::PickShell(class AHermitShellActor* InShellActor)
{
	// TODO: Animations?

	if (!InShellActor || !InShellActor->ShellMesh)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitPlayer::EquipShell: Invalid InShell!"));
		return;
	}

	if (ShellActorClass)
	{
		DropShell();
	}

	ShellActorClass = InShellActor->GetClass();
	Shell = InShellActor->Shell;

	auto* OtherComponent = InShellActor->ShellMesh;
	OtherComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	InShellActor->ShellMesh = nullptr;
	OtherComponent->UnregisterComponent();
	//this->AddInstanceComponent(OtherComponent);
	ShellMesh = OtherComponent;
	ShellMesh->Rename(nullptr, this);
	ShellMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Shell->ShellSocketName);
	ShellMesh->RegisterComponent();
	ShellMesh->SetRelativeScale3D(FVector(Shell->ShellScale));
	ShellMesh->SetUsingAbsoluteScale(true);
	// 
	// 
	//ShellMesh = ShellActor->ShellMesh;
	//ShellActor->ShellMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "TailSocket");

	
	GetWorld()->DestroyActor(InShellActor);

	//Shell = ShellActor->ShellMesh;
	//ShellMesh->SetStaticMesh(Shell->ShellMesh->GetStaticMesh());
	//ShellMesh = Shell->ShellMesh;
}

void AHermitPlayer::DropShell()
{
	check(ShellActorClass);
	check(ShellMesh);

	UWorld* World = GetWorld();

	//FActorSpawnParameters Params;
	//Params.Template = ShellActor;

	FVector NewLoc = GetActorLocation() - GetActorRotation().Vector().GetSafeNormal() * TEMPDistToSpawn;
	FRotator NewRot = ShellMesh->GetComponentTransform().Rotator();
	//FVector NewScal = ShellMesh->GetComponentTransform().GetScale3D();
	FTransform Transform(NewRot, NewLoc, FVector(1, 1, 1));

	AActor* SpawnedActor = World->SpawnActor(ShellActorClass, &Transform);
	AHermitShellActor* NewShellActor = Cast<AHermitShellActor>(SpawnedActor);
	NewShellActor->Shell = Shell;

	if (!NewShellActor)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitPlayer::EquipShell: Spawned Actor!"));
		return;
	}

	auto* MyComponent = ShellMesh;
	auto* OtherComponent = NewShellActor->ShellMesh;

	MyComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	MyComponent->UnregisterComponent();

	OtherComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	OtherComponent->UnregisterComponent();
	OtherComponent->DestroyComponent();

	ShellMesh = nullptr;
	NewShellActor->ShellMesh = MyComponent;

	NewShellActor->ShellMesh->Rename(nullptr, NewShellActor);
	NewShellActor->ShellMesh->AttachToComponent(NewShellActor->CollisionCapsule, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewShellActor->ShellMesh->RegisterComponent();
	NewShellActor->ShellMesh->SetRelativeScale3D(FVector(NewShellActor->Shell->ShellScale));

	ShellActorClass = nullptr;
	Shell = nullptr;
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

	//CurrentDirection = FMath::VInterpTo(CurrentDirection, DesiredDirection, DeltaTime, HermitRotationSpeedDegrees);
	CurrentDirection = FMath::VInterpNormalRotationTo(CurrentDirection, DesiredDirection, DeltaTime, HermitRotationSpeedDegrees);
	//UE_LOG(LogHermit, Warning, TEXT("Curr: %s, Desir: %s"), *CurrentDirection.ToString(), *DesiredDirection.ToString());
	//SetActorRotation(CurrentDirection.Rotation());

	if (!Shell)
	{
		TimeLeftToDieWithoutShell -= DeltaTime;
	}
	else
	{
		TimeLeftToDieWithoutShell += DeltaTime;
		if (TimeLeftToDieWithoutShell > DefaultTimeToDieWithoutShell)
		{
			TimeLeftToDieWithoutShell = DefaultTimeToDieWithoutShell;
		}
	}

	if (Shell)
	{
		FVector2D MinMax = Shell->GetMinMaxCrabScale();
		check(CurrentHermitScale > MinMax.X);

		if (CurrentHermitScale > MinMax.Y)
		{
			DropShell();
			OnShellDropTight.Broadcast();
		}
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

			EnhancedInputComponent->BindAction(SpawnShellAction, ETriggerEvent::Triggered, this, &AHermitPlayer::SpawnShell);
		}
		else 
		{
			UE_LOGFMT(LogTemp, Warning, "One or more of the input actions has not be set in player blueprint.");
		}
	}
}

void AHermitPlayer::ResetCharacter()
{
	CurrentDirection = FVector(FMath::RandRange(0., 1.), FMath::RandRange(0., 1.), 0.).GetSafeNormal();
	DesiredDirection = CurrentDirection;
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

	const FVector2D MovementVectorNormalized = MovementVector.GetSafeNormal();
	DesiredDirection = FVector(MovementVectorNormalized.X, MovementVectorNormalized.Y, 0.);

	AddMovementInput(FVector::RightVector, MovementVector.Y);
	AddMovementInput(FVector::ForwardVector, -MovementVector.X);


	//FRotator r = FVector(0., 1., 0.).Rotation();
	//
	//const FVector v = KML::GetRightVector({ 0, r.Roll, r.Yaw });
	//AddMovementInput(v, MovementVector.X);
	//
	//const FVector va = KML::GetForwardVector({ 0, 0, r.Yaw });
	//AddMovementInput(va, MovementVector.Y);

	
}

void AHermitPlayer::Interact(const FInputActionValue& Value)
{
	OnInteractPressed.Broadcast();
}

void AHermitPlayer::SpawnShell(const FInputActionValue& Value)
{
	FVector LocToSpawnTemp = GetActorLocation() + GetActorRotation().Vector().GetSafeNormal() * TEMPDistToSpawn;
	FTransform Transform(LocToSpawnTemp);
	GetWorld()->SpawnActor(TEMPShell, &Transform, FActorSpawnParameters());
}
