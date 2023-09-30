

#pragma once

#include "CoreMinimal.h"

#include "Ludum54GM.h"
#include "Enumerations/GameplayState.h"

#include "HermitStateChangedInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHermitStateChangedInterface : public UInterface
{
    GENERATED_BODY()

protected:
};

class IHermitStateChangedInterface
{
    GENERATED_BODY()

public:

    // Subscribe to state change event and initialize initial state
    // Call this on BeginPlay() like this: InitializeStateChange(this, HermitGameMode);
    template<typename DerivedCallerT>
    void InitializeStateChange(DerivedCallerT* Instance, class ALudum54GM* InHermitGameMode)
    {
        InHermitGameMode->OnGameplayStateChanged.AddDynamic(Instance, &DerivedCallerT::StateChanged);
        EHermitGameplayState StateAtBegin = InHermitGameMode->GetGameplayState();
        StateChanged(StateAtBegin, EHermitGameplayState::End);
    }

    bool GetIsPlayingCharacter() { return bIsPlayingCharacter; }
    
    // Implement this as UFUNCTION calling StateChangedImplementation. (limitation of Unreal reflection)
    virtual void StateChanged(EHermitGameplayState NewState, EHermitGameplayState OldState) = 0;

    virtual void StateChanged_MainMenu() {}
    virtual void StateChanged_PlayingCharacter() {}
    virtual void StateChanged_EndGameSequence() {}
    virtual void StateChanged_ScoreTable() {}


protected:
    void StateChangedImplementation(EHermitGameplayState NewState, EHermitGameplayState OldState);

private:
    bool bIsPlayingCharacter = false;
};
