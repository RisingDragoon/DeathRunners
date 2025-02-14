// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayer.h"
#include "DoubleJumpPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API ADoubleJumpPlayer : public ABasePlayer
{
	GENERATED_BODY()

public:
	ADoubleJumpPlayer();

	virtual void Tick(float DeltaSeconds) override;

	void BeginPlay() override;

	void Jump() override;
};
