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
	enum TipoSmash { Caricato, Normale };

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void UpdateAnimation();

	void UpdateCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float AbilityCooldown = 3.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashForce = 0.0;

	FTimerHandle Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float FallingTimeRate = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool CanSmash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		ABasePlayer* PlayerToSmash = nullptr;

	void SetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void ResetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool SpecialAbilityIsReady = true;

	void EnableSpecialAbility();

	void LoseControl();

	void ChargeSmash();

	bool IsFalling;

	bool IsCharging;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
	//	float SmashCharge = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float MaxSmashForce = 450;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashChargeSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SmashForceLevel = 50;

	TipoSmash tipoSmash;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	void Smash();

	void RegainControl();

	virtual void Jump() override;

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);


	bool IsJumping;

	bool IsOutOfControl = false;

};
