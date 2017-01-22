// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlayer.h"

#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"



ABasePlayer::ABasePlayer()
{
	GetSprite()->SetIsReplicated(true);
	//OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPickup);
	//OnActorBeginOverlap.AddDynamic(this, &ABasePlayer::CheckCollision);
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	if(!IsOutOfControl)
	{ 
		playerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
		playerInputComponent->BindAxis("MoveRightOrLeft", this, &ABasePlayer::MoveRightOrLeft);
		playerInputComponent->BindAction("Smash", IE_Pressed, this, &ABasePlayer::Smash);
	}
	/*
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADeathRunnersCppCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADeathRunnersCppCharacter::TouchStopped);*/
}

void ABasePlayer::Jump()
{
	IsJumping = true;
	ACharacter::Jump();
	IsJumping = false;
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
}

void ABasePlayer::Smash()
{
	if (CanSmash && IsJumping)
	{
		if (PlayerToSmash != nullptr)
		{
			PlayerToSmash->StartFalling();
			PlayerToSmash->LaunchCharacter(FVector(0.0f, 0.0f, 1000.0f), false, false);
		}
	}
}

void ABasePlayer::StartFalling()
{
	IsOutOfControl = true;
	IsFalling = true;
	GetWorld()->GetTimerManager().SetTimer(FallingTime, &ABasePlayer::StopFalling, FallingTimeRate, false);
	//GetWorld()->GetTimerManager().SetTimer(FallingTime, other, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	IsOutOfControl = false;
	IsFalling = false;
	//GetWorld()->GetTimerManager().SetTimer(FallingTime, other, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

/*GetWorld()->GetTimerManager().SetTimer(FallingTime, this, &ASBombActor::StopFalling, MaxFuzeTime, false);*/

void ABasePlayer::SpecialAbility()
{

}

void ABasePlayer::SetCanSmashTrue(class AActor* other)
{
	/*if (other->IsA<APaperCharacter*>())
	{
		CanSmash = true;
	}*/
}

//void ABasePlayer::SetCanSmashFalse(class AActor* other)
//{
//	CanSmash = true;
//}

void ABasePlayer::UpdateAnimation()
{
	UPaperFlipbook* DesiredAnimation;
	if (IsJumping)
	{
		DesiredAnimation = RunningAnimation;
	}
	else if (IsFalling)
	{
		DesiredAnimation = FallingAnimation;
	}
	else
	{
		DesiredAnimation = IdleAnimation;
	}
	//UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
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

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
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


