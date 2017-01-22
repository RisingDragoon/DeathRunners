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
		float MaxSmashCharge = 100.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashChargeSpeed = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float AbilityCooldown = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		FTimerHandle FallingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float FallingTimeRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool CanSmash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		ABasePlayer* PlayerToSmash = nullptr;


protected:

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//bool CheckRangeSmash();

	void StartFalling();

	void StopFalling();

	//void SetCanSmashTrue(class AActor* otherActor);

	//void SetCanSmashFalse(class AActor* otherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* JumpingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* FallingAnimation;

	void Smash();

	//void Jump();

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	float SmashCharge = 0;

	bool IsJumping;

	bool IsFalling;
	
	bool IsOutOfControl = false;
};
