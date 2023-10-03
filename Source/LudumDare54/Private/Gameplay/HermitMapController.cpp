

#include "Gameplay/HermitMapController.h"
#include "LudumDare54.h"

#include "Kismet/GameplayStatics.h"
#include "Curves/CurveFloat.h"

#include "Ludum54GM.h"
#include "Characters/HermitPlayer.h"

#if WITH_EDITORONLY_DATA
#include "DrawDebugHelpers.h"
#endif


AHermitMapController::AHermitMapController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHermitMapController::BeginPlay()
{
	UE_LOG(LogHermit, Warning, TEXT("AHermitMapController::BeginPlay"));
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
	/*if (!PlayerCharacter)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitMapController::Tick: PlayerCharacter is nullptr!"));
		return;
	}*/
	
	if (!GetIsPlayingCharacter())
	{
		return;
	}

	//UE_LOG(LogHermit, Warning, TEXT("AHermitMapController::Tick"));

	check(PlayerCharacter);
	check(VerticalScaleCurve);

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const double Ratio = ViewportSize.X / ViewportSize.Y;

	CurrentPosition += UpwardMovementRate * DeltaSeconds;
	CurrentVerticalSize = VerticalScaleCurve->GetFloatValue(PlayerCharacter->CurrentHermitScale);
	
	if (CurrentVerticalSize * Ratio > HorizontalSize)
	{
		CurrentVerticalSize = HorizontalSize / Ratio;
	}

	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	
	//UE_LOG(LogHermit, Log, TEXT("%s"), *ViewportSize.ToString());

	const FBox CameraSpaceBox(
		FVector(0.,				CurrentPosition,					   0./*DebugZCoord*/),
		FVector(HorizontalSize, CurrentPosition + CurrentVerticalSize, 0./*DebugZCoord*/));

	const FVector CameraViewBoxHalfDiagonalVector(CurrentVerticalSize * 0.5 * Ratio, CurrentVerticalSize * 0.5, 0.);

	const double DesiredLocationForCameraX = FMath::Clamp(PlayerLocation.X, CameraViewBoxHalfDiagonalVector.X, HorizontalSize - CameraViewBoxHalfDiagonalVector.X);
	const double DesiredLocationForCameraY = CurrentPosition + CurrentVerticalSize * 0.5;
	const FVector DesiredLocationForCamera(DesiredLocationForCameraX, DesiredLocationForCameraY, 0./*DebugZCoord*/);
	CameraViewBox =
		FBox(DesiredLocationForCamera - CameraViewBoxHalfDiagonalVector,
			DesiredLocationForCamera + CameraViewBoxHalfDiagonalVector);

#if WITH_EDITORONLY_DATA
	UWorld* World = GetWorld();
	FlushPersistentDebugLines(World);
	if (bDrawDebugCameraSpace)
	{
		FBox CameraSpaceBoxDebug = CameraSpaceBox.MoveTo(CameraSpaceBox.GetCenter() + FVector(0.,0.,DebugZCoord));
		FBox CameraViewBoxDebug = CameraViewBox.MoveTo(CameraViewBox.GetCenter() + FVector(0.,0.,DebugZCoord));


		FVector CameraSpaceBoxTopLeft = CameraSpaceBoxDebug.Min + FVector(0., CameraSpaceBoxDebug.GetSize().Y, 0.);
		FVector CameraSpaceBoxBottomRight = CameraSpaceBoxDebug.Min + FVector(CameraSpaceBoxDebug.GetSize().X, 0., 0.);
		DrawDebugLine(World, CameraSpaceBoxDebug.Min, CameraSpaceBoxTopLeft, DebugCameraSpaceBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraSpaceBoxTopLeft, CameraSpaceBoxDebug.Max, DebugCameraSpaceBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraSpaceBoxDebug.Max, CameraSpaceBoxBottomRight, DebugCameraSpaceBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraSpaceBoxBottomRight, CameraSpaceBoxDebug.Min, DebugCameraSpaceBoxColor, true, -1.f, 0, DebugLineThickness);

		CameraViewBoxDebug = CameraViewBoxDebug.ExpandBy(-DebugLineThickness);
		FVector CameraViewBoxTopLeft = CameraViewBoxDebug.Min + FVector(0., CameraViewBoxDebug.GetSize().Y, 0.);
		FVector CameraViewBoxBottomRight = CameraViewBoxDebug.Min + FVector(CameraViewBoxDebug.GetSize().X, 0., 0.);
		DrawDebugLine(World, CameraViewBoxDebug.Min, CameraViewBoxTopLeft, CameraViewBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraViewBoxTopLeft, CameraViewBoxDebug.Max, CameraViewBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraViewBoxDebug.Max, CameraViewBoxBottomRight, CameraViewBoxColor, true, -1.f, 0, DebugLineThickness);
		DrawDebugLine(World, CameraViewBoxBottomRight, CameraViewBoxDebug.Min, CameraViewBoxColor, true, -1.f, 0, DebugLineThickness);
	}
#endif

}

void AHermitMapController::StateChanged_MainMenu()
{

}

void AHermitMapController::StateChanged_PlayingCharacter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (!PlayerController)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitMapController::StateChanged_PlayingCharacter: Failed to get correct PlayerController!"));
		return;
	}

	auto* Character = Cast<AHermitPlayer>(PlayerController->GetCharacter());

	if (!Character)
	{
		UE_LOG(LogHermit, Error, TEXT("AHermitMapController::StateChanged_PlayingCharacter: Failed to get correct Character!"));
		return;
	}

	UE_LOG(LogHermit, Warning, TEXT("AHermitMapController::StateChanged_PlayingCharacter success"));

	ResetMap();
	PlayerCharacter = Character;
}

void AHermitMapController::StateChanged_EndGameSequence()
{

}

void AHermitMapController::StateChanged_ScoreTable()
{

}

void AHermitMapController::ResetMap()
{
	CurrentPosition = 0.f;
}
