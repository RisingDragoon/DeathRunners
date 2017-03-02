// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GunPlayer.h"
#include "DrawDebugHelpers.h"


void AGunPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("FireGun", IE_Released, this, &AGunPlayer::SpecialAbility);
	playerInputComponent->BindAxis("FireGunX", this, &AGunPlayer::LogX);
	playerInputComponent->BindAxis("FireGunY", this, &AGunPlayer::LogY);
}
void AGunPlayer::SpecialAbility()
{
	//if (SpecialAbilityIsReady)
		if (true)
	{
		//TODO: spara
		if (LastAxisX != 0 || LastAxisY != 0)
		{
			FVector direzione = FVector(LastAxisX, 0, LastAxisY);
			FVector location = GetActorLocation();
			FVector StartTrace = location;
			FVector EndTrace = location + direzione * 600;
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 0.f, 0, 10.f);

			UE_LOG(LogTemp, Warning, TEXT("Pistola usata"));
			SpecialAbilityIsReady = false;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
		}
	}
}


void AGunPlayer::LogX(float value)
{
	if (value == 0 && LastAxisY==0)
	{
		return;
	}
	if (value !=LastAxisX)
	{
		LastAxisX = value;
		SpecialAbility();
		UE_LOG(LogTemp, Warning, TEXT("AXIS X: %f"), LastAxisX);//X
	}
}

void AGunPlayer::LogY(float value)
{
	if (value == 0 && LastAxisX == 0)
	{
		return;
	}
	if (value != LastAxisY)
	{
		LastAxisY = -value;
		SpecialAbility();
		UE_LOG(LogTemp, Warning, TEXT("AXIS Y: %f"), LastAxisY);//Z
	}
}