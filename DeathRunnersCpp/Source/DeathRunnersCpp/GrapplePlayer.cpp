// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GrapplePlayer.h"
#include "Hand.h"


AGrapplePlayer::AGrapplePlayer()
{	
}


void AGrapplePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("GunOrGrapple", IE_Released, this, &AGrapplePlayer::SpecialAbility);
	playerInputComponent->BindAxis("AxisX", this, &AGrapplePlayer::LogX);
	playerInputComponent->BindAxis("AxisY", this, &AGrapplePlayer::LogY);
}

void AGrapplePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AGrapplePlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		if (LastAxisY >= 0)
		{
			FVector direzione = FVector(LastAxisX, 0, LastAxisY);
			SpawnPosition = GetActorLocation() + SpawnPositionOffset;
			FVector EndTrace = SpawnPosition + direzione * 300;
			direzione = SpawnPosition + direzione;

			float base = EndTrace.X - SpawnPosition.X;
			float altezza = EndTrace.Z - SpawnPosition.Z;
			base = (base > 0) ? base : -base;
			altezza = (altezza > 0) ? altezza : -altezza;

			float value = sqrt(pow(2, (base)) + pow(2, (altezza)));
			//UE_LOG(LogTemp, Warning, TEXT("Modulo %f"), value);

			if (value > MinValueShot)
			{
				//DrawDebugLine(GetWorld(), SpawnPosition, EndTrace, FColor(255, 0, 0), true, 0.f, 0, 5.f);
				AHand* hand = GetWorld()->SpawnActor<AHand>(Hand, SpawnPosition, FRotator(0, 0, 0));
				FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);

				hand->SetDirectionToGo(directionToGo, this);
				UE_LOG(LogTemp, Warning, TEXT("Mano lanciata"));
				SpecialAbilityIsReady = false;
				GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nop"));
			}
		}
	}
}


void AGrapplePlayer::LogX(float value)
{
	if (value == 0 && LastAxisY == 0)
	{
		return;
	}
	if (value != LastAxisX)
	{
		LastAxisX = value;
	}
}

void AGrapplePlayer::LogY(float value)
{
	if (value == 0 && LastAxisX == 0)
	{
		return;
	}
	if (value != LastAxisY)
	{
		LastAxisY = -value;
	}
}

