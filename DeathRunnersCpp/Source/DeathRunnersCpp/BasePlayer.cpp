// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlayer.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "BasePlatform.h"
#include <string>


ABasePlayer::ABasePlayer()
{
	GetSprite()->SetIsReplicated(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	Timer = FTimerHandle();
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->OnComponentBeginOverlap.__Internal_AddDynamic(this, &ABasePlayer::SetPlayerToSmash, FName("SetPlayerToSmash"));
	capsule->OnComponentEndOverlap.__Internal_AddDynamic(this, &ABasePlayer::ResetPlayerToSmash, FName("ResetPlayerToSmash"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	//ParticleSystemCharging = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));

	static ConstructorHelpers::FObjectFinder<USoundBase> smashSound(TEXT("SoundWave'/Game/Sounds/dr_jump1.dr_jump1'"));
	SmashSound = CreateDefaultSubobject<UAudioComponent>(TEXT("sound"));
	//SoundWave'/Game/Sounds/dr_grab.dr_grab'
	SmashSound->SetSound(smashSound.Object);
	//ParticleSystemCharging->SetTemplate(PS.Object);
	//ParticleSystemCharging->Activate();
	//ParticleSystemCharging->SetActive(false);
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("MoveRightOrLeft", this, &ABasePlayer::MoveRightOrLeft);
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	playerInputComponent->BindAction("Smash", IE_Pressed, this, &ABasePlayer::ChargeSmash);
	playerInputComponent->BindAction("Smash", IE_Released, this, &ABasePlayer::Smash);
}

void ABasePlayer::Jump()
{
	//UE_LOG(LogTemp, Warning, TEXT("Salto"));
	Super::Jump();
	//SmashSound->Play(0.0);//VA BENE
}

void ABasePlayer::ChargeSmash()
{
	//UE_LOG(LogTemp, Warning, TEXT("ChargeSmash"));
	//ParticleSystemCharging->SetActive(true);
	//ParticleSystemCharging->Activate();
	IsCharging = true;
	//SmashForce += SmashChargeSpeed;
	//UE_LOG(LogTemp, Warning, TEXT("potenza pugno : FORZA %d SPEED %d"),SmashForce, SmashChargeSpeed);
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	UpdateCharacter();
	if (!IsOutOfControl)
	{
		if (IsCharging && !IsJumping)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Carico e mi muovo di meta"));
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value / 2);
		}
		else
		{
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
		}
	}
}

void ABasePlayer::Smash()
{
	//UE_LOG(LogTemp, Warning, TEXT("Tempo smash %f"), SmashingAnimation->GetTotalDuration());
	//ParticleSystemCharging->SetActive(false);
	IsCharging = false;
	if (IsJumping)
	{
		IsSmashing = true;
		float duration = SmashingAnimation->GetTotalDuration();
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::StopSmashing, duration, false);
		if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl)
		{
			if (PlayerToSmash->IsJumping)
			{
				//PlaySmashSound();
				UE_LOG(LogTemp, Warning, TEXT("Potenza pugno : FORZA %f "), SmashForce);
				PlayerToSmash->AppliedForce = SmashForce;
				PlayerToSmash->StartFalling();
			}
		}
	}
	SmashForce = 0;
}

void ABasePlayer::EnableSpecialAbility()
{
	//UE_LOG(LogTemp, Warning, TEXT("Abilita Pronta"));
	SpecialAbilityIsReady = true;
}

void ABasePlayer::StartFalling()
{
	//UE_LOG(LogTemp, Warning, TEXT("StartFalling"));
	IsOutOfControl = true;
	IsFalling = true;
	if (AppliedForce >= SmashForceLevel)
	{
		UE_LOG(LogTemp, Warning, TEXT("PUGNO CARICATO"));
		if (GetCapsuleComponent())
		{
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Capsule component null"));

		}
		LaunchCharacter(FVector(0.0f, 0.0f, -AppliedForce), false, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PUGNO BASE"));
		LaunchCharacter(FVector(0.0f, 0.0f, -BaseSmashForce), false, false);
	}
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	/*if (AppliedForce >= SmashForceLevel)
	{
		UE_LOG(LogTemp, Warning, TEXT("RITORNA A PAWN"));
	}*/
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	IsOutOfControl = false;
	IsFalling = false;
}

void ABasePlayer::StopSmashing()
{
	IsSmashing = false;
}

void ABasePlayer::SpecialAbility()
{
}


void ABasePlayer::PlaySmashSound()
{
}

void ABasePlayer::SetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("SetPlayerToSmash"));
	ABasePlayer* player = static_cast<ABasePlayer*>(OtherActor);
	if (player)
	{
		//UE_LOG(LogTemp, Warning, TEXT("CanSmash = true;"));
		CanSmash = true;
		PlayerToSmash = player;
	}
}

void ABasePlayer::ResetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("ResetPlayerToSmash"));
	ABasePlayer* player = static_cast<ABasePlayer*>(OtherActor);
	if (player)
	{
		//UE_LOG(LogTemp, Warning, TEXT("CanSmash = false;"));
		CanSmash = false;
		PlayerToSmash = nullptr;
	}
}

void ABasePlayer::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	
	//const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation;
	if (IsSmashing)
	{
		DesiredAnimation = SmashingAnimation;
	}
	else if (IsFalling)
	{
		DesiredAnimation = FallingAnimation;
	}
	else if (PlayerVelocity.Z > 0.0f)
	{
		DesiredAnimation = JumpingAnimation;
	}
	else if (PlayerVelocity.Z < 0.0f)
	{
		DesiredAnimation = DropAnimation;
	}
	else if (PlayerVelocity.X != 0.0f)
	{
		DesiredAnimation = RunningAnimation;
	}
	else
	{
		DesiredAnimation = IdleAnimation;
	}
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void ABasePlayer::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	UpdateCharacter();
	//ParticleSystemCharging->SetRelativeLocation(GetActorLocation());
	IsJumping = GetVelocity().Z != 0.0f;
	if (IsCharging && SmashForce < MaxSmashForce)
	{
		SmashForce += SmashChargeSpeed;
		//UE_LOG(LogTemp, Warning, TEXT("Potenza pugno : FORZA %f SPEED %f"), SmashForce, SmashChargeSpeed);
	}
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	//ParticleSystemCharging->SetActive(false);
}

void ABasePlayer::UpdateCharacter()
{
	UpdateAnimation();
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	if (Controller != nullptr)
	{
		//Ruota il Player
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("PlayerVelocity Z %f"), PlayerVelocity.Z);
	if (PlayerVelocity.Z > 0.0f)
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Jumping"));
	}
	else if (!IsFalling)
	{
		TArray<AActor*> overlappingPlatforms;
		GetOverlappingActors(overlappingPlatforms, TSubclassOf<ABasePlatform>());
		
		if (overlappingPlatforms.Num() == 0)
		{
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
		}
	}
}

void ABasePlayer::RegainControl()
{
	IsOutOfControl = false;
}

void ABasePlayer::LoseControl()
{
	IsOutOfControl = true;
	UE_LOG(LogTemp, Warning, TEXT("%s Loses control"), *GetName());

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::RegainControl, FallingTimeRate, false);
}
