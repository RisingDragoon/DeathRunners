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
	void SpecialAbility() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void LogX(float value);

	void LogY(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		float LastAxisX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		float LastAxisY = 0;

};
