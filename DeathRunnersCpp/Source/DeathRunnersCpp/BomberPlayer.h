// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayer.h"
#include "BomberPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API ABomberPlayer : public ABasePlayer
{
	GENERATED_BODY()
	
public:
	void SpecialAbility() override;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	TSubclassOf<class ABomb> BombBlueprint;
};
