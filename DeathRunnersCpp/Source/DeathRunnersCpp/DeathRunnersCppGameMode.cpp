// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DeathRunnersCpp.h"
#include "DeathRunnersCppGameMode.h"
#include "DeathRunnersCppCharacter.h"
#include "BasePlayer.h"

ADeathRunnersCppGameMode::ADeathRunnersCppGameMode()
{
	// set default pawn class to our character
	//DefaultPawnClass = ABasePlayer::StaticClass();
	//DefaultPawnClass = ADeathRunnersCppCharacter::StaticClass();	
}
void ADeathRunnersCppGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<ABasePlayer*> ADeathRunnersCppGameMode::GetPlayers()
{
	return players;
}

void ADeathRunnersCppGameMode::AddPlayer( ABasePlayer* player )
{
	players.Add( player );
	UE_LOG( LogTemp, Warning, TEXT( "%s added to player array. Player count: %d" ), *GetName(), players.Num() );
}

void ADeathRunnersCppGameMode::RemovePlayer( ABasePlayer* player )
{
	players.Remove( player );
	UE_LOG( LogTemp, Warning, TEXT( "%s removed from player array. Player count: %d" ), *GetName(), players.Num() );

	if ( players.Num() == 1 )
	{
		UGameplayStatics::SetGamePaused( GetWorld(), true );
		GameOver( players[0] ); // Spara un evento da blueprint
	}
}
