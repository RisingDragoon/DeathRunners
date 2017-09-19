// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "PlatformSpawner.h"
#include "BasePlatform.h"

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "Platform Spawner" ) );
	RootComponent = sceneComponent;

	// Popola l'array con 5 punti di spawn a x = -512, -256, 0, 256 e 512.
	for ( int x = -512; x <= 512; x += 256 )
	{
		spawnPoints.Add( FVector( x, 0.0, 0.0 ) );
	}
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	nextSpawnZ = GetActorLocation().Z;
}

void APlatformSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if ( GetActorLocation().Z > nextSpawnZ )
	{
		SpawnPlatforms( nextSpawnZ );
		nextSpawnZ += spawningGap;
	}
}

void APlatformSpawner::SpawnPlatforms( float z )
{
	UWorld* const world = GetWorld();

	if ( world )
	{
		FActorSpawnParameters params;
		params.Owner = this;
		params.Instigator = Instigator;

		TArray<bool> pattern = GeneratePattern();

		int specialPos = -1;

		if ( FMath::FRandRange( 0.0, 1.0 ) < 0.33 )
		{
			do
			{
				specialPos = FMath::RandRange( 0, spawnPoints.Num() - 1 );//Da 0 a 3
			} while ( !pattern[specialPos] );
		}

		for ( int col = 0; col < spawnPoints.Num(); col++ )
		{
			if ( pattern[col] )
			{
				//Aggiunge un offset sulla x per spawnarla nella colonna
				FVector spawnLocation = FVector( 0.0, 0.0, z ) + spawnPoints[col];
				TSubclassOf<ABasePlatform> toSpawn = normalPlatform;
				//Sceglie la piattaforma se è speciale
				if ( col == specialPos )
				{
					int rand = FMath::RandRange( 0, specialPlatforms.Num() - 1 );
					toSpawn = specialPlatforms[rand];
				}
				//Spawna
				world->SpawnActor<ABasePlatform>( toSpawn, spawnLocation, FRotator::ZeroRotator, params );
			}
		}
	}
}

TArray<bool> APlatformSpawner::GeneratePattern()
{
	TArray<bool> pattern;

	if ( FMath::RandBool() )
		pattern = { false, false, false, false, false };
	else
		pattern = { true, true, true, true, true };

	TArray<int> rand = { NULL, NULL };

	while ( rand[0] == rand[1] )
	{
		rand[0] = FMath::RandRange( 0, spawnPoints.Num() - 1 );
		rand[1] = FMath::RandRange( 0, spawnPoints.Num() - 1 );
	}

	for ( int i : rand )
		pattern[i] = !pattern[i];

	return pattern;
}
