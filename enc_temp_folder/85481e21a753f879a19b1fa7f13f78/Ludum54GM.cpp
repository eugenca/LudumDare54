// Fill out your copyright notice in the Description page of Project Settings.


#include "Ludum54GM.h"

void ALudum54GM::SetGameplayState(EGameplayState NewState)
{
	EGameplayState OldState = State;
	State = NewState;

	OnGameplayStateChangedDelegate.Broadcast(State, OldState);
}
