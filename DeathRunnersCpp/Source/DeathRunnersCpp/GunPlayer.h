// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayer.h"
#include "GunPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API AGunPlayer : public ABasePlayer
{
	GENERATED_BODY()
public:

	AGunPlayer();
	virtual void BeginPlay() override;

	void SpecialAbility() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void LogX(float value);

	void LogY(float value);

	float LastAxisX = 0;

	float LastAxisY = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		FVector SpawnPositionOffset;

	FVector SpawnPosition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UClass* Projectile;
};
