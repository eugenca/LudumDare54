

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HermitPlayerController.generated.h"

UCLASS()
class LUDUMDARE54_API AHermitPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};