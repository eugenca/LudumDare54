

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Enumerations/GameplayState.h"

#include "HermitPlayerController.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = HermitControls)
	void SetGameplayState(EHermitGameplayState State);

};
