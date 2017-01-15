// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DeathRunnersCpp.h"
#include "DeathRunnersCppGameMode.h"
#include "DeathRunnersCppCharacter.h"

ADeathRunnersCppGameMode::ADeathRunnersCppGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ADeathRunnersCppCharacter::StaticClass();	
}
