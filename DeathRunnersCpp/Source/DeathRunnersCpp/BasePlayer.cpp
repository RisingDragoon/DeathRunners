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
	capsule->OnComponentEndOverlap.__Internal_AddDynamic(this, &ABasePlayer::ResetPlayerToSmash,FName("ResetPlayerToSmash"));
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
}

void ABasePlayer::ChargeSmash()
{
	//UE_LOG(LogTemp, Warning, TEXT("ChargeSmash"));
	IsCharging = true;
	//SmashForce += SmashChargeSpeed;
	//UE_LOG(LogTemp, Warning, TEXT("potenza pugno : FORZA %d SPEED %d"),SmashForce, SmashChargeSpeed);
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	UpdateCharacter();
	if (!IsOutOfControl)
	{
		if (IsCharging)
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
	UE_LOG(LogTemp, Warning, TEXT("Smash"));
	IsCharging = false;
	if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl && IsJumping)
	{
		if (PlayerToSmash->IsJumping)
		{
			UE_LOG(LogTemp, Warning, TEXT("Forza prima di StartFalling %f"), SmashForce);
			PlayerToSmash->AppliedForce = SmashForce;
			PlayerToSmash->StartFalling();
		}
	}
	SmashForce = 0;
	UE_LOG(LogTemp, Warning, TEXT("Forza dovrebbe essere 0 %f"), SmashForce);
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
		UE_LOG(LogTemp, Warning, TEXT("Il pugno è caricato"));
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
	}
	LaunchCharacter(FVector(0.0f, 0.0f, -AppliedForce), false, false);
	UE_LOG(LogTemp, Warning, TEXT("Forza %f"), AppliedForce);

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	UE_LOG(LogTemp, Warning, TEXT("StopFalling"));
	if (AppliedForce >= SmashForceLevel)
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	}
	IsOutOfControl = false;
	IsFalling = false;
}

void ABasePlayer::SpecialAbility()
{

}

void ABasePlayer::SetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation;
	if (IsFalling)
	{
		DesiredAnimation = FallingAnimation;
	}
	else if (PlayerVelocity.Z > 0.0f)
	{
		DesiredAnimation = JumpingAnimation;
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
	IsJumping = GetVelocity().SizeSquared() > 0.0f;
	if (IsJumping && IsCharging && SmashForce < MaxSmashForce)
	{
		SmashForce += SmashChargeSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Potenza pugno : FORZA %f SPEED %f"), SmashForce, SmashChargeSpeed);
	}
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
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
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

		if (overlappingPlatforms.Num() == 0)
		{
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
		}
		//UE_LOG(LogTemp, Warning, TEXT("overlappingPlatforms num %d"), overlappingPlatforms.Num());
	}
}

void ABasePlayer::RegainControl()
{
	IsOutOfControl = false;
}

void ABasePlayer::LoseControl()
{
	IsOutOfControl = true;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::RegainControl, FallingTimeRate, false);
}
