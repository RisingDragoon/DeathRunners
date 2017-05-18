// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayer.h"
#include "GrapplePlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API AGrapplePlayer : public ABasePlayer
{
	GENERATED_BODY()
public:

	AGrapplePlayer();

	virtual void BeginPlay() override;

	void SpecialAbility() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	void LogX(float value);

	void LogY(float value);

	float LastAxisX = 0;

	float LastAxisY = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		FVector SpawnPositionOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float MinValueShot = 40;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		//class UPaperFlipbook* Skill;


	FVector SpawnPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UClass* Hand;
	
};
