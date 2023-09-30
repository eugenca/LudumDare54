

#include "Gameplay/HermitMapController.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"
#include "Curves/CurveFloat.h"

#include "Ludum54GM.h"




void AHermitMapController::BeginPlay()
{
	ALudum54GM* GameMode = Cast<ALudum54GM>(UGameplayStatics::GetGameMode(this));

	if (!GameMode)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitCamera: Failed to get gamemode!"));
		return;
	}

	// Subscribe to state change event and initialize initial state
	InitializeStateChange(this, GameMode);
}

void AHermitMapController::Tick(float DeltaSeconds)
{
	if (!GetIsPlayingCharacter())
	{
		return;
	}


}

void AHermitMapController::StateChanged_MainMenu()
{

}

void AHermitMapController::StateChanged_PlayingCharacter()
{

}

void AHermitMapController::StateChanged_EndGameSequence()
{

}

void AHermitMapController::StateChanged_ScoreTable()
{

}
