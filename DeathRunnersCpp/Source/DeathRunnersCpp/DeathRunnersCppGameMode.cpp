// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DeathRunnersCpp.h"
#include "DeathRunnersCppGameMode.h"
#include "DeathRunnersCppCharacter.h"
#include "BasePlayer.h"

ADeathRunnersCppGameMode::ADeathRunnersCppGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ABasePlayer::StaticClass();
	//DefaultPawnClass = ADeathRunnersCppCharacter::StaticClass();	
}
