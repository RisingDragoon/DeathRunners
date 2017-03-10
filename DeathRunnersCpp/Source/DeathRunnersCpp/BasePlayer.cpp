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
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddUnique(&ABasePlayer::SetPlayerToSmash);
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
	Super::Jump();
	UE_LOG(LogTemp, Warning, TEXT("Salto"));

}
void ABasePlayer::ChargeSmash()
{
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
			UE_LOG(LogTemp, Warning, TEXT("Carico e mi muovo di meta"));
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
	IsCharging = false;
	if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl && IsJumping)
	{
		if (PlayerToSmash->IsJumping)
		{
			IsOutOfControl = true;
			IsFalling = true;
			LaunchCharacter(FVector(0.0f, 0.0f, -SmashForce), false, false);
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::StopFalling, FallingTimeRate, false);
			//PlayerToSmash->StartFalling();
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
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
	IsOutOfControl = true;
	IsFalling = true;
	LaunchCharacter(FVector(0.0f, 0.0f, -SmashForce), false, false);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	IsOutOfControl = false;
	IsFalling = false;
}

void ABasePlayer::SpecialAbility()
{

}

void ABasePlayer::SetPlayerToSmash()
{

}

void ABasePlayer::ResetPlayerToSmash()
{

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
	else if (PlayerSpeedSqr > 0.0f)
	{
		DesiredAnimation = JumpingAnimation;
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
	if (IsCharging)
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
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::RegainControl, FallingTimeRate, false);
}

