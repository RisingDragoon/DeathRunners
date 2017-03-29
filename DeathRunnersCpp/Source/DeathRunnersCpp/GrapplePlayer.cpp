// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GrapplePlayer.h"
#include "Hand.h"
#include "DrawDebugHelpers.h"


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
			DrawDebugLine(GetWorld(), SpawnPosition, EndTrace, FColor(255, 0, 0), true, 0.f, 0, 5.f);
			AHand* hand = GetWorld()->SpawnActor<AHand>(Hand, SpawnPosition, FRotator());
			//AProjectile* hand = GetWorld()->SpawnActor<AProjectile>(Hand, SpawnPosition, FRotator());
			FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);

			//FVector directionToGo = FVector(direzione.X , 0, direzione.Z);
			//UE_LOG(LogTemp, Warning, TEXT("StartTrace x= %f,y = %f,  z=%f"), StartTrace.X, StartTrace.Y, StartTrace.Z);
			//UE_LOG(LogTemp, Warning, TEXT("EndTrace x= %f,y = %f,  z=%f"), EndTrace.X, EndTrace.Y, EndTrace.Z);
			//FVector directionToGo = location + 600;
			//directionToGo.Y = 0;
			//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), directionToGo.X, directionToGo.Y, directionToGo.Z);
			
			hand->SetDirectionToGo(directionToGo, this);
			UE_LOG(LogTemp, Warning, TEXT("Mano lanciata"));
			SpecialAbilityIsReady = false;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
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

