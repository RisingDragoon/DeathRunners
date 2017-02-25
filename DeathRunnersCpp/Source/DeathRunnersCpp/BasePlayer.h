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

	virtual void BeginPlay() override;

	void UpdateAnimation();

	void UpdateCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float AbilityCooldown = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashForce = 100.0;

		FTimerHandle Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float FallingTimeRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool CanSmash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		ABasePlayer* PlayerToSmash = nullptr;

	void SetPlayerToSmash();

	void ResetPlayerToSmash();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool SpecialAbilityIsReady = true;

	void EnableSpecialAbility();

	void LoseControl();

	bool IsFalling;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void StartFalling();

	void StopFalling();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* JumpingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FallingAnimation;

	void Smash();

	void RegainControl();

	virtual void Jump() override;

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	float SmashCharge = 0;

	bool IsJumping;
	
	bool IsOutOfControl = false;

};
