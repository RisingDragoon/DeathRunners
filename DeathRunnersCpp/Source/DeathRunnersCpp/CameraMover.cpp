// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "DeathRunnersCppGameMode.h"
#include "BasePlayer.h"
#include "CameraMover.h"

UCameraMover::UCameraMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraMover::BeginPlay()
{
	Super::BeginPlay();

}

void UCameraMover::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!canMove)
	{
		return;
	}
	ADeathRunnersCppGameMode* gameMode = (ADeathRunnersCppGameMode*)GetWorld()->GetAuthGameMode();
	TArray<ABasePlayer*> characters = gameMode->GetPlayers();//BasePlayer in game

	float averageZ = 0;
	//fa la media delle Z dei player
	if ( characters.Num() != 0 )
	{
		for ( auto item : characters )
		{
			if (item)
			{
				averageZ += item->GetActorLocation().Z;
			}
		}

		averageZ /= characters.Num();
	}
	//Aggiusta la velocità
	float speedFactor = (( averageZ - GetOwner()->GetActorLocation().Z ) / 1080.0 ) + 0.5;
	float speed = FMath::Lerp( minSpeed, maxSpeed, speedFactor );

	if (speed < minSpeed)
	{
		speed = minSpeed;
	}

	FVector offset = FVector( 0.0, 0.0, speed ) * DeltaTime;

	for ( auto item : actorsToMove )
	{
		if (item)
		{
		item->AddActorWorldOffset( offset, false );
		}
	}

	GetOwner()->AddActorWorldOffset( offset, false );
}
