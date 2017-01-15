// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "BasePlatform.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API ABasePlatform : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleani)
		bool OneSide = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleani)
		bool IsThick = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleani)
		bool IsDestructible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleani)
		bool IsHarmful = false;
	
};
