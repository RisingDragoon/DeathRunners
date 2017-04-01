// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

enum class PlayerState : uint8
{
	Idle,
	Running,
	Jumping,
	Drop,
	Falling,
	Smash,
	Stun,
	JumpStart,
	JumpEnd,
	RunStart,
	RunEnd,
	ChangeDirectionDx,
	ChangeDirectionSx,
	Die
};

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float BaseSmashForce = 300;
	float AppliedForce = 0;
	UFUNCTION(BlueprintCallable, Category = "Sounds")
		virtual void PlaySmashSound();

	void StartFalling();

	void StopFalling();

	void StopSmashing();
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
	class UParticleSystemComponent* ParticleSystemCharging;

	//Animazioni
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Running;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Jumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Falling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Die;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Dropping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Smash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* Stun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* JumpStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* JumpEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ChangeDirectionDx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* ChangeDirectionSx;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class UAudioComponent* SmashSound;

	void ThrowSmash();

	void RegainControl();

	virtual void Jump() override;

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	bool IsJumping;
	bool IsSmashing;
	bool DontUpdate;
	bool IsOutOfControl = false;
};
