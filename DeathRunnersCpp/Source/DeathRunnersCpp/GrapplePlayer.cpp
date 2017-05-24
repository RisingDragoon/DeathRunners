// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "PaperFlipbookComponent.h"
#include "GrapplePlayer.h"
#include "Hand.h"


AGrapplePlayer::AGrapplePlayer()
{	
}


void AGrapplePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("SpecialAbility", IE_Released, this, &AGrapplePlayer::SpecialAbility);
}

void AGrapplePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AGrapplePlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		SpawnPosition = GetActorLocation() + SpawnPositionOffset;
		FVector direction = IsFaceRight ? FVector(1, 0, 1) : FVector(-1, 0, 1);
		FVector EndTrace = SpawnPosition + direction * ShotVelocity;
		FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);

		AHand* hand = GetWorld()->SpawnActor<AHand>(Hand, SpawnPosition, FRotator(0, 0, 0));
		if (hand)
		{
			if (!IsFaceRight)
			{
				UActorComponent* comp = hand->GetComponentByClass(UPaperFlipbookComponent::StaticClass());
				UPaperFlipbookComponent* flip = (UPaperFlipbookComponent*)comp;
				if (flip)
				{
					UE_LOG(LogTemp, Warning, TEXT("MANO RUOTATA"));
					flip->SetRelativeRotation(FRotator(0,180,0));
				}
			}
			hand->SetDirectionToGo(directionToGo, this);
		
			UE_LOG(LogTemp, Warning, TEXT("Mano lanciata"));
			SpecialAbilityIsReady = false;
			IsOutOfControl = true;
			SetSounds(PlayerAnimation::Skill);
			GetWorld()->GetTimerManager().SetTimer(TimerSpecialAbility, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Mano non spawnata"));
		}
	}
}

//
//void AGrapplePlayer::LogX(float value)
//{
//	if (value == 0 && LastAxisY == 0)
//	{
//		return;
//	}
//	if (value != LastAxisX)
//	{
//		LastAxisX = value;
//	}
//}
//
//void AGrapplePlayer::LogY(float value)
//{
//	if (value == 0 && LastAxisX == 0)
//	{
//		return;
//	}
//	if (value != LastAxisY)
//	{
//		LastAxisY = -value;
//	}
//}