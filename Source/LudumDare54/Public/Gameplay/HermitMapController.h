

#pragma once

#include "CoreMinimal.h"

#include "Gameplay/HermitStateChangedInterface.h"

#include "HermitMapController.generated.h"



// TODO: Do we really need AInfo, or we can do just UObject?

UCLASS(Blueprintable)
class LUDUMDARE54_API AHermitMapController : public AInfo, public IHermitStateChangedInterface 
{
	GENERATED_BODY()

public:

	AHermitMapController();

protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// End AActor Interface

	// Begin IHermitStateChangedInterface Interface
public:
	UFUNCTION() virtual void StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState) override { StateChangedImplementation(NewState, OldState); }
protected:
	virtual void StateChanged_MainMenu() override;
	virtual void StateChanged_PlayingCharacter() override;
	virtual void StateChanged_EndGameSequence() override;
	virtual void StateChanged_ScoreTable() override;
	// End IHermitStateChangedInterface Interface

public:

	// Rate of upward autoscrolling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MapController)
	float UpwardMovementRate = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapController)
	class UCurveFloat* VerticalScaleCurve = nullptr;

	// Bottomest playable position, that we can't view or move under. Increasing with UpwardMovementRate speed
	UPROPERTY(BlueprintReadOnly, Category = MapController)
	double CurrentPosition = 0.f;

	// Vertical size of playable space. Scales according to VerticalScaleCurve depending on scale of the crab
	UPROPERTY(BlueprintReadOnly, Category = MapController)
	double CurrentVerticalSize;

	UPROPERTY(BlueprintReadOnly, Category = MapController)
	FBox CameraViewBox;

	// TODO: obtain from appropriate source
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapController)
	double HorizontalSize = 2000;

	

	class AHermitPlayer* PlayerCharacter;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = MapContollerDebugDraw)
	bool bDrawDebugCameraSpace = false;

	UPROPERTY(EditAnywhere, Category = MapContollerDebugDraw)
	float DebugLineThickness = 2.f;

	UPROPERTY(EditAnywhere, Category = MapContollerDebugDraw)
	double DebugZCoord = 50.f;

	UPROPERTY(EditAnywhere, Category = MapContollerDebugDraw)
	FColor DebugCameraSpaceBoxColor = FColor::Red;

	UPROPERTY(EditAnywhere, Category = MapContollerDebugDraw)
	FColor CameraViewBoxColor = FColor::Blue;
#endif

};
