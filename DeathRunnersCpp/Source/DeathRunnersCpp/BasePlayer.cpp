// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlayer.h"

#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"



ABasePlayer::ABasePlayer()
{
	GetSprite()->SetIsReplicated(true);
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	playerInputComponent->BindAxis("MoveRightOrLeft", this, &ABasePlayer::MoveRightOrLeft);
	/*
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADeathRunnersCppCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADeathRunnersCppCharacter::TouchStopped);*/
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
}

void ABasePlayer::Smash(ABasePlayer other)
{
}

void ABasePlayer::SpecialAbility()
{
	
}

void ABasePlayer::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void ABasePlayer::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	UpdateCharacter();
}

void ABasePlayer::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}


