// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "PlatformSpawner.h"
#include "BasePlatform.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	/*for ( auto item : spawnPoints )
	{
		UE_LOG( LogTemp, Warning, TEXT( "I detected a spawner" ) );
	}*/

	GetWorldTimerManager().SetTimer( spawnTimer, this, &APlatformSpawner::SpawnPlatform, spawnDelay, true );
}

// Called every frame
void APlatformSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APlatformSpawner::SpawnPlatform()
{
	UWorld* const world = GetWorld();

	if ( world )
	{
		FActorSpawnParameters params;
		params.Owner = this;
		params.Instigator = Instigator;

		// Prende un punto casuale dove spawnare la piattaforma. Non sarà così nel gioco.
		int i = FMath::RandRange( 0, spawnPoints.Num() - 1 );
		FVector spawnLocation = GetActorLocation() + spawnPoints[i];

		// Seleziona solo la prima piattaforma dell'array. Non sarà così nel gioco.
		world->SpawnActor<ABasePlatform>( platformTypes[0], spawnLocation, FRotator::ZeroRotator, params );
	}
}