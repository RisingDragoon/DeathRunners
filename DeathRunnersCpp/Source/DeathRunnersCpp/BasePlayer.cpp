// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlayer.h"

#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"



ABasePlayer::ABasePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Costruttore  "));
	GetSprite()->SetIsReplicated(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	FallingTime = FTimerHandle();
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("MoveRightOrLeft", this, &ABasePlayer::MoveRightOrLeft);
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	//playerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	playerInputComponent->BindAction("Smash", IE_Pressed, this, &ABasePlayer::Smash);
	playerInputComponent->BindAction("SmashDebug", IE_Pressed, this, &ABasePlayer::SmashDebug);
}

void ABasePlayer::Jump()
{
	ACharacter::Jump();
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	if (!IsOutOfControl)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
	}
}

void ABasePlayer::SmashDebug()
{
	if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl)//da aggiungere controllo isjumping
	{
		if (PlayerToSmash != nullptr)
		{
			StartFalling();
			//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
			//PlayerToSmash->StartFalling();
			//PlayerToSmash->AddMovementInput(FVector(0.0f, 0.0f, 1.0f), 100, true);
			//PlayerToSmash->LaunchCharacter(FVector(0.0f, 0.0f, 1000.0f), false, false);
		}
	}
}

void ABasePlayer::Smash()
{
	if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl)//da aggiungere controllo isjumping
	{
		if (PlayerToSmash != nullptr)
		{
			//StartFalling();
			//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
			PlayerToSmash->StartFalling();
			//PlayerToSmash->AddMovementInput(FVector(0.0f, 0.0f, 1.0f), 100, true);
			//PlayerToSmash->LaunchCharacter(FVector(0.0f, 0.0f, 1000.0f), false, false);
		}
	}
}

void ABasePlayer::StartFalling()
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	IsOutOfControl = true;
	IsFalling = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
	//FName s = GetCapsuleComponent()->GetCollisionProfileName();
	//UE_LOG(LogTemp, Warning, TEXT("Settata %s"), s.ToString() );
	GetWorld()->GetTimerManager().SetTimer(FallingTime,this, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	IsOutOfControl = false;
	IsFalling = false;
}

void ABasePlayer::SpecialAbility()
{

}

//void ABasePlayer::SetCanSmashTrue(class AActor* other)
//{
//	/*if (other->IsA<APaperCharacter*>())
//	{
//		CanSmash = true;
//	}*/
//}

//void ABasePlayer::SetCanSmashFalse(class AActor* other)
//{
//	CanSmash = true;
//}

void ABasePlayer::UpdateAnimation()
{
	/*if (AutoJump)
	{
		ACharacter::Jump();
	}*/
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
	
	UPaperFlipbook* DesiredAnimation;
	if (PlayerSpeedSqr > 0.0f)
	{
		DesiredAnimation = JumpingAnimation;
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

	if (PlayerVelocity.Z>0.0f)
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Jumping"));
	}
	else if(!IsFalling)
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	}
}


