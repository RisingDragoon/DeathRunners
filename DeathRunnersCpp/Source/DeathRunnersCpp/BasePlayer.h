// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "BasePlayer.generated.h"

enum class PlayerAnimation : uint8
{
	Nothing,
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
	Die,
	RunChangeDirection,
	JumpChangeDirection,
	Hit,
	DropChangeDirection,
	Skill,
	Knock,
	Smaterialize,
	Materialize,
	NoHand,
	AirPuke
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

	FTimerHandle TimerSpecialAbility;
	FTimerHandle TimerFalling;
	FTimerHandle TimerEndAnimation;
	FTimerHandle TimerGainControl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
	float FallingTimeRate = 1.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool CanSmash = false;

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

	void StopCharging();

	bool IsFalling;

	bool IsCharging;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
	//	float SmashCharge = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float MaxSmashForce = 450;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float SmashChargeSpeed = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float SmashForceLevel = 350;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float BaseSmashForce = 300;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float DeadZoneUp = 0.4f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Modificabili)
		float DeadZoneDown = -0.4f;

		int SpikeForce = 20.0f;

	float AppliedForce = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float SpikeLaunchSpeed = 1000;
	UFUNCTION(BlueprintCallable, Category = "Sounds")
		virtual void PlaySound();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void Suicide();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void Spike();

	void StartFalling();

	void StopFalling();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void ReceiveShot();

	//void StopSmashing();

	void StartAnimation(PlayerAnimation animazione);

	void EndAnimation();

	PlayerAnimation SelectedAnimation = PlayerAnimation::Nothing;

	void GetFlipbookByAnimation(PlayerAnimation animation);

	class UPaperFlipbook* SelectedFlipbook = nullptr;

	FVector LocationToTeleport = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool IsOutOfControl = false;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
	class UParticleSystemComponent* ParticleSystemCharging;

	//Animazioni
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Idle;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunStart;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Running;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunEnd;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunChangeDirection;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpStart;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Jumping;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Dropping;//mmm

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpEnd;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpChangeDirection;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DropChangeDirection;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Smash;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Hit;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Falling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Stun;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Die;//ok

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* Knock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* NoHandAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* SmaterializeAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MaterializeAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* AirPuke;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class UAudioComponent* SoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* JumpAudio=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* SmashAudio = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* StunAudio = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* SpecialAbilityAudio = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* IdleAudio = nullptr;

	
	void ThrowSmash();

	void RegainControl();
	
	void SetSounds(PlayerAnimation animation);
	
	virtual void Jump() override;

	virtual void SpecialAbility();

	void MoveRightOrLeft(float value);

	bool IsJumping;
	bool IsFaceRight = true;
	bool IsSmashing;
	
	bool HasNoHand = false;



	void SetAnimationIdleNoHand(class UPaperFlipbook* NoHand);
};
