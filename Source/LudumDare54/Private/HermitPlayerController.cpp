

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HermitPlayerController.h"

#include "Logging/StructuredLog.h"

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
