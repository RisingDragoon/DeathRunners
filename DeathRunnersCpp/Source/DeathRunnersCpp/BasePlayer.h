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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float AbilityCooldown = 3.0;

	float SmashForce = 0.0;

	FTimerHandle Timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float FallingTimeRate = 1.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool CanSmash = false;//VisibleAnywhere

	ABasePlayer* PlayerToSmash = nullptr;

	UFUNCTION()
	void SetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ResetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool SpecialAbilityIsReady = true;

	void EnableSpecialAbility();

	void LoseControl();

	void ChargeSmash();

	bool IsFalling;

	bool IsCharging;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
	//	float SmashCharge = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float MaxSmashForce = 450;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float SmashChargeSpeed = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float SmashForceLevel = 100;

	float AppliedForce = 0;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void StartFalling();

	void StopFalling();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FallingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DyingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DropAnimation;

	void Smash();

	void RegainControl();

	virtual void Jump() override;

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	bool IsJumping;

	bool IsOutOfControl = false;
};
