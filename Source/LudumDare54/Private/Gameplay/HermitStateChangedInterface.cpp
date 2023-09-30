

#include "Gameplay/HermitStateChangedInterface.h"

#include "LudumDare54.h"


void IHermitStateChangedInterface::StateChangedImplementation(EHermitGameplayState NewState, EHermitGameplayState OldState)
{
	// TODO: treat OldState to toggle animations

	bIsPlayingCharacter = false;

	switch (NewState)
	{
	case MainMenu:
		StateChanged_MainMenu();
		break;
	case PlayingCharacter:
		bIsPlayingCharacter = true;
		StateChanged_PlayingCharacter();
		break;
	case EndGameSequence:
		StateChanged_EndGameSequence();
		break;
	case ScoreTable:
		StateChanged_ScoreTable();
		break;
	case End:
	default:
		UE_LOG(LogHermit, Error, TEXT("IHermitStateChangedInterface::StateChangedImplementation Invalid NewState!"));
		break;
	}
}
