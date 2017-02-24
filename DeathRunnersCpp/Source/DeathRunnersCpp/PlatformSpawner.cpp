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

	/*for ( auto item : spawnPoints )
	{
		UE_LOG( LogTemp, Warning, TEXT( "I detected a spawner" ) );
	}*/

	spawnPatterns = {
		{ true, false, false, true, true },
		{ true, true, false, false, true },
		{ false, false, true, true, true },
		{ true, true, true, false, false },
		{ true, false, true, false, true },
		{ true, true, false, true, true },
		{ false, true, true, true, false },
		{ false, false, false, true, true },
		{ false, false, true, true, false },
		{ false, true, true, false, false },
		{ true, true, false, false, false },
		{ false, false, false, false, true },
		{ false, false, false, true, false },
		{ false, false, true, false, false },
		{ false, true, false, false, false },
		{ true, false, false, false, false }
	};
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

		// Seleziona un pattern casuale con cui spawnare le piattaforme.
		int randPattern = FMath::RandRange( 0, spawnPatterns.Num() - 1 );

		// Scorre il pattern e spawna le piattaforme.
		for ( int col = 0; col < spawnPatterns[randPattern].Num(); col++ )
		{
			if ( spawnPatterns[randPattern][col] )
			{
				FVector spawnLocation = FVector( 0.0, 0.0, z ) + spawnPoints[col];

				// Seleziona una piattaforma casuale da spawnare. Soluzione temporanea.
				int randPlatform = FMath::RandRange( 0, platformTypes.Num() - 1 );
				world->SpawnActor<ABasePlatform>( platformTypes[randPlatform], spawnLocation, FRotator::ZeroRotator, params );
			}
		}
	}
}