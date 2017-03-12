// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasePlatform.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class DEATHRUNNERSCPP_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UPROPERTY( VisibleAnywhere )
	USceneComponent* sceneComponent;

	UPROPERTY( EditAnywhere, Category = "Spawn" )
	TSubclassOf<class ABasePlatform> normalPlatform;

	UPROPERTY( EditAnywhere, Category = "Spawn" )
	TArray<TSubclassOf<class ABasePlatform>> specialPlatforms;

	UPROPERTY( EditAnywhere, Category = "Spawn" )
	float spawningGap;

	TArray<FVector> spawnPoints;
	float nextSpawnZ;

	void SpawnPlatforms( float z );
	TArray<bool> GeneratePattern();
};
