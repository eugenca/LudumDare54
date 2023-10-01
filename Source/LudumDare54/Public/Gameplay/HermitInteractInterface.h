

#pragma once

#include "CoreMinimal.h"

#include "HermitInteractInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHermitInteractInterface : public UInterface
{
    GENERATED_BODY()
};


class IHermitInteractInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void InteractBP(AActor* Instigator);

    virtual void Interact(AActor* Instigator) = 0;
};
