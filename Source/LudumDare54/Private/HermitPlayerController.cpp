

#include "HermitPlayerController.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"

#include "Ludum54GM.h"

void AHermitPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
