

#include "HermitPlayerController.h"
#include "LudumDare54.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"

#include "Ludum54GM.h"

using EILPS = UEnhancedInputLocalPlayerSubsystem;

void AHermitPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (EILPS* Subsystem = ULocalPlayer::GetSubsystem<EILPS>(GetLocalPlayer()))
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


void AHermitPlayerController::SetGameplayState(EHermitGameplayState State)
{
	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitPlayerController::SetGameplayState: Failed to get gamemode!"));
		return;
	}

	GameMode->SetGameplayState(State);
}
