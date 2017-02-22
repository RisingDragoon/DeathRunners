// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BomberPlayer.h"


void ABomberPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("input setup"));
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("Bomb", IE_Released, this, &ABomberPlayer::SpecialAbility);
}

void ABomberPlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		UE_LOG(LogTemp, Warning, TEXT("Usata bomba"));
		SpecialAbilityIsReady = false;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
	}
}