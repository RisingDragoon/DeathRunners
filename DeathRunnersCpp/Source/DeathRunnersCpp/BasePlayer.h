// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API ABasePlayer : public APaperCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();

	virtual void Tick(float DeltaSeconds) override;

	void UpdateAnimation();

	void UpdateCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float JumpForce = 100.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float MaxSmashCharge = 100.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashChargeSpeed = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float AbilityCooldown = 10.0;
protected:

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	void Smash(ABasePlayer other);

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	float SmashCharge = 0;

	bool IsJumping;
	
};
